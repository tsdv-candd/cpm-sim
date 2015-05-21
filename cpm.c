/* cpm.c
   Useful functions for Workshop E
*/
#include"cpm.h"
unsigned char bitmap[12];
struct CPMdirent directory[64];

int toggle_bit(int block)
{

    int elem=block/8;
    int pos=block%8;
    int mask=1<<pos;

    bitmap[elem]^=mask;

    return bitmap[elem]&mask;
}


int block_status(int block)
{
    int elem=block/8;
    int pos=block%8;
    int mask=1<<pos;

    return bitmap[elem]&mask;
}