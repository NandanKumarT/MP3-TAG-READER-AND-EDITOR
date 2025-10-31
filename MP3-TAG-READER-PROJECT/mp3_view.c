/*Name:Nandan Kumar T
Date:26/10/2025
Description:MP3 Tag Reader & Editor – Documentation*/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "mp3_header.h"
char *tag_list[] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "TCOM","COMM","APIC"};
char *desc[]     = {"Title", "Artist", "Album", "Year", "Content Type", "Composer","Comment","Attached Picture"};
void view_mp3(const char *filename){
    unsigned char sizebytes[4];
    //open the file in read mode
    FILE *fptr=fopen(filename,"r");
    if(fptr==NULL)
    {
        printf(RED"FILE NOT FOUND !!!\n"RESET);
        exit(0);
    }
    //read 1st 3bytes from the file
    char id3[4];
    fread(id3,(sizeof(id3)-1),1,fptr);
    if(strcmp(id3,"ID3")==0)
    {
        printf(YELLOW1"\nIt is a Mp3 file\n"RESET);
    }
    else
    {
        printf(RED"It is not a Mp3 file\n"RESET);
        exit(0);
    }
    fseek(fptr,7,SEEK_CUR);
    printf(YELLOW"\n==============================> MP3 TAG VIEW <====================================\n\n"RESET);
    int i=0;
    while(i<7){
        //skip the next 7 bytes
        char TAG[5];
        fread(TAG,(sizeof(TAG)-1),1,fptr);
        TAG[4] = '\0';
        //read 4 bytes from the file(size))
        fread(sizebytes,4,1,fptr);
        unsigned int size=big_to_little(sizebytes);
        //skip 2 byte 
        fseek(fptr,2,SEEK_CUR);
        //read size no of bytes and print the output using fread() or character by character
        char *data = malloc(size + 1);
        if(data==NULL){
            printf("memory not allocated");
            return;
        }
        fread(data, 1, size, fptr);
        data[size] = '\0';
        for (int j = 0; j < 8; j++) {
            if (strcmp(TAG, tag_list[j]) == 0) {
                printf(CYAN"%-20s :  %s\n"RESET, desc[j], data + 1);
            }
        }
        i++;
    }
    printf(YELLOW"\n=================================================================================\n\n"RESET);

}