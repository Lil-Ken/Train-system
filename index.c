#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#pragma warning(disable:4996)

// Define constants
#define BOOKING_FRONT_ID 'B'
#define MEMBER_FRONT_ID 'M'
#define STAFF_FRONT_ID 'S'
#define TRAIN_FRONT_ID 'T'
#define MAX_BOOKING_DAYS 30
#define ROWS 100
#define COLS 4
#define MAX_BOOKING 10000


// Structure Declaration
struct Date {
	int day, month, year;
};

struct Time {
	int hour, min;
};

typedef struct {
	char seatNumber[4]; // 01A, 02A, 03A, ...
	char coach; // Q, R, X, Y, Z
}Seat;

typedef struct {
	int trainID;
	char departureStation[50], arrivalStation[50];
	struct Date departureDate;
	struct Date arrivalDate;
	struct Time departureTime;
	struct Time arrivalTime;
	int availableSeats; // number of available seats
	float ticketPrice;
	Seat seats[10]; // booked seat
} TrainSchedule;

typedef struct {
	char paymentInfo[20], ticketStatus[10];
	struct Date bookingDate;
	int quantity, bookingID;
	double amount;
	TrainSchedule trains;
}Booking;

typedef struct {
	Booking book[MAX_BOOKING];
	int backMemberID, password;
	char frontMemberID, name[30], gender, IC[17], contactNumber[12], passRecovery[30];
}Member;

typedef struct {
	char  name[51], frontID, position[51], fatherName[51], pass[7];
	int  backID;

}staffinfo;




// Function Declaration
// Main
int menu();
void staffMain();
void memberMain();
void schedulingMain();
void bookingMain();

// Staff
int staffMenu();
int addStaff();
int searchStaff();
int modifyStaff();
int displayStaff();
int passwordRecovery(int id);
int deleteStaff();
int staffid();
int staffPayslip();

// Member
int memberMenu();
void addMember();
void searchMember();
void modifyMember();
void displayMember();
void deleteMember();
void passwordRecoveryMember();
void memberID(int* id);
bool loginStaffMem();
int validateName(const char* name);
int validatePassword(int password);
int validateGender(char gender);
int validateIC(const char* IC);
int validateContactNumber(const char* contactNumber);
int validatePassRec(const char* passRec);
void memberLogo();

// Schldule
int scheduleMode(int selection);
void scheduleMenu(int* mode);
void searchSchedule();
void modifySchedule();
int addSchedule(int trainIDCounter);
void displaySchedule();
void deleteSchedule();
void scheduleReport(int* sreport);
void dateScheduleReport(int day, int month, int year);
void overalScheduleReport(int day, int month, int year);
void stationScheduleReport(char station[50]);
void scheduleLogo();
void staffVerify();
void memberVerify(int* mode);
void memberLogin(int* mode);

// Booking
void bookingMenu(int* loginMode);
void bookingMenuStaff(int* mode);
void bookingMenuMember(int* mode);
void addBooking();
void searchBooking(char mode[]);
void modifyBooking();
void displayBooking(int i, char mode[]);
void cancelBooking();
void deleteBooking();
void summaryReport();
bool loginMember(int* ID);
bool loginStaff();
bool schedulingData(int trainID, char purpose[], int bookingNum, double* price);
void paymentMethod(int bookingNum);
int bookingID_Num(int* id);
void displaySeat(int trainID);
bool seat(int bookingNum, int count, int mode);
void modifySeat(int mode, int bookingNum, int count, bool* valid);
void bookingLogo();


// Modules
// Main
void main() {

	int mode;
	while (1) {
		mode = menu();
		switch (mode) {
		case 1:
			staffMain();
			break;
		case 2:
			memberMain();
			break;
		case 3:
			schedulingMain();
			break;
		case 4:
			bookingMain();
			break;
		default:
			exit(-1);
			break;
		}
	}
}

int menu() {
	int mode;


	do {
		system("cls");

		system("color 06");

		printf("                                ___________                .__            _________                  __                    \n");
		printf("                                \\__    ___/_______ _____   |__|  ____    /   _____/ ___.__.  _______/  |_   ____    _____  \n");
		printf("                                  |    |   \\_  __ \\ \\__ \\  |  | /    \\   \\_____  \\ <   |  | /  ___/\\   __\\_/ __ \\  /     \\ \n");
		printf("                                  |    |    |  | \\/ / __ \\_|  ||   |  \\  /        \\ \\___  | \\___ \\  |  |  \\  ___/ |  Y Y  \\ \n");
		printf("                                  |____|    |__|   (____  /|__||___|  / /_______  / / ____|/____  > |__|   \\___  >|__|_|  / \n");
		printf("                                                        \\/          \\/          \\/  \\/          \\/             \\/       \\/  \n");

		printf("_____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ ____\n");
		printf("\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\___\\\n");

		printf("  __         ____  ____   __   ____  ____                                                 ____        _  _  ____  _  _  ____  ____  ____      \n");
		printf(" /  \\       / ___)(_  _) / _\\ (  __)(  __)                                               (___ \\      ( \\/ )(  __)( \\/ )(  _ \\(  __)(  _ \\\n");
		printf("(_/ /   _   \\___ \\  )(  /    \\ ) _)  ) _)                                                 / __/  _   / \\/ \\ ) _) / \\/ \\ ) _ ( ) _)  )   / \n");
		printf(" (__)  (_)  (____/ (__) \\_/\\_/(__)  (__)                                                 (____) (_)  \\_)(_/(____)\\_)(_/(____/(____)(__\\_)  \n");


		printf(" ____        ____   ___  _  _  ____  ____  _  _  __     __   __ _   ___                    ___        ____   __    __   __ _   __   __ _   ___      \n");
		printf("(__  \\      / ___) / __)/ )( \\(  __)(    \\/ )( \\(  )   (  ) (  ( \\ / __)                  / _ \\      (  _ \\ /  \\  /  \\ (  / ) (  ) (  ( \\ / __)\n");
		printf(" (__ (  _   \\___ \\( (__ ) __ ( ) _)  ) D () \\/ (/ (_/\\  )(  /    /( (_ \\                 (__  (  _    ) _ ((  O )(  O ) )  (   )(  /    /( (_ \\    \n");
		printf("(____/ (_)  (____/ \\___)\\_)(_/(____)(____/\\____/\\____/ (__) \\_)__) \\___/                   (__/ (_)  (____/ \\__/  \\__/ (__\\_) (__) \\_)__) \\___/\n");


		printf("  ___        ____  _  _   __   ____ \n");
		printf(" / __)      (  __)( \\/ ) (  ) (_  _)\n");
		printf("(___ \\  _    ) _)  )  (   )(    )(  \n");
		printf("(____/ (_)  (____)(_/\\_) (__)  (__) \n");

		printf("\nEnter Mode: ");
		scanf("%d", &mode);
		rewind(stdin);


	} while (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5);
	return mode;
}


// Staff
staffinfo staff;
void staffMain() {
	int mode;
	mode = staffMenu();
	switch (mode) {
	case 1:
		addStaff();
		break;
	case 2:
		searchStaff();
		break;
	case 3:
		modifyStaff();
		break;
	case 4:
		displayStaff();
		break;
	case 5:
		deleteStaff();
		break;
	case 6:
		staffPayslip();
		break;
	default:
		break;
	}

}


int staffMenu() {
	int mode;


	do {


		system("cls");
		printf("==============================\n");
		printf("       Select Function\n");
		printf("==============================\n\n");

		printf("Add Staff --------------- 1\n");
		printf("Search Staff ------------ 2\n");
		printf("Modify Staff ------------ 3\n");
		printf("Display Staff ----------- 4\n");
		printf("Delete Staff ------------ 5\n");
		printf("Staff Payslip ----------- 6\n");
		printf("Back -------------------- 7\n\n");
		printf("Enter Number --------------- ");
		scanf("%d", &mode); rewind(stdin);
	} while (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5 && mode != 6 && mode != 7);

	return mode;

}


int addStaff() {

	int exit, passrec, valid = 0;
	staff.frontID = 'S';



	do {



		FILE* stf;
		stf = fopen("staff.bin", "ab");

		if (stf == NULL) {
			printf("disable to open file");
			system("pause");
			return;
		}
		staff.backID = staffid();

		printf("Your staff id is %c%d\n", staff.frontID, staff.backID);
		printf("Staff Name :");
		scanf("%[^\n]", staff.name);	rewind(stdin);
		printf("Staff position :");
		scanf("%s", staff.position);	rewind(stdin);



		do {
			printf("Password (6 digit number) :");
			scanf("%s", &staff.pass); rewind(stdin);

			if (strlen(staff.pass) != 6) {
				printf("Invalid input. Password must be 6 digits.\n");
				continue;
			}
			int i;

			for (i = 0; i < 6; i++) {
				if (isdigit(staff.pass[i]) == 0) {
					printf("Invalid input. Password must contain only digits.\n");
					break;
				}


			}
			if (i == 6) {
				valid = 1;

			}

		} while (valid == 0);






		do {
			printf("Please enter your father name be your password recovery : ");
			scanf("%[^\n]", &staff.fatherName);  rewind(stdin);
			printf("Confirm father name is %s ?\n", staff.fatherName);
			printf("[1] YES \n");
			printf("[2] NO \n");
			scanf("%d", &passrec); rewind(stdin);
			if (passrec != 1 && passrec != 2) {
				printf("Input not valid,please try again\n");

			}
		} while (passrec != 1);

		for (int i = 0; staff.fatherName[i] != '\0'; i++) {
			staff.fatherName[i] = toupper(staff.fatherName[i]);
		}



		fwrite(&staff, sizeof(staffinfo), 1, stf);

		fclose(stf);

		printf("\n==============================\n");
		printf("     Add staff completed\n");
		printf("==============================\n\n");
		printf("[1] Countinue add staff\n");
		printf("[2] Exit\n :");
		scanf("%d", &exit); rewind(stdin);
		while (exit != 1 && exit != 2) {
			printf("Input not valid,please try again : ");
			scanf("%d", &exit); rewind(stdin);
		}
	} while (exit == 1);


	system("pause");
	staffMain();
}


int searchStaff() {
	char frontid;
	int backid, num = 0;

	FILE* stf;
	stf = fopen("staff.bin", "rb");

	if (stf == NULL) {
		printf("Unabale to open file");
		return;
	}


	printf("Please enter staff id : "); rewind(stdin);
	scanf("%c%d", &frontid, &backid);

	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
		if (backid == staff.backID) {
			num = 1;
			printf("\n\nID             NAME             POSITION         PASSWORD \n");
			printf("-------------------------------------------------------------\n");
			printf("%c%-12d  %-15s  %-15s  %-15s\n", staff.frontID, staff.backID, staff.name, staff.position, staff.pass);
			system("pause");
			staffMain();


		}

	}

	if (num == 0) {
		printf("Invalid ID, please try again\n\n");
		system("pause");
		staffMain();
	}




}


int modifyStaff() {

	char frontid, ctn;
	int backid, selection, num = 0, valid = 0;

	FILE* stf;
	FILE* stf1;
	stf = fopen("staff.bin", "rb");
	stf1 = fopen("staffmodify.bin", "wb");
	if (stf == NULL || stf1 == NULL) {
		printf("Unabale to open file");
		return;
	}

	printf("Enter the staff ID need to modify : ");
	scanf("%c%d", &frontid, &backid); rewind(stdin);


	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
		if (staff.backID == backid) {
			num = 1;
			do {

				printf("\n\nID             NAME             POSITION         PASSWORD \n");
				printf("-------------------------------------------------------------\n");
				printf("%c%-12d  %-15s  %-15s  %-15s\n", staff.frontID, staff.backID, staff.name, staff.position, staff.pass);


				printf("\nName -------------------- 1\n");
				printf("position ---------------- 2\n");
				printf("password ---------------- 3\n");
				printf("Cancel modify ----------- 4\n");
				printf("\nSelect a field to modify: ");
				scanf(" %d", &selection); rewind(stdin);
				while (selection != 1 && selection != 2 && selection != 3 && selection != 4)
				{
					printf("Invalid, please enter again : ");
					scanf("%d", &selection); rewind(stdin);
				}
				switch (selection) {
				case 1:
					printf("Enter new name : ");
					scanf("%[^\n]", &staff.name);
					rewind(stdin);
					break;
				case 2:
					printf("Enter new position : ");
					scanf("%s", &staff.position);
					rewind(stdin);
					break;
				case 3:
					do {
						printf("Enter new Password (6 digit number) :");
						scanf("%s", &staff.pass); rewind(stdin);

						if (strlen(staff.pass) != 6) {
							printf("Invalid input. Password must be 6 digits.\n");
							continue;
						}
						int i;

						for (i = 0; i < 6; i++) {
							if (isdigit(staff.pass[i]) == 0) {
								printf("Invalid input. Password must contain only digits.\n");
								break;
							}


						}
						if (i == 6) {
							valid = 1;

						}

					} while (valid == 0);
					break;
				case 4:
					staffMain();
					break;
				default:
					break;
				}
				do {
					printf("\n\nID             NAME             POSITION         PASSWORD \n");
					printf("-------------------------------------------------------------\n");
					printf("%c%-12d  %-15s  %-15s  %-15s\n", staff.frontID, staff.backID, staff.name, staff.position, staff.pass);
					printf("Need to modify more (Y/N) : ");
					scanf("%c", &ctn); rewind(stdin);
				} while (ctn != 'Y' && ctn != 'y' && ctn != 'N' && ctn != 'n');
			} while (ctn == 'Y' || ctn == 'y');
			fwrite(&staff, sizeof(staffinfo), 1, stf1);
		}
		else fwrite(&staff, sizeof(staffinfo), 1, stf1);
	}
	fclose(stf);
	fclose(stf1);


	if (num == 1) {
		FILE* stf;
		FILE* stf1;
		stf = fopen("staff.bin", "wb");
		stf1 = fopen("staffmodify.bin", "rb");
		if (stf == NULL || stf1 == NULL) {
			printf("Unabale to open file");
			return;
		}

		while (fread(&staff, sizeof(staffinfo), 1, stf1) != 0) {
			fwrite(&staff, sizeof(staffinfo), 1, stf);
		}
		fclose(stf);
		fclose(stf1);
	}
	else {
		printf("Invalid ID, please try again\n\n");
		system("pause");
		staffMain();

	}

	system("pause");
	staffMain();

}


int displayStaff() {

	FILE* stf;
	stf = fopen("staff.bin", "rb");

	if (stf == NULL) {
		printf("Unable to open file");
		system("pause");
		return;
	}

	printf("\n\nID             NAME             POSITION         PASSWORD \n");
	printf("-------------------------------------------------------------\n");
	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
		printf("%c%-12d  %-15s  %-15s  %-15s\n", staff.frontID, staff.backID, staff.name, staff.position, staff.pass);
	}
	fclose(stf);

	system("pause");
	staffMain();
}

int passwordRecovery(int id) {

	int num1 = 0;
	char frontid, passrec[51];
	FILE* stf;
	stf = fopen("staff.bin", "rb");

	if (stf == NULL) {
		printf("Disable to open file");
		return;
	}


	printf("Please enter your father name : ");
	scanf("%[^\n]", passrec);

	for (int i = 0; passrec[i] != '\0'; i++) {
		passrec[i] = toupper(passrec[i]);
	}

	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
		if (id == staff.backID) {
			if (strcmp(passrec, staff.fatherName) == 0) {
				num1 = 1;

				printf("Your password is %s\n\n", staff.pass);

			}
		}



	}
	if (num1 == 0) {

		printf("Invalid ID, please try again\n");

	}

	fclose(stf);
	system("pause");

}

