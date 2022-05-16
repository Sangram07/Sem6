#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	int no;
	float at,bt,st,wt,ft,tat,tmpbt;
        int priority;
	struct node *next ;
}NODE;

void sorting(NODE *start);
int process,min,count=0;
float S_time=0.0,idle[100];

void create_insert(NODE **p,int no,float at,float bt,int priority){
NODE *q,*r=*p;
q = (NODE*)malloc(sizeof(NODE));
q->no=no+1;
q->at=at;
q->bt=bt;
q->tmpbt=bt;
q->priority=priority;
q->next= NULL;
if(*p==NULL)
{
	*p=q;
}
else
{
	while(r->next!=NULL)
	{
		r=r->next;
	}
	r->next=q;
}
}

void calculate(NODE **p)
{
    NODE *q=*p;
    float tmp;
    printf("\n\n GANTT CHART \n=========================================================================================\n");
    if(q->at!=0.0)
        S_time=q->at;
    else
        S_time=0.0;

    while(count!=process)
    {
        q=*p;
        int counter=0;
        min=1000;
        for(;q!=NULL;q=q->next)
        {
            if(min>q->priority && q->at<=S_time && q->bt>0.0)
            {
                min=q->priority;
            }
            counter++;
        }
        q=*p;
        while(q)
        {
            tmp=1.0;
            if(q->priority==min)
            {
                printf("|P%d",q->no);
                if(q->bt<1.0  && q->bt > 0.0)
                {
                    tmp=q->bt;
                    q->bt-=tmp;
                }
                else
                    q->bt=q->bt-tmp;
               if(q->bt==0.0)
                {
                  count++;
                  q->ft=S_time+tmp;
                  q->tat=S_time+tmp-q->at;    
                  q->wt=q->tat-q->tmpbt;
                }
                break;
            }
            q=q->next;
        }
        S_time+=tmp;
    }    
    printf("|\n==========================================================================================");
}

void display_sort(NODE *p)
{
    NODE *r=p;
    printf("\n======================================\n|ProcessId | A.T   |   B.T  | Priority |\n=========================================");
    while(r)
    {
        printf("\n| P%d     |  %.2f   |  %.2f   |   %d",r->no,r->at,r->bt,r->priority);
        r=r->next;
    }
}

void display_chart(NODE *p)
{
    NODE *r=p;
    printf("\n\n|ProcessId | A.T   |   B.T   |  F.T   |  W.T   |  T.A.T  |\n===================================================");
    while(r)
    {
        printf("\n| P%d     |  %.2f   |  %.2f   |  %.2f   |  %.2f   |   %.2f   |",r->no,r->at,r->tmpbt,r->ft,r->wt,r->tat);
        r=r->next;
    }
}

void swap(NODE *a,NODE *b)
{
    float tmp,tmp1;
    int pno;
    pno = a->no;
    a->no = b->no;
    b->no =pno;
    
    tmp = a->at;
    a->at = b->at;
    b->at =tmp;
    
    tmp = a->bt;
    a->bt = b->bt;
    b->bt =tmp;

    tmp = a->tmpbt;
    a->tmpbt = b->tmpbt;
    b->tmpbt =tmp;

    pno = a->priority;
    a->priority = b->priority;
    b->priority =pno;
    
}

void sorting(NODE *start)
{
    int swapped,i;
    NODE *ptr;
    NODE *lptr =NULL;
    if(start == NULL)
        return;
    
    do
    {
      swapped=0;
      ptr=start;
      while(ptr->next!=lptr)
      {
        if(ptr->at > ptr->next->at)
        {
            swap(ptr,ptr->next);
            swapped=1;
        }  
        ptr = ptr->next;
      }
    }while(swapped);
}

void display(NODE *p,int process){
	float ttat,twt,trd,trt,tbt;
	ttat=twt=trd=trt=tbt=0;
//	printf("\n\n PROCESS DETAILS :");
	while(p!=NULL){
/*	printf("\n PROCESS : %d \n",p->no);
	printf("\n ARRIVAL TIME : %.2f \n",p->at);
	printf("\n BURST TIME : %.2f\n",p->tmpbt);
	printf("\n PRIORITY : %d\n",p->priority);
	printf("\n TURN AROUND TIME : %.2f\n",p->tat);
	printf("\n WAITING TIME: %.2f\n",p->wt);
        printf("\n ========================\n");*/
	ttat+=p->tat;
	twt+=p->wt;
	tbt+=p->tmpbt;
	p=p->next;
	}
	printf("\n\n OVERALL DETAILS \n");
        printf("\n Throughput : %.2f",process/tbt);
	printf("\n Average wait time : %.2f",twt/process);
        printf("\n Average turn around time : %.2f",ttat/process);
}

void main()
{
	NODE *head=NULL;
	char ch;
	int i,j,k,priority;
	float arr_time,burst_time;
    do
    {
	printf("\n <== Enter process  details ==> ");
        printf("\n Arrival Time : ");
	scanf("%f",&arr_time);
	printf("\n Burst Time   : ");
	scanf("%f",&burst_time);
        printf("\n Enter the priority ==> ");
        scanf("%d",&priority);
	create_insert(&head,process,arr_time,burst_time,priority);
        process++;
        printf("Is there any other process (Y/N) ==> ");
        scanf("%d",&i);
        scanf("%c",&ch);
    }while(ch=='y'|| ch=='Y');    
    printf(" \t Process list ");
    display_sort(head);
    sorting(head);
    calculate(&head);
    display_chart(head);
    display(head,process);
 printf("\n===================STOP======================\n\n");
}

