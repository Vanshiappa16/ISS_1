#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef enum acc_type //enum to define account type
{
	savings = 1,
	current
}at;
typedef struct AccountInfo//structure to store a persons information
{
	int no;
	char name[100];
    at type;
	float bal;
}AI;

typedef struct Node// node to move the list to next
{
	AI data;
	struct Node* next;
}Node;
typedef Node* ll;// to connect the nodes
int strt;
//Function to create an account
ll createAccount(ll l, at t,char name[], float balance)
{
	if (l==NULL)
	{
		ll V= (Node*) malloc(sizeof(Node));
		V->data.no=strt;
		V->data.type=t;
		strcpy(V->data.name,name);
		V->data.bal=balance;
		V->next=NULL;
		printf("Account Number:%d \nAccount Holder:%s\nAccount Type:%s\nBalance:%.2f\n\n",
        100, name, (V->data.type == savings) ? "Savings" : "Current", balance);

		return V;
	}
	if(l->next==NULL )
	{
		ll V= (Node*) malloc(sizeof(Node));
		V->data.no=strt;
		V->data.type=t;
		strcpy(V->data.name,name);
		V->data.bal=balance;
		V->next=NULL;
		l->next=V;
		
	}
	//checking if there is an available account number
	else if (strt>l->data.no && strt<(l->next)->data.no)
	{
		ll V= (Node*) malloc(sizeof(Node));
		V->data.no=strt;
		V->data.type=t;
		strcpy(V->data.name,name);
		V->data.bal=balance;
		V->next=NULL;
		V->next=l->next;
		l->next=V;
		
	}
	else
	{
		l->next= createAccount(l->next,t,name,balance);
	
	}
	printf("Account Number:%d \nAccount Holder:%s\nAccount Type:%s\nBalance:%.2f\n\n",
           l->data.no, l->data.name, (l->data.type == savings) ? "Savings" : "Current", l->data.bal);
	return l;

}
int check(ll l,at t,char name[])//acc availiblity check
{
	while(l!=NULL)
	{
		if(l->data.type==t && strcmp(l->data.name,name)==0)
			{
            return 0;
            }
		l=l->next;
	}
	return 1;
}
int check_2(int c, ll l)//smallest no check
{
	while(l!=NULL)
	{
		if(c==l->data.no)
		{
			return 0;
		}
		l=l->next;
	}
	return 1;
}

int small_acc_no(ll l)//gives the least possible acc no.
{
	int c=100;
	while(1)
	{
		if(check_2(c,l)==0)
			
            {c++;}
		else
			return c;	
	}
}
//Function to delete account
ll del(ll l, at t,char nom[50])
{
	if(l==NULL)
	{
		printf("Invalid: User does not exist\n");
		return l;
	}
	if(t==l->data.type && strcmp(nom,l->data.name)==0)
	{
		printf("Account deleted successfully\n");
		ll V=l->next;
		free(l);
		return V;	
	}
	else
	{
		l->next=del(l->next,t,nom);
		return l;
	}
}
ll transaction(ll l, int a, float balance, int operator)
{
	if(a==0)
	{
		if(operator==1)
		{
			l->data.bal=(l->data.bal)+balance;
			printf("Updated balance is Rs %f\n",l->data.bal);
		}

		else if(operator==0&&((l->data.bal)-balance)>=100)
		{
			l->data.bal=(l->data.bal)-balance;
			printf("Updated balance is Rs %f\n",l->data.bal);
		}
		else
		{
			printf("The balance is insufficient for the specified withdrawal\n\n");
		}
		return l;	
	}
	else if(a>0)
	{
		l->next=transaction(l->next,a-1,balance,operator);
		return l;
	}
	else
	{
		printf("Invalid: User does not exist\n");
		return l;
	}
}
int find(int x,ll l)//find acc details with acc number
{
	int c=0;
	while(l!=NULL)
	{
		if(l->data.no==x)
			{return c;}
		c++;
		l=l->next;
	}
	return 0;
}

void lowBalanceAccounts(ll l)//for low balance accounts
{
	while(l!=NULL)
	{
		if(l->data.bal<=100.0)
			printf("Account Number: %d, Name: %s, Balance: %f\n",l->data.no,l->data.name,l->data.bal);
		l=l->next;
	}
}
void display(ll l)//printing 
{
	if(l==NULL)
		printf("No accounts to display\n");
	else
	{
		printf("Account Number\t\tAccount Type\t\tName\t\tBalance\n"
		        "-------------------------------------------------------------------------------------\n");
		while(l!=NULL)
		{
			char d[10];
			if(l->data.type==1)
				{strcpy(d,"savings");}
			else
				{strcpy(d,"current");}
			printf("%d\t\t\t%s\t\t\t%s\t\t%f\n",l->data.no,d,l->data.name,l->data.bal);
			l=l->next;
		}
	}
}
int main()
{
	int ac_num,operator,ind;
	char type[100],task[100];
	char name[100];
	float balance;
	at t;
	ll l=NULL;
	while(1)
	{
		
		printf("1.CREATE AccountType Name Amount\n"
                "2.DELETE AccountType Name\n"
		        "3.TRANSACTION AccountNumber Amount Code\n"
                "4.LOWBALANCE\n"
		        "5.DISPLAY\n"		
                "6.EXIT\n"
		        "Enter choice\n");
		scanf("%s",&task);
		if(strcmp(task,"CREATE")==0)
			{
                scanf("%s %s %f",&type,name,&balance);
					if(strcmp(type,"savings")==0)
						{t=savings;}
					else
						{t=current;}
					strt=small_acc_no(l);
					if(check(l,t,name)==1)
						{l=createAccount(l,t,name,balance);}
					else
						{printf("Invalid: User already exists!\n");}
					
            }
		else if(strcmp(task,"DELETE")==0)
			{
                scanf("%s %s",type,name);
					if(strcmp(type,"savings")==0)
						t=savings;
					else
						t=current;
					l=del(l,t,name);
			
            }
		else if(strcmp(task,"TRANSACTION")==0)
			{
                scanf("%d %f %d",&ac_num,&balance,&operator);
					ind=find(ac_num,l);
					l=transaction(l,ind,balance,operator);
				
            }
		else if(strcmp(task,"LOWBALANCE")==0)
			{
                lowBalanceAccounts(l);
					
            }
		else if(strcmp(task,"DISPLAY")==0)
			{
                display(l);
					printf("\n");
            }
		else if(strcmp(task,"EXIT")==0)
			{
                free(l);
                return 0;
            }
		else
			{
                printf("INVALID CHOICE\n");
            }
		
	}
}