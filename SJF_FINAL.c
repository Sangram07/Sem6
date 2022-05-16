#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<limits.h>

typedef struct node{
	int no;
	float at,bt,st,wt,ft,tat;
    int done;
	struct node *next ;
}NODE;

int process=0,no=0,c=0,count=0,proc_count=0;
float S_time=0.0,idle[100];

void display_sort(NODE *p);
void create_insert(NODE **p,int no,float at,float bt){
NODE *q,*r=*p;
q= (NODE*)malloc(sizeof(NODE));
q->no=no;
q->at=at;
q->bt=bt;
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

    tmp= a->ft;
    a->ft=b->ft;
    b->ft=tmp;

    tmp= a->st;
    a->st=b->st;
    b->st=tmp;

    tmp= a->tat;
    a->tat=b->tat;
    b->tat=tmp;

    tmp= a->wt;
    a->wt=b->wt;
    b->wt=tmp;
}

int calculate(NODE **p)
{
    NODE *q=*p,*r=*p,*tmp=*p;
    int c1=0,i=0,c2,tmp1;
    float time,min;
    printf("\n---------------------------------------------------------------------");
    printf("\n|Process |  A.T    |  B.T    |  S.T    |  W.T    |  F.T   |  T.A.T  |");
    printf("\n---------------------------------------------------------------------");

   while(q!=NULL)
    {   
        c2=0;
        if(c1==0)
        {   
            if(q->at>S_time)
            {
                idle[c++]=0.0;
                idle[c++]=q->at;
                S_time=q->at;
                c2=2;
            }
            else
            {
                q->st=q->at;
                q->wt=q->at;
                idle[c++]=q->st;
                c1++;
            }
        }
        else
        {  
             if(q->at>S_time)
	        {
		        q->st=S_time + (q->at-S_time);
                q->wt=q->st-q->at;  
		        idle[c++]=q->st;
		        idle[c++]=q->at;
	        }   
            else
    	    {
		        q->st=S_time;
		        q->wt=q->st-q->at;  
                idle[c++]=q->st;
	        }
        }   
            
        if(c2!=2)
        {
            q->ft=q->st+q->bt;
            time=q->ft;
            tmp1=q->no;
	        idle[c++]=q->ft;
            q->tat=q->ft-q->at;
            S_time=q->ft;
            printf("\n| P%d     |  %.2f   |  %.2f   |  %.2f   |  %.2f   |  %.2f  |  %.2f   |",q->no,q->at,q->bt,q->st,q->wt,q->ft,q->tat);
            r=*p;
            r=q->next;
            while(r!=NULL)
            {
                if(r->no==tmp1)
                {
                   if(r->at==1000) 
                    {
                        r->at=time+2;
                        proc_count++;  // TO COUNT IS ALL THE ARRIVAL TIME FOR BURST TIME GETS INITIALIZE 
                    }   
                }
			r=r->next;
            }
            
        q=q->next;
        r=*p;
            if(q!=NULL)
		    {	    	
		        if(q->at==1000)
		        { 
		    	tmp=q->next;
			        while(tmp)
		    	    {
	    			    if(tmp->no==q->no)
		    		    {
			    	    	swap(q,tmp);
				        	break;
			    	    }
				        tmp=tmp->next;
		    	    }
	    	    }

                min=q->bt;
    	        if(proc_count!=process/2)
                    r=q->next;
                else
                {
                    r=q;
                }     
            
                while(r  && proc_count!=(process/2))
		        {
                if(min>r->bt && r->at<=S_time && r->at!=1000)
                    {
                        min = r->bt;
                        if(proc_count<process/2)
                            swap(q,r);
                        else    
                            swap(q,q->next);
                    }
                    r=r->next;
                }
            
                if(proc_count==(process/2))
                {
                    if(q->next!=NULL)
                    {
                        min=q->bt;
                        if(q->at>S_time)
                        {
                            swap(q,q->next);
                        }
                    }
                }
            }        
        }
    }
    return c;
}


/*void display_sort(NODE *p)
{
    NODE *r=p;
    printf("\n=================================\n|ProcessId | A.T   | B.T  |  F.T |\n=================================");
    while(r)
    {
        printf("\n| P%d     |  %.2f   |  %.2f   |  %.2f",r->no,r->at,r->bt,r->ft);
        r=r->next;
    }
}*/


void sorting(NODE *start)
{
    int swapped,j,i;
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

    do
    {
      i=1;  
      swapped=0;
      ptr=start;
      while(i<process)
      {
      if(ptr->at==ptr->next->at )
      {
        if(ptr->bt > ptr->next->bt)
        {
            swap(ptr,ptr->next);
            swapped=1;
        }  
       }
        ptr = ptr->next;
        ++i;
      }
    }while(swapped);
}

