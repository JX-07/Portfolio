#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Header.h"

int memberCount = 0;

void read_memberinfo() {
    FILE* fptr = fopen("member.txt", "r");
    if (fptr == NULL) {
        printf("Error: Unable to open member.txt file.");
        exit(-1);
    }
    memberCount = 0;
    while (fscanf(fptr, "%6[^#]#%24[^#]#%24[^#]# %c#%24[^#]#%12[^#]#%13[^#]#%24[^#]#%d#%d\n",
        member[memberCount].memberId,
        member[memberCount].firstName,
        member[memberCount].lastName,
        &member[memberCount].gender,
        member[memberCount].email,
        member[memberCount].phoneNo,
        member[memberCount].memIc,
        member[memberCount].password,
        &member[memberCount].securityOption,
        &member[memberCount].securityRespond) != EOF) {
        memberCount++;
    }
    fclose(fptr);
}

void searchMember() {
    char searchFirstName[25] = { 0 };
    char searchLastName[25] = { 0 };

    printf("\033[H\033[J");     // CLS

    printf(
        "===========================================================================================================================================================\n"
        "                                                               SEARCH MEMBER INFORMATION                                                                   \n"
        "===========================================================================================================================================================\n\n"
    );

    printf("Please enter the first name you want to search: ");
    (void)scanf(" %[^\n]", searchFirstName);
    rewind(stdin);

    printf("Please enter the last name you want to search: ");
    (void)scanf(" %[^\n]", searchLastName);
    rewind(stdin);

    int result = -1;

    for (int i = 0; i < memberCount; i++) {
        if (strcmp(searchFirstName, member[i].firstName) == 0 && strcmp(searchLastName, member[i].lastName) == 0) {
            result = i;
            break;
        }
    }
    if (result != -1) {
        printf("\n===================================================\n");
        printf("Member Found. \n");
        printf("===================================================\n");
        printf("Member ID        : %s\n", member[result].memberId);
        printf("Name             : %s %s\n", member[result].firstName, member[result].lastName);
        printf("Gender           : %c\n", member[result].gender);
        printf("Email            : %s\n", member[result].email);
        printf("Phone Number     : %s\n", member[result].phoneNo);
        printf("IC Number        : %sm\n", member[result].memIc);
        printf("Password         : %s\n", member[result].password);
        printf("Security Option  : %d\n", member[result].securityOption);
        printf("Security Respond : %d\n", member[result].securityRespond);
        printf("===================================================\n");
    }
    else {
        printf("Member not found.\n");
    }

    printf("\nPress Enter To Return To Menu! ");
    (void)getchar();

    adminMenu();
}

void generateMemberId(char* newMemberId) {
    // If no members exist, start from MB0001
    if (memberCount == 0) {
        strcpy(newMemberId, "MB0001");
        return;
    }

    // Get the last member ID
    char lastMemberId[7];
    strcpy(lastMemberId, member[memberCount - 1].memberId);

    // Extract the numeric part and increment it
    int numPart = 0;
    for (int i = 2; i < 6; ++i) {
        numPart = numPart * 10 + (lastMemberId[i] - '0');
    }
    numPart++;

    // Format the new member ID
    newMemberId[0] = 'M';
    newMemberId[1] = 'B';
    newMemberId[2] = (numPart / 1000) % 10 + '0';
    newMemberId[3] = (numPart / 100) % 10 + '0';
    newMemberId[4] = (numPart / 10) % 10 + '0';
    newMemberId[5] = (numPart % 10) + '0';
    newMemberId[6] = '\0';
}

