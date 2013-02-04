#ifndef STRING_H
#define STRING_H
#include <common.h>

void intToHexStr(u32int n, char *buffer);
void intToBinStr(u32int n, char *buffer);
void intToStr(u32int n, char *buffer);

u32int strlen(char *str);
void strrev(char *str);

/* Compare S1 and S2, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
int strcmp(const char *str1, const char *str2);

/* Compare no more than N characters of S1 and S2,
   returning less than, equal to or greater than zero
   if S1 is lexicographically less than, equal to or
   greater than S2.  */
int strncmp(const char *str1, const char *str2, u32int n);

/* Copy SRC to DEST.  */
char *strcpy(char *dest, const char *src);

/* Append SRC on the end of DEST.  */
char *strcat(char *dest, const char *src);

#endif//STRING_H
