#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<windows.h>
#include "Header.h"

int choice;

/*read the binary file first and save into a structure array for further function*/
int read_schedule() {
    FILE* fptr;
    fptr = fopen("schedule.dat", "rb");
    if (fptr == NULL) {
        printf("Error opening the file.\n");
        exit(-1);
    }

    int scheduleCount = 0;
    while (fread(&trainSchedule[scheduleCount], sizeof(schedule), 1, fptr) == 1 && scheduleCount < MAX_SCHEDULE) {
        if (strlen(trainSchedule[scheduleCount].scheduleID) > 0) {
            scheduleCount++;
        }
    }
    fclose(fptr);
    return (scheduleCount);

}

void display_schedule() {
    SYSTEMTIME time;
    GetLocalTime(&time);
    printf("============================================================================================================================================================\n");
    printf("\t\t\t\t\t\t\t\tTrain Schedule \t\t\t\t\t\t\t\t  %d/%d/%d  %02d:%02d", time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute);
    printf(" \n");
    printf("============================================================================================================================================================\n");
    printf("%-12s %-12s%-8s %-11s%-20s %-20s%-15s %-15s %-18s %-15s\n",
        "Schedule ID", "Date", "Train ID", "Staff ID", "Departure State", "Arrival State", "Departure Time", "Arrival Time", "Ticket Price(RM)", "Available Seats");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < MAX_SCHEDULE; i++) {
        if (strlen(trainSchedule[i].scheduleID) > 0) {
            printf("%-12s %02d/%02d/%d  %-8s %-11s%-20s %-20s",
                trainSchedule[i].scheduleID, trainSchedule[i].day, trainSchedule[i].month, trainSchedule[i].year, trainSchedule[i].trainID, trainSchedule[i].staffID, trainSchedule[i].departState, trainSchedule[i].arriveState);

            if (trainSchedule[i].departTime != 0) {
                printf("%-15d ", trainSchedule[i].departTime);
            }
            else {
                printf(" ");
            }

            if (trainSchedule[i].arriveTime != 0) {
                printf("%-15d ", trainSchedule[i].arriveTime);
            }
            else {
                printf(" ");
            }

            if (trainSchedule[i].price != 0) {
                printf("%-18d ", trainSchedule[i].price);
            }
            else {
                printf(" ");
            }

            if (trainSchedule[i].seat != 0) {
                printf("%-15d\n", trainSchedule[i].seat);
            }
            else {
                printf(" \n");
            }
        }
    }
    printf(" \n");
}