int deleteStaff() {

	int backid, num = 0;
	char frontid, ctn;

	FILE* stf;
	FILE* stf1;
	stf = fopen("staff.bin", "rb");
	stf1 = fopen("staffmotify.bin", "wb");

	if (stf == NULL && stf1 == NULL) {
		printf("Disable open file");
		exit(-1);
	}

	printf("Enter Staff ID need to delete : ");
	scanf("%c%d", &frontid, &backid); rewind(stdin);



	while (fread(&staff, sizeof(staffinfo), 1, stf) == 1)
	{
		if (backid == staff.backID) {
			num = 1;
			do {
				printf("Comfirm delete (Y/N) : ");
				scanf("%c", &ctn); rewind(stdin);
			} while (ctn != 'Y' && ctn != 'N' && ctn != 'y' && ctn != 'n');


			if (ctn == 'N') {
				return;
			}

		}
		else {
			fwrite(&staff, sizeof(staffinfo), 1, stf1);
		}
	}
	fclose(stf);
	fclose(stf1);


	if (num == 1) {

		FILE* stf;
		FILE* stf1;
		stf = fopen("staff.bin", "wb");
		stf1 = fopen("staffmotify.bin", "rb");

		if (stf == NULL && stf1 == NULL) {
			printf("Disable open file");
			exit(-1);
		}

		while (fread(&staff, sizeof(staffinfo), 1, stf1) != 0) {
			fwrite(&staff, sizeof(staffinfo), 1, stf);
		}

		printf("\n\n\nDone Delete staff\n\n\n");

	}
	else
	{
		printf("Invalid ID or password, please try again\n\n");
		system("pause");
		staffMain();
	}
	fclose(stf);
	fclose(stf1);
	system("pause");
	staffMain();
}


int staffid() {


	int num = 0;
	int num2;


	FILE* stf;

	stf = fopen("staffid.bin", "rb");
	if (stf == NULL) {

		FILE* stf2;
		stf2 = fopen("staffid.bin", "wb");
		if (stf2 == NULL) {
			printf("Unable to open file");
			system("pause");
			return;

		}
		staff.backID = 1001;
		num++;

		fwrite(&num, sizeof(int), 1, stf2);
		fclose(stf2);
		return staff.backID;



	}



	fread(&num, sizeof(int), 1, stf);


	if (num == 0) {
		staff.backID = 1001;
		num++;

	}
	else {
		staff.backID = num + 1001;
		num++;

	}
	fclose(stf);

	FILE* stf1;
	stf1 = fopen("staffid.bin", "wb");
	if (stf1 == NULL) {
		printf("Unable to open file");
		system("pause");
		return;
	}
	fwrite(&num, sizeof(int), 1, stf1);

	fclose(stf1);
	return staff.backID;
}

int staffPayslip() {

	int backid, ot, othour = 0, num = 0;
	char frontid;
	double  basic, allowance = 600.00, epf, socso, eis;
	FILE* stf;
	stf = fopen("staff.bin", "rb");

	if (stf == NULL) {

		printf("Enable to open file");
		system("pause");
	}

	printf("Enter staff ID : ");
	scanf("%c%d", &frontid, &backid);

	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {

		if (backid == staff.backID) {
			num = 1;

			do {
				printf("Please enter your basic pay : "); rewind(stdin);
				scanf("%lf", &basic);
			} while (basic < 0 || basic>10000000000000);




			do {
				printf("Do you OT in this month :\n"); rewind(stdin);
				printf("[1] YES\n");
				printf("[2] NO\n");
				scanf("%d", &ot);
			} while (ot != 1 && ot != 2);

			if (ot == 1) {
				do {
					printf("how many hour you OT : ");
					scanf("%d", &othour);
				} while (othour < 0 || othour>10000);

			}

			epf = basic * 0.11;
			socso = basic * 0.05;
			eis = basic * 0.02;
			othour = othour * 11.00;
			printf("\t\t     __________              ___        ___             __      __      __________\n");
			printf("\t\t    |   ____   |     /\\      \\  \\      /  /            |  |    ||    |   ____   |\n");
			printf("\t\t    |  |    |  |    /  \\      \\  \\    /  /  ______     |  |     __     |  |    |  |   \n");
			printf("\t\t    |  ||  |   / /\\ \\      \\  \\  /  /  /  __  \\    |  |    |  |    |  ||  |    \n");
			printf("\t\t    |    _____|  / /  \\ \\      \\  \\/  /  /  /  \\_\\   |  |    |  |    |    ______|  \n");
			printf("\t\t    |   |        / /\\ \\      \\    /   \\  \\_____    |  |    |  |    |   |       \n");
			printf("\t\t    |   |       /  ______  \\      |  |     \\_____  \\   |  |    |  |    |   | \n");
			printf("\t\t    |   |      /  /      \\  \\     |  |    ______/  /   |  |    |  |    |   |\n");
			printf("\t\t    ||     /  /        \\  \\    ||    \\/    ||    ||    |_|\n\n");

			printf("           ---------------------------------------------------------------------------------------------\n\n");


			printf("                NAME : %s \t\t\t\t\t\t\tEND PAYMENT\n", staff.name);
			printf("                POSITION : %s\n", staff.position);
			printf("                STAFF ID : %c%d\n", staff.frontID, staff.backID);



			printf("                _______________________________________________________________________________\n");
			printf("                |Earning/income                        |DETUCTION                             |\n");
			printf("                |______________________________________|______________________________________|\n");
			printf("                |BASIC PAY:%28.2f|EMPLOYEE EPF:%25.2f|\n", basic, epf);
			printf("                |NORMAL OT:%28.2f|EMPLOYEE SOCSO:%23.2f|\n", othour, socso);
			printf("                |FIXED ALLOWANCE:%22.2f|EMPLOYEE EIS:%25.2f|\n", allowance, eis);
			printf("                |                                      |                                      |\n");
			printf("                |                                      |                                      |\n");
			printf("                |                                      |                                      |\n");
			printf("                |______________________________________|______________________________________|\n");
			printf("                |GROSS PAY:%28.2f|TOTAL DETUCTION:%22.2f|\n", basic + othour + allowance, epf + socso + eis);
			printf("                |______________________________________|______________________________________|\n");
			printf("                |                                      |NETT PAY:%29.2f|\n", basic + othour + allowance - epf - socso - eis);
			printf("                |______________________________________|______________________________________|\n");

			system("pause");

		}


	}
	if (num == 0) {
		printf("invalid ID, please try again\n");
		system("pause");
		staffMain();

	}
	staffMain();

}

// Member
void memberMain() {
	loginStaffMem();

	int mode;
	mode = memberMenu();
	switch (mode) {
	case 1:
		addMember();
		break;
	case 2:
		searchMember();
		break;
	case 3:
		modifyMember();
		break;
	case 4:
		displayMember();
		break;
	case 5:
		deleteMember();
		break;
	case 6:
		main();
	default:
		break;
	}

	system("pause");
}

// display the member menu
int memberMenu() {
	int mode;
	do {
		system("cls");


		printf("==============================\n");
		printf("       Select Function\n");
		printf("==============================\n\n");

		printf("Add Member --------------- 1\n");
		printf("Search Member ------------ 2\n");
		printf("Modify Member ------------ 3\n");
		printf("Display Member ----------- 4\n");
		printf("Delete Member ------------ 5\n");
		printf("Back --------------------- 6\n\n");
		printf("Enter Number ------------- ");
		scanf(" %d", &mode);
	} while (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5 && mode != 6);

	return mode;

}

void addMember() {
	Member member;
	char cont;
	int id;

	memberID(&id);
	member.backMemberID = id;

	FILE* fp;
	fp = fopen("member.txt", "a");
	system("cls");

	do {
		// auto generate ID:
		member.frontMemberID = 'M';
		member.backMemberID++;

		// get user input
		printf("Enter your Name:");
		rewind(stdin);
		scanf("%[^\n]", &member.name);
		while (!validateName(member.name)) {
			printf("Invalid name format. Name must contain only alphabetic characters and spaces.\n");
			printf("Enter your Name:");
			rewind(stdin);
			scanf("%[^\n]", &member.name);
		}

		printf("Enter your password:");
		rewind(stdin);
		scanf("%d", &member.password);
		while (!validatePassword(member.password)) {
			printf("Invalid password format. Password must be a positive integer.\n");
			printf("Enter your password:");
			rewind(stdin);
			scanf("%d", &member.password);
		}

		printf("Enter the favorite food for your Password Recovery: ");
		rewind(stdin);
		scanf("%[^\n]", &member.passRecovery);
		while (!validatePassRec(member.passRecovery)) {
			printf("Invalid format. Password Recovery must contain only alphabetic characters and spaces.\n");
			printf("Enter the favorite food for your Password Recovery: ");
			rewind(stdin);
			scanf("%[^\n]", &member.passRecovery);
		}

		printf("Enter your gender (M/F):");
		rewind(stdin);
		scanf("%c", &member.gender);
		while (!validateGender(member.gender)) {
			printf("Invalid gender input. Please enter 'M' for male or 'F' for female.\n");
			printf("Enter your gender (M/F):");
			rewind(stdin);
			scanf("%c", &member.gender);
		}

		printf("Enter your IC:");
		scanf("%s", &member.IC);
		rewind(stdin);
		while (!validateIC(member.IC)) {
			printf("Invalid IC format. IC must be 14 characters long.\n");
			printf("Enter your IC:");
			scanf("%s", &member.IC);
			rewind(stdin);
		}

		printf("Enter your contact number:");
		rewind(stdin);
		scanf("%s", &member.contactNumber);
		while (!validateContactNumber(member.contactNumber)) {
			printf("Invalid contact number format. Contact number must be 11 digits long.\n");
			printf("Enter your contact number:");
			rewind(stdin);
			scanf("%s", &member.contactNumber);
		}

		printf("Success to create an account!!!\nYour Member ID: %c%d\n\n", member.frontMemberID, member.backMemberID);

		printf("Do you want to add more (Y to add more): ");
		rewind(stdin);
		scanf("%c", &cont);

		// record in file
		fprintf(fp, "%c%d | %s | %d | %s| %c | %s | %s\n", member.frontMemberID, member.backMemberID, member.name, member.password, member.passRecovery, member.gender, member.IC, member.contactNumber);

	} while (cont == 'y' || cont == 'Y');

	fclose(fp);
}



void searchMember() {
	Member member;

	char frontID, cnt;
	int backID, found = 0;



	FILE* fp;
	fp = fopen("member.txt", "r");
	system("cls");

	if (fp == NULL) {
		printf("Unable to open file!\n");
		return;
	}


	printf("Enter the Member ID:");
	scanf(" %c%d", &frontID, &backID);

	while (!feof(fp)) {
		fscanf(fp, "%c%d | %[^|]| %d | %[^|]| %c | %[^|]| %[^\n]\n", &member.frontMemberID, &member.backMemberID, &member.name, &member.password, &member.passRecovery, &member.gender, &member.IC, &member.contactNumber);

		if (frontID == member.frontMemberID && backID == member.backMemberID) {
			found = 1;
			printf("%-15s%-15s%-15s%-15s%-18s%-15s\n", "Member ID", "Name", "Password", "Gender", "IC", "Contact Number");
			printf("%c%-13d %-14s %-14d %-14c %-17s %-14s\n", member.frontMemberID, member.backMemberID, member.name, member.password, member.gender, member.IC, member.contactNumber);

			system("pause");
			memberMain();
		}
	}

	if (!found) {
		printf("Member not found!\n");
		system("pause");
		memberMain();
	}


	fclose(fp);
}

void modifyMember() {
	Member member;
	char frontID, ctn;
	int backID, found = 0, selection;

	FILE* fp, * fp1;
	fp = fopen("member.txt", "r");
	fp1 = fopen("memberModify.txt", "w");

	if (fp == NULL) {
		printf("Enable to open this file\n");
		exit(-1);
	}

	system("cls");
	displayMember();

	printf("Enter a Member ID to modify: ");
	scanf(" %c%d", &frontID, &backID);

	while (!feof(fp)) {
		fscanf(fp, "%c%d | %[^|]| %d | %[^|]| %c | %[^|]| %[^\n]\n", &member.frontMemberID, &member.backMemberID, &member.name, &member.password, &member.passRecovery, &member.gender, &member.IC, &member.contactNumber);
		if (frontID == 'M' && backID == member.backMemberID) {
			found = 1;
			// loop for modify more data
			do {
				// loop for validation
				do {
					printf("\nName -------------------- 1\n");
					printf("password ------------------ 2\n");
					printf("gender -------------------- 3\n");
					printf("IC ------------------------ 4\n");
					printf("Contact number ------------ 5\n");
					printf("Cancel modify ------------- 6\n");
					printf("\nSelect a field to modify: ");
					scanf(" %d", &selection);

				} while (!(selection == 1 || selection == 2 || selection == 3 || selection == 4 || selection == 5 || selection == 6));

				switch (selection) {
				case 1:
					printf("Enter the new name:");
					scanf("%s", member.name);
					rewind(stdin);
					while (!validateName(member.name)) {
						printf("Invalid name format. Name must contain only alphabetic characters and spaces.\n");
						printf("Enter your Name:");
						rewind(stdin);
						scanf("%[^\n]", &member.name);
					}
					break;
				case 2:
					printf("Enter the new password:");
					scanf("%d", &member.password);
					rewind(stdin);
					while (!validatePassword(member.password)) {
						printf("Invalid password format. Password must be a positive integer.\n");
						printf("Enter your password:");
						rewind(stdin);
						scanf("%d", &member.password);
					}
					break;
				case 3:
					printf("Enter the new gender:");
					scanf("%c", &member.gender);
					rewind(stdin);
					while (!validateGender(member.gender)) {
						printf("Invalid gender input. Please enter 'M' for male or 'F' for female.\n");
						printf("Enter your gender (M/F):");
						rewind(stdin);
						scanf("%c", &member.gender);
					}
					break;
				case 4:
					printf("Enter the new IC:");
					scanf("%s", member.IC);
					rewind(stdin);
					while (!validateIC(member.IC)) {
						printf("Invalid IC format. IC must be 14 characters long.\n");
						printf("Enter your IC:");
						scanf("%s", &member.IC);
						rewind(stdin);
					}
					break;
				case 5:
					printf("Enter the new contact number:");
					scanf("%s", member.contactNumber);
					rewind(stdin);
					while (!validateContactNumber(member.contactNumber)) {
						printf("Invalid contact number format. Contact number must be 11 digits long.\n");
						printf("Enter your contact number:");
						rewind(stdin);
						scanf("%s", &member.contactNumber);
					}
				default:
					break;
				}

				// write modified data into the temporary file


				printf("Modify more (Y/N): ");
				scanf(" %c", &ctn);
			} while (ctn == 'Y' || ctn == 'y');
			fprintf(fp1, "%c%d | %s | %d | %s| %c | %s | %s\n", member.frontMemberID, member.backMemberID, member.name, member.password, member.passRecovery, member.gender, member.IC, member.contactNumber);
		}
		else {
			fprintf(fp1, "%c%d | %s | %d | %s| %c | %s | %s\n", member.frontMemberID, member.backMemberID, member.name, member.password, member.passRecovery, member.gender, member.IC, member.contactNumber);
		}

	}
	fclose(fp);
	fclose(fp1);

	remove("member.txt");
	rename("memberModify.txt", "member.txt");

}


void displayMember() {
	Member member;

	FILE* fp;
	fp = fopen("member.txt", "r");
	system("cls");

	if (fp == NULL) {
		printf("Enable to open the file\n");
		return;
	}

	printf("%-15s%-15s%-15s%-15s%-18s%-15s\n", "Member ID", "Name", "Password", "Gender", "IC", "Contact Number");


	while (!feof(fp)) {
		fscanf(fp, "%c%d | %[^|]| %d | %[^|]| %c | %[^|]| %[^\n]\n", &member.frontMemberID, &member.backMemberID, &member.name, &member.password, &member.passRecovery, &member.gender, &member.IC, &member.contactNumber);
		printf("%c%-13d %-14s %-14d %-14c %-17s %-14s\n", member.frontMemberID, member.backMemberID, member.name, member.password, member.gender, member.IC, member.contactNumber);

	}

	fclose(fp);

}

void deleteMember() {
	Member member;
	char frontID, cnt;
	int backID, found = 0;

	FILE* fp, * fp1;
	fp = fopen("member.txt", "r");
	fp1 = fopen("new.txt", "w");

	if (fp == NULL || fp1 == NULL) {
		printf("Unable to open files for deletion.\n");
		return;
	}

	system("cls");
	displayMember();

	printf("Enter the Member ID to delete: ");
	scanf(" %c%d", &frontID, &backID);

	while (fscanf(fp, "%c%d | %[^|]| %d | %[^|]| %c | %[^|]| %[^\n]\n", &member.frontMemberID, &member.backMemberID, &member.name, &member.password, &member.passRecovery, &member.gender, &member.IC, &member.contactNumber) != EOF) {
		if (frontID == member.frontMemberID && backID == member.backMemberID) {
			found = 1;
			printf("Member found and deleted.\n");
		}
		else {
			fprintf(fp1, "%c%d | %s | %d | %s| %c | %s | %s\n", member.frontMemberID, member.backMemberID, member.name, member.password, member.passRecovery, member.gender, member.IC, member.contactNumber);
		}
	}

	fclose(fp);
	fclose(fp1);

	if (!found) {
		printf("Member not found.\n");
		remove("new.txt");
	}
	else {
		remove("member.txt");
		rename("new.txt", "member.txt");
	}
}

