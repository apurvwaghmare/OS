//  C_SCAN DISK SCHEDULING



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
void c_scan(int requests[], int n, int head) {
    int total_head_movement = 0;
    int cur_head = head;

    // Sort requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Moving towards the right
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            total_head_movement += abs(requests[i] - cur_head);
            cur_head = requests[i];
        }
    }

    // Moving to the end (199)
    total_head_movement += abs(199 - cur_head);
    cur_head = 199;

    // Moving towards the left
    total_head_movement += 199; // Move from 199 to 0
    cur_head = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            total_head_movement += abs(requests[i] - cur_head);
            cur_head = requests[i];
        }
    }

    printf("Total head movements: %d\n", total_head_movement);
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

    c_scan(requests, n, head);

    return 0;
}
