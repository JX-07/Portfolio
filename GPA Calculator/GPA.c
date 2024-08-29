#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <math.h>
#pragma warning (disable:4996)

//DEFINE
#define MAX_SEMESTER 3
#define COURSE_CODE_LENGTH 8

 //Grade Point
#define A "A"
#define AM "A-"
#define BP "B+"
#define B "B"
#define BM "B-"
#define CP "C+"
#define C "C"
#define F "F"

 //Colours
#define MAGENTA "\x1b[35m"
#define YELLOW   "\x1B[33m"
#define RESET "\x1B[0m"
#define CYAN   "\x1B[36m"
#define RED "\033[1;31m"
#define GREEN "\x1b[32m"


//USER-DEFINED FUNCTION
void mainMenu();
void staffMenu();
void studentMenu();
void studentDetails();
void studentCourse();
void viewGPAT();
void viewCGPAT();
void viewGPAS();
void viewCGPAS();
void generateGPA();
void generateCGPA();
int genGPA();
int genCGPA();
int nameValid();
int idValid();
int courseCodeValid();
int noCourseChecker();
int gradeValid();



//GLOBAL VARIABLE
int option = 0;
int totalNumCourse = 0;
int creditHours[3][999];
int creditHoursSem[3];
int invalid = 0;
int currentSemester = 0;
int durationSeconds = 5;
int coursesPerSemester[MAX_SEMESTER];
char courseCode[MAX_SEMESTER][5][COURSE_CODE_LENGTH];
char name[100];
char id[10];
char gradeAlpha[3][5][3];
float gpa[3];
float cgpa = 0.0;
float totalQualityPoint = 0.0;
float totalCreditHours = 0.0;
float qualityPoint[3][3];
float qualityPointSem[MAX_SEMESTER];
float gradeP[3][3];

//MAIN FUNCTION
void main()
{
    //Main Menu
    mainMenu();

}

//------------------- Menu -------------------//
void mainMenu()
{
    int valid = 0;
    printf("\033[H\033[J");
    printf(
        MAGENTA "---------------------------------------------\n"
        "Welcome To Kolej Pasar GPA/CGPA Calculator!\n"
        "---------------------------------------------\n"
        RESET "Staff   -- 1\n"
        "Student -- 2\n"
        "Exit    -- 3\n\n"
        CYAN "Enter your Option : "RESET);
    scanf("%d", &option);
    rewind(stdin);
    do
    {
        valid = 0;
        if(option > 0 && option < 4)
        {
            switch (option)
            {
            case 1:
                staffMenu();
                break;
            case 2:
                studentMenu();
                break;
            case 3:
                return(0);
            }
            valid = 1;
        }
        else
        {
            printf(RED"Invalid Option Entered! Please re-enter.\n"RESET);
            printf(CYAN "Enter your Option : "RESET);
            scanf("%d", &option);
            rewind(stdin);
        }
    } while (valid != 1);

}

void staffMenu()
{
    printf("\033[H\033[J");
    int valid = 0;
    printf(
        YELLOW "----------------------------\n"
        "Staff Administrator Mode\n"
        "----------------------------\n\n"
        RESET "Enter Student's details -- 1\n"
        "Enter Student's Course details -- 2\n"
        "Generate the GPA score -- 3\n"
        "Generate the CGPAs score -- 4\n"
        "View Student's GPA  -- 5\n"
        "View Student's CGPA -- 6\n"
        "Return to Main Menu -- 7\n\n"
        CYAN "Enter your Option: "RESET);
    scanf("%d", &option);
    rewind(stdin);
    do
    {
        if (option > 0 && option < 8)
        {
            switch (option)
            {
            case 1:
                studentDetails();
                break;
            case 2:
                studentCourse();
                break;
            case 3:
                generateGPA();
                break;
            case 4:
                generateCGPA();
                break;
            case 5:
                viewGPAT();
                break;
            case 6:
                viewCGPAT();
                break;
            case 7:
                mainMenu();
                break;
            }
            valid = 1;
        }
        else
        {
            printf(RED"Invalid Option Entered! Please re-enter.\n"RESET);
            printf(CYAN"Enter your Option: "RESET);
            scanf("%d", &option);
            rewind(stdin);
        }
    } while (valid != 1);
}
void studentMenu()
{
    int valid = 0;
    printf("\033[H\033[J");
    printf(
        GREEN "----------------------------\n"
        "Student Mode\n"
        "----------------------------\n"
        RESET "Name        : %-99s\n"
        "Student ID  : %-10s\n"
        "Current Sem : %d\n"
        "----------------------------\n"
        "View Student GPA  -- 1\n"
        "View Student CGPA -- 2\n"
        "Return to Welcome -- 3\n\n"
        CYAN "Enter Your Option : "RESET, name, id, currentSemester);
    scanf("%d", &option);
    rewind(stdin);
    do
    {
        if (option > 0 && option < 4)
        {
            switch (option)
            {
            case 1:
                viewGPAS();
                break;
            case 2:
                viewCGPAS();
                break;
            case 3:
                mainMenu();
                break;
            }
            valid = 1;
        }
        else
        {
            printf(RED"Invalid Option Entered! Please re-enter.\n"RESET);
            printf(CYAN"Enter your Option: "RESET);
            scanf("%d", &option);
            rewind(stdin);
        }
    } while (valid != 1);

}