void add_new_member() {
    char newMemberId[7];
    int validEmail = 0;
    int validPhone = 0;
    int validIC = 0;
    generateMemberId(newMemberId);
    printf("Enter new member details:\n");
    printf("Member ID: %s\n", newMemberId);
    rewind(stdin);
    printf("First Name: ");
    (void)scanf("%[^\n]", member[memberCount].firstName);
    rewind(stdin);
    printf("Last Name: ");
    (void)scanf("%[^\n]", member[memberCount].lastName);
    rewind(stdin);

    do {
        printf("Email: ");
        (void)scanf("%s", member[memberCount].email);
        /*check the @ symbol in the email*/
        for (int i = 0; i < strlen(member[memberCount].email); i++) {
            if (member[memberCount].email[i] == '@') {
                validEmail = 1;
                break;
            }
        }
        if (validEmail == 0) {
            printf("Invalid email format. Email must contain '@'. Please re-enter.\n");
        }
    } while (validEmail == 0);
    rewind(stdin);

    do {
        printf("Phone Number: ");
        (void)scanf("%s", member[memberCount].phoneNo);
        int num1;
        num1 = strlen(member[memberCount].phoneNo);
        validPhone = 1;
        /*check the chatacter inside phoneNo all is digit*/
        for (int i = 0; i < num1; i++) {
            if (!isdigit(member[memberCount].phoneNo[i])) {
                validPhone = 0;
                printf("Invalid phone number. Please enter again.\n");
                break;
            }
        }
    } while (validPhone == 0);
    rewind(stdin);

    do {
        printf("IC Number (without '-'): ");
        (void)scanf("%s", member[memberCount].memIc);
        validIC = 0;
        /*check the ic length*/
        if (strlen(member[memberCount].memIc) != 12) {
            printf("Invalid IC number. IC number must be 12 digits long. Please enter again.\n");
        }
        else {
            /*check the ic all is digits only*/
            validIC = 1;
            for (int i = 0; i < 12; i++) {
                if (!isdigit(member[memberCount].memIc[i])) {
                    validIC = 0;
                    printf("Invalid IC number. IC number must contain digits only. Please enter again.\n");
                    break;
                }
            }
        }
    } while (validIC == 0);
    /*get the last digit of ic to generate gender*/ 
    int lastDigit;
    lastDigit = member[memberCount].memIc[strlen(member[memberCount].memIc) - 1];
    if (lastDigit % 2 == 0) {
        member[memberCount].gender = 'F';
    }
    else {
        member[memberCount].gender = 'M';
    }
    rewind(stdin);
    printf("Password: ");
    (void)scanf("%s", member[memberCount].password);
    rewind(stdin);

    // Security question options
    printf("\n\n---------------------------------------------\n");
    printf("| 1. Choose a fruit from these options      |\n");
    printf("| 2. Choose a colour from these options     |\n");
    printf("| 3. Choose a shape from these options      |\n");
    printf("---------------------------------------------\n");

    printf("\nPlease select one question for saving the password (1, 2, or 3): ");
    (void)scanf("%d", &member[memberCount].securityOption);

    // Switch statement for security options
    switch (member[memberCount].securityOption) {
    case 1:
        printf("1) Apple     2) Orange     3) Mangosteen\n");
        printf("\nYour option:");
        (void)scanf("%d", &member[memberCount].securityRespond);
        break;
    case 2:
        printf("1) Black     2) Violet     3) White");
        printf("\nYour option:");
        (void)scanf("%d", &member[memberCount].securityRespond);
        break;
    case 3:
        printf("1) Parallelogram     2) Heart     3) Round");
        printf("\nYour option:");
        (void)scanf("%d", &member[memberCount].securityRespond);
        break;
    default:
        printf("Invalid option. Please select 1, 2, or 3.\n");
        break;
    }

    memberCount++;

    FILE* fptr = fopen("member.txt", "a");
    if (fptr == NULL) {
        printf("Error: Unable to open member.txt file.");
        return;
    }

    fprintf(fptr, "%s#%s#%s#%c#%s#%s#%s#%s#%d#%d\n",
        newMemberId,
        member[memberCount - 1].firstName,
        member[memberCount - 1].lastName,
        member[memberCount - 1].gender,
        member[memberCount - 1].email,
        member[memberCount - 1].phoneNo,
        member[memberCount - 1].memIc,
        member[memberCount - 1].password,
        member[memberCount - 1].securityOption,
        member[memberCount - 1].securityRespond);

    fclose(fptr);
    read_memberinfo();
}

