#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void MenuAwal()//function to show menu awal
{
	printf ("*******WELCOME TO BEE BANK!*******\nBEE BANK is a digital bank where you can do your transactions safely.\n");
	int i;
	for (i=0;i<120;i++)//looping for giving divider as long as the string
	{
		printf ("_");
	}
	printf ("\n\nI'm sorry for your inconvinience because the CASH DEPOSIT and CASH WITHDRAWAL option are under maintenance");
	printf ("\n\nPlease choose the remaining option : \n\n");
	printf ("1. Deposit\n");
	printf ("2. Planned Saving\n");
	printf ("3. Done/ cancel transaction\n\n");
	printf ("Enter your option using number only (1/2/3) : ");
}

struct tabungan//struct for tabungan berencana/ planned savings
{
	char savingName[101];
	long long saving2, month2, date, total[1001];
}
savingBgt[1001], temp; //temp for temporary place in bubblesorting

float plannedSaving(int x) //function for returning the correct interest based of the ifs
{
	if (savingBgt[x].saving2 < 1000000)// the first condition if the input is less than 1 million
	{
		if (savingBgt[x].month2 < 12) 
		{
			return 0.01;
		}
		else if (savingBgt[x].month2 >= 12 && savingBgt[x].month2 < 36)//the second condition based on monthly interest requirements
		{
			return 0.01;//to return 0.01 as the interest if the condition match up
		}
		else if (savingBgt[x].month2 >= 36 && savingBgt[x].month2 < 60)
		{
			return 0.012;//to return 0.012 as the interest if the condition match up
		}
		else if (savingBgt[x].month2 >= 60 )
		{
			return 0.015;//to return 0.015 as the interest if the condition match up
		}
	}
	else if (savingBgt[x].saving2 >= 1000000)// the othe first condotion if the input is same or more than 1 million
	{
		if (savingBgt[x].month2 < 12) 
		{
			return 0.01;
		}
		else if (savingBgt[x].month2 >= 12 && savingBgt[x].month2 < 36)//the second condition based on monthly interest requirements
		{
			return 0.012;//to return 0.012 as the interest if the condition match up
		}
		else if (savingBgt[x].month2 >= 36 && savingBgt[x].month2 < 60)
		{
			return 0.015;//to return 0.015 as the interest if the condition match up
		}
		else if (savingBgt[x].month2 >= 60 )
		{
			return 0.017;//to return 0.017 as the interest if the condition match up
		}
	}
}

