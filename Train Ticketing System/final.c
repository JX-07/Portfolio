#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>
#include "Header.h"

// VARIABLE
int menuChoice;
int index = 0;
SYSTEMTIME time;

void main() {
    
    mainMenu();
}

// INTERFACES
int memCount;
int staffCount;

// MAIN MENU

void mainMenu() {       // MENU (1st PAGE) [MAIN]
   
    // READ AND STORE DATA INTO STRUCTURES ARRAYS
    GetLocalTime(&time);
    memCount = readMember();
    staffCount = readStaff();
    read_schedule();
    read_ticketBooking();
    read_memberinfo();

    do
    {
        mainMenuFORMAT();
        mainMenuFUNCTION();
            
    } while (index == 1);

}

int readMember() {
    FILE* memberFPTR = fopen("member.txt", "r");
    int loopIndex = 0;
    if (memberFPTR == NULL)
    {
        printf("\n\nEmpty File : \"member.txt\"");
    }
    else
    {
        while (fscanf(memberFPTR, "%6[^#]#%24[^#]#%24[^#]# %c#%24[^#]#%12[^#]#%13[^#]#%24[^#]#%d#%d\n",
            member[loopIndex].memberId,
            member[loopIndex].firstName,
            member[loopIndex].lastName,
            &member[loopIndex].gender,
            member[loopIndex].email,
            member[loopIndex].phoneNo,
            member[loopIndex].memIc,
            member[loopIndex].password,
            &member[loopIndex].securityOption,
            &member[loopIndex].securityRespond) != EOF) {
                      
            rewind(stdin);
            loopIndex++;
        }

    }

    return loopIndex;
}

int readStaff() {
    FILE* fRead = fopen("staff.bin", "rb");

    int index = 0;
    while (fread(&staffs[index], sizeof(struct Staff), 1, fRead) == 1) {
        index++;
    }
    fclose(fRead);
    return (index);
}

int readSchedule() {
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
        return(scheduleCount);
}

void mainMenuFUNCTION() {      // MENU (1st PAGE) [FUNCTIONS]
   
    // TAKE USER TO NEXT PAGE
        index = 0;
        readChoice();
        switch (menuChoice) {
        case 0:         // Enter 0 to Quit
            exit(0);
            break;
        case 1:         // Enter 1 to Go to Login Page
            printf("\033[H\033[J");
            loginPage();
            break;
        case 2:         // Enter 2 to Check train schedule
            printf("\033[H\033[J");
            main_schedule();
            break;
        case 3: 
            printf("\033[H\033[J");
            add_new_member();
            break; 
        case 4:
            rewind(stdin);
            printf("\033[H\033[J");
            passwordRecov(memCount, staffCount);
            break;
        default:
            printf("%38sInvalid Option Selected!\n", " ");
            index = 1;
            rewind(stdin);  // Remove scanf Input to before repeat scanf
            printf("\n%38sPress ANY KEY to Retry!\n", " ");
            (void)getchar();
            printf("\033[H\033[J");     //CLS
        }

}

void mainMenuFORMAT() {       // MENU (1st PAGE) [FORMATTING]
   
    thomasLogo();

    printf(
        "\n\n\n%67s\n\n" 
        "\n%40s"            // Blank Space (FORMATTING)
        "%-50s"
        "\n%40s"            // Blank Space (FORMATTING)
        "%-50s"
        "\n%40s"            // Blank Space (FORMATTING)
        "%-50s"
        "\n%40s"            // Blank Space (FORMATTING)
        "%-50s"
        "\n%40s"            // Blank Space (FORMATTING)
        "%-50s" , "WELCOME TO THOMAS DUDU TRAIN!"," ", "(1) - Login "," ", "(2) - Check Train Schedules", " ", "(3) - Create New Account", " ", "(4) - Password Recovery", " ", "(0) - Exit"
    );

    printf("\n\n\n");


}

