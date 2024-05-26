// FCFS SCHEDULING ALGORITHM




#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    
    int P[n], AT[n], BT[n], CT[n], TAT[n], WT[n];
    float Average_TAT = 0.0, Average_WT = 0.0;
    
    printf("Enter Process ID: ");
    for(int i = 0; i < n; i++){
        scanf("%d",&P[i]);
    }
    
    for(int i = 0; i < n; i++){
        printf("Enter the Process Arrival and Burst Time for P%d: ",i+1);
        scanf("%d %d",&AT[i], &BT[i]);
    }
    
    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j < n; j++){
            if(AT[i] > AT[j]){
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
    
    // Calculating Completion time
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            CT[i] = AT[i] + BT[i];
        } else {
            if (AT[i] > CT[i-1]) {
                CT[i] = AT[i] + BT[i];
            } else {
                CT[i] = CT[i-1] + BT[i];
            }
        }
    }
    
    // Calculating turnaround time and waiting time
    for(int i = 0; i < n; i++){
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
    }
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t\n", P[i], AT[i], BT[i], CT[i], TAT[i], WT[i]);
        Average_TAT += TAT[i];
        Average_WT += WT[i];
    }

    Average_TAT /= n;
    Average_WT /= n;
    printf("Average Turnaround Time: %.2f\n", Average_TAT);
    printf("Average Waiting Time: %.2f\n", Average_WT);
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