void deleteMember() {
    char memberId[7] = { 0 };
    int result = -1; /*initialize result =-1 to estimate the member not found*/
    printf("\033[H\033[J");     // CLS

    printf(
        "===========================================================================================================================================================\n"
        "                                                                DELETE MEMBER ACCOUNT                                                                      \n"
        "===========================================================================================================================================================\n\n"
    );
    printf("Enter the Member ID to delete: ");
    (void)scanf("%s", memberId);
    rewind(stdin);

    for (int i = 0; i < memberCount; i++) {
        if (strcmp(memberId, member[i].memberId) == 0) {
            result = i;
            break;
        }
    }
    if (result != -1) {
        /*open the file to overwrite all the member info again except the member going to delete*/
        FILE* fptr = fopen("member.txt", "w");
        if (fptr == NULL) {
            printf("Error: Unable to open member.txt file.");
            return;
        }

        for (int i = 0; i < memberCount; i++) {
            if (i != result) {
                fprintf(fptr, "%s#%s#%s#%c#%s#%s#%s#%s#%d#%d\n",
                    member[i].memberId,
                    member[i].firstName,
                    member[i].lastName,
                    member[i].gender,
                    member[i].email,
                    member[i].phoneNo,
                    member[i].memIc,
                    member[i].password,
                    member[i].securityOption,
                    member[i].securityRespond);
            }
        }
        fclose(fptr);
        printf("Member with ID %s deleted successfully.\n", memberId);
        memberCount--;
        /*shift the member at the bck to fill the blank of deleted member*/
        for (int i = result; i < memberCount; i++) {
            member[i] = member[i + 1];
        }
        read_memberinfo();
    }
    else {
        printf("Member with ID %s not found.\n", memberId);
    }
}

void deleteMemberSelf(char userID[USER_ID_FORMAT]) {
    int memCount = 0;
    int i = 0;
    int totalItem = 0;
    FILE* readFPTR = fopen("member.txt", "r");
    if (readFPTR == NULL) {
        printf("\nError Opening \"member.txt\"");
    }
    
    memCount = readMember();

    while ((strcmp(member[i].memberId, userID) != 0)) {
        i++;
    }

    for (int j = i; j < memCount; j++) {
        member[j] = member[j + 1];
    }

    FILE* writeFPTR = fopen("member.txt", "w");
    if (writeFPTR == NULL) {
        printf("\n Error Opening \"member.txt\"");
    }

    for (int index = 0; index < MAX_MEMBERS; index++){
        if (member[index].securityRespond != 0) {
            totalItem++;
        }
    }
    for (int index = 0; index < totalItem; index++) {
        fprintf(writeFPTR, "%s#%s#%s#%c#%s#%s#%s#%s#%d#%d\n",
            member[index].memberId,
            member[index].firstName,
            member[index].lastName,
            member[index].gender,
            member[index].email,
            member[index].phoneNo,
            member[index].memIc,
            member[index].password,
            member[index].securityOption,
            member[index].securityRespond);
    }


    printf("\nAccount Successfully Removed! ");
    (void)getchar();
    rewind(stdin);

    printf("\033[H\033[J");     // CLS

    fclose(readFPTR);
    fclose(writeFPTR);

    mainMenu();


}

void passwordRecovery() {
    char newPassword[25] = { 0 };
    char memberId[7] = { 0 };
    int question, ans;
    printf("Enter your Member ID: ");
    (void)scanf("%s", memberId);
    rewind(stdin);

    int result = -1;
    for (int i = 0; i < memberCount; i++) {
        if (strcmp(memberId, member[i].memberId) == 0) {
            result = i;
            break;
        }
    }

    if (result != -1) {
        printf("Choose your security question option:\n");
        printf("1. Choose a fruit from these options\n");
        printf("2. Choose a colour from these options\n");
        printf("3. Choose a shape from these options\n");
        printf("Enter option number: ");
        (void)scanf("%d", &question);
        rewind(stdin);
        if (question < 1 || question > 3) {
            printf("Invalid security option.\n");
            return;
        }
        printf("Answer the security question:\n");
        switch (question) {
        case 1:
            printf("Choose your answer from the options below (1, 2, or 3)\n");
            printf("1) Apple     2) Orange     3) Mangosteen\n");
            break;
        case 2:
            printf("Choose your answer from the options below (1, 2, or 3)\n");
            printf("1) Black     2) Violet     3) White\n");
            break;
        case 3:
            printf("Choose your answer from the options below (1, 2, or 3)\n");
            printf("1) Parallelogram     2) Heart     3) Round\n");
            break;
        }
        printf("Your option: ");
        (void)scanf("%d", &ans);
        rewind(stdin);

        if (ans < 1 || ans > 3) {
            printf("Invalid response.\n");
            return;
        }
        /*compare the security option and security respond*/
        if (ans == member[result].securityRespond && question == member[result].securityOption) {
            printf("Correct answer!\n");
            printf("Enter your new password: ");
            (void)scanf("%s", &newPassword);
            rewind(stdin);
            printf("Password changed successfully.\n");
            (void)strcpy(member[result].password, newPassword);

            FILE* fptr = fopen("member.txt", "w");
            if (fptr == NULL) {
                printf("Error: Unable to open member.txt file.");
                return;
            }
            for (int i = 0; i < memberCount; i++) {
                fprintf(fptr, "%s#%s#%s#%c#%s#%s#%s#%s#%d#%d\n",
                    member[i].memberId,
                    member[i].firstName,
                    member[i].lastName,
                    member[i].gender,
                    member[i].email,
                    member[i].phoneNo,
                    member[i].memIc,
                    member[i].password,
                    member[i].securityOption,
                    member[i].securityRespond);
            }
            fclose(fptr);
        }
        else {
            printf("Incorrect answer.\n");
        }

    }
    else {
        printf("Member with ID %s not found.\n", memberId);
    }
}

