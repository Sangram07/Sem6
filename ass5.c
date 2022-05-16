#include<stdio.h>
#include<stdlib.h>
int n,m,**Max,**Alloc,**Need,*Avail,*Work,*Request;
int **Malloc(int **ptr)
{
	int i;
	ptr=(int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	ptr[i]=(int*)malloc(m*sizeof(int));
	return ptr;
}
void Display(int **ptr)
{
	printf("\n---------------------------------------\n");
	printf("              ");
	int i,j;
	for(i=0;i<m;i++)printf("Res %d\t",i+1);
	printf("\n---------------------------------------\n");
	for(i=0;i<n;i++)
	{
		printf("Process %d:\t",i+1);
		for(j=0;j<m;j++)
		{
			printf("%d\t  ",ptr[i][j]);
		}
		printf("\n");
	}
	printf("---------------------------------------\n\n");
}
void display(int *ptr)
{
	printf("\n---------------------------------------\n");
	int i;
	printf("  ");
	for(i=0;i<m;i++)printf("Res %d\t",i+1);
	printf("\n---------------------------------------\n");
	printf("   ");
	for(i=0;i<m;i++)
	{
			printf("%d\t  ",ptr[i]);
	}
	printf("\n---------------------------------------\n\n");
}

void Safety_Algo(int **Need,int *Work)
{
	int *Finish=(int*)malloc(n*sizeof(int));
	int flag,c=0,i,j;
	for(i=0;i<n;i++)Finish[i]=0;
	while(c<n){
	for(i=0;i<n;i++)
	{
		flag=0;
		for(j=0;j<m;j++)
		{
			if(Need[i][j]>Work[j])				
			{
				flag=1;break;
			}
		}
		if(flag==0){flag=3;break;}
	}
	if(flag==3)
	{	
		Finish[i]=1;
		c++;
		for(j=0;j<m;j++)
		{
			Work[j]+=Need[i][j];
		}
	}
	else if(flag==1)
	{
		printf("\nSystem is Not in Safe State\n");exit(0);
	}
	}
	printf("\nSystem is in Safe State\n");
			
}




void main()
{
	int i,j,k;
	printf("\nEnter Number of Processes: ");
	scanf("%d",&n);
	while(n<=0)
	{
		printf("\nInvalid input, Enter again: ");
		scanf("%d",&n);
	}

	printf("\nEnter Number of Resources: ");
	scanf("%d",&m);
	while(m<=0)
	{
		printf("\nInvalid input, Enter again: ");
		scanf("%d",&m);
	}

	Avail=(int*)malloc(m*sizeof(int));
	Work=(int*)malloc(m*sizeof(int));
	printf("\nAvailability Information");
	for(i=0;i<m;i++)
	{
		printf("\nResource %d: ",i+1);
		scanf("%d",&Avail[i]);
		while(Avail[i]<0)
		{
			printf("\nInvalid input, Enter again: ");
			scanf("%d",&Avail[i]);
		}
	}

	Max=Malloc(Max);
	printf("\nMaximum Need Information");
	for(i=0;i<n;i++)
	{
		printf("\nMaximum Need for Process %d",i+1);
		for(j=0;j<m;j++)
		{
			printf("\nResource %d: ",i+1);
			scanf("%d",&Max[i][j]);
			while(Max[i][j]>Avail[j]||Max[i][j]<0)
			{
			printf("\nInvalid input, Enter Valid Need: ");
			scanf("%d",&Max[i][j]);
			}
		}
	}

	Need=Malloc(Need);
	Alloc=Malloc(Alloc);
	printf("\nAllocation Information");
	for(i=0;i<n;i++)
	{
		printf("\nResources Allocated for Process %d",i+1);
		for(j=0;j<m;j++)
		{
			printf("\nResource %d: ",i+1);
			scanf("%d",&Alloc[i][j]);
			while(Max[i][j]<Alloc[i][j]||Alloc[i][j]<0)
			{
			printf("\nInvalid input, Enter Valid Allocation: ");
			scanf("%d",&Alloc[i][j]);
			}
		}
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			Avail[j]-=Alloc[i][j];
			//Availability Calcuation
		}
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			Need[i][j]=Max[i][j]-Alloc[i][j];
			//Need Calcuation
		}
	}
	
	for(i=0;i<m;i++)Work[i]=Avail[i];

	printf("\nMaximum Need\n");
	Display(Max);
	printf("\nAllocated Resources\n");
	Display(Alloc);
	printf("\nRemaining Need\n");
	Display(Need);
	printf("\nAvailable Resources\n");
	display(Avail);
	Safety_Algo(Need,Work);
	printf("\nChoose Process for Resource-Request( 0 - %d ): ",n);
	scanf("%d",&k);
	Request=(int*)malloc(n*sizeof(int));
	printf("\nEnter Resource-Request Information");
	for(i=0;i<m;i++)
	{
		printf("\nResource %d: ",i+1);
		scanf("%d",&Request[i]);
		while(Request[i]<0)
		{
			printf("\nInvalid input, Enter again: ");
			scanf("%d",&Request[i]);
		}
		while(Request[i]>Need[k][i])
		{
			printf("\nRequest can't be Greater than Need, Enter again: ");
			scanf("%d",&Request[i]);
		}
		Avail[i]-=Request[i];
		Alloc[k][i]+=Request[i];
		Need[k][i]-=Request[i];

	}

	for(i=0;i<m;i++)Work[i]=Avail[i];
	
	Safety_Algo(Need,Work);




}