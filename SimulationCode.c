#include<stdio.h>
#include<conio.h>

struct process
{
	int arrivalTime;
	int burstTime;
	int priority;
	char processName[3];
	int averageTime;
	int status;// 0-waiting, 1-running
};

struct queue{
	struct process *p;
	struct Queue *next;
}*readyQueue=NULL,*temp,*prev=NULL;

struct process* createProcess(int userProcess);
void Stimulate(struct process *p,int userProcess,int executionTime);


void main()
{
	int userProcess;
	int i;
	struct process *p;
	printf("Enter the number of the process");
	scanf("%d",&userProcess);
	p=createProcess(userProcess);
	for(i=0;i<userProcess;i++)
	{
		printf("\nProcess Name  %s",(p+i)->processName);
		printf("\t with Arrival Time  %d",(p+i)->arrivalTime);
		printf("\tand Burst Time %d",(p+i)->burstTime);
	}
	Stimulate(p,userProcess,0);
	getch();
	
}

//Function  to input the n process with its arrival time and burst time

struct process* createProcess(int userProcess)
{
	struct process *p;
	int i;
	p=calloc(userProcess,sizeof(struct process));
	for(i=0;i<userProcess;i++)
	{
		printf("Enter the process name\t");
		scanf("%s",(p+i)->processName);
		printf("Enter the Arrivl time of the Process");
		scanf("%d",&(p+i)->arrivalTime);
		printf("Enter the burst time");
		scanf("%d",&(p+i)->burstTime);
		(p+i)->priority=0;
		(p+i)->averageTime=0;
	}
	return p;
}

//Simulation function



void Stimulate(struct process *pr,int userProcess,int executionTime)
{
	
	struct process *runingProcess;
	struct queue *ready;
	
	int i;

		for(i=0;i<userProcess;i++)
		{
			if(((pr+i)->arrivalTime-executionTime)==0)
			{
				ready=malloc(ready);
				ready->p = (pr+i);
				ready->next=NULL;
				if(readyQueue==NULL)
				{
					readyQueue=ready;
							
				}
				else
				{	
					
					temp=readyQueue;
					while(temp->next!=NULL )
					{
						
						if( ready->p->priority <= temp->p->priority )
						{
						prev=temp;
						temp=temp->next;
						}
						else
						{
							break;
						}
					}
					if(prev==NULL  && ( ready->p->priority>temp->p->priority ))
					{
						ready->next=readyQueue;
						readyQueue=ready;
					} else 
					if(temp->next==NULL)
					{
						if( ready->p->priority <= temp->p->priority )
						temp->next=ready;
					}
					else
					{
						ready->next=temp;
						prev->next=ready;
					}
					
				}
			}
			executionTime++;
		}

	temp=readyQueue;
	while(temp!=NULL)
	{
		printf("%s",(temp->p->processName));
		temp=temp->next;
	}

	
}