int main ()
{
	int inputMenu; //declare for input menu variable
	
	do //to do looping and validation while inputing the chosen option
	{
		system("cls"); //to show new blank page
		MenuAwal(); //to call menu awal function and show all the operations
		scanf("%d", &inputMenu);
		
		while (inputMenu < 1 && inputMenu > 3) //input validation for main menu option
		{
			printf("\nSorry, your input must be a number between 1 2 or 3\nPlease input the correct number\n");
			scanf("%d", &inputMenu);
		}
		
		if (inputMenu == 1)//if the user choose 1, then the deposit menu will started
		{
			FILE *deposito = fopen ("DEPOSIT_REPORT.txt", "w");//make a deposit file that we can write 'w'
			fprintf (deposito, "**WELCOME TO BEE BANK!**\nBEE BANK is a digital bank where you can do your transactions safely.\n\n");
			fprintf (deposito, "BEE BANK DEPOSIT MENU\n");//fprintf operation is to print in the file
			fprintf (deposito, "______________________________\n\n");
			
			long long month, totalBunga, x;
			double interest, saving;
			char yaTidak, nama[41];
			x = 1;

			do //looping for when user choose y at the end of the process, all the input process will restarted
			{
				system  ("cls"); //to show blank page
				printf ("*******WELCOME TO BEE BANK!*******\nBEE BANK is a digital bank where you can do your transactions safely.");
				printf ("\n-----------------------------------------------------------------------\n\n");
				printf ("DEPOSIT MENU\n\n");
				
				printf ("ENTER YOUR NAME (IN UPPERCASE) : ");getchar ();
				scanf ("%[^\n]", &nama);
				
				do //input validation so the user did not input 0 or - number
				{
					printf ("\nEnter the desired savings (min 1000000) : Rp. ");
					scanf ("%lf", &saving);
				}
				while (saving<1000000);
			
				do //input validation so the user did not input 0 or - months
				{
					printf ("Enter the desired month to do deposit : ");
					scanf ("%lld", &month);
				}
				while (month<1);
			
				do //vinput validation so the user did not input 0 or - interest
				{
					printf ("Enter the desired interest per month (%%) : ");
					scanf ("%lf", &interest);
				}
				while (interest<1);
				system ("cls");
				
				printf ("\n***BEE BANK***\n");
				printf ("DEPOSIT REPORT OF %s\n", nama);
				printf("__________________________________________\n\n");
				fprintf (deposito, "DEPOSIT %d %s\n\n", x++, nama); //to write in the DEPOSIT_REPORT file
				
				int i;
				for (i=1; i<=month; i++) //count the total deposit
				{
					totalBunga = saving * interest * 80 / 12 / 100 / 100;
					saving += totalBunga; //to add totalBunga to saving
					
					printf("Deposit on the month %d: Rp.%-14.2lf\n", i, saving);//to print in cpp
					
					fprintf (deposito, "Deposit on the month %d: Rp.%-14.2lf\n", i, saving); //to write in DEPOSIT_REPORT file
				}
				
				printf("\nYou can see the Deposit Report on the DEPOSIT_REPORT.txt\n\n");
    			printf("Do you want to do another deposit? (y/n): ");
    			
				scanf("%s",&yaTidak);//to scan y or n, y = yes, n = no
				printf ("\n");
    			system("cls"); 
    			
    			fprintf (deposito, "\n*******THANK YOU FOR YOUR TRANSACTIONS!*******\n\n");//closing in DEPOSITO_REPORT file
			}	
			while (yaTidak == 'y');//if the user input y, all the deposit process will restarted. y = yes, n = no
			fclose(deposito);//to close DEPOSITO_REPORT file. if u dont close it, the next input will be not shown
		}
		
		
		else if (inputMenu == 2)//if the user choose option 2, the planned saving procedure will start
		{
			FILE *tabunganBerencana = fopen ("PLANNED_SAVING.txt", "w"); //make the PLANNED_SAVING file
			fprintf (tabunganBerencana, "****WELCOME TO BEE BANK!****\nBEE BANK is a digital bank where you can do your transactions safely.\n\n");
			fprintf (tabunganBerencana, "PLANNED SAVINGS REPORT OF \n");
			fprintf (tabunganBerencana, "------------------------------\n\n");
			
			
			int x=0, tabunganSementara, i;
			char yaTidak;
	
			do
			{
				system ("cls");
				printf ("*******Welcome to BEE BANK!*******\nBEE BANK is a digital bank where you can do your transactions safely.");
				printf ("\n-----------------------------------------------------------------------\n\n");
				printf ("PLANNED SAVING MENU\n\n");
				printf ("INPUT YOUR NAME (IN UPPERCASE) : "); getchar();
				scanf ("%[^\n]s", &savingBgt[x].savingName); 
				
				do //input validation so the user did not input 0 or - number
				{
					printf ("\nEnter the desired savings per month : Rp. ");
					scanf ("%lld", &savingBgt[x].saving2); 
				}
				while (savingBgt[x].saving2<1);
			
				do //input validation so the user did not input less than 12 more than 120 months
				{
					printf ("Enter the desired month to do saving  : ");
					scanf ("%lld", &savingBgt[x].month2);
				}
				while (savingBgt[x].month2<1 || savingBgt[x].month2>120);
			
				do //input validation so the user did not input less than 1 or more than 31 dates
				{
					printf ("Enter the autodebet date (1 - 31): ");
					scanf ("%lld", &savingBgt[x].date);
				}
				while (savingBgt[x].date<1 || savingBgt[x].date>31);
				
				savingBgt[x].saving2 = savingBgt[x].saving2 + (savingBgt[x].saving2 * plannedSaving(x)); //counting the saving + interest. also calling the interest function
				tabunganSementara = savingBgt[x].saving2; //tabunganSementara is a temporary place to hold the calculation
				
				system ("cls");
				printf ("\n***BEE BANK***\n");
				printf ("%s PLANNED SAVING REPORT\n", savingBgt[x].savingName);
				printf("__________________________________________\n\n");
				printf ("Autodebet date %d\n\n", savingBgt[x].date);
				
				int i;
				for (i=1;i<=savingBgt[x].month2;i++)//loop for printing the months, and the amount of savings per month
				{
					printf ("Saving in month %d : Rp. %lld\n", i, savingBgt[x].saving2);
					savingBgt[x].total[i-1] = savingBgt[x].saving2;
					savingBgt[x].saving2 += tabunganSementara; //after being temporary held in tabunganSementara, the saving can be add up
				}
				printf("\nYou can see the Planned Saving Report on the PLANNED_SAVING.txt\n\n");
    			printf("Do you want to do another planned saving? (y/n): ");
    			
				scanf("%s",&yaTidak);
				printf ("\n");
    			x++;//will increment and affect the sorting date and print the amount of savings that have been sorted in the PLANNED_SAVING file
    			
			}
			while (yaTidak == 'y');// if the user input y, then all the planned saving procedures will restarted. y = yes, n = no
			
			int a;
			for (a=0;a<x;a++)// to bubblesort the planned saving by the date 
			{
				int j;
				for (j=x-1;j>a;j--)
				{
					if (savingBgt[j].date < savingBgt[j-1].date)//ascending
					{
						temp = savingBgt[j];//swaping moment
						savingBgt[j] = savingBgt[j-1];
						savingBgt[j-1] = temp;
					}
				}
			}
			int b;
			for (b=0; b<x; b++)//looping for printing the name, autodebet date, and conditioning the month and saving amount that will be sorted
			{
				fprintf (tabunganBerencana, "%s\n", savingBgt[b].savingName);
				fprintf(tabunganBerencana, "Autodebet date for planned saving: %lld\n", savingBgt[b].date);
				fprintf(tabunganBerencana, "------------------------------\n\n");
				int j;
				for (j=1; j<=savingBgt[b].month2; j++)//print the month and the saving per month, after being sorted (ascending)
				{
					fprintf(tabunganBerencana, "Savings in month %d: Rp. %lld\n", j, savingBgt[b].total[j-1]);	
				}
				fprintf(tabunganBerencana, "\n");//give enter after every print package
			}
			fprintf (tabunganBerencana, "*******THANK YOU FOR YOUR TRANSACTIONS!*******\n");//clpsing for PLANNED_SAVING file
			fclose(tabunganBerencana);//to close the PLANNED_SAVING file
		}	
	}
	while (inputMenu != 3); //input validation, if the user choose option 3, then it will display THANK YOU FOR YOUR TRANSACTIONS! and the programme will be done and return to 0
	printf ("\n\nTHANK YOU FOR YOUR TRANSACTIONS!\n");
	return 0;//end of programme
}
