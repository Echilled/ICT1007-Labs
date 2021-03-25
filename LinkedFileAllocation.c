#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define TOTAL_BLOCKS 32
#define NUMBER_OF_INODES 8
#define INODE_ENTRY 1
#define FILE_ENTRY 2
#define SIZE_OF_ENTRY 1

typedef struct FileTableEntry
{
    char fileName[20];
    int startBlock;
    int fileSize;
    int allocatedStatus;
    int allocatedBlock;
    struct FileTableEntry * next;
} fileTableEntry;

void printStart()
{
    printf("File allocation method: SEQUENTIAL\n");
    printf("Total blocks: %d\n", TOTAL_BLOCKS);
    printf("File allocation starts at block: %d\n", NUMBER_OF_INODES);
    printf("File allocation of end at block: %d\n", TOTAL_BLOCKS - 1);
    printf("Size (kB) of each block: %d\n", SIZE_OF_ENTRY);
}

void printFileTable(fileTableEntry *fileTable)
{
    int i = NUMBER_OF_INODES;
    fileTableEntry * current = NULL;
    printf("FILE_NAME\tFILE_SIZE\tBLOCKS_OCCUPIED\n");
    while (i < TOTAL_BLOCKS)
    {
        if (fileTable[i].allocatedStatus == FILE_ENTRY && fileTable[i].startBlock == i)
        {
            //print whole linked list
            current = &fileTable[i];
            printf("%s\t%2d\t\t", current->fileName, current->fileSize);
            while (current)
            {
                if (current->next)
                    printf("%d-", current->allocatedBlock);
                else    
                    printf("%d\n", current->allocatedBlock);
                
                current = current->next;
            }   
        }
        
        i++;
        
    }
}
bool checkIfAllocated(fileTableEntry *fileTable, int fileTableIndex)
{
    if (fileTableIndex > 32)
        return false;
    else if (fileTable[fileTableIndex].allocatedStatus == FILE_ENTRY)
    {
        printf("Filetable[%d].allocatedStatus = %d\n", fileTableIndex, fileTable[fileTableIndex].allocatedStatus);
        return false;
    }
    return true;
}

int main()
{
    int numberOfFilesToAllocate = 0, startingBlock = 0;
    //init file table
    srand(time(NULL)); // set srand
    fileTableEntry fileTable[TOTAL_BLOCKS];
    memset(&fileTable, 0, sizeof(fileTableEntry) * TOTAL_BLOCKS);

    for (int i = 0; i < 8; i++)
    {
        fileTable[i].allocatedStatus = INODE_ENTRY; //set these to INODE_ENTRY as the first 8 blocks are used for inodes
    }
    printStart();

    printf("Enter no. of files to allocate: ");
    scanf("%d", &numberOfFilesToAllocate);

    for (int i = 0; i < numberOfFilesToAllocate; i++)
    {
        int currentFileNumber = i + 1, sizeOfFile = 0, currentBlock = 0, prevBlock = 0;
        char fileName[20];
        printf("Enter the name of file #%d: ", currentFileNumber);
        scanf("%s", fileName);
        printf("Enter the size (kB) of file #%d: ", currentFileNumber);
        scanf("%d", &sizeOfFile);
        fileTableEntry * newEntryHead = NULL;
        startingBlock = (rand() % (TOTAL_BLOCKS - NUMBER_OF_INODES)) + (NUMBER_OF_INODES - 1);
        currentBlock = startingBlock;
        printf("Debug starting block generated: %d\n", startingBlock);
        for (int j = 0; j < sizeOfFile; j++)
        {
            if (checkIfAllocated(fileTable, currentBlock))
            {
            //allocate
                if (currentBlock == startingBlock) // first entry in new linked list
                {
                    fileTable[currentBlock].allocatedStatus = FILE_ENTRY;
                    memcpy(fileTable[currentBlock].fileName, fileName, sizeof(char) * 20);
                    fileTable[currentBlock].fileSize = sizeOfFile;
                    fileTable[currentBlock].startBlock = startingBlock;
                    fileTable[currentBlock].allocatedBlock = currentBlock;
                
                    
                }
                else if (j == sizeOfFile - 1)
                {
                    fileTable[currentBlock].allocatedStatus = FILE_ENTRY;
                    memcpy(fileTable[currentBlock].fileName, fileName, sizeof(char) * 20);
                    fileTable[currentBlock].fileSize = sizeOfFile;
                    fileTable[currentBlock].startBlock = startingBlock;
                    fileTable[prevBlock].next = &fileTable[currentBlock];
                    fileTable[currentBlock].allocatedBlock = currentBlock;
                    fileTable[currentBlock].next = NULL;
                    
                }
                else
                {
                    fileTable[currentBlock].allocatedStatus = FILE_ENTRY;
                    memcpy(fileTable[currentBlock].fileName, fileName, sizeof(char) * 20);
                    fileTable[currentBlock].fileSize = sizeOfFile;
                    fileTable[currentBlock].startBlock = startingBlock;
                    fileTable[currentBlock].allocatedBlock = currentBlock;
                    fileTable[prevBlock].next = &fileTable[currentBlock];
                    
                }
                prevBlock = currentBlock;
                currentBlock = (rand() % (TOTAL_BLOCKS - NUMBER_OF_INODES)) + (NUMBER_OF_INODES - 1);
                printf("debug: end of code currentBlock value: %d\n", currentBlock);
            }
            else
            {
                printf("Unable to allocate file, not enough memory.\nSkipping. %s\n", fileName);

                break;
            }
        }

        
    }

    printFileTable(fileTable);
    
}