void passwordRecoveryMember() {
	Member member;
	char frontID, cnt, passrecov[30];
	int backID, found = 0;

	FILE* fp;
	fp = fopen("member.txt", "r");

	if (fp == NULL) {
		printf("Unable to open files for deletion.\n");
		return;
	}
	printf("Please enter your member ID:");
	scanf(" %c%d", &frontID, &backID);
	rewind(stdin);

	printf("\nEnter the favorite food that you like:");
	scanf("%[^\n]", &passrecov);
	rewind(stdin);

	while (fscanf(fp, "%c%d | %[^|]| %d | %[^|]| %c | %[^|]| %[^\n]\n", &member.frontMemberID, &member.backMemberID, &member.name, &member.password, &member.passRecovery, &member.gender, &member.IC, &member.contactNumber) != EOF) {
		if (frontID == member.frontMemberID && backID == member.backMemberID && strcmp(passrecov, member.passRecovery) == 0) {
			found = 1;
			printf("This is your password : %d.\n", member.password);
		}
	}

	if (found == 0) {
		printf("\nInvalid Member, Please try again.\n");
	}

	fclose(fp);

}

staffinfo staffs;
bool loginStaffMem() {
	char contn = ' ', pass[7];
	int staffID, found = 0;

	// open staff binary file for reading
	FILE* fp;
	fp = fopen("staff.bin", "rb");

	if (fp == NULL) {
		printf("Staff record not found!\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return false;
	}

	do {
		system("cls");
		do
		{
			memberLogo();
			printf("Enter your Staff ID: S");
			scanf(" %d", &staffID);
			rewind(stdin);
			if (!(staffID > 1000 && staffID < 10000)) {
				printf("Invalid Staff ID!\n\n");
			}
		} while (!(staffID > 1000 && staffID < 10000));


		printf("Enter your password");
		if (found != 1) {
			printf(" (Enter 0 if forgot password): ");
		}
		else printf(": ");
		scanf("%s", pass);
		rewind(stdin);
		if (strcmp(pass, "0") == 0) {
			if (found == 1) {
				printf("Request password operation too frequent, please retry later\n\n");
				continue;
			}
			found = 1;
			passwordRecovery(staffID);
			printf("\n");
			continue;
		}


		// read all records
		rewind(fp);
		while (fread(&staffs, sizeof(staffinfo), 1, fp) == 1) {
			if (staffID == staffs.backID && strcmp(pass, staffs.pass) == 0) {
				printf("Successful login!\n");
				printf("Enter Any Key to continue...");
				rewind(stdin);
				while (getc(stdin) != '\n');
				fclose(fp);
				return true;
			}
		}

		do {
			printf("\n*** Invalid STAFF ID or PASSWORD ***\n");
			printf("[Y] Retry\n");
			printf("[N] Back to Menu\n");
			printf("Enter Your Selection: ");
			scanf(" %c", &contn);
			rewind(stdin);
			if (contn == 'N' || contn == 'n') {
				fclose(fp);
				return false;
			}
		} while (!(contn == 'Y' || contn == 'y'));
	} while (1);
	fclose(fp);
	return false;
}

void memberID(int* id) {
	Member member;
	FILE* fpt = fopen("member.txt", "r");

	if (fpt == NULL) {
		*id = 1000;
		return;
	}

	while (!feof(fpt)) {
		fscanf(fpt, "%c%d | %[^|]| %d | %[^|]| %c | %[^|]| %[^\n]\n", &member.frontMemberID, &member.backMemberID, member.name, &member.password, &member.passRecovery, &member.gender, member.IC, member.contactNumber);
	}

	*id = member.backMemberID;


	fclose(fpt);
}

int validateName(const char* name) {
	// Name must be non-empty and contain only alphabetic characters
	int length = strlen(name);
	if (length == 0)
		return 0;
	for (int i = 0; i < length; ++i) {
		if (!isalpha(name[i]) && !isspace(name[i]))
			return 0;
	}
	return 1;
}

int validatePassRec(const char* passRec) {
	/* Name must be non-empty and contain only alphabetic characters*/
	int length = strlen(passRec);
	if (length == 0)
		return 0;
	for (int i = 0; i < length; ++i) {
		if (!isalpha(passRec[i]) && !isspace(passRec[i]))
			return 0;
	}
	return 1;
}

int validatePassword(int password) {
	// Password must be a positive integer
	if (password >= 0)
		return 1;
	else
		return 0;
}

int validateGender(char gender) {
	// Gender must be 'M' or 'F'
	if (toupper(gender) == 'M' || toupper(gender) == 'F')
		return 1;
	else
		return 0;
}

int validateIC(const char* IC) {
	// IC must be 12 characters long
	if (strlen(IC) == 14)
		return 1;
	else
		return 0;
}

int validateContactNumber(const char* contactNumber) {
	// Contact number must be 10 digits long
	if (strlen(contactNumber) == 11)
		return 1;
	else
		return 0;
}

void memberLogo() {
	printf("  __  __                _               \n");
	printf(" |  \\/  |              | |              \n");
	printf(" | \\  / | ___ _ __ ___ | |__   ___ _ __ \n");
	printf(" | |\\/| |/ _ \\ '_ ` _ \\| '_ \\ / _ \\ '__|\n");
	printf(" | |  | |  __/ | | | | | |_) |  __/ |   \n");
	printf(" |_|  |_|\\___|_| |_| |_|_.__/ \\___|_|   \n\n");
}



// Shedule
int scheduleMode(int selection) {
	system("cls");
	printf("=================================\n");
	printf("       Select Schedule Mode\n");
	printf("=================================\n\n");
	printf("Staff ---------------- 1\n");
	printf("Member --------------- 2\n");
	printf("Back to main menu ---- 3\n");
	printf("Enter your mode selection: ");
	scanf("%d", &selection);
	return selection;
}

void schedulingMain() {
	int select = 0, mode = 0;
	char choice;
	TrainSchedule schedule;
	int currentTrainID = 1001;
	schedule.availableSeats = 400;

	FILE* fptr = fopen("train_schedule.txt", "a");
	if (fptr == NULL) {
		printf("Error opening file");
		exit(-1);
	}

	do {
		select = scheduleMode(select);

		if (select == 1) {
			staffVerify(&select);
			if (select != 0) {
				do {
					scheduleMenu(&select);

					// admin mode
					switch (select) {
					case 1:
						do {
							currentTrainID = addSchedule(currentTrainID);
							printf("Do you want to add another schedule? (Y/N): ");
							scanf(" %c", &choice);
						} while (choice == 'Y' || choice == 'y');
						break;
					case 2:
						do {
							searchSchedule();
							printf("Do you want to search another schedule? (Y/N): ");
							scanf(" %c", &choice);
						} while (choice == 'Y' || choice == 'y');
						break;
					case 3:
						do {
							modifySchedule();
							printf("Do you want to modify another schedule? (Y/N): ");
							scanf(" %c", &choice);
						} while (choice == 'Y' || choice == 'y');
						break;
					case 4:
						displaySchedule();
						printf("Do you want to back to menu? (Y/N): ");
						scanf(" %c", &choice);
						break;
					case 5:
						do {
							deleteSchedule();
							printf("Do you want to delete another schedule? (Y/N): ");
							scanf(" %c", &choice);
						} while (choice == 'Y' || choice == 'y');
						break;
					case 6:
						scheduleReport(&mode);
						printf("Do you want to go back to the schedule menu? (Y/N): ");
						scanf(" %c", &choice);
						break;
					case 7:

						break;
					default:
						printf("Invalid option\n");
						break;
					}
				} while (select != 7);
			}
		}
		else if (select == 2) {
			memberVerify(&mode);
		}
		else if (select == 3) {
			main();

		}
		else {
			printf("\nInvalid option\n");
			system("pause");
		}
	} while (select != 3);

	fclose(fptr);
}


void memberVerify(int* mode) {
	typedef struct {
		char bookingId[10], trainID[10];
	} Booking;

	struct Member {
		char frontMemberID, name[30], passwordrec[10], gender, IC[15], contactNumber[12];
		int password, backMemberID;
		Booking booking;
	};

	int memberID, password;
	struct Member member;
	char cnt;
	int found = 0;

	FILE* fp;
	fp = fopen("member.txt", "r");
	system("cls");

	if (fp == NULL) {
		printf("Unable to open file!\n");
		system("pause");
		return;
	}

	do {
		system("cls");
		printf("=================================\n");
		printf("         Member Mode\n");
		printf("=================================\n");
		printf("Enter Your Member ID: M");
		scanf("%d", &memberID);
		printf("Enter password: ");
		scanf("%d", &password);

		rewind(fp); // reset file pointer to the beginning

		while (!feof(fp)) {
			fscanf(fp, "M%d | %[^|]| %d | %c | %[^|]| %[^\n]\n", &member.backMemberID, &member.name, &member.password, &member.gender, &member.IC, &member.contactNumber);

			if (memberID == member.backMemberID && password == member.password) {
				found = 1;
				printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Member ID", "Name", "Password", "Gender", "IC", "Contact Number");
				printf("M%-13d %-14s %-14d %-14c %-14s %-14s\n", member.backMemberID, member.name, member.password, member.gender, member.IC, member.contactNumber);
				rewind(stdin);
				break;
			}
		}

		if (found == 1) {
			memberLogin(mode);
		}
		else {
			printf("Invalid Member ID or Password\n");
			printf("Invalid ID or Password, please try again\n\n");
			printf("Try again --------- Y\n");
			printf("Back -------------- N\n");
			printf("Enter your selection: ");
			scanf(" %c", &cnt);
			rewind(stdin);
		}
	} while (cnt == 'y' || cnt == 'Y');//got error while returning or something

	fclose(fp);
}



void memberLogin(int* mode) {
	int choice;

	do {
		system("cls");
		printf("=================================\n");
		printf("         Login Successful\n");
		printf("=================================\n");
		printf("         Member Mode\n");
		printf("=================================\n");
		printf("       Select Schedule Function\n");
		printf("=================================\n\n");

		printf("Search Schedule ------------ 1\n");
		printf("Display Schedule ----------- 2\n");
		printf("Back ----------------------- 3\n");
		printf("Main Menu ------------------ 4\n");
		printf("Enter Selection: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			do {
				searchSchedule();
				printf("Do you want to search another schedule? (Y/N): ");
				scanf(" %c", &choice);
			} while (choice == 'Y' || choice == 'y');
			break;
		case 2:
			displaySchedule();
			break;
		case 3:
			return;
		case 4:
			main();
			return;
		default:
			printf("Invalid option\n");
			break;
		}

		char backChoice;
		printf("Return Back? (Y/N): ");
		scanf(" %c", &backChoice);

		if (backChoice == 'Y' || backChoice == 'y') {
			memberLogin(mode);
			return;
		}

	} while (1); // unlimited loop 
}



void staffVerify() {
	typedef struct {
		char  name[51], frontID, position[51], fatherName[51], pass[7];
		int  backID;

	}staffinfo;

	int staffID, mode;
	char frontid, password[7];
	int backid, num = 0;
	char cont;
	staffinfo staff;

	FILE* stf;
	stf = fopen("staff.bin", "rb");

	if (stf == NULL) {
		printf("Unabale to open file");
		return;
	}

	system("cls");
	printf("=================================\n");
	printf("         Staff Mode\n");
	printf("=================================\n");
	printf("Enter Your Staff Id: S");
	scanf("%d", &staffID);
	printf("Enter password: ");
	scanf("%s", password);

	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
		if (staffID == staff.backID && strcmp(password, staff.pass) == 0) {
			num = 1;
		}
	}


	if (num == 0) {

		printf("Invalid ID or Password, please try again\n\n");
		printf("Continue --------- Y\n");
		printf("Back ------------- N\n");
		printf("Enter your selection: ");
		rewind(stdin);
		scanf("%c", &cont);
		if (cont == 'y' || cont == 'Y') {
			staffVerify();
		}
		else if (cont == 'n' || cont == 'N') {
			schedulingMain();
		}
		else {
			printf("Invalid option, enter to continue: ");
			system("pause");
			return;
		}
	}

	num = 0;
}


void scheduleMenu(int* mode) {
	do {
		system("cls");
		printf("=================================\n");
		printf("         Login Successful\n");
		printf("=================================\n");
		printf("         Staff Mode\n");
		printf("=================================\n");
		printf("       Select Schedule Function\n");
		printf("=================================\n\n");

		printf("Add Schedule --------------- 1\n");
		printf("Search Schedule ------------ 2\n");
		printf("Modify Schedule ------------ 3\n");
		printf("Display Schedule ----------- 4\n");
		printf("Delete Schedule ------------ 5\n");
		printf("Schedule Report ------------ 6\n");
		printf("Back ----------------------- 7\n");
		printf("Main Menu------------------- 8\n\n");
		printf("Enter Number --------------- ");
		scanf("%d", mode);
	} while (*mode != 1 && *mode != 2 && *mode != 3 && *mode != 4 && *mode != 5 && *mode != 6 && *mode != 7 && *mode != 8);

	return;

}


int addSchedule(int currentTrainID) {
	system("cls");
	printf("==============================\n");
	printf("       Add Schedule\n");
	printf("==============================\n\n");

	TrainSchedule schedule;

	FILE* fptr = fopen("train_schedule.txt", "a");

	if (fptr == NULL) {
		printf("Error opening file\n");
		return currentTrainID;
	}

	FILE* read = fopen("train_schedule.txt", "r");

	if (read == NULL) {
		schedule.trainID = 1001;
		printf("Train ID: %c%d\n", TRAIN_FRONT_ID, schedule.trainID);
		return currentTrainID;
	}

	while (!feof(read)) {
		fscanf(read, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice);

		if (currentTrainID <= schedule.trainID) {
			currentTrainID = schedule.trainID + 1;
		}

	}
	fclose(read);

	schedule.trainID = currentTrainID;
	printf("Train ID: %c%d\n", TRAIN_FRONT_ID, schedule.trainID);

	printf("Enter Departure Station: ");
	rewind(stdin);
	scanf("%s", schedule.departureStation);
	printf("Enter Arrival Station: ");
	rewind(stdin);
	scanf("%s", schedule.arrivalStation);
	printf("Enter Departure Date (DD/MM/YYYY): ");
	rewind(stdin);
	scanf("%d/%d/%d", &schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year);
	printf("Enter Arrival Date (DD/MM/YYYY): ");
	rewind(stdin);
	scanf("%d/%d/%d", &schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year);

	schedule.departureTime.hour = 0, schedule.departureTime.min = 0;

	do {
		printf("Enter Departure Time 24 hours (HH:MM): ");
		rewind(stdin);
		scanf("%d:%d", &schedule.departureTime.hour, &schedule.departureTime.min);
		if (
			schedule.departureTime.hour < 0 || schedule.departureTime.hour >= 24 ||
			schedule.departureTime.min < 0 || schedule.departureTime.min >= 60) {
			printf("Invalid time. Please enter a valid time.\n");
		}
	} while (schedule.departureTime.hour < 0 || schedule.departureTime.hour >= 24 ||
		schedule.departureTime.min < 0 || schedule.departureTime.min >= 60);

	schedule.arrivalTime.hour = 0, schedule.arrivalTime.min = 0;
	do {
		printf("Enter Arrival Time 24 hours (HH:MM): ");
		rewind(stdin);
		scanf("%d:%d", &schedule.arrivalTime.hour, &schedule.arrivalTime.min);
		if (
			schedule.arrivalTime.hour < 0 || schedule.arrivalTime.hour >= 24 ||
			schedule.arrivalTime.min < 0 || schedule.arrivalTime.min >= 60) {
			printf("Invalid time. Please enter a valid time.\n");
		}
	} while (schedule.arrivalTime.hour < 0 || schedule.arrivalTime.hour >= 24 ||
		schedule.arrivalTime.min < 0 || schedule.arrivalTime.min >= 60);


	schedule.availableSeats = 400;
	printf("Available Seats: %d\n", schedule.availableSeats);
	printf("Enter ticket price: RM");
	scanf("%f", &schedule.ticketPrice);



	fprintf(fptr, "%c%d, %s, %s, %02d/%02d/%04d, %02d/%02d/%04d, %02d:%02d, %02d:%02d, %d, %.2f\n",
		TRAIN_FRONT_ID,
		schedule.trainID, schedule.departureStation, schedule.arrivalStation,
		schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
		schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
		schedule.departureTime.hour, schedule.departureTime.min,
		schedule.arrivalTime.hour, schedule.arrivalTime.min,
		schedule.availableSeats, schedule.ticketPrice);

	fclose(fptr);
	return schedule.trainID;
}



