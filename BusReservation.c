#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#pragma comment(lib, "WinMM.lib")

time_t currentTime;

// creating node for Bus
struct nodeBus
{
    int busNo, price, totalSeats, availableSeats;
    char source[100], destination[100], date[100], driver[100], time[100];
    int seats[100];

    struct nodeBus *next;
} * head1;
// creating node for User Data
struct userNode
{
    int ticketID, age, busNo, seatNo[5], noOfSeats, price;
    char name[100], bookTime[100];
    char start[100], destination[100], date[100], time[100], phoneNo[100];
    double discount;
    struct userNode *next;
} * head2;

// initializing Reg Number of Bus
int regNum = 1021;

// Function Declaration for Upper Case and Lower Case
void UpperCase(char str[]);

// Function Declaration for Admin Menu
void login();
void createBus();
void removeBus();
void calculateProfit();
void calculateEmployeeSalaries();
void admin_menu();
void DisplayAllPassengers();
void updateBus();

// Function Declaration for User to select and Register Bus
void selectBus(int busCount, char destination[20], char source[20]);
void ticketRegistration();
void cancelTicket();
void confirmTicket(struct nodeBus *BUS, int busNo, char destination[20], char source[20]);
double promoCrode(char promoCode[20]);

// Function Declaration for Printing All Type of Data
void printBusses(struct nodeBus *ptr);
void printTickets(struct userNode *ticket);
void DisplayAllBusses();
void searchBus();

void first();

void cyan()
{
    printf("\033[0;36m");
}
void purple()
{
    printf("\033[0;35m");
}
void red()
{
    printf("\033[1;31m");
}

void yellow()
{
    printf("\033[1;33m");
}

void green()
{
    printf("\033[0;32m");
}

void blue()
{
    printf("\033[0;34m");
}
void reset()
{
    printf("\033[0m");
}

void first()
{

    int i, j;

    blue();
    printf("\n\n\n\t\t\t \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb WELCOME TO THE BUS MANAGEMEDNT SYSTEM \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
    green();
    printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t LOADING...\n");
    printf("\t\t\t");
    for (i = 1; i <= 75; i++)
    {
        for (j = 1; j <= 7500000; j++)
            ;
        printf("%c", 177);
    }

    system("cls");
}

// File Data Retreive
void recoverDataFromFile()
{
    FILE *file;
    file = fopen("BusData.csv", "r"); // reading data
    if (!file)
    {
        printf("File Not Found");
        return;
    }
    else
    {
        char buffer[1024];
        while (fgets(buffer, 1024, file))
        {
            struct nodeBus *p;
            p = (struct nodeBus *)malloc(sizeof(struct nodeBus));

            char *value = strtok(buffer, ",");

            while (value)
            {
                printf("hello");
                p->busNo = atoi(value);
                value = strtok(buffer, ",");
                fflush(stdin);
                strcpy(p->driver, value);
                value = strtok(buffer, ",");

                strcpy(p->source, value);
                value = strtok(buffer, ",");

                strcpy(p->destination, value);
                value = strtok(buffer, ",");

                strcpy(p->date, value);
                value = strtok(buffer, ",");

                strcpy(p->time, value);
                value = strtok(buffer, ",");

                p->totalSeats = atoi(value);
                value = strtok(buffer, ",");

                p->price = atoi(value);
                value = strtok(buffer, ",");
                for (int i = 0; i < p->totalSeats; i++)
                {
                    p->seats[i] = i + 1;
                }
                break;
            }

            if (head1 == NULL)
            {
                head1 = p;
            }
            else
            {
                struct nodeBus *q = head1;
                while (q->next != NULL)
                {
                    q = q->next;
                }
                q->next = p;
            }
            break;
        }
    }
    fclose(file);
}

/*==========================================================================================================*/
/*-------------------------------------------Main Menu------------------------------------------------------*/
/*==========================================================================================================*/

int main()
{

    first();
    //	recoverDataFromFile();
    printf("\n\t\t\t\t\t*********************************");
    printf("\n\t\t\t\t\t|\tDSA PROJECT\t\t|");
    printf("\n\t\t\t\t\t|  Haris Ahsan And Ameer Moavia\t|");
    printf("\n\t\t\t\t\t*********************************");

    printf("\n");
    printf("\n\t\t\t*********************************************************");
    printf("\n\t\t\t---WELCOME TO THE BUS RESERVATION MANAGEMENT SYSTEM---");
    printf("\n\t\t\t*********************************************************\n");
    Sleep(500);
    printf("\n\t\t\t--------------Press Any Key to Continue---------------");
    getch();
    system("cls");

    FILE *file;
    file = fopen("TicketData.csv", "w"); // 'a' Append the Data and 'w' overwrite the Data
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "ID", "NAME", "AGE", "PHONE NUMBER", "BUS NUMBER", "TIME", "DATE", "NUMBER OF SEATS", "PRICE", "DEPARTRE", "DESTINATION");
    fclose(file);

    FILE *file1;
    file1 = fopen("BusData.csv", "w"); // 'a' Append the Data and 'w' overwrite the Data
    fprintf(file1, "%s,%s,%s,%s,%s,%s,%s,%s\n", "BUS NO", "DRIVER", "DEPARTURE", "DESTINATION", "DATE", "TIME", "SEATS", "PRICE");
    fclose(file1);

    FILE *file2;
    file2 = fopen("EmployeeSalary.csv", "w"); // 'a' Append the Data and 'w' overwrite the Data
    fprintf(file2, "%s,%s,%s\n", "EMPLOYEE TYPE", "DISTANCE", "SALARY");
    fclose(file2);
    FILE *file3;
    file3 = fopen("IncomeStatement.csv", "w"); // 'a' Append the Data and 'w' overwrite the Data
    fprintf(file3, "%s,%s,%s,%s,%s,%s,%s\n", "EXPENSE ", "AMOUNT", "REVENUE", "AMOUNT", "TOTAL EXPENSE", "TOTAL REVENUE", "PROFIT");
    fclose(file3);
    system("cls");

    int choice = 0, choose, y, z;

    while (choose != 3)
    {

        printf("\n\t\t\t\t\t***********************************************\n");
        printf("\n");
        printf("\t\t\t\t\t|\tPress 1 For Admin Panel\t\t|\n\t\t\t\t\t|\tPress 2 For Customer Panel\t|\n\t\t\t\t\t|\tPress 3 For Exit\t\t|\n");
        printf("\nEnter your choice:	");
        scanf("%d", &choose);
        printf("\n\t\t\t\t\t***********************************************\n");
        printf("\n");
        int exit = 0;
        system("cls");

        switch (choose)
        {
        case 1:
            blue();
            login();
            reset();
            break;
        case 2:

            while (exit == 0)
            {
                cyan();
                printf("\n");
                printf("\n\t\t\t*********************************************************");
                printf("\n\t\t\t--------------WELCOME TO THE *User Menu*---------------");
                printf("\n\t\t\t*********************************************************\n");

                printf("\n\t\t\t\t\t|\t1 To REGISTER TICKET\t\t|\n\t\t\t\t\t|\t2 To CANCEL TICKET\t\t|\n"
                       "\t\t\t\t\t|\t3 View AVAIBLE BUSES\t\t|\n\t\t\t\t\t|\t4 EXIT\t|");
                printf("\n");
                printf("\t\t===========================");
                printf("\n\t\tEnter Choice :: ");
                scanf("%d", &y);
                printf("\n\t\t=========================\n");
                system("cls");
                switch (y)
                {
                case 1:
                    blue();
                    ticketRegistration();
                    printf("\n\t\t\t\t--------------Press Any Key to Continue---------------");
                    getch();
                    system("cls");
                    reset();
                    break;
                case 2:
                    yellow();
                    cancelTicket();
                    reset();
                    break;
                case 3:
                    cyan();
                    DisplayAllBusses();
                    reset();
                    break;
                case 4:
                    exit = 1;
                    break;

                default:
                    printf("\nInvalid Input");
                    break;
                }
            }

            break;
        case 3:

            break;

        default:
            printf("Invalid Input");
            break;
        }
    }

    return 0;
}