void add_schedule() {
    schedule new_schedule;
    FILE* fptr;

    fptr = fopen("schedule.dat", "ab");
    if (fptr == NULL) {
        printf("Error opening the file.\n");
        exit(-1);
    }

    printf("\033[H\033[J");     // CLS

    printf(
        "===========================================================================================================================================================\n"
        "                                                                    ADD TRAIN SCHEDULE                                                                     \n"
        "===========================================================================================================================================================\n\n"
    );

    printf("Enter Schedule ID (e.g. TS001): ");
    (void)scanf("%s", &new_schedule.scheduleID);
    strcpy(_strupr(new_schedule.scheduleID), new_schedule.scheduleID);
    /*check the schedule id format and repeated schedule id*/
    if (strlen(new_schedule.scheduleID) != 5 || strncmp(new_schedule.scheduleID, "TS", 2) != 0) {
        printf("Invalid Schedule ID Entered.\n");
        printf("Enter Schedule ID (e.g. TS001): ");
        scanf("%s", &new_schedule.scheduleID);
        strcpy(_strupr(new_schedule.scheduleID), new_schedule.scheduleID);
    }
    for (int i = 0; i < MAX_SCHEDULE; i++) {
        if (strcmp(trainSchedule[i].scheduleID, new_schedule.scheduleID) == 0) {
            printf("The Schedule ID Already Exists.\n");
            printf("Enter Schedule ID (e.g. TS001): ");
            scanf("%s", &new_schedule.scheduleID);
            strcpy(_strupr(new_schedule.scheduleID), new_schedule.scheduleID);
        }
    }

    rewind(stdin);
    printf("Date (dd/mm/yyyy)      : ");
    (void)scanf("%d/%d/%d", &new_schedule.day, &new_schedule.month, &new_schedule.year);
    /*check the date*/
    if ((new_schedule.month % 2 == 0 && (new_schedule.day < 1 || new_schedule.day > 30)) ||
        (new_schedule.month % 2 != 0 && (new_schedule.day < 1 || new_schedule.day > 31))) {
        printf("Invalid Date Entered. Please re-enter (dd/mm/yyyy): ");
        (void)scanf("%d/%d/%d", &new_schedule.day, &new_schedule.month, &new_schedule.year);
    }
    rewind(stdin);
    printf("Enter Train ID (T01-T08) : ");
    scanf("%s", &new_schedule.trainID);
    strcpy(_strupr(new_schedule.trainID), new_schedule.trainID);
    if (strlen(new_schedule.trainID) != 3 || new_schedule.trainID[0] != 'T' ||
        new_schedule.trainID[2] < '0' || new_schedule.trainID[2] > '8' || !isdigit(new_schedule.trainID[2])) {
        printf("Invalid Schedule ID Entered.\nPlease re-enter train id: ");
        scanf("%s", new_schedule.trainID);
        strcpy(_strupr(new_schedule.trainID), new_schedule.trainID);
    }
    rewind(stdin);
    printf("Enter Staff ID         : ");
    (void)scanf("%s", &new_schedule.staffID);
    strcpy(_strupr(new_schedule.staffID), new_schedule.staffID);
    rewind(stdin);
    printf("Enter Departure State  : ");
    (void)scanf("%[^\n]", &new_schedule.departState);
    rewind(stdin);
    printf("Enter Arrival State    : ");
    (void)scanf("%[^\n]", &new_schedule.arriveState);
    rewind(stdin);
    printf("Enter Departure Time   : ");
    (void)scanf("%d", &new_schedule.departTime);
    rewind(stdin);
    printf("Enter Arrival Time     : ");
    (void)scanf("%d", &new_schedule.arriveTime);
    rewind(stdin);
    printf("Enter Ticket Price(RM) : ");
    (void)scanf("%d", &new_schedule.price);
    rewind(stdin);
    printf("Enter Available Seats  : ");
    (void)scanf("%d", &new_schedule.seat);

    fwrite(&new_schedule, sizeof(schedule), 1, fptr);

    fclose(fptr);


    read_schedule();

    rewind(stdin);
    printf("\n\nNew schedule added successfully. ");
    (void)getchar();

    adminMenu();


}

void search_schedule() {
    char scheduleID[10];
    printf("=========================================================================================================================\n");
    printf("                                                 SEARCH TRAIN SCHEDDULE                                                  \n");
    printf("=========================================================================================================================\n");
    printf("Enter Schedule ID to search(e.g. TS001): ");
    (void)scanf(" %s", &scheduleID);
    strcpy(_strupr(scheduleID), scheduleID);

    int i;
    int result = -1; /*initialize result to - 1 first(indicating not found)*/

    for (i = 0; i < MAX_SCHEDULE; i++) {
        if (strcmp(trainSchedule[i].scheduleID, scheduleID) == 0) { /*loop to string compare the schedule ID*/
            result = i;
            break;
        }
    }

    if (result != -1) {
        printf("\n");
        printf("=======================================\n");
        printf("Schedule found!\n");
        printf("----------------------------------------\n");
        printf("Schedule ID         : %s\n", trainSchedule[result].scheduleID);
        printf("Date                : %d/%d/%d\n", trainSchedule[result].day, trainSchedule[result].month, trainSchedule[result].year);
        printf("Train ID            : %s\n", trainSchedule[result].trainID);
        printf("Staff ID            : %s\n", trainSchedule[result].staffID);
        printf("Departure State     : %s\n", trainSchedule[result].departState);
        printf("Arrival State       : %s\n", trainSchedule[result].arriveState);
        printf("Departure Time      : %04d\n", trainSchedule[result].departTime);
        printf("Arrival Time        : %04d\n", trainSchedule[result].arriveTime);
        printf("Ticket Price(RM)    : %d\n", trainSchedule[result].price);
        printf("Available Seats     : %d\n", trainSchedule[result].seat);
        printf("=======================================\n");
        printf("\n");
    }
    else {
        printf("\n");
        printf("Result %s not found.\n", scheduleID);
        printf("\n");
    }
}

