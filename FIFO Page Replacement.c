#include <stdio.h>

int main(void) {
  int i,j,k,f,pf =0, count=0,n;
  int rs[25], m[10];


  printf("\n Page Replacement Method: FIFO");
  printf("\n Enter the number of pages (length of the reference string): ");


  scanf("%d", &n);
  printf("\n Enter the page numbers (reference string):");

  for(i = 0;i < n; i++){
    scanf("%d", &rs[i]);
  
  printf("\n Enter the number of frames");

  scanf("%d", &f);

  for(i = 0; i < f; i++){
    m[i] = -1;

printf("\n The Page Replacement Process is\n");
printf("\t REF STRING");

  }
printf("\nThenumberofPageFaultsusingFIFO:%d\n",pf);

  }




}
