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
			delete_file(fd);
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
    //while ( getchar() != '\n' );

    return input;
}

void disk_init ()
{
    memset(bitmap, 0, sizeof(bitmap));
    memset(directory, 0, sizeof(directory));
}

void list_file_in_dir()
{
    int i = 0;
    int is_empty_dir = 1;
    fprintf(stderr, "List of files in directory\n");
    printf("-------------------------------------------------------------------------\n");
    printf("|\tFile name\t|\tFile type \t|\tFile size\t|\n");
    printf("-------------------------------------------------------------------------\n");
    for(i = 0; i < ENTRIES_NUM; i++) {
        /*  Print file information : | file name | file type | fileize |
         *	Size of each block = 4 KB then file_size = (block count) *4 (KB)
         */
        if(strlen(directory[i].filename)) {
            printf("|\t%s\t\t|\t%s\t\t|\t%dKB\t\t|\n", directory[i].filename, directory[i].filetype, (directory[i].blockcount * 4));
            printf("-------------------------------------------------------------------------\n");
            is_empty_dir = 0;
        }
    }
    if(is_empty_dir) {
        printf("Empty directory! There is not any file\n");
    }
}

void disp_bit_map()
{
    fprintf(stderr, "Display bitmap status\n");
}

int open_create_file(char *fname, char *ftype)
{
    int error = -2;
    int create_file = -1;
    int i = 0;
    //fprintf(stderr, "Open/Create File\n");
    if((fname == NULL) || ftype == NULL) {
        fprintf(stderr,"Error! could not open NULL file name or file type\n");
        return error;
    }
    if(strlen(fname) > FILE_NAME_LEN) {
        fprintf(stderr,"Error! not allow file name length > %d\n", FILE_NAME_LEN);
        return error;
    }
    if(strlen(ftype) > FILE_TYPE_LEN) {
        fprintf(stderr,"Error! not allow file type length > %d\n", FILE_TYPE_LEN);
        return error;
    }
    for(i = 0; i < ENTRIES_NUM; i++) {
        /* In case found file name and file type in directory
         * Return position of the file as the file descriptor.
         */
        if(strcmp(directory[i].filename,fname) == 0 && strcmp(directory[i].filetype, ftype) == 0) {
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
		printf("\tThe File: '%s.%s' occupied blocks No: ",directory[fd].filename, directory[fd].filetype);
		for (i=0; i<16; i++)
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
    int numbytes = -1;
    fprintf(stderr, "Start write file\n");
    return numbytes;
}


int delete_file(int fd)
{
    //int numbytes = -1;
    fprintf(stderr, "Start delete file\n");
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