// RESOURCCE REQUEST ALGORITHM


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

    int Allocated[n][m], Maximum[n][m], Request[m];

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

    // Print matrices for verification
    printf("PID\tAllocated\tMaximum\n");
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
        printf("\n");
    }

    // Resource Request Algorithm
    int process;
    printf("Enter the process ID making the resource request: ");
    scanf("%d", &process);

    printf("Enter the request vector: ");
    for (int j = 0; j < m; j++)
    {
        scanf("%d", &Request[j]);
    }

    int isValid = 1;
    for (int j = 0; j < m; j++)
    {
        if (Request[j] > (Maximum[process][j] - Allocated[process][j]))
        {
            isValid = 0;
            break;
        }
    }

    if (isValid)
    {
        for (int j = 0; j < m; j++)
        {
            if (Request[j] > Available[j])
            {
                isValid = 0;
                break;
            }
        }

        if (isValid)
        {
            // Temporarily allocate the resources
            for (int j = 0; j < m; j++)
            {
                Available[j] -= Request[j];
                Allocated[process][j] += Request[j];
            }

            // Check for safety
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
            int safe = 1;

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
                            if (Allocated[i][j] > Work[j])
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
                            safe = 0;
                            break;
                        }
                    }
                    break;
                }
            }

            if (safe)
            {
                printf("Request can be granted.\n");
                printf("Safe sequence is: ");
                for (int i = 0; i < n; i++)
                {
                    printf("P%d ", safeSequence[i]);
                }
                printf("\n");
            }
            else
            {
                // Revert allocation
                for (int j = 0; j < m; j++)
                {
                    Available[j] += Request[j];
                    Allocated[process][j] -= Request[j];
                }
                printf("Request cannot be granted. System would be unsafe.\n");
            }
        }
        else
        {
            printf("Request exceeds available resources. Process must wait.\n");
        }
    }
    else
    {
        printf("Request exceeds maximum claim. Invalid request.\n");
    }

    return 0;
}

/*

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

1

1 0 2

*/