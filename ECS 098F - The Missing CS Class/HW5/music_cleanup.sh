#!/usr/bin/bash

getArtistName() {
    # I wrote this one to take one argument and set a global variable to the 
    # artist's name with whitespace removed
    # Note that this is where you'll want/need to use ffprobe
    echo "$FILE"
    artist_name="$(ffprobe -loglevel error -show_entries format_tags=artist -of default=noprint_wrappers=1:nokey=1 "$FILE")"
    artist_name="${artist_name// /}"
    #echo $artist_name
    getSongName "$FILE" artist_name
    :;
}

getSongName() {
    # Same deal as getArtistName but with the song name
    # Note that this is where you'll want/need to use ffprobe
    song_name="$(ffprobe -loglevel error -show_entries format_tags=title -of default=noprint_wrappers=1:nokey=1 "$FILE")" 
    #echo $artist_name
    song_name="${song_name// /}"
    #echo $song_name 
    doConversion "$FILE" artist_name song_name
    :;
}

doConversion() {
    # This function performs the conversion on a single file   
    new_file_name=${artist_name}_${song_name}.mp3
    ffmpeg -i "$FILE" -vn -ar 44100 -ac 2 -b:a 192k "$TARGET_DIR"/"${new_file_name}"
    rm "$FILE"
    #echo "$new_file_name"
    :;
}

# Takes one argument, that being a directory
TARGET_DIR=$1

# Now we should iterate over every file in the directory and do the conversion
# for each file
#echo $TARGET_DIR
for FILE in "$TARGET_DIR"/*; do getArtistName "$FILE"; done
#for new_file in $(find -name "*.mp3"); do mv "$new_file" "$TARGET_DIR"/; done