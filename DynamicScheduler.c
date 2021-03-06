#include<stdio.h>
#include<conio.h>

struct process
{
	int arrivalTime;
	int burstTime;
	int priority;
	char processName[3];
	int averageTime;
	int status; // 0-waiting, 1-running
};

struct queue{
	struct process *p;
	struct queue *next;
}*readyQueue=NULL,*temp,*prev=NULL,*Sequence=NULL;

struct process* createProcess(int userProcess);
void Stimulate(struct process *p,int userProcess,int executionTime);
void CreateSequence(struct process *np);

 main()
{
	int userProcess;
	int i,sum=0;
	struct process *p;
	printf("Enter the number of the process\t");
	scanf("%d",&userProcess);
	p=createProcess(userProcess);
	printf("\nThe Initial condition set are \n");
	for(i=0;i<userProcess;i++)
	{
		printf("\nProcess Name  %s",(p+i)->processName);
		printf("\t with Arrival Time  %d",(p+i)->arrivalTime);
		printf("\tand Burst Time %d",(p+i)->burstTime);
	}
	Stimulate(p,userProcess,0);
	for(i=0;i<userProcess;i++)
	{
		sum+=(p+1)->averageTime;
	}
	printf("Average Waiting Time = %d",(sum/userProcess));
		getch();
	
}

//Function  to input the n process with its arrival time and burst time

struct process* createProcess(int userProcess)
{
	struct process *p;
	int i;
	p=calloc(userProcess,(sizeof(struct process)));
	for(i=0;i<userProcess;i++)
	{
		printf("Enter the process name\t");
		scanf("%s",(p+i)->processName);
		printf("Enter the Arrivl time of the Process\t");
		scanf("%d",&(p+i)->arrivalTime);
		printf("Enter the burst time\t");
		scanf("%d",&(p+i)->burstTime);
		(p+i)->priority=0;
		(p+i)->averageTime=0;
		(p+i)->status=0;
	}
	return p;
}

//Simulation function



void Stimulate(struct process *pr,int userProcess,int executionTime)
{

	struct process *runingProcess=NULL;
	struct queue *ready,*temp2;
	int flagCheck=1,flag=0;
	Sequence=NULL;
	int i;
		while(flagCheck)
		{
			flag=0;
			readyQueue=NULL;
		
			for(i=0;i<userProcess;i++)
			{	
				
				if(((pr+i)->arrivalTime-executionTime)<=0 && (pr+i)->burstTime>0)
				{
					ready=malloc(sizeof(struct queue));
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
							if(ready->p->priority == temp->p->priority)
							{
								if(temp->p->status==1)
								{
									break;
								}
								else
								{
									prev=temp;
									temp=temp->next;
								}
							
								
							 }
							else if( ready->p->priority < temp->p->priority )
							{
							prev=temp;
							temp=temp->next;
							}
							else
							{
								break;
							}
						}
						if(prev==NULL )
						{
							if(( ready->p->priority==temp->p->priority ))
							{
								if(temp->p->status==1)
								{
									
									ready->next=readyQueue;
									readyQueue=ready;
								}else
								{
									temp->next=ready;
								}
							}else if(ready->p->priority<temp->p->priority)
							{
								temp->next=ready;
							}
							else if(ready->p->priority>temp->p->priority)
							{
									ready->next=readyQueue;
									readyQueue=ready;
								
							}
						
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
				}}
					
										
					runingProcess=readyQueue->p;
					CreateSequence(runingProcess);
					readyQueue->p->burstTime-=1;
					readyQueue->p->status=1;
					readyQueue->p->priority+=1;
				    temp=readyQueue;
					while(temp!=NULL)
					{	
						if(temp->p == runingProcess)   //changing here
						{
													
						}
					    else
						{
							temp->p->priority+=2;
							temp->p->status=0;
							temp->p->averageTime+=1;
						}
						temp=temp->next;
					}
											
					for(i=0;i<userProcess;i++)
					{
						if((pr+i)->burstTime!=0)
						{
							flag=1;
							break;
						}
					}
					if(flag==1)
					{
						executionTime++;
					}
					else
					{
						flagCheck=0;
					}
		}
				
	printf("\nThe final status for all the Process are :- \n");
	for(i=0;i<userProcess;i++)
	{
		printf("\nProcess Name  %s",(pr+i)->processName);
	    printf("\t with Arrival Time  %d",(pr+i)->arrivalTime);
		printf("  and Burst Time %d",(pr+i)->burstTime);
	    printf("  and average Waiting Time %d",(pr+i)->averageTime);
		printf("  and priority %d",(pr+i)->priority);
	}	

	
	printf("\nThe Sequnce for Execution is given as \n\t\t");

	temp=Sequence;
	while(temp!=NULL)
	{
		printf("%s  - > ",(temp->p->processName));
		temp=temp->next;
	}
	printf("\nTotal execution Time Require :- %d\n",executionTime+1);

	
}



void CreateSequence(struct process *np)
{
	struct queue *temp,*temp2;
	temp=malloc(sizeof(struct queue));
	temp->p=np;
	temp->next=NULL;
	if(Sequence==NULL)
	{
		Sequence=temp;
	}
	else
	{
		temp2=Sequence;
		while(temp2->next!=NULL)
		{
			temp2=temp2->next;
		}
		temp2->next=temp;
	}
}
