
#include <stdio.h>
#include <string.h>

#define Total_TURFS 10
#define MAX_NAME_LENGTH 50
#define MAX_LOCATION_LENGTH 50


#define Total_TIMESLOTS 16
#define FILENAME "bookings.txt"


char booking_username[100]=" ";
char booking_username_cheak[100]=" ";

struct Turf {
    char name[MAX_NAME_LENGTH];
    char location[MAX_LOCATION_LENGTH];
    int timeSlots[Total_TIMESLOTS];

};

struct Turf turfs[Total_TURFS];

float time[18]={8.00,8.45,9.30,10.15,11.00,11.45,12.30,13.15,14.00,14.45,15.30,16.15,17.00,17.45,18.30,19.15,20.00};

void displayTimeSlots(int timeSlots[], int choice12) { int a=0;
    printf("Available Time Slots:\n");
    for (int i = 0; i < Total_TIMESLOTS; ++i)
        {
        printf("Slot %d: %s", i + 1, turfs[choice12-1].timeSlots[i] ? "Booked" : "Available");

        for(int j=a;j<a+1;j++)
        {

            printf("------Time--->(%.2f-%.2f)\n",time[j],time[j+1]);

        }
        a++;
        }
    printf("\n");
}

   void  verify_account_write(char booking_username[])
     {
         FILE * file;
         file=fopen("ID_verify.txt","a");
         if(file==0)
         {
              file=fopen("ID_verify.txt","w");
         }
         else
         {
           fprintf(file,"%s\n",booking_username);
         }
     }

// Function to book a time slot
void bookTimeSlot(int timeSlots[], int slotNumber,int choice11) {
    if (slotNumber < 1 || slotNumber > Total_TIMESLOTS) {
        printf("Invalid time slot number.\n");
        return;
    }

    if (turfs[choice11-1].timeSlots[slotNumber - 1] == 0) {
        turfs[choice11-1].timeSlots[slotNumber - 1] = 1;

        char verification[100]=" ";
        printf("\n---->Enter a verification code:");
        scanf("%s",verification);
        strcat(booking_username,verification);
        verify_account_write(booking_username);
        printf("------Time slot %d booked successfully!-----\n", slotNumber);
        printf("----For confirm you book you have pay 30%% of slot payment with in 30 min otherwise your booking will be canceled----\n");
        printf("----You can pay by our Bkash Or Rocket account.Please use your website user name and verification code as a reference.----\n");
        printf("\t\t----Thank you----\n");

        // Write the booking information to the file
        FILE *file = fopen(FILENAME, "a");
        if (file != NULL) {
            fprintf(file, "%d %d\n",choice11, slotNumber);
            fclose(file);
        } else {
            printf("Error writing to the file.\n");
        }
    } else {
        printf("\t\t-------Sorry!Time slot %d is already booked.-------\n", slotNumber);
    }
}

// Function to display booked time slots
void displayBookedSlots() {
    printf("Booked Time Slots:\n");

    FILE *file = fopen(FILENAME, "r");
    if (file != NULL) {

        int i,j,a=0,b=0;
        while(!feof(file))
        {
            fscanf(file,"%d %d",&i,&j);
            if(i!=a || j!=b)
            {
            printf("Turf num: %d\t Slot num:%d\n",i,j);
            i=a;
            j=b;
            }
        }

        fclose(file);
    } else {
        printf("Error reading from the file.\n");
    }

    printf("\n");

}

//Function to cancel booked time slots
void cancleTimeSlot(int timeSlots[], int slotNumber,int choice1) {
    if (slotNumber < 1 || slotNumber > Total_TIMESLOTS)
        {
        printf("Invalid time slot number.\n");
        return;
        }


        if (turfs[choice1-1].timeSlots[slotNumber - 1] == 1)
        {
                turfs[choice1-1].timeSlots[slotNumber - 1] = 0;
        printf("Time slot %d cancel successfully!\n", slotNumber);

        FILE *file = fopen(FILENAME, "w");
        if (file != NULL) {
        for(int i=0;i<Total_TURFS;i++)
        {
            for( int j=0;j<Total_TIMESLOTS;j++)
            {
                if(turfs[i].timeSlots[j]==1)
                {
                    fprintf(file,"%d %d\n",i+1 ,j+1);
                }
            }
        }
    }
        }
    else {
        printf("Time slot %d is already empty.\n", slotNumber);
    }
}

