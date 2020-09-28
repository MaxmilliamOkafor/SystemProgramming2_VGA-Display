#include "types.h"
#include "user.h"

int main (int argc, char* argv[])
{
	setvideomode(0x13);
	clearscreen();
		for (int i = 0 ; i < 16; i++)
		{ 
			drawline(0, i * 10, 319, 199 - (i * 10), i);
			drawline(319, i * 10, 0, 199 - (i * 10), i);
		}
	// setpixel(150, 150, 7);
	getch();
	setvideomode(0x03);
	exit();

}