void searchSchedule() {
	system("cls");
	printf("==============================\n");
	printf("       Search Schedule\n");
	printf("==============================\n\n");
	int trainID;
	FILE* fptr = fopen("train_schedule.txt", "r");
	if (fptr == NULL) {
		printf("Error opening file\n");
		exit(-1);
	}

	printf("Enter Train ID to search: T");
	scanf("%d", &trainID);

	TrainSchedule schedule;
	int found = 0;

	printf("\nTrain Schedule:\n");
	printf("===========================================================================================================\n");
	printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
	printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
	printf("===========================================================================================================\n");

	while (!feof(fptr)) {
		fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice);

		if (trainID == schedule.trainID) {
			found = 1;
			printf("%c%d\t    %-13s%-14s%02d/%02d/%04d   %02d/%02d/%04d\t   %02d:%02d\t%02d:%02d\t    %-9d %.2f\n",
				TRAIN_FRONT_ID,
				schedule.trainID, schedule.departureStation, schedule.arrivalStation,
				schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
				schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
				schedule.departureTime.hour, schedule.departureTime.min,
				schedule.arrivalTime.hour, schedule.arrivalTime.min,
				schedule.availableSeats, schedule.ticketPrice);
		}

	}

	if (!found) {
		printf("Train ID '%c%d' not found\n", TRAIN_FRONT_ID, trainID);
	}

	fclose(fptr);
}


void modifySchedule() {
	system("cls");
	printf("==============================\n");
	printf("       Modify Schedule\n");
	printf("==============================\n\n");
	int trainID;
	printf("Enter Train ID to modify: T");
	scanf("%d", &trainID);

	FILE* fptr = fopen("train_schedule.txt", "r");
	FILE* temp = fopen("temp.txt", "w");

	if (fptr == NULL || temp == NULL) {
		printf("Error opening file\n");
		exit(-1);
	}

	printf("\nTrain Schedule:\n");
	printf("===========================================================================================================\n");
	printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
	printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
	printf("===========================================================================================================\n");

	TrainSchedule schedule;
	int found = 0;

	while (!feof(fptr)) {
		fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice);

		if (trainID == schedule.trainID) {
			found = 1;
			printf("%c%d\t    %-13s%-14s%02d/%02d/%04d   %02d/%02d/%04d\t   %02d:%02d\t%02d:%02d\t    %-9d %.2f\n",
				TRAIN_FRONT_ID,
				schedule.trainID,
				schedule.trainID, schedule.departureStation, schedule.arrivalStation,
				schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
				schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
				schedule.departureTime.hour, schedule.departureTime.min,
				schedule.arrivalTime.hour, schedule.arrivalTime.min,
				schedule.availableSeats, schedule.ticketPrice);
			printf("\nEnter New Departure Station: ");
			scanf(" %[^\n]", schedule.departureStation);
			printf("Enter New Arrival Station: ");
			scanf(" %[^\n]", schedule.arrivalStation);
			printf("Enter New Departure Date (DD/MM/YYYY): ");
			scanf("%d/%d/%d", &schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year);
			printf("Enter New Arrival Date (DD/MM/YYYY): ");
			scanf("%d/%d/%d", &schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year);

			do {
				printf("Enter New Departure Time 24 hours (HH:MM): ");
				rewind(stdin);
				scanf("%d:%d", &schedule.departureTime.hour, &schedule.departureTime.min);
				if (
					schedule.departureTime.hour < 0 || schedule.departureTime.hour >= 24 ||
					schedule.departureTime.min < 0 || schedule.departureTime.min >= 60) {
					printf("Invalid time. Please enter a valid time.\n");
				}
			} while (schedule.departureTime.hour < 0 || schedule.departureTime.hour >= 24 ||
				schedule.departureTime.min < 0 || schedule.departureTime.min >= 60);

			schedule.arrivalTime.hour = 0, schedule.arrivalTime.min = 0;
			do {
				printf("Enter New Arrival Time 24 hours (HH:MM): ");
				rewind(stdin);
				scanf("%d:%d", &schedule.arrivalTime.hour, &schedule.arrivalTime.min);
				if (
					schedule.arrivalTime.hour < 0 || schedule.arrivalTime.hour >= 24 ||
					schedule.arrivalTime.min < 0 || schedule.arrivalTime.min >= 60) {
					printf("Invalid time. Please enter a valid time.\n");
				}
			} while (schedule.arrivalTime.hour < 0 || schedule.arrivalTime.hour >= 24 ||
				schedule.arrivalTime.min < 0 || schedule.arrivalTime.min >= 60);

			printf("Enter ticket price: ");
			scanf("%f", &schedule.ticketPrice);

			char confirm; // check confirm
			printf("Confirm modify (Y/N): ");
			scanf(" %c", &confirm);
			if (confirm != 'Y' && confirm != 'y') {
				printf("\nCancelled\n");
				fclose(fptr);
				fclose(temp);
				return;
			}
		}

		fprintf(temp, "%c%d, %s, %s, %02d/%02d/%04d, %02d/%02d/%04d, %02d:%02d, %02d:%02d, %d, %.2f\n",
			TRAIN_FRONT_ID,
			schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
			schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
			schedule.departureTime.hour, schedule.departureTime.min,
			schedule.arrivalTime.hour, schedule.arrivalTime.min,
			schedule.availableSeats, schedule.ticketPrice);
	}

	fclose(fptr);
	fclose(temp);

	fptr = fopen("train_schedule.txt", "w");
	temp = fopen("temp.txt", "r");

	while (!feof(temp)) {
		fscanf(temp, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice);

		fprintf(fptr, "%c%d, %s, %s, %02d/%02d/%04d, %02d/%02d/%04d, %02d:%02d, %02d:%02d, %d, %.2f\n",
			TRAIN_FRONT_ID,
			schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
			schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
			schedule.departureTime.hour, schedule.departureTime.min,
			schedule.arrivalTime.hour, schedule.arrivalTime.min,
			schedule.availableSeats, schedule.ticketPrice);
	}

	if (!found) {
		printf("Train ID '%c%d' not found\n", TRAIN_FRONT_ID, trainID);
	}
	else {
		printf("\nSchedule modified successfully\n");
	}
	fclose(fptr);
	fclose(temp);
}


void deleteSchedule() {
	system("cls");
	printf("==============================\n");
	printf("       Delete Schedule\n");
	printf("==============================\n\n");

	int trainID;
	printf("Enter Train ID to delete: T");
	scanf("%d", &trainID);

	FILE* fptr = fopen("train_schedule.txt", "r");
	FILE* temp = fopen("temp.txt", "w");

	if (fptr == NULL || temp == NULL) {
		printf("Error opening file\n");
		exit(-1);
	}

	printf("\nTrain Schedule:\n");
	printf("===========================================================================================================\n");
	printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
	printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
	printf("===========================================================================================================\n");

	TrainSchedule schedule;
	int found = 0;

	while (!feof(fptr)) {
		fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice);

		if (trainID == schedule.trainID) {
			found = 1;
			printf("%c%d\t    %-13s%-14s%02d/%02d/%04d    %02d/%02d/%04d\t   %02d:%02d\t%02d:%02d\t    %-9d %.2f\n",
				TRAIN_FRONT_ID,
				schedule.trainID, schedule.departureStation, schedule.arrivalStation,
				schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
				schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
				schedule.departureTime.hour, schedule.departureTime.min,
				schedule.arrivalTime.hour, schedule.arrivalTime.min,
				schedule.availableSeats, schedule.ticketPrice);

			char confirm;
			printf("Confirm delete (Y/N): ");
			scanf(" %c", &confirm);
			if (confirm != 'Y' && confirm != 'y') {
				printf("\nCancelled\n");
				fclose(fptr);
				fclose(temp);
				return;
			}
		}
		else {
			fprintf(temp, "T%d, %s, %s, %02d/%02d/%04d, %02d/%02d/%04d, %02d:%02d, %02d:%02d, %d, %.2f\n",
				schedule.trainID, schedule.departureStation, schedule.arrivalStation,
				schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
				schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
				schedule.departureTime.hour, schedule.departureTime.min,
				schedule.arrivalTime.hour, schedule.arrivalTime.min,
				schedule.availableSeats, schedule.ticketPrice);
		}
	}

	fclose(fptr);
	fclose(temp);

	fptr = fopen("train_schedule.txt", "w");
	temp = fopen("temp.txt", "r");

	while (!feof(temp)) {
		fscanf(temp, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice);

		fprintf(fptr, "T%d, %s, %s, %02d/%02d/%04d, %02d/%02d/%04d, %02d:%02d, %02d:%02d, %d, %.2f\n",
			schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
			schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
			schedule.departureTime.hour, schedule.departureTime.min,
			schedule.arrivalTime.hour, schedule.arrivalTime.min,
			schedule.availableSeats, schedule.ticketPrice);
	}

	fclose(fptr);
	fclose(temp);

	if (found) {
		printf("\nSchedule deleted successfully\n");
	}
	else {
		printf("Train ID '%c%d' not found\n", TRAIN_FRONT_ID, trainID);
	}
}


void displaySchedule() {
	system("cls");
	printf("==============================\n");
	printf("       Display Schedule\n");
	printf("==============================\n\n");
	FILE* fptr = fopen("train_schedule.txt", "r");
	if (fptr == NULL) {
		printf("Error opening file\n");
		exit(-1);
	}

	char checkRecord[7];
	TrainSchedule schedule;

	printf("\nTrain Schedule:\n");
	printf("===========================================================================================================\n");
	printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
	printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
	printf("===========================================================================================================\n");

	//here is to check the file record, if no record then return
	if (fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
		&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
		&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
		&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
		&schedule.departureTime.hour, &schedule.departureTime.min,
		&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
		&schedule.availableSeats, &schedule.ticketPrice) == EOF) {
		printf("No records found in the schedule.\n");
		fclose(fptr);
		return;
	}

	//if got record, the value will store to variable, so print out the record first and continue with while loop do display next record
	printf("%c%d\t    %-13s%-14s%02d/%02d/%04d   %02d/%02d/%04d\t   %02d:%02d\t%02d:%02d\t    %-9d %.2f\n",
		TRAIN_FRONT_ID,
		schedule.trainID, schedule.departureStation, schedule.arrivalStation,
		schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
		schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
		schedule.departureTime.hour, schedule.departureTime.min,
		schedule.arrivalTime.hour, schedule.arrivalTime.min,
		schedule.availableSeats, schedule.ticketPrice);

	//display the next record until end file
	while (!feof(fptr)) {
		fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice);

		printf("%c%d\t    %-13s%-14s%02d/%02d/%04d   %02d/%02d/%04d\t   %02d:%02d\t%02d:%02d\t    %-9d %.2f\n",
			TRAIN_FRONT_ID,
			schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
			schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
			schedule.departureTime.hour, schedule.departureTime.min,
			schedule.arrivalTime.hour, schedule.arrivalTime.min,
			schedule.availableSeats, schedule.ticketPrice);
	}

	fclose(fptr);
}


void scheduleReport(int* sreport) {

	int menu, day, month, year;
	char cont;
	char station[50];

	TrainSchedule schedule;
	int found = 0;
	int totalSchedule = 0;
	float totalRevenue = 0.0;

	FILE* fptr = fopen("train_schedule.txt", "r");
	if (fptr == NULL) {
		printf("Error opening file\n");
		return;
	}

	system("cls");
	printf("==============================\n");
	printf("       Schedule Report\n");
	printf("==============================\n\n");
	printf("Select an option:\n");
	printf("1. View overall report\n");
	printf("2. Search report based on departure station\n");
	printf("3. Search report based on departure date\n");
	printf("4. Back\n");
	printf("Enter your choice: ");
	scanf("%d", &menu);

	switch (menu) {
	case 1:
		totalSchedule = 0;
		totalRevenue = 0.0;
		system("cls");
		printf("==============================\n");
		printf("     Overal Schedule Report  \n");
		printf("==============================\n\n");
		printf("===========================================================================================================\n");
		printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
		printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
		printf("===========================================================================================================\n");

		// read data until end of file
		while (fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice) != EOF) {

			printf("%c%d\t    %-13s%-14s%02d/%02d/%04d   %02d/%02d/%04d\t   %02d:%02d\t%02d:%02d\t    %-9d %.2f\n",
				TRAIN_FRONT_ID,
				schedule.trainID, schedule.departureStation, schedule.arrivalStation,
				schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
				schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
				schedule.departureTime.hour, schedule.departureTime.min,
				schedule.arrivalTime.hour, schedule.arrivalTime.min,
				schedule.availableSeats, schedule.ticketPrice);
			totalSchedule++;
			totalRevenue += schedule.ticketPrice;

		}

		printf("\n\nTotal number of schedules: %d\n", totalSchedule);
		printf("Total revenue generated: RM%.2f\n\n", totalRevenue);

		fclose(fptr);

		printf("Do you want to back to schedule report menu?(Y/N):");
		rewind(stdin);
		cont = getchar();
		if (cont == 'y' || cont == 'Y') {
			scheduleReport(&sreport);
		}

		break;
	case 2:
		do {
			system("cls");
			printf("==============================\n");
			printf("       Schedule Report By Station\n");
			printf("==============================\n\n");
			printf("Enter the departure station: ");
			scanf("%s", station);

			stationScheduleReport(station);

			printf("\nDo you want continue search another report?(Y/N): ");
			rewind(stdin);
			cont = getchar();
			printf("\n");
		} while (cont == 'y' || cont == 'Y');
		printf("Do you want to back to schedule report menu?(Y/N):");
		rewind(stdin);
		cont = getchar();
		if (cont == 'y' || cont == 'Y') {
			scheduleReport(&sreport);
		}
		break;
	case 3:
		do {
			system("cls");
			printf("==============================\n");
			printf("       Schedule Report By Date\n");
			printf("==============================\n\n");
			printf("Enter the departure date (DD/MM/YYYY): ");
			scanf("%d/%d/%d", &day, &month, &year);
			printf("%d/%d/%d\n", day, month, year);
			dateScheduleReport(day, month, year);

			printf("\nDo you want continue search another report?(Y/N): ");
			rewind(stdin);
			cont = getchar();
			printf("\n");
		} while (cont == 'y' || cont == 'Y');

	case 4:
		//exit
		return;
	default:
		printf("Invalid choice. Please try again.\n");
		break;
	}



}


void overalScheduleReport(int day, int month, int year) {
	FILE* fptr = fopen("train_schedule.txt", "r");
	if (fptr == NULL) {
		printf("Error opening file\n");
		return;
	}

	TrainSchedule schedule;
	int found = 0;
	int totalSchedule = 0;
	float totalRevenue = 0.0;

	// read data until end of file
	while (fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
		&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
		&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
		&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
		&schedule.departureTime.hour, &schedule.departureTime.min,
		&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
		&schedule.availableSeats, &schedule.ticketPrice) != EOF) {

		//find the record by date and make calculation of total train schedule and total price 
		if (schedule.departureDate.day == day && schedule.departureDate.month == month && schedule.departureDate.year == year) {
			found = 1;
			printf("%c%d\t    %-13s%-14s%02d/%02d/%04d   %02d/%02d/%04d\t   %02d:%02d\t%02d:%02d\t    %-9d %.2f\n",
				TRAIN_FRONT_ID,
				schedule.trainID, schedule.departureStation, schedule.arrivalStation,
				schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
				schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
				schedule.departureTime.hour, schedule.departureTime.min,
				schedule.arrivalTime.hour, schedule.arrivalTime.min,
				schedule.availableSeats, schedule.ticketPrice);
			totalSchedule++;
			totalRevenue += schedule.ticketPrice;
		}

	}

	printf("\n\nTotal number of schedules: %d\n", totalSchedule);
	printf("Total overal revenue: RM%.2f\n", totalRevenue);

	fclose(fptr);

	if (!found || totalSchedule == 0) {
		printf("\nNo record\n", day, month, year);
	}

	totalSchedule = 0;
	totalRevenue = 0;
}

