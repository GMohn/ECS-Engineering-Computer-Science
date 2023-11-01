#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

#include "disk.h"
#include "fs.h"

const char DELETE_NULL = '\0';
const uint16_t FAT_EOC = 0xFFFF;

const char signature[] = "ECS150FS";

/* TODO: Phase 1 */
struct __attribute__((__packed__)) super_block {
	char signature[8];	//ECS150FS
	uint16_t total_blocks;
	uint16_t r_dir_block_index;
	uint16_t data_block_start_index;
	uint16_t amount_of_data_blocks;
	uint8_t fat_blocks;
	int8_t padding[4079]; //4079 bytes
};

uint16_t* ptr_to_fat_array;

struct __attribute__((__packed__)) rd_file {
	char filename[16];	//last byte is null character
	uint32_t file_size;
	uint16_t first_block_index;
	uint64_t padding;//8bytes
	uint16_t padding2;//2bytes
};

struct __attribute__((__packed__)) fd_o {
	char filename[16];
	int fd;
	size_t offset;
	size_t file_size;
	int first_block_index;
};

struct super_block sb;
struct fat *fat;
struct rd_file rd_array[128]; 
struct fd_o fd_array[32];
int mounted = -1;
int file_count = 0;
int open_file_count = 0;
int fat_used = 0;

//int fs_close(int fd);



int fs_mount(const char *diskname)
{
	if(block_disk_open(diskname) == -1)
		return -1;

	int block_count = block_disk_count();
	int fat_count = (block_count*2+BLOCK_SIZE-1)/BLOCK_SIZE;
	int8_t *block_temp = malloc(BLOCK_SIZE * sizeof(int8_t));

	//load the first block into the super block struct
	block_read(0, block_temp);
	for(int i=0; i<8; i++) {
		sb.signature[i] = *(block_temp + sizeof(char)*i);
		if(sb.signature[i] != signature[i])
			return -1;
	}
	sb.total_blocks = *(uint16_t*)(block_temp+8*sizeof(char));
	sb.r_dir_block_index = *(uint16_t*)(block_temp+10*sizeof(char));
	sb.data_block_start_index = *(uint16_t*)(block_temp+12*sizeof(char));
	sb.amount_of_data_blocks = *(uint16_t*)(block_temp+14*sizeof(char));
	sb.fat_blocks = *(block_temp+16*sizeof(char));

	//load the following block[s] into FAT struct
	fat = malloc(fat_count*BLOCK_SIZE);
	ptr_to_fat_array = malloc(fat_count*BLOCK_SIZE);
	for(int i=0; i<fat_count; i++) {
		block_read(i+1, ptr_to_fat_array + i*BLOCK_SIZE);
	}

	//load the final block into the root directory struct
	block_read(fat_count+1, block_temp);
	for(int i=0;i<128;i++) {
		int file_offset = sizeof(struct rd_file);
		for(int j=0;j<16;j++) {
			rd_array[i].filename[j] = *(block_temp + file_offset*i + j);
		}
		if(rd_array[i].filename[0] != DELETE_NULL) {
			file_count++;
		}
		rd_array[i].file_size = *(uint32_t*)(block_temp + file_offset*i + sizeof(rd_array[i].filename)); //memcpy???
		rd_array[i].first_block_index = *(uint16_t*)(block_temp + file_offset*i + sizeof(rd_array[i].filename) + sizeof(rd_array[i].file_size));

	}

	//count fat used
	for(int i=0; i<sb.amount_of_data_blocks;i++) {
		if(*(ptr_to_fat_array + i) != 0) {
			fat_used++;
		}
	}

	//set all slots in fd_array to available
	for(int i=0;i<32;i++) {
		fd_array[i].fd = -1;
	}

	free(block_temp);
	mounted = 0;
	return 0;
	
}

