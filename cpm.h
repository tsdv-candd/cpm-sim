#ifndef CPM_H
#define CMP_H
/* Prevent multiple inclusion */


/* cpm.h
   Various definitions for Workshop E
*/
/* Define */
#define BITMAP_LENGHT 	12		/* Bit map size in bytes */
#define ENTRIES_NUM 	128		/* Number of directory */
#define FILE_NAME_LEN 	8		/* Lenght of the file name */
#define FILE_TYPE_LEN 	3		/* Lenght of the file name */
#define BLOCKS_PER_FILE 16		/* Number of block in each file */
#define DISK_CAPACITY	360		/* Capacity of the disk in KB */
#define BLOCK_SIE		4 		/* Size of each block in KB */
#define NUMBER_OF_BLOCK (DISK_CAPACITY/BLOCK_SIE)
/* The bitmap */
extern unsigned char bitmap[BITMAP_LENGHT];
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
extern struct CPMdirent directory[ENTRIES_NUM];

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

void list_file_in_dir();
/* List all file in the directory.
*/

void disp_bit_map();
/* Display bit map status
*/

int open_create_file(char *fname, char *ftype);
/* Open/Create file
*/

int read_file(int fd);
/* Read file by the file descriptor
*/

int write_file(int fd);
/* Write file by the file descriptor
*/

int delete_file(int *fd);
/* Delete file by the file descriptor
*/

int get_name_and_type( char fname[9], char ftype[4]);
/* Get file name and file type from input keyboard.
*/

void clear_stdin();
/* Clear standard input buffer
*/
#endif

