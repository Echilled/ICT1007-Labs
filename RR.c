#include <stdio.h>



int main(void) {
  //Declaring vairables
  int i, j, n, bu[10], wa[10], tat[10], timeSlice, ct[10], max_process_time, temp = 0, burst_times[10];
  float awt = 0.0, att=0.0;
  int loop;


printf("Enter the no of processes:");
scanf("%d", &n);
for(i = 0; i < n; i++){
  printf("\nEnter Burst Time for process %d: ",i + 1);
  scanf("%d", &bu[i]); //Storing burst times into the burst time array
}

//Duplcating another array
for(i=0; i<10; i++)
{
    burst_times[i] = bu[i];
}


printf("\nEnter the size of time slice:");
scanf("%d",&timeSlice);
max_process_time=bu[0];

for(i=1;i<n;i++) //Finding the biggest process time among the processes
  {
    if(max_process_time<bu[i])
      max_process_time=bu[i];
  }
  for(j = 0; j<(max_process_time/timeSlice) + 1; j++){
    for(i=0; i < n; i++){
      if(bu[i]!=0){
        if(bu[i] <= timeSlice){ //Arranging the process gant chart
          tat[i] = temp + bu[i];
          temp = temp + bu[i]; //Waiting time
          bu[i] = 0;  //Resetting
        }
        else{
          bu[i] = bu[i] - timeSlice;
          temp = temp + timeSlice;
        }
      }
    }
  }
//Get waiting time for each process
printf("Waiting times:\n");
for(loop = 0; loop < n; loop++) {
    wa[loop] = tat[loop] - burst_times[loop];
    awt += wa[loop];
    printf("Process %d:",loop+1);
    printf("%d\n", wa[loop]);
   }
printf("Average Waiting time:\n");
printf("%f", awt/n);


//Get turnaround time for each process
printf("\n\nTurnaround times:\n");
for(loop = 0; loop < n; loop++) {
    ct[loop] = wa[loop] + burst_times[loop];
    att += ct[loop];
    printf("Process %d:",loop+1);
    printf("%d\n", ct[loop]);
   }
printf("Average Turnaround Time:\n");
printf("%f", att/n);

}
