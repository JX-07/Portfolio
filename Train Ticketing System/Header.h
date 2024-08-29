#pragma once

#ifndef HEADER_H
#define HEADER_H		// HEADER GUARD (PREVENT MULTI INCLUSIONS)


// DEFINE COACH PAX
#define COACH_A_PAX 90
#define COACH_B_PAX 80
#define COACH_C_PAX 72
#define COACH_D_PAX 24

// USER LOGIN ID FORMAT 
#define USER_ID_FORMAT 6
#define USER_ID_ALPHA 2
#define USER_ID_NUMBER 4

// CONSTANT VARIABLE
#define MAX_STAFF 200
#define MAX_MEMBERS 200
#define MAX_SCHEDULE 100 
#define MAX_MATCHING_SCHEDULES 100
#define MAX_TICKET_BOOKING 200


// FUNCTION DECLARATIONS

// INTERFACES

	// MAIN MENU
	void mainMenu();
	void mainMenuFORMAT();
	void mainMenuFUNCTION();
	void readChoice();
	int readMember();
	int readStaff();
	int readSchedule();

	// LOGIN PAGE
	void loginPage();
	void loginUserIDInvalid();
	void loginUserPassInvalid();
	void welcomeMessage();

	// PASSWORD RECOVERY
	void passwordRecov(int memCount, int staffCount);
	void passwordRecovAns();
	void passwordRecovStrAns();
	void passwordRecovInvalid();

	// MEMBER MODULE
	void memberMain(char userID[USER_ID_FORMAT]);
	void memberMenu(char userID[USER_ID_FORMAT]);
	void memberNav(int n, char userID[USER_ID_FORMAT]);
	void read_memberinfo();
	void searchMember();
	void generateMemberId(char* newMemberId);
	void add_new_member();
	void deleteMember();
	void deleteMemberSelf(char userID[USER_ID_FORMAT]);
	void passwordRecovery();
	void modifyInfo(char userID[USER_ID_FORMAT]);
	void displayMember();

	// STAFF MODULE
	void staffMain();
	void adminMenu();
	void adminNav(int n); // ADMIN Menu MODULE
	void adminNav(int n);
	void staffMenu(); // STAFF Menu MODULE
	void staffNav(int n);
		// ADMIN SUBMODULES
		void tabDisplay();
		void adminAdd();
		void adminModify();
		void adminRemove();
		void adminSearch();
		void adminSort();
		void adminDisplay();
		// STAFF SUBMODULES
		void staffDisplay();
		void staffModify();
		// VALIDATION FUNCTIONS
		void validateID(struct Staff* staff);
		void validateName(struct Staff* staff);
		void validatePassword(struct Staff* staff);
		void validateRecovery(struct Staff* staff);
		void validateContact(struct Staff* staff);
		// SORTING ALGORITHM
		void sortSort(int i, int j, struct Staff temp, struct Staff sort[100]);

	// TRAIN SCHEDULE MODULE
	void main_schedule();
	void menu_schedule();
	int read_schedule();
	void display_schedule();
	void add_schedule();
	void search_schedule();
	void modify_schedule();
	void delete_schedule();
	void sort_schedule();

	// BOOKING MODULE
	int extractNumber(char* str);
	void add_ticketBooking(char userID[USER_ID_FORMAT]);
	void search_ticketBooking();
	void modify_ticketBooking(char userID[USER_ID_FORMAT]);
	void displayAll_ticketBookingStaff();
	void displayAll_ticketBookingMember(char userID[USER_ID_FORMAT]);
	void payment_ticketBooking(char userID[USER_ID_FORMAT]);
	void cancel_ticketBooking(char userID[USER_ID_FORMAT]);
	void generate_ticketReport();

	void read_ticketBooking();
	void ticketIdGenerate(char* newTicketId);
	void seatSelection(int train);
	void seatBooking();
	void seatSelectionCA();
	void seatSelectionCAA();
	void seatSelectionCB();
	void seatSelectionCBB();
	void seatSelectionCC();
	void seatSelectionCCC();
	void seatSelectionCD();
	void seatSelectionCDD();

// FORMAT FUNCTIONS
void thomasLogo();


// VARIBALE DECLARATION
char userID[USER_ID_FORMAT];		// USE FOR LOGIN
char userPassword[20];
int menuChoice;


// STRUCTURE DEDCLARATION

// STAFF INFO

struct Staff {                     
	char id[7];
	char name[21];
	char password[5];
	int recov_ques;
	char recov_ans[21];
	char position[21];
	char contact_no[14];
}staff;

struct Staff staffs[MAX_STAFF];

// MEMBER INFO

typedef struct {                   
	char memberId[7];
	char firstName[25];
	char lastName[25];
	char gender;
	char email[25];
	char phoneNo[12];
	char memIc[13];
	char password[25];
	int securityOption;
	int securityRespond;
} MemberInfo;

MemberInfo member[MAX_MEMBERS];

// TRAIN SCHEDULE INFO

typedef struct {                  
	char scheduleID[10];
	int day;
	int month;
	int year;
	char trainID[5];
	char staffID[10];
	char departState[30];
	char arriveState[30];
	int departTime, arriveTime;
	int price, seat;
} schedule;

schedule trainSchedule[MAX_SCHEDULE];
schedule promptSchedule;

// TICKET BOOKING INFO

typedef struct {
	int day, month, year;
}date;

date train_departure_date;

typedef struct {
	double totalAmount;
	char paymentMethod[20];
	char paymentStatus[20];
}payment;

typedef struct {
	char ticket_id[10];
	char member_id[10];
	date booking_date;
	char trainScheduleID[10];
	int ticket_seat;
	payment booking_payment;
}booking;

booking ticketBooking[MAX_TICKET_BOOKING];
booking userInput;



#endif

