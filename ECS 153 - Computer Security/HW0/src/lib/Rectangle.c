
#include "Rectangle.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

DEFINE_STRUCT(Rectangle)

// Constructor for Rectangle
void *new_Rectangle(char *string) {
    Rectangle *rect = (Rectangle *)malloc(sizeof(Rectangle));
    sscanf(string, "%d %d", &(rect->height), &(rect->width));
    // Set the GenericTraits implementation
    rect->impl = malloc(sizeof(GenericTraits));
    rect->impl->new = new_Rectangle;
    rect->impl->dump = dump_Rectangle;
    rect->impl->cmp = cmp_Rectangle;
    rect->impl->drop = drop_Rectangle;
    return rect;
}

// Dump function for Rectangle
void dump_Rectangle(void *this, FILE *fp) {
    Rectangle *rect = (Rectangle *)this;
    fprintf(fp, "%d %d\n", rect->height, rect->width);
}

int cmp_Rectangle(void *this1, void *this2) {
    Rectangle *rect1 = (Rectangle *)this1;
    Rectangle *rect2 = (Rectangle *)this2;

    //printf("Rectangle 1: height=%d, width=%d\n", rect1->height, rect1->width);
    //printf("Rectangle 2: height=%d, width=%d\n", rect2->height, rect2->width);
    // Compare areas
    long long area1 = (long long)rect1->height * rect1->width;
    long long area2 = (long long)rect2->height * rect2->width;
    //printf("Comparing areas: %lld vs %lld\n", area1, area2);
    if (area1 != area2)
        return (area1 < area2) ? -1 : 1;

    // Compare heights
    //printf("Areas are equal. Comparing heights: %d vs %d\n", rect1->height, rect2->height);
    if (rect1->height < rect2->height) {
        //printf("%d < %d, returning -1\n", rect1->height, rect2->height);
        return -1;
    }
    else if (rect1->height > rect2->height) {
        //printf("%d > %d, returning 1\n", rect1->height, rect2->height);
        return 1;
    }

    // Compare widths
    //printf("Heights are equal. Comparing widths: %d vs %d\n", rect1->width, rect2->width);
    if (rect1->width < rect2->width) {
        //printf("%d < %d, returning -1\n", rect1->width, rect2->width);
        return -1;
    }
    else if (rect1->width > rect2->width) {
        //printf("%d > %d, returning 1\n", rect1->width, rect2->width);
        return 1;
    }

    // All properties are equal
    //printf("Widths are equal. Returning 0\n");
    return 0;
}






