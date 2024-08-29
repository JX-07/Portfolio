#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Header.h"

SYSTEMTIME time;


char newTicketId[10];
int selectSeat = 0;
int ticketCount = 0;

void add_ticketBooking(char userID[USER_ID_FORMAT]) {

    printf("\033[H\033[J");     // CLS
    display_schedule();
    int j = 0;                      // LOOP GUIDE
    char trainSchedID[10];          // USER INPUT - TRAIN ID
    int selectNum = 0;              // SELECT GUIDE
    printf("Enter Current Location : ");
    (void)scanf("%[^\n]", promptSchedule.departState);
    rewind(stdin);
    printf("Enter Destination      : ");
    (void)scanf("%[^\n]", promptSchedule.arriveState);
    rewind(stdin);

    int matchingIndices[MAX_MATCHING_SCHEDULES]; // Array to store indices of matching schedules
    int numMatching = 0; // Counter for the number of matching schedules found

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(promptSchedule.departState, trainSchedule[i].departState) == 0 &&
            strcmp(promptSchedule.arriveState, trainSchedule[i].arriveState) == 0) {
            // Schedule found
            matchingIndices[numMatching++] = i; // Store index of matching schedule
        }
    }
    if (numMatching > 0) {
        // At least one matching schedule found
        printf("======================================================\n");
        printf("Available Time :\n");
        printf("------------------------------------------------------\n");
        for (int i = 0; i < numMatching; i++) {
            int index = matchingIndices[i];
            printf("%5s %-20s to %20s %8d to %8d\n", trainSchedule[index].scheduleID, trainSchedule[index].departState, trainSchedule[index].arriveState, trainSchedule[index].departTime, trainSchedule[index].arriveTime);
        }
        printf("======================================================\n");

        // Select Train Schedule
        printf("\nEnter Train Schedule ID : ");
        (void)scanf("%s", trainSchedID);
        rewind(stdin);

        selectNum = extractNumber(trainSchedID);
        printf("\n");

        printf("\033[H\033[J");

        // Display selected train information
        printf("\n======================================================\n");
        printf("\"%s\" Train Selected! Confirm Train Information.\n", trainSchedule[selectNum - 1].scheduleID);
        printf("======================================================\n");
        printf(
            "Train ID               : %s\n"
            "Date                   : %02d/%02d/%4d\n"
            "Departure State        : %s\n"
            "Arrival State          : %s\n"
            "Time                   : %d to %d\n"
            "Ticket Price           : %d\n"
            "Available Seat (left)  : %d\n",
            trainSchedule[selectNum - 1].trainID,
            trainSchedule[selectNum - 1].day, trainSchedule[selectNum - 1].month, trainSchedule[selectNum - 1].year,
            trainSchedule[selectNum - 1].departState,
            trainSchedule[selectNum - 1].arriveState,
            trainSchedule[selectNum - 1].departTime, trainSchedule[selectNum - 1].arriveTime,
            trainSchedule[selectNum - 1].price,
            trainSchedule[selectNum - 1].seat);
        printf("======================================================\n");
        char choice;
        int guide = 0;
        printf("Confirmation (Y/N) : ");
        (void)scanf("%c", &choice);
        rewind(stdin);

        do {
            if (choice == 'Y' || choice == 'y') {
                int trainselect = 0;
                trainselect = extractNumber(trainSchedule[selectNum - 1].trainID);
                seatSelection(trainselect);
                ticketIdGenerate(newTicketId);
                FILE* appenFPTR = fopen("ticketbooking.txt", "a");
                fprintf(appenFPTR, "%6s|%6s|%d/%d/%d|%s|%d|%.2lf|%s|%s\n",
                    newTicketId,
                    userID,
                    time.wDay, time.wMonth, time.wYear,
                    trainSchedID,
                    selectSeat,
                    (double)trainSchedule[selectNum - 1].price, "null", "Unpaid");
                guide = 1;
                fclose(appenFPTR);
            }
            else if (choice == 'N' || choice == 'n') {
                printf("\033[H\033[J");
                mainMenu();
                guide = 1;
            }
            else {
                printf("\nInvalid Choice! Please re-enter.\n\n");
                printf("Confirmation (Y/N) : ");
                (void)scanf("%c", &choice);
                rewind(stdin);
                guide = 0;

            }
        } while (guide == 0);
    }
    else {
        // No matching schedules found
        printf("\nNo Train Scheduled for %s to %s\n", promptSchedule.departState, promptSchedule.arriveState);
    }
    (void)getchar();
    memberMenu(userID);
}

void search_ticketBooking() {
    int found = 1; // LOOP GUIDE
    //HEADER
    printf("\033[H\033[J");     // CLS

    printf(
        "===========================================================================================================================================================\n"
        "                                                                   SEARCH TICKET BOOKING                                                                   \n"
        "===========================================================================================================================================================\n"
    );

    // PROMPT
    printf("\nEnter Ticket ID : ");
    (void)scanf("%10[^\n]", &userInput.ticket_id);
    rewind(stdin);
    printf("--------------------------------------------------------\n");

    // SEARCH
    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(userInput.ticket_id, ticketBooking[i].ticket_id) == 0) {

            printf(
                "Ticket ID          : %s\n"
                "Member ID          : %s\n"
                "Booking Date       : %d/%d/%d\n"
                "Train Schedule ID  : %s\n"
                "Seat Number        : %d\n"
                "Price              : %.2lf\n"
                "Payment Method     : %s\n"
                "Payment Status     : %s\n",
                ticketBooking[i].ticket_id,
                ticketBooking[i].member_id,
                ticketBooking[i].booking_date.day, ticketBooking[i].booking_date.month, ticketBooking[i].booking_date.year,
                ticketBooking[i].trainScheduleID,
                ticketBooking[i].ticket_seat,
                ticketBooking[i].booking_payment.totalAmount,
                ticketBooking[i].booking_payment.paymentMethod,
                ticketBooking[i].booking_payment.paymentStatus);
            printf("--------------------------------------------------------\n");
            printf("%s found! Press Enter to Return.", userInput.ticket_id);
            found = 0;
        }

    } if(found == 1){
        printf("\nBooking Not Found! Press Enter to Return.");
    }
    (void)getchar();
    adminMenu();
    
}

