/*Name:Nandan Kumar T
Date:26/10/2025
Description:MP3 Tag Reader & Editor – Documentation*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3_header.h"

void edit_mp3(char *tag, char *newname, char *filename) {

    FILE *fptr = fopen(filename, "rb");
    if (!fptr) {
        printf(RED "File not Found !!!❌\n" RESET);
        return;
    }

    FILE *ftemp = fopen("temp.mp3", "wb");
    if (!ftemp) {
        printf(RED "Cannot create temp file !!! ❌\n" RESET);
        fclose(fptr);
        return;
    }

    // Copy MP3 header (10 bytes)
    unsigned char header[10];
    if (fread(header, 1, 10, fptr) != 10) {
        printf(RED "Failed to read header❌\n" RESET);
        fclose(fptr);
        fclose(ftemp);
        return;
    }
    fwrite(header, 1, 10, ftemp);

    // Process ID3v2 frames
    while (!feof(fptr)) {
        char TAG[5];
        if (fread(TAG, 1, 4, fptr) != 4) break;

        unsigned char sizebytes[4];
        if (fread(sizebytes, 1, 4, fptr) != 4) break;
        unsigned int size=big_to_little(sizebytes);
        // Sanity check for valid size
        if (size == 0 || size > 100000)
            break;
        unsigned char flag_bytes[2];
        if (fread(flag_bytes, 1, 2, fptr) != 2) break;
        
        char *data = malloc(size);
        if (!data) {
            free(data);
            break;
        }
        fread(data, 1, size, fptr);

        // If this is the tag to edit
        if (strcmp(tag, TAG) == 0) {
            unsigned int new_len = strlen(newname) + 1; // +1 for encoding byte
            unsigned char new_size_bytes[4];
            little_to_big(new_len, new_size_bytes);
            fwrite(TAG, 1, 4, ftemp);
            fwrite(new_size_bytes, 1, 4, ftemp);
            fwrite(flag_bytes, 1, 2, ftemp);

            unsigned char encoding = 0x00;
            fwrite(&encoding, 1, 1, ftemp);
            fwrite(newname, 1, new_len - 1, ftemp);
            printf(RED"changed %s :%s\n"RESET,TAG,newname);
        } else {
            // Copy original tag
            fwrite(TAG, 1, 4, ftemp);
            fwrite(sizebytes, 1, 4, ftemp);
            fwrite(flag_bytes, 1, 2, ftemp);
            fwrite(data, 1, size, ftemp);
        }
    }
    char ch;
    printf(CYAN"Coping the remaining data...\n"RESET);
    while (fread(&ch, 1, 1, fptr) == 1)
    {
        if (fwrite(&ch, 1, 1, ftemp) != 1)
        {
            printf(RED"❌ Error writing remaining byte to destination.\n"RESET);
            return ;
        }
    }  
    fclose(fptr);
    fclose(ftemp);
    remove(filename);
    rename("temp.mp3", filename);
    printf(MAGENTA"TAG edited successfully\n"RESET);
}

// Function to convert 4-byte big endian to little endian integer
unsigned int big_to_little(unsigned char bytes[4]) {
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

// Function to convert integer to 4-byte big endian format
void little_to_big(unsigned int size, unsigned char sizeBytes[4]) {
    sizeBytes[0] = (size >> 24) & 0xFF;
    sizeBytes[1] = (size >> 16) & 0xFF;
    sizeBytes[2] = (size >> 8) & 0xFF;
    sizeBytes[3] = size & 0xFF;
}

