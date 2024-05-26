//  PRIORITY PREEMPTIVE




#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int P[n], AT[n], BT[n], PR[n], CT[n], TAT[n], WT[n];
    int remaining_BT[n], is_completed[n];
    float total_TAT = 0.0, total_WT = 0.0;
    
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival time, Burst time, and Priority for Process P%d: ", i + 1);
        scanf("%d %d %d", &AT[i], &BT[i], &PR[i]);
        P[i] = i + 1;
        remaining_BT[i] = BT[i];
        is_completed[i] = 0;
    }
    
    int current_time = 0, completed = 0, index;
    
    while (completed != n) {
        int min_priority = INT_MAX;
        index = -1;
        
        for (int i = 0; i < n; i++) {
            if (AT[i] <= current_time && is_completed[i] == 0 && PR[i] < min_priority) {
                min_priority = PR[i];
                index = i;
            }
        }
        
        if (index == -1) {
            current_time++;
            continue;
        }
        
        remaining_BT[index]--;
        current_time++;
        
        if (remaining_BT[index] == 0) {
            CT[index] = current_time;
            TAT[index] = CT[index] - AT[index];
            WT[index] = TAT[index] - BT[index];
            
            total_TAT += TAT[index];
            total_WT += WT[index];
            
            is_completed[index] = 1;
            completed++;
        }
    }
    
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", P[i], AT[i], BT[i], PR[i], CT[i], TAT[i], WT[i]);
    }
    
    float Average_TAT = total_TAT / n;
    float Average_WT = total_WT / n;
    
    printf("Average Turn Around Time: %.2f\n", Average_TAT);
    printf("Average Waiting Time: %.2f\n", Average_WT);
    
    return 0;
}

/*
4 
0 10 5 
1 6 4 
3 2 2 
5 4 0 

 */