int fs_umount(void)
{
	if(mounted == -1)
		return -1;
	//write metadata and file information to the disk before closing
	int block_count = block_disk_count();
	int fat_count = (block_count*2+BLOCK_SIZE-1)/BLOCK_SIZE;
	int ret;

	ret = block_write(0, &sb);
	if(ret == -1) {
		return -1;
	}

	for(int i=0; i<fat_count; i++) {
		ret = block_write(i+1, ptr_to_fat_array + i*BLOCK_SIZE/2);
		if(ret == -1) {
			return -1;
		}
	}

	ret = block_write(fat_count+1, rd_array);
	if(ret == -1) {
		return -1;
	}

	//close all open files
	for(int i=0; i < 32;i++) {
		if(fd_array[i].fd != -1) {
			ret = fs_close(i);
			if(ret == -1)
				return -1;
		}
	}

	free(fat);
	
	if(block_disk_close() == -1)
		return -1;

	mounted = -1;
	file_count = 0;
	open_file_count = 0;
	fat_used = 0;

	return 0;
}

int fs_info(void)
{
	/*	
		**Reference Output from CSIF**
		**./test_fs.x info disk.fs**
		FS Info:
		total_blk_count=8198
		fat_blk_count=4
		rdir_blk=5
		data_blk=6
		data_blk_count=8192
		fat_free_ratio=8191/8192
		rdir_free_ratio=128/128	
	*/
	if(mounted == -1)
		return -1;
	

	printf("FS Info:\n");
	printf("total_blk_count=%d\n", sb.total_blocks);
	printf("fat_blk_count=%d\n", sb.fat_blocks);
	printf("rdir_blk=%d\n", sb.r_dir_block_index);
	printf("data_blk=%d\n", sb.data_block_start_index);
	printf("data_blk_count=%d\n", sb.amount_of_data_blocks);
	printf("fat_free_ratio=%d/%d\n", sb.amount_of_data_blocks-fat_used, sb.amount_of_data_blocks);	//fix this!!!
	printf("rdir_free_ratio=%d/%d\n", 128-file_count, 128);

	// printf("\n\nTHE FAT:\n");
	// for(int i=0;i<sb.amount_of_data_blocks;i++) {
	// 	printf("index = %d; value = %d\n", i, *(ptr_to_fat_array+i));
	// }
	// printf("\n\nTHE RD\n");
	// for(int i=0;i<128;i++) {
	// 	printf("i = %d; file = %s\n", i, rd_array[i].filename);
	// }

	return 0;
}

int fs_create(const char *filename)
{
	if(mounted == -1 || strlen(filename) > 16 || file_count > 127)
		return -1;

	//check to make sure filename doesn't already exist
	for(int i=0; i<128; i++) {
		if(!strcmp(rd_array[i].filename, filename)) {
			return -1;
		}
	}

	//find index of NULL character start that signifies empty spot
	int file_offset = -1;
	for(int i=0; i<128; i++) {
		if(rd_array[i].filename[0] == DELETE_NULL) {
			file_offset = i;
			break;
		}
	}
	
	//update rd_array
	strcpy(rd_array[file_offset].filename, filename);
	rd_array[file_offset].file_size = 0;
	rd_array[file_offset].first_block_index = FAT_EOC; //fat_index
	file_count++;

	return 0;
}

int fs_delete(const char *filename)
{
	if(mounted == -1 || strlen(filename) > 16)
		return -1;

	//search for the index of the filename
	int file_offset = -1;
	for(int i=0; i<128; i++) {
		if(!strcmp(rd_array[i].filename, filename)) {
			file_offset = i;
			break;
		}
		if(i == 127)
			return -1;
	}

	//free fat if applicable
	int fat_index = rd_array[file_offset].first_block_index;
	if(fat_index != FAT_EOC) {	
		int current = *(ptr_to_fat_array+fat_index);
		while(current != FAT_EOC) {
			int temp = current;
			*(ptr_to_fat_array+fat_index) = 0;
			fat_index = temp;
			current = *(ptr_to_fat_array+fat_index);
			fat_used--;
		}
		*(ptr_to_fat_array+fat_index) = 0;
		fat_used--;
	}

	//update rd_array
	rd_array[file_offset].filename[0] = DELETE_NULL;
	rd_array[file_offset].file_size = 0;
	rd_array[file_offset].first_block_index = FAT_EOC;
	file_count--;

	return 0;
}