void readChoice() {
    printf("\n%38s", " ");            // Blank Space (FORMATTING)
    printf("Enter Your Choice => "); 
    if (scanf("%d", &menuChoice) != 1)  // IF number then SCANF = 1
    {
        menuChoice = -1;        // To Ensure Invalid 
    }
}

// LOGIN PAGE

void loginPage() {        // MENU (2nd PAGE) [LOGIN PAGE]

    thomasLogo();

    printf(                     // PROMPT USER FOR USER
        "\n\n\n%57s\n\n"
        "\n%40s"            // Blank Space (FORMATTING)
        "%15s", "Login Page", " ", "User ID  : "
    );
    (void)scanf(" %[^\n]", userID);
    rewind(stdin);
    
    int stopper = 0;        // Loop Guide

    if (strlen(userID) == USER_ID_FORMAT)      // CHECK NUMBER OF CHARACTER 
    {
        do
        {

            int j = 0;              // Loop Guide

            for (int i = 0; i < USER_ID_ALPHA ; i++)
            {

                userID[i] = toupper(userID[i]);
                if (userID[0] == 'S' && userID[1] == 'T') {
                    j = 1;  
                }
                else if (userID[0] == 'M' && userID[1] == 'B') {
                    j = 1;
                }
                else {
                    printf("\n%35sThe ID is not in the correct format!", " ");
                    loginUserIDInvalid();
                }
            }
            if (j == 1)     // CORRECT INPUT [STEP 1]  // CHECK NUMBER AFTER ALPHA
            {
                for (int i = USER_ID_ALPHA; i < USER_ID_NUMBER; i++)
                {
                    if (isdigit(userID[i])) {
                        j = 2;            // CORRECT INPUT [STEP 2]
                    }
                    else {
                        printf("\n%35sThe ID is not in the correct format!", " ");
                        loginUserIDInvalid();
                    }
                }
            }
            if (j == 2)     // CORRECT INPUT [STEP 2]   
            {
                int higherCount = 0;
                if (memCount >= staffCount) {
                    higherCount = memCount;
                }
                else if (staffCount >= memCount) {
                    higherCount = staffCount;
                }
                for (int i = 0; i < higherCount; i++) {
                    if (strcmp(userID, member[i].memberId) == 0 || strcmp(userID, staffs[i].id) == 0) {

                        j = 3;
                        break;
                    }
                    else {
                        j = 4;
                    }
                }
            }
            if (j == 3) {
                printf("%40s"                          // Blank Space (FORMATTING)      // PROMT USER FOR PASSWORD
                    "%15s", " ", "Password : ");
                (void)scanf(" %[^\n]", userPassword);
                rewind(stdin);


                // OPEN FILE BASED ON USER_ID
                if (userID[0] == 'M') {             // IF FIRST LETTER = M -> MEMBER PAGE
                    memberMain(userID);
                    stopper = 1;
                }
                else if (userID[0] == 'S') {        // IF FIRST LETTER = S -> STAFF PAGE
                    staffMain();
                    stopper = 1;
                }
            }
            if (j == 4) {
                printf("\n%45sID Not Found!\n\n", " ");
                (void)getchar();
                stopper = 1;

                printf("\033[H\033[J");     // REFERSH PAGE
                mainMenu();
            }

        } while (stopper == 0);

    }
    else if (strlen(userID) > USER_ID_FORMAT) {
        printf("\n%40sToo much character for User ID!", " ");
        loginUserIDInvalid();
    }
    else if (strlen(userID) < USER_ID_FORMAT) {
        printf("\n%40sToo less character for User ID!", " ");
        loginUserIDInvalid();
    }


}

void loginUserIDInvalid() {
    printf("\n%40sPress Enter to Retry!", " ");
    (void)getchar();

    printf("\033[H\033[J");     // REFERSH PAGE
    loginPage();
}

void loginUserPassInvalid() {
    int loopPointer = 0;
    printf("\n%40sInvalid Password Entered!", " ");
    (void)getchar();

    printf("\033[H\033[J");     // REFERSH PAGE
    loginPage();
}

