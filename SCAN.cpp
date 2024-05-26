// SCAN DISK SCHEDULING

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    int n;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the order of requests: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    int head;
    printf("Enter initial head position: ");
    scanf("%d", &head);

    int direction;
    printf("Enter direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    // Initialize an array to keep track of visited requests
    int visited[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    int total_head_movement = 0;
    int cur_head = head;

    // Moving towards right
    if (direction == 1)
    {
        for (int cur_track = head; cur_track < 200; cur_track++)
        {
            for (int j = 0; j < n; j++)
            {
                if (requests[j] == cur_track && visited[j] == 0)
                {
                    total_head_movement += abs(cur_track - cur_head);
                    cur_head = cur_track;
                    visited[j] = 1;
                }
            }
        }

        // Go to the end and then move left
        total_head_movement += abs(199 - cur_head);
        cur_head = 199;

        for (int cur_track = 199; cur_track >= 0; cur_track--)
        {
            for (int j = 0; j < n; j++)
            {
                if (requests[j] == cur_track && visited[j] == 0)
                {
                    total_head_movement += abs(cur_track - cur_head);
                    cur_head = cur_track;
                    visited[j] = 1;
                }
            }
        }
    }
    // Moving towards left
    else if (direction == 0)
    {
        for (int cur_track = head; cur_track >= 0; cur_track--)
        {
            for (int j = 0; j < n; j++)
            {
                if (requests[j] == cur_track && visited[j] == 0)
                {
                    total_head_movement += abs(cur_track - cur_head);
                    cur_head = cur_track;
                    visited[j] = 1;
                }
            }
        }

        // Go to the beginning and then move right
        total_head_movement += abs(0 - cur_head);
        cur_head = 0;

        for (int cur_track = 0; cur_track < 200; cur_track++)
        {
            for (int j = 0; j < n; j++)
            {
                if (requests[j] == cur_track && visited[j] == 0)
                {
                    total_head_movement += abs(cur_track - cur_head);
                    cur_head = cur_track;
                    visited[j] = 1;
                }
            }
        }
    }

    printf("Total head movements: %d\n", total_head_movement);

    return 0;
}
