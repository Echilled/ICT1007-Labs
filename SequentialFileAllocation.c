#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_DISK_BLOCKS 32
#define TOTAL_DISK_INODES 8
int blockStatus[TOTAL_DISK_BLOCKS]; // free = 0 
int blockStart; 

struct file_table {  
    char fileName[20];  
    int startBlock; 
    int fileSize; 
    int allotStatus; 
}; 
    
struct file_table fileTable[TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES]; 
int AllocateBlocks(int Size) { 
    int i = 0, count = 0, inList = 0, nextBlock = 0;
    int allocStartBlock = TOTAL_DISK_INODES;
    int allocEndBlock = TOTAL_DISK_BLOCKS - 1; 
    // check whether sufficient free blocks are available
    for (i = 0; i < (TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES); i++) 
        if (blockStatus[i] == 0)
            count++; 
        if (count < Size)
            return 1;  // not enough free blocks
        count = 0; 
        while (count < Size) {
            nextBlock = (rand() % (allocEndBlock - allocStartBlock + 1)) + allocStartBlock; 
            for (i = nextBlock; i < (nextBlock + Size); i++)
            {
                if (blockStatus[i] == 0)
                    count = count + 1;
                else {
                    count = 0; 
                    break;
                }         
            }    
        }
        blockStart = nextBlock;
        if (count == Size)
            return 0; // success
        else
            return 1; // not successful
}

int main()  {  
    int i =0, j = 0, numFiles = 0, nextBlock = 0, ret = 1;
	int fileSize = 0;
    char s[20];

	printf("Enter Number of files: ");
	scanf("%d", &numFiles);

    for(i = 0; i < numFiles; i++) {
		printf("Enter the name of file #%d: ", i+1);
		scanf("%s", fileTable[i].fileName);
		printf("%s\n", fileTable[i].fileName);
		printf("Enter the size (kB) of file #%d: ", i+1);
		scanf("%d", &fileSize);
		fileTable[i].fileSize = fileSize;
        ret = AllocateBlocks(fileTable[i].fileSize);
		if (ret == 0) {
			fileTable[i].startBlock = blockStart;
			nextBlock = blockStart;
			for (int u = 0; u < fileTable[i].fileSize; u++){
				printf("Next Block 1 %d\n", nextBlock);
				blockStatus[nextBlock++] = 1;
			}
			fileTable[i].allotStatus = 1;
		}
    }

	for (int f = 0; f < TOTAL_DISK_BLOCKS; f++){
		printf("Block %d %d\n", f, blockStatus[f]);
	}

	printf("FILE_fileName\tFILE_SIZE\tBLOCKS_OCCUPIED\n");

	for (int z = 0; z < numFiles; z++) {
    printf("\t%s\t\t", fileTable[z].fileName);
    printf("\t%d\t\t", fileTable[z].fileSize);
    printf("\t%d", fileTable[z].startBlock);
		int startBlk = fileTable[i].startBlock;
		for (int y = 1; y < fileTable[z].fileSize; y++){
        printf("-%d", fileTable[z].startBlock + y);
    }
    printf("\n");

	}

	return 0;
}
