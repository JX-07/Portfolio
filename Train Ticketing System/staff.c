#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Header.h"


char recovQues[6][51] = {
	"What is your favourite food?", 
	"Who is your favourite idol?", 
	"What is your favourite movie?", 
	"What is the name of your favourite pet?", 
	"Who is your favourite childhood hero?", 
	"Where is your favourite holiday destination?"
}; 



void staffMain() {
	FILE* fRead;
	fRead = fopen("staff.bin", "rb");
	int index = 0;
	while (fread(&staffs[index], sizeof(struct Staff), 1, fRead) != 0) {
		index++;
	}
	for (int i = 0; i < MAX_STAFF; i++) {
		if (strcmp(userID, staffs[i].id) == 0) {
			if (strcmp(userPassword, staffs[i].password) == 0) {
				if (strcmp(staffs[i].position, "Administrator") == 0)
					adminMenu();
				else
					staffMenu();
			}
			else {
				loginUserPassInvalid();
				break;
			}
		}
	}
	fclose(fRead);
}

void adminMenu() {
	char input;
	int select = 0;
	printf("\033[H\033[J\033[?25l");
	printf("=========================================================================================================================\n");
	printf("                                                  STAFF MENU  ( ADMIN )                                                  \n");
	printf("=========================================================================================================================\n");
	printf("                                          What action would you like to perform?                                         \n");
	printf("                                    \033[5m*Navigate through arrow keys and space to select*\033[0m                                    \n");
	printf("=========================================================================================================================\n");
	printf(" /                                        \033[5m>\033[0m           Staff Function          \033[5m<\033[0m                                        \\ \n");
	printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
	printf("|\033[7m                  (1)                  \033[0m|                  (2)                  |                  (3)                  |\n");
	printf("|\033[7m            Add Staff Info             \033[0m|           Modify Staff Info           |           Remove Staff Info           |\n");
	printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
	printf("|                  (4)                  |                  (5)                  |                  (6)                  |\n");
	printf("|           Search Staff Info           |            Sort Staff Info            |          Display Staff Info           |\n");
	printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
	printf(" /                                        \033[5m>\033[0m     Train Scheduling Function     \033[5m<\033[0m                                        \\ \n");
	printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
	printf("|                  (1)                  |                  (2)                  |                  (3)                  |\n");
	printf("|           Add Train Schedule          |         Modify Train Schedule         |         Remove Train Schedule         |\n");
	printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
	printf(" /                                         \033[5m>\033[0m     Ticket Booking Function     \033[5m<\033[0m                                         \\ \n");
	printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
	printf("|                  (1)                  |                  (2)                  |                  (3)                  |\n");
	printf("|         Search Ticket Booking         |         Generate Ticket Report        |       Display All Ticket Booking      |\n");
	printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
	printf(" /                                        \033[5m>\033[0m          Member Function          \033[5m<\033[0m                                        \\ \n");
	printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
	printf("|                  (1)                  |                  (2)                  |                  (3)                  |\n");
	printf("|       Search Member Information       |     Display All Member Information    |         Remove Member Account         |\n");
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
			if (select >= 3 && select <= 15)
				select -= 3;
			break;
		case 75://left
			if (select != 0 && select != 3 && select != 6 && select != 9 && select != 12 && select != 15)
				select--;
			break;
		case 77://right
			if (select != 2 && select != 5 && select != 8 && select != 11 && select != 14 && select != 15)
				select++;
			break;
		case 80://down
			if (select >= 0 && select <= 11)
				select += 3;
			else if (select >= 12 && select <= 14)
				select = 15;
			break;
		case 32:
			adminNav(select);
			break;
		}
		if (select == 0) {
			printf("\033[26A");
			printf("|\033[7m                  (1)                  \033[0m|\n");
			printf("|\033[7m            Add Staff Info             \033[0m|\n");
			printf("\033[24B");
		}
		else {
			printf("\033[26A");
			printf("|                  (1)                  |\n");
			printf("|            Add Staff Info             |\n");
			printf("\033[24B");
		}
		if (select == 1) {
			printf("\033[26A\033[40C");
			printf("|\033[7m                  (2)                  \033[0m|\n");
			printf("\033[40C");
			printf("|\033[7m           Modify Staff Info           \033[0m|\n");
			printf("\033[24B");
		}
		else {
			printf("\033[26A\033[40C");
			printf("|                  (2)                  |\n");
			printf("\033[40C");
			printf("|           Modify Staff Info           |\n");
			printf("\033[24B");
		}
		if (select == 2) {
			printf("\033[26A\033[80C");
			printf("|\033[7m                  (3)                  \033[0m|\n");
			printf("\033[80C");
			printf("|\033[7m           Remove Staff Info           \033[0m|\n");
			printf("\033[24B");
		}
		else {
			printf("\033[26A\033[80C");
			printf("|                  (3)                  |\n");
			printf("\033[80C");
			printf("|           Remove Staff Info           |\n");
			printf("\033[24B");
		}
		if (select == 3) {
			printf("\033[23A");
			printf("|\033[7m                  (4)                  \033[0m|\n");
			printf("|\033[7m           Search Staff Info           \033[0m|\n");
			printf("\033[21B");
		}
		else {
			printf("\033[23A");
			printf("|                  (4)                  |\n");
			printf("|           Search Staff Info           |\n");
			printf("\033[21B");
		}
		if (select == 4) {
			printf("\033[23A\033[40C");
			printf("|\033[7m                  (5)                  \033[0m|\n");
			printf("\033[40C");
			printf("|\033[7m            Sort Staff Info            \033[0m|\n");
			printf("\033[21B");
		}
		else {
			printf("\033[23A\033[40C");
			printf("|                  (5)                  |\n");
			printf("\033[40C");
			printf("|            Sort Staff Info            |\n");
			printf("\033[21B");
		}
		if (select == 5) {
			printf("\033[23A\033[80C");
			printf("|\033[7m                  (6)                  \033[0m|\n");
			printf("\033[80C");
			printf("|\033[7m          Display Staff Info           \033[0m|\n");
			printf("\033[21B");
		}
		else {
			printf("\033[23A\033[80C");
			printf("|                  (6)                  |\n");
			printf("\033[80C");
			printf("|          Display Staff Info           |\n");
			printf("\033[21B");
		}
		if (select == 6) {
			printf("\033[18A");
			printf("|\033[7m                  (1)                  \033[0m|\n");
			printf("|\033[7m           Add Train Schedule          \033[0m|\n");
			printf("\033[16B");
		}
		else {
			printf("\033[18A");
			printf("|                  (1)                  |\n");
			printf("|           Add Train Schedule          |\n");
			printf("\033[16B");
		}
		if (select == 7) {
			printf("\033[18A\033[40C");
			printf("|\033[7m                  (2)                  \033[0m|\n");
			printf("\033[40C");
			printf("|\033[7m         Modify Train Schedule         \033[0m|\n");
			printf("\033[16B");
		}
		else {
			printf("\033[18A\033[40C");
			printf("|                  (2)                  |\n");
			printf("\033[40C");
			printf("|         Modify Train Schedule         |\n");
			printf("\033[16B");
		}
		if (select == 8) {
			printf("\033[18A\033[80C");
			printf("|\033[7m                  (3)                  \033[0m|\n");
			printf("\033[80C");
			printf("|\033[7m         Remove Train Schedule         \033[0m|\n");
			printf("\033[16B");
		}
		else {
			printf("\033[18A\033[80C");
			printf("|                  (3)                  |\n");
			printf("\033[80C");
			printf("|         Remove Train Schedule         |\n");
			printf("\033[16B");
		}
		if (select == 9) {
			printf("\033[13A");
			printf("|\033[7m                  (1)                  \033[0m|\n");
			printf("|\033[7m         Search Ticket Booking         \033[0m|\n");
			printf("\033[11B");
		}
		else {
			printf("\033[13A");
			printf("|                  (1)                  |\n");
			printf("|         Search Ticket Booking         |\n");
			printf("\033[11B");
		}
		if (select == 10) {
			printf("\033[13A\033[40C");
			printf("|\033[7m                  (2)                  \033[0m|\n");
			printf("\033[40C");
			printf("|\033[7m         Generate Ticket Report        \033[0m|\n");
			printf("\033[11B");
		}
		else {
			printf("\033[13A\033[40C");
			printf("|                  (2)                  |\n");
			printf("\033[40C");
			printf("|         Generate Ticket Report        |\n");
			printf("\033[11B");
		}
		if (select == 11) {
			printf("\033[13A\033[80C");
			printf("|\033[7m                  (3)                  \033[0m|\n");
			printf("\033[80C");
			printf("|\033[7m       Display All Ticket Booking      \033[0m|\n");
			printf("\033[11B");
		}
		else {
			printf("\033[13A\033[80C");
			printf("|                  (3)                  |\n");
			printf("\033[80C");
			printf("|       Display All Ticket Booking      |\n");
			printf("\033[11B");
		}
		if (select == 12) {
			printf("\033[8A");
			printf("|\033[7m                  (1)                  \033[0m|\n");
			printf("|\033[7m       Search Member Information       \033[0m|\n");
			printf("\033[6B");
		}
		else {
			printf("\033[8A");
			printf("|                  (1)                  |\n");
			printf("|       Search Member Information       |\n");
			printf("\033[6B");
		}
		if (select == 13) {
			printf("\033[8A\033[40C");
			printf("|\033[7m                  (2)                  \033[0m|\n");
			printf("\033[40C");
			printf("|\033[7m     Display All Member Information    \033[0m|\n");
			printf("\033[6B");
		}
		else {
			printf("\033[8A\033[40C");
			printf("|                  (2)                  |\n");
			printf("\033[40C");
			printf("|     Display All Member Information    |\n");
			printf("\033[6B");
		}
		if (select == 14) {
			printf("\033[8A\033[80C");
			printf("|\033[7m                  (3)                  \033[0m|\n");
			printf("\033[80C");
			printf("|\033[7m         Remove Member Account         \033[0m|\n");
			printf("\033[6B");
		}
		else {
			printf("\033[8A\033[80C");
			printf("|                  (3)                  |\n");
			printf("\033[80C");
			printf("|         Remove Member Account         |\n");
			printf("\033[6B");
		}
		if (select == 15) {
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

void adminNav(int n) {
	printf("\033[?25h");
	switch (n) {
	case 0:
		adminAdd();
		break;
	case 1:
		adminModify();
		break;
	case 2:
		adminRemove();
		break;
	case 3:
		adminSearch();
		break;
	case 4:
		adminSort();
		break;
	case 5:
		adminDisplay();
		break;
	case 6:
		add_schedule();
		break;
	case 7:
		modify_schedule();
		break;
	case 8:
		delete_schedule();
		break;
	case 9:
		search_ticketBooking();
		break;
	case 10:
		generate_ticketReport();
		break;
	case 11:
		displayAll_ticketBookingStaff();
		break;
	case 12:
		searchMember();
		break;
	case 13:
		displayMember();
		break;
	case 14:
		deleteMember();
		break;
	case 15:
		printf("\033[H\033[J");     // CLS
		mainMenu();
		break;
	}
}

void staffMenu() {
	printf("\033[H\033[J");
	char input;
	int select = 0;
	printf("=========================================================================================================================\n");
	printf("                                                        STAFF MENU                                                       \n");
	printf("=========================================================================================================================\n");
	printf("                                          What action would you like to perform?                                         \n");
	printf("                                    \033[5m*Navigate through arrow keys and space to select*\033[0m                                    \n");
	printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");
	printf("|\033[7m                  (1)                  \033[0m|                  (2)                  |                  (3)                  |\n");
	printf("|\033[7m          Display Information          \033[0m|           Modify Information          |                  Exit                 |\n");
	printf("+---------------------------------------+---------------------------------------+---------------------------------------+\n");

	for (int i = 0;; i++) { //\033[47;30m
		input = getch();
		rewind(stdin);
		switch (input) {
		case -32:
			break;
		case 75://left
			if (select != 0)
				select--;
			break;
		case 77://right
			if (select != 2)
				select++;
			break;
		case 32:
			staffNav(select);
			break;
		}
		if (select == 0) {
			printf("\033[3A");
			printf("|\033[7m                  (1)                  \033[0m|\n");
			printf("|\033[7m          Display Information          \033[0m|\n");
			printf("\033[B");
		}
		else {
			printf("\033[3A");
			printf("|                  (1)                  |\n");
			printf("|          Display Information          |\n");
			printf("\033[B");
		}
		if (select == 1) {
			printf("\033[3A\033[40C");
			printf("|\033[7m                  (2)                  \033[0m|\n");
			printf("\033[40C");
			printf("|\033[7m           Modify Information          \033[0m|\n");
			printf("\033[B");
		}
		else {
			printf("\033[3A\033[40C");
			printf("|                  (2)                  |\n");
			printf("\033[40C");
			printf("|           Modify Information          |\n");
			printf("\033[B");
		}
		if (select == 2) {
			printf("\033[3A\033[80C");
			printf("|\033[7m                  (3)                  \033[0m|\n");
			printf("\033[80C");
			printf("|\033[7m                  Exit                 \033[0m|\n");
			printf("\033[B");
		}
		else {
			printf("\033[3A\033[80C");
			printf("|                  (3)                  |\n");
			printf("\033[80C");
			printf("|                  Exit                 |\n");
			printf("\033[B");
		}
	}
}

void staffNav(int n) {
	switch (n) {
	case 0:
		staffDisplay();
		break;
	case 1:
		staffModify();
		break;
	case 2:
		exit(0);
		break;
	}
}

void adminAdd() {
	char optionCont = 'A', option = 'A';
	char staffIDTemp[7] = "ST0000";
	struct Staff temp;
	int validateStatus = 0, optionInt = 0, invalidLines = -1;
	FILE* fRead;
	fRead = fopen("staff.bin", "rb");
	FILE* fAdd;
	fAdd = fopen("staff.bin", "ab");
	printf("\033[H\033[J");
	printf("=========================================================================================================================\n");
	printf("                                             ADD STAFF INFORMATION MODULE                                                \n");
	printf("=========================================================================================================================\n");
	do {
		invalidLines++;
		// FOLLOW LATEST STAFF ID?
		printf("Continue latest Staff ID? (Y/N): ");
		(void)scanf("%c", &option);
		rewind(stdin);
		option = toupper(option);
		// INCORRECT INPUT
		if (option != 'Y' && option != 'N')
			printf("Incorrect option entered..\n");
	} while (option != 'Y' && option != 'N');
	for (int i = 0; i < (invalidLines * 2) + 1; i++) {
		printf("\033[A\033[K");
	}
	printf("Continue latest Staff ID? (Y/N): %c\n", option);

	// FOLLOW STAFF ID
	if (option == 'Y') {
		// Read latest staff ID
		while (!feof(fRead)) {
			fread( &staff, sizeof(struct Staff), 1, fRead);
			if (strcmp(staffIDTemp, staff.id) < 0)
				strcpy(staffIDTemp, staff.id);
		}
		strcpy(staff.id, staffIDTemp);
		printf("Latest staff ID is %s. ", staff.id);
		// STRING INCREMENT
		if (staff.id[5] == '9') {
			if (staff.id[4] == '9') {
				if (staff.id[3] == '9') {
					staff.id[5] = '0';
					staff.id[4] = '0';
					staff.id[3] = '0';
					staff.id[2]++;
				}
				else {
					staff.id[5] = '0';
					staff.id[4] = '0';
					staff.id[3]++;
				}
			}
			else {
				staff.id[5] = '0';
				staff.id[4]++;
			}
		}
		else {
			staff.id[5]++;
		}
		option = 'A';
		invalidLines = -1;
		do {
			invalidLines++;
			// FOLLOW LATEST STAFF ID?
			printf("Create data for staff %s? (Y/N): ", staff.id);
			(void)scanf("%c", &option);
			rewind(stdin);
			option = toupper(option);
			// INCORRECT INPUT
			if (option != 'Y' && option != 'N')
				printf("Incorrect option entered..\n");
		} while (option != 'Y' && option != 'N');
		for (int i = 0; i < (invalidLines * 2) + 1; i++) {
			printf("\033[A\033[K");
		}
		printf("Create data for staff %s? (Y/N): %c\n", staff.id, option);

	}

	if (option == 'N') {
		int availID = 0;
		invalidLines = -1;
		do {
			invalidLines++;
			availID = 0;
			validateID(&staff);
			rewind(fRead);
			while (!feof(fRead)) {
				fread(&temp, sizeof(struct Staff), 1, fRead);
				if (strcmp(temp.id, staff.id) == 0) {
					availID++;
					printf("Duplicate ID Found\n\n");
					break;
				}
			}
		} while (availID != 0);
	}
	for (int i = 0; i < (invalidLines * 3) + 1; i++) {
		printf("\033[A\033[K");
	}
	printf("Staff ID: %s\n", staff.id);
	fclose(fRead);
	option = 'A';

	printf("\nCreating data for staff %s\n", staff.id);
	printf("------------------------------------------------------\n");

	// OBTAIN, VALIDATE, REDECLARE VALIDATESTATUS EVEYRHTING
	validateName(&staff);
	validatePassword(&staff);

	//Password Recovery
	printf("\nPASSWORD RECOVERY QUESTIONS\n");
	for (int i = 0; i < 6; i++) {
		printf("%d) %s\n", i + 1, recovQues[i]);
	}
	invalidLines = -1;
	staff.recov_ques = 9;
	do {
		invalidLines++;
		printf("Select Password Recovery Question: ");
		(void)scanf("%d", &staff.recov_ques);
		rewind(stdin);
		if (staff.recov_ques < 1 || staff.recov_ques > 6) {
			printf("Option is limited from 1 to 6.. Please try again\n");
		}
	} while (staff.recov_ques < 1 || staff.recov_ques > 6);
	for (int i = 0; i < (invalidLines * 2) + 9; i++) {
		printf("\033[A\033[K");
	}
	printf("%-30s : %d) %s\n", "Password Recovery Question", staff.recov_ques, recovQues[staff.recov_ques - 1]);
	validateRecovery(&staff);

	//Position
	printf("\nSTAFF POSITION TABLE\n");
	printf("1) Administrator            7) Security Personnel\n");
	printf("2) Ticketing Agent          8) Janitor\n");
	printf("3) Train Scheduler          9) Sales and Marketing Representative\n");
	printf("4) Ticket Inspector        10) Finance and Accounting Personnel\n");
	printf("5) Train Operator          11) Customer Service Representative\n");
	printf("6) Technical Support\n");
	invalidLines = -1;
	do {
		invalidLines++;
		printf("Select Staff Position: ");
		(void)scanf("%d", &optionInt);
		rewind(stdin);
		if (optionInt < 1 || optionInt > 11) {
			printf("Option is limited from 1 to 11.. Please try again\n");
		}
	} while (optionInt < 1 || optionInt > 11);
	switch (optionInt) {
		case 1:
			strcpy(staff.position, "Administrator");
			break;
		case 2:
			strcpy(staff.position, "Ticketing Agent");
			break;
		case 3:
			strcpy(staff.position, "Train Scheduler");
			break;
		case 4:
			strcpy(staff.position, "Ticket Inspector");
			break;
		case 5:
			strcpy(staff.position, "Train Operator");
			break;
		case 6:
			strcpy(staff.position, "Technical Support");
			break;
		case 7:
			strcpy(staff.position, "Security Personnel");
			break;
		case 8:
			strcpy(staff.position, "Janitor");
			break;
		case 9:
			strcpy(staff.position, "SnM Representative");
			break;
		case 10:
			strcpy(staff.position, "FnA Personnel");
			break;
		case 11:
			strcpy(staff.position, "CS Representative");
			break;
		}
	for (int i = 0; i < (invalidLines * 2) + 9; i++) {
		printf("\033[A\033[K");
	}
	printf("%-30s : %s\n", "Staff Position", staff.position);

	//Contact No.
	validateContact(&staff);

	fwrite( &staff, sizeof(struct Staff), 1, fAdd);
	fclose(fAdd);
	printf("------------------------------------------------------\n");
	printf("New staff data entered successfully!");

	//OPTION TO REPEAT 
	option = 'A';
	do {
		printf("\n\nContinue adding new staff data? (Y/N): ");
		(void)scanf("%c", &option);
		rewind(stdin);
		option = toupper(option);
		if (option != 'Y' && option != 'N')
			printf("\nIncorrect option entered..\n");
	} while (option != 'Y' && option != 'N');
	if (option == 'Y') {
		printf("\033[H\033[J");
		adminAdd();
	}
	if (option == 'N') {
		printf("\033[H\033[J");
		adminMenu();
	}
}

void adminModify() {
	FILE* fptr, * fptr2;
	fptr = fopen("staff.bin", "rb");
	fptr2 = fopen("staff.bin", "ab");
	struct Staff temp[100] = { "ST0001", "Nigga", "1234", "1 Niggas", "Nigga", "60123456789" };
	struct Staff update;
	char optionCont = 'A', input;
	int option = 0, optionPosition = 0,invalidLines = -1, i = 0, removeLocation = 0;
	printf("\033[H\033[J");
	printf("=========================================================================================================================\n");
	printf("                                             MODIFY STAFF INFORMATION MODULE                                             \n");
	printf("=========================================================================================================================\n");
	int availID = 0;
	invalidLines = -1;
	do {
		invalidLines++;
		availID = 0;
		i = 0;
		printf("View Staff Information? (Press Tab) | Return to Main Menu? (Press Esc)	\n");
		input = getch();
		rewind(stdin);
		printf("\033[A\033[K");
		if (input == 9) {
			tabDisplay();
		}
		else if (input == 27) {
			adminMenu();
		}
		validateID(&staff);
		rewind(fptr);
		while (fread(&temp[i], sizeof(struct Staff), 1, fptr) == 1) {
			if (strcmp(staff.id, temp[i].id) == 0) {
				availID++;
				strcpy(staff.id, temp[i].id);
				strcpy(staff.name, temp[i].name);
				strcpy(staff.password, temp[i].password);
				staff.recov_ques = temp[i].recov_ques;
				strcpy(staff.recov_ans, temp[i].recov_ans);
				strcpy(staff.position, temp[i].position);
				strcpy(staff.contact_no, temp[i].contact_no);
				removeLocation = i;
			}
			i++;
		}
		if (availID == 0) {
			printf("Staff not found.\n");
		}
	} while (availID == 0);
	for (int j = 0; j < (invalidLines * 2) + 1; j++) {
		printf("\033[A\033[K");
	}
	strcpy(update.id, staff.id);
	strcpy(update.name, staff.name);
	strcpy(update.password, staff.password);
	update.recov_ques = staff.recov_ques;
	strcpy(update.recov_ans, staff.recov_ans);
	strcpy(update.position, staff.position);
	strcpy(update.contact_no, staff.contact_no);
	do {
		option = 0;
		printf(" __________________________________________________________    __________________________________________________________\n");
		printf("|  UNREVISED Staff Information                             |  |  UPDATED Staff Information                               |\n");
		printf(" ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯    ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
		printf("|  %-30s : %-21s  |  |  %-30s : %-21s  |\n", "Staff ID", staff.id, "Staff ID", update.id);
		printf("|  %-30s : %-21s  |  |  %-30s : ", "Staff Name", staff.name, "Staff Name");
		if (strcmp(staff.name,update.name) != 0)
			printf("\033[1;32m%-21s\033[1;0m", update.name);
		else
			printf("%-21s", update.name);
		printf("  |\n");
		printf("|  %-30s : %-21s  |  |  %-30s : ", "Staff Password", staff.password, "Staff Password");
		if (strcmp(staff.password, update.password) != 0)
			printf("\033[1;32m%-21s\033[1;0m", update.password);
		else
			printf("%-21s", update.password);
		printf("  |\n");
		printf("|  %-30s : %-21d  |  |  %-30s : ", "Staff Recovery Question", staff.recov_ques, "Staff Recovery Question");
		if (staff.recov_ques != update.recov_ques)
			printf("\033[1;32m%-21d\033[1;0m", update.recov_ques);
		else
			printf("%-21d", update.recov_ques);
		printf("  |\n");
		printf("|  %-30s : %-21s  |  |  %-30s : ", "Staff Recovery Answer", staff.recov_ans, "Staff Recovery Answer");
		if (strcmp(staff.recov_ans, update.recov_ans) != 0)
			printf("\033[1;32m%-21s\033[1;0m", update.recov_ans);
		else
			printf("%-21s", update.recov_ans);
		printf("  |\n");
		printf("|  %-30s : %-21s  |  |  %-30s : ", "Staff Position", staff.position, "Staff Position");
		if (strcmp(staff.position, update.position) != 0)
			printf("\033[1;32m%-21s\033[1;0m", update.position);
		else
			printf("%-21s", update.position);
		printf("  |\n");
		printf("|  %-30s : %-21s  |  |  %-30s : ", "Staff Contact Number", staff.contact_no, "Staff Contact Number");
		if (strcmp(staff.contact_no, update.contact_no) != 0)
			printf("\033[1;32m%-21s\033[1;0m", update.contact_no);
		else
			printf("%-21s", update.contact_no);
		printf("  |\n");
		printf(" ----------------------------------------------------------    ----------------------------------------------------------\n\n");
		fclose(fptr);

		printf("=========================================================================================================================\n");
		printf("                                                 Modification Selection                                                  \n");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf("               (1) Staff Name                (2) Staff Contact Number              (3) Staff Position                    \n");
		printf("               (4) Staff Password            (5) Staff Recovery Question & Answer                                        \n");
		printf("               (6) Apply Changes             (7) Discard Changes                                                         \n");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		invalidLines = -1;
		do {
			invalidLines++;
			printf("Option: ");
			(void)scanf("%d", &option);
			rewind(stdin);
			if (option < 1 || option > 7) {
				printf("Option is limited from 1 to 7.. Please try again\n");
			}
		} while (option < 1 || option > 7);
		for (int i = 0; i < (invalidLines * 2) + 1; i++) {
			printf("\033[A\033[K");
		}
		printf("Option: %d\n", option);
		switch (option) {
		case 1:
			validateName(&update);
			break;
		case 2:
			validateContact(&update);
			break;
		case 3:
			//Position
			printf("\nSTAFF POSITION TABLE\n");
			printf("1) Administrator            7) Security Personnel\n");
			printf("2) Ticketing Agent          8) Janitor\n");
			printf("3) Train Scheduler          9) Sales and Marketing Representative\n");
			printf("4) Ticket Inspector        10) Finance and Accounting Personnel\n");
			printf("5) Train Operator          11) Customer Service Representative\n");
			printf("6) Technical Support\n");
			invalidLines = -1;
			optionPosition = 0;
			do {
				invalidLines++;
				printf("Select Staff Position: ");
				(void)scanf("%d", &optionPosition);
				rewind(stdin);
				if (optionPosition < 1 || optionPosition > 11) {
					printf("Option is limited from 1 to 11.. Please try again\n");
				}
			} while (optionPosition < 1 || optionPosition > 11);
			switch (optionPosition) {
			case 1:
				strcpy(update.position, "Administrator");
				break;
			case 2:
				strcpy(update.position, "Ticketing Agent");
				break;
			case 3:
				strcpy(update.position, "Train Scheduler");
				break;
			case 4:
				strcpy(update.position, "Ticket Inspector");
				break;
			case 5:
				strcpy(update.position, "Train Operator");
				break;
			case 6:
				strcpy(update.position, "Technical Support");
				break;
			case 7:
				strcpy(update.position, "Security Personnel");
				break;
			case 8:
				strcpy(update.position, "Janitor");
				break;
			case 9:
				strcpy(update.position, "SnM Representative");
				break;
			case 10:
				strcpy(update.position, "FnA Personnel");
				break;
			case 11:
				strcpy(update.position, "CS Representative");
				break;
			}
			for (int i = 0; i < (invalidLines * 2) + 9; i++) {
				printf("\033[A\033[K");
			}
			printf("%-30s : %s\n", "Staff Position", update.position);
			break;
		case 4:
			validatePassword(&update);
			break;
		case 5:
			//Password Recovery
			printf("\nPASSWORD RECOVERY QUESTIONS\n");
			for (int z = 0; z < 6; z++) {
				printf("%d) %s\n", z + 1, recovQues[z]);
			}
			invalidLines = -1;
			update.recov_ques = 9;
			do {
				invalidLines++;
				printf("Select Password Recovery Question: ");
				(void)scanf("%d", &update.recov_ques);
				rewind(stdin);
				if (update.recov_ques < 1 || update.recov_ques > 6) {
					printf("Option is limited from 1 to 6.. Please try again\n");
				}
			} while (update.recov_ques < 1 || update.recov_ques > 6);
			for (int i = 0; i < (invalidLines * 2) + 9; i++) {
				printf("\033[A\033[K");
			}
			printf("%-30s : %d) %s\n", "Password Recovery Question", update.recov_ques, recovQues[update.recov_ques - 1]);
			validateRecovery(&update);
			printf("\033[A\033[K");

			break;
		case 6:
			//throw inside array
			strcpy(temp[removeLocation].id, update.id);
			strcpy(temp[removeLocation].name, update.name);
			strcpy(temp[removeLocation].password, update.password);
			temp[removeLocation].recov_ques = update.recov_ques;
			strcpy(temp[removeLocation].recov_ans, update.recov_ans);
			strcpy(temp[removeLocation].position, update.position);
			strcpy(temp[removeLocation].contact_no, update.contact_no);
			//throw into file
			(void)fopen("staff.bin", "wb");
			fclose(fopen("staff.bin", "wb"));
			for (int k = 0; k < i; k++) {
					fwrite(&temp[k], sizeof(struct Staff), 1, fptr2);
			}
			fclose(fptr2);
			printf("\nStaff %s updated.", staff.id);
			break;
		default:
			printf("\nModifications discarded.");
			break;
		}
		if (option != 6 && option != 7) {
			for (int i = 0; i < 21; i++) {
				printf("\033[A\033[K");
			}
		}	
	} while (option != 6 && option != 7);

	// OPTION TO CONTINUE OR RETURN TO MAIN
	optionCont = 'A';
	do {
		printf("\n\nContinue modifying staff information? (Y/N): ");
		(void)scanf("%c", &optionCont);
		rewind(stdin);
		optionCont = toupper(optionCont);
		if (optionCont != 'Y' && optionCont != 'N')
			printf("\nIncorrect option entered..\n");
	} while (optionCont != 'Y' && optionCont != 'N');
	if (optionCont == 'Y') {
		printf("\033[H\033[J");
		adminModify();
	}
	if (optionCont == 'N') {
		printf("\033[H\033[J");
		adminMenu();
	}
}

void adminRemove() {
	FILE* fptr, * fptr2;
	fptr = fopen("staff.bin", "rb");
	fptr2 = fopen("staff.bin", "ab");
	struct Staff temp[100] = {"ST0001", "Nigga", "1234", "1 Niggas", "Nigga", "60123456789"};
	char optionCont = 'A', option = 'A', input;
	int invalidLines = -1, i = 0, removeLocation = 0;
	printf("\033[H\033[J");
	printf("=========================================================================================================================\n");
	printf("                                             REMOVE STAFF INFORMATION MODULE                                             \n");
	printf("=========================================================================================================================\n");
	int availID = 0;
	invalidLines = -1;
	do {
		invalidLines++;
		availID = 0;
		i = 0; 		
		printf("View Staff Information? (Press Tab) | Return to Main Menu? (Press Esc)	\n");
		input = getch();
		rewind(stdin);
		printf("\033[A\033[K");
		if (input == 9) {
			tabDisplay();
		}
		else if (input == 27) {
			adminMenu();
		}
		validateID(&staff);
		rewind(fptr);
		while (fread(&temp[i], sizeof(struct Staff), 1, fptr) == 1) {
			if (strcmp(staff.id, temp[i].id) == 0) {
				availID++;
				strcpy(staff.id, temp[i].id);
				strcpy(staff.name, temp[i].name);
				strcpy(staff.password, temp[i].password);
				staff.recov_ques = temp[i].recov_ques;
				strcpy(staff.recov_ans, temp[i].recov_ans);
				strcpy(staff.position, temp[i].position);
				strcpy(staff.contact_no, temp[i].contact_no);
				removeLocation = i;
			}
			i++;
		}
		if (availID == 0) {
			printf("Staff not found.\n");
		}
	} while (availID == 0);
	for (int j = 0; j < (invalidLines * 2) + 1; j++) {
		printf("\033[A\033[K");
	}
	printf("STAFF INFORMATION\n");
	printf("----------------------------------------------\n");
	printf("%-30s : %s\n", "Staff ID", staff.id);
	printf("%-30s : %s\n", "Staff Name", staff.name);
	printf("%-30s : %s\n", "Staff Password", staff.password);
	printf("%-30s : %d\n", "Staff Recovery Question", staff.recov_ques);
	printf("%-30s : %s\n", "Staff Recovery Answer", staff.recov_ans);
	printf("%-30s : %s\n", "Staff Position", staff.position);
	printf("%-30s : %s\n", "Staff Contact Number", staff.contact_no);
	printf("----------------------------------------------\n");
	fclose(fptr);

	do {
		printf("Remove all existing data of staff %s? (Y/N): ", staff.id);
		(void)scanf("%c", &option);
		rewind(stdin);
		option = toupper(option);
		if (option != 'Y' && option != 'N')
			printf("\nIncorrect option entered..\n");
	} while (option != 'Y' && option != 'N');

	if (option == 'Y') {
		(void)fopen("staff.bin", "wb");
		fclose(fopen("staff.bin", "wb"));
		for (int k = 0; k < i; k++) {
			if (k != removeLocation) {
				fwrite(&temp[k], sizeof(struct Staff), 1, fptr2);
			}
		}
		fclose(fptr2);
		printf("\nStaff %s removed.", staff.id);
	}
	if (option == 'N') {
		printf("\nStaff removal cancelled.");
	}

	// OPTION TO CONTINUE OR RETURN TO MAIN
	optionCont = 'A';
	do {
		printf("\n\nContinue staff removal? (Y/N): ");
		(void)scanf("%c", &optionCont);
		rewind(stdin);
		optionCont = toupper(optionCont);
		if (optionCont != 'Y' && optionCont != 'N')
			printf("\nIncorrect option entered..\n");
	} while (optionCont != 'Y' && optionCont != 'N');
	if (optionCont == 'Y') {
		printf("\033[H\033[J");
		adminRemove();
	}
	if (optionCont == 'N') {
		printf("\033[H\033[J");
		adminMenu();
	}
}

void adminSearch() {
	FILE* fptr;
	fptr = fopen("staff.bin", "rb");
	struct Staff temp[100];
	struct Staff staff;
	char optionCont = 'A';
	int i = 0, j = 0, option = 0;
	int invalidLines = -1, optionInt = 0;
	printf("\033[H\033[J");
	printf("=========================================================================================================================\n");
	printf("                                             SEARCH STAFF INFORMATION MODULE                                             \n");
	printf("=========================================================================================================================\n");
	printf("                                         How would you like to search your data?                                         \n");
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	printf("                           (1) Staff ID                                    (2) Staff Name                                \n");
	printf("                           (3) Staff Position                              (4) Contact Number                            \n");
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	printf("Option: ");
	(void)scanf("%d", &option);
	rewind(stdin);
	i = 0;
	j = 0;
	while (!feof(fptr)) {
		fread( &temp[i], sizeof(struct Staff), 1, fptr);
		i++;
	}
	switch (option) {
	case 1:
		validateID(&staff);
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf(" %-12s %-21s %-12s %-15s %-21s %-21s %-14s\n", "STAFF_ID", "STAFF_NAME", "PASSWORD", "RECOVERY_QUES", "RECOVERY_ANS", "POSITION", "CONTACT_NO");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		for (int s = 0; s < i; s++) {
			if (strcmp(staff.id, temp[s].id) == 0) {
				printf(" %-12s %-21s %-12s %-15d %-21s %-21s %-13s\n", temp[s].id, temp[s].name, temp[s].password, temp[s].recov_ques, temp[s].recov_ans, temp[s].position, temp[s].contact_no);
				j++;
			}
		}
		break;
	case 2:
		validateName(&staff);
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf(" %-12s %-21s %-12s %-15s %-21s %-21s %-14s\n", "STAFF_ID", "STAFF_NAME", "PASSWORD", "RECOVERY_QUES", "RECOVERY_ANS", "POSITION", "CONTACT_NO");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		for (int s = 0; s < i; s++) {
			if (strcmp(staff.name, temp[s].name) == 0) {
				printf(" %-12s %-21s %-12s %-15d %-21s %-21s %-13s\n", temp[s].id, temp[s].name, temp[s].password, temp[s].recov_ques, temp[s].recov_ans, temp[s].position, temp[s].contact_no);
				j++;
			}
		}
		break;
	case 3:
		printf("\nSTAFF POSITION TABLE\n");
		printf("1) Administrator            7) Security Personnel\n");
		printf("2) Ticketing Agent          8) Janitor\n");
		printf("3) Train Scheduler          9) Sales and Marketing Representative\n");
		printf("4) Ticket Inspector        10) Finance and Accounting Personnel\n");
		printf("5) Train Operator          11) Customer Service Representative\n");
		printf("6) Technical Support\n");
		invalidLines = -1;
		optionInt = 0;
		do {
			invalidLines++;
			printf("Select Staff Position: ");
			(void)scanf("%d", &optionInt);
			rewind(stdin);
			if (optionInt < 1 || optionInt > 11) {
				printf("Option is limited from 1 to 11.. Please try again\n");
			}
		} while (optionInt < 1 || optionInt > 11);
		switch (optionInt) {
		case 1:
			strcpy(staff.position, "Administrator");
			break;
		case 2:
			strcpy(staff.position, "Ticketing Agent");
			break;
		case 3:
			strcpy(staff.position, "Train Scheduler");
			break;
		case 4:
			strcpy(staff.position, "Ticket Inspector");
			break;
		case 5:
			strcpy(staff.position, "Train Operator");
			break;
		case 6:
			strcpy(staff.position, "Technical Support");
			break;
		case 7:
			strcpy(staff.position, "Security Personnel");
			break;
		case 8:
			strcpy(staff.position, "Janitor");
			break;
		case 9:
			strcpy(staff.position, "SnM Representative");
			break;
		case 10:
			strcpy(staff.position, "FnA Personnel");
			break;
		case 11:
			strcpy(staff.position, "CS Representative");
			break;
		}
		for (int i = 0; i < (invalidLines * 2) + 9; i++) {
			printf("\033[A\033[K");
		}
		printf("%-30s : %s\n", "Staff Position", staff.position);
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf(" %-12s %-21s %-12s %-15s %-21s %-21s %-14s\n", "STAFF_ID", "STAFF_NAME", "PASSWORD", "RECOVERY_QUES", "RECOVERY_ANS", "POSITION", "CONTACT_NO");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		for (int s = 0; s < i; s++) {
			if (strcmp(staff.position, temp[s].position) == 0) {
				printf(" %-12s %-21s %-12s %-15d %-21s %-21s %-13s\n", temp[s].id, temp[s].name, temp[s].password, temp[s].recov_ques, temp[s].recov_ans, temp[s].position, temp[s].contact_no);
				j++;
			}
		}
		break;
	case 4:
		validateContact(&staff);
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf(" %-12s %-21s %-12s %-15s %-21s %-21s %-14s\n", "STAFF_ID", "STAFF_NAME", "PASSWORD", "RECOVERY_QUES", "RECOVERY_ANS", "POSITION", "CONTACT_NO");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		for (int s = 0; s < i; s++) {
			if (strcmp(staff.contact_no, temp[s].contact_no) == 0) {
				printf(" %-12s %-21s %-12s %-15d %-21s %-21s %-13s\n", temp[s].id, temp[s].name, temp[s].password, temp[s].recov_ques, temp[s].recov_ans, temp[s].position, temp[s].contact_no);
				j++;
			}
		}
		break;
	default:
		adminSearch();
		break;
	}

	fclose(fptr);
	if (j != 0) {
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf("%119s%d\n\n", "Total Number of Staff Displayed: ", j);
	}
	else {
		printf("No relevant staff found.\n\n");
	}
	
	//OPTION TO REPEAT 
	optionCont = 'A';
	do {
		printf("\n\nContinue searching staff data? (Y/N): ");
		(void)scanf("%c", &optionCont);
		rewind(stdin);
		optionCont = toupper(optionCont);
		if (optionCont != 'Y' && optionCont != 'N')
			printf("\nIncorrect option entered..\n");
	} while (optionCont != 'Y' && optionCont != 'N');

	if (optionCont == 'Y') {
		printf("\033[H\033[J");
		adminSearch();
	}	
	if (optionCont == 'N') {
		printf("\033[H\033[J");
		adminMenu();
	}
}

void adminSort() {//SORTING ALGORITHM LETS FUCKING GO
	FILE* fptr;
	fptr = fopen("staff.bin", "ab+");
	struct Staff sort[100];
	struct Staff temp = { "ST0001", "Nigga", "1234", "1 Niggas", "Nigga", "60123456789" };
	char optionCont = 'A';
	int i = 0, j = 0, option = 0;
	i = 0;
	printf("\033[H\033[J");
	printf("=========================================================================================================================\n");
	printf("                                              SORT STAFF INFORMATION MODULE                                              \n");
	printf("=========================================================================================================================\n");
	printf("                                          How would you like to sort your data?                                          \n");
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	printf("                     (1) Staff ID                  (2) Staff Name                  (3) Staff Position                    \n");
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	printf("Option: ");
	(void)scanf("%d", &option);
	rewind(stdin);
	while (fread(&sort[i], sizeof(struct Staff), 1, fptr) == 1) {
		i++;
	}
	switch (option)
	{
	case 1:
		option = 0;
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                    Staff ID Sorting                                                     \n");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf("                           (1) Ascending Order                            (2) Descending Order                           \n");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf("Option: ");
		(void)scanf("%d", &option);
		rewind(stdin);
		switch (option)
		{
		case 1:
			for (int n = 0; n < i - 1; n++) {
				j = 0;
				for (int k = 0; k < i - 1; k++) {
					if (strcmp(sort[j].id, sort[j + 1].id) > 0) {
						sortSort(i, j, temp, sort);
					}
					j++;
				}
			}
			break;
		case 2:
			for (int n = 0; n < i - 1; n++) {
				j = 0;
				for (int k = 0; k < i - 1; k++) {
					if (strcmp(sort[j].id, sort[j + 1].id) < 0) {
						sortSort(i, j, temp, sort);
					}
					j++;
				}
			}
			break;
		default:
			printf("Incorrect option entered..\n\n");
			adminSort();
			break;
		}
		break;

	case 2:
		option = 0;
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                   Staff Name Sorting                                                    \n");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf("                   (1) Alphabetical Ascending Order                   (2) Alphabetical Descending Order                  \n");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf("Option: ");
		(void)scanf("%d", &option);
		rewind(stdin);
		switch (option)
		{
		case 1:
			for (int n = 0; n < i - 1; n++) {
				j = 0;
				for (int k = 0; k < i - 1; k++) {
					if (strcmp(sort[j].name, sort[j + 1].name) > 0) {
						sortSort(i, j, temp, sort);
					}
					j++;
				}
			}
			break;
		case 2:
			for (int n = 0; n < i - 1; n++) {
				j = 0;
				for (int k = 0; k < i - 1; k++) {
					if (strcmp(sort[j].name, sort[j + 1].name) < 0) {
						sortSort(i, j, temp, sort);
					}
					j++;
				}
			}
			break;
		default:
			adminSort();
			break;
		}
		break;

	case 3:
		option = 0;
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                 Staff Position Sorting                                                  \n");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf("                   (1) Alphabetical Ascending Order                   (2) Alphabetical Descending Order                  \n");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf("Option: ");
		(void)scanf("%d", &option);
		rewind(stdin);
		switch (option)
		{
		case 1:
			for (int n = 0; n < i - 1; n++) {
				j = 0;
				for (int k = 0; k < i - 1; k++) {
					if (strcmp(sort[j].position, sort[j + 1].position) > 0) {
						sortSort(i, j, temp, sort);
					}
					j++;
				}
			}
			break;
		case 2:
			for (int n = 0; n < i - 1; n++) {
				j = 0;
				for (int k = 0; k < i - 1; k++) {
					if (strcmp(sort[j].position, sort[j + 1].position) < 0) {
						sortSort(i, j, temp, sort);
					}
					j++;
				}
			}
			break;
		default:
			printf("Incorrect option entered..\n\n");
			adminSort();
			break;
		}
		break;

	default:
		adminSort();
		break;
	}
	(void)fopen("staff.bin", "wb");
	fclose(fopen("staff.bin", "wb"));

	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	printf(" %-12s %-21s %-12s %-15s %-21s %-21s %-14s\n", "STAFF_ID", "STAFF_NAME", "PASSWORD", "RECOVERY_QUES", "RECOVERY_ANS", "POSITION", "CONTACT_NO");
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	for (int k = 0; k < i; k++) {
		printf(" %-12s %-21s %-12s %-15d %-21s %-21s %-13s\n", sort[k].id, sort[k].name, sort[k].password, sort[k].recov_ques, sort[k].recov_ans, sort[k].position, sort[k].contact_no);
		fwrite(&sort[k], sizeof(struct Staff), 1, fptr);
	}
	fclose(fptr);
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	printf("%119s%d\n\n", "Total Number of Staff Displayed: ", i);

	//OPTION TO REPEAT 
	optionCont = 'A';
	do {
		printf("\n\nContinue sorting staff data? (Y/N): ");
		(void)scanf("%c", &optionCont);
		rewind(stdin);
		optionCont = toupper(optionCont);
		if (optionCont != 'Y' && optionCont != 'N')
			printf("\nIncorrect option entered..\n");
	} while (optionCont != 'Y' && optionCont != 'N');

	if (optionCont == 'Y') {
		printf("\033[H\033[J");		
		adminSort();
	}
	if (optionCont == 'N') {
		printf("\033[H\033[J");
		adminMenu();
	}	
}

void adminDisplay() {
	char optionCont = 'A';
	int i = 0;
	FILE* fRead;
	fRead = fopen("staff.bin", "rb");
	printf("\033[H\033[J");
	printf("=========================================================================================================================\n");
	printf("                                             DISPLAY STAFF INFORMATION MODULE                                            \n");
	printf("=========================================================================================================================\n\n");
	printf(" %-12s %-21s %-12s %-15s %-21s %-21s %-14s\n", "STAFF_ID", "STAFF_NAME", "PASSWORD", "RECOVERY_QUES", "RECOVERY_ANS", "POSITION", "CONTACT_NO");
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	while (fread(&staff, sizeof(struct Staff), 1, fRead) == 1) {
		
		printf(" %-12s %-21s %-12s %-15d %-21s %-21s %-13s\n", staff.id, staff.name, staff.password, staff.recov_ques, staff.recov_ans, staff.position, staff.contact_no);
		i++;
	}
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	printf("%119s%d\n\n", "Total Number of Staff Displayed: ", i);

	//OPTION TO REPEAT 
	optionCont = 'A';
	do {
		printf("\n\nToo much information? Try using the search function. (Y/N): ");
		(void)scanf("%c", &optionCont);
		rewind(stdin);
		optionCont = toupper(optionCont);
		if (optionCont != 'Y' && optionCont != 'N')
			printf("\nIncorrect option entered..\n");
	} while (optionCont != 'Y' && optionCont != 'N');
	if (optionCont == 'Y') {
		printf("\033[H\033[J");		
		adminSearch();
	}
	if (optionCont == 'N') {
		printf("\033[H\033[J");		
		adminMenu();
	}
}

void staffDisplay() {
	char optionCont = 'A';
	int i = 0;
	FILE* fRead;
	fRead = fopen("staff.bin", "rb");
	printf("\033[H\033[J");
	printf("=========================================================================================================================\n");
	printf("                                             DISPLAY STAFF INFORMATION MODULE                                            \n");
	printf("=========================================================================================================================\n");
	while (fread(&staff, sizeof(struct Staff), 1, fRead) == 1) {
		if (strcmp(userID, staff.id) == 0) {
			printf(" _______________________________________________________________________________________________________________________\n");
			printf("|  Staff Information                                                                                                    |\n");
			printf(" ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			printf("|  %-30s : %-82s  |\n", "Staff ID", staff.id);
			printf("|  %-30s : %-82s  |\n", "Staff Name", staff.name);
			printf("|  %-30s : %-82s  |\n", "Staff Password", staff.password);
			printf("|  %-30s : %-1d) %-79s  |\n", "Staff Recovery Question", staff.recov_ques, recovQues[staff.recov_ques - 1]);
			printf("|  %-30s : %-82s  |\n", "Staff Recovery Answer", staff.recov_ans);
			printf("|  %-30s : %-82s  |\n", "Staff Position", staff.position);
			printf("|  %-30s : %-82s  |\n", "Staff Contact Number", staff.contact_no);
			printf(" -----------------------------------------------------------------------------------------------------------------------\n\n");
		}
	}

	//OPTION TO REPEAT 
	optionCont = 'A';
	do {
		printf("\nReturn to main module? (Y/N): ");
		(void)scanf("%c", &optionCont);
		rewind(stdin);
		optionCont = toupper(optionCont);
		if (optionCont != 'Y' && optionCont != 'N')
			printf("Incorrect option entered..\n");
	} while (optionCont != 'Y' && optionCont != 'N');
	if (optionCont == 'Y') {
		printf("\033[H\033[J");
		staffMenu();
	}
	if (optionCont == 'N') {
		printf("\033[H\033[J");
		exit(0);
	}
}

void staffModify() {
	FILE* fptr, * fptr2;
	fptr = fopen("staff.bin", "rb");
	fptr2 = fopen("staff.bin", "ab");
	struct Staff temp[100] = { "ST0001", "Nigga", "1234", "1 Niggas", "Nigga", "60123456789" };
	struct Staff update;
	char optionCont = 'A', input;
	int option = 0, optionPosition = 0, invalidLines = -1, i = 0, removeLocation = 0;
	printf("\033[H\033[J");
	printf("=========================================================================================================================\n");
	printf("                                             MODIFY STAFF INFORMATION MODULE                                             \n");
	printf("=========================================================================================================================\n");
	int availID = 0;
	invalidLines = -1;
	do {
		invalidLines++;
		availID = 0;
		i = 0;
		while (fread(&temp[i], sizeof(struct Staff), 1, fptr) == 1) {
			if (strcmp(userID, temp[i].id) == 0) {
				availID++;
				strcpy(staff.id, temp[i].id);
				strcpy(staff.name, temp[i].name);
				strcpy(staff.password, temp[i].password);
				staff.recov_ques = temp[i].recov_ques;
				strcpy(staff.recov_ans, temp[i].recov_ans);
				strcpy(staff.position, temp[i].position);
				strcpy(staff.contact_no, temp[i].contact_no);
				removeLocation = i;
			}
			i++;
		}
		if (availID == 0) {
			printf("Staff not found.\n");
		}
	} while (availID == 0);
	strcpy(update.id, staff.id);
	strcpy(update.name, staff.name);
	strcpy(update.password, staff.password);
	update.recov_ques = staff.recov_ques;
	strcpy(update.recov_ans, staff.recov_ans);
	strcpy(update.position, staff.position);
	strcpy(update.contact_no, staff.contact_no);
	do {
		option = 0;
		printf(" __________________________________________________________    __________________________________________________________\n");
		printf("|  UNREVISED Staff Information                             |  |  UPDATED Staff Information                               |\n");
		printf(" ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯    ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
		printf("|  %-30s : %-21s  |  |  %-30s : %-21s  |\n", "Staff ID", staff.id, "Staff ID", update.id);
		printf("|  %-30s : %-21s  |  |  %-30s : ", "Staff Name", staff.name, "Staff Name");
		printf("%-21s", update.name);
		printf("  |\n");
		printf("|  %-30s : %-21s  |  |  %-30s : ", "Staff Password", staff.password, "Staff Password");
		if (strcmp(staff.password, update.password) != 0)
			printf("\033[1;32m%-21s\033[1;0m", update.password);
		else
			printf("%-21s", update.password);
		printf("  |\n");
		printf("|  %-30s : %-21d  |  |  %-30s : ", "Staff Recovery Question", staff.recov_ques, "Staff Recovery Question");
		if (staff.recov_ques != update.recov_ques)
			printf("\033[1;32m%-21d\033[1;0m", update.recov_ques);
		else
			printf("%-21d", update.recov_ques);
		printf("  |\n");
		printf("|  %-30s : %-21s  |  |  %-30s : ", "Staff Recovery Answer", staff.recov_ans, "Staff Recovery Answer");
		if (strcmp(staff.recov_ans, update.recov_ans) != 0)
			printf("\033[1;32m%-21s\033[1;0m", update.recov_ans);
		else
			printf("%-21s", update.recov_ans);
		printf("  |\n");
		printf("|  %-30s : %-21s  |  |  %-30s : ", "Staff Position", staff.position, "Staff Position");
		printf("%-21s", update.position);
		printf("  |\n");
		printf("|  %-30s : %-21s  |  |  %-30s : ", "Staff Contact Number", staff.contact_no, "Staff Contact Number");
		if (strcmp(staff.contact_no, update.contact_no) != 0)
			printf("\033[1;32m%-21s\033[1;0m", update.contact_no);
		else
			printf("%-21s", update.contact_no);
		printf("  |\n");
		printf(" ----------------------------------------------------------    ----------------------------------------------------------\n\n");
		fclose(fptr);

		printf("=========================================================================================================================\n");
		printf("                                                 Modification Selection                                                  \n");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf("               (1) Staff Contact Number      (2) Staff Password            (3) Staff Recovery Question & Answer          \n");
		printf("               (4) Apply Changes             (5) Discard Changes                                                         \n");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		invalidLines = -1;
		do {
			invalidLines++;
			printf("Option: ");
			(void)scanf("%d", &option);
			rewind(stdin);
			if (option < 1 || option > 7) {
				printf("Option is limited from 1 to 7.. Please try again\n");
			}
		} while (option < 1 || option > 7);
		for (int i = 0; i < (invalidLines * 2) + 1; i++) {
			printf("\033[A\033[K");
		}
		printf("Option: %d\n", option);
		switch (option) {
		case 1:
			validateContact(&update);
			break;
		case 2:
			validatePassword(&update);
			break;
		case 3:
			//Password Recovery
			printf("\nPASSWORD RECOVERY QUESTIONS\n");
			for (int z = 0; z < 6; z++) {
				printf("%d) %s\n", z + 1, recovQues[z]);
			}
			invalidLines = -1;
			update.recov_ques = 9;
			do {
				invalidLines++;
				printf("Select Password Recovery Question: ");
				(void)scanf("%d", &update.recov_ques);
				rewind(stdin);
				if (update.recov_ques < 1 || update.recov_ques > 6) {
					printf("Option is limited from 1 to 6.. Please try again\n");
				}
			} while (update.recov_ques < 1 || update.recov_ques > 6);
			for (int i = 0; i < (invalidLines * 2) + 9; i++) {
				printf("\033[A\033[K");
			}
			printf("%-30s : %d) %s\n", "Password Recovery Question", update.recov_ques, recovQues[update.recov_ques - 1]);
			validateRecovery(&update);
			printf("\033[A\033[K");

			break;
		case 4:
			//throw inside array
			strcpy(temp[removeLocation].id, update.id);
			strcpy(temp[removeLocation].name, update.name);
			strcpy(temp[removeLocation].password, update.password);
			temp[removeLocation].recov_ques = update.recov_ques;
			strcpy(temp[removeLocation].recov_ans, update.recov_ans);
			strcpy(temp[removeLocation].position, update.position);
			strcpy(temp[removeLocation].contact_no, update.contact_no);
			//throw into file
			(void)fopen("staff.bin", "wb");
			fclose(fopen("staff.bin", "wb"));
			for (int k = 0; k < i; k++) {
				fwrite(&temp[k], sizeof(struct Staff), 1, fptr2);
			}
			fclose(fptr2);
			printf("\nStaff %s updated.", staff.id);
			break;
		default:
			printf("\nModifications discarded.");
			break;
		}
		if (option != 4 && option != 5) {
			for (int i = 0; i < 20; i++) {
				printf("\033[A\033[K");
			}
		}
	} while (option != 4 && option != 5);

	// OPTION TO CONTINUE OR RETURN TO MAIN
	optionCont = 'A';
	do {
		printf("\n\nReturn to Main Menu? (Y/N): ");
		(void)scanf("%c", &optionCont);
		rewind(stdin);
		optionCont = toupper(optionCont);
		if (optionCont != 'Y' && optionCont != 'N')
			printf("\nIncorrect option entered..\n");
	} while (optionCont != 'Y' && optionCont != 'N');
	if (optionCont == 'Y') {
		printf("\033[H\033[J");
		staffMenu();
	}
	if (optionCont == 'N') {
		printf("\033[H\033[J");
		exit(0);
	}
}

void tabDisplay() {
	char input;
	int i = 0;
	FILE* fRead;
	fRead = fopen("staff.bin", "rb");
	printf("=========================================================================================================================\n");
	printf("                                        Displaying Staff Information (Tab to leave)                                      \n");
	printf("=========================================================================================================================\n\n");
	printf(" %-12s %-21s %-12s %-15s %-21s %-21s %-14s\n", "STAFF_ID", "STAFF_NAME", "PASSWORD", "RECOVERY_QUES", "RECOVERY_ANS", "POSITION", "CONTACT_NO");
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	while (fread(&staff, sizeof(struct Staff), 1, fRead) == 1) {

		printf(" %-12s %-21s %-12s %-15d %-21s %-21s %-13s\n", staff.id, staff.name, staff.password, staff.recov_ques, staff.recov_ans, staff.position, staff.contact_no);
		i++;
	}
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	printf("%119s%d\n\n", "Total Number of Staff Displayed: ", i);
	fclose(fRead);
	for (int j = 0;; j++){
		input = getch();
		if (input == 9) {
			for (int m = 0; m < 9; m++)
				printf("\033[A\033[K");
			for (int m = 0; m < i; m++)
				printf("\033[A\033[K");
			break;
		}
	}
}

// VALIDATION FUNCTIONS
void validateID(struct Staff* staff) {
	int validateCount = 0, validateStatus = 0, invalidLines = -1;
	do {
		invalidLines++;
		validateCount = 0;
		printf("Enter staff ID: ");
		(void)scanf("%[^\n]", &staff->id);
		rewind(stdin);
		for (int i = 0; i < 4; i++) {
			if (staff->id[0] != 'S' || staff->id[1] != 'T' || !isdigit(staff->id[i + 2])) {
				validateCount++;
			}
		}
		if (validateCount != 0) {
			printf("Incorrect Staff ID input.. Please try again\n");
			printf("Example Format: ST0001\n\n");
			validateStatus = 0;
		}
		else {
			validateStatus = 1;
		}
	} while (validateStatus != 1);
	for (int i = 0; i < ( invalidLines * 4 ) + 1; i++) {
		printf("\033[A\033[K");
	}
	printf("Staff ID: %s\n", staff->id);
}
void validateName(struct Staff *staff) {
	int validateCount = 0, validateStatus = 0, invalidLines = -1;
	do {
		invalidLines++;
		validateCount = 0;
		printf("Staff Name: ");
		(void)scanf("%[^\n]", &staff->name);
		rewind(stdin);
		for (int i = 0; i < strlen(staff->name); i++) {
			if (!isalpha(staff->name[i]) && staff->name[i] != ' ') {
				validateCount++;
			}
		}
		if (validateCount != 0) {
			printf("Incorrect name input.. Please try again\n");
			printf("Example Format: (Only characters and space allowed)\n\n");
			validateStatus = 0;
		}
		else {
			validateStatus = 1;
		}
	} while (validateStatus != 1);
	for (int i = 0; i < (invalidLines * 4) + 1; i++) {
		printf("\033[A\033[K");
	}
	printf("%-30s : %s\n", "Staff Name", staff->name);
}
void validatePassword(struct Staff *staff) {
	int validateCount = 0, validateStatus = 0, invalidLines = -1;
	do {
		invalidLines++;
		validateCount = 0;
		printf("Staff Password: ");
		(void)scanf("%[^\n]", &staff->password);
		rewind(stdin);
		for (int i = 0; i < strlen(staff->password); i++) {
			if (!isdigit(staff->password[i])) {
				validateCount++;
			}
		}
		if (validateCount != 0 || strlen(staff->password) != 4) {
			printf("Incorrect password input.. Please try again\n");
			printf("Example Format: 0000\n\n");
			validateStatus = 0;
		}
		else {
			validateStatus = 1;
		}
	} while (validateStatus != 1);
	for (int i = 0; i < (invalidLines * 4) + 1; i++) {
		printf("\033[A\033[K");
	}
	printf("%-30s : %s\n", "Staff Password", staff->password);
}
void validateRecovery(struct Staff *staff) {
	int validateCount = 0, validateStatus = 0, invalidLines = -1;
	do {
		invalidLines++;
		validateCount = 0;
		printf("Enter Password Recovery Answer: ");
		(void)scanf("%[^\n]", &staff->recov_ans);
		rewind(stdin);
		for (int i = 0; i < strlen(staff->recov_ans); i++) {
			if (!isalpha(staff->recov_ans[i]) && staff->recov_ans[i] != ' ') {
				validateCount++;
			}
		}
		if (validateCount != 0) {
			printf("Limit recovery answer to characters only.. Please try again\n\n");
			validateStatus = 0;
		}
		else {
			validateStatus = 1;
		}
	} while (validateStatus != 1);
	for (int i = 0; i < (invalidLines * 3) + 1; i++) {
		printf("\033[A\033[K");
	}
	printf("%-30s : %s\n", "Password Recovery Answer", staff->recov_ans);
}
void validateContact(struct Staff *staff) {
	int validateCount = 0, validateStatus = 0, invalidLines = -1;
	do {
		invalidLines++;
		validateCount = 0;
		printf("Staff Contact Number: ");
		(void)scanf("%[^\n]", &staff->contact_no);
		rewind(stdin);
		for (int i = 0; i < strlen(staff->contact_no); i++) {
			if (!isdigit(staff->contact_no[i])) {
				validateCount++;
			}
		}
		if (validateCount != 0 || strlen(staff->contact_no) != 11) {
			printf("Incorrect contact number input.. Please try again\n");
			printf("Example Format: 60123456789\n\n");
			validateStatus = 0;
		}
		else {
			validateStatus = 1;
		}
	} while (validateStatus != 1);
	for (int i = 0; i < (invalidLines * 4) + 1; i++) {
		printf("\033[A\033[K");
	}
	printf("%-30s : %s\n", "Contact Number", staff->contact_no);
}

//SORTING ALGORITHM
void sortSort(int i, int j, struct Staff temp, struct Staff sort[100]) {
	strcpy(temp.id, sort[j].id);
	strcpy(temp.name, sort[j].name);
	strcpy(temp.password, sort[j].password);
	temp.recov_ques = sort[j].recov_ques;
	strcpy(temp.recov_ans, sort[j].recov_ans);
	strcpy(temp.position, sort[j].position);
	strcpy(temp.contact_no, sort[j].contact_no);

	strcpy(sort[j].id, sort[j + 1].id);
	strcpy(sort[j].name, sort[j + 1].name);
	strcpy(sort[j].password, sort[j + 1].password);
	sort[j].recov_ques = sort[j + 1].recov_ques;
	strcpy(sort[j].recov_ans, sort[j + 1].recov_ans);
	strcpy(sort[j].position, sort[j + 1].position);
	strcpy(sort[j].contact_no, sort[j + 1].contact_no);

	strcpy(sort[j + 1].id, temp.id);
	strcpy(sort[j + 1].name, temp.name);
	strcpy(sort[j + 1].password, temp.password);
	sort[j + 1].recov_ques = temp.recov_ques;
	strcpy(sort[j + 1].recov_ans, temp.recov_ans);
	strcpy(sort[j + 1].position, temp.position);
	strcpy(sort[j + 1].contact_no, temp.contact_no);
}
