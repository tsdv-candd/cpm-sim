/* cpm.c
   Useful functions for Workshop E
*/
#include <stdio.h>	/* For using printf function */
#include <string.h> /* For using memset function */
#include"cpm.h"

unsigned char bitmap[BITMAP_LENGHT];
struct CPMdirent directory[ENTRIES_NUM];

#define EMPTY_STR "";

int main ()
{
    int select = -1;
    int fd = -1;
    printf("Hello cpmsim!\n");
    do {
        select = menu();
        switch(select)
        {
        case INIT_DISK:
            disk_init();
            break;
        case LIST_FILE:
            list_file_in_dir();
            break;
        case DISPLAY_FREE_BITMAP:
            disp_bit_map();
            break;
        case OPEN_CREATE_FILE:
        {
            char fname[9];
            char ftype[4];
            get_name_and_type(fname, ftype);
            fd = open_create_file(fname, ftype);
            if(fd >= 0) {
                printf("File '%s.%s' is opened\n", directory[fd].filename, directory[fd].filetype);
            } else if (fd == -1) {
                printf("File '%s.%s' is created\n",fname, ftype);
            } else {
                printf("Error! Open/Create file\n");
            }
        }
        break;
        case READ_FILE:
            read_file(fd);
            break;
        case WRITE_FILE:
            write_file(fd);
            break;
        case DELETE_FILE:
            delete_file(&fd);
            break;
        case EXIT:
        default:
            break;
        }
    } while (select != EXIT);
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

menu_type menu()
{
    int input = -1;

    /* Display the help menu
    */
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

    /* Read the input from keyboard.
    */
    scanf("%d", &input);

    /*
     * Clear stdin after read input
     */
    clear_stdin();

    /* Return the value appropriate to the selected key Num.
     */
    return input;
}

void disk_init ()
{
    /* Reset bitmap.
    */
    memset(bitmap, 0, sizeof(bitmap));

    /* Reset directory.
    */
    memset(directory, 0, sizeof(directory));
}

void list_file_in_dir()
{
    int i = 0;
    int is_empty_dir = 1;
    printf("List of files in directory:\n");
    printf("+-----------------------------------------------------------------------+\n");
    printf("|\tFile name\t|\tFile type \t|\tFile size\t|\n");
    printf("+-----------------------------------------------------------------------+\n");

    /* List all file in the directory if it existed.
     */
    for(i = 0; i < ENTRIES_NUM; i++) {
        /*  Print file information : | file name | file type | fileize |
         *	Size of each block = 4 KB then file_size = (block count) *4 (KB)
         */
        if(strlen(directory[i].filename)) {
            printf("|\t%s\t\t|\t%s\t\t|\t%dKB\t\t|\n", directory[i].filename, directory[i].filetype, (directory[i].blockcount * 4));
            printf("+-----------------------------------------------------------------------+\n");
            is_empty_dir = 0;
        }
    }
    /* In case the dirrectory is empty, just notify it's empty directory!
     */
    if(is_empty_dir) {
        printf("Empty directory!\n");
    }
}

void disp_bit_map()
{
    int i=0;
    int j = 0;
    int block_post = 0;
    printf("Bitmap status: 0 - free block, 1 - occupied block\n");

    /* Draw column index (equivalence to 8 bits of each element of bitmap array)
    */
    printf("\t");
    for(j = 0; j < 8; j++) {
        printf("  %d ", j);
    }
    printf("\n\t+---+---+---+---+---+---+---+---+\n");
    for (i = 0; i < BITMAP_LENGHT; i++) {
        /* Draw row index 0 - 11 (equivalence to 12 element of bitmap array)
        */
        printf("%d\t",i);

        /* Display status of each block:
         * 0 - the appropriate block are free.
         * 1 - the appropriate block are occupied by a file.
         */
        for(j = 0; j < 8; j++) {
            /* Calculate block position.
             */
            block_post = 8*i + j;
            if(block_status(block_post)) {
                /* occupied block
                 */
                printf("| 1 ");
            } else {
                /* free block.
                 */
                printf("| 0 ");
            }
        }
        printf("|\n");
        printf("\t+---+---+---+---+---+---+---+---+\n");
    }
}

int open_create_file(char *fname, char *ftype)
{
    int error = -2;
    int create_file = -1;
    int i = 0;

    /* Not allow Null file name or file type.
     */
    if((fname == NULL) || ftype == NULL) {
        fprintf(stderr,"Error! could not open NULL file name or file type\n");
        return error;
    }

    /* Not allowed the file name > 8
     */
    if(strlen(fname) > FILE_NAME_LEN) {
        fprintf(stderr,"Error! not allow file name length > %d\n", FILE_NAME_LEN);
        return error;
    }

    /* Not allowed the file type > 3
     */
    if(strlen(ftype) > FILE_TYPE_LEN) {
        fprintf(stderr,"Error! not allow file type length > %d\n", FILE_TYPE_LEN);
        return error;
    }
    for(i = 0; i < ENTRIES_NUM; i++) {
        /* In case found file name and file type in directory
         * Return position of the file as the file descriptor.
         */
        if((strcmp(directory[i].filename,fname) == 0)
                && (strcmp(directory[i].filetype, ftype) == 0)) {
            printf("\tOpen file '%s.%s' at position [%d]\n", directory[i].filename, directory[i].filetype,i);
            return i;
        }
    }
    for(i = 0; i < ENTRIES_NUM; i++) {
        /* Create the file with the file name and file type
         * And append that file at the end of directory entries.
         */
        if(strlen(directory[i].filename) == 0) {
            directory[i].usercode = 1;
            strncpy(directory[i].filename, fname, strlen(fname) + 1);
            strncpy(directory[i].filetype, ftype, strlen(ftype) + 1);
            return create_file;
        }
    }
    return error;
}


int read_file(int fd)
{
    int i = 0;
    fprintf(stderr, "Start read file\n");
    if(fd > -1) {
        printf("\tThe File: '%s.%s' occupied blocks No: ", directory[fd].filename, directory[fd].filetype);
        for (i=0; i<BLOCKS_PER_FILE; i++)
        {
            printf("%d, ", directory[fd].blocks [i]);
        }
        printf("\n");
    } else {
        printf("\tThe file not opened, need open for reading\n");
    }
    return 0;
}

int write_file(int fd)
{
    int write_flag = 0;
    char i = 0;
    if(fd < 0) {
        fprintf(stderr, "ERROR: the file has not open yet, please open before write.\n");
        return -1;
    }
    /* The maximum size of a ﬁle is 64 kbytes, block's size = 4KB
     * So maximum number of block per file is 16
     */
    if(directory[fd].blockcount == BLOCKS_PER_FILE) {
        fprintf(stderr, "ERROR: File size reach the limit of 64KB, could not write more data\n");
        return -1;
    }

    /* Write data if the block have not occupied by any file.
     *
     */
    for (i=1; i<NUMBER_OF_BLOCK; i++) {
        if(block_status(i) == 0) {
            int updateblock_count = -1;
            updateblock_count = directory[fd].blockcount++;
            directory[fd].blocks[updateblock_count] = i;
            toggle_bit(i);
            write_flag = 1;
            printf("Info: Write block [%d]\n", i);
            break;
        }
    }

    /* In case disk full, the write_flag will
     * not change the value.
     */
    if(write_flag == 0) {
        fprintf(stderr, "ERROR: Disk full, could not write more data\n");
        return -1;
    }
    return 0;
}


int delete_file(int *fd)
{
    int i = 0;
    if(*fd > ENTRIES_NUM) {
        printf("Error! file descriptor is out of range, [%d]\n",ENTRIES_NUM);
        return -1;
    }
    if(*fd < 0) {
        printf("Could not delete because no file open, please open it before delete\n");
        return -1;
    }

    /* Free bitmap
     */
    for(i=0; i<directory[*fd].blockcount+1; i++)
    {
        toggle_bit(directory[*fd].blocks[i]);
    }

    /* Reset file name, file type, blocks array and block count of the appropriate entry.
     */
    memset(directory[*fd].filename, 0, (FILE_NAME_LEN + 1));
    memset(directory[*fd].filetype, 0, (FILE_TYPE_LEN + 1));
    memset(directory[*fd].blocks, 0, BLOCKS_PER_FILE);
    directory[*fd].blockcount = 0;
    *fd = -1;
    return 0;

}

int get_name_and_type( char fname[9], char ftype[4])
{
    printf("\tEnter file name> ");
    scanf("%s", fname);
    clear_stdin();
    printf("\tEnter file type> ");
    scanf("%s", ftype);
    clear_stdin();
    return 0;
}

void clear_stdin()
{
    /*
     * Clear stdin after read input
     */
    while ( getchar() != '\n' );
}