int fs_ls(void)
{
	/*
		**Reference output from CSIF**
		**./test_fs.x ls disk2.fs**
		FS Ls:
		file: fuck_it, size: 0, data_blk: 65535
		file: ur_mum, size: 0, data_blk: 65535
		file: fs_make.x, size: 22424, data_blk: 1
		file: yoyo, size: 0, data_blk: 65535
	*/
	if(mounted == -1)
		return -1;
	printf("FS Ls:\n");
	for(int i=0;i<128;i++) {
		if(rd_array[i].filename[0] != DELETE_NULL) {
			printf("file: %s, size: %u, data_blk: %u\n", rd_array[i].filename, rd_array[i].file_size, rd_array[i].first_block_index);
		}
	}
	
	return 0;
}

int fs_open(const char *filename)
{
	if(mounted == -1 || strlen(filename) > 16)
		return -1;

	//check to see if filename exists in fs
	for(int i=0; i<128; i++) {
		if(!strcmp(rd_array[i].filename, filename)) {
			break;
		}
		if(i == 127)
			return -1;
	}

	//find available fd_array slot
	int fd_index;
	for(int i=0; i<32; i++) {
		if(fd_array[i].fd == -1) {
			fd_index = i;	
			break;
		}
		if(i==31)
			return -1;
	}

	//gather data from rd
	for(int i=0; i<128; i++) {
		if(!strcmp(rd_array[i].filename, filename)) {
			fd_array[fd_index].first_block_index = rd_array[i].first_block_index;
			fd_array[fd_index].file_size = rd_array[i].file_size;
		}
	}

	//update fd_array
	fd_array[fd_index].fd = fd_index;
	fd_array[fd_index].offset = 0;
	strcpy(fd_array[fd_index].filename, filename);
	open_file_count++;

	return fd_index;
}

int fs_close(int fd)
{
	if(mounted == -1 || fd < 0 || fd > 31) 
		return -1;
	
	//update fd_array
	fd_array[fd].fd = -1;
	fd_array[fd].file_size = 0;
	fd_array[fd].first_block_index = 0;
	fd_array[fd].offset = 0;
	open_file_count--;
	
	return 0;
}

int fs_stat(int fd)
{
	if(mounted == -1 || fd < 0 || fd > 31)
		return -1;

	return fd_array[fd].file_size;
}

int fs_lseek(int fd, size_t offset)
{
	if(mounted == -1 || fd < 0 || fd > 31 || offset > fd_array[fd].file_size) 
		return -1;

	fd_array[fd].offset = offset;

	return 0;
}

int available_fat_entry() {
	//allocate a fat space if file is empty
	int fat_index = 0;
	//int offset = sizeof(uint16_t);
	int end_index = sb.amount_of_data_blocks;
	while(fat_index != end_index) {	//make this a function
		if(*(ptr_to_fat_array+fat_index) == 0) {
			return fat_index;
		} 
		fat_index++;
	}
	return -1;
}

