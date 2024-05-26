// DEADLOCK DETECTION ALGORITHM


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

    int Allocated[n][m], Request[n][m];

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &Allocated[i][j]);
        }
    }

    printf("Enter request matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &Request[i][j]);
        }
    }

    printf("PID\tAllocated\tRequest\n");
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
            printf("%d ", Request[i][j]);
        }
        printf("\n");
    }

    // Deadlock Detection Algorithm
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
    int safeIndex = 0;
    int deadlock = 0;

    while (1)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (Finish[i] == 0)
            {
                int j;
                for (j = 0; j < m; j++)
                {
                    if (Request[i][j] > Work[j])
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
                    Finish[i] = 1;
                    safeSequence[safeIndex++] = P[i];
                    found = 1;
                }
            }
        }

        if (!found)
        {
            for (int i = 0; i < n; i++)
            {
                if (Finish[i] == 0)
                {
                    deadlock = 1;
                    printf("System is in a deadlock state.\n");
                    printf("Deadlocked processes are: ");
                    for (int j = 0; j < n; j++)
                    {
                        if (Finish[j] == 0)
                        {
                            printf("P%d ", P[j]);
                        }
                    }
                    printf("\n");
                    break;
                }
            }
            break;
        }
    }

    if (!deadlock)
    {
        printf("No deadlock detected.\n");
        printf("Safe sequence is: ");
        for (int i = 0; i < n; i++)
        {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    }

    return 0;
}

/*

5
3
1 2 3 4 5
0 0 0

0 1 0
2 0 0
3 0 3
2 1 1
0 0 2

0 0 0
2 0 2
0 0 0
1 0 0
0 0 2

*/
