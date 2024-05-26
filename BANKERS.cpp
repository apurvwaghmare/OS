// BANKERS algorithm



#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int P[n];
    printf("Enter process IDs: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &P[i]);
    }

    int Available[m];
    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &Available[i]);
    }

    int Allocated[n][m], Maximum[n][m], Need[n][m];

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &Allocated[i][j]);
        }
    }

    printf("Enter maximum matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &Maximum[i][j]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            Need[i][j] = Maximum[i][j] - Allocated[i][j];
        }
    }

    printf("PID\tAllocated\tMaximum\t\tNeed\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t", P[i]);
        for (int j = 0; j < m; j++)
        {
            printf("%d ", Allocated[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < m; j++)
        {
            printf("%d ", Maximum[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < m; j++)
        {
            printf("%d ", Need[i][j]);
        }
        printf("\n");
    }

    // Safety algorithm
    int Work[m];
    for (int i = 0; i < m; i++)
    {
        Work[i] = Available[i];
    }

    int Finish[n];
    for (int i = 0; i < n; i++)
    {
        Finish[i] = 0;
    }

    int safeSequence[n];
    int count = 0;

    while (count < n)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (Finish[i] == 0)
            {
                int j;
                for (j = 0; j < m; j++)
                {
                    if (Need[i][j] > Work[j])
                    {
                        break;
                    }
                }

                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                    {
                        Work[k] += Allocated[i][k];
                    }
                    safeSequence[count++] = P[i];
                    Finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            printf("System is not in a safe state.\n");
            return -1;
        }
    }

    printf("System is in a safe state.\n");
    printf("Safe Sequence is: ");
    for (int i = 0; i < n; i++)
    {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return 0;
}

/*

5
3
1 2 3 4 5
3 3 2

0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

*/