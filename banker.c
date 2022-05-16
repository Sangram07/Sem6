#include <stdio.h>
#include <stdlib.h>

int **NEED, *WORK, *AVAILABLE, **MAX, **ALLOCATION, *safe_seq;
int n, m, is_safe = 1;

void init_matrices();
void printMatrix(int **);
void acceptAvailable();
void acceptMax();
void acceptAllocation();
void calculateNeed();
void safety_algo();
void copy_tuple(int *a, int *b);
int cmp_tuple(int *a, int *b);


int main()
{
    int i, j;

    do
    {    
        printf("\nEnter number of processes (n) :");
        scanf("%d", &n);

        if(n <= 0)
            printf("Please enter number greater than 0.\n");
    } while (n <= 0);
    
    do
    {
        printf("\nEnter number of type of resource types (m) :");
        scanf("%d", &m);

        if(m <= 0)
            printf("Please enter number greater than 0.\n");
    } while (m <= 0);

    init_matrices();
    acceptAvailable();
    acceptMax();
    acceptAllocation();
    calculateNeed();

    printf("MAX ");
    printMatrix(MAX);
    printf("Allocation");
    printMatrix(ALLOCATION);
    printf("NEED :\n");
    printMatrix(NEED);
    
    safety_algo();

    if(is_safe == 1)
    {
        printf("\nSystem is safe.\nSafe sequence :");
        for(i = 0; i < n; i++)
            printf("%d ", safe_seq[i]);
        printf("\n");
    }
    else{
        printf("\nSystem is not safe.\n");
    }

    return 0;
}


void init_matrices()
{
    int i;
    AVAILABLE = (int *)malloc(sizeof(int) * m);

    NEED = (int **)malloc(sizeof(int *) * n);
    for(i = 0; i < n; i++)
        NEED[i] = (int *)malloc(sizeof(int) * m);
        
    MAX = (int **)malloc(sizeof(int *) * n);
    for(i = 0; i < n; i++)
        MAX[i] = (int *)malloc(sizeof(int ) * m);

    ALLOCATION = (int **)malloc(sizeof(int *) * n);
    for(i = 0; i < n; i++)
        ALLOCATION[i] = (int *)malloc(sizeof(int) * m);
}


void printMatrix(int **mat)
{
    int i, j;
    printf("\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
            printf("%d ", mat[i][j]);

        printf("\n");
    }
}


void acceptAvailable()
{
    int res_count = 0, i;
    printf("Enter resource instances count.\n");
    for(i = 0; i < m; i++)
    {
        do
        {
            printf("Enter number of instances of resources type(%d) :", i + 1);
            scanf("%d", &res_count);    

            if(res_count < 0)
                printf("Instances should be greater than 0.\n");
            else
                AVAILABLE[i] = res_count;
        } while (res_count < 0);
    }   
}


void acceptMax()
{
    int max_req = 0, i, j;
    printf("Enter MAX matrix.\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            do
            {
                printf("Enter MAX[%d][%d] entry :", i , j);
                scanf("%d", &max_req);    

                if(max_req < 0 || max_req > AVAILABLE[j])
                    printf("MAX demand should be >=0 & less than resource type instances.\n");
                else
                    MAX[i][j] = max_req;
            } while (max_req < 0 || max_req > AVAILABLE[j]);
        }
    }   
}


void acceptAllocation()
{
    int allocation = 0, i, j;
    printf("Enter ALLOCATION matrix.\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            do
            {
                printf("Enter ALLOCATION[%d][%d] entry :", i , j);
                scanf("%d", &allocation);    

                if(allocation < 0 || allocation > MAX[i][j])
                    printf("allocation should be >=0 & less than MAX demand of process.\n");
                else
                    ALLOCATION[i][j] = allocation;
            } while (allocation < 0 || allocation > MAX[i][j]);
            AVAILABLE[j] -= ALLOCATION[i][j];
        }
    }   
}


void calculateNeed()
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
            NEED[i][j] = MAX[i][j] - ALLOCATION[i][j];
    }   
}

void safety_algo()
{
    int *work = (int *)malloc(sizeof(int) * m), *finish = (int *)malloc(sizeof(int) * n);
    int i, j, c = 0;

    safe_seq = (int *)malloc(sizeof(int) * n);
    for(i = 0; i < n; i++)
        finish[i] = 0;

    copy_tuple(AVAILABLE, work);

    for(i = 0; i < 2*n; i++)
    {
        if(finish[i%n] == 0 && cmp_tuple(NEED[i%n], work))
        {
            safe_seq[c++] = i%n;
            finish[i%n] = 1;
            for(j = 0; j < m; j++)
                work[j] += ALLOCATION[i%n][j];
        }
    }

    for(i = 0; i < n; i++)
        if (finish[i] != 1)
            is_safe = 0;
}

 
int cmp_tuple(int *a, int *b)
{
    int i = 0;
    for(i = 0; i <m; i++)
        if(a[i] > b[i])
            return 0;
    return 1;
}

void copy_tuple(int *a, int *b)
{
    int i = 0;
    for(i = 0; i < m; i++)
        b[i] = a[i];
}
