// SJF NON - PREEMPTIVE


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int P[n], AT[n], BT[n], CT[n], TAT[n], WT[n];
    float total_TAT = 0.0, total_WT = 0.0;
    printf("Enter processes ID: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &P[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival and Burst time for P%d: ", P[i]);
        scanf("%d %d", &AT[i], &BT[i]);
    }
    
    // Sort by Arrival Time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (AT[i] > AT[j]) {
                int temp = AT[i];
                AT[i] = AT[j];
                AT[j] = temp;

                temp = BT[i];
                BT[i] = BT[j];
                BT[j] = temp;

                temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
        }
    }
    
    int completed = 0, current_time = 0;
    int is_completed[n];
    for(int i = 0; i < n; i++){
        is_completed[i] = 0;
    }
    
    while(completed != n){
        int index = -1;
        int min_burst_time = INT_MAX;
        
        for(int i = 0; i < n; i++){
            if(AT[i] <= current_time && is_completed[i] == 0){
                if(BT[i] < min_burst_time){
                    min_burst_time = BT[i];
                    index = i;
                }
                if(BT[i] == min_burst_time){
                    if(AT[i] < AT[index]){
                        index = i;
                    }
                }
            }
        }
        if(index != -1){
            CT[index] = current_time + BT[index];
            TAT[index] = CT[index] - AT[index];
            WT[index] = TAT[index] - BT[index];
            total_TAT += TAT[index];
            total_WT += WT[index];
            
            is_completed[index] = 1;
            completed++;
            current_time = CT[index];
        }
        else{
            current_time++;
        }
    }
    
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", P[i], AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }
    
    float Average_TAT = total_TAT / n;
    float Average_WT = total_WT / n;
    
    printf("Average Turn Around time: %.2f", Average_TAT);
    printf("\nAverage Waiting time: %.2f", Average_WT);
    return 0;
}


/*
5
0 3 
2 6 
4 4 
6 5 
8 2 

*/