void modify_ticketBooking(char userID[USER_ID_FORMAT]) {
    int loopGuide = 0; // Loop Guide
    char index[MAX_MATCHING_SCHEDULES] = { 0 };
    int k = 0;  // Store Modified Array Location
    int trainselect = 0;

    printf("\033[H\033[J");     // CLS

    printf(
        "===========================================================================================================================================================\n"
        "                                                                    MODIFY TICKET BOOKING                                                                  \n"
        "===========================================================================================================================================================\n"
    );

    printf("%10s %10s %8s %10s %8s   %-10s %10s %-20s\n",
        "Ticket ID", "Member ID", "Booking Date", "Schedule ID", "Seat Number", "Amount", "Payment Method", "Payment Status");

    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(userID, ticketBooking[i].member_id) == 0 && strcmp(ticketBooking[i].booking_payment.paymentStatus, "Unpaid") == 0) {

            printf("%10s %10s %2d/%2d/%4d %10s %8d %13.2lf %10s %15s\n",
                ticketBooking[i].ticket_id,
                ticketBooking[i].member_id,
                ticketBooking[i].booking_date.day, ticketBooking[i].booking_date.month, ticketBooking[i].booking_date.year,
                ticketBooking[i].trainScheduleID,
                ticketBooking[i].ticket_seat,
                ticketBooking[i].booking_payment.totalAmount,
                ticketBooking[i].booking_payment.paymentMethod,
                ticketBooking[i].booking_payment.paymentStatus);

            loopGuide = 1;
        }
    }
    if (loopGuide == 0) {
        printf("\nNo Booking Found! Press Enter to Return.");
        (void)getchar();
    }
    else if (loopGuide == 1) {
        printf("\nEnter Ticket ID to Modify : ");
        (void)scanf("%[^\n]", userInput.ticket_id);
        rewind(stdin);
        for(int i = 0; i < ticketCount ; i++)
        {
            if (strcmp(userInput.ticket_id, ticketBooking[i].ticket_id) == 0) {

                for (int j = 0; j < MAX_SCHEDULE; j++) {
                    if (strcmp(ticketBooking[i].trainScheduleID, trainSchedule[j].scheduleID) == 0 ) {

                        trainselect = extractNumber(trainSchedule[j].trainID);
                        seatSelection(trainselect);

                        ticketBooking[i].ticket_seat = selectSeat;

                    }
                }
            }
        }
        FILE* writeFPTR = fopen("ticketbooking.txt", "w");
        for (int i = 0; i < ticketCount; i++) {
            fprintf(writeFPTR, "%6s|%6s|%d/%d/%d|%s|%d|%.2lf|%s|%s\n", 
                ticketBooking[i].ticket_id,
                ticketBooking[i].member_id,
                ticketBooking[i].booking_date.day, ticketBooking[i].booking_date.month, ticketBooking[i].booking_date.year,
                ticketBooking[i].trainScheduleID,
                ticketBooking[i].ticket_seat,
                ticketBooking[i].booking_payment.totalAmount,
                ticketBooking[i].booking_payment.paymentMethod,
                ticketBooking[i].booking_payment.paymentStatus);
        }
        printf("\nTicket Seat Modified Succesfully!");
        (void)getchar();
    }   
    // RETURN TO MENU
    memberMenu(userID);
}

void read_ticketBooking() {
    ticketCount = 0;
    FILE* readFPTR = fopen("ticketbooking.txt", "r");

    while (
        fscanf(readFPTR, "%[^|]|%[^|]|%d/%d/%d|%[^|]|%d|%lf|%[^|]|%[^\n]\n",
            ticketBooking[ticketCount].ticket_id,
            ticketBooking[ticketCount].member_id,
            &ticketBooking[ticketCount].booking_date.day, &ticketBooking[ticketCount].booking_date.month, &ticketBooking[ticketCount].booking_date.year,
            ticketBooking[ticketCount].trainScheduleID,
            &ticketBooking[ticketCount].ticket_seat,
            &ticketBooking[ticketCount].booking_payment.totalAmount,
            ticketBooking[ticketCount].booking_payment.paymentMethod,
            ticketBooking[ticketCount].booking_payment.paymentStatus) != EOF) {
        ticketCount++;
    }
    fclose(readFPTR);
}

void displayAll_ticketBookingStaff() {

    // HEADER
        //HEADER
    printf("\033[H\033[J");     // CLS

    printf(
        "===========================================================================================================================================================\n"
        "                                                                DISPLAY ALL TICKET BOOKING                                                                 \n"
        "===========================================================================================================================================================\n"
    );

    // DISPLAY ALL
    printf("%s\t%s\t%s\t%s\t%s\t%s\t\t%s\t\t%s\n", "Ticket ID", "Member ID", "Booking Date", "Schedule ID", "Seat Number", "Amount", "Payment Method", "Payment Status");

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < ticketCount; i++) {
       

        printf("%s\t\t%s\t\t%d/%d/%d\t%s\t\t%d\t\t%.2lf\t\t%-20s\t%s\n",
            ticketBooking[i].ticket_id,
            ticketBooking[i].member_id,
            ticketBooking[i].booking_date.day, ticketBooking[i].booking_date.month, ticketBooking[i].booking_date.year,
            ticketBooking[i].trainScheduleID,
            ticketBooking[i].ticket_seat,
            ticketBooking[i].booking_payment.totalAmount,
            ticketBooking[i].booking_payment.paymentMethod,
            ticketBooking[i].booking_payment.paymentStatus);
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    printf("\n%d records displayed! Presse Enter to Return.", ticketCount);
    (void)getchar();

    // MAIN MENU
    adminMenu();
}

