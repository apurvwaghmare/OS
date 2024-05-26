// FCFS DISK SCHEDLUING 


#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter number of request: ");
    scanf("%d",&n);
    
    int request[n];
    printf("Enter the order of request: ");
    for(int i = 0; i < n; i++){
        scanf("%d",&request[i]);
    }
    
    int head;
    printf("Enter initial head position: ");
    scanf("%d",&head);
    
    int total_head_movement = 0;
    
    for(int i = 0; i < n; i++){
        total_head_movement += abs(request[i] - head);
        head = request[i];
    }
    
    printf("Total head movements: %d",total_head_movement);
    return 0;
}

/*

7
82 170 43 140 24 16 190 
50

*/
