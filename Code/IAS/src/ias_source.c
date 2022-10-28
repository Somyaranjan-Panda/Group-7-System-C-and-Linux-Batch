/******************************************************************************************************************************
 ** FILE NAME   : ias_source.c

 ** DESCRIPTION : This file contains the source functions and perform the operations which is
 calling by the main program.
 **

 ** REVISION HISTORY:

 **     DATE                  NAME                      REVISION
 ------------------------------------------------------------------
 **                            1. Somyaranjan Panda
 **                            2. Shemona Roseny
 **     25-10-22               3. Sobika k
 **                            4. Sowmya Harika Tummuri
                               5. Sumera Tasleem    
 **
 *********************************************************************************************************************************
 */

#include<stdio.h>
#include<time.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<header.h>
#include<assert.h>
#define INITIAL 0
#define SIZE 30
#define MINSIZE 10
#define MAXSIZE 1024
struct inventory
{
	int product_id;
	char product_name[SIZE];
	char description[SIZE];
	int quantity;
};
struct sales
{
	int transaction_id;
	int quantity;
	int product_id;
};
/***********************************************************************************************************************************************
 ** FUNCTION NAME    : product_verification

 ** DESCRIPTION      : This function verifies the product id and quantity which is in correct format.

 ** RETURN           : If product id and quantity is verified successfully, it returns 1 otherwise it returns 0.

 *************************************************************************************************************************************************
 */
int product_verification(int product_id,int quantity)
{
	char *product;
	product = (char*)calloc(MINSIZE,sizeof(char));
	sprintf(product,"%d",product_id);
	if((strlen(product)>4 || strlen(product)<4) || (quantity<0))
	{
		printf("\nPlease Enter The Details In Correct Format\n");
		free(product);
		return 0;
	}

	else
	{
		free(product);
		return 1;
	}

}
/**********************************************************************************************************************************************
 ** FUNCTION NAME    : verification

 ** DESCRIPTION      : This function verifies the user login id and password..

 ** RETURN           : If login id and password is verified successfully, it returns 1 otherwise it returns 0.

 ***********************************************************************************************************************************************
 */
int verification(char *id,int pass)
{
	char *log_id;
	log_id=(char*)calloc(MINSIZE,sizeof(char));
	int log_pass=INITIAL;
	int cmp = INITIAL;
	printf("Enter id : ");
	(void)scanf("%s",log_id);
	printf("Enter password : ");
	(void)scanf("%d",&log_pass);
        cmp=strcmp(id,log_id);

	if ((cmp==0) && log_pass==pass)
	{
		printf("\nyou have successfully logged in\n");
		free(log_id);
		return 1;
	}
	else
	{
		printf("\nplease enter correct login id and password\n");
		free(log_id);
		return 0;
	}
}
/***********************************************************************************************************************************************
 ** FUNCTION NAME    : display_inventory

 ** DESCRIPTION      : This function displays the product information in inventorylog.

 **RETURN            : void.

 *************************************************************************************************************************************************
 */


void display_inventory()
{
	FILE *filepointer = NULL;
	char file_content;
	filepointer = fopen("inventorylog.csv","r");
	if(filepointer == NULL)
	{
		
		printf("\nFile Cannot Be Opened\n");
	}
	else
	{
		
		printf("\nThe Product Details Are\n");
		printf("\npr_id   pr_name desc  quan \n");
		while(!feof(filepointer))
		{
			file_content = fgetc(filepointer);
			printf("%c",file_content);

		}
		(void)fclose(filepointer);

	}
}

/*************************************************************************************************************************************************
 ** FUNCTION NAME    : create_inventory

 ** DESCRIPTION      : This function creates a log of products and write into a file.

 ** RETURN           : void   

 **************************************************************************************************************************************************
 */