void displayAll_ticketBookingMember(char userID[USER_ID_FORMAT]) {

    // HEADER
        //HEADER
    printf("\033[H\033[J");     // CLS

    printf(
        "===========================================================================================================================================================\n"
        "                                                                DISPLAY ALL TICKET BOOKING                                                                 \n"
        "===========================================================================================================================================================\n"
    );

    // DISPLAY ALL
    printf("%s\t%s\t%s\t%s\t%s\t%s\t\t%s\t\t%s\n", "Ticket ID", "Member ID", "Booking Date", "Schedule ID", "Seat Number", "Amount", "Payment Method", "Payment Status");

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(userID, ticketBooking[i].member_id) == 0) {

            printf("%s\t\t%s\t\t%d/%d/%d\t%s\t\t%d\t\t%.2lf\t\t%-20s\t%s\n",
                ticketBooking[i].ticket_id,
                ticketBooking[i].member_id,
                ticketBooking[i].booking_date.day, ticketBooking[i].booking_date.month, ticketBooking[i].booking_date.year,
                ticketBooking[i].trainScheduleID,
                ticketBooking[i].ticket_seat,
                ticketBooking[i].booking_payment.totalAmount,
                ticketBooking[i].booking_payment.paymentMethod,
                ticketBooking[i].booking_payment.paymentStatus);
        }
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    printf("\n%d records displayed! Presse Enter to Return.", ticketCount);
    (void)getchar();

    // MAIN MENU
    memberMenu(userID);
}

void payment_ticketBooking(char userID[USER_ID_FORMAT]) {      // NOT YET DONE

    int j = 0;      // FOR INDEX
    int k = 0;      // FOR CHECKING PRESENCE OF DATA
    int select = 0; // TICKET SELECTION
    int payMed = 0;

    // HEADER
    printf("\033[H\033[J");     // CLS

    printf(
        "===========================================================================================================================================================\n"
        "                                                                      PAYMENT PROCESSING                                                                   \n"
        "===========================================================================================================================================================\n"
    );
    printf("%3s\t%s\t%s\t%s\t%s\t%s\t%s\t\t%s\t\t%s\n", "No.", "Ticket ID", "Member ID", "Booking Date", "Schedule ID", "Seat Number", "Amount", "Payment Method", "Payment Status");

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < ticketCount; i++) {

        if (strcmp(ticketBooking[i].member_id, userID) == 0 && strcmp(ticketBooking[i].booking_payment.paymentStatus, "Unpaid") == 0) {
            printf("%02d.\t%s\t\t%s\t\t%d/%d/%d\t%s\t\t%d\t\t%.2lf\t\t%-20s\t%s\n",
                ++j,
                ticketBooking[i].ticket_id,
                ticketBooking[i].member_id,
                ticketBooking[i].booking_date.day, ticketBooking[i].booking_date.month, ticketBooking[i].booking_date.year,
                ticketBooking[i].trainScheduleID,
                ticketBooking[i].ticket_seat,
                ticketBooking[i].booking_payment.totalAmount,
                ticketBooking[i].booking_payment.paymentMethod,
                ticketBooking[i].booking_payment.paymentStatus);
            k = 1;
        }
    }
    printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------");
    if (k == 0) {
        printf("\nNo Current Ticket Booking in-need of Payment!");
    }
    if (k == 1) {
        printf("\nEnter Ticket Booking ID to Pay : ");
        (void)scanf("%[^\n]", userInput.ticket_id);
        rewind(stdin);

        printf("-------------------------"
            "\n|(1) Cash                |"
            "\n|(2) E-Wallet            |"
            "\n|(3) Credit Card         |"
            "\n-------------------------");
        printf("\nSelect Payment Method :  ");
        (void)scanf("%d", &payMed);
        rewind(stdin);

        if (payMed < 0 || payMed > 3) {
            printf("\nInvalid Payment Method! Please Re-enter.");
            printf("\nSelect Payment Method :  ");
            (void)scanf("%d", &payMed);
            rewind(stdin);
        }
        else {
            printf("Payment Succesful!");
        }

        select = extractNumber(userInput.ticket_id);

        if (strlen(userInput.ticket_id) == USER_ID_FORMAT) {
            strcpy(userInput.ticket_id, _strupr(userInput.ticket_id));
            if (isalpha(userInput.ticket_id[0]) != 0 && isalpha(userInput.ticket_id[1]) != 0) {
                switch (payMed) {
                case 1:
                    strcpy(ticketBooking[select - 1].booking_payment.paymentMethod, "Cash");
                    break;
                case 2:
                    strcpy(ticketBooking[select - 1].booking_payment.paymentMethod, "E-Wallet");
                    break;
                case 3:
                    strcpy(ticketBooking[select - 1].booking_payment.paymentMethod, "Credit Card");
                    break;
                }
                strcpy(ticketBooking[select - 1].booking_payment.paymentStatus, "Paid");
            }
            for(int i = 0; i < ticketCount - 1; i++){
            FILE* writeFPTR = fopen("ticketbooking.txt", "w");
            for (int i = 0; i < ticketCount; i++) {
                fprintf(writeFPTR, "%s|%s|%d/%d/%d|%s|%d|%lf|%s|%s\n",
                    ticketBooking[i].ticket_id,
                    ticketBooking[i].member_id,
                    ticketBooking[i].booking_date.day, ticketBooking[i].booking_date.month, ticketBooking[i].booking_date.year,
                    ticketBooking[i].trainScheduleID,
                    ticketBooking[i].ticket_seat,
                    ticketBooking[i].booking_payment.totalAmount,
                    ticketBooking[i].booking_payment.paymentMethod,
                    ticketBooking[i].booking_payment.paymentStatus);
            }
            }
        }
    }
    (void)getchar();
    memberMenu(userID);

}

