#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

void login();
int mainmenu();
int passenger();
int admin();

struct train
{
    int data; //stores index number
    char trainName[100];
    char route[100];    //Mumbai-Delhi
    int Ticketfare;     //stores ticket ka paisa
    char date[20];      // 23 Jan 2021
    char deptTime[20];  // 00 : 59
    struct train *next; //stores the address of next train node
};

struct ticket
{
    int Tnum;
    char trainName[20];
    int indexNumber;
    char PName[100];
    int age;
    char gender;
    char date[11];
    char Bdate[11];
    int TicketFare;
    struct ticket *next;
};

//function inserts node at last
void InsertNewTrain(struct train **start, int indexNumber, char trainName[100], char route[100], int ticketFare, char date[20], char deptTime[20])
{
    struct train *NewTrain, *temp;
    NewTrain = (struct train *)malloc(sizeof(struct train));

    NewTrain->data = indexNumber;
    strcpy(NewTrain->route, route);
    strcpy(NewTrain->trainName, trainName);
    NewTrain->Ticketfare = ticketFare;
    strcpy(NewTrain->date, date);
    strcpy(NewTrain->deptTime, deptTime);
    NewTrain->next = NULL;

    if (*start == NULL)
        *start = NewTrain; //*start means whatever the pointer is pointing to

    else
    {
        temp = *start; //pehle node ka address is start's value
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = NewTrain;
    }
}

int display(struct train *start)
{

    if(!start){
        printf("No trains Vailable Trains!\n");
        return 0;
    }

    while (start)
    {
        printf("%d", start->data);
        printf("\t%s\n", start->trainName);
        printf("\tRoute: %s\n", start->route);
        printf("\tDate: %s\n", start->date);
        printf("\tTime: %s \n", start->deptTime);
        start = start->next;
        printf("\n");
    }

    
}

void insertTicket(struct ticket **startTk, struct train *s, int indexNumber, char pName[100], char Bdate[20], int age, char gender, int tNum)
{
    struct ticket *newTicket, *temp;
    struct train *t;
    newTicket = (struct ticket *)malloc(sizeof(struct ticket));

    t = s;
    int flag = 0;
    while (t != NULL)
    {
        if (t->data == indexNumber)
        {
            flag = 1;
            break;
        }
        t = t->next;
    }

    if (flag == 1)
    {
        //  printf("Node found!");
        newTicket->Tnum= tNum;
        newTicket->indexNumber = indexNumber;
        strcpy(newTicket->trainName, t->trainName);
        strcpy(newTicket->PName, pName);
        strcpy(newTicket->date, t->date);
        strcpy(newTicket->Bdate, Bdate);
        
        newTicket->TicketFare = t->Ticketfare;
        newTicket->next = NULL;

        if (*startTk == NULL)
        {
            *startTk = newTicket;
        }
        else
        {
            temp = *startTk;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newTicket;
        }
    }

    else
    {
        printf("Invalid train!");
    }
}


void delete(struct train **s, int indexNumber){
    struct train *t1, *t2;
if(*s==NULL){
    printf("There are no trains to delete\n");
}
else{
    t1=*s;
    t2=NULL;
    while(t1->data!=indexNumber){
        t2=t1;
        t1=t1->next;
    }
if(t2!=NULL){
    t2->next=t1->next;
}
else{
    *s=t1->next;
}
free(t1);
}

}

//--------------------------------------------------------Delete ticket
void deleteTk(struct ticket**s, int tNum){
    struct ticket *t1, *t2;
if(*s==NULL){
    printf("There are no tickets to delete\n");
}
else{
    t1=*s;
    t2=NULL;
    while(t1->Tnum!=tNum){
        t2=t1;
        t1=t1->next;
    }
if(t2!=NULL){
    t2->next=t1->next;
}
else{
    *s=t1->next;
}
printf("%d Refunded", t1->TicketFare);
free(t1);
}

}

//---------------------------------------------------------------------Dsiplay Ticket

void displayTk(struct ticket *start)
{
    if(start == NULL){
        printf("No tickets Booked");
    }
    while (start != NULL)
    {
        printf("\n\n%d\n", start->indexNumber);
        printf("\n\n%s\n", start->trainName);
        printf("\t%d\n", start->TicketFare);
        printf("\tPassenger Name: %s\n", start->PName);
        printf("\tDate: %s\n", start->date);
        start = start->next;
        
    }
    printf("\n");
}
//------------------------------------------------------------------Display Single Ticket
dsiplaySingleTicket(struct ticket *stk, int tNum){
struct ticket *temp = stk;
while(temp!=NULL){
    if(temp->Tnum == tNum){
        printf("------------------------------------------\n TICKET \n -----------------------\n %s\n ", temp->PName);
    }
    temp=temp->next;
}
}