void create_inventory()
{
	char ch='y';
	FILE *filepointer = NULL;
	struct inventory log;
	int var=INITIAL;
	filepointer = fopen("inventorylog.csv","a");
	if(filepointer == NULL)
	{
		printf("\nFile Cannot Be Opened\n");
	}
	else
	{
		while(ch == 'y')
		{
			printf("\nEnter The Details\n");
			printf(" Product id : ");
			(void)scanf("%d",&log.product_id);
			printf(" Product name : ");
			(void)scanf(" %[^\n]s",log.product_name);
			printf(" Description : ");
			(void)scanf(" %[^\n]s",log.description);
			printf(" Quantity : ");
			(void)scanf(" %d",&log.quantity);
			var=product_verification(log.product_id,log.quantity);
			if(var==1)
			{
				fprintf(filepointer,"%d,\t%s,\t%s,\t%d\n",log.product_id,log.product_name,log.description,log.quantity);
			}


			printf("\nDo You Want To Add More Products[y/n] : ");
			scanf(" %c",&ch);
		}
	}
	(void)fclose(filepointer);

}
/*********************************************************************************************************************************************
 ** FUNCTION NAME    : create_sales

 ** DESCRIPTION      : This function creates a log of sales and write into a file.

 ** RETURN           : void

 ************************************************************************************************************************************************
 */

void create_sales()
{
	char ch='y';
	FILE *filepointer = NULL;
	int var = INITIAL;
	bool check = INITIAL;
	struct sales slog;
	time_t ltime = time(NULL);
	struct tm *tm = localtime(&ltime);

	filepointer = fopen("saleslog.csv","a");
	if(filepointer == NULL)
	{
		printf("\nFile Cannot Be Opened\n");
	}
	else
	{
		while(ch == 'y')
		{
			printf("\nEnter The Details\n");
			printf(" Transaction id : ");
			(void)scanf("%d",&slog.transaction_id);
			printf(" Product id : ");
		        (void)scanf(" %d",&slog.product_id);
			printf(" Quantity : ");
			(void)scanf(" %d",&slog.quantity);
			var=product_verification(slog.transaction_id,slog.quantity);
			if(var==1)
			{
			        check = sale_inventory(slog.product_id,slog.quantity);
				if(check == 1)
				{
					fprintf(filepointer,"%d,\t%d,\t%d,\t%s\n",slog.transaction_id,slog.product_id,slog.quantity,asctime(tm));
				}

				else
				{

					printf("\nProduct Id Is Not Found/ Low Quantity Detected\n");
				}

			}

			printf("\nDo You Want To Add More Products[y/n] : ");
			(void)scanf(" %c",&ch);
		}
	}

	(void)fclose(filepointer);
}
/*********************************************************************************************************************************************
 ** FUNCTION NAME    : display_sales

** DESCRIPTION      : This function displays the product information in saleslog.

** RETURN           : void

 **********************************************************************************************************************************************
 */



void display_sales()
{
	FILE *filepointer = NULL;
	char file_content;
	filepointer = fopen("saleslog.csv","r");

	if(filepointer == NULL)
	{
		printf("\nFile Cannot Be Opened\n");
	}
	else
	{
		printf("\nThe Product Details Are\n");
		printf("\ntr_id   pro_id quan          date_time_year\n");
		while(!feof(filepointer))
		{
			file_content = fgetc(filepointer);
			printf("%c",file_content);

		}
		(void)fclose(filepointer);
	}

}
/*********************************************************************************************************************************************
 ** FUNCTION NAME    : delete_inventoty

 ** DESCRIPTION      : This function delete the information of given product id in inventorylog.

 ** RETURN           : void

 *********************************************************************************************************************************************
 */