// Sorting based on pid
void sorting_id(NODE *start)
{
    int swapped,j,i;
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
        if(ptr->no > ptr->next->no)
        {
            swap(ptr,ptr->next);
            swapped=1;
        }  
        ptr = ptr->next;
      }
    }while(swapped);

}


void gantt_chart(NODE *p,int process,float idle[],int c)
{
	int i,count=1;
	NODE *r=p;
	printf("\n\n GANTT CHART:\n");
    if(c>process)
        process=c;
	for(i=1;i<process;i++)
	{
		printf("--------");
	}	
	printf("\n");

	for(i=1;i<process;i++)
	{   
	    if(p->st==idle[i-1])
        {
            printf("|P%d\t",p->no);
		    p=p->next;
        }
        else{
            printf("!I%d\t",count);
            count++;
        }
	}	
	printf("|\n");

	for(i=1;i<process;i++)
		printf("--------");
	printf("\n");
	for(i=1;i<process;i++)	
	{
        if(r->st==idle[i-1])
        {
            printf("%.1f  \t",r->st);
		    r=r->next;
        }
        else{
            printf("%.1f  \t",idle[i-1]);
        }
	}	
    printf("%.1f",idle[c-1]);
}
/*
void display(NODE *p){
	printf("\n\n PROCESS DETAILS :");
	while(p!=NULL)
    {
        printf("\n PROCESS : %d \n",p->no);
        printf("\n ARRIVAL TIME : %.2f \n",p->at);
        printf("\n BURST TIME : %.2f\n",p->bt);
        printf("\n TURN AROUND TIME : %.2f\n",p->tat);
        printf("\n WAITING TIME: %.2f\n",p->wt);
        printf("\n ========================\n");
        p=p->next;    
	}
}*/

void display_overall(NODE *p){
    NODE *r=p,*q=p;
    float ttat,twt,tbt,tat,wt;
	ttat=twt=tbt=0;
    int i=1;
	r=r->next;
   /* printf("\n---------------------------------------------------------------------");
    printf("\n|Process |  A.T.1  |  B.T.1  |  A.T.2  |  B.T.2  |  W.T   |  T.A.T  |");
    printf("\n---------------------------------------------------------------------");*/
    while(q)
    {
        tat=r->ft-q->at;
        wt=tat-(q->bt+r->bt+2);
        ttat+=tat;
        twt+=wt;
        tbt+=q->bt+r->bt;
      //  printf("\n| P%d     |  %.2f   |  %.2f   |  %.2f   |  %.2f   |  %.2f  |  %.2f   |",q->no,q->at,q->bt,r->at,r->bt,wt,tat);
            
        if(i<proc_count)        
          {
            q=r->next;
            r=q->next;
          }
        else
        q=r->next;  
        ++i;
    }
    printf("\n\n OVERALL DETAILS \n");
    printf("\n Throughput : %.2f",proc_count/tbt);
    printf("\n Average wait time : %.2f",twt/proc_count);
    printf("\n Average turn around time : %.2f",ttat/proc_count);
}

void main()
{
	NODE *head=NULL;
	char ch;
	int i=0,j,k;
	float arr_time1,arr_time2,burst_time1,burst_time2;
    do
    {
	    printf("\n <== Enter process  details ==> ");
        printf("\n Arrival Time : ");
		scanf("%f",&arr_time1);
		printf("\n Burst Time 1 : ");
		scanf("%f",&burst_time1);
		printf("\n Burst Time 2 : ");
		scanf("%f",&burst_time2);
    		arr_time2=1000;
		create_insert(&head,no,arr_time1,burst_time1);
        create_insert(&head,no,arr_time2,burst_time2);
        process=process+2;
        no++;
        printf("Is there any other process (Y/N) ==> ");
        scanf("%d",&i);
        scanf( "%c",&ch);
    }while(ch=='y'|| ch=='Y');    
    
    printf("\n\t ALL PROCESS DETAILS \n");
   // display_sort(head);
    sorting(head);
   // printf("\n------------------------------------\n\n ALL PROCESS SORTED ACCORDING TO ARRIVAL TIME \n");
    //display_sort(head);
    c=calculate(&head);

      // removing duplicate entries
    for(i=0;i<c;++i)
    {
        for(j=i+1;j<c;++j)
        {
            if(idle[i]==idle[j])
            {
                for(k=j;k<c;k++)
                {
                    idle[k]=idle[k+1];
                }   
            j--;
            c--;
            }
        }
    }
gantt_chart(head,process,idle,c);
//display(head);
//printf("\n All process according to ID's");
//sorting_id(head);   // ID based swap 
//display_sort(head); // Display of all process 
display_overall(head);
}