//-------------------------------------------------------------------Validate Train
int validateTrain(struct train *s, int indexNumber){
    struct train *t;
    t = s;
    
    while (t != NULL)
    {
        if (t->data == indexNumber)
        {
            return 1;
        }
        t = t->next;
    }
    printf("Invalid Train Number!");
    return 0;
}


//----------------------------------------------------------------------Menu-start

int mainmenu(struct train *st, struct ticket *stk)
{
    int prt, actadm;
    while (1)
    {
        printf("||||| Welcome to K-S-K Railways |||||");
        printf("\n\n\nWhich portal you want access? ");
        printf("\n\n1.Passenger");
        printf("\n2.Admin");
        printf("\n3.Exit");
        printf("\n\nEnter which portal you want to enter: ");
        scanf("%d", &prt);
        // system("cls");
        switch (prt)
        {
        case 1:
            passenger(st, stk);
            break;

        case 2:
            login();
            admin(st, stk);
            break;

        case 3:
            exit(0);
        default:
            printf("\n--Invalid choice--\n");
            break;
        }
    }
}

int passenger(struct train *st, struct ticket *stk)
{
    int indexNumber;
    char pName[100];
    char Bdate[20];
    int age;
    char gender;
    int actpass, status=1, val,tNum,flag;

    while(1){
    printf("\n\n1. Book a ticket");
    printf("\n2. Cancel a ticket");
    printf("\n3. View all trains");
    printf("\n4. <-- Go back ");
    printf("\n\nEnter which action you would like to perform (Enter number of respective action): ");
    scanf("%d", &actpass);
    //system("cls");
    switch (actpass)
    {
    case 1: 
       status = display(st);
        if(status){
        printf("Enter the index number of train for which u want to book a ticket: ");
        scanf("%d", &indexNumber);
      val  =  validateTrain(st, indexNumber);
        if(val){
        printf("Enter ticket Number\n");
        scanf("%d", &tNum);
        flag=0;
        struct ticket *temp = stk;
            while(temp!=NULL){
            if(temp->Tnum == tNum)
            {
             printf("Ticket with this ticket number already exists");
            flag=1;
            break;
            }
            temp = temp->next;
            }
            if (flag==1)
                break;

        printf("Enter Your Full Name: ");
        fflush(stdin);
        gets(pName);
        fflush(stdin);
        printf("Enter your age\n");
        scanf("%d", &age);
        fflush(stdin);
        printf("Enter your Gender (M/F/O)\n");
        scanf("%c", &gender);

        insertTicket(&stk, st, indexNumber, pName, Bdate, age, gender, tNum);
        printf("Your ticket is booked sucessfully!\n");
        printf("\n\nHere is your Ticket\n\n\n");
        dsiplaySingleTicket(stk, tNum);
}
}
        break;

    case 2: 
     printf("Enter the ticket number to delete\n");\
        scanf("%d", &tNum);

            struct ticket *t = stk;
            flag=0;
            while(t!=NULL){
            if(t->Tnum== tNum)
            {
            deleteTk(&stk, tNum);
            printf("Ticket deleted Successfully!");
            flag=1;
            break;
            }
            t = t->next;
            }
            if (flag==0)
               printf("Invalid Ticket number!");
                break;
    

    break;
    case 3: 
        display(st);
        displayTk(stk);
        break;
        case 4: mainmenu(st,stk);
        break;
    default:
        printf("\n--Invalid choice--\n");
        break;
    }
    }
}

int admin(struct train *start, struct ticket *s)
{

    int indexNumber;
    char trainName[100];
    char route[100];
    int ticketFare;
    char date[20];
    char deptTime[20];
    int actadm, flag;
    while (1)
    {
        printf("\n\n1. Add trains detail");
        printf("\n2. Cancel a train detail");
        printf("\n3. View all trains details");
        printf("\n4. View all Bookings");
        printf("\n5. <-- Go back ");
        printf("\n\nEnter which action you would like to perform (Enter number of respective action): ");
        scanf("%d", &actadm);
        switch (actadm)
        {
        case 1:
       flag=0;
            printf("Enter Serial Number\n");
            scanf("%d", &indexNumber);
            struct train *temp = start;
            while(temp!=NULL){
            if(temp->data == indexNumber)
            {
             printf("Train with this train number already exists");
            flag=1;
            break;
            }
            temp = temp->next;
            }
            if (flag==1)
                break;

            printf("\nEnter Train Name\n");
            fflush(stdin);
            gets(trainName);

            printf("Enter Route\n");
            fflush(stdin);
            gets(route);

            printf("Enter ticket Fare\n");
            scanf("%d", &ticketFare);

            printf("Enter Departure Date\n");
            fflush(stdin);
            gets(date);

            printf("Enter Departure time\n");
            fflush(stdin);
            gets(deptTime);
            InsertNewTrain(&start, indexNumber, trainName, route, ticketFare, date, deptTime);
            
            break;
        case 2:
         flag=0;
        printf("Enter the train number to delete\n");\
        scanf("%d", &indexNumber);

            struct train *t = start;

            while(t!=NULL){
            if(t->data == indexNumber)
            {
            delete(&start, indexNumber);
            printf("Train deleted Successfully!");
            flag=1;
            break;
            }

            t = t->next;
            }
            if (flag==0)
               printf("Invalid Train number!");
                break;
        
            
        case 3:
            display(start);
            break;
        case 4:
            displayTk(s);
            break;
        case 5:
            mainmenu(start, s);
            break;
        default:
            printf("\n--Invalid choice--\n");
            break;
        }
    }
}

