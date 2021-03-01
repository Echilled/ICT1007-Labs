#include<stdio.h>
#include<stdlib.h>

int main()
{
    int rs[20]; // = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int i, j, k, m, f, next, pf = 0;
    int resource, min_arr_index = 0, arr_index[3], min_count = 0;
    int cntr[3], a[3];

    system("clear");

    printf("\n Page Replacement Method: Least Frequently Used (LFU)"); 
    printf("\n Enter the number of pages (length of the reference string): "); 
    scanf("%d", &m);
    //m = 20;

    printf("\n Enter the page numbers (reference string): "); 
    // 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1    
    for (i = 0; i < m; i++)
        scanf("%d", &rs[i]);

    printf("\nEnter the number of frames: "); 
    scanf("%d", &f);    //3
    //f = 3;

    for (i = 0; i < f; i++){
        cntr[i] = -1;
        a[i] = -1;
        arr_index[i] = -1;
    }

    printf("\n The Page Replacement Process is\n");
    printf("\tREF STRING");
    for (j = 0; j < f; j++)
        printf("\tPAGE_FRAME%d", j + 1);
    printf("\tPAGE_FAULT_NUMBER\n");

    for (i = 0; i < m; i++){
        resource = rs[i];
        for (j = 0; j < f; j++) {
            if (rs[i] == a[j]) {              
                //arr_index[j] = i;
                cntr[j]++;
                break;
            }
        }
        if (j == f){     
            next = 0;
            // Find frame with lowest count
            min_count = 9999;
            for (k = 0; k < f; k++) {
                if (cntr[k] < min_count) {
                    min_count = cntr[k];
                }
            }
            // Find frame that has an earliest arrival index and has lowest count
            min_arr_index = 9999;
            for (k = 0; k < f; k++) {
                if ((cntr[k] == min_count) && (arr_index[k] < min_arr_index)) {
                    min_arr_index = arr_index[k];
                    }
            }

            // Find frame that has an earliest arrival index and alos lowest count to replace
            for (k = 0; k < f; k++) {
                if ((cntr[k] == min_count) && (arr_index[k] == min_arr_index)) {
                    next = k;
                    break;
                }
            }
            arr_index[next] = i;
            a[next] = rs[i];
            cntr[next] = 1;
            pf++;
        }

        printf("\t%d", rs[i]);
        for (j = 0; j < f; j++)
            printf("\t\t%d", a[j]);
        if (j == f)
            printf("\t\t%d", pf);

        printf("\n");
    }
    printf("\n\n Total number of page faults: %d\n", pf);
}