void cancel_ticketBooking(char userID[USER_ID_FORMAT]) {
    int j = 0;      // FOR INDEX
    int k = 0;      // FOR CHECKING PRESENCE OF DATA
    int select = 0; // TICKET SELECTION

    // HEADER
    printf("\033[H\033[J");     // CLS

    printf(
        "===========================================================================================================================================================\n"
        "                                                                   CANCEL TICKET BOOKING                                                                   \n"
        "===========================================================================================================================================================\n"
        "                                                   *Only Ticket Booking in \'Unpaid\' Status Can Be Cancelled*                                               \n"
        "-----------------------------------------------------------------------------------------------------------------------------------------------------------\n"
    );
    printf("%3s\t%s\t%s\t%s\t%s\t%s\t%s\t\t%s\t\t%s\n", "No.", "Ticket ID", "Member ID", "Booking Date", "Schedule ID", "Seat Number", "Amount", "Payment Method", "Payment Status");

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < ticketCount; i++) {

        if (strcmp(ticketBooking[i].member_id, userID) == 0 && strcmp(ticketBooking[i].booking_payment.paymentStatus, "Unpaid") == 0) {
            printf("%02d.\t%s\t\t%s\t\t%d/%d/%d\t%s\t\t%d\t\t%.2lf\t\t%-20s\t%s\n",
                ++j,
                ticketBooking[i].ticket_id,
                ticketBooking[i].member_id,
                ticketBooking[i].booking_date.day, ticketBooking[i].booking_date.month, ticketBooking[i].booking_date.year,
                ticketBooking[i].trainScheduleID,
                ticketBooking[i].ticket_seat,
                ticketBooking[i].booking_payment.totalAmount,
                ticketBooking[i].booking_payment.paymentMethod,
                ticketBooking[i].booking_payment.paymentStatus);
            k = 1;
        }
    }
    printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    if (k == 0) {
        printf("\nNo Record Found! Make Sure the Status must be \'Unpaid\' to be able to Cancel!");
    }
    else if (k == 1)
    {
            printf("\nEnter Ticket Booking ID to Remove : ");
            (void)scanf("%[^\n]", userInput.ticket_id);
            rewind(stdin);

            select = extractNumber(userInput.ticket_id);

            if (strlen(userInput.ticket_id) == USER_ID_FORMAT) {
                strcpy(userInput.ticket_id, _strupr(userInput.ticket_id));
                if (isalpha(userInput.ticket_id[0]) != 0 && isalpha(userInput.ticket_id[1]) != 0) {
                    for (int i = select - 1; i < ticketCount; i++) {
                        ticketBooking[i] = ticketBooking[i + 1];
                    }

                    FILE* writeFPTR = fopen("ticketbooking.txt", "w");
                    for (int i = 0; i < ticketCount - 1; i++) {
                        fprintf(writeFPTR, "%s|%s|%d/%d/%d|%s|%d|%lf|%s|%s\n",
                            ticketBooking[i].ticket_id,
                            ticketBooking[i].member_id,
                            ticketBooking[i].booking_date.day, ticketBooking[i].booking_date.month, ticketBooking[i].booking_date.year,
                            ticketBooking[i].trainScheduleID,
                            ticketBooking[i].ticket_seat,
                            ticketBooking[i].booking_payment.totalAmount,
                            ticketBooking[i].booking_payment.paymentMethod,
                            ticketBooking[i].booking_payment.paymentStatus);
                    }
                    printf("\n%s Ticket Booking Cancelled Succesfully!", userInput.ticket_id);
                }
                else {
                    printf("\nInput Incorrect Format!");
                }
            }
            else {
                printf("\nInput Incorrect Length Size!");
            }

    }

    // Return To Menu
    (void)getchar();
    memberMenu(userID);
}

