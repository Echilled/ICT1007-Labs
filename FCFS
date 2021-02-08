#include <stdio.h>

int main(void) {
  int i, j, n, bu[10], wa[10], tat[10], timeSlice, ct[10], max_process_time, temp = 0, burst_times[10], waiting_time = 0;
  float awt = 0.0, att=0.0;
  int loop;


printf("Enter the no of processes:");
scanf("%d", &n);
for(i = 0; i < n; i++){
  printf("\nEnter Burst Time for process %d: ",i + 1);
  scanf("%d", &bu[i]); //Storing burst times into the burst time array
}

wa[0] = 0; //First process wil always have zero waiting time


//Get waiting times
printf("Waiting times:\n");
for(loop = 0; loop < n; loop++) {
    wa[loop] = bu[loop-1] + wa[loop-1];
    awt += wa[loop];
    printf("Process %d:",loop+1);
    printf("%d\n", wa[loop]);
   }
printf("Average Waiting time:\n");
printf("%f", awt/n);

//Get turnaround time
printf("\n\nTurnaround times:\n");
for(i=0; i<n; i++)
{
    tat[i] = wa[i] + bu[i];
    att += tat[i];
    printf("Process %d:",i+1);
    printf("%d\n", tat[i]);
   }
printf("Average Turnaround time:\n");
printf("%f", att/n);


  return 0;
}
