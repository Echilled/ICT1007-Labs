#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_DISK_BLOCKS 32
#define TOTAL_DISK_INODES 8
int blockStatus[TOTAL_DISK_BLOCKS]; // free = 0
int blockList[TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES]; //list of blocks of a file

struct file_table {  
    char fileName[20];  
    int fileSize; 
    int blocks[TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES];
}; 
    
struct file_table fileTable[TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES];

int AllocateBlocks(struct file_table* newFile) {
	int count = 0;
	int startBlk = TOTAL_DISK_INODES;
	int endBlk = TOTAL_DISK_BLOCKS - 1;
	int Size = newFile->fileSize;

	//Calculate total number of available blocks
	for (int i = startBlk; i < TOTAL_DISK_BLOCKS; i++) {
		if (blockStatus[i] == 0){
			count++;
		}
	}

	//Not enough free blocks
	if (count < Size) {
		return 1;
	}

	count = 0;

	while (count < Size) {
		int genBlk = (rand() % (endBlk - startBlk + 1) + startBlk);
		if (blockStatus[genBlk] == 0) {
			newFile->blocks[count] = genBlk;
			blockStatus[genBlk] = 1;
			count++;
		}
	}

	return 0;
}

int getNumElem(int blockArr[], int size) {
	int count = 0;
	for (int i = 0; i < size; i++){
		if (blockArr[i] != 0) {
			count++;
		}
	}
	return count;
}

int main()  {  
    int i =0, j = 0, numFiles = 0, nextBlock = 0, ret = 1;
	int fileSize = 0;
    char s[20];
	struct block *temp;

	printf("Enter Number of files: ");
	scanf("%d", &numFiles);

    for(i = 0; i < numFiles; i++) {
		printf("Enter the name of file #%d: ", i+1);
		scanf("%s", fileTable[i].fileName);
		
		printf("Enter the size (kB) of file #%d: ", i+1);
		scanf("%d", &fileSize);
		fileTable[i].fileSize = fileSize;
        ret = AllocateBlocks(&fileTable[i]);
		
    }

	printf("FILE_fileName\tFILE_SIZE\tBLOCKS_OCCUPIED\n");

	for (int z = 0; z < numFiles; z++) {
		char blockStr[100];
		char blkNum[5];
		int inxLen = sizeof(fileTable[z].blocks)/sizeof(fileTable[z].blocks[0]);
		int elLen = getNumElem(fileTable[z].blocks, inxLen);
		int *inxBlk = fileTable[z].blocks;
		if (elLen == 0) {
			snprintf(blockStr, 100, "Not enough space");
		}
		for (int x = 0; x < elLen; x++) {
			if (x == 0) {
				snprintf(blockStr, 100, "%d-", inxBlk[x]);
			} else {
				snprintf(blkNum, 5, "%d", inxBlk[x]);
				if (x != elLen - 1) {
					strcat(blkNum, "-");
				}
				strcat(blockStr, blkNum);
			}
		}
		printf("%-13s\t%-9d\t%s\n", fileTable[z].fileName, fileTable[z].fileSize, blockStr);
	}

	return 0;
}