void modifyInfo(char userID[USER_ID_FORMAT]) {
    char newEmail[25] = { 0 };
    char newPhoneNo[12] = { 0 };
    char newMemIc[13] = { 0 };
    int newSecurityOption = 0;
    int newSecurityRespond = 0;
    int validPhone = 0;
    int validEmail = 0;

    int result = -1;
    printf("\033[H\033[J");     // CLS

    printf(
        "===========================================================================================================================================================\n"
        "                                                                   MODIFY MEMBER INFO                                                                      \n"
        "===========================================================================================================================================================\n\n"
    );

    for (int i = 0; i < memberCount; i++) {
        if (strcmp(userID, member[i].memberId) == 0) {
            result = i;
            break;
        }
    }
    if (result != -1) {
        printf("Enter New Details \n");

        do {
            printf("Member ID      : %s\n", userID);
            printf("Email          : ");
            (void)scanf("%s", newEmail);
            for (int i = 0; i < strlen(newEmail); i++) {
                if (newEmail[i] == '@') {
                    validEmail = 1;
                    break;
                }
            }
            if (validEmail == 0) {
                printf("Invalid email format. Email must contain '@'. Please re-enter.\n");
                rewind(stdin);
            }
        } while (validEmail == 0);

        do {
            printf("Phone Number   : ");
            (void)scanf("%s", newPhoneNo);
            validPhone = 1;
            for (int i = 0; i < strlen(newPhoneNo); i++) {
                if (!isdigit(newPhoneNo[i])) {
                    validPhone = 0;
                    printf("Invalid phone number. Please enter again.\n");
                    rewind(stdin);
                    break;
                }
            }
        } while (validPhone == 0);
        rewind(stdin);
        // Security question options
        printf("\n\n---------------------------------------------\n");
        printf("| 1. Choose a fruit from these options      |\n");
        printf("| 2. Choose a colour from these options     |\n");
        printf("| 3. Choose a shape from these options      |\n");
        printf("---------------------------------------------\n");

        printf("\nPlease select one question for saving the password (1, 2, or 3): ");
        (void)scanf("%d", &newSecurityOption);

        // Switch statement for security options
        switch (newSecurityOption) {
        case 1:
            printf("1) Apple     2) Orange     3) Mangosteen\n");
            printf("\nYour option:");
            (void)scanf("%d", &newSecurityRespond);
            break;
        case 2:
            printf("1) Black     2) Violet     3) White");
            printf("\nYour option:");
            (void)scanf("%d", &newSecurityRespond);
            break;
        case 3:
            printf("1) Parallelogram     2) Heart     3) Round");
            printf("\nYour option:");
            (void)scanf("%d", &newSecurityRespond);
            break;
        default:
            printf("Invalid option. Please select 1, 2, or 3.\n");
            break;
        }
        strcpy(member[result].email, newEmail);
        strcpy(member[result].phoneNo, newPhoneNo);
        member[result].securityOption = newSecurityOption;
        member[result].securityRespond = newSecurityRespond;

        FILE* fptr = fopen("member.txt", "w");
        if (fptr == NULL) {
            printf("Error: Unable to open member.txt file.");
            return;
        }
        for (int i = 0; i < memberCount; i++) {
            fprintf(fptr, "%s#%s#%s#%c#%s#%s#%s#%s#%d#%d\n",
                userID,
                member[i].firstName,
                member[i].lastName,
                member[i].gender,
                member[i].email,
                member[i].phoneNo,
                member[i].memIc,
                member[i].password,
                member[i].securityOption,
                member[i].securityRespond);
        }
        fclose(fptr);
        read_memberinfo();
    }
    else {
        printf("Member Not Found.\n");
    }

    (void)getchar();
    memberMenu(userID);
}

