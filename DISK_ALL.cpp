// DISK SCHEDULING ALL 



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// FCFS Disk Scheduling
void fcfs(int requests[], int n, int head) {
    int total_head_movement = 0;
    for(int i = 0; i < n; i++){
        total_head_movement += abs(requests[i] - head);
        head = requests[i];
    }
    printf("FCFS Total head movements: %d\n", total_head_movement);
}

// SSTF Disk Scheduling
void sstf(int requests[], int n, int head) {
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
                int distance = abs(requests[j] - head);
                if(distance < min_distance){
                    min_distance = distance;
                    min_index = j;
                }
            }
        }
        if(min_index != -1){
            total_head_movement += min_distance;
            head = requests[min_index];
            visited[min_index] = 1;
        }
    }
    printf("SSTF Total head movements: %d\n", total_head_movement);
}

// SCAN Disk Scheduling
void scan(int requests[], int n, int head, int direction) {
    int visited[n];
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }
    int total_head_movement = 0;
    int cur_head = head;
    if (direction == 1) {
        for (int cur_track = head; cur_track < 200; cur_track++) {
            for (int j = 0; j < n; j++) {
                if (requests[j] == cur_track && visited[j] == 0) {
                    total_head_movement += abs(cur_track - cur_head);
                    cur_head = cur_track;
                    visited[j] = 1;
                }
            }
        }
        total_head_movement += abs(199 - cur_head);
        cur_head = 199;
        for (int cur_track = 199; cur_track >= 0; cur_track--) {
            for (int j = 0; j < n; j++) {
                if (requests[j] == cur_track && visited[j] == 0) {
                    total_head_movement += abs(cur_track - cur_head);
                    cur_head = cur_track;
                    visited[j] = 1;
                }
            }
        }
    } else if (direction == 0) {
        for (int cur_track = head; cur_track >= 0; cur_track--) {
            for (int j = 0; j < n; j++) {
                if (requests[j] == cur_track && visited[j] == 0) {
                    total_head_movement += abs(cur_track - cur_head);
                    cur_head = cur_track;
                    visited[j] = 1;
                }
            }
        }
        total_head_movement += abs(0 - cur_head);
        cur_head = 0;
        for (int cur_track = 0; cur_track < 200; cur_track++) {
            for (int j = 0; j < n; j++) {
                if (requests[j] == cur_track && visited[j] == 0) {
                    total_head_movement += abs(cur_track - cur_head);
                    cur_head = cur_track;
                    visited[j] = 1;
                }
            }
        }
    }
    printf("SCAN Total head movements: %d\n", total_head_movement);
}

// C-SCAN Disk Scheduling
void c_scan(int requests[], int n, int head) {
    int total_head_movement = 0;
    int cur_head = head;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            total_head_movement += abs(requests[i] - cur_head);
            cur_head = requests[i];
        }
    }
    total_head_movement += abs(199 - cur_head);
    cur_head = 199;
    total_head_movement += 199;
    cur_head = 0;
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            total_head_movement += abs(requests[i] - cur_head);
            cur_head = requests[i];
        }
    }
    printf("C-SCAN Total head movements: %d\n", total_head_movement);
}

int main() {
    int n;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the order of requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    int head;
    printf("Enter initial head position: ");
    scanf("%d", &head);

    int direction;
    printf("Enter direction for SCAN (0 for left, 1 for right): ");
    scanf("%d", &direction);

    printf("\n");
    fcfs(requests, n, head);
    printf("\n");
    sstf(requests, n, head);
    printf("\n");
    scan(requests, n, head, direction);
    printf("\n");
    c_scan(requests, n, head);

    return 0;
}