void stationScheduleReport(char station[50]) {
	system("cls");
	printf("======================================\n");
	printf("  Schedule Report By Departure Station\n");
	printf("======================================\n\n");

	FILE* fptr = fopen("train_schedule.txt", "r");
	if (fptr == NULL) {
		printf("Error opening file\n");
		return;
	}

	TrainSchedule schedule;
	int found = 0;
	int totalSchedule = 0;
	float totalRevenue = 0.0;

	printf("===========================================================================================================\n");
	printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
	printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
	printf("===========================================================================================================\n");

	while (!feof(fptr)) {
		fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice);

		if (strcmp(station, schedule.departureStation) == 0) {
			found = 1;
			printf("%c%d\t    %-13s%-14s%02d/%02d/%04d   %02d/%02d/%04d\t   %02d:%02d\t%02d:%02d\t    %-9d %.2f\n",
				TRAIN_FRONT_ID,
				schedule.trainID, schedule.departureStation, schedule.arrivalStation,
				schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
				schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
				schedule.departureTime.hour, schedule.departureTime.min,
				schedule.arrivalTime.hour, schedule.arrivalTime.min,
				schedule.availableSeats, schedule.ticketPrice);
			totalSchedule++;
			totalRevenue += schedule.ticketPrice;
		}
	}
	printf("\n\nTotal number of schedules: %d\n", totalSchedule);
	printf("Total revenue by departure date: RM%.2f\n", totalRevenue);

	fclose(fptr);

	if (!found) {
		printf("No record\n");
	}
}

void dateScheduleReport(int day, int month, int year) {
	system("cls");
	printf("===================================\n");
	printf("  Schedule Report By Departure Date\n");
	printf("===================================\n\n");

	FILE* fptr = fopen("train_schedule.txt", "r");
	if (fptr == NULL) {
		printf("Error opening file\n");
		return;
	}

	TrainSchedule schedule;
	int found = 0;
	int totalSchedule = 0;
	float totalRevenue = 0.0;

	printf("===========================================================================================================\n");
	printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
	printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
	printf("===========================================================================================================\n");

	// read data until end of file
	while (!feof(fptr)) {
		fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice);
		//find the record by date and make calculation of total train schedule and total price 
		if (schedule.departureDate.day == day && schedule.departureDate.month == month && schedule.departureDate.year == year) {
			found = 1;
			printf("%c%d\t    %-13s%-14s%02d/%02d/%04d   %02d/%02d/%04d\t   %02d:%02d\t%02d:%02d\t    %-9d %.2f\n",
				TRAIN_FRONT_ID,
				schedule.trainID, schedule.departureStation, schedule.arrivalStation,
				schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
				schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
				schedule.departureTime.hour, schedule.departureTime.min,
				schedule.arrivalTime.hour, schedule.arrivalTime.min,
				schedule.availableSeats, schedule.ticketPrice);
			totalSchedule++;
			totalRevenue += schedule.ticketPrice;
		}

	}

	printf("\n\nTotal number of schedules: %d\n", totalSchedule);
	printf("Total revenue by departure date: RM%.2f\n", totalRevenue);

	fclose(fptr);

	if (!found) {
		printf("No record\n");
	}
}

void scheduleLogo() {
	printf("  _____      _              _       _      \n");
	printf(" / ____|    | |            | |     | |     \n");
	printf("| (___   ___| |__   ___  __| |_   _| | ___ \n");
	printf(" \\___ \\ / __| '_ \\ / _ \\/ _` | | | | |/ _ \\\n");
	printf(" ____) | (__| | | |  __/ (_| | |_| | |  __/\n");
	printf("|_____/ \\___|_| |_|\\___|\\__,_|\\__,_|_|\\___|\n");

}




// Booking
// quantity and seat number

Member member;
Member memberTemp;
Member memberTemp2;
staffinfo staffs;
TrainSchedule schedule = { 0 };
struct Date availableSeat[MAX_BOOKING_DAYS];

void bookingMain() {
	int mode, loginMode, trainID;
	bookingMenu(&loginMode);

	// staff mode
	if (loginMode == 1) {
		// login Staff
		if (!loginStaff()) return;

		mode = 0;
		while (1) {
			bookingMenuStaff(&mode);
			switch (mode) {
			case 1:
				displayBooking(0, "staff");
				break;
			case 2:
				searchBooking("staff");
				break;
			case 3:
				deleteBooking();
				break;
			case 4:
				do {
					system("cls");
					printf("Enter Train ID that you want to view seats (Enter 0 to view train schedule): T");
					scanf("%d", &trainID);
					rewind(stdin);

					if (trainID <= 1000 || trainID >= 10000) {
						continue;
					}

					// display train information
					if (trainID == 0) {
						schedulingData(trainID, "display", 0, 0);
						printf("\n");
						continue;
					}
				} while (1);

				system("cls");
				displaySeat(trainID);
				break;
			case 5:
				summaryReport();
				break;
			default:
				return;
			}
		}
	}
	// member mode
	else if (loginMode == 2) {
		// login member and get member id
		if (loginMember(&member.backMemberID) == false) return;

		mode = 0;
		while (1) {
			bookingMenuMember(&mode);
			switch (mode) {
			case 1:
				addBooking();
				break;
			case 2:
				searchBooking("member");
				break;
			case 3:
				modifyBooking();
				break;
			case 4:
				displayBooking(0, "member");
				break;
			case 5:
				cancelBooking();
				break;
			default:
				return;
			}
		}
	}
	else return;




}

// Menu
void bookingMenu(int* loginMode) {
	do {
		system("cls");
		bookingLogo();

		printf("   Login\n");
		printf("===========\n");
		printf("[1] Staff\n");
		printf("[2] Member\n");
		printf("[3] Back to Main Menu\n");
		printf("\nSelect: ");
		scanf("%d", loginMode);
		rewind(stdin);
	} while (!(*loginMode == 1 || *loginMode == 2 || *loginMode == 3));

}

void bookingMenuStaff(int* mode) {
	do {
		system("cls");
		bookingLogo();

		printf("*******************************************\n");
		printf("         Welcome Back, Staff S%d\n", staffs.backID);
		printf("*******************************************\n\n");
		printf("View All Booking Records ---------------- 1\n");
		printf("Search a Booking Record  ---------------- 2\n");
		printf("Delete a Booking Record ----------------- 3\n");
		printf("View Seats ------------------------------ 4\n");
		printf("View Booking Summary Report ------------- 5\n");
		printf("Back to Main Menu ----------------------- 6\n\n");
		printf("Enter Number ---------------------------- ");
		scanf(" %d", mode);
		rewind(stdin);
	} while (*mode != 1 && *mode != 2 && *mode != 3 && *mode != 4 && *mode != 5);
}

void bookingMenuMember(int* mode) {
	do {
		system("cls");
		bookingLogo();

		printf("********************************************\n");
		printf("         Welcome Back, Member M%d\n", member.backMemberID);
		printf("********************************************\n\n");
		printf("Add a Booking ---------------------------- 1\n");
		printf("Search a Booking ------------------------- 2\n");
		printf("Modify Booking Details ------------------- 3\n");
		printf("View Booking Details --------------------- 4\n");
		printf("Cancel a Booking ------------------------- 5\n");
		printf("Back to Main Menu ------------------------ 6\n\n");
		printf("Enter Number ----------------------------- ");
		scanf(" %d", mode);
		rewind(stdin);
	} while (*mode != 1 && *mode != 2 && *mode != 3 && *mode != 4 && *mode != 5 && *mode != 6);

}

void addBooking() {
	char confirm;
	int id, bookingNum, found = 0;
	double price;
	bool valid;
	FILE* fp = fopen("Booking.bin", "ab");

	if (fp == NULL) {
		printf("Unable to open file!");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return;
	}

	// get booking ID (auto increment)
	bookingNum = bookingID_Num(&id);
	member.book[bookingNum].bookingID = id;

	system("cls");

	// booking ID
	member.book[bookingNum].bookingID++;

	// booking date
	time_t bookingDate;
	time(&bookingDate);
	struct tm date = *localtime(&bookingDate);
	member.book[bookingNum].bookingDate.day = date.tm_mday;
	member.book[bookingNum].bookingDate.month = date.tm_mon + 1;
	member.book[bookingNum].bookingDate.year = date.tm_year + 1900;
	time_t bookingTimestamp = mktime(&date);

	printf("Booking ID: %c%d\n\n", BOOKING_FRONT_ID, member.book[bookingNum].bookingID);

	// user input
	do {
		printf("Enter Train ID");
		if (found != 1) {
			printf(" (Enter 0 to view train schedule): T");
		}
		else printf(": T");
		scanf(" %d", &member.book[bookingNum].trains.trainID);
		rewind(stdin);

		// display train information
		if (member.book[bookingNum].trains.trainID == 0 && found != 1) {
			found = 1;
			valid = schedulingData(member.book[bookingNum].trains.trainID, "display", bookingNum, &price);
			printf("\n");
			continue;
		}
		// validate train ID
		else if (member.book[bookingNum].trains.trainID > 1000 || member.book[bookingNum].trains.trainID < 10000) {
			valid = schedulingData(member.book[bookingNum].trains.trainID, "validate", bookingNum, &price);
		}

		if (valid) {
			break;
		}
		else {
			printf("Invalid Train ID!\n\n");
		}
	} while (1);

	// enter quntity of booking
	do {
		printf("\nEnter quantity of booking: ");
		scanf(" %d", &member.book[bookingNum].quantity);
		rewind(stdin);
		if (member.book[bookingNum].quantity >= 1 && member.book[bookingNum].quantity <= 10) {
			break;
		}
		else {
			if (member.book[bookingNum].quantity > 10)
				printf("Invalid! Maximum quantity is 10\n\n");

			else
				printf("Invalid quantity of booking\n\n");
		}
	} while (1);

	found = 0;

	// select seat
	printf("\n             Select Seat            \n");
	printf("<<< Enter 0 to veiw available seat >>>\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (int i = 0; i < member.book[bookingNum].quantity; i++) { // based on quantity
		do {
			printf("\n");

			// Coach
			do {
				printf("[%d] Enter coach: ", i + 1);
				scanf(" %c", &member.book[bookingNum].trains.seats[i].coach);
				rewind(stdin);

				// Upper Case
				if (member.book[bookingNum].trains.seats[i].coach >= 'q' && member.book[bookingNum].trains.seats[i].coach <= 'z')
					member.book[bookingNum].trains.seats[i].coach = toupper(member.book[bookingNum].trains.seats[i].coach);

				// View seat
				if (member.book[bookingNum].trains.seats[i].coach == '0' && found != 1) {
					found = 1;
					displaySeat(member.book[bookingNum].trains.trainID);
					continue;
				}
			} while (member.book[bookingNum].trains.seats[i].coach < 'Q' || member.book[bookingNum].trains.seats[i].coach > 'Z');

			int repeat = 0;
			// Seat Number
			do {
				printf("[%d] Enter Seat Number (Example: 01A): ", i + 1);
				scanf(" %s", member.book[bookingNum].trains.seats[i].seatNumber);
				rewind(stdin);

				// Upper Case
				if (isalpha(member.book[bookingNum].trains.seats[i].seatNumber[2]))
					member.book[bookingNum].trains.seats[i].seatNumber[2] = toupper(member.book[bookingNum].trains.seats[i].seatNumber[2]);

				// View seat
				if (strcmp(member.book[bookingNum].trains.seats[i].seatNumber, "0") == 0 && found != 1) {
					found = 1;
					displaySeat(member.book[bookingNum].trains.trainID);
					continue;
				}

				repeat = 0;
				// check if repeat seat number with previous seats
				for (int d = 0; d < i; d++) {
					if (strcmp(member.book[bookingNum].trains.seats[d].seatNumber, member.book[bookingNum].trains.seats[i].seatNumber) == 0 &&
						member.book[bookingNum].trains.seats[d].coach == member.book[bookingNum].trains.seats[i].coach) {
						repeat = 1;
						printf("Repeated seat number!\n\n");
						break;
					}
				}

			} while (!(isdigit(member.book[bookingNum].trains.seats[i].seatNumber[0]) &&
				isdigit(member.book[bookingNum].trains.seats[i].seatNumber[1]) &&
				isalpha(member.book[bookingNum].trains.seats[i].seatNumber[2])) || repeat == 1);

			// check if repeat seat number with booked seats
			bool seatAvailability = seat(bookingNum, i, 0);
			if (seatAvailability) {
				break;
			}
			else {
				printf("\nSeat at %s, Coach %c has been booked.\nEnter again!\n", member.book[bookingNum].trains.seats[i].seatNumber, member.book[bookingNum].trains.seats[i].coach);
				continue;
			}

		} while (1);
	}

	// calculate amount
	printf("\nTotal amount (RM%.2f * %d pax): RM%.2f\n", member.book[bookingNum].amount, member.book[bookingNum].quantity, member.book[bookingNum].amount * member.book[bookingNum].quantity);
	member.book[bookingNum].amount *= member.book[bookingNum].quantity;

	// choose payment method
	paymentMethod(bookingNum);

	// Booking Status
	strcpy(member.book[bookingNum].ticketStatus, "Booked");

	do {
		printf("\nConfirm Booking (Y/N): ");
		scanf(" %c", &confirm);
		rewind(stdin);
		// Confirmed Booking
		if (confirm == 'Y' || confirm == 'y') {
			bool seatAvailability = seat(bookingNum, 0, 1);
			fwrite(&member.backMemberID, sizeof(int), 1, fp);
			fwrite(&member.book[bookingNum], sizeof(Booking), 1, fp);
			printf("Successfully Booking\n");
			break;
		}
	} while (!(confirm == 'N' || confirm == 'n'));


	fclose(fp);

	return;
}

