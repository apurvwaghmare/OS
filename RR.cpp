// ROUND ROBIN



#include <stdio.h>
#include <stdlib.h>
#define TIME_QUANTUM 2

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int P[n], AT[n], BT[n], CT[n], TAT[n], WT[n];
    int remaining_BT[n], is_completed[n];
    float total_TAT = 0.0, total_WT = 0.0;
    
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival time and Burst time for Process P%d: ", i + 1);
        scanf("%d %d", &AT[i], &BT[i]);
        P[i] = i + 1;
        remaining_BT[i] = BT[i];
        is_completed[i] = 0;
    }
    
    int current_time = 0, completed = 0;
    
    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (remaining_BT[i] > 0) {
                if (remaining_BT[i] > TIME_QUANTUM) {
                    current_time += TIME_QUANTUM;
                    remaining_BT[i] -= TIME_QUANTUM;
                } else {
                    current_time += remaining_BT[i]; 
                    CT[i] = current_time;
                    TAT[i] = CT[i] - AT[i];
                    WT[i] = TAT[i] - BT[i];
                    
                    total_TAT += TAT[i];
                    total_WT += WT[i];
                    
                    remaining_BT[i] = 0;
                    is_completed[i] = 1;
                    completed++;
                }
            }
        }
    }
    
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", P[i], AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }
    
    float Average_TAT = total_TAT / n;
    float Average_WT = total_WT / n;
    
    printf("Average Turn Around Time: %.2f\n", Average_TAT);
    printf("Average Waiting Time: %.2f\n", Average_WT);
    
    return 0;
}


/*

4 
0 5 
1 4 
2 2 
4 1 
*/