/*-----------------------------------------------END MAIN MENU---------------------------------------------*/

/*------------------------------------------UPPER CASE AND LOWER CASE CONVERSION----------------------------*/

/*
Funtion For Upper Case And Lower Case
*/
void UpperCase(char str[])
{
    int n = strlen(str);
    for (int i = 0; i < n; ++i) // For loop Starts To readThe Character One BY One
    {
        if (str[i] >= 'a' && str[i] <= 'z') // This If Blocks Runs when character or Letter is of Small Case
        {
            str[i] = str[i] - ' '; // Converting Lower Case Letter To Upper Case By Subtracting Its ASCII Value By ' '(Space=32)
        }
    }
}

/*==========================================================================================================*/
/*-------------------------------------------ADMIN PANEL----------------------------------------------------*/
/*==========================================================================================================*/
/*
--Admin Menu--
Function to *LOGIN AS ADMIN*
*/
void login()
{

    char pass[90];
    char name[90];
    printf("\n");
    printf("\n\t\t\t*********************************************************");
    printf("\n\t\t\t--------------WELCOME TO THE Admin Panel-----------------");
    printf("\n\t\t\t*********************************************************\n");
    printf("\t\t=========================\n");
    printf("\t\tEnter username::	");
    scanf("%s", name);

    printf("\n\t\tEnter Password::	");
    scanf("%s", pass);
    printf("\n\t\t=========================\n");
    printf("\n\t\t\t\t\t***********************************************\n");
    system("cls");
    if ((strcmp(name, "1") == 0) && (strcmp(pass, "1") == 0))
    {
        admin_menu();
    }
    else
    {
        printf("Invalid Password,Please Try Again");
    }
}

/*
--Admin Menu--
Function to *Admin Menu*
*/
void admin_menu()
{
    int exit = 0, x;

    while (exit == 0)
    {

        printf("\n");
        printf("\n\t\t\t*********************************************************");
        printf("\n\t\t\t--------------WELCOME TO THE *Admin Menu*---------------");
        printf("\n\t\t\t*********************************************************\n");

        printf("\n\t\t\t\t\t|\t1 To Add New BUS\t\t|\n\t\t\t\t\t|\t2 To Remove BUS\t\t\t|\n"
               "\t\t\t\t\t|\t3 View All Passengers\t\t|\n\t\t\t\t\t|\t4 To Calculate Employee Salary\t|"
               "\n\t\t\t\t\t|\t5 Check Financial Position\t|\n\t\t\t\t\t|\t6 Search BUS\t\t\t|\n\t\t\t\t\t|\t7 To Display All Buses\t\t|\n\t\t\t\t\t|\t8 To Update Bus\t\t\t|\n\t\t\t\t\t|\t9 Logout\t\t\t|");
        printf("\n");
        printf("\t\t=========================");
        printf("\n\t\tEnter Choice :: ");
        scanf("%d", &x);
        printf("\n\t\t=========================\n");
        system("cls");

        switch (x)
        {
        case 1:
            createBus();

            break;
        case 2:
            removeBus();

            break;
        case 3:
            DisplayAllPassengers();
            break;
        case 4:
            calculateEmployeeSalaries();
            break;
        case 5:
            calculateProfit();
            break;
        case 6:
            searchBus();
            break;
        case 7:
            DisplayAllBusses();
            break;
        case 8:
            updateBus();
            break;
        case 9:
            exit = 1;
            break;
        default:
            break;
        }
    }
}

