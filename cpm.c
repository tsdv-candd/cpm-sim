/* cpm.c
   Useful functions for Workshop E
*/
#include <stdio.h>
#include"cpm.h"

unsigned char bitmap[12];
struct CPMdirent directory[128];

/* Function declaration
 */
int toggle_bit(int block);
int block_status(int block);
int menu();

int main ()
{
    int select = -1;
    printf("Hello cpmsim!\n");
    select = menu();
    fprintf(stderr, "Select #%d\n", select);
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
int menu()
{
    int input = -1;
    do {
        printf("\n----------------------------------\n");
        printf("\t\tMenu\n");
        printf("----------------------------------\n");
        printf("0.Exit\n");
        printf("1.Initialise Disk\n");
        printf("2.List Files in the Directory\n");
        printf("3.Display the Free Bitmap\n");
        printf("4.Open/Create File\n");
        printf("5.Read File\n");
        printf("6.Write File\n");
        printf("7.Delete File\n");
        printf("----------------------------------\n");
        printf("Select number> ");
        scanf("%d", &input);
        while ( getchar() != '\n' );
    } while ((input < 0) || (input > 7));
    return input;
}