void modify_schedule() {
    char scheduleID[10];

    printf("\033[H\033[J");     // CLS

    printf(
        "===========================================================================================================================================================\n"
        "                                                                 MODIFY TRAIN SCHEDULE                                                                     \n"
        "===========================================================================================================================================================\n\n"
    );
    printf("Enter Schedule ID to modify (e.g. TS001): ");
    (void)scanf("%s", scheduleID);
    strcpy(_strupr(scheduleID), scheduleID);
    int i;
    int result = -1;
    for (i = 0; i < MAX_SCHEDULE; i++) {
        if (strcmp(trainSchedule[i].scheduleID, scheduleID) == 0) {
            result = i;
            break;
        }
    }

    if (result != -1) {
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("Schedule found! Enter new details:\n");
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("Date (dd/mm/yyyy)  : ");
        (void)scanf("%d/%d/%d", &trainSchedule[result].day, &trainSchedule[result].month, &trainSchedule[result].year);
        /*check the date*/
        if ((trainSchedule[result].month % 2 == 0 && (trainSchedule[result].day < 1 || trainSchedule[result].day > 30)) ||
            (trainSchedule[result].month % 2 != 0 && (trainSchedule[result].day < 1 || trainSchedule[result].day > 31))) {
            printf("Invalid Date Entered. Please re-enter (dd/mm/yyyy): ");
            (void)scanf("%d/%d/%d", &trainSchedule[result].day, &trainSchedule[result].month, &trainSchedule[result].year);
        }
        rewind(stdin);
        printf("Enter New Train ID (T01-T08) : ");
        scanf("%s", &trainSchedule[result].trainID);
        strcpy(_strupr(trainSchedule[result].trainID), trainSchedule[result].trainID);
        if (strlen(trainSchedule[result].trainID) != 3 ||
            trainSchedule[result].trainID[0] != 'T' ||
            (trainSchedule[result].trainID[2] < '0' || trainSchedule[result].trainID[2] > '8') ||
            !isdigit(trainSchedule[result].trainID[2])) {
            printf("Invalid Schedule ID Entered.\nPlease re-enter train id: ");
            scanf("%s", trainSchedule[result].trainID);
            strcpy(_strupr(trainSchedule[result].trainID), trainSchedule[result].trainID);
        }
        rewind(stdin);
        printf("Staff ID         : ");
        (void)scanf("%s", &trainSchedule[result].staffID);
        strcpy(_strupr(trainSchedule[result].staffID), trainSchedule[result].staffID);
        rewind(stdin);
        printf("Departure State    : ");
        (void)scanf("%[^\n]", &trainSchedule[result].departState);
        rewind(stdin);
        printf("Arrival State      : ");
        (void)scanf("%[^\n]", &trainSchedule[result].arriveState);
        rewind(stdin);
        printf("Departure Time     : ");
        (void)scanf("%d", &trainSchedule[result].departTime);
        rewind(stdin);
        printf("Arrival Time       : ");
        (void)scanf("%d", &trainSchedule[result].arriveTime);
        rewind(stdin);
        printf("Ticket Price(RM)   : ");
        (void)scanf("%d", &trainSchedule[result].price);
        rewind(stdin);
        printf("Available Seats    : ");
        (void)scanf("%d", &trainSchedule[result].seat);
        rewind(stdin);

        printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("Schedule modified successfully.");

        FILE* fptr;
        fptr = fopen("schedule.dat", "wb");
        if (fptr == NULL) {
            printf("Error opening the file.\n");

        }
        fwrite(trainSchedule, sizeof(schedule), MAX_SCHEDULE, fptr);
        fclose(fptr);

        (void)getchar();
        adminMenu();

    }
    else {
        rewind(stdin);
        printf("\n");
        printf("Result \"%s\" Schedule ID not found.\n", scheduleID);
        printf("Press Enter to Return to Menu! ");
        (void)getchar();

        adminMenu();
    }

}

