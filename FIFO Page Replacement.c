#include <stdio.h>

int main()
{
int i,j,n,a[50],frame[10],no,k,avail,count=0, page_fault = 0;
            printf("\n ENTER THE NUMBER OF PAGES (legnth of the ref string):\n");
scanf("%d",&n);
            printf("\n ENTER THE PAGE NUMBERS:\n");
            for(i=1;i<=n;i++)
            scanf("%d",&a[i]);
            printf("\n ENTER THE NUMBER OF FRAMES :");
            scanf("%d",&no);
            printf("The Page replacement process is\n");
for(i=0;i<no;i++)
            frame[i]= -1;
                        j=0;
                        printf("Referece string\t\t");
                for(int m = 0; m < no; m++){
                  
                        printf("page frame_%d\t",m+1);
                  
                        }
                        printf("Page fault number");
for(i=1;i<=n;i++)
                        { 
                                    printf("\n\t\t\t%d\t\t\t\t",a[i]);
                                    avail=0;
                                    for(k=0;k<no;k++)
                      if(frame[k]==a[i]){ 
                                  avail=1;
                      
                                        }
                                           
                                    if (avail==0)
                                    {
                                                frame[j]=a[i];
                                                j=(j+1)%no;
                                                count++;
                                                for(k=0;k<no;k++)
                                                printf("%d\t\t\t",frame[k]);
}


                                    printf("\n");
}
    printf("Page Fault Is %d",count);
                        return 0;
}
