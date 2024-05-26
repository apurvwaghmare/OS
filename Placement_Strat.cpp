// PLACEMENT STRATEGIES


#include <stdio.h>
#include <stdlib.h>

void firstFit(int n, int processsize[], int m, int blocksize[], int allocation[]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (processsize[i] <= blocksize[j]) {
                allocation[i] = j + 1;
                blocksize[j] -= processsize[i];
                break;
            }
        }
    }
}

void nextFit(int n, int processsize[], int m, int blocksize[], int allocation[]) {
    int last_allocated = 0;
    for (int i = 0; i < n; i++) {
        int allocated = 0;
        for (int j = 0; j < m; j++) {
            int index = (last_allocated + j) % m;
            if (processsize[i] <= blocksize[index]) {
                allocation[i] = index + 1;
                blocksize[index] -= processsize[i];
                last_allocated = (index + 1) % m;
                allocated = 1;
                break;
            }
        }
        if (!allocated) {
            allocation[i] = -1;
        }
    }
}

void bestFit(int n, int processsize[], int m, int blocksize[], int allocation[]) {
    for (int i = 0; i < n; i++) {
        int best_index = -1;
        for (int j = 0; j < m; j++) {
            if (processsize[i] <= blocksize[j]) {
                if (best_index == -1 || blocksize[j] < blocksize[best_index]) {
                    best_index = j;
                }
            }
        }
        if (best_index != -1) {
            allocation[i] = best_index + 1;
            blocksize[best_index] -= processsize[i];
        }
    }
}

void worstFit(int n, int processsize[], int m, int blocksize[], int allocation[]) {
    for (int i = 0; i < n; i++) {
        int worst_index = -1;
        for (int j = 0; j < m; j++) {
            if (processsize[i] <= blocksize[j]) {
                if (worst_index == -1 || blocksize[j] > blocksize[worst_index]) {
                    worst_index = j;
                }
            }
        }
        if (worst_index != -1) {
            allocation[i] = worst_index + 1;
            blocksize[worst_index] -= processsize[i];
        }
    }
}

int main() {
    int n, m, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processsize[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the size of Process%d: ", i + 1);
        scanf("%d", &processsize[i]);
    }

    printf("Enter the number of blocks: ");
    scanf("%d", &m);

    int blocksize[m];
    for (int i = 0; i < m; i++) {
        printf("Enter the size of Block%d: ", i + 1);
        scanf("%d", &blocksize[i]);
    }

    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    printf("Choose the allocation strategy:\n");
    printf("1. First Fit\n");
    printf("2. Next Fit\n");
    printf("3. Best Fit\n");
    printf("4. Worst Fit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            firstFit(n, processsize, m, blocksize, allocation);
            break;
        case 2:
            nextFit(n, processsize, m, blocksize, allocation);
            break;
        case 3:
            bestFit(n, processsize, m, blocksize, allocation);
            break;
        case 4:
            worstFit(n, processsize, m, blocksize, allocation);
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }

    printf("PID\tProcess Size\tBlock\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", i + 1, processsize[i], allocation[i]);
    }

    return 0;
}

/*

4 
212
417
112
426
5
100
500
200
300
600
1 or 2 or 3 or 4

*/