void login()
{
    int i = 0;
    char username[50], password[50];
    char ch;
    //system("cls");
    printf("\n\t\t\t\t**");
    printf("\n\t\t\t\t**Admin Login*");
    printf("\n\t\t\t\t**");
    printf("\n\nEnter User Name: ");
    fflush(stdin);
    gets(username);
    printf("\n\nEnter Password: ");
    while (1)
    {
        ch = getch();
        if (ch == 13)
        {
            password[i] = '\0';
            break;
        }
        else
        {
            password[i] = ch;
            i++;
            printf("*");
        }
    }
    if (strcmp(username, "ksk") == 0)
    {
        if (strcmp(password, "12345") == 0)
        {
            printf("\n\n\t\t\t\t_Logged IN Successfully");
            //Satyam Pe chodta hu 
            Beep(750,1000);
            Beep(550,1000);
            Beep(650,1000);
            printf("\n\n\t\t\t\t__WELCOME %s!", username);
        }
        else
        {
            printf("\a\n\n\t\t\t\tERROR!Invalid Password!");
            printf("\nPress any key to exit!");
            getch();
            exit(0);
        }
    }
    else
    {
        printf("\a\n\n\t\t\t\tERROR!Invalid Username!__");
        printf("\nPress any key to exit!");
            getch();
            exit(0);

    }
}

//Menu-end

int main()
{
    //------------------Actual Code starts here-----------------
    struct train *start = NULL;
    struct ticket *startTk = NULL;

    int actadm;
    mainmenu(start, startTk);

    return 0;
}
//     int indexNumber;

    //     InsertNewTrain(&start, 1, "Avantika Express" ,"Mumbai-Delhi", 100, "23/11/21", "23:59"); //want the access of start from insertNewTrain() function
    //     InsertNewTrain(&start, 2, "KSK Express" ,"Mumbai-Delhi", 500, "23/11/21", "9:00");
    //     InsertNewTrain(&start, 3, "Shatadi Express" ,"Mumbai-Delhi", 200, "25/11/21", "23:59");
    //     display(start);
    //     printf("Book a ticket for train\n");
    //     display(start);
    //     scanf("%d", &indexNumber);
    //     insertTicket(&startTk, start, indexNumber, "Kush Kapadia", "23:59" );
    //     displayTk(startTk);

    // printf("Control here");
    //     scanf("%d", &indexNumber);
    //     insertTicket(&startTk, start, indexNumber, "Satyam", "10:00" );
    //     displayTk(startTk);

    // int indexNumber = 1;
    // char trainName[100];
    // char route[100];
    // int ticketFare;
    // char date[11];
    // char deptTime[7];

    // actadm = mainmenu();

    // switch(actadm)
    // 	{
    // 		case 1:
    //             printf("\nEnter Train Name\n");
    //             fflush(stdin);
    //             gets(trainName);

    //             printf("Enter Route\n");
    //             fflush(stdin);
    //             gets(route);

    //             printf("Enter ticket Fare\n");
    //             scanf("%d", &ticketFare);

    //             printf("Enter Departure Date\n");
    //             fflush(stdin);
    //             gets(date);

    //             printf("Enter Departure time\n");
    //             fflush(stdin);
    //             gets(deptTime);
    //             InsertNewTrain(&start, indexNumber, trainName, route, ticketFare, date, deptTime);
    //             indexNumber++;

    // 		    break;
    // 		case 2:
    //             //canceltraindetails()
    // 		    break;
    // 		case 3:
    //             display(start);
    // 		    break;
    // 		case 4:
    //             //viewallbookings()
    // 		    break;
    // 		case 5:
    //             mainmenu();
    // 		    break;
    // 		default:
    //     		printf("\n--Invalid choice--\n");
    //     		break;
    // 	}

    // display(start);

    // while(1){
    // actadm = mainmenu();

    // }

    