/*
--Admin Menu--
Function to *CREATE BUS* when Admin wants
*/
void createBus()
{
    printf("\n");
    printf("\n\t\t\t*********************************************************");
    printf("\n\t\t\t-------------WELCOME TO THE *ADD BUS RECORD* Menu--------------");
    printf("\n\t\t\t*********************************************************\n");
    printf("***************\n");

    // creating Node For Adding Bus
    struct nodeBus *newBus, *temp, *temp1 = NULL;
    newBus = (struct nodeBus *)malloc(sizeof(struct nodeBus));
    int exit = 0;
    while (exit == 0)
    {
        int found = 0;
        printf("\nEnter Bus No:	");
        scanf("%d", &newBus->busNo);
        fflush(stdin);
        temp = head1;
        while (temp != NULL)
        {
            if (temp->busNo == newBus->busNo)
            {
                printf("BUS ALREADY REGISTERED\n");
                found++;
                break;
            }
            temp = temp->next;
        }
        if (found == 0)
        {
            exit = 1;
        }
    }

    printf("\nEnter Driver Name:	");
    gets(newBus->driver);

    UpperCase(newBus->driver);
    printf("\nEnter the Departure City:	");
    gets(newBus->source);
    UpperCase(newBus->source);

    printf("\nEnter the Destination City:	");
    gets(newBus->destination);
    UpperCase(newBus->destination);

    printf("\nEnter the date of journey: mm/dd/yyyy:	");
    gets(newBus->date);

    printf("\nEnter Time Of Departure:	");
    gets(newBus->time);

    printf("\nEnter Total Number Of Seats:	");
    scanf("%d", &newBus->totalSeats);
    newBus->availableSeats = newBus->totalSeats;

    printf("\nEnter the price of one Ticket:	");
    scanf("%d", &newBus->price);

    /*
    ---Inserting Data in FIle---

    */
    FILE *file;
    file = fopen("BusData.csv", "a"); // 'a' Append the Data and 'w' overwrite the Data
    fprintf(file, "%d,%s,%s,%s,%s,%s,%d,%d\n", newBus->busNo, newBus->driver, newBus->source, newBus->destination, newBus->date, newBus->time, newBus->totalSeats, newBus->price);
    fclose(file);

    // Assigning Seats
    for (int i = 0; i < newBus->totalSeats; i++)
    {
        newBus->seats[i] = i + 1;
    }
    newBus->next = NULL;
    temp = head1;

    while (temp != NULL)
    {

        temp1 = temp;
        temp = temp->next;
    }
    if (temp1 == NULL)
    {
        head1 = newBus;
    }
    else
    {
        temp1->next = newBus;
    }

    printf("\n\t\t\t-------------BUS has been Successfully Added--------------");
    printf("\nDo You Want To Add More Busses?Y/N:	");

    // Asking the Admin if he want to Add more Bus or not
    char addMore;
    fflush(stdin);
    scanf("%c", &addMore);
    system("cls");

    if (addMore == 'Y' || addMore == 'y')
    {
        createBus();
    }
    else
    {
        admin_menu();
    }
}

/*
--Admin Menu--
Function to *REMOVE BUS* when Admin wants
*/
void removeBus()
{
    printf("\n");
    printf("\n\t\t\t*********************************************************");
    printf("\n\t\t\t-------------WELCOME TO THE *REMOVE BUS* Menu--------------");
    printf("\n\t\t\t*********************************************************\n");
    printf("***************\n");

    struct nodeBus *temp, *temp2 = NULL;

    int busNo;

    printf("Enter The Bus No You Want To Remove :");
    scanf("%d", &busNo);

    // Finding Bus Using Bus Number
    temp = head1;
    while (temp != NULL)
    {
        if (temp->busNo == busNo)
        {
            printBusses(temp);
            busNo = -1;
            break;
        }

        temp2 = temp;
        temp = temp->next;
    }

    // Removing Bus if Bus is Head Node
    if (temp2 == NULL && busNo == -1)
    {
        head1 = temp->next;
        printf("\n\nBUS with BUS No %d Removed Successfully..!", temp->busNo);
        free(temp);
    }

    else if (temp2 != NULL && busNo == -1)
    {
        temp2->next = temp->next;
        printf("\n\nBUS with BUS No %d Removed Successfully..!", temp->busNo);
        free(temp);
    }
    else
    {
        printf("\n\nBUS with BUS No %d Not Found..!", busNo);
    }

    // If Admin Wants to Remove More Buses
    printf("\n\nDo You Want To Remove More Busses? Y/N:	");
    char addMore;
    fflush(stdin);
    scanf("%c", &addMore);
    printf("\n\t\t\t\t--------------Press Any Key to Continue---------------");
    getch();
    system("cls");
    if (addMore == 'Y' || addMore == 'y')
    {
        removeBus();
    }
    else if (addMore == 'N' || addMore == 'n')
    {
        admin_menu();
    }
}