void delete_inventory()
{
	FILE *filepointer1= NULL;
	FILE *filepointer2 = NULL;
	struct inventory log;
	int product_id = INITIAL;
	char *token;
	char *buffer;
	char ch ='y';
	int flag=INITIAL;
	int var = INITIAL;
	buffer =(char*)calloc(MAXSIZE,sizeof(char));

	while(ch == 'y')
	{
		printf("\nEnter The Product Id To Delete : ");
		(void)scanf("%d",&product_id);
		var=product_verification(product_id,1);
		if(var == 1)
		{

			filepointer1 = fopen("inventorylog.csv","r");
			if(filepointer1 == NULL)
			{
				printf("\nFile Cannot Be Opened\n");
				exit(0);
			}
			filepointer2 = fopen("temperorylog.csv","a");
			if(filepointer2 == NULL)
			{
				printf("File Cannot Be Opened\n");
				exit(0);
			}
			while(fgets(buffer,1024,filepointer1)!=NULL)
			{
				token = strtok(buffer,",");
				while(token != NULL)
				{
					if(atoi(token) == product_id)
					{
						flag=1;
						log.product_id = atoi(token);
						token=strtok(NULL,",");
						strcpy(log.product_name,token);
						token = strtok(NULL,",");
						strcpy(log.description, token);
						token = strtok(NULL,"\n");
						log.quantity=atoi(token);
						token = strtok(NULL,",");



					}
					else 
					{

						log.product_id = atoi(token);
						token=strtok(NULL,",");
						strcpy(log.product_name,token);
						token = strtok(NULL,",");
						strcpy(log.description, token);
						token = strtok(NULL,"\n");
						log.quantity=atoi(token);
						token = strtok(NULL,",");
						fprintf(filepointer2,"%d,%s,%s,\t%d\n",log.product_id,log.product_name,log.description,log.quantity);
					}
				}
			}
			



			if(flag==0)
			{
				printf("Sorry Product Id Is Not Found\n");
			}
			else
			{
				printf("\nProduct Deleted Successfully\n");
			}

			flag=0;
			printf("\nDo You Want To Delete More Products[y/n] : ");
			(void)scanf(" %c",&ch);


			(void)fclose(filepointer1);
			(void)fclose(filepointer2);
			(void)remove("inventorylog.csv");
			(void)rename("temperorylog.csv","inventorylog.csv");
		}

	}

	free(buffer);

}
/***********************************************************************************************************************************************
 ** FUNCTION NAME    : update_inventory

 ** DESCRIPTION      : This function update the information of given product id in inventorylog.
 
 ** RETURN           : void.
 *************************************************************************************************************************************************
 */

void update_inventory()
{


	FILE *filepointer1= NULL;
	FILE *filepointer2 = NULL;
	struct inventory log;
	struct inventory newlog;
	int product_id = INITIAL;
	char *token;
	char ch ='y';
	int flag=0;
	int var =INITIAL;
	char *buffer;
	buffer =(char*)calloc(MAXSIZE,sizeof(char));
	token = strtok(buffer,",");

	while(ch == 'y')
	{
		printf("\nEnter The Product Id To Update : ");
		scanf("%d",&product_id);
		var=product_verification(product_id,1);
		if(var==1)
		{
			filepointer1 = fopen("inventorylog.csv","r");
			if(filepointer1 == NULL)
			{
				printf("File Cannot Be Opened\n");
				exit(0);
			}
			filepointer2 = fopen("temperorylog.csv","a");
			if(filepointer2 == NULL)
			{
				printf("File Cannot Be Opened\n");
				exit(0);
			}
			while(fgets(buffer,1024,filepointer1)!=NULL)
			{
				token = strtok(buffer,",");
				while(token != NULL)
				{
					if(atoi(token) == product_id)
					{


						flag=1;
						printf("Enter The Details\n");
						printf("product name : ");
						(void)scanf("%s",newlog.product_name);
						printf("description : ");
						(void)scanf(" %[^\n]s",newlog.description);
						printf("quantity : ");
						(void)scanf(" %d",&newlog.quantity);

						newlog.product_id = atoi(token);
						token=strtok(NULL,",");
						strcpy(log.product_name,newlog.product_name);
						token = strtok(NULL,",");
						strcpy(log.description,newlog.description);
						token = strtok(NULL,"\n");
						log.quantity=newlog.quantity;
						token = strtok(NULL,",");
						fprintf(filepointer2,"%d,\t%s,\t%s,\t%d\n",newlog.product_id,log.product_name,log.description,log.quantity);


					}
					else 
					{

						log.product_id = atoi(token);
						token=strtok(NULL,",");
						strcpy(log.product_name,token);
						token = strtok(NULL,",");
						strcpy(log.description, token);
						token = strtok(NULL,"\n");
						log.quantity=atoi(token);
						token = strtok(NULL,",");
						fprintf(filepointer2,"%d,%s,%s,\t%d\n",log.product_id,log.product_name,log.description,log.quantity);
					}
				}


			}
			
			if(flag==0)
			{
				printf("\nSorry Product Id Is Not Found\n");
			}
			else
			{
				printf("\nProduct Updated Successfully\n");
			}
			flag=0;
			printf("\nDo You Want To Update More Products[y/n] : ");
		        scanf(" %c",&ch);


			(void)fclose(filepointer1);
			(void)fclose(filepointer2);
			(void)remove("inventorylog.csv");
			(void)rename("temperorylog.csv","inventorylog.csv");
		
		}
		
	

	}
	free(buffer);
}
/****************************************************************************************************************************
 **   FUNCTION NAME : sale_inventory 

 **   DESCRIPTION   : This function update the quantity of products in inventory log.

 **   RETURN        : If product id and enough quantity is present it returns 1 otherwisw 0.
 **********************************************************************************************************************************
 */
