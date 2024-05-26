// PRIORITY NON - PREEMPTIVE


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int P[n], AT[n], BT[n], PR[n], CT[n], TAT[n], WT[n];
    float total_TAT = 0.0, total_WT = 0.0;
    
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival time, Burst time and Priority for Process P%d: ", i+1);
        scanf("%d %d %d", &AT[i], &BT[i], &PR[i]);
        P[i] = i + 1;
    }
    
    int completed = 0, current_time = 0;
    int is_completed[n];
    for(int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }
    
    while (completed != n) {
        int index = -1;
        int min_priority = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (AT[i] <= current_time && is_completed[i] == 0) {
                if (PR[i] < min_priority) {
                    min_priority = PR[i];
                    index = i;
                }
                if (PR[i] == min_priority) {
                    if (AT[i] < AT[index]) {
                        index = i;
                    }
                }
            }
        }
        
        if (index != -1) {
            CT[index] = current_time + BT[index];
            TAT[index] = CT[index] - AT[index];
            WT[index] = TAT[index] - BT[index];
            total_TAT += TAT[index];
            total_WT += WT[index];

            is_completed[index] = 1;
            completed++;
            current_time = CT[index];
        } else {
            current_time++;
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
5
0  12  4 
4  7  3 
7  3  1 
9  3  2
12 2  2 
*/