void searchBooking(char mode[]) {
	int backBookingID, cnt = 0;
	system("cls");

	FILE* fp;
	fp = fopen("Booking.bin", "rb");

	if (fp == NULL) {
		printf("NO Booking Record!\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return;
	}

	printf("Enter Booking ID to search: B");
	scanf(" %d", &backBookingID);

	// read all data in the file
	while (fread(&memberTemp.backMemberID, sizeof(int), 1, fp) == 1 &&
		fread(&memberTemp.book[cnt], sizeof(Booking), 1, fp) == 1) {

		// check whether booking id and member ID are correct or not
		if (memberTemp.book[cnt].bookingID == backBookingID) {

			printf("\n");
			if (strcmp(mode, "staff") == 0) for (int i = 0; i < 15; i++) printf("=");
			for (int i = 0; i < 135; i++)
				printf("=");
			printf("\n");
			if (strcmp(mode, "staff") == 0) printf("%-15s", "Member ID");
			printf("%-15s", "Train ID");
			printf("%-16s%-15s", "Seat Number", "Coach");
			printf("%-15s%-15s%-15s%-16s%-16s%-16s\n", "Payment Info", "Ticket Status", "Booking Date", "Departure Date", "Quantity", "Amount");
			if (strcmp(mode, "staff") == 0) for (int i = 0; i < 15; i++) printf("=");
			for (int i = 0; i < 135; i++)
				printf("=");
			printf("\n");

			if (strcmp(mode, "staff") == 0) printf("\n%c%-14d", MEMBER_FRONT_ID, memberTemp.backMemberID);

			printf("%-15d", memberTemp.book[cnt].trains.trainID);

			// seat and coach based on quantity
			// seat
			for (int i = 0; i < memberTemp.book[cnt].quantity; i++) {
				if (i < 3) {
					if (memberTemp.book[cnt].quantity >= 3) {
						if (i != 2) {
							printf("%s, ", memberTemp.book[cnt].trains.seats[i].seatNumber);
						}
						else printf("%-5s", memberTemp.book[cnt].trains.seats[i].seatNumber); // 15 - 5 - 5 = 5
					}
					else {
						switch (memberTemp.book[cnt].quantity)
						{
						case 1:
							printf("%-15s", memberTemp.book[cnt].trains.seats[i].seatNumber); // just 1 seat number
							break;
						case 2:
							if (i == 0) {
								printf("%s, ", memberTemp.book[cnt].trains.seats[i].seatNumber);
							}
							else
								printf("%-10s", memberTemp.book[cnt].trains.seats[i].seatNumber); // 15 - 5 = 10
							break;
						}
					}
				}
				else break;
			}
			// coach
			for (int i = 0; i < memberTemp.book[cnt].quantity; i++) {
				if (i < 3) {
					if (memberTemp.book[cnt].quantity >= 3) {
						if (i != 2) {
							printf("%c, ", memberTemp.book[cnt].trains.seats[i].coach);
						}
						else printf("%-9c", memberTemp.book[cnt].trains.seats[i].coach); // 15 - 3 - 3 = 9
					}
					else {
						switch (memberTemp.book[cnt].quantity) {
						case 1:
							printf("%-15c", memberTemp.book[cnt].trains.seats[i].coach); // just 1 coach
							break;
						case 2:
							if (i == 0) {
								printf("%c, ", memberTemp.book[cnt].trains.seats[i].coach);
							}
							else
								printf("%-12c", memberTemp.book[cnt].trains.seats[i].coach); // 15 - 3 = 12
							break;
						}
					}

				}
				else break;
			}


			printf("%-15s%-15s", memberTemp.book[cnt].paymentInfo,
				memberTemp.book[cnt].ticketStatus);
			printf("%02d/%02d/%04d     %02d/%02d/%04d      ", memberTemp.book[cnt].bookingDate.day, memberTemp.book[cnt].bookingDate.month,
				memberTemp.book[cnt].bookingDate.year, memberTemp.book[cnt].trains.departureDate.day, memberTemp.book[cnt].trains.departureDate.month,
				memberTemp.book[cnt].trains.departureDate.year);
			printf("%-16d%-16.2f\n", memberTemp.book[cnt].quantity, memberTemp.book[cnt].amount);


			// 4 - 6
			if (memberTemp.book[cnt].quantity > 3) {
				printf("%15s", "");
				// seat
				for (int i = 3; i < memberTemp.book[cnt].quantity; i++) {
					if (i >= 3 && i < 6) {
						if (memberTemp.book[cnt].quantity >= 6) {
							if (i != 5) {
								printf("%-3s, ", memberTemp.book[cnt].trains.seats[i].seatNumber);
							}
							else printf("%-5s", memberTemp.book[cnt].trains.seats[i].seatNumber);
						}
						else {
							switch (memberTemp.book[cnt].quantity) {
							case 4:
								printf("%-15s", memberTemp.book[cnt].trains.seats[i].seatNumber);
								break;
							case 5:
								if (i == 3) {
									printf("%s, ", memberTemp.book[cnt].trains.seats[i].seatNumber);
								}
								else
									printf("%-10s", memberTemp.book[cnt].trains.seats[i].seatNumber);
								break;
							}
						}
					}
					else break;
				}
				// coach
				for (int i = 3; i < memberTemp.book[cnt].quantity; i++) {
					if (i >= 3 && i < 6) {
						if (memberTemp.book[cnt].quantity >= 6) {
							if (i != 5) {
								printf("%c, ", memberTemp.book[cnt].trains.seats[i].coach);
							}
							else printf("%-9c", memberTemp.book[cnt].trains.seats[i].coach);
						}
						else {
							switch (memberTemp.book[cnt].quantity) {
							case 4:
								printf("%-15c", memberTemp.book[cnt].trains.seats[i].coach);
								break;
							case 5:
								if (i == 3) {
									printf("%c, ", memberTemp.book[cnt].trains.seats[i].coach);
								}
								else
									printf("%-12c", memberTemp.book[cnt].trains.seats[i].coach);
								break;
							}
						}
					}
					else break;
				}
				printf("\n");
			}

			// 7-9
			if (memberTemp.book[cnt].quantity > 6 && memberTemp.book[cnt].quantity <= 9) {
				printf("%15s", "");
				// seat
				for (int i = 6; i < memberTemp.book[cnt].quantity; i++) {
					if (i >= 6 && i < 9) {
						if (memberTemp.book[cnt].quantity >= 9) {
							if (i != 8) {
								printf("%s, ", memberTemp.book[cnt].trains.seats[i].seatNumber);
							}
							else printf("%-5s", memberTemp.book[cnt].trains.seats[i].seatNumber);
						}
						else {
							switch (memberTemp.book[cnt].quantity) {
							case 7:
								printf("%-15s", memberTemp.book[cnt].trains.seats[i].seatNumber);
								break;
							case 8:
								if (i == 6) {
									printf("%s, ", memberTemp.book[cnt].trains.seats[i].seatNumber);
								}
								else
									printf("%-10s", memberTemp.book[cnt].trains.seats[i].seatNumber);
								break;
							}
						}
					}
					else break;
				}
				// coach
				for (int i = 6; i < memberTemp.book[cnt].quantity; i++) {
					if (i >= 6 && i < 9) {
						if (memberTemp.book[cnt].quantity >= 9) {
							if (i != 8) {
								printf("%c, ", memberTemp.book[cnt].trains.seats[i].coach);
							}
							else printf("%-9c", memberTemp.book[cnt].trains.seats[i].coach);
						}
						else {
							switch (memberTemp.book[cnt].quantity) {
							case 7:
								printf("%-15c", memberTemp.book[cnt].trains.seats[i].coach);
								break;
							case 8:
								if (i == 6) {
									printf("%c, ", memberTemp.book[cnt].trains.seats[i].coach);
								}
								else
									printf("%-12c", memberTemp.book[cnt].trains.seats[i].coach);
								break;
							}
						}
					}
					else break;
				}
				printf("\n");
			}

			// 10
			if (memberTemp.book[cnt].quantity == 10) {
				printf("%15s", "");
				printf("%-15s", memberTemp.book[cnt].trains.seats[9].seatNumber);
				printf("%-15c", memberTemp.book[cnt].trains.seats[9].coach);
			}

			printf("Enter Any Key to continue...");
			rewind(stdin);
			while (getc(stdin) != '\n');
			fclose(fp);
			return;
		}
		cnt++;

	}
	printf("Ticket not found\n");
	printf("Enter Any Key to continue...");
	rewind(stdin);
	while (getc(stdin) != '\n');

	fclose(fp);
	return;
}

void modifyBooking() {
	int selection, backBookingID, cnt = 0, found = 0, oriQuantity;
	bool valid = false;

	FILE* fp = fopen("Booking.bin", "rb");
	FILE* fp2 = fopen("Booking_Modify.bin", "wb");

	system("cls");

	if (fp == NULL || fp2 == NULL) {
		printf("NO booking record!\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return;
	}

	// display all data of booking
	displayBooking(1, "member");

	printf("\n\nEnter Booking ID to modify: B");
	scanf(" %d", &backBookingID);

	// read all data in the file
	while (fread(&memberTemp.backMemberID, sizeof(int), 1, fp) == 1 &&
		fread(&memberTemp.book[cnt], sizeof(Booking), 1, fp) == 1) {

		// check whether booking id and member ID are correct or not
		if (memberTemp.book[cnt].bookingID == backBookingID &&
			member.backMemberID == memberTemp.backMemberID) {
			found = 1;
			// loop for modify more data
			do {
				// loop for validation
				do {
					printf("\nSeat number & Coach ---------- 1\n");
					printf("Quantity --------------------- 2\n");
					printf("Cancel modify ---------------- 3\n");
					printf("\nSelect a field to modify: ");
					scanf(" %d", &selection);
					rewind(stdin);
				} while (!(selection == 1 || selection == 2 || selection == 3));

				switch (selection) {
				case 1:
					// select seat
					printf("\n             Select Seat            \n");
					printf("<<< Enter 0 to veiw available seat >>>\n");
					printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
					for (int i = 0; i < memberTemp.book[cnt].quantity; i++) { // based on quantity
						do {
							printf("\n");
							int once = 0;
							// Coach
							do {
								printf("[%d] Enter coach: ", i + 1);
								scanf(" %c", &memberTemp.book[cnt].trains.seats[i].coach);
								rewind(stdin);

								// Upper Case
								if (memberTemp.book[cnt].trains.seats[i].coach >= 'q' && memberTemp.book[cnt].trains.seats[i].coach <= 'z')
									memberTemp.book[cnt].trains.seats[i].coach = toupper(memberTemp.book[cnt].trains.seats[i].coach);

								// View seat
								if (memberTemp.book[cnt].trains.seats[i].coach == '0' && once != 1) {
									once = 1;
									displaySeat(memberTemp.book[cnt].trains.trainID);
								}
							} while (!(memberTemp.book[cnt].trains.seats[i].coach >= 'Q' && memberTemp.book[cnt].trains.seats[i].coach <= 'Z'));

							int repeat = 0;
							// Seat Number
							do {
								printf("[%d] Enter Seat Number (Example: 01A): ", i + 1);
								scanf(" %s", memberTemp.book[cnt].trains.seats[i].seatNumber);
								rewind(stdin);

								// Upper Case
								if (isalpha(memberTemp.book[cnt].trains.seats[i].seatNumber[2]))
									memberTemp.book[cnt].trains.seats[i].seatNumber[2] = toupper(memberTemp.book[cnt].trains.seats[i].seatNumber[2]);

								// View seat
								if (strcmp(memberTemp.book[cnt].trains.seats[i].seatNumber, "0") == 0 && once != 1) {
									once = 1;
									displaySeat(memberTemp.book[cnt].trains.trainID);
									continue;
								}

								repeat = 0;
								// check if repeat seat number with previous seats
								for (int d = 0; d < i; d++) {
									if (strcmp(memberTemp.book[cnt].trains.seats[d].seatNumber, memberTemp.book[cnt].trains.seats[i].seatNumber) == 0 &&
										memberTemp.book[cnt].trains.seats[d].coach == memberTemp.book[cnt].trains.seats[i].coach) {
										repeat = 1;
										printf("Repeated seat number!\n\n");
										break;
									}
								}

							} while (!(isdigit(memberTemp.book[cnt].trains.seats[i].seatNumber[0]) &&
								isdigit(memberTemp.book[cnt].trains.seats[i].seatNumber[1]) &&
								isalpha(memberTemp.book[cnt].trains.seats[i].seatNumber[2])) || repeat == 1);

							valid = false;
							// check if repeat seat number with booked seats
							modifySeat(0, cnt, i, &valid);
							if (valid) {
								break;
							}
							else {
								printf("\nSeat at %s, Coach %c has been booked.\nEnter again!\n", member.book[cnt].trains.seats[i].seatNumber, member.book[cnt].trains.seats[i].coach);
								continue;
							}

						} while (1);
					}
					break;
				case 2:

					oriQuantity = memberTemp.book[cnt].quantity;
					do {
						printf("\nEnter quantity of booking: ");
						scanf(" %d", &memberTemp.book[cnt].quantity);
						rewind(stdin);
						if (memberTemp.book[cnt].quantity >= 1 && memberTemp.book[cnt].quantity <= 10) {
							break;
						}
						else {
							if (memberTemp.book[cnt].quantity > 10)
								printf("Invalid! Maximum quantity is 10\n\n");

							else
								printf("Invalid quantity of booking\n\n");
						}
					} while (1);

					if (memberTemp.book[cnt].quantity > oriQuantity) {

						// select seat
						printf("\n        Select Additional Seat      \n");
						printf("<<< Enter 0 to veiw available seat >>>\n");
						printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
						for (int i = oriQuantity; i < memberTemp.book[cnt].quantity; i++) { // based on quantity
							do {
								printf("\n");
								int once = 0;
								// Coach
								do {
									printf("[%d] Enter coach: ", i + 1);
									scanf(" %c", &memberTemp.book[cnt].trains.seats[i].coach);
									rewind(stdin);

									// Upper Case
									if (memberTemp.book[cnt].trains.seats[i].coach >= 'q' && memberTemp.book[cnt].trains.seats[i].coach <= 'z')
										memberTemp.book[cnt].trains.seats[i].coach = toupper(memberTemp.book[cnt].trains.seats[i].coach);

									// View seat
									if (memberTemp.book[cnt].trains.seats[i].coach == '0' && once != 1) {
										once = 1;
										displaySeat(memberTemp.book[cnt].trains.trainID);
									}
								} while (!(memberTemp.book[cnt].trains.seats[i].coach >= 'Q' && memberTemp.book[cnt].trains.seats[i].coach <= 'Z'));

								int repeat = 0;
								// Seat Number
								do {
									printf("[%d] Enter Seat Number (Example: 01A): ", i + 1);
									scanf(" %s", memberTemp.book[cnt].trains.seats[i].seatNumber);
									rewind(stdin);

									// Upper Case
									if (isalpha(memberTemp.book[cnt].trains.seats[i].seatNumber[2]))
										memberTemp.book[cnt].trains.seats[i].seatNumber[2] = toupper(memberTemp.book[cnt].trains.seats[i].seatNumber[2]);

									// View seat
									if (strcmp(memberTemp.book[cnt].trains.seats[i].seatNumber, "0") == 0 && once != 1) {
										once = 1;
										displaySeat(memberTemp.book[cnt].trains.trainID);
										continue;
									}

									repeat = 0;
									// check if repeat seat number with previous seats
									for (int d = 0; d < i; d++) {
										if (strcmp(memberTemp.book[cnt].trains.seats[d].seatNumber, memberTemp.book[cnt].trains.seats[i].seatNumber) == 0 &&
											memberTemp.book[cnt].trains.seats[d].coach == memberTemp.book[cnt].trains.seats[i].coach) {
											repeat = 1;
											printf("Repeated seat number!\n\n");
											break;
										}
									}

								} while (!(isdigit(memberTemp.book[cnt].trains.seats[i].seatNumber[0]) &&
									isdigit(memberTemp.book[cnt].trains.seats[i].seatNumber[1]) &&
									isalpha(memberTemp.book[cnt].trains.seats[i].seatNumber[2])) || repeat == 1);

								double price;
								// update quantity
								bool valid = schedulingData(memberTemp.book[cnt].trains.trainID, "validate", cnt, &price);
								memberTemp.book[cnt].amount = price * memberTemp.book[cnt].quantity;

								valid = false;
								// check if repeat seat number with booked seats
								modifySeat(0, cnt, i, &valid);
								if (valid) {
									break;
								}
								else {
									printf("\nSeat at %s, Coach %c has been booked.\nEnter again!\n", member.book[cnt].trains.seats[i].seatNumber, member.book[cnt].trains.seats[i].coach);
									continue;
								}

							} while (1);
						}
					}
					else if (memberTemp.book[cnt].quantity < oriQuantity) {
						printf("\nThe quantity of booking can't reduce!\n");
						break;
					}
					else {
						printf("\nThe quantity doesn't has any change!\n");
						break;
					}
					break;

				default:
					break;
				}

				do {
					printf("\n[1] Confirm modify\n");
					printf("[2] Cancel modify\n");
					printf("Select number: ");
					scanf(" %d", &selection);
					rewind(stdin);
				} while (!(selection == 1 || selection == 2));

				if (selection == 1) {
					modifySeat(1, cnt, memberTemp.book[cnt].quantity, &valid);
					break;
				}
				else return;

			} while (1);
			// write modified data into the temporary file
			fwrite(&memberTemp.backMemberID, sizeof(int), 1, fp2);
			fwrite(&memberTemp.book[cnt], sizeof(Booking), 1, fp2);
		}
		else {
			// write the original data into temporary file
			fwrite(&memberTemp.backMemberID, sizeof(int), 1, fp2);
			fwrite(&memberTemp.book[cnt], sizeof(Booking), 1, fp2);
		}

		cnt++;

	}

	// rewrite to the original file
	if (found == 1) {
		fclose(fp);
		fclose(fp2);

		FILE* fpt = fopen("Booking_Modify.bin", "rb");
		FILE* fpt2 = fopen("Booking.bin", "wb");

		if (fpt == NULL || fpt2 == NULL) {
			printf("Unable to open file");
			return;
		}

		cnt = 0;

		// read the temporary file data
		while (fread(&memberTemp.backMemberID, sizeof(int), 1, fp) == 1 &&
			fread(&memberTemp.book[cnt], sizeof(Booking), 1, fpt) == 1) {
			// write it into original file
			fwrite(&memberTemp.backMemberID, sizeof(int), 1, fpt2);
			fwrite(&memberTemp.book[cnt], sizeof(Booking), 1, fpt2);
			cnt++;
		}

		fclose(fpt);
		fclose(fpt2);
	}
	else printf("Invalid Booking ID\n");
	printf("Enter Any Key to continue...");
	rewind(stdin);
	while (getc(stdin) != '\n');
	return;
}

void displayBooking(int i, char mode[]) {
	int c = 0;
	FILE* fp;
	fp = fopen("Booking.bin", "rb");

	system("cls");

	if (fp == NULL) {
		printf("NO booking record!\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return;
	}

	// read data and display 
	while (fread(&memberTemp.backMemberID, sizeof(int), 1, fp) == 1 &&
		fread(&memberTemp.book[c], sizeof(Booking), 1, fp) == 1) {

		if (member.backMemberID != memberTemp.backMemberID &&
			strcmp(mode, "member") == 0) continue;

		// display header
		if (c == 0) {
			if (strcmp(mode, "member") == 0)
				printf("Member ID: M%d\n\n", memberTemp.backMemberID);

			if (strcmp(mode, "staff") == 0) for (int i = 0; i < 15; i++) printf("=");
			for (int i = 0; i < 150; i++)
				printf("=");
			printf("\n");
			if (strcmp(mode, "staff") == 0) printf("%-15s", "Member ID");
			printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-16s%-16s%-16s\n", "Booking ID", "Train ID", "Seat Number", "Coach", "Payment Info", "Ticket Status", "Booking Date", "Departure Date", "Quantity", "Amount");
			if (strcmp(mode, "staff") == 0) for (int i = 0; i < 15; i++) printf("=");
			for (int i = 0; i < 150; i++)
				printf("=");
			printf("\n");
		}

		printf("\n");

		// display data
		if (strcmp(mode, "staff") == 0) printf("%c%-14d", MEMBER_FRONT_ID, memberTemp.backMemberID);
		printf("%c%-14d%c%-14d", BOOKING_FRONT_ID, memberTemp.book[c].bookingID, TRAIN_FRONT_ID, memberTemp.book[c].trains.trainID);

		// seat and coach based on quantity
		// seat
		for (int i = 0; i < memberTemp.book[c].quantity; i++) {
			if (i < 3) {
				if (memberTemp.book[c].quantity >= 3) {
					if (i != 2) {
						printf("%s, ", memberTemp.book[c].trains.seats[i].seatNumber);
					}
					else printf("%-5s", memberTemp.book[c].trains.seats[i].seatNumber); // 15 - 5 - 5 = 5
				}
				else {
					switch (memberTemp.book[c].quantity)
					{
					case 1:
						printf("%-15s", memberTemp.book[c].trains.seats[i].seatNumber); // just 1 seat number
						break;
					case 2:
						if (i == 0) {
							printf("%s, ", memberTemp.book[c].trains.seats[i].seatNumber);
						}
						else
							printf("%-10s", memberTemp.book[c].trains.seats[i].seatNumber); // 15 - 5 = 10
						break;
					}
				}
			}
			else break;
		}
		// coach
		for (int i = 0; i < memberTemp.book[c].quantity; i++) {
			if (i < 3) {
				if (memberTemp.book[c].quantity >= 3) {
					if (i != 2) {
						printf("%c, ", memberTemp.book[c].trains.seats[i].coach);
					}
					else printf("%-9c", memberTemp.book[c].trains.seats[i].coach); // 15 - 3 - 3 = 9
				}
				else {
					switch (memberTemp.book[c].quantity) {
					case 1:
						printf("%-15c", memberTemp.book[c].trains.seats[i].coach); // just 1 coach
						break;
					case 2:
						if (i == 0) {
							printf("%c, ", memberTemp.book[c].trains.seats[i].coach);
						}
						else
							printf("%-12c", memberTemp.book[c].trains.seats[i].coach); // 15 - 3 = 12
						break;
					}
				}

			}
			else break;
		}

		printf("%-15s%-15s", memberTemp.book[c].paymentInfo,
			memberTemp.book[c].ticketStatus);
		printf("%02d/%02d/%04d     %02d/%02d/%04d      ", memberTemp.book[c].bookingDate.day, memberTemp.book[c].bookingDate.month,
			memberTemp.book[c].bookingDate.year, memberTemp.book[c].trains.departureDate.day, memberTemp.book[c].trains.departureDate.month,
			memberTemp.book[c].trains.departureDate.year);
		printf("%-16d%-16.2f\n", memberTemp.book[c].quantity, memberTemp.book[c].amount);

		// 4-7
		if (memberTemp.book[c].quantity > 3) {
			if (strcmp(mode, "staff") == 0) printf("%15s", "");
			printf("%30s", "");
			// seat
			for (int i = 3; i < memberTemp.book[c].quantity; i++) {
				if (i >= 3 && i < 6) {
					if (memberTemp.book[c].quantity >= 6) {
						if (i != 5) {
							printf("%-3s, ", memberTemp.book[c].trains.seats[i].seatNumber);
						}
						else printf("%-5s", memberTemp.book[c].trains.seats[i].seatNumber);
					}
					else {
						switch (memberTemp.book[c].quantity) {
						case 4:
							printf("%-15s", memberTemp.book[c].trains.seats[i].seatNumber);
							break;
						case 5:
							if (i == 3) {
								printf("%s, ", memberTemp.book[c].trains.seats[i].seatNumber);
							}
							else
								printf("%-10s", memberTemp.book[c].trains.seats[i].seatNumber);
							break;
						}
					}
				}
				else break;
			}
			// coach
			for (int i = 3; i < memberTemp.book[c].quantity; i++) {
				if (i >= 3 && i < 6) {
					if (memberTemp.book[c].quantity >= 6) {
						if (i != 5) {
							printf("%c, ", memberTemp.book[c].trains.seats[i].coach);
						}
						else printf("%-9c", memberTemp.book[c].trains.seats[i].coach);
					}
					else {
						switch (memberTemp.book[c].quantity) {
						case 4:
							printf("%-15c", memberTemp.book[c].trains.seats[i].coach);
							break;
						case 5:
							if (i == 3) {
								printf("%c, ", memberTemp.book[c].trains.seats[i].coach);
							}
							else
								printf("%-12c", memberTemp.book[c].trains.seats[i].coach);
							break;
						}
					}
				}
				else break;
			}
			printf("\n");
		}

		// 7-9
		if (memberTemp.book[c].quantity > 6 && memberTemp.book[c].quantity <= 9) {
			if (strcmp(mode, "staff") == 0) printf("%15s", "");
			printf("%15s", "");
			// seat
			for (int i = 6; i < memberTemp.book[c].quantity; i++) {
				if (i >= 6 && i < 9) {
					if (memberTemp.book[c].quantity >= 9) {
						if (i != 8) {
							printf("%s, ", memberTemp.book[c].trains.seats[i].seatNumber);
						}
						else printf("%-5s", memberTemp.book[c].trains.seats[i].seatNumber);
					}
					else {
						switch (memberTemp.book[c].quantity) {
						case 7:
							printf("%-15s", memberTemp.book[c].trains.seats[i].seatNumber);
							break;
						case 8:
							if (i == 6) {
								printf("%s, ", memberTemp.book[c].trains.seats[i].seatNumber);
							}
							else
								printf("%-10s", memberTemp.book[c].trains.seats[i].seatNumber);
							break;
						}
					}
				}
				else break;
			}
			// coach
			for (int i = 6; i < memberTemp.book[c].quantity; i++) {
				if (i >= 6 && i < 9) {
					if (memberTemp.book[c].quantity >= 9) {
						if (i != 8) {
							printf("%c, ", memberTemp.book[c].trains.seats[i].coach);
						}
						else printf("%-9c", memberTemp.book[c].trains.seats[i].coach);
					}
					else {
						switch (memberTemp.book[c].quantity) {
						case 7:
							printf("%-15c", memberTemp.book[c].trains.seats[i].coach);
							break;
						case 8:
							if (i == 6) {
								printf("%c, ", memberTemp.book[c].trains.seats[i].coach);
							}
							else
								printf("%-12c", memberTemp.book[c].trains.seats[i].coach);
							break;
						}
					}
				}
				else break;
			}
			printf("\n");
		}

		// 10
		if (memberTemp.book[c].quantity == 10) {
			if (strcmp(mode, "staff") == 0) printf("%15s", "");
			printf("%30s", "");
			printf("%-15s", memberTemp.book[c].trains.seats[9].seatNumber);
			printf("%-15c", memberTemp.book[c].trains.seats[9].coach);
		}
		c++;
	}


	if (c == 0) printf("Record not found!\n");

	if (i != 1) {
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
	}
	fclose(fp);
	return;
}

void cancelBooking() {
	int backBookingID;
	char confirm;
	int cnt = 0, found = 0;

	FILE* fp = fopen("Booking.bin", "rb");
	FILE* fp2 = fopen("Booking_Modify.bin", "wb");

	system("cls");

	if (fp == NULL || fp2 == NULL) {
		printf("NO booking record!\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return;
	}

	displayBooking(1, "member");

	printf("\n\nEnter Booking ID to cancel: B");
	scanf(" %d", &backBookingID);

	// read all data in the file
	while (fread(&memberTemp.backMemberID, sizeof(int), 1, fp) == 1 &&
		fread(&memberTemp.book[cnt], sizeof(Booking), 1, fp) == 1) {

		// check whether booking id correct or not
		if (memberTemp.book[cnt].bookingID == backBookingID &&
			member.backMemberID == memberTemp.backMemberID) {
			found = 1;

			do {
				printf("\nConfirm cancel(Y/N): ");
				scanf(" %c", &confirm);
				rewind(stdin);
			} while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n');

			if (confirm == 'N' || confirm == 'n') {
				return;
			}

			// write to temporary file
			strcpy(memberTemp.book[cnt].ticketStatus, "Canceled");
			fwrite(&memberTemp.backMemberID, sizeof(int), 1, fp2);
			fwrite(&memberTemp.book[cnt], sizeof(Booking), 1, fp2);
		}
		else {
			// write the original data into temporary file
			fwrite(&memberTemp.backMemberID, sizeof(int), 1, fp2);
			fwrite(&memberTemp.book[cnt], sizeof(Booking), 1, fp2);
		}

		cnt++;
	}

	fclose(fp);
	fclose(fp2);

	if (found == 1) {


		FILE* fpt = fopen("Booking_Modify.bin", "rb");
		FILE* fpt2 = fopen("Booking.bin", "wb");

		if (fpt == NULL || fpt2 == NULL) {
			printf("Unable to open file");
			return;
		}

		cnt = 0;

		// read the temporary file data
		while (fread(&memberTemp.backMemberID, sizeof(int), 1, fpt) == 1 &&
			fread(&memberTemp.book[cnt], sizeof(Booking), 1, fpt) == 1) {
			// write it into original file
			fwrite(&memberTemp.backMemberID, sizeof(int), 1, fpt2);
			fwrite(&memberTemp.book[cnt], sizeof(Booking), 1, fpt2);
			cnt++;
		}
		printf("Successfully cancel\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');

		fclose(fpt);
		fclose(fpt2);
	}
	else printf("Invalid Booking ID\n");
	printf("Enter Any Key to continue...");
	rewind(stdin);
	while (getc(stdin) != '\n');
	return;
}

void deleteBooking() {
	int backBookingID;
	int cnt = 0, found = 0;
	char confirm;

	FILE* fp = fopen("Booking.bin", "rb");
	FILE* fp2 = fopen("Booking_Modify.bin", "wb");

	system("cls");

	if (fp == NULL || fp2 == NULL) {
		printf("NO booking record!\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return;
	}

	displayBooking(1, "staff");

	printf("\n\nEnter Booking ID to delete: B");
	scanf(" %d", &backBookingID);

	// read all data in the file
	while (fread(&memberTemp.backMemberID, sizeof(int), 1, fp) == 1 &&
		fread(&memberTemp.book[cnt], sizeof(Booking), 1, fp) == 1) {

		// check whether booking id correct or not
		if (memberTemp.book[cnt].bookingID == backBookingID) {
			found = 1;

			do {
				printf("\nConfirm delete(Y/N): ");
				scanf(" %c", &confirm);
				rewind(stdin);
			} while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n');

			if (confirm == 'N' || confirm == 'n') {
				return;
			}
		}
		else {
			// write the original data into temporary file
			fwrite(&memberTemp.backMemberID, sizeof(int), 1, fp2);
			fwrite(&memberTemp.book[cnt], sizeof(Booking), 1, fp2);
		}

		cnt++;
	}

	fclose(fp);
	fclose(fp2);

	if (found == 1) {

		// if just 1 record
		if (cnt == 1) {
			remove("Booking.bin");
			return;
		}

		FILE* fpt = fopen("Booking_Modify.bin", "rb");
		FILE* fpt2 = fopen("Booking.bin", "wb");

		if (fpt == NULL || fpt2 == NULL) {
			printf("Unable to open file");
			return;
		}

		cnt = 0;

		// read the temporary file data
		while (fread(&memberTemp.backMemberID, sizeof(int), 1, fpt) == 1 &&
			fread(&memberTemp.book[cnt], sizeof(Booking), 1, fpt) == 1) {
			// write it into original file
			fwrite(&memberTemp.backMemberID, sizeof(int), 1, fpt2);
			fwrite(&memberTemp.book[cnt], sizeof(Booking), 1, fpt2);
			cnt++;
		}
		printf("Successfully delete\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');

		fclose(fpt);
		fclose(fpt2);
		return;
	}
	else printf("Invalid Booking ID\n");
	printf("Enter Any Key to continue...");
	rewind(stdin);
	while (getc(stdin) != '\n');
	return;
}

void summaryReport() {
	int selection;
	int totalBookings = 0;
	double totalRevenue = 0;
	int creditCardCount = 0, cashCount = 0, debitCardCount = 0, bankTransferCount = 0, touchNGoCount = 0;
	int bookedCount = 0, canceledCount = 0;

	FILE* fp = fopen("Booking.bin", "rb");

	system("cls");

	if (fp == NULL) {
		printf("NO booking record!\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return;
	}

	while (fread(&memberTemp.backMemberID, sizeof(int), 1, fp) == 1 &&
		fread(&memberTemp.book[totalBookings], sizeof(Booking), 1, fp) == 1) {

		// count total revenue generated
		totalRevenue += memberTemp.book[totalBookings].amount;

		// count total number of each payment method
		if (strcmp(memberTemp.book[totalBookings].paymentInfo, "Credit Card") == 0) {
			creditCardCount++;
		}
		else if (strcmp(memberTemp.book[totalBookings].paymentInfo, "Cash") == 0) {
			cashCount++;
		}
		else if (strcmp(memberTemp.book[totalBookings].paymentInfo, "Debit Card") == 0) {
			debitCardCount++;
		}
		else if (strcmp(memberTemp.book[totalBookings].paymentInfo, "Bank Transfer") == 0) {
			bankTransferCount++;
		}
		else if (strcmp(memberTemp.book[totalBookings].paymentInfo, "Touch n Go") == 0) {
			touchNGoCount++;
		}

		// count book status
		if (strcmp(memberTemp.book[totalBookings].ticketStatus, "Booked") == 0) {
			bookedCount++;
		}
		else if (strcmp(memberTemp.book[totalBookings].ticketStatus, "Canceled") == 0) {
			canceledCount++;
		}

		// count total number of bookings
		totalBookings++;
	}

	// Average booking amount
	double averageAmount = totalRevenue / totalBookings;

	fclose(fp);

	// Display the report
	system("cls");
	printf(" Booking Summary Report\n");
	printf("========================\n\n");
	printf("Total number of bookings: %d\n", totalBookings);
	printf("Total revenue: RM%.2f\n", totalRevenue);
	printf("Average booking amount: RM%.2f\n", averageAmount);
	printf("Total Booked Booking: %d\n", bookedCount);
	printf("Total Canceled Booking: %d\n", canceledCount);
	printf("Number of Payment Method:\n");
	printf(" - Credit Card: %d\n", creditCardCount);
	printf(" - Cash: %d\n", cashCount);
	printf(" - Debit Card: %d\n", debitCardCount);
	printf(" - Bank Transfer: %d\n", bankTransferCount);
	printf(" - Touch n Go: %d\n", touchNGoCount);

	do {
		printf("\n[1] Generate Text File Report\n");
		printf("[2] Back\n");
		printf("Enter number: ");
		scanf(" %d", &selection);
		rewind(stdin);
	} while (!(selection == 1 || selection == 2));

	if (selection == 2) return;

	// write into file
	FILE* fp2 = fopen("summaryBookingReport.txt", "w");

	fprintf(fp2, "Booking Summary Report:\n");
	printf("=======================\n\n");
	fprintf(fp2, "Total number of bookings: %d\n", totalBookings);
	fprintf(fp2, "Total revenue generated: RM%.2f\n", totalRevenue);
	fprintf(fp2, "Average booking amount: RM%.2f\n", averageAmount);
	fprintf(fp2, "Total Booked Booking: %d\n", bookedCount);
	fprintf(fp2, "Total Canceled Booking: %d\n", canceledCount);
	fprintf(fp2, "Number of Payment Method:\n");
	fprintf(fp2, " - Credit Card: %d\n", creditCardCount);
	fprintf(fp2, " - Cash: %d\n", cashCount);
	fprintf(fp2, " - Debit Card: %d\n", debitCardCount);
	fprintf(fp2, " - Bank Transfer: %d\n", bankTransferCount);
	fprintf(fp2, " - Touch n Go: %d\n", touchNGoCount);


	printf("\nSuccessfuly generate a Text File Report: summaryBookingReport.txt\n");

	fclose(fp2);
	printf("Enter Any Key to continue...");
	rewind(stdin);
	while (getc(stdin) != '\n');
	return;
}

bool schedulingData(int trainID, char purpose[], int bookingNum, double* price) {

	FILE* fptr = fopen("train_schedule.txt", "r");

	if (fptr == NULL) {
		printf("No scheduling record\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return false;
	}

	if (strcmp(purpose, "display") == 0) {
		printf("===========================================================================================================\n");
		printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
		printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
		printf("===========================================================================================================\n");
	}


	while (!feof(fptr)) {
		fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice);

		if (strcmp(purpose, "validate") == 0 && trainID == schedule.trainID) {
			member.book[bookingNum].trains.departureDate.day = schedule.arrivalDate.day;
			member.book[bookingNum].trains.departureDate.month = schedule.arrivalDate.month;
			member.book[bookingNum].trains.departureDate.year = schedule.arrivalDate.year;
			member.book[bookingNum].amount = schedule.ticketPrice;
			*price = schedule.ticketPrice;
			return true;
		}
		if (strcmp(purpose, "display") == 0) {
			printf("%c%d\t    %-13s%-14s%02d/%02d/%04d   %02d/%02d/%04d\t   %02d:%02d\t%02d:%02d\t    %-9d %.2f\n",
				TRAIN_FRONT_ID,
				schedule.trainID, schedule.departureStation, schedule.arrivalStation,
				schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
				schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
				schedule.departureTime.hour, schedule.departureTime.min,
				schedule.arrivalTime.hour, schedule.arrivalTime.min,
				schedule.availableSeats, schedule.ticketPrice);
		}
	}
	fclose(fptr);
	return false;
}

bool loginMember(int* ID) {
	int backMemberID, pass, found = 0;
	char contn = ' ', frontMemberID;
	char name[30], gender, IC[15], phone[15], passRecovery[30];

	// open member text file for reading
	FILE* fp;
	fp = fopen("member.txt", "r");

	if (fp == NULL) {
		printf("Member record not found!\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return false;
	}

	do {
		system("cls");
		bookingLogo();
		do {
			printf("Enter your Member ID: M");
			scanf(" %d", &backMemberID);
			rewind(stdin);
		} while (!(backMemberID > 1000 && backMemberID < 10000));

		printf("Enter your password");
		if (found != 1) {
			printf(" (Enter 0 if forgot password): ");
		}
		else printf(": ");
		scanf("%d", &pass);
		rewind(stdin);

		if (pass == 0) {
			if (found == 1) {
				printf("Request password too frequent, please retry later\n\n");
				continue;
			}
			found = 1;
			passwordRecoveryMember();
			printf("\n");
			continue;
		}

		// read all records
		fseek(fp, 0, SEEK_SET);
		while (!feof(fp)) {
			fscanf(fp, "%c%d | %[^|]| %d | %[^|]| %c | %[^|]| %[^\n]\n", &frontMemberID, &member.backMemberID, &name, &member.password, &passRecovery, &gender, &IC, &phone);
			// if ID and password is correct
			if (member.backMemberID == backMemberID && member.password == pass) {
				printf("Successful login!\n");
				*ID = member.backMemberID;
				printf("Enter Any Key to continue...");
				rewind(stdin);
				while (getc(stdin) != '\n');
				fclose(fp);
				return true;
			}

		}

		do {
			printf("\n*** Invalid MEMBER ID or PASSWORD ***\n");
			printf("[Y] Retry\n");
			printf("[N] Back to Menu\n");
			printf("Enter Your Selection: ");
			scanf(" %c", &contn);
			rewind(stdin);
			if (contn == 'N' || contn == 'n') {
				fclose(fp);
				return false;
			}
		} while (!(contn == 'Y' || contn == 'y'));

	} while (contn == 'Y' || contn == 'y');
	fclose(fp);
	return false;
}

bool loginStaff() {
	char contn = ' ', pass[7];
	int staffID, found = 0;

	// open staff binary file for reading
	FILE* fp;
	fp = fopen("staff.bin", "rb");

	if (fp == NULL) {
		printf("Staff record not found!\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return false;
	}

	do {
		system("cls");
		bookingLogo();
		do
		{
			printf("Enter your Staff ID: S");
			scanf(" %d", &staffID);
			rewind(stdin);
			if (!(staffID > 1000 && staffID < 10000)) {
				printf("Invalid Staff ID!\n\n");
			}
		} while (!(staffID > 1000 && staffID < 10000));


		printf("Enter your password");
		if (found != 1) {
			printf(" (Enter 0 if forgot password): ");
		}
		else printf(": ");
		scanf("%s", pass);
		rewind(stdin);

		if (strcmp(pass, "0") == 0) {
			if (found == 1) {
				printf("Request password too frequent, please retry later\n\n");
				continue;
			}
			found = 1;
			passwordRecovery(staffID);
			printf("\n");
			continue;
		}


		// read all records
		rewind(fp);
		while (fread(&staffs, sizeof(staffinfo), 1, fp) == 1) {
			if (staffID == staffs.backID && strcmp(pass, staffs.pass) == 0) {
				printf("Successful login!\n");
				printf("Enter Any Key to continue...");
				rewind(stdin);
				while (getc(stdin) != '\n');
				fclose(fp);
				return true;
			}
		}

		do {
			printf("\n*** Invalid STAFF ID or PASSWORD ***\n");
			printf("[Y] Retry\n");
			printf("[N] Back to Menu\n");
			printf("Enter Your Selection: ");
			scanf(" %c", &contn);
			rewind(stdin);
			if (contn == 'N' || contn == 'n') {
				fclose(fp);
				return false;
			}
		} while (!(contn == 'Y' || contn == 'y'));
	} while (1);
	fclose(fp);
	return false;
}

void paymentMethod(int bookingNum) {
	int method;

	printf("\n[1] Credit Card\n");
	printf("[2] Debit Card\n");
	printf("[3] Cash\n");
	printf("[4] Bank Transfer\n");
	printf("[5] Touch n Go\n");

	do {
		printf("Select payment method: ");
		scanf(" %d", &method);
		rewind(stdin);
		if (!(method == 1 || method == 2 || method == 3 || method == 4 || method == 5)) {
			printf("\n***Invalid Number***\n");
		}
	} while (!(method == 1 || method == 2 || method == 3 || method == 4 || method == 5));


	// assign value
	switch (method) {
	case 1:
		strcpy(member.book[bookingNum].paymentInfo, "Credit Card");
		break;
	case 2:
		strcpy(member.book[bookingNum].paymentInfo, "Debit Card");
		break;
	case 3:
		strcpy(member.book[bookingNum].paymentInfo, "Cash");
		break;
	case 4:
		strcpy(member.book[bookingNum].paymentInfo, "Bank Transfer");
		break;
	case 5:
		strcpy(member.book[bookingNum].paymentInfo, "Touch n Go");
		break;
	default:
		break;
	}

	return;
}


int bookingID_Num(int* id) {
	int maxID = 0, num = 0;
	FILE* fp = fopen("Booking.bin", "rb");

	if (fp == NULL) {
		*id = 1000;
		return 0;
	}

	while (fread(&memberTemp.backMemberID, sizeof(int), 1, fp) == 1 &&
		fread(&memberTemp.book[num], sizeof(Booking), 1, fp) == 1)
	{
		*id = memberTemp.book[num].bookingID;
		if (*id > maxID)
			maxID = *id;
		num++;
	}
	*id = maxID;

	if (num == 0)
		*id = 1000;

	fclose(fp);
	return num;
}

void displaySeat(int trainID) {
	FILE* fp = fopen("availableSeat.bin", "rb");
	int valid = 1;
	if (fp == NULL) {
		valid = 0;
	}

	char coach, row[3];
	char seatA[4], seatB[4], seatC[4], seatD[4];

	printf("           ._______.\n");
	printf("           | |...| |\n");
	printf("           |_|___|_|\n");
	printf("           |       |\n");
	printf("          /_________\\\n");
	for (int d = 0; d < 5; d++) { // coach
		switch (d) {
		case 0:
			coach = 'Q';
			break;
		case 1:
			coach = 'R';
			break;
		case 2:
			coach = 'X';
			break;
		case 3:
			coach = 'Y';
			break;
		case 4:
			coach = 'Z';
			break;
		}
		printf("    .---------------------.\n");
		printf("    |       Coach %c       |\n", coach);
		printf("    |      =========      |\n");
		printf("    |                     |\n");
		for (int r = 1; r <= 20; r++) { // 1 coach have 20 row, 1 row have 4 column
			// set seat number
			sprintf(seatA, "%02dA", r);
			sprintf(seatB, "%02dB", r);
			sprintf(seatC, "%02dC", r);
			sprintf(seatD, "%02dD", r);

			// read file - check the seat availability
			if (valid == 1) {
				int bookingNum = 0;
				rewind(fp);
				while (fread(&memberTemp2.book[bookingNum].trains, sizeof(TrainSchedule), 1, fp) == 1) {
					for (int count = 0; count < (sizeof(memberTemp2.book[bookingNum].trains.seats) / sizeof(memberTemp2.book[bookingNum].trains.seats[0])); count++) {
						// if train id correct
						if (trainID == memberTemp2.book[bookingNum].trains.trainID && memberTemp2.book[bookingNum].trains.seats[count].coach == coach) {
							switch (memberTemp2.book[bookingNum].trains.seats[count].seatNumber[2])
							{
							case 'A':
								if (memberTemp2.book[bookingNum].trains.seats[count].seatNumber[0] == seatA[0] &&
									memberTemp2.book[bookingNum].trains.seats[count].seatNumber[1] == seatA[1]) {
									strcpy(seatA, "XXX");
								}
								break;
							case 'B':
								if (memberTemp2.book[bookingNum].trains.seats[count].seatNumber[0] == seatB[0] &&
									memberTemp2.book[bookingNum].trains.seats[count].seatNumber[1] == seatB[1]) {
									strcpy(seatB, "XXX");
								}
								break;
							case 'C':
								if (memberTemp2.book[bookingNum].trains.seats[count].seatNumber[0] == seatC[0] &&
									memberTemp2.book[bookingNum].trains.seats[count].seatNumber[1] == seatC[1]) {
									strcpy(seatC, "XXX");
								}
								break;
							case 'D':
								if (memberTemp2.book[bookingNum].trains.seats[count].seatNumber[0] == seatD[0] &&
									memberTemp2.book[bookingNum].trains.seats[count].seatNumber[1] == seatD[1]) {
									strcpy(seatD, "XXX");
								}
								break;
							default:
								break;
							}
						}
					}
					bookingNum++;
				}
			}
			printf("    |  %s %s   %s %s  |\n", seatA, seatB, seatC, seatD);
		}
		printf("    |_____________________|\n");
		if (d != 4)
			printf("            | ... |        \n");
		else {
			printf("    |_____________________|\n");
		}
	}
	printf("\n* XXX = booked\n");
}

bool seat(int bookingNum, int count, int mode) {
	// mode 0 = check
	// mode 1 = add record

	FILE* fp2 = fopen("availableSeat.bin", "ab");
	FILE* fp = fopen("availableSeat.bin", "rb");
	static int found = 0;

	if (fp2 == NULL || fp == NULL) {
		printf("Error to open file!\n");
		system("pause");
		return false;
	}

	// if no record, then direct wirte data into file
	if (fread(&memberTemp.book[bookingNum].trains, sizeof(TrainSchedule), 1, fp) == 0) {
		if (mode == 1) {
			fwrite(&member.book[bookingNum].trains, sizeof(TrainSchedule), 1, fp2);
			fclose(fp2);
			return true;
		}
		return true;
	}

	if (mode == 0) {
		// compare all data (seat availability)
		fseek(fp, 0, SEEK_SET);
		while (fread(&memberTemp.book[bookingNum].trains, sizeof(TrainSchedule), 1, fp) == 1) {
			// compare train id
			if (member.book[bookingNum].trains.trainID == memberTemp.book[bookingNum].trains.trainID) {
				for (int i = 0; i < member.book[bookingNum].quantity; i++) {
					// compare seat number and coach
					if (strcmp(member.book[bookingNum].trains.seats[count].seatNumber, memberTemp.book[bookingNum].trains.seats[i].seatNumber) == 0 &&
						member.book[bookingNum].trains.seats[count].coach == memberTemp.book[bookingNum].trains.seats[i].coach) {
						fclose(fp);
						fclose(fp2);
						return false;
					}
				}
			}
		}
		return true;
	}

	// add data into file
	if (mode == 1) {
		fwrite(&member.book[bookingNum].trains, sizeof(TrainSchedule), 1, fp2);
		fclose(fp);
		fclose(fp2);
		return true;
	}

	return true;
}

void modifySeat(int mode, int bookingNum, int seatNum, bool* valid) {
	// mode 0 = check
	// mode 1 = modify
	int found = 0;

	if (mode == 0) {
		FILE* fp2 = fopen("availableSeat.bin", "ab");
		FILE* fp = fopen("availableSeat.bin", "rb");
		while (fread(&memberTemp2.book[bookingNum].trains, sizeof(TrainSchedule), 1, fp) == 1) {
			// compare train id
			if (memberTemp2.book[bookingNum].trains.trainID == memberTemp.book[bookingNum].trains.trainID) {
				for (int i = 0; i < (sizeof(memberTemp2.book[bookingNum].trains.seats) / sizeof(memberTemp2.book[bookingNum].trains.seats[0])); i++) {
					// compare seat number and coach
					if (strcmp(memberTemp2.book[bookingNum].trains.seats[i].seatNumber, memberTemp.book[bookingNum].trains.seats[seatNum].seatNumber) == 0 &&
						memberTemp2.book[bookingNum].trains.seats[i].coach == memberTemp.book[bookingNum].trains.seats[seatNum].coach) {
						fclose(fp);
						fclose(fp2);
						return;
					}
				}
			}
		}
		fclose(fp2);
		fclose(fp);
		*valid = true;
		return;
	}

	if (mode == 1) {
		FILE* fpTemp = fopen("availableSeat_Modify.bin", "wb");
		FILE* fp = fopen("availableSeat.bin", "rb");
		while (fread(&memberTemp2.book[bookingNum].trains, sizeof(TrainSchedule), 1, fp) == 1) {
			// compare train ID and booking ID
			if (memberTemp2.book[bookingNum].trains.trainID == memberTemp.book[bookingNum].trains.trainID) {
				found = 1;
				fwrite(&memberTemp.book[bookingNum].trains, sizeof(TrainSchedule), 1, fpTemp);

			}
			else {
				fwrite(&memberTemp2.book[bookingNum].trains, sizeof(TrainSchedule), 1, fpTemp);
			}
		}

		fclose(fpTemp);
		fclose(fp);

		if (found == 1) {
			fpTemp = fopen("availableSeat_Modify.bin", "rb");
			fp = fopen("availableSeat.bin", "wb");

			while (fread(&memberTemp2.book[bookingNum].trains, sizeof(TrainSchedule), 1, fpTemp) == 1) {
				fwrite(&memberTemp2.book[bookingNum].trains, sizeof(TrainSchedule), 1, fp);
			}
			fclose(fpTemp);
			fclose(fp);
		}
	}
}

void bookingLogo() {
	printf("______                _     _               \n");
	printf("| ___ \\              | |   (_)              \n");
	printf("| |_/ /  ___    ___  | | __ _  _ __    __ _ \n");
	printf("| ___ \\ / _ \\  / _ \\ | |/ /| || '_ \\  / _` |\n");
	printf("| |_/ /| (_) || (_) ||   < | || | | || (_| |\n");
	printf("\\____/  \\___/  \\___/ |_|\\_\\|_||_| |_| \\__, |\n");
	printf("                                       __/ |\n");
	printf("                                      |___/ \n\n");

}
