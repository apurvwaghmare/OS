// SSTF DISK SCHEDLUING 


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
    
    int visited[n];
    for(int i = 0; i < n; i++){
        visited[i] = 0;    
    }
    
    int total_head_movement = 0;
    
    for(int i = 0; i < n; i++){
        int min_distance = INT_MAX;
        int min_index = -1;
        for(int j = 0; j < n; j++){
            if(visited[j] != 1){
                int distance = abs(request[j] - head);
                if(distance < min_distance){
                    min_distance = distance;
                    min_index = j;
                }
            }
        }
        if(min_index != -1){
            total_head_movement += min_distance;
            head = request[min_index];
            visited[min_index] = 1;
        }
    }
    
    printf("Total head movements: %d",total_head_movement);
    return 0;
}


/*

7
82 170 43 140 24 16 190 
50

*/

