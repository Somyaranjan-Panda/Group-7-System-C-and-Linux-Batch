/***************************************************************************************************
 
** FILE NAME   : ias_main.c
 
** DESCRIPTION : This file maintains the inventorylog and saleslog by calling the functions based on user's choice. 
    
 
** REVISION HISTORY:
 
**     DATE                  NAME                      REVISION
---------------------  ---------------------------------------------
**                       1. Somyaranjan Panda
                         2. Shemona Roseny
**     25-10-2022        3. Sobika K
                         4. Sowmya Harika Tummuri
**                       5. Sumera Tasleem
 
********************************************************************************************************
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<header.h>
#define INITIAL 0
#define SIZE 10

int main()
{

	int user_choice = INITIAL;
	int manager_choice = INITIAL;
	char manager_user_id[SIZE] = "manager";
	int manager_password = 1234;
	char executive_user_id[SIZE] = "executive";
	int executive_password = 5678;
	int ver = INITIAL;
	int manager_operation = INITIAL;
	int executive_operation = INITIAL;
	char ch='y';
	printf("\nAre You A Manager Or Sales Executive\n  1-Manager\n  2-Sales Executive\n");
	printf("\nEnter Your Choice\n");
	(void)scanf("%d",&user_choice);


	if(user_choice==1)

	{
	 printf("\nEnter the login id and password\n");
		do{
			
			ver=verification(manager_user_id,manager_password);

		}while (ver==0);
		printf("\nChoose The Operation To Do\n");
		printf("\n 1 - Inventory\n 2 - Sales\n");
		(void)scanf("%d",&manager_choice);
		if(manager_choice == 1)
		{
			while(ch=='y')
			{
			printf("\n 1 - Create Inventory\n 2 - Display Inventory\n 3 - Update Inventory\n 4 - Delete Inventory\n");
			(void)scanf("%d",&manager_operation);
			if(manager_operation == 1)
			{
				create_inventory();
			}
			else if(manager_operation == 2)
			{
				display_inventory();
			}
			else if(manager_operation == 3)
			{
				update_inventory();
			}
			else if(manager_operation == 4)
			{
				delete_inventory();
			}
			else
			{
				printf("\nChoose The Correct Option\n");
			}
			printf("\nDo You Want To Continue With Other Operation [y/n] : ");
			(void)scanf(" %c",&ch);
			}
		}
		else if(manager_choice == 2)
		{
			while(ch=='y')
			{
			printf("\n 1 - Create Sales\n 2 - Display Sales\n");
			(void)scanf("%d",&manager_operation);
			if(manager_operation == 1)
			{
				create_sales();
			}
			else if(manager_operation ==2)
			{

               			display_sales();
			}
			else
			{
				printf("\nChoose The Correct Option\n");
			}
			printf("\nDo You Want To Continue With Other Operation [y/n] : ");
			(void)scanf(" %c",&ch);
			}
		}
		else
		{
			printf("\nChoose The Correct Option\n");
		}
	}


	else if(user_choice==2)
	
	{
		 printf("\nEnter the login id and password\n");

		do{
			ver=verification(executive_user_id,executive_password);
		}while (ver==0);

		while(ch == 'y')
		{
		printf("\n 1 - Create Sales\n 2 - Display Sales\n");
		(void)scanf("%d",&executive_operation);
		if(executive_operation == 1)
		{
			create_sales();
		}
		else if(executive_operation == 2)
		{
			display_sales();
		}
		else
		{
			printf("\nChoose The Correct Option\n");
		}
		printf("\nDo You Want To Continue With Other Operation [y/n] : ");
		(void)scanf(" %c",&ch);
		}
	}

	else
	{
		printf("\nplease choose the correct choice\n");

	}
	return 0;
}