/*
--Admin Menu--
Function for *CALCULATE PROFIT*
*/
struct expensesRevenue
{
    char expRev[20];
};
void calculateProfit()
{
    printf("\n");
    printf("\n\t\t\t*********************************************************");
    printf("\n\t\t\t-------------WELCOME TO THE *PROFIT RECORD* Menu--------------");
    printf("\n\t\t\t*********************************************************\n");

    double expense[20], revenue[20], totalExpense = 0, totalRevenue = 0;
    struct expensesRevenue expenseName[20], revenueName[20];
    int eCount = 0, rCount = 0;
    char flag = 'Y';
    int i = 0;
    printf("================================\n");
    while (flag == 'Y' || flag == 'y')
    {
        fflush(stdin);
        printf("Enter Expense Name:	");
        gets(expenseName[i].expRev);
        UpperCase(expenseName[i].expRev);

        printf("\nEnter Expense Amount:	");
        scanf("%lf", &expense[i]);
        eCount++;
        totalExpense = totalExpense + expense[i];
        fflush(stdin);
        printf("\n\nDo You Want To Add More Expense? Y/N:	");
        scanf("%c", &flag);
        fflush(stdin);
        i++;

    } // if flag==n then loop terminate
    printf("================================\n\n");
    /*
    	---Inserting Data in FIle---
    	*/

    flag = 'Y';
    i = 0;
    while (flag == 'Y' || flag == 'y')
    {
        printf("********************************\n");
        printf("Enter Revenue Name:	");
        gets(revenueName[i].expRev);
        UpperCase(revenueName[i].expRev);

        printf("\nEnter Revenue Amount:	");
        scanf("%lf", &revenue[i]);
        rCount++;
        totalRevenue = totalRevenue + revenue[i];
        fflush(stdin);
        printf("\n\nDo You Want To Add More Revenue? Y/N:	");
        scanf("%c", &flag);
        fflush(stdin);
        i++;
        printf("********************************");
    }
    /*
    		---Inserting Data in FIle---
    		*/
    FILE *file;

    // Printing Profit Data
    printf("\n");
    printf("\n\t\t\t*********************************************************");
    printf("\n\t\t\t-------------WELCOME TO THE *Income Statement* --------------");
    printf("\n\t\t\t*********************************************************\n");

    i = 0;
    printf("\n");
    printf("\n\t\t\t ================================================================================");
    printf("\n\t\t\t Expense\t\tAmount\t\t\t||\t Revenue\tAmount\n");

    while (i < eCount || i < rCount)
    {

        if (i < eCount)
        {
            printf("\t\t\t%d %s\t\t\t %.2f", i + 1, expenseName[i].expRev, expense[i]);

            file = fopen("IncomeStatement.csv", "a"); // 'a' Append the Data and 'w' overwrite the Data
            fprintf(file, "%s, %.2lf", expenseName[i].expRev, expense[i]);
            fclose(file);
        }
        if (i < rCount)
        {
            printf("|| \t\t%s\t\t %.2f\n", revenueName[i].expRev, revenue[i]);
            file = fopen("IncomeStatement.csv", "a"); // 'a' Append the Data and 'w' overwrite the Data
            fprintf(file, ",%s, %.2lf\n", revenueName[i].expRev, revenue[i]);
            fclose(file);
        }
        i++;
    }

    printf("\n\t\t\t-------------------------------------------------------------------------------\n");
    printf("\t\t\t TOTAL EXPENSE: %.2f\t\t\t||\t TOTAL REVENUE: %.2f", totalExpense, totalRevenue);
    printf("\n\t\t\t-------------------------------------------------------------------------------\n");

    printf("\t\t\t **PROFIT :  \t   %.2f**\t", totalRevenue - totalExpense);

    double profit;
    profit = totalRevenue - totalExpense;
    file = fopen("IncomeStatement.csv", "a"); // 'a' Append the Data and 'w' overwrite the Data
    fprintf(file, "\n,,,,%.2lf, %.2lf,%.2lf\n", totalExpense, totalRevenue, profit);
    fclose(file);

    if (totalRevenue - totalExpense <= 0)
    {
        printf("OH.....We Are In loss......!!!!!");
    }

    else
    {
        printf("ALHUMDULILLAH.....WE ARE GROWING");
    }
    printf("\n\t\t\t--------------------------------------------------------------------------------");
    printf("\n\t\t\t ===============================================================================\n");

    printf("\n\t\t\t\t--------------Press Any Key to Continue---------------");
    getch();
    system("cls");

    /*
    ---Inserting Data in FIle---

    */
}