void displayMember() {
    printf("\033[H\033[J");     // CLS

    printf(
        "===========================================================================================================================================================\n"
        "                                                              DISPLAY MEMBER INFORMATION                                                                      \n"
        "===========================================================================================================================================================\n"
    );

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-10s%-15s%-15s%-8s%-22s%-14s%-14s%-18s%-20s%-20s\n",
        "Member ID", "First Name", "Last Name", "Gender", "Email", "Phone No", "MemIc", "Password", "Security Option", "Security Respond");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < memberCount; i++) {
        printf("%-10s%-15s%-15s%-8c%-22s%-14s%-14s%-18s%-20d%-20d\n",
            member[i].memberId,
            member[i].firstName,
            member[i].lastName,
            member[i].gender,
            member[i].email,
            member[i].phoneNo,
            member[i].memIc,
            member[i].password,
            member[i].securityOption,
            member[i].securityRespond);
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    printf("\nPress Enter To Return!");
    (void)getchar();

    adminMenu();
}

void memberMenu(char userID[USER_ID_FORMAT]) {
    char input;
    int select = 0;
    printf("\033[H\033[J\033[?25l");
    printf("=========================================================================================================================\n");
    printf("                                                      MEMBER MODULE                                                      \n");
    printf("=========================================================================================================================\n");
    printf("                                          What action would you like to perform?                                         \n");
    printf("                                    \033[5m*Navigate through arrow keys and space to select*\033[0m                                    \n");
    printf("=========================================================================================================================\n");
    printf(" /                                         \033[5m>\033[0m     Ticket Booking Function     \033[5m<\033[0m                                         \\ \n");
    printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
    printf("|\033[7m                  (1)                  \033[0m|                  (2)                  |                  (3)                  |\n");
    printf("|\033[7m              Book Ticket              \033[0m|         Modify Ticket Booking         |         Remove Ticket Booking         |\n");
    printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
    printf("|                  (4)                  |                  (5)                  |                                       |\n");
    printf("|      Display All Ticket Booking       |                Payment                |                                       |\n");
    printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
    printf(" /                                        \033[5m>\033[0m          Account Function          \033[5m<\033[0m                                       \\ \n");
    printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
    printf("|                  (1)                  |                  (2)                  |                                       |\n");
    printf("|           Modify Information          |            Remove Account             |                                       |\n");
    printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
    printf(" /                                                                                                                     \\ \n");
    printf("+-----------------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                                          ( )                                                          |\n");
    printf("|                                                         Exit.                                                         |\n");
    printf("+-----------------------------------------------------------------------------------------------------------------------+\n");
    for (int i = 0;; i++) { //\033[47;30m
        input = getch();
        rewind(stdin);
        switch (input) {
        case -32:
            break;
        case 72://up
            if (select >= 3 && select <= 4)
                select -= 3;
            else if (select >= 5 && select <= 7)
                select -= 2;
            break;
        case 75://left
            if (select != 0 && select != 3 && select != 5 && select != 7)
                select--;
            break;
        case 77://right
            if (select != 2 && select != 4 && select != 6 && select != 7)
                select++;
            break;
        case 80://down
            if (select >= 0 && select <= 1)
                select += 3;
            else if (select >= 2 && select <= 5)
                select += 2;
            else if (select == 6)
                select = 7;
            break;
        case 32:
            memberNav(select, userID);
            break;
        }
        if (select == 0) {
            printf("\033[16A");
            printf("|\033[7m                  (1)                  \033[0m|\n");
            printf("|\033[7m              Book Ticket              \033[0m|\n");
            printf("\033[14B");
        }
        else {
            printf("\033[16A");
            printf("|                  (1)                  |\n");
            printf("|              Book Ticket              |\n");
            printf("\033[14B");
        }
        if (select == 1) {
            printf("\033[16A\033[40C");
            printf("|\033[7m                  (2)                  \033[0m|\n");
            printf("\033[40C");
            printf("|\033[7m         Modify Ticket Booking         \033[0m|\n");
            printf("\033[14B");
        }
        else {
            printf("\033[16A\033[40C");
            printf("|                  (2)                  |\n");
            printf("\033[40C");
            printf("|         Modify Ticket Booking         |\n");
            printf("\033[14B");
        }
        if (select == 2) {
            printf("\033[16A\033[80C");
            printf("|\033[7m                  (3)                  \033[0m|\n");
            printf("\033[80C");
            printf("|\033[7m         Remove Ticket Booking         \033[0m|\n");
            printf("\033[14B");
        }
        else {
            printf("\033[16A\033[80C");
            printf("|                  (3)                  |\n");
            printf("\033[80C");
            printf("|         Remove Ticket Booking         |\n");
            printf("\033[14B");
        }
        if (select == 3) {
            printf("\033[13A");
            printf("|\033[7m                  (4)                  \033[0m|\n");
            printf("|\033[7m      Display All Ticket Booking       \033[0m|\n");
            printf("\033[11B");
        }
        else {
            printf("\033[13A");
            printf("|                  (4)                  |\n");
            printf("|      Display All Ticket Booking       |\n");
            printf("\033[11B");
        }
        if (select == 4) {
            printf("\033[13A\033[40C");
            printf("|\033[7m                  (5)                  \033[0m|\n");
            printf("\033[40C");
            printf("|\033[7m                Payment                \033[0m|\n");
            printf("\033[11B");
        }
        else {
            printf("\033[13A\033[40C");
            printf("|                  (5)                  |\n");
            printf("\033[40C");
            printf("|                Payment                |\n");
            printf("\033[11B");
        }
        if (select == 5) {
            printf("\033[8A");
            printf("|\033[7m                  (1)                  \033[0m|\n");
            printf("|\033[7m           Modify Information          \033[0m|\n");
            printf("\033[6B");
        }
        else {
            printf("\033[8A");
            printf("|                  (1)                  |\n");
            printf("|           Modify Information          |\n");
            printf("\033[6B");
        }
        if (select == 6) {
            printf("\033[8A\033[40C");
            printf("|\033[7m                  (2)                  \033[0m|\n");
            printf("\033[40C");
            printf("|\033[7m            Remove Account             \033[0m|\n");
            printf("\033[6B");
        }
        else {
            printf("\033[8A\033[40C");
            printf("|                  (2)                  |\n");
            printf("\033[40C");
            printf("|            Remove Account             |\n");
            printf("\033[6B");
        }
        if (select == 7) {
            printf("\033[3A");
            printf("|\033[7m                                                          ( )                                                          \033[0m|\n");
            printf("|\033[7m                                                         Exit.                                                         \033[0m|\n");
            printf("\033[B");
        }
        else {
            printf("\033[3A");
            printf("|                                                          ( )                                                          |\n");
            printf("|                                                         Exit.                                                         |\n");
            printf("\033[B");
        }
    }
}

void memberNav(int n, char userID[USER_ID_FORMAT]) {
    printf("\033[?25h");
    switch (n) {
    case 0:
        add_ticketBooking(userID);
        break;
    case 1:
        modify_ticketBooking(userID);
        break;
    case 2:
        cancel_ticketBooking(userID);
        break;
    case 3:
        displayAll_ticketBookingMember(userID);
        break;
    case 4:
        payment_ticketBooking(userID);
        break;
    case 5:
        modifyInfo(userID);
        break;
    case 6:
        deleteMemberSelf(userID);
        break;
    case 7:
        printf("\033[H\033[J");     // CLS
        mainMenu();
        break;
    }
}

void memberMain(char userID[USER_ID_FORMAT]) {

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(userID, member[i].memberId) == 0) {
            if (strcmp(userPassword, member[i].password) == 0) {

                memberMenu(userID);               // DIRECT TO MEMBER PAGE
            }
            else {
                loginUserPassInvalid();
                break;
            }

        }
    }
    loginUserPassInvalid();

    printf("\033[H\033[J");     // REFERSH PAGE
    mainMenu();
}