//Function to verify your id
   verify_account_read(int timeSlots[], int slotNumber,int choice1)
     {
         int cheak=0;
         char verify[100]=" ";
         printf("Enter your verification code: ");
         scanf("%s",verify);
         strcat(booking_username,verify);

         FILE * file;
         file=fopen("ID_verify.txt","r");
         if(file==0)
         {
              file=fopen("ID_verify.txt","w");
         }
         else
         {
             while(!feof(file))
                   {
                       fscanf(file,"%s",booking_username_cheak);

             if(strcmp(booking_username_cheak,booking_username)==0)
                {
                    printf("Id Verified\n");
                    cheak=1;
                    break;
                }
                   }

         }

            if(cheak==1){
          cancleTimeSlot(timeSlots, slotNumber,choice1);
          }

            else
            {
                printf("\t\t------>You input wrong verification code.<------\n");

            }
     }

     //Function for bookings menu
book() {
    int choice1;
    int choice15;
    int timeSlots[Total_TIMESLOTS];// = {0}; // 0 represents an available slot, 1 represents a booked slot
    displayAllTurfs();
    printf("\n\nEnter the turf number you want to book: ");
    scanf("%d", &choice1);
    // Read existing bookings from the file
    FILE *file = fopen(FILENAME, "r");
    if (file != NULL) {
        int slot;

        while (!feof(file)) {
           // if (slot >= 1 && slot <= Total_TIMESLOTS)
                {
                        fscanf(file, "%d %d \n",&choice15, &slot);
                turfs[choice15-1].timeSlots[slot - 1] = 1;

            }
        }


        fclose(file);
    }
    else{
            printf("file not found");

    }


    int choice2, slotNumber;

    do {
        printf("Booking Menu:\n ");
        printf("\t1. Display available time slots\n");
        printf("\t2. Book a time slot\n");
        printf("\t3. cancel a time slot\n");
        printf("\t4. Display booked time slots\n");

        printf("\t5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice2);

        switch (choice2) {
            case 1:
                displayTimeSlots(timeSlots,choice1);
                break;
            case 2:
                printf("Enter the time slot number you want to book: ");
                scanf("%d", &slotNumber);
                bookTimeSlot(timeSlots, slotNumber,choice1);
                break;
            case 3:
                printf("Enter the time slot number you want to cancel: ");
                scanf("%d", &slotNumber);
                 verify_account_read(timeSlots, slotNumber,choice1);
                break;
            case 4:
                displayBookedSlots();
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (choice2 != 5);


}
 //Fucntion for all turfs name and location and slot price
void displayAllTurfs() {
    printf("\n\t\t\t\t---->Available Turfs<----\n\n");
    for (int i = 0; i < Total_TURFS; ++i) {
        printf("\n%d. Turf name: %s, Location: %s\n", i + 1, turfs[i].name, turfs[i].location);
        if(i==0)
        {
            printf("Slot price: 8:00-15:30--->Per slot 1000tk\t\t15:30-20:00--->Per slot 1300tk\n");
        }
        if(i==1)
        {
            printf("Slot price: 8:00-15:30--->Per slot 1000tk\t\t15:30-20:00--->Per slot 1300tk\n");
        }
        if(i==2)
        {
            printf("Slot price: 8:00-15:30--->Per slot 1000tk\t\t15:30-20:00--->Per slot 1300tk\n");
        }
        if(i==3)
        {
            printf("Slot price: 8:00-15:30--->Per slot 1500tk\t\t15:30-20:00--->Per slot 2000tk\n");
        }
        if(i==4)
        {
            printf("Slot price: 8:00-15:30--->Per slot 1300tk\t\t15:30-20:00--->Per slot 1800tk\n");
        }
        if(i==5)
        {
            printf("Slot price: 8:00-15:30--->Per slot 1000tk\t\t15:30-20:00--->Per slot 1300tk\n");
        }
        if(i==6)
        {
            printf("Slot price: 8:00-15:30--->Per slot 1000tk\t\t15:30-20:00--->Per slot 1300tk\n");
        }
        if(i==7)
        {
            printf("Slot price: 8:00-15:30--->Per slot 800tk\t\t15:30-20:00--->Per slot 1200tk\n");
        }
        if(i==8)
        {
            printf("Slot price: 8:00-15:30--->Per slot 1000tk\t\t15:30-20:00--->Per slot 1300tk\n");
        }
        if(i==9)
        {
            printf("Slot price: 8:00-15:30--->Per slot 1000tk\t\t15:30-20:00--->Per slot 1300tk\n");
        }
    }
}

void readTurfDataFromFile() {
  // printf("jhdvs");
    FILE *file = fopen("turfs.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < Total_TURFS; ++i) {
        fscanf(file, "%s %s\n", turfs[i].name, turfs[i].location);

    }

    fclose(file);

}



    void writeTurfDataToFile() {
    FILE *file = fopen("turfs.txt", "w");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < Total_TURFS; ++i) {


       // scanf("%s %s %s %d\n", turfs[i].name, turfs[i].location, turfs[i].timeSlots, turfs[i].isBooked);

        fprintf(file, "%s %s \n", turfs[i].name, turfs[i].location);
    }

    fclose(file);
}

  struct login{
    char first_name[100];
    char last_name[100];
    char username[100];
    char password[100];
};
//login function
   login()
     {

         int cheak=0;
         char username[100];
         char password[100];

         FILE*log;
         log=fopen("login12.txt", "r");
         struct login l;
         printf("Enter your USER ID: ");
         scanf("%s", username);
         printf("\n\nEnter your password: ");
         scanf("%s", password);




         while(fread(&l,sizeof(l),1,log))
         {
             if(strcmp(username,l.username)==0 && strcmp(password,l.password)==0)
             {
                 printf("\n\t\t------S1uccesfully login------");
                 cheak=1;
                 strcpy(booking_username,username);
                 break;
             }
            /* else if(feof(log))
             {
                  printf("\nPlease enter correct USER ID and password");

             }*/

         }
           int choice;

     //Menu option after login
           if(cheak==1){
    do {
        printf("\nMenu:\n");
        printf("\t\t1. Display all turfs\n");
        printf("\t\t2. Book or cancel turf\n");
        printf("\t\t3. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAllTurfs();
                break;
            case 2:
                book();
                break;
            case 3:
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);

    writeTurfDataToFile();


    printf("\n\t\t\t--------WELLCOME--------");
    getch();
         }

        else if(cheak==0)
         {
              printf("\nPlease enter correct USER ID and password");
         }
        }
// Function for create id
        create()
     {
         FILE * log;
         log = fopen("login12.txt", "a");
         struct login l;

         printf("Enter your first name: ");
         scanf("%s", l.first_name);
         printf("\n\nEnter your last name: ");
         scanf("%s", l.last_name);
         printf("\n\nEnter a username: ");
         scanf("%s", l.username);
         printf("\n\nEnter password: ");
         scanf("%s", l.password);
         fwrite(&l,sizeof(l),1,log);

         fclose(log);

         printf("\n\nYour user name is USER ID ");
         printf("\n\nNow login with your USER ID and password");
         printf("\n\n------Press any key to continue------\n\n");
         getch();
         login();
     }



int main()
{

    readTurfDataFromFile();

    int choice;
     printf("------Press '1' for CREATE ID------ \n\n------Press '2' for LOGIN ID------\n\n");
         scanf("%d",&choice);
         if(choice==1)
         {
             create();
         }
         else if(choice==2)
         {
             login();
         }
         else
         {
             printf("------>You input wrong number<-----");
         }


    return 0;


}


