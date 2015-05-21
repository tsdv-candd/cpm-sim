#ifndef CPM_H
#define CMP_H
/* Prevent multiple inclusion */


/* cpm.h
   Various definitions for Workshop E
*/

/* The bitmap */
extern unsigned char bitmap[12];
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
extern struct CPMdirent directory[128];

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
#endif