// PASSWORD RECOVERY
void passwordRecov(int memCount, int staffCount) {
    int stopper = 0;
    thomasLogo();
    printf("\n\n\n\n%40s"                         
        "%15s", " ", "USER ID : ");
    (void)scanf("%6[^\n]", &userID);
    rewind(stdin);



    if (strlen(userID) == USER_ID_FORMAT)      // CHECK NUMBER OF CHARACTER 
    {
        do
        {
            int j = 0;              // Loop Guide

            for (int i = 0; i < USER_ID_ALPHA; i++)
            {

                userID[i] = toupper(userID[i]);
                if (userID[0] == 'S' && userID[1] == 'T') {
                    j = 1;
                }
                else if (userID[0] == 'M' && userID[1] == 'B') {
                    j = 1;
                }
                else {
                    printf("\n%35sThe ID is not in the correct format!", " ");
                    stopper = 1;
                    break;
                }
            }
            if (j == 1)     // CORRECT INPUT [STEP 1]  // CHECK NUMBER AFTER ALPHA
            {
                for (int i = USER_ID_ALPHA; i < USER_ID_NUMBER; i++)
                {
                    if (isdigit(userID[i])) {
                        j = 2;            // CORRECT INPUT [STEP 2]
                    }
                    else {
                        printf("\n%35sThe ID is not in the correct format!", " ");
                        stopper = 1;
                        break;
                    }
                }
            }
            if (j == 2)     // CORRECT INPUT [STEP 2]   
            {
                // OPEN FILE BASED ON USER_ID
                if (userID[0] == 'M') {             // IF FIRST LETTER = M -> MEMBER PAGE
                    for (int index = 0; index < memCount; index++) {
                        if (strcmp(userID, member[index].memberId) == 0) {
                            switch (member[index].securityOption) {
                            case 1: 
                                printf("\n%40s1. Choose a fruit from these options\n", " ");
                                printf("\n%40s1) Apple     2) Orange     3) Mangosteen\n", " ");
                                passwordRecovAns();
                                break;
                            case 2:
                                printf("\n%40s2. Choose a colour from these options\n", " ");
                                printf("\n%40s1) Black     2) Violet     3) White\n", " ");
                                passwordRecovAns();
                                break;
                            case 3:
                                printf("\n%40sChoose your answer from the options below (1, 2, or 3)\n", " ");
                                printf("\n%40s1) Parallelogram     2) Heart     3) Round\n", " ");
                                passwordRecovAns();
                                break;
                            default:
                                printf("\n%40sInvalid Security Option!", " ");
                                (void)getchar();
                                printf("\033[H\033[J");     // REFERSH PAGE
                                passwordRecov(memCount, staffCount);
                            }


                            stopper = 1;
                            break;
                        }
                    }
                }
                else if (userID[0] == 'S') {        // IF FIRST LETTER = S -> STAFF PAGE
                    for (int index = 0; index < staffCount; index++) {
                        if (strcmp(userID, staffs[index].id) == 0) {
                            int ansLocate = index;
                            switch (staffs[index].recov_ques) {
                            case 1:
                                printf("\n%35s1. What is your favourite food?\n", " ");
                                passwordRecovStrAns(ansLocate);
                                break;
                            case 2:
                                printf("\n%35s2. Who is your favourite idol?\n", " ");
                                passwordRecovStrAns(ansLocate);
                                break;
                            case 3:
                                printf("\n%35s3,What is your favourite movie?\n", " ");
                                passwordRecovStrAns(ansLocate);
                                break;
                            case 4:
                                printf("\n%35s4. What is the name of your favourite pet?\n", " ");
                                passwordRecovStrAns(ansLocate);
                                break;
                            case 5:
                                printf("\n%35s5. Who is your favourite childhood hero?\n", " ");
                                passwordRecovStrAns(ansLocate);
                                break;
                            case 6:
                                printf("\n%35s6.Where is your favourite holiday destination?\n", " ");
                                passwordRecovStrAns(ansLocate);
                                break;
                            }
                            stopper = 1;
                            break;
                        }
                    }
                  
                }
            }
        } while (stopper == 0);

    }
    else if (strlen(userID) > USER_ID_FORMAT) {
        printf("\n%40sToo much character for User ID!", " ");
        passwordRecovInvalid();
    }
    else if (strlen(userID) < USER_ID_FORMAT) {
        printf("\n%40sToo less character for User ID!", " ");
        passwordRecovInvalid();
    }

    printf("\n\n\n%40s Press Enter To Return!", " ");
    (void)getchar();
    printf("\033[H\033[J");     // REFERSH PAGE

    do
    {
        mainMenuFORMAT();
        mainMenuFUNCTION();

    } while (index == 1);

}