/*
--Admin Menu--
Function for *CALCULATE Employee Salary*
*/
void calculateEmployeeSalaries()
{
    printf("\n");
    printf("\n\t\t\t*********************************************************");
    printf("\n\t\t\t-------------WELCOME TO THE *EMPLOYEE SALARY RECORD* Menu--------------");
    printf("\n\t\t\t*********************************************************\n");

    int choose, exit = 0;
    double distance;
    while (exit == 0)
    {
        printf("\n\t\t\t\t\t|\t1 For Employee Type\t\t|\n\t\t\t\t\t|\t2 For Driver\t\t\t|\n"
               "\t\t\t\t\t|\t3 For Bus Hostess\t\t|\n\t\t\t\t\t|\t4 EXIT\t\t\t\t|");
        printf("\n***************\n");
        printf("Enter Your Choice:	");
        scanf("%d", &choose);
        if (choose == 1)
        {
            printf(" \n\n====RS 20 per KM For Employee===\n");
            printf("\nEnter Distance of Services In KM:");
            scanf("%lf", &distance);

            /*
            	---Inserting Data in FIle---
            */
            FILE *file;
            file = fopen("EmployeeSalary.csv", "a"); // 'a' Append the Data and 'w' overwrite the Data
            fclose(file);

            printf("\n\n-------------------------\n");
            printf("Employee Salary\n\n");
            printf(" RS 20 X %.2lf KMs = RS %.2lf\n", distance, distance * 20);
            printf("-------------------------");

            /*
            ---Inserting Data in FIle---

            */

            file = fopen("EmployeeSalary.csv", "a"); // 'a' Append the Data and 'w' overwrite the Data

            fprintf(file, "%s,%.2lf,%.2lf\n", "Employee", distance, distance * 20);
            fclose(file);

            printf("\n\t\t\t\t--------------Press Any Key to Continue---------------");
            getch();
            system("cls");
        }
        else if (choose == 2)
        {
            printf("\n\n====RS 10 per KM===\n");
            printf("\nEnter Distance of Services In KM:");
            scanf("%lf", &distance);
            printf("\n\n-------------------------\n");
            printf("Driver Salary\n\n");
            printf("RS 10 X %.2lf KMs =RS %.2lf\n", distance, distance * 10);
            printf("-------------------------");

            FILE *file;
            file = fopen("EmployeeSalary.csv", "a"); // 'a' Append the Data and 'w' overwrite the Data
            // fprintf(file, " Employee" );
            fprintf(file, "%s,%.2lf,%.2lf\n", "DRIVER", distance, distance * 20);
            fclose(file);

            printf("\n\t\t\t\t--------------Press Any Key to Continue---------------");
            getch();
            system("cls");
        }
        else if (choose == 3)
        {
            printf("\n\n====RS 8 per KM===\n");
            printf("\nEnter Distance of Services In KM:");
            scanf("%lf", &distance);
            printf("\n\n-------------------------\n");
            printf("Bus Hostess Salary\n\n");
            printf("RS 8 X %.2lf KMs =RS %.2lf\n", distance, distance * 8);
            printf("-------------------------");

            FILE *file;
            file = fopen("EmployeeSalary.csv", "a"); // 'a' Append the Data and 'w' overwrite the Data
            // fprintf(file, " Employee" );
            fprintf(file, "%s,%.2lf,%.2lf\n", "BUS HOSTESS", distance, distance * 20);
            fclose(file);

            printf("\n\t\t\t\t--------------Press Any Key to Continue---------------");
            getch();
            system("cls");
        }
        else if (choose == 4)
        {
            exit = 1;
        }
        else
        {
            printf("Are You Crazy....Invalid Input\n");
        }
    }

    system("cls");
}

/*
Function for *Search Bus*
*/
void searchBus()
{
    printf("\n");
    printf("\n\t\t\t**************************************************************");
    printf("\n\t\t\t-------------WELCOME TO THE *SEARCH RECORD* Menu--------------");
    printf("\n\t\t\t**************************************************************\n");
    printf("***************\n");
    int busNo;
    printf("Enter BUS NO to Search:	");
    scanf("%d", &busNo);
    struct nodeBus *temp;
    temp = head1;
    while (temp != NULL)
    {
        if (temp->busNo == busNo)
        {
            printBusses(temp);
            busNo = -1;
            break;
        }
        temp = temp->next;
    }
    if (busNo != -1)
    {
        printf("\n\nBUS with BUS No %d Not Found..!", busNo);
    }
    printf("\n\t\t\t\t--------------Press Any Key to Continue---------------");
    getch();
    system("cls");
}

void updateBus()
{
    printf("\n");
    printf("\n\t\t\t*********************************************************");
    printf("\n\t\t\t-------------WELCOME TO THE *TICKET REGISTRATION* Menu--------------");
    printf("\n\t\t\t*********************************************************\n");
    printf("***************\n");

    struct nodeBus *temp;
    int busId, found = 0, choose;
    printf("\n\nEnter Bus ID To Update:	");
    scanf("%d", &busId);
    temp = head1;
    while (temp != NULL)
    {
        if (temp->busNo == busId)
        {
            found++;
            printBusses(temp);

            int exit = 0;
            while (exit == 0)
            {
                printf("\n\t\t\t\t\t|\t1 To Update Driver Name\t\t|\n\t\t\t\t\t|\t2 To Update Departure City\t|\n"
                       "\t\t\t\t\t|\t3 To Update Arrival City\t|\n\t\t\t\t\t|\t4 To Update Date\t\t|\n\t\t\t\t\t|\t5 To Update TIme\t\t|\n\t\t\t\t\t|\t6 To Update Seats\t\t|\n\t\t\t\t\t|\t7 To Update Price\t\t|\n\t\t\t\t\t|\t8 To Exit\t\t|");
                printf("\n***************\n");
                printf("Enter Your Choice:	");
                scanf("%d", &choose);
                if (choose == 1)
                {
                    fflush(stdin);
                    printf("\nEnter Driver Name:	");
                    fflush(stdin);
                    gets(temp->driver);
                    UpperCase(temp->driver);
                }
                else if (choose == 2)
                {
                    printf("\nEnter the Departure City:	");
                    fflush(stdin);
                    gets(temp->source);
                    UpperCase(temp->source);
                }
                else if (choose == 3)
                {
                    printf("\nEnter the Destination City:	");
                    fflush(stdin);
                    gets(temp->destination);
                    UpperCase(temp->destination);
                }
                else if (choose == 4)
                {
                    printf("\nEnter the date of journey: mm/dd/yyyy:	");
                    fflush(stdin);
                    gets(temp->date);
                }
                else if (choose == 5)
                {
                    printf("\nEnter Time Of Departure:	");
                    fflush(stdin);
                    gets(temp->time);
                }
                else if (choose == 6)
                {
                    printf("\nEnter Total Number Of Seats:	");
                    scanf("%d", &temp->totalSeats);
                    temp->availableSeats = temp->totalSeats;
                    for (int i = 0; i < temp->totalSeats; i++)
                    {
                        temp->seats[i] = i + 1;
                    }
                }
                else if (choose == 7)
                {
                    printf("\nEnter the price of one Ticket:	");
                    scanf("%d", &temp->price);
                }
                else if (choose == 8)
                {
                    exit = 1;
                }
                else
                {
                    printf("Invalid Input");
                }
            }
            break;
        }
        temp = temp->next;
    }

    if (found == 0)
    {
        printf("Bus ID not Found");
    }
    printf("\n\t\t\t\t--------------Press Any Key to Continue---------------");
    getch();
    system("cls");
}

