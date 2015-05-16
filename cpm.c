/* cpm.c
   Useful functions for Workshop E 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include "cpm.h"
unsigned char bitmap[23];
struct CPMdirent directory[32];

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

void displayelem(int elem)
{
    int i=0;
    for (i=0; i<8; i++)
    {
        if(block_status((elem*8)+i) ==0)
        {
            printf("%d  ",0);
        }
        else
        {
            printf("%d  ",1);
        }
    }
}

void display()
{
    int i=0;
    for (i=0; i<23; i++)
    {
        if((i%2) == 0) {
            if((i/2)==10)
            {
                printf("A  ");
            }
            else if((i/2)==11)
            {
                printf("B  ");
            }
            else
            {
                printf("%d  ",i/2);
            }
            displayelem(i);
        }
        if((i%2) != 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}

void initialise()
{
    memset(&bitmap[0], 0, sizeof(bitmap));
    memset(&directory[0], (int *)NULL, sizeof(directory));
    display();
}

void listFile()
{
    int i;
    int check=0;

    printf("File Name\t\tFile Type\t\tFile Size\n");

    for (i=0; i<32; i++)
    {
        if(strcmp(directory[i].filename,"")!=0)
        {
            printf("%s\t\t\t%s\t\t\t%dKB\n",directory[i].filename,directory[i].filetype,  directory[i].blockcount);
            check=1;
        }
    }
    if (check=0)
    {
        printf("Don't have any file this in directory\n");
    }

}

int openFile(char name[9],char type[9])
{

    int i=0;
    for (i=0; i<32; i++)
    {
        if (strcmp(directory[i].filename, name)==0 && strcmp(directory[i].filetype, type)==0)//true>
        {
            return i;
        }
    }

    for (i=0; i<32; i++)
    {
        if(strcmp(directory[i].filename,"")==0)
        {
            directory[i].usercode =1;
            strcat(directory[i].filename,name);
            strcat(directory[i].filetype, type);
            return -1;
        }
    }

}

//Menu of the System
int main()
{

    int command=8;
    int i;
    int writeBit=-1;
    int filePos=-1;
    char filename[9];
    char filetype[9];

    while(command != 0)
    {

        printf("1.Initialise Disk\n");
        printf("2.List Files in the Directory\n");
        printf("3.Display Bitmap\n");
        printf("4.Open/ Create file\n");
        printf("5.Read File\n");
        printf("6.Write File\n");
        printf("7.Delete File\n");
        printf("\n");
        printf("0.Exit\n");

        if (filePos!=-1)
        {
            printf("Currently file %s.%s opened\n\n", directory[filePos].filename,directory[filePos].filetype  );
        }

        else
        {
            printf("No file open\n\n");
        }

        printf("Select the number:");
        scanf("%d",&command);
        switch (command)
        {
			case 1:
				initialise();
				filePos=-1;
				continue;
				break;
			case 2:
				listFile();
				continue;
			case 3:
				display();
				continue;
			case 4:
			{
				printf(" enter your file name: ");
				scanf("%s",filename);
				printf(" enter file extention: ");
				scanf("%s",filetype);
				filePos = openFile(filename,filetype);
				if(filePos==-1)
				{
					printf("File %s.%s created\n",filename, filetype);
					continue;
				}
				else
				{
					printf("Opened file %s.%s\n", directory[filePos].filename , directory[filePos].filetype );
					continue;
				}
			}
			case 5:
				if(filePos>-1)
				{
					printf("File name: %s.%s on bit: ",directory[filePos].filename, directory[filePos].filetype);
					for (i=0; i<16; i++)
					{
						printf("%d ,",directory[filePos].blocks [i]);
					}
					printf("\n");
					continue;
				} else {
					printf(" need to open the file first\n");
					continue;
				}
			case 6:
			{
				if(filePos!=-1)
				{
					for (i=1; i<184; i++) {
						if(block_status(i)==0) {
							toggle_bit(i);
							writeBit=i;
							break;
						}
					}
					directory[filePos].blocks[directory[filePos].blockcount]=writeBit;
					directory[filePos].blockcount ++;
				} else {
					printf(" need to open the file first\n\n");
				}
				continue;
				break;
			}
			case 7:
				if(filePos!=-1)
				{
					for(i=0; i<directory[filePos].blockcount+1; i++)
					{
						toggle_bit(directory[filePos].blocks[i]);
						continue;
					}
					memset(&directory[filePos].blocks,NULL, sizeof(char)*16);
					memset(&directory[filePos].filename,NULL, sizeof(char)*9);
					memset(&directory[filePos].filetype,NULL, sizeof(char)*9);
					directory[filePos].blockcount =0;
					filePos=-1;
				} else {
					printf("No file open");

				}
				continue;
			case 0:
			{
				filePos=-1;
			}
			default:
				break;
        }
    }
    return 0;
}