void passwordRecovAns(){
    int ans = 0;
    printf("%40sAnswer : ", " ");
    (void)scanf("%d", &ans);
    rewind(stdin);
    if (ans == member[index].securityRespond) {
        printf("\n%40s PASSWORD : %s", " ", member[index].password);
    }
    else {
        printf("%40s Wrong Option Selected!", " ");
    }
}
void passwordRecovStrAns(int index) {
    char answer[50] = { 0 };
    printf("%35sAnswer : ", " ");
    (void)scanf("%[^\n]", answer);
    rewind(stdin);

    if(strcmp(answer, staffs[index].recov_ans) == 0) {
        printf("\n%-35s PASSWORD : %4s", " ", staffs[index].password);
    }
    else {
        printf("\n%40s Wrong Answer!"," ");
    }
}
void passwordRecovInvalid() {
    int loopPointer = 0;
    printf("\n%40sInvalid Answer Entered!", " ");
    (void)getchar();

    printf("\033[H\033[J");     // REFERSH PAGE
}

// WELCOME MESSAGE

void welcomeMessage() {

    printf(
            "\n                 /\\                 "
            "\n _               \\/               _"
            "\n(______________/\\/\\/\\______________)"
            "\n\n\n"
            "  ~ WELCOME TO THOMAS DUDU TRAIN ~    "
            "\n\n   %-31s "  
            "\n\n   %-31s "
            "\n"
            "\n ______________      ______________ "
            "\n(_             \\/\\/\\/             _)"
            "\n                 /\\                 "
            "\n                 \\/               " ,"A", "B" // NAME , USER POSITION
    );

}

// FORMAT FUNCTIONS

void thomasLogo() {         // TO print "Thomas Duu Duu Train"
    printf(
        " _____ _                                 ____              ____                _____          _       \n"
        "|_   _| |__   ___  _ __ ___   __ _ ___  |  _ \\ _   _ _   _|  _ \\ _   _ _   _  |_   _| __ __ _(_)_ __  \n"
        "  | | | '_ \\ / _ \\| '_ ` _ \\ / _` / __| | | | | | | | | | | | | | | | | | | |   | || '__/ _` | | '_ \\ \n"
        "  | | | | | | (_) | | | | | | (_| \\__ \\ | |_| | |_| | |_| | |_| | |_| | |_| |   | || | | (_| | | | | |\n"
        "  |_| |_| |_|\\___/|_| |_| |_|\\__,_|___/ |____/ \\__,_|\\__,_|____/ \\__,_|\\__,_|   |_||_|  \\__,_|_|_| |_|\n"
    );
}



// USE TO EXTRACT NUMBER LIKE "M0003" GET 3
int extractNumber(char* str) {
    int number = 0;

    while (*str && !isdigit(*str)) {         // Skip non-digit characters and the initial 
        str++;
    }

    while (*str && isdigit(*str)) {           // Extract number
        number = number * 10 + (*str - '0');
        str++;
    }
                                               // Return the extracted number to main
    return number;
}