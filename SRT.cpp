//  SRTF PREEMPTIVE



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int P[n], AT[n], BT[n], remaining_BT[n], CT[n], TAT[n], WT[n], start_time[n];
    float total_TAT = 0.0, total_WT = 0.0;
    
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival time and Burst time for Process P%d: ", i + 1);
        scanf("%d %d", &AT[i], &BT[i]);
        P[i] = i + 1;
        remaining_BT[i] = BT[i];
        start_time[i] = -1;
    }
    
    int completed = 0, current_time = 0;
    int is_completed[n];
    for(int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }
    
    while (completed != n) {
        int index = -1;
        int min_remaining_time = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (AT[i] <= current_time && is_completed[i] == 0) {
                if (remaining_BT[i] < min_remaining_time) {
                    min_remaining_time = remaining_BT[i];
                    index = i;
                }
                if (remaining_BT[i] == min_remaining_time) {
                    if (AT[i] < AT[index]) {
                        index = i;
                    }
                }
            }
        }
        
        if (index != -1) {
            if (start_time[index] == -1) {
                start_time[index] = current_time;
            }
            current_time++;
            remaining_BT[index]--;
            
            if (remaining_BT[index] == 0) {
                CT[index] = current_time;
                TAT[index] = CT[index] - AT[index];
                WT[index] = TAT[index] - BT[index];
                
                total_TAT += TAT[index];
                total_WT += WT[index];

                is_completed[index] = 1;
                completed++;
            }
        } else {
            current_time++;
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
0 8 
1 4 
2 9 
3 5

*/