void delete_schedule() {
    char ans;
    char scheduleID[10];

    printf("\033[H\033[J");     // CLS

    printf(
        "===========================================================================================================================================================\n"
        "                                                                REMOVE TRAIN SCHEDULE                                                                      \n"
        "===========================================================================================================================================================\n\n"
    );
    printf("\nEnter Schedule ID to delete (e.g. TS001): ");
    (void)scanf("%s", scheduleID);
    strcpy(_strupr(scheduleID), scheduleID);
    rewind(stdin);
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Are you sure to delete the schedule? (yes - y, no - n): ");
    (void)scanf(" %c", &ans);
    rewind(stdin);

    if (toupper(ans) == 'Y') {
        int i;
        int result = -1;
        for (i = 0; i < MAX_SCHEDULE; i++) {
            if (strcmp(trainSchedule[i].scheduleID, scheduleID) == 0) {
                result = i;
                break;
            }
        }
        if (result != -1) {
            strcpy(trainSchedule[result].scheduleID, "");
            trainSchedule[result].day = 0;
            trainSchedule[result].month = 0;
            trainSchedule[result].year = 0;
            strcpy(trainSchedule[result].trainID, "");
            strcpy(trainSchedule[result].staffID, "");
            strcpy(trainSchedule[result].departState, "");
            strcpy(trainSchedule[result].arriveState, "");
            trainSchedule[result].departTime = 0;
            trainSchedule[result].arriveTime = 0;
            trainSchedule[result].price = 0;
            trainSchedule[result].seat = 0;

            printf("\nSchedule with ID %s deleted successfully.", scheduleID);
            FILE* fptr;
            fptr = fopen("schedule.dat", "wb");
            if (fptr == NULL) {
                printf("Error opening the file.\n");
            }
            fwrite(trainSchedule, sizeof(schedule), MAX_SCHEDULE, fptr);
            fclose(fptr);

            read_schedule();
        }
        else {
            printf("\nSchedule with ID %s not found.\n", scheduleID);
        }
    }
    else if (toupper(ans) == 'N') {
        printf("\nDeletion cancel.");
    }
    else {
        printf("\nInvalid input. Deletion cancelled.");
    }

    printf("\nEnter to Return. ");
    (void)getchar();
    adminMenu();
}

void sort_schedule() {
    int i, j;
    schedule temp;
    int choice;
    printf("Sort by:\n");
    printf("1. Train ID\n");
    printf("2. Date\n");
    printf("3. Schedule ID\n");
    printf("Enter your choice: ");
    (void)scanf("%d", &choice);

    if (choice == 1) { /*sorting by train id*/
        for (i = 0; i < MAX_SCHEDULE - 1; i++) {
            for (j = 0; j < MAX_SCHEDULE - i - 1; j++) {
                /*compare the Train ID which one greater*/
                if (strcmp(trainSchedule[j].trainID, trainSchedule[j + 1].trainID) > 0) {
                    temp = trainSchedule[j];
                    trainSchedule[j] = trainSchedule[j + 1];
                    trainSchedule[j + 1] = temp;
                }
            }
        }
    }
    else if (choice == 2) { /*sorting by date*/
        for (i = 0; i < MAX_SCHEDULE - 1; i++) {
            for (j = 0; j < MAX_SCHEDULE - i - 1; j++) {
                /*compare the year fis*/
                if (trainSchedule[j].year > trainSchedule[j + 1].year ||
                    /*if year same, den compare the month*/
                    (trainSchedule[j].year == trainSchedule[j + 1].year && trainSchedule[j].month > trainSchedule[j + 1].month) ||
                    /*if year & month same, den compare the day*/
                    (trainSchedule[j].year == trainSchedule[j + 1].year && trainSchedule[j].month == trainSchedule[j + 1].month && trainSchedule[j].day > trainSchedule[j + 1].day)) {
                    temp = trainSchedule[j];
                    trainSchedule[j] = trainSchedule[j + 1];
                    trainSchedule[j + 1] = temp;
                }
            }
        }
    }
    else if (choice == 3) { /*sorting by scheduleID*/
        for (i = 0; i < MAX_SCHEDULE - 1; i++) {
            for (j = 0; j < MAX_SCHEDULE - i - 1; j++) {
                /*compare the scheduleID which one greater*/
                if (strcmp(trainSchedule[j].scheduleID, trainSchedule[j + 1].scheduleID) > 0) {
                    temp = trainSchedule[j];
                    trainSchedule[j] = trainSchedule[j + 1];
                    trainSchedule[j + 1] = temp;
                }
            }
        }
    }

    printf("\nSorted Schedule:\n");
    display_schedule();
}


void menu_schedule() {
    int choice;

    read_schedule();

    do {
        printf("Menu:\n");
        printf("1. Display Existing schedule\n");
        printf("2. Sort schedule\n");
        printf("3. Search for a schedule\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        (void)scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("\033[H\033[J");
            display_schedule();
            break;
        case 2:
            printf("\033[H\033[J");
            sort_schedule();
            break;
        case 3:
            printf("\033[H\033[J");
            search_schedule();
            break;

        case 4:
            read_schedule();
            printf("\033[H\033[J");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);



    printf("Exiting...\n");
    (void)getchar();

    printf("\033[H\033[J");
    mainMenuFORMAT();
    mainMenuFUNCTION();

}

void main_schedule() {

    menu_schedule();
}