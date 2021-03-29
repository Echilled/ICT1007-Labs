#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TOTAL_DISK_BLOCKS 32
#define TOTAL_DISK_INODES 8

struct file_table { 
    char fileName[20];
    int fileSize;
    struct block *sb;
};

typedef struct block {
    int blockNumber;
    struct block *next;
} Block;

Block * AllocateBlocks(int Size);
Block * enqueue(Block * head, int val);
void printList(Block * head);

int blockStatus[TOTAL_DISK_BLOCKS]; // free = 0
int blockList[TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES]; // list of blocks of a file
struct file_table fileTable[TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES];

int main() {
    srand(time(NULL));
    int i = 0, j = 0, numFiles = 0, nextBlock= 0;
    Block *ret;
    char s[20]; struct block *temp;
    
    printf("Enter no of files: ");
    scanf("%d", &numFiles);
    for(i = 0; i < numFiles; i++) {
        char file_name[20];
        printf("\nEnter the name of the file #%d: ", i+1);
        scanf("%s", file_name);
        sprintf(fileTable[i].fileName, "%s", file_name);

        printf("Enter the size (kB) of file #%d: ", i+1);
        scanf("%d", &fileTable[i].fileSize);

        ret = AllocateBlocks(fileTable[i].fileSize);

        if(ret != NULL){
            fileTable[i].sb = ret;
        } else {
            printf("Error trying to allocation file. Exiting.\n");
            exit(0);
        }
    }

    printf("\n%-20s%-20s%-20s\n", "FILE_fileName", "FILE_SIZE", "BLOCKS_OCCUPIED");
    for(i = 0; i < numFiles; i++) {
        printf("%-20s%-20d", fileTable[i].fileName, fileTable[i].fileSize);
        printList(fileTable[i].sb);
        printf("\n");
    }

    printf("File allocation completed. Exiting.\n");
} 


Block * AllocateBlocks(int Size) {
    int i = 0, count = 0, inList = 0, nextBlock = 0;
    int allocStartBlock = TOTAL_DISK_INODES;
    int allocEndBlock = TOTAL_DISK_BLOCKS - 1;

    // check whether sufficient free blocks are available
    for (i = allocStartBlock; i < allocEndBlock+1; i++) 
        if (blockStatus[i] == 0)
            count++;
    if (count < Size)
        return NULL; // not enough free blocks

    count = 0;
    Block * head = NULL;
    while(count < Size){
        nextBlock = (rand() % (allocEndBlock - allocStartBlock + 1)) + allocStartBlock;
        if(blockStatus[nextBlock] == 0){
            head = enqueue(head, nextBlock);
            blockStatus[nextBlock] = 1;
            count += 1;
        } 
    }

    if (count == Size)
        return head; // success
    else
        return NULL; // not successful
}


Block * enqueue(Block * head, int val) {
    if(head == NULL){
        Block *ptr = (Block *) malloc(sizeof(Block));
        ptr->blockNumber = val;
        ptr->next = NULL;
        head = ptr;
    } else {
        Block * current = head;
        while (current->next != NULL) {
            current = current->next;
        }

        /* now we can add a new variable */
        current->next = (Block *) malloc(sizeof(Block));
        current->next->blockNumber = val;
        current->next->next = NULL;
    }
    return head;
}


void printList(Block * head) {
    Block *ptr = head;

    //start from the beginning
    while(ptr != NULL) {
        printf("%d", ptr->blockNumber);
        if(ptr->next != NULL){
            printf("-");
        }
        ptr = ptr->next;
    }
}
