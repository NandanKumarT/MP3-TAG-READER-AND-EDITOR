/* Name: Nandan Kumar T
   Date: 26/10/2025
   Description: MP3 Tag Reader & Editor – Documentation
*/

#include<stdio.h>
#include<string.h>
#include "mp3_header.h"

int main(int argc, char *argv[])
{
    // Check if the user wants to view MP3 tags
    if(argc == 3 && (strcmp(argv[1], "-v") == 0))
    {
        view_mp3(argv[2]); // Call view function with file name
    }
    // Check if the user wants to edit MP3 tags
    else if(argc == 5 && (strcmp(argv[1], "-e") == 0))
    {
        // Edit title tag
        if(strcmp(argv[2], "-t") == 0)
        {
            edit_mp3("TIT2", argv[3], argv[4]);
        }
        // Edit artist tag
        else if(strcmp(argv[2], "-a") == 0)
        {
            edit_mp3("TPE1", argv[3], argv[4]);
        }
        // Edit album tag
        else if(strcmp(argv[2], "-A") == 0)
        {
            edit_mp3("TALB", argv[3], argv[4]);
        }
        // Edit year tag
        else if(strcmp(argv[2], "-y") == 0)
        {
            edit_mp3("TYER", argv[3], argv[4]);
        }
        // Edit genre tag
        else if(strcmp(argv[2], "-C") == 0)
        {
            edit_mp3("TCON", argv[3], argv[4]);
        }
        // Edit comments tag
        else if(strcmp(argv[2], "-c") == 0)
        {
            edit_mp3("COMM", argv[3], argv[4]);
        }
        // If none match, show help
        else
        {
            help_main();
        }
    }
    // Show help if user passes --help
    else if(argc == 2 && (strcmp(argv[1], "--help") == 0))
    {
        help_main();
    }
    // Handle invalid commands
    else
    {
        Eror(); // Call error function
    }
}

// Function to display help menu
void help_main() {
    printf(YELLOW"\n=================> HELP <=======================\n\n"RESET);

    printf(CYAN"1. -v  --> to view mp3 file data\n");
    printf("2. -e  --> to edit mp3 file data\n");
    printf("\t2.1 -t --> to edit song title\n");
    printf("\t2.1 -a --> to edit artist name\n");
    printf("\t2.1 -A --> to edit album name\n");
    printf("\t2.1 -y --> to edit year\n");
    printf("\t2.1 -C --> to edit content\n");
    printf("\t2.1 -c --> to edit comment\n"RESET);

    printf(YELLOW"\n================================================\n\n"RESET);
}

// Function to display error message for invalid arguments
void Eror() {
    printf(GREEN"\n=================> ERROR <=======================\n\n"RESET);
    printf(RED"ERROR : INVALID ARGUMENTS.\n"RESET);
    printf(MAGENTA"\nUSAGE:"RESET CYAN"\nTo VIEW pass like : ./a.out -v <filename>\n");
    printf("To EDIT pass like : ./a.out -e <option> (-t/-a/-A/-y/-C/-c) new_data <filename>\n"RESET);
    printf(CYAN"To get help pass like : ./a.out --help\n"RESET);
    printf(GREEN"\n==================================================\n\n"RESET);
}
