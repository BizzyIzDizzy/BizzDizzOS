#include <monitor.h>
#include <common.h>
#include <string.h>

// VGA framebuffer starts at 0xB8000
u16int *video_memory = (u16int *)0xB8000;
// stores the cursor position
u8int cursor_x = 0;
u8int cursor_y = 0;

// updates the hardware cursor
static void move_cursor(){
	u16int cursorLocation = cursor_y*80 + cursor_x; // the screen is 80 chars wide
	outb(0x3d4, 14);				// tell the VGA board we are setting the high cursor byte
	outb(0x3d5, cursorLocation >> 8);		// send the high cursor byte
	outb(0x3d4, 15);				// tell the VGA board we are setting the low cursor byte
	outb(0x3d5, cursorLocation);			// send the low cursor byte
}

// scrolls the text on the screen up by one line
static void scroll(){
	// get a space character with the default color attributes
	u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
	u16int blank = 0x20 /*space*/ |(attributeByte << 8);
	
	// row 25 is the end, this means we need to scroll up
	if(cursor_y >= 25){
		// move the current text chunk that makes up the screen
		// back in the buffer by a line
		int i;
		for(i = 0*80; i<=24*80; i++){
			video_memory[i] = video_memory[i+80];	
		}
		
		// the last line should now be blank. Do this by writing 80 spaces to it
		for(i = 24*80; i<25*80; i++){
			video_memory[i] = blank;	
		}
		// the cursor should now be on the last line
		cursor_y = 24;
	}
}

// writes a single character out to the screen
void monitor_put(char c){
	// the background color is black (0), the foreground is white (15)
	u8int backColor = 0;
	u8int foreColor = 15;
	
	// the attribute byte is made up of two nibbles - the lower being the foreground color, and the upper background color
	u8int attributeByte = (backColor << 4) | (foreColor & 0x0F);
	// the attribute byte is the top 8 bits of the word we have to send to the VGA board
	u16int attribute = attributeByte << 8;
	u16int *location;
	
	// handle a backspace, by moving the cursor back one space
	if(c == 0x08 && cursor_x){
		cursor_x--;	
	}
	
	// handle a tab by increasing the cursor's X, but only to a point where it is divisible by 8
	else if(c == 0x09){
		cursor_x = (cursor_x+8) & ~(8-1);	
	}
	
	// handle carriage return
	else if(c == '\r'){
		cursor_x = 0;	
	}
	
	// handle newline by moving cursor back to left and increasing the row
	else if(c == '\n'){
		cursor_x = 0;
		cursor_y++;
	}
	
	// handle any other printable character
	else if(c >= ' '){
		location = video_memory +(cursor_y*80+cursor_x);
		*location = c | attribute;
		cursor_x++;
	}
	
	// check if we need to insert a new line because we have reached the end of the screen
	if(cursor_x >= 80){
		cursor_x = 0;
		cursor_y++;
	}
	
	// scroll the sceen if needed
	scroll();
	// move the hardware cursor
	move_cursor();
}
// clears the screen by copying lots of spaces to the framebuffer.
void monitor_clear(){
	// make an attribute byte for the default colors
	u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
	u16int blank = 0x20 /*space*/ | (attributeByte << 8);

	int i;
	for(i = 0; i<80*25; i++){
		video_memory[i] = blank;	
	}
	
	// move the hardware cursor back to the start
	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

// outputs a null-terminated ASCII string to the monitor
void monitor_write(char *c){
	int i = 0;
	while(c[i]){
		monitor_put(c[i++]);	
	}
}

// print 32bit integer as binary
void monitor_write_bin(u32int n){
	char buffer[33];	// 32 bits plus \0
	intToBinStr(n, buffer);
	strrev(buffer);
	monitor_write("0b");
	monitor_write(buffer);	
}


// print 32bit integer as hexadecimal value
void monitor_write_hex(u32int n){
	char buffer[9];
	intToHexStr(n, buffer);
	strrev(buffer);
	monitor_write("0x");
	monitor_write(buffer);
}
// print 32bit integer as decimal value
void monitor_write_dec(u32int n){
	char buffer[11]; 	// U_MAX_INT -> 2^32 has 10chars + \0
	intToStr(n, buffer);
	strrev(buffer);
	monitor_write(buffer);
}