//Processes
void studentDetails()
{
    printf("\033[H\033[J");
    printf(
        YELLOW "--------------------\n"
        "Student Details\n"
        "--------------------\n" RESET);
    //Enter Name
    int validName = 0;
    do
    {
        printf("Name : ");
        scanf(" %[^\n]", &name);
        rewind(stdin);
        if (nameValid(name))
            validName = 1;
        else
            printf(RED"Invalid Name Entered. Please re-enter.\n"RESET);
    } while (validName != 1);

    //Enter Student ID
    int validID = 0;
    do
    {
        printf("Student ID (e.g)[KPKL12345]: ");
        scanf("%[^\n]", &id);
        rewind(stdin);
        if (idValid(id))
        {
            validID = 1;
        }
        else
            printf(RED"Invalid ID Entered. Please re-enter\n"RESET);
    } while (validID != 1);
    printf("Press Enter to continue...\n");
    getchar();
    mainMenu();



}
void studentCourse()
{
    printf("\033[H\033[J");
    //Enter Course Code
    int w = 1;

    printf(
        YELLOW "--------------------\n" 
        "Course Code Detail\n"
        "(e.g.)[AAA1473]\n"
        "--------------------\n" RESET);

    //Semester Loop
    for (int semester = 1;semester <= MAX_SEMESTER; semester++)
    {
        int valid = 0;

        do
        {

            printf("Enter number of Courses for Semester %d: ", semester);
            scanf("%d", &coursesPerSemester[semester - 1]);
            rewind(stdin);

            if (coursesPerSemester[semester - 1] < 5)
            {
                valid = 1;
            }
            else {
                printf(RED"Invalid Amount of Course! Please re-enter.\n"RESET);
                valid = 0;
            }

        } while (valid != 1);

        for (int w = 1; w <= coursesPerSemester[semester - 1]; w++)
        {
            printf("Enter Course Code %d: ", w);
            scanf("%8s", &courseCode[semester - 1][w - 1]);
            rewind(stdin);
            totalNumCourse++;

            //Course Code Format Checker
            int valid = 0;
            do
            {

                if (courseCodeValid(courseCode))
                {
                    strcpy(courseCode[semester - 1][w - 1], courseCode);
                    valid = 1;
                }
                else
                {
                    printf(RED"Invalid Course Code. Please re-enter.\n"RESET);
                    printf(CYAN"Enter Course Code %d: "RESET, w);
                    scanf("%8s", &courseCode);
                    rewind(stdin);
                }


            } while (valid != 1);
        }
        printf("\n");

    }

    //Enter Current Semester Session
    printf("\nEnter Current Semester Session (e.g)[1,2,3]: ");
    scanf("%d", &currentSemester);

    //Credit Hours
    //Credit hours calculate by semester all added
    int len = 0;

    for (int semester = 0; semester < MAX_SEMESTER; semester++)
    {
        int a = 0;
        for (int j = 0; j < coursesPerSemester[semester]; j++)
        {
            len = strlen(courseCode[semester][j]);
            int i = len - 1;

            creditHours[semester][j] = courseCode[semester][j][i] - '0';
        }
    }


    //Enter Grade Obtained
    int valid = 0;

    for (int semester = 0; semester < MAX_SEMESTER;semester++)
    {
        printf("\nSemester %d\n", semester + 1);
        for (int j = 0; j < coursesPerSemester[semester]; j++)
        {
            printf("Grade Obtained for %s: ", strupr(courseCode[semester][j]));
            scanf("%s", &gradeAlpha[semester][j]);
            rewind(stdin);
        }
    }
    //Grade Point

    for (int semester = 0; semester < MAX_SEMESTER; semester++)
    {
        for (int j = 0; j < coursesPerSemester[semester]; j++)
        {
            float num = 0.0;
            int invalid = 1;
            if (strcmp(gradeAlpha[semester][j], A) == 0)
            {
                num = 4.00;
                invalid = 0;
            }
            else if (strcmp(gradeAlpha[semester][j], AM) == 0)
            {
                num = 3.75;
                invalid = 0;
            }
            else if (strcmp(gradeAlpha[semester][j], BP) == 0)
            {
                num = 3.50;
                invalid = 0;
            }
            else if (strcmp(gradeAlpha[semester][j], B) == 0)
            {
                num = 3.00;
                invalid = 0;
            }
            else if (strcmp(gradeAlpha[semester][j], BM) == 0)
            {
                num = 2.75;
                invalid = 0;
            }
            else if (strcmp(gradeAlpha[semester][j], CP) == 0)
            {
                num = 2.50;
                invalid = 0;
            }
            else if (strcmp(gradeAlpha[semester][j], C) == 0)
            {
                num = 2.00;
                invalid = 0;
            }
            else if (strcmp(gradeAlpha[semester][j], F) == 0)
            {
                num = 0.00;
                invalid = 0;
            }
            else
            {
                printf(RED"Invalid Grade Point Entered! Please re-enter."RESET);
                printf("Grade Obtained for %s: ", courseCode[semester][j]);
                scanf("%s", &gradeAlpha[semester][j]);
                rewind(stdin);
            }
            gradeP[semester][j] = num;
        }
    }



    //Quality Point
    printf("\nQuality Point\n");
    for (int semester = 0; semester < MAX_SEMESTER; semester++)
    {
        printf("Semester %d\n", semester + 1);
        for (int i = 0; i < coursesPerSemester[semester];i++)
        {

            qualityPoint[semester][i] = gradeP[semester][i] * creditHours[semester][i];
            printf("Quality Point Of %s = %.2f\n", courseCode[semester][i], qualityPoint[semester][i]);
        }
    }
    //Combine quality points and credit hour into 3 sem
    for (int semester = 0; semester < MAX_SEMESTER; semester++)
    {
        for (int i = 0; i < coursesPerSemester[semester];i++)
        {
            qualityPointSem[semester] += qualityPoint[semester][i];
            totalQualityPoint += qualityPointSem[semester];
            creditHoursSem[semester] += creditHours[semester][i];
            totalCreditHours += creditHoursSem[semester];
        }
    }

    //GPA
    for (int semester = 0; semester < MAX_SEMESTER;semester++)
    {
        gpa[semester] = qualityPointSem[semester] / creditHoursSem[semester];
    }
    //CGPA
    cgpa = totalQualityPoint / totalCreditHours;
    printf("Press Enter to continue...\n");
    getchar();

    mainMenu();
}
//----------------------GPA & CGPA----------------------//
void viewGPAT() {
    printf("\033[H\033[J");

    printf(YELLOW"Staff Mode\n");
    printf("----------------------------\n"RESET);
    printf("Name        : %-99s\n", name);
    printf("Student ID  : %-10s\n", id);
    printf("Current Sem : %d\n", currentSemester);
    printf("----------------------------\n");
    printf("GPA\n");
    printf("Sem 1       : %-4.2f", gpa[0]);
    if (gpa[0] > 2.85) {
        printf(GREEN" Passed\n"RESET);
    }
    else { printf(RED" Failed\n"RESET); }
    printf("Sem 2       : %-4.2f", gpa[1]);
    if (gpa[1] > 2.85) {
        printf(GREEN" Passed\n"RESET);
    }
    else { printf(RED" Failed\n"RESET); }
    printf("Sem 3       : %-4.2f", gpa[2]);
    if (gpa[2] > 2.85) {
        printf(GREEN" Passed\n"RESET);
    }
    else { printf(RED" Failed\n"RESET); }


    printf("Press Enter to continue...\n");
    getchar();
    staffMenu();
}