int sale_inventory(int product_id,int quantity)
{

	FILE *filepointer1= NULL;
	FILE *filepointer2 = NULL;
	struct inventory log;
	char *token;
	char *buffer;
	int flag=INITIAL;
	int var =INITIAL;
        int id_present=INITIAL;
	buffer=(char*)calloc(MAXSIZE,sizeof(char));

	var=product_verification(product_id,quantity);
	
	if(var==1)
	{
		filepointer1 = fopen("inventorylog.csv","r");
		if(filepointer1 == NULL)
		{
			printf("File Cannot Be Opened\n");
			exit(0);
		}
		filepointer2 = fopen("temperorylog.csv","a");
		if(filepointer2 == NULL)
		{
			printf("File Cannot Be Opened\n");
			exit(0);
		}
		while(fgets(buffer,MAXSIZE,filepointer1)!=NULL)
		{
			token = strtok(buffer,",");
			while(token != NULL)
			{
				if(atoi(token) == product_id)
				{
					id_present=1;
					log.product_id = atoi(token);
					token=strtok(NULL,",");
					strcpy(log.product_name,token);
					token = strtok(NULL,",");
					strcpy(log.description,token);
					token = strtok(NULL,"\n");
					log.quantity=atoi(token);
					token = strtok(NULL,",");

					if(log.quantity>=quantity){
					fprintf(filepointer2,"%d,%s,%s,\t%d\n",log.product_id,log.product_name,log.description,log.quantity-quantity);
						flag=1;
					}
					if(log.quantity<quantity)
					{
						flag=0;
						fprintf(filepointer2,"%d,%s,%s,\t%d\n",log.product_id,log.product_name,log.description,log.quantity);
					}
				}

				else
				{

					log.product_id = atoi(token);
					token=strtok(NULL,",");
					strcpy(log.product_name,token);
					token = strtok(NULL,",");
					strcpy(log.description, token);
					token = strtok(NULL,"\n");
					log.quantity=atoi(token);
					token = strtok(NULL,",");
					fprintf(filepointer2,"%d,%s,%s,\t%d\n",log.product_id,log.product_name,log.description,log.quantity);
				}
			}


		}



		(void)fclose(filepointer1);
		(void)fclose(filepointer2);
		(void)remove("inventorylog.csv");
		(void)rename("temperorylog.csv","inventorylog.csv");
	}
	

	free(buffer);

	return(id_present && flag);

}