int fs_write(int fd, void *buf, size_t count)
{
	if(mounted == -1 || fd < 0 || fd > 31 || buf==NULL || sb.amount_of_data_blocks-fat_used==0 || fd_array[fd].offset>fd_array[fd].file_size)
		return -1;

	int bytes_written = 0;
	int current_index = fd_array[fd].first_block_index;
	if(current_index == FAT_EOC) {
		current_index = available_fat_entry();
		if(current_index == -1)
				return bytes_written;
		fd_array[fd].first_block_index = current_index;
		*(ptr_to_fat_array+current_index) = FAT_EOC;
	}

	int offset = fd_array[fd].offset;
	int file_size = fd_array[fd].file_size;
	int bytes_to_be_written = count;

	int starting_index = offset/BLOCK_SIZE;
	for(int i=0; i<starting_index; i++) {
		current_index = *(ptr_to_fat_array+current_index);
	}
	size_t num_of_loops = (offset+count+BLOCK_SIZE-1)/BLOCK_SIZE;
	
	void *temp = malloc(BLOCK_SIZE);

	for(size_t i=0; i<num_of_loops; i++) {
		if(sb.amount_of_data_blocks-fat_used == 0)	//fat full
			break;
		int mod_offset = offset%BLOCK_SIZE;
		block_read(sb.data_block_start_index + current_index, temp);
		if(offset % BLOCK_SIZE != 0) {	//overwriting
			int sum = mod_offset+bytes_to_be_written;
			if(sum <= BLOCK_SIZE) {	//start and finish block
				memcpy(temp+mod_offset, buf, bytes_to_be_written);
				block_write(sb.data_block_start_index + current_index, temp);
				bytes_written += bytes_to_be_written;
				offset += bytes_to_be_written;
				break;
			} else {	//start block
				memcpy(temp+mod_offset, buf, BLOCK_SIZE-mod_offset);
				block_write(sb.data_block_start_index + current_index, temp);
				bytes_written+=(BLOCK_SIZE-mod_offset);
				offset+=(BLOCK_SIZE-mod_offset);
				bytes_to_be_written-=bytes_written;
			}
		} else {
			if(bytes_to_be_written<=BLOCK_SIZE) {
				memcpy(temp, buf, bytes_to_be_written);
				block_write(sb.data_block_start_index + current_index, temp);
				bytes_written += bytes_to_be_written;
				offset += bytes_to_be_written;
				break;
			} else {
				memcpy(temp, buf, BLOCK_SIZE);
				block_write(sb.data_block_start_index + current_index, temp);
				bytes_written+=(BLOCK_SIZE);
				offset+=(BLOCK_SIZE-mod_offset);
				bytes_to_be_written-=bytes_written;
			}
		}
		if(*(ptr_to_fat_array+current_index) == FAT_EOC) {
			current_index = available_fat_entry();
			if(current_index == -1)
				return bytes_written;
			*(ptr_to_fat_array+current_index) = FAT_EOC;
		} else {
			current_index = *(ptr_to_fat_array+current_index);
		}
		
	}
	free(temp);
	if(file_size < offset+bytes_written) {
		file_size = offset+bytes_written;
	}
	//update the rd 
	int rd_index = 0;
	for(int i=0; i<128; i++) {
		if(!strcmp(rd_array[i].filename, fd_array[fd].filename)) {
			rd_index = i;
		}
	}
	rd_array[rd_index].file_size += bytes_written; 
	
	fd_array[fd].file_size = file_size;
	fd_array[fd].offset = offset;

	return bytes_written;
}

int fs_read(int fd, void *buf, size_t count)
{
	if(mounted == -1 || fd < 0 || fd > 31 || buf==NULL || fd_array[fd].file_size == 0)
		return -1;

	int bytes_read = 0;
	int file_size = fd_array[fd].file_size;
	int offset = fd_array[fd].offset;
	int current_index = fd_array[fd].first_block_index;
	int bytes_to_be_read = file_size - offset;
	if(bytes_to_be_read > (int)count)
		bytes_to_be_read = count;
	int starting_index = offset/BLOCK_SIZE;
	for(int i=0; i<starting_index; i++)
		current_index = *(ptr_to_fat_array+current_index);
	int num_of_loops = ((bytes_to_be_read)+BLOCK_SIZE-1)/BLOCK_SIZE;

	void *temp = malloc(num_of_loops*BLOCK_SIZE*sizeof(char));
	for(int i=0; i<num_of_loops; i++) {
		int mod_offset = offset%BLOCK_SIZE;
		block_read(sb.data_block_start_index + current_index, temp+i*BLOCK_SIZE);
		if(mod_offset != 0) {	//offset is in the middle of the block somewhere
			int sum = mod_offset+bytes_to_be_read;
			if(sum < BLOCK_SIZE) {	//start and finish block
				memcpy(buf, temp+mod_offset, bytes_to_be_read);
				bytes_read += bytes_to_be_read;
				offset +=bytes_to_be_read;
				break;
			} else {	//start block
				memcpy(buf, temp+mod_offset, BLOCK_SIZE-mod_offset);
				bytes_read+=(BLOCK_SIZE-mod_offset);
				offset+=(BLOCK_SIZE-mod_offset);
				bytes_to_be_read-=bytes_read;
			}
		} else {	//offset is even with start of block
			if(bytes_to_be_read<BLOCK_SIZE) {	//finish block
				memcpy(buf, temp, bytes_to_be_read);
				bytes_read += bytes_to_be_read;
				offset +=bytes_to_be_read;
				break;
			} else {	//middle block
				memcpy(buf, temp, BLOCK_SIZE);
				bytes_read+=BLOCK_SIZE;
				offset+=BLOCK_SIZE;
				bytes_to_be_read-=bytes_read;
			}
		}
		current_index = *(ptr_to_fat_array+current_index);
	}

	fd_array[fd].offset = offset;
	free(temp);

	return bytes_read;
}

