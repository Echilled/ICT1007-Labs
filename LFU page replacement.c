#include <stdio.h>


void print(int frameno,int frame[])
{
            int j;
            for(j=0;j<frameno;j++)
            printf("%d\t",frame[j]);
            printf("\n");
}         


int main()
{
int rs[50],i,j,k,m,f,min,pf=0, avail=0, location=0, repindex;
int a[20]; int cntr[20] = {0};
                        
printf("\n Page replacement Method:Least Frequently Used (LFU)");
printf("\nEnter the number of pages(length of the reference string):");
scanf("%d", &m);          

printf("\n Enter the page numbers (reference string): ");

for(i = 0; i < m; i++){
  scanf("%d", &rs[i]);
}


printf("\nEnter the number of frames");
scanf("%d", &f);



for(i = 0; i < f; i ++){
  cntr[i] = 0;
  a[i] = -1;

}

printf("\n The page replacement Process is \n");
printf("REF STRING");

for(j =0; j<f; j++){
  printf("\tPAGE_FRAME_%d", j+1);
}
  printf("\t PAGE_FAULT_NUMBER\n");
 


for(i = 0; i < m; i++){
  printf("%d\t\t",rs[i]);
  avail = 0;
  
  for(j = 0; j < f; j++){
    if(rs[i] == a[j]){
      avail = 1; //hit
      cntr[j]++;
      break;
    }
  
  }
  if(avail == 0 && pf <f){ 
      a[location] = rs[i];
      cntr[location] =1;
      location=(location + 1)%f;
      pf++;
      print(f,a);
      }

  else if(avail ==0 ){
      repindex = 0;
      min = cntr[0];
       for(j=1; j<f; j++){
          if(cntr[j]<min){
                repindex=j;
              min=cntr[j];
          }
        }
        a[repindex]=rs[i];
        cntr[repindex]=1;
        pf++;
        print(f,a);                      
  }
  
 


}

printf("\n\n Total number of page faults using :LFU %d\n", pf);

            
return 0;


}
