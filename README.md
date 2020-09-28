# SystemProgramming2_VGA-Display

Made improvements from my previous project (SystemProgramming_using_Intel_Intel_x86assembler) and starting playing around set pixel on screen operated by VGA Display.

- I added several functions:

- I created a function of Setvideomode which switches text mode into videomode and setpixel whilst adding some parameters.

- I created a new function of clearscreen by setting the value 0 to the memory location that was provided (0xA0000)

- I added new system calls to support the function in sysproc.c

- Created int drawline(int x0, int y0, int x1, int y1, int colour)
which i drew a line between co-ordinates (x0, y0) and (x1, y1) on the display using several colours. 

////////////////////   RESULT OF MY PROJECT.pdf - IS AN IMAGE OF MY END RESULT OF MY PROJECT   /////////////////////////////