void viewCGPAT()
{
    printf("\033[H\033[J");

    printf(YELLOW"Staff Mode\n");
    printf("----------------------------\n"RESET);
    printf("Name        : %-99s\n", name);
    printf("Student ID  : %-10s\n", id);
    printf("Current Sem : %d\n", currentSemester);
    printf("----------------------------\n");
    printf("CGPA        : %-4.2f", cgpa);
    if (cgpa > 2.85) {
        printf(GREEN" Passed\n"RESET);
    }
    else { printf(RED" Failed\n"RESET); }
    printf("Press Enter to continue...\n");
    getchar();
    staffMenu();
}
void viewGPAS() {
    printf("\033[H\033[J");

    printf(GREEN"Student Mode\n");
    printf("----------------------------\n"RESET);
    printf("Name        : %-99s\n", name);
    printf("Student ID  : %-10s\n", id);
    printf("Current Sem : %d\n", currentSemester);
    printf("----------------------------\n");
    printf("GPA\n");
    printf("Sem 1       : %-4.2f", gpa[0]);
    if (gpa[0] > 2.85) {
        printf(GREEN" Passed\n"RESET);
    }
    else { printf(RED" Failed\n"RESET); }
    printf("Sem 2       : %-4.2f", gpa[1]);
    if (gpa[1] > 2.85) {
        printf(GREEN" Passed\n"RESET);
    }
    else { printf(RED" Failed\n"RESET); }
    printf("Sem 3       : %-4.2f", gpa[2]);
    if (gpa[2] > 2.85) {
        printf(GREEN" Passed\n"RESET);
    }
    else { printf(RED" Failed\n"RESET); }

    printf("Press Enter to continue...\n");
    getchar();
    studentMenu();
}


