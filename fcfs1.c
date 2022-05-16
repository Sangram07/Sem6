#include<stdio.h>
#include<stdlib.h>

float twt=0,ttat=0;
int n;

typedef struct process
{
   int pid;
   float at,bt,ct,tat,wt;
   struct process *next;
}process;

process *get_process(float at, float bt)
{
     static int i = 1;
     process *pr = (process*)malloc(sizeof(process));
     pr->at = at;
     pr->bt = bt;
     pr->pid=i++;
     pr->next = NULL;
     return pr;
}

void insert(process *ptr,float at,float bt)
{
      process *pro,*temp;
      pro = get_process(at,bt);
      while(ptr->next!=NULL)
        {
                temp=ptr;
                ptr=ptr->next;
                if(ptr->at>at)
                {
                     pro->next = ptr;
                     temp->next = pro;
                     return;
                }
        }
        ptr->next=pro;
}

void display(process *ptr)
{
          process *temp = ptr->next;
          printf("\n\nProcess\tArrival time\tBurst time\tComplete time\tturn around time\tWaiting time\n");
          while(temp!=NULL)
          {
             	printf("P%d\t %.2f\t\t%.2f\t\t%.2f\t\t%.2f\t\t\t%.2f\n",temp->pid,temp->at,temp->bt,temp->ct,temp->tat,temp->wt);
                temp=temp->next;
          }
          printf("\n\nAverage waiting time : %.2f \n Average turn around time : %.2f \n",twt/n,ttat/n);
}

void gantt_chart(process *p, int n)
{
   int i=0;
	p = p->next;
   process *r = p;
	
   printf("\n\n Gantt Chart: \n ");
   for(i=1; i<=n; i++)
        printf("----------------");
   printf("\n");


   for(i=1; i<=n && p != NULL; i++)
   {
         
        printf("|\tP%d\t",p->pid);
        p = p->next;
	
   }
        printf("|\n");

   for(i=1; i<=n; i++)
        printf("-----------------");

   printf("\n");
   printf("%.1f   \t\t",r->at);
   for(i=1; i<=n+1 && r != NULL; i++){
        printf("%.1f  \t\t",r->ct);
        r = r->next;
        }
}

void complete_time(process *ptr)
{
     process *temp, *t;
     temp = ptr->next;
     t = ptr;
     while(temp!=NULL)
     { 
        if(temp->at - t->ct<=0)
       	temp->ct = t->ct + temp->bt;
        else if(temp->at - t->ct >0)
        temp->ct = temp->bt+temp->at;
        t = temp;
        temp = temp->next;
     }
} 

void wt_and_tat(process *ptr)
{
       	process *temp=ptr->next;
        while(temp!=NULL)
        {
           	temp->tat = temp->ct - temp->at;
                ttat +=temp->tat;
                temp->wt = temp->tat-temp->bt;
                twt +=temp->wt;
                temp = temp->next; 
        }
}

void main(){
        process *head = NULL;
        int proc,i;
        float arrival_time,burst_time;
        process *START=(process*)malloc(sizeof(process));
        START ->next =NULL;
        printf("Enter the no. of Process: ");
        scanf("%d",&n);
        while(n<1)
        {
            printf("Number of process cannot be less than 1");
            scanf("%d",&n);
        }
        for(i=1; i<= n;i++){
                printf("\n Enter the details for process %d: \n",i);
                printf("\tArrival Time: ");
                scanf("%f",&arrival_time);
                printf("\tBurst Time : ");
                scanf("%f",&burst_time);
                
                insert(START,arrival_time,burst_time);
                }
        printf("\n<---------------------------START----------------------------------->\n");
//	wt_and_tat(START);
        complete_time(START);
        wt_and_tat(START);
        gantt_chart(START,n);
        display(START);
        printf("\n<-------------------------END----------------------------->\n");
}


