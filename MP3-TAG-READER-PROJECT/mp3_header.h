/*Name:Nandan Kumar T
Date:26/10/2025
Description:MP3 Tag Reader & Editor – Documentation*/

#ifndef CUSTOMER_H
#define CUSTOMER_H

#define RED     "\033[1;31m"
#define YELLOW  "\033[4;33m"
#define YELLOW1  "\033[1;33m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m" 
#define MAGENTA "\033[1;35m"
#define RESET   "\033[0m" 

void view_mp3();
void edit_mp3();
void help_main();
void Eror();
void little_to_big(unsigned int,unsigned char *);
unsigned int big_to_little(unsigned char *);

#endif
