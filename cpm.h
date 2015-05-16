#ifndef CPM_H
#define CMP_H
/* Prevent multiple inclusion */


/* cpm.h
   Various definitions for Workshop E
*/
/* Define */
#define BITMAP_SIZE 12	/* Bit map size in bytes */
#define DIR_NUM 128		/* number of directory */

/* The bitmap */
//extern unsigned char bitmap[23];
extern unsigned char bitmap[BITMAP_SIZE];
/* 360Kb disk with 4Kb blocks -> 11.25 bytes for bitmap
   so round up to 12 */

/* The directory entry */
struct CPMdirent
{
    signed char usercode;
    char filename[9];
    char filetype[4];
    char extent;
    char blockcount;
    char blocks[16];
};
/* Modelled on the description in [1].

   The two unused bytes have been added to the
   end of the two name parameters to allow them
   to be C strings
*/

/* The Directory */
//extern struct CPMdirent directory[32];
extern struct CPMdirent directory[DIR_NUM];

/* Enum type for display the menu */
typedef enum {
	EXIT = 0,
	INIT_DISK,
	LIST_FILE,
	DISPLAY_FREE_BITMAP,
	OPEN_CREATE_FILE,
	READ_FILE,
	WRITE_FILE,
	DELETE_FILE
} menu_type;

int toggle_bit(int block);
/* Toggles the value of the bit block, in
   the external array bitmap.
   returns the current value of the bit
   Does NOT validate block!!!
*/
int block_status(int block);
/* Returns if block block is allocated
   returns 0 if bitmap bit is 0, not
   0 if bitmap bit is 1
   Does NOT validate block!!!
*/
menu_type menu();
/* Display the operation menu of the pcm simulator
*/

void disk_init ();
/* Disk initialise : initialise the content of the Disk.
   return : none
*/
#endif