void generate_ticketReport() {
    int scheduleCount = 0;

    scheduleCount = read_schedule();


    printf("\033[H\033[J");
    printf("=========================================================================================================================\n");
    printf("                                             GENERATE TICKET SALES REPORT                                                \n");
    printf("=========================================================================================================================\n");

    int trainIdCount[8] = { 0 };
    double trainProfit[8] = { 0.0 };
    int sumCount = 0;
    double sumProfit = 0.0;

    for (int i = 0; i < ticketCount; i++) {
        for (int j = 0; j < scheduleCount; j++) {

            if (strcmp(ticketBooking[i].trainScheduleID, trainSchedule[j].scheduleID) == 0 && strcmp(ticketBooking[i].booking_payment.paymentStatus, "Paid") == 0) {
                int counting = 0;
                counting = extractNumber(trainSchedule[j].trainID);

                switch (counting) {
                case 1:
                    trainIdCount[0]++;
                    trainProfit[0] += trainSchedule[j].price;
                    break;
                case 2:
                    trainIdCount[1]++;
                    trainProfit[1] += trainSchedule[j].price;
                    break;
                case 3:
                    trainIdCount[2]++;
                    trainProfit[2] += trainSchedule[j].price;
                    break;
                case 4:
                    trainIdCount[3]++;
                    trainProfit[3] += trainSchedule[j].price;
                    break;
                case 5:
                    trainIdCount[4]++;
                    trainProfit[4] += trainSchedule[j].price;
                    break;
                case 6:
                    trainIdCount[5]++;
                    trainProfit[5] += trainSchedule[j].price;
                    break;
                case 7:
                    trainIdCount[6]++;
                    trainProfit[6] += trainSchedule[j].price;
                    break;
                case 8:
                    trainIdCount[7]++;
                    trainProfit[7] += trainSchedule[j].price;
                    break;
                }
            }
        }
    }
    printf("---------- + ---------------- + ------------------+\n");
    printf("|Train ID  | Schedule Count   |      Profit       |\n");
    printf("---------- + ---------------- + ------------------+\n");
    for (int i = 0; i < 8; i++) {
        printf("|  T0%d     |%12d      |    RM%8.2lf     |\n", i + 1, trainIdCount[i], trainProfit[i]);
        sumCount += trainIdCount[i];
        sumProfit += trainProfit[i];
    }
    printf("---------- + ---------------- + ------------------+\n");
    printf("|Total     |  %12d    |    RM%8.2lf     |\n", sumCount, sumProfit);
    printf("---------- + ---------------- + ------------------+\n");
    printf("|Average Profit :  %.2lf                          |\n", sumProfit / (double)sumCount);
    printf("--------------------------------------------------+\n");
    printf("Press Enter to Return to Menu.");
    (void)getchar();
    adminMenu();
}

void seatBooking() {
    printf("\nEnter Booking Seat : ");
    (void)scanf("%d", &selectSeat);
    rewind(stdin);
}

void seatSelection(int train) {
    switch (train) {
    case 1:
        seatSelectionCA();
        do {
            seatBooking();
            if (selectSeat > 90 || selectSeat < 1) {
                printf("\nInvalid Seat Selection! Please Re-enter.");
            }
            break;
        } while (selectSeat > 90 || selectSeat < 1);
        break;
    case 2:
        seatSelectionCAA();
        do {
            seatBooking();
            if (selectSeat > 180 || selectSeat < 1) {
                printf("\nInvalid Seat Selection! Please Re-enter.");
            }
            break;
        } while (selectSeat > 180 || selectSeat < 1);
        break;
    case 3:
        seatSelectionCB();
        do {
            seatBooking();
            if (selectSeat > 80 || selectSeat < 1) {
                printf("\nInvalid Seat Selection! Please Re-enter.");
            }
            break;
        } while (selectSeat > 80 || selectSeat < 1);
        break;
    case 4:
        seatSelectionCBB();
        do {
            seatBooking();
            if (selectSeat > 160 || selectSeat < 1) {
                printf("\nInvalid Seat Selection! Please Re-enter.");
            }
            break;
        } while (selectSeat > 160 || selectSeat < 1);
        break;
    case 5:
        seatSelectionCC();
        do {
            seatBooking();
            if (selectSeat > 72 || selectSeat < 1) {
                printf("\nInvalid Seat Selection! Please Re-enter.");
            }
            break;
        } while (selectSeat > 72 || selectSeat < 1);
        break;
    case 6:
        seatSelectionCCC();
        do {
            seatBooking();
            if (selectSeat > 144 || selectSeat < 1) {
                printf("\nInvalid Seat Selection! Please Re-enter.");
            }
            break;
        } while (selectSeat > 144 || selectSeat < 1);
        break;
    case 7:
        seatSelectionCD();
        do {
            seatBooking();
            if (selectSeat > 24 || selectSeat < 1) {
                printf("\nInvalid Seat Selection! Please Re-enter.");
            }
            break;
        } while (selectSeat > 24 || selectSeat < 1);
        break;
    case 8:
        seatSelectionCDD();
        do {
            seatBooking();
            if (selectSeat > 48 || selectSeat < 1) {
                printf("\nInvalid Seat Selection! Please Re-enter.");
            }
            break;
        } while (selectSeat > 48 || selectSeat < 1);
        break;
    }
    printf("\nBooking Succesfully Added!");
}

void seatSelectionCA()
{
    printf("\033[H\033[J");     // CLS
    // COACH A (90 PAX)
    int i = 0;
    printf(
        "==========================================================================================\n"
        "| SEAT SELECTION | TRAIN ID : T01 | COACH : A           \n"
        "==========================================================================================\n"
    );
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    for (int row = 0; row < 15; row++) {                // Print 3 Seat Section
        printf("-------------------------");
        printf("%-9s", " ");
        printf("-------------------------\n");
        if (row == 4 || row == 12) {
            printf("+%57s+\n", " ");
            printf("-------------------------");
            printf("%-9s", " ");
            printf("-------------------------\n");
        }
        for (int col = 0; col < 3; col++)
        {
            printf("|  %03d  ", ++i);            // To print the LEFT seats
        }
        printf("%-10s", "|");
        for (int col = 0; col < 3; col++)
        {
            printf("|  %03d  ", ++i);            // To print the RIGHT seats
        }
        printf("|\n");
    }
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    printf("==========================================================================================\n");


}