/*==========================================================================================================*/
/*-------------------------------------------USER PANEL----------------------------------------------------*/
/*==========================================================================================================*/

/*
--User Menu--
Function for *Ticker Registeration*
*/
void ticketRegistration()
{
    printf("\n");
    printf("\n\t\t\t*********************************************************");
    printf("\n\t\t\t-------------WELCOME TO THE *TICKET REGISTRATION* Menu--------------");
    printf("\n\t\t\t*********************************************************\n");
    printf("***************\n");
    fflush(stdin);
    char source[20], destination[20];
    int busCount = 0;
    printf("\nEnter The Source:	");
    gets(source);
    UpperCase(source);
    printf("\nEnter The Destination:	");
    gets(destination);
    UpperCase(destination);
    struct nodeBus *temp = head1;
    while (temp != NULL)
    {

        if (strcmp(temp->source, source) == 0 && strcmp(temp->destination, destination) == 0)
        {
            busCount++;
            printBusses(temp);
        }
        temp = temp->next;
    }
    if (busCount == 0)
    {
        printf("\n\nNO BUSES for %s to %s Available\n", source, destination);
    }
    else
    {
        selectBus(busCount, destination, source);
    }
    printf("\n\t\t\t\t--------------Press Any Key to Continue---------------");
    getch();
    system("cls");
}

/*
--User Menu--
Further Function for *Ticket Registration*
Function --- Select Bus
*/
void selectBus(int busCount, char destination[20], char source[20])
{
    int busNO;
    printf("\n%d Bus(es) Available For  %s to %s\n", busCount, source, destination);
    printf("\nEnter BUS No:	");
    scanf("%d", &busNO);
    struct nodeBus *temp = head1, *temp2 = NULL;
    while (temp != NULL)
    {
        if (strcmp(temp->source, source) == 0 && strcmp(temp->destination, destination) == 0 && temp->busNo == busNO)
        {
            temp2 = temp;
            break;
        }
        temp = temp->next;
    }
    if (temp2 == NULL)
    {
        printf("\n----------------------\n");
        printf("Bus Not Available");
        printf("\n----------------------\n");
        printf("\nEnter Bus Number Again:	");
        temp = head1;
        busCount = 0;
        while (temp != NULL)
        {
            if (strcmp(temp->source, source) == 0 && strcmp(temp->destination, destination) == 0)
            {
                busCount++;
                printBusses(temp);
            }
            temp = temp->next;
        }
        selectBus(busCount, destination, source);
    }
    else
    {
        confirmTicket(temp2, busNO, destination, source);
    }
    printf("\nDo You Want To Buy More Tickets?	Y/N:	");
    char addMore;
    fflush(stdin);
    scanf("%c", &addMore);
    if (addMore == 'Y' || addMore == 'y')
    {
        ticketRegistration();
    }
}

/*
--User Menu--
Further Function for *Select Bus*
Function --- Ticket Confirmation
*/
void confirmTicket(struct nodeBus *BUS, int busNo, char destination[20], char source[20])
{
    struct userNode *ticket, *temp, *temp2 = NULL;
    ticket = (struct userNode *)malloc(sizeof(struct userNode));
    fflush(stdin);
    printf("\nEnter Name:	");
    gets(ticket->name);
    UpperCase(ticket->name);

    printf("\nEnter Age:	");
    scanf("%d", &ticket->age);

    strcpy(ticket->start, source);
    strcpy(ticket->destination, destination);
    ticket->busNo = busNo;
    fflush(stdin);

    printf("\nEnter Phone No:	");
    gets(ticket->phoneNo);
    strcpy(ticket->date, BUS->date);
    strcpy(ticket->time, BUS->time);
    time(&currentTime);
    strcpy(ticket->bookTime, ctime(&currentTime));
    ticket->ticketID = regNum;

    regNum++;

    int seatNo, k = 0;
    printf("\nEnter No Of Seats You want to Book:	");
    scanf("%d", &ticket->noOfSeats);

    for (int j = 0; j < ticket->noOfSeats; ++j)
    {
        printf("\t\t=================================\n");
        for (int i = 0; i < BUS->totalSeats;)
        {
            printf("\t\t|");
            if (i != BUS->totalSeats)
            {
                printf("\t%.2d", BUS->seats[i]);
                i++;
            }
            if (i != BUS->totalSeats)
            {
                printf("-%.2d", BUS->seats[i]);
                i++;
            }
            if (i != BUS->totalSeats)
            {
                printf("\t|\t%.2d", BUS->seats[i]);
                i++;
            }
            if (i != BUS->totalSeats)
            {
                printf("-%.2d", BUS->seats[i]);
                i++;
            }
            printf("\t|\n");
        }
        printf("\t\t=================================\n");

        printf("\nAvailable Seats\n\n\n");
        for (int i = 0; i < BUS->totalSeats; i++)
            if (BUS->seats[i] != 0)
            {
                printf("%d,", BUS->seats[i]);
            }
        int exit = 0;

        while (exit == 0)
        {
            printf("\n\n\n Enter Seat No %d From Available:	", j + 1);
            scanf("%d", &seatNo);
            if (BUS->seats[seatNo - 1] == 0)
            {
                printf("Seat Not Available!\n");
            }
            else if (seatNo > BUS->totalSeats)
            {
                printf("\nSeat Not Available!");
            }
            else if (seatNo <= 0)
            {
                printf("\nEnter Valid Seat No!");
            }
            else
            {
                ticket->seatNo[k] = seatNo;
                BUS->seats[seatNo - 1] = 0;
                k++;
                exit = 1;
            }
        }
    }

    BUS->availableSeats = BUS->availableSeats - ticket->noOfSeats;
    char promoCode[20];
    printf("Enter Promo Code:");
    fflush(stdin);
    gets(promoCode);
    UpperCase(promoCode);
    ticket->price = ticket->noOfSeats * BUS->price;
    ticket->discount= promoCrode(promoCode);
    if(ticket->discount==0)
    {
        printf("O Discount");
    }
    else
    {
        printf("\nYou Have Availed %.0lf%% Discount i.e %.2lf of Your FEE...\n",ticket->discount,ticket->price*((ticket->discount)/100));
        ticket->price= ticket->price*((100-ticket->discount)/100);
    }
    /*
    ---Inserting Data in FIle---

    */
    // FILE *file1;
    // file1 = fopen("TicketData.csv", "a"); // 'a' Append the Data and 'w' overwrite the Data
    // fprintf(file1, "%s,%d,%s,%s,%s,%s\n", ticket->name, ticket->age, ticket->start, ticket->destination, ticket->phoneNo, ticket->noOfSeats);
    // fclose(file1);

    printf("=========CUSTOMER CHALLAN==========");
    printTickets(ticket);

    ticket->next = NULL;
    temp = head2;
    while (temp != NULL)
    {

        temp2 = temp;
        temp = temp->next;
    }
    if (temp2 == NULL)
    {
        head2 = ticket;
    }
    else
    {
        temp2->next = ticket;
    }
}

