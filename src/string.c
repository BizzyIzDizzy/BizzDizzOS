#include <string.h>
#include <common.h>

void intToStr(u32int n, char *buffer){
	int i = 0;
	char c;
	while(n!=0){
		c=48+(n%10);
		n/=10;		
		buffer[i++]=c;
	}
	buffer[i]='\0';
}

void intToBinStr(u32int n, char *buffer){
	int i = 0;
	char c;
	while(n!=0){
		c=48+(n%2);
		n/=2;
		buffer[i++]=c;
	}
	buffer[i]='\0';
}

void intToHexStr(u32int n, char *buffer){
	int i = 0;
	char c;
	while(n!=0){
		int mod=n%16;
		n/=16;
		if(mod<10){
			c = 48+mod; // 0-9
		}else{
			c = 55+mod; // A-F
		}
		buffer[i++]=c;
	}
	buffer[i]='\0';
}

u32int strlen(char *str){
	u32int length = 0;	
	while(str[length]){
		length++;	
	}
	return length;
}

void strrev(char *str){
	int length, c;
	char *begin, *end, temp;
	
	length = strlen(str);
	
	begin = str;
	end = str;
	
	for ( c = 0 ; c < ( length - 1 ) ; c++ ){
		end++;
	}
	
	for ( c = 0 ; c < length/2 ; c++ ){        
		temp = *end;
		*end = *begin;
		*begin = temp;
		
		begin++;
		end--;
	}  
}

int strncmp(const char *str1, const char *str2, u32int n){
	  unsigned char c1 = '\0';
	  unsigned char c2 = '\0';

	  if (n >= 4)
	    {
	      u32int n4 = n >> 2;
	      do
		{
		  c1 = (unsigned char) *str1++;
		  c2 = (unsigned char) *str2++;
		  if (c1 == '\0' || c1 != c2)
		    return c1 - c2;
		  c1 = (unsigned char) *str1++;
		  c2 = (unsigned char) *str2++;
		  if (c1 == '\0' || c1 != c2)
		    return c1 - c2;
		  c1 = (unsigned char) *str1++;
		  c2 = (unsigned char) *str2++;
		  if (c1 == '\0' || c1 != c2)
		    return c1 - c2;
		  c1 = (unsigned char) *str1++;
		  c2 = (unsigned char) *str2++;
		  if (c1 == '\0' || c1 != c2)
		    return c1 - c2;
		} while (--n4 > 0);
	      n &= 3;
	    }

	  while (n > 0)
	    {
	      c1 = (unsigned char) *str1++;
	      c2 = (unsigned char) *str2++;
	      if (c1 == '\0' || c1 != c2)
		return c1 - c2;
	      n--;
	    }

	  return c1 - c2;

}

int strcmp(const char *str1, const char *str2){
	  register const unsigned char *s1 = (const unsigned char *) str1;
	  register const unsigned char *s2 = (const unsigned char *) str2;
	  unsigned char c1, c2;

	  do
	    {
	      c1 = (unsigned char) *s1++;
	      c2 = (unsigned char) *s2++;
	      if (c1 == '\0')
		return c1 - c2;
	    }
	  while (c1 == c2);

	  return c1 - c2;
}

char *strcpy(char *dest, const char *src){
	do{
		*dest++ = *src++;
	}while(*src != 0);

	return dest;
}

char *strcat(char *dest, const char *src){
	while(*dest != 0){
		*dest = *dest++;
	}

	do{
		*dest++ = *src++;
	}while(*src != 0);

	return dest;
}