void seatSelectionCAA()
{
    // COACH A (180 PAX)
    int i = 0;
    printf("\033[H\033[J");
    printf(
        "==========================================================================================\n"
        "| SEAT SELECTION | TRAIN ID : T02 | COACH : A           \n"
        "==========================================================================================\n"
    );
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    for (int row = 0; row < 15; row++) {                // Print 3 Seat Section
        printf("-------------------------");
        printf("%-9s", " ");
        printf("-------------------------\n");
        if (row == 4 || row == 12) {
            printf("+%57s+\n", " ");
            printf("-------------------------");
            printf("%-9s", " ");
            printf("-------------------------\n");
        }
        for (int col = 0; col < 3; col++)
        {
            printf("|  %03d  ", ++i);            // To print the LEFT seats
        }
        printf("%-10s", "|");
        for (int col = 0; col < 3; col++)
        {
            printf("|  %03d  ", ++i);            // To print the RIGHT seats
        }
        printf("|\n");
    }
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");

    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    for (int row = 0; row < 15; row++) {                // Print 3 Seat Section
        printf("-------------------------");
        printf("%-9s", " ");
        printf("-------------------------\n");
        if (row == 4 || row == 12) {
            printf("+%57s+\n", " ");
            printf("-------------------------");
            printf("%-9s", " ");
            printf("-------------------------\n");
        }
        for (int col = 0; col < 3; col++)
        {
            printf("|  %03d  ", ++i);            // To print the LEFT seats
        }
        printf("%-10s", "|");
        for (int col = 0; col < 3; col++)
        {
            printf("|  %03d  ", ++i);            // To print the RIGHT seats
        }
        printf("|\n");
    }
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");

    printf("==========================================================================================\n");


}

void seatSelectionCB() {

    // COACH B (80  PAX)
    int i = 0;
    printf("\033[H\033[J");
    printf(
        "==========================================================================================\n"
        "| SEAT SELECTION | TRAIN ID : T03 | COACH : B           \n"
        "==========================================================================================\n"
    );

    for (int row = 0; row < 12; row++) {
        if (row == 0) {                                // To Print 1st Row of Seat
            printf("-------------------------");
            printf("%-9s", " ");
            printf("-------------------------\n");
            for (int col = 0; col < 2; col++)
            {
                printf("|  %03d  ", ++i);            // To print the LEFT seats
            }
            printf("%-26s", "|");
            for (int col = 0; col < 2; col++)
            {
                printf("|  %03d  ", ++i);            // To print the RIGHT seats
            }
            printf("|\n");
            printf("-----------------");
            printf("%-5s%15s%5s", " ", "---------------", " ");
            printf("-----------------\n");
        }
        if (row == 6) {
            printf("+%57s+\n", " ");
            printf("-----------------");
            printf("%-5s%15s%5s", " ", "---------------", " ");
            printf("-----------------\n");
        }
        for (int col = 0; col < 2; col++)
        {
            printf("|  %03d  ", ++i);            // To print the LEFT seats
        }
        printf("%-5s", "|");
        for (int col = 0; col < 2; col++) {
            printf("|  %03d  ", ++i);
        }
        printf("%-5s", "|");
        for (int col = 0; col < 2; col++)
        {
            printf("|  %03d  ", ++i);            // To print the RIGHT seats
        }
        printf("|\n");
        printf("-----------------");
        printf("%-5s%15s%5s", " ", "---------------", " ");
        printf("-----------------\n");

        if (row == 11) {                                // To Print 1st Row of Seat

            for (int col = 0; col < 2; col++)
            {
                printf("|  %03d  ", ++i);            // To print the LEFT seats
            }
            printf("%-26s", "|");
            for (int col = 0; col < 2; col++)
            {
                printf("|  %03d  ", ++i);            // To print the RIGHT seats
            }
            printf("|\n");
            printf("-------------------------");
            printf("%-9s", " ");
            printf("-------------------------\n");
        }
    }


    printf("==========================================================================================\n");


}