void viewCGPAS()
{
    printf("\033[H\033[J");

    printf(GREEN"Student Mode\n");
    printf("----------------------------\n"RESET);
    printf("Name        : %-99s\n", name);
    printf("Student ID  : %-10s\n", id);
    printf("Current Sem : %d\n", currentSemester);
    printf("----------------------------\n");
    printf("CGPA        : %-4.2f", cgpa);
    if (cgpa > 2.85) {
        printf(GREEN" Passed\n"RESET);
    }
    else { printf(RED" Failed\n"RESET); }
    printf("Press Enter to continue...\n");
    getchar();
    studentMenu();
}
void generateGPA()
{
    printf("\033[H\033[J");
    printf(
        YELLOW "----------------------------\n"
        "Staff Mode\n"
        "----------------------------\n"
        RESET "Name        : % -99s\n"
        "Student ID  : %-10s\n"
        "----------------------------\n", name, id
    );
    genGPA(durationSeconds);
    printf("Press Enter to continue...\n");
    getchar();
    staffMenu();
}
void generateCGPA()
{
    printf("\033[H\033[J");
    printf(
        YELLOW "----------------------------\n"
        "Staff Mode\n"
        "----------------------------\n"
        RESET "Name        : %-99s\n"
        "Student ID  : %-10s\n"
        "----------------------------\n", name, id
    );
    genCGPA(durationSeconds);
    printf("Press Enter to continue...\n");
    getchar();
    staffMenu();
}
//----------------------- Loading Screen ----------------------------//
int genGPA(int seconds)
{
    char animation[] = { '|', '/', '-', '\\' };
    int animationLength = sizeof(animation) / sizeof(animation[0]);

    int cycles = seconds * 10; // Number Of Cycle

    for (int i = 0; i < cycles; i++)
    {
        printf(CYAN"Generating GPA... %c\r"RESET, animation[i % animationLength]);
        rewind(stdout);

        Sleep(100); // Sleep 0.1 seconds
    }
    printf("\nGeneration complete!\n");
}
int genCGPA(int seconds)
{
    char animation[] = { '|', '/', '-', '\\' };
    int animationLength = sizeof(animation) / sizeof(animation[0]);

    int cycles = seconds * 10; 

    for (int i = 0; i < cycles; i++)
    {
        printf(CYAN"Generating CGPA... %c\r"RESET, animation[i % animationLength]);
        rewind(stdout);

        Sleep(100);
    }
    printf("\nGeneration complete!\n");
}



//-----------------------------   Checker    -----------------------------//

int nameValid(const char* name)
{
    //Empty
    if (strlen(name) == 0)
    {
        return 0;
    }
    //Not Number Only //Not Spaces Only 
    for (int n = 0; n < strlen(name); n++)
    {
        if (!isalpha(name[n]) && name[n] != ' ')
            return 0;
    }
    //Start End with ' '
    if (name[0] == ' ' || name[strlen(name) - 1] == ' ')
        return 0;

    return 1; //Valid
}
int idValid(const char* id)
{
    int idLength;
    idLength = strlen(id);

    //9 character
    if (idLength != 9)
        return 0;
    //Check abcs (first 4 char)
    for (int i = 0;i < 4;i++)
    {
        if (!isalpha(id[i]))
            return 0;
    }
    //Check last 5 char is num
    for (int i = 5; i < 9; i++)
    {
        if (!isdigit(id[i]))
            return 0;
    }
    return 1; //Valid
}
int courseCodeValid(const char* courseCode)
{
    int courseCodeLength;
    courseCodeLength = strlen(courseCode);
    //7 Character [AAA1473]
    if (courseCodeLength != 7)
        return 0;
    //Check for abcs first 3 char
    for (int a = 0; a < 3; a++)
    {
        if (!isalpha(courseCode[a]))
            return 0;
    }
    //Check for num last 4 char
    for (int a = 3; a < 7; a++)
    {
        if (!isdigit(courseCode[a]))
            return 0;
    }
    return 1; //Valid
}