/*
--User Menu--
Function --- Cancellation of Ticket
*/
void cancelTicket()
{
    printf("\n");
    printf("\n\t\t\t**************************************************************");
    printf("\n\t\t\t-------------WELCOME TO THE *CANCEL TICKET* Menu--------------");
    printf("\n\t\t\t**************************************************************\n");
    printf("***************\n");
    int id;
    printf("Enter Ticket ID to Delete:	");
    scanf("%d", &id);
    struct userNode *temp, *temp2 = NULL;
    temp = head2;
    while (temp != NULL)
    {
        if (temp->ticketID == id)
        {
            printTickets(temp);
            id = -1;
            break;
        }
        temp2 = temp;
        temp = temp->next;
    }
    if (temp2 == NULL && id == -1)
    {
        head2 = temp->next;
        printf("\n\nTicket with Ticket ID %d Removed Successfully..!", temp->ticketID);
        free(temp);
    }
    else if (temp2 != NULL && id == -1)
    {
        temp2->next = temp->next;
        printf("\n\nTicket with Ticket ID %d Removed Successfully..!", temp->ticketID);
        free(temp);
    }
    else
    {
        printf("\n\nTicket with Ticket ID %d Not Found..!\n\n", id);
    }
    printf("Do You Want To Remove More Tickets?	Y/N:	");
    char addMore;
    fflush(stdin);
    scanf("%c", &addMore);
    system("cls");
    if (addMore == 'Y' || addMore == 'y')
    {
        cancelTicket();
    }
}

/*==========================================================================================================*/
/*-------------------------------------------DATA PRINTING--------------------------------------------------*/
/*==========================================================================================================*/

/*
Function for *Displaying All Buses*
*/
void DisplayAllBusses()
{

    FILE *file;
    file = fopen("BusData.csv", "w"); // 'a' Append the Data and 'w' overwrite the Data
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s\n", "BUS NO", "DRIVER", "DEPARTURE", "DESTINATION", "DATE", "TIME", "SEATS", "PRICE");
    fclose(file);

    printf("\n");
    printf("\n\t\t\t*************************************************************");
    printf("\n\t\t\t-------------WELCOME TO THE *BUSES RECORD* Menu--------------");
    printf("\n\t\t\t*************************************************************\n");
    printf("***************\n");
    struct nodeBus *temp = head1;
    if (temp == NULL)
    {
        printf("\nNo Record Found......\n");
    }
    else

        while (temp != NULL)
        {
            printf("\n\t\t\t*************************************************************\n");

            FILE *file;
            file = fopen("BusData.csv", "a"); // 'a' Append the Data and 'w' overwrite the Data
            fprintf(file, "%d,%s,%s,%s,%s,%s,%d,%d\n", temp->busNo, temp->driver, temp->source, temp->destination, temp->date, temp->time, temp->availableSeats, temp->price);
            fclose(file);
            printBusses(temp);
            temp = temp->next;
            printf("\n\t\t\t*************************************************************");
        }
    printf("\n\t\t\t--------------------------------------------------------------------------------");
    printf("\n\t\t\t ===============================================================================\n");
    printf("\n\t\t\t\t--------------Press Any Key to Continue---------------");
    getch();
    system("cls");
}