void seatSelectionCBB() {

    // COACH B (160  PAX)
    int i = 0;
    printf("\033[H\033[J");
    printf(
        "==========================================================================================\n"
        "| SEAT SELECTION | TRAIN ID : T04 | COACH : B           \n"
        "==========================================================================================\n"
    );

    for (int row = 0; row < 12; row++) {
        if (row == 0) {                                // To Print 1st Row of Seat
            printf("-------------------------");
            printf("%-9s", " ");
            printf("-------------------------\n");
            for (int col = 0; col < 2; col++)
            {
                printf("|  %03d  ", ++i);            // To print the LEFT seats
            }
            printf("%-26s", "|");
            for (int col = 0; col < 2; col++)
            {
                printf("|  %03d  ", ++i);            // To print the RIGHT seats
            }
            printf("|\n");
            printf("-----------------");
            printf("%-5s%15s%5s", " ", "---------------", " ");
            printf("-----------------\n");
        }
        if (row == 6) {
            printf("+%57s+\n", " ");
            printf("-----------------");
            printf("%-5s%15s%5s", " ", "---------------", " ");
            printf("-----------------\n");
        }
        for (int col = 0; col < 2; col++)
        {
            printf("|  %03d  ", ++i);            // To print the LEFT seats
        }
        printf("%-5s", "|");
        for (int col = 0; col < 2; col++) {
            printf("|  %03d  ", ++i);
        }
        printf("%-5s", "|");
        for (int col = 0; col < 2; col++)
        {
            printf("|  %03d  ", ++i);            // To print the RIGHT seats
        }
        printf("|\n");
        printf("-----------------");
        printf("%-5s%15s%5s", " ", "---------------", " ");
        printf("-----------------\n");

        if (row == 11) {                                // To Print 1st Row of Seat

            for (int col = 0; col < 2; col++)
            {
                printf("|  %03d  ", ++i);            // To print the LEFT seats
            }
            printf("%-26s", "|");
            for (int col = 0; col < 2; col++)
            {
                printf("|  %03d  ", ++i);            // To print the RIGHT seats
            }
            printf("|\n");
            printf("-------------------------");
            printf("%-9s", " ");
            printf("-------------------------\n");
        }
    }    for (int row = 0; row < 12; row++) {
        if (row == 0) {                                // To Print 1st Row of Seat
            printf("-------------------------");
            printf("%-9s", " ");
            printf("-------------------------\n");
            for (int col = 0; col < 2; col++)
            {
                printf("|  %03d  ", ++i);            // To print the LEFT seats
            }
            printf("%-26s", "|");
            for (int col = 0; col < 2; col++)
            {
                printf("|  %03d  ", ++i);            // To print the RIGHT seats
            }
            printf("|\n");
            printf("-----------------");
            printf("%-5s%15s%5s", " ", "---------------", " ");
            printf("-----------------\n");
        }
        if (row == 6) {
            printf("+%57s+\n", " ");
            printf("-----------------");
            printf("%-5s%15s%5s", " ", "---------------", " ");
            printf("-----------------\n");
        }
        for (int col = 0; col < 2; col++)
        {
            printf("|  %03d  ", ++i);            // To print the LEFT seats
        }
        printf("%-5s", "|");
        for (int col = 0; col < 2; col++) {
            printf("|  %03d  ", ++i);
        }
        printf("%-5s", "|");
        for (int col = 0; col < 2; col++)
        {
            printf("|  %03d  ", ++i);            // To print the RIGHT seats
        }
        printf("|\n");
        printf("-----------------");
        printf("%-5s%15s%5s", " ", "---------------", " ");
        printf("-----------------\n");

        if (row == 11) {                                // To Print 1st Row of Seat

            for (int col = 0; col < 2; col++)
            {
                printf("|  %03d  ", ++i);            // To print the LEFT seats
            }
            printf("%-26s", "|");
            for (int col = 0; col < 2; col++)
            {
                printf("|  %03d  ", ++i);            // To print the RIGHT seats
            }
            printf("|\n");
            printf("-------------------------");
            printf("%-9s", " ");
            printf("-------------------------\n");
        }
    }

    printf("==========================================================================================\n");



}

void seatSelectionCC() {

    // COACH C (72 PAX)
    int i = 0;
    printf("\033[H\033[J");
    printf(
        "==========================================================================================\n"
        "| SEAT SELECTION | TRAIN ID : T05 | COACH : C           \n"
        "==========================================================================================\n"
    );
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    for (int row = 0; row < 12; row++) {                // 2 2 2 Seats

        if (row == 6)
        {
            printf("-------------------------");          // Line To seperate section of LEFT seats
            printf("%-9s", " ");
            printf("-------------------------\n");          // Line To seperate section of RIGHT seats
            printf("+%57s+\n", " ");
        }
        if (row % 2 == 0)
        {
            printf("-------------------------");          // Line To seperate section of LEFT seats
            printf("%-9s", " ");
            printf("-------------------------\n");          // Line To seperate section of RIGHT seats
        }
        else
        {
            for (int index = 0; index < 2; index++)
            {
                printf("|%57s|\n", " ");                       // Empty Space Seperation between seats
            }
        }

        for (int col = 0; col < 3; col++)
        {
            printf("|  %03d  ", ++i);            // To print the LEFT seats

        }
        printf("%-10s", "|");
        for (int col = 0; col < 3; col++)
        {
            printf("|  %03d  ", ++i);
        }
        printf("|\n");
    }
    for (int index = 0; index < 2; index++) {
        printf("-------------------------");
        printf("%-9s", " ");
        printf("-------------------------\n");
    }
    printf("==========================================================================================\n");

}

void seatSelectionCCC() {

    // COACH C (144 PAX)
    int i = 0;
    printf("\033[H\033[J");
    printf(
        "==========================================================================================\n"
        "| SEAT SELECTION | TRAIN ID : T06 | COACH : C           \n"
        "==========================================================================================\n"
    );
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    for (int row = 0; row < 12; row++) {                // 2 2 2 Seats

        if (row == 6)
        {
            printf("-------------------------");          // Line To seperate section of LEFT seats
            printf("%-9s", " ");
            printf("-------------------------\n");          // Line To seperate section of RIGHT seats
            printf("+%57s+\n", " ");
        }
        if (row % 2 == 0)
        {
            printf("-------------------------");          // Line To seperate section of LEFT seats
            printf("%-9s", " ");
            printf("-------------------------\n");          // Line To seperate section of RIGHT seats
        }
        else
        {
            for (int index = 0; index < 2; index++)
            {
                printf("|%57s|\n", " ");                       // Empty Space Seperation between seats
            }
        }

        for (int col = 0; col < 3; col++)
        {
            printf("|  %03d  ", ++i);            // To print the LEFT seats

        }
        printf("%-10s", "|");
        for (int col = 0; col < 3; col++)
        {
            printf("|  %03d  ", ++i);
        }
        printf("|\n");
    }
    for (int index = 0; index < 2; index++) {
        printf("-------------------------");
        printf("%-9s", " ");
        printf("-------------------------\n");
    }   printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    for (int row = 0; row < 12; row++) {                // 2 2 2 Seats

        if (row == 6)
        {
            printf("-------------------------");          // Line To seperate section of LEFT seats
            printf("%-9s", " ");
            printf("-------------------------\n");          // Line To seperate section of RIGHT seats
            printf("+%57s+\n", " ");
        }
        if (row % 2 == 0)
        {
            printf("-------------------------");          // Line To seperate section of LEFT seats
            printf("%-9s", " ");
            printf("-------------------------\n");          // Line To seperate section of RIGHT seats
        }
        else
        {
            for (int index = 0; index < 2; index++)
            {
                printf("|%57s|\n", " ");                       // Empty Space Seperation between seats
            }
        }

        for (int col = 0; col < 3; col++)
        {
            printf("|  %03d  ", ++i);            // To print the LEFT seats

        }
        printf("%-10s", "|");
        for (int col = 0; col < 3; col++)
        {
            printf("|  %03d  ", ++i);
        }
        printf("|\n");
    }
    for (int index = 0; index < 2; index++) {
        printf("-------------------------");
        printf("%-9s", " ");
        printf("-------------------------\n");
    }
    printf("==========================================================================================\n");

}

