/* cpm.c
   Useful functions for Workshop E
*/
#include <stdio.h>	/* For using printf function */
#include <string.h> /* For using memset function */
#include"cpm.h"

unsigned char bitmap[BITMAP_SIZE];
struct CPMdirent directory[DIR_NUM];

int main ()
{
	int select = -1;
	printf("Hello cpmsim!\n");
	select = menu();
	fprintf(stderr, "Select #%d\n", select);
	switch(select) {
		case INIT_DISK:
		break;
		case LIST_FILE:
		break;
		case DISPLAY_FREE_BITMAP:
		break;
		case OPEN_CREATE_FILE:
		break;
		case READ_FILE:
		break;
		case WRITE_FILE:
		break;
		case DELETE_FILE:
		break;
		default:
		break;		
	}
	return 0;
}

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

/*
 * Display main menu of the program
 */
 menu_type menu()
 {
	int input = -1;
	do {
		printf("\n\n----------------------------------\n");
		printf("\tCP/M simulation Menu\n");
		printf("----------------------------------\n");
		printf("0 - Exit\n");
		printf("1 - Initialise Disk\n");
		printf("2 - List Files in the Directory\n");
		printf("3 - Display the Free Bitmap\n");
		printf("4 - Open/Create File\n");
		printf("5 - Read File\n");
		printf("6 - Write File\n");
		printf("7 - Delete File\n");
		printf("----------------------------------\n");
		printf("Select number> ");
		scanf("%d", &input);
		
		/*
		 * Clear stdin after read input 
		 */
		while ( getchar() != '\n' );
	} while ((input < 0) || (input > 7));
	return input;
 }

 /* Initialise Disk
 */
 void disk_init ()
 {
	 memset(bitmap, 0, sizeof(bitmap));
	 memset(directory, 0, sizeof(directory));
 }