/*
Function for *Printing All Buses*
*/
void printBusses(struct nodeBus *ptr)
{
    printf("================================================");
    printf("\n| BUS NO                 :   %d\t\t|", ptr->busNo);
    printf("\n| SOURCE                 :   %s\t\t|", ptr->source);
    printf("\n| DESTINATION            :   %s\t\t|", ptr->destination);
    printf("\n| DRIVER                 :   %s\t\t|", ptr->driver);
    printf("\n| DATE                   :   %s\t\t|", ptr->date);
    printf("\n| TIME                   :   %s\t\t|", ptr->time);
    printf("\n| PRICE PER SEAT         :   %d\t\t|", ptr->price);
    printf("\n| Total NUMBER OF SEATS  :   %d\t\t\t|", ptr->totalSeats);
    printf("\n| AVAILABLE N0 OF SEATS  :   %d\t\t\t|\n", ptr->availableSeats);
    printf("================================================\n");
    printf("\n\t\t                   SEATS                \n");
    /*
    ---Inserting Data in FIle---

    */

    printf("\n\t\t=================================\n");
    for (int i = 0; i < ptr->totalSeats;)
    {
        printf("\t\t|");
        if (i != ptr->totalSeats)
        {
            printf("\t%.2d", ptr->seats[i]);
            i++;
        }
        if (i != ptr->totalSeats)
        {
            printf("-%.2d", ptr->seats[i]);
            i++;
        }
        if (i != ptr->totalSeats)
        {
            printf("\t|\t%.2d", ptr->seats[i]);
            i++;
        }
        if (i != ptr->totalSeats)
        {
            printf("-%.2d", ptr->seats[i]);
            i++;
        }
        printf("\t|\n");
    }
    printf("\t\t=================================\n");
}

/*
Function for *Printing Ticket*
*/
void printTickets(struct userNode *ticket)
{

    printf("\n\t\t\t\t\t   |================================================|\n");
    printf("\t\t\t\t\t   |\t\tSKYWAYS DAEWOO BUS TEMINAL\t    |\n");
    printf("\t\t\t\t\t   |------------------------------------------------|\n");
    printf("\t\t\t\t\t   |\t\t\t\t\t\t    |");
    printf("\n\t\t\t\t\t   |\tTicket    ID         :  %d\t\t    |", ticket->ticketID);
    printf("\n\t\t\t\t\t   |\tPassenger Name       :  %s\t\t    |", ticket->name);
    printf("\n\t\t\t\t\t   |\tPassenger Age        :  %d\t\t    |", ticket->age);
    printf("\n\t\t\t\t\t   |\tPassenger PhoneNo    :  %s\t    |", ticket->phoneNo);
    printf("\n\t\t\t\t\t   |\tPassenger BUS        :  %d\t\t    |", ticket->busNo);
    printf("\n\t\t\t\t\t   |\tDeparture Time       :  %s\t    |", ticket->time);
    printf("\n\t\t\t\t\t   |\tDeparture Date       :  %s\t    |", ticket->date);
    printf("\n\t\t\t\t\t   |\tPassenger Seat       :  %d\t\t    |", ticket->noOfSeats);
    printf("\n\t\t\t\t\t   |\tFEE (%.0lf%% Discount)   :  %d\t\t     |",ticket->discount, ticket->price);
    printf("\n\t\t\t\t\t   |\tPassenger Seat/s     : ");
    for (int i = 0; i < ticket->noOfSeats; i++)
    {
        printf("%d ", ticket->seatNo[i]);
    }
    printf(" \t\t    |");

    printf("\n\t\t\t\t\t   |\tDeparture City       :  %s\t\t    |", ticket->start);
    printf("\n\t\t\t\t\t   |\tArrival   City       :  %s\t\t    |", ticket->destination);

    printf("\n\t\t\t\t\t   |================================================|");
    printf("\n\t\t\t\t\t   |\t--------%s    ", ticket->bookTime);
    printf("\n\t\t\t\t\t   |================================================|");

    /*

    ---Inserting Data in FIle---

    */
}

/*
Function for *Displaying *
*/
void DisplayAllPassengers()
{
    FILE *file;
    file = fopen("TicketData.csv", "w"); // 'a' Append the Data and 'w' overwrite the Data
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "ID", "NAME", "AGE", "PHONE NUMBER", "BUS NUMBER", "TIME", "DATE", "NUMBER OF SEATS", "PRICE", "DEPARTRE", "DESTINATION");
    fclose(file);

    printf("\n");
    printf("\n\t\t\t******************************************************************");
    printf("\n\t\t\t-------------WELCOME TO THE *PASSENGERS RECORD* Menu--------------");
    printf("\n\t\t\t******************************************************************\n");
    printf("***************\n");
    struct userNode *temp = head2;
    if (temp == NULL)
    {
        printf("\nNo Record Found......\n");
    }
    else
        while (temp != NULL)
        {
            FILE *file;
            file = fopen("TicketData.csv", "a"); // 'a' Append the Data and 'w' overwrite the Data
            fprintf(file, "%d,%s,%d,%s,%d,%s,%s,%d,%d,%s,%s\n", temp->ticketID,
                    temp->name, temp->age, temp->phoneNo, temp->busNo,
                    temp->time, temp->date, temp->noOfSeats, temp->price, temp->start, temp->destination);
            fclose(file);
            printTickets(temp);
            temp = temp->next;
        }
    printf("\n\t\t\t--------------------------------------------------------------------------------");
    printf("\n\t\t\t ===============================================================================\n");
    printf("\n\t\t\t\t--------------Press Any Key to Continue---------------");
    getch();
    system("cls");
}
double promoCrode(char promoCode[20])
{
    char promo1[20] = "BUS25", promo2[20] = "BUS30", promo3[20] = "BUS35";
    double discount = 0.0;
    if (strcmp(promo1, promoCode) == 0)
    {
        discount = 25.0;
        return discount;
    }
    else if (strcmp(promo2, promoCode) == 0)
    {
        discount = 30.0;
        return discount;
    }
    else if (strcmp(promo3, promoCode) == 0)
    {
        discount = 35.0;
        return discount;
    }
    else
        return discount;
}