void seatSelectionCD() {
    // COACH D (12 ROOMS 24PAX) [PER ROOM 2 Beds]
    int i = 0;
    printf("\033[H\033[J");
    printf(
        "==========================================================================================\n"
        "| SEAT SELECTION | TRAIN ID : T07 | COACH : D           \n"
        "==========================================================================================\n"
    );
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    printf("|%57s|\n", " ");                       // Empty Space Seperation between seats
    for (int row = 0; row < 6; row++) {                // Rooms 
        printf("%-4s%s%4s\n", "|", "-------------------------|-------------------------", "|");
        if (row == 3)
        {
            printf("+%57s+\n", " ");
            printf("%-4s%s%4s\n", "|", "-------------------------|-------------------------", "|");
        }
        for (int index = 0; index < 2; index++)
        {
            printf("%-4s|%24s|%24s|%4s\n", "|", " ", " ", "|");
        }
        printf("%-4s+%10s%04d%10s|", "|", " ", ++i, " ");
        printf("%10s%04d%10s+%4s\n", " ", ++i, " ", "|");
        for (int index = 0; index < 2; index++)
        {
            printf("%-4s|%24s|%24s|%4s\n", "|", " ", " ", "|");
        }

    }
    printf("%-4s%s%4s\n", "|", "---------------------------------------------------", "|");
    printf("|%57s|\n", " ");                       // Empty Space Seperation between seats
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    printf("==========================================================================================\n");


}

void seatSelectionCDD() {
    // COACH D (12 ROOMS 24PAX) [PER ROOM 2 Beds]
    int i = 0;
    printf("\033[H\033[J");
    printf(
        "==========================================================================================\n"
        "| SEAT SELECTION | TRAIN ID : T08 | COACH : D           \n"
        "==========================================================================================\n"
    );
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    printf("|%57s|\n", " ");                       // Empty Space Seperation between seats
    for (int row = 0; row < 6; row++) {                // Rooms 
        printf("%-4s%s%4s\n", "|", "-------------------------|-------------------------", "|");
        if (row == 3)
        {
            printf("+%57s+\n", " ");
            printf("%-4s%s%4s\n", "|", "-------------------------|-------------------------", "|");
        }
        for (int index = 0; index < 2; index++)
        {
            printf("%-4s|%24s|%24s|%4s\n", "|", " ", " ", "|");
        }
        printf("%-4s+%10s%04d%10s|", "|", " ", ++i, " ");
        printf("%10s%04d%10s+%4s\n", " ", ++i, " ", "|");
        for (int index = 0; index < 2; index++)
        {
            printf("%-4s|%24s|%24s|%4s\n", "|", " ", " ", "|");
        }

    }
    printf("%-4s%s%4s\n", "|", "---------------------------------------------------", "|");
    printf("|%57s|\n", " ");                       // Empty Space Seperation between seats
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");   printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    printf("|%57s|\n", " ");                       // Empty Space Seperation between seats
    for (int row = 0; row < 6; row++) {                // Rooms 
        printf("%-4s%s%4s\n", "|", "-------------------------|-------------------------", "|");
        if (row == 3)
        {
            printf("+%57s+\n", " ");
            printf("%-4s%s%4s\n", "|", "-------------------------|-------------------------", "|");
        }
        for (int index = 0; index < 2; index++)
        {
            printf("%-4s|%24s|%24s|%4s\n", "|", " ", " ", "|");
        }
        printf("%-4s+%10s%04d%10s|", "|", " ", ++i, " ");
        printf("%10s%04d%10s+%4s\n", " ", ++i, " ", "|");
        for (int index = 0; index < 2; index++)
        {
            printf("%-4s|%24s|%24s|%4s\n", "|", " ", " ", "|");
        }

    }
    printf("%-4s%s%4s\n", "|", "---------------------------------------------------", "|");
    printf("|%57s|\n", " ");                       // Empty Space Seperation between seats
    printf("-------------------------");
    printf("%-9s", " ");
    printf("-------------------------\n");
    printf("==========================================================================================\n");


}

void ticketIdGenerate(char* newTicketId) {
    if (ticketCount == 0) {
        strcpy(newTicketId, "BT0001");
    }
    char lastId[7];
    (void)strcpy(lastId, ticketBooking[ticketCount - 1].ticket_id);

    // Extract the numeric part and increment it
    int numPart = 0;
    for (int i = 2; i < 6; ++i) {
        numPart = numPart * 10 + (lastId[i] - '0');
    }
    numPart++;

    newTicketId[0] = 'B';
    newTicketId[1] = 'T';
    newTicketId[2] = (numPart / 1000) % 10 + '0';
    newTicketId[3] = (numPart / 100) % 10 + '0';
    newTicketId[4] = (numPart / 10) % 10 + '0';
    newTicketId[5] = (numPart % 10) + '0';
    newTicketId[6] = '\0';
}