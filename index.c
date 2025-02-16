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
#define MAX_AVAILABLE_SEATS 400
#define LATEST_YEAR 2024

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

TrainSchedule schedule;

// Booking
// quantity and seat number

Member member;
Member memberTemp;
Member memberTemp2;
staffinfo staffs;
TrainSchedule schedule = { 0 };
struct Date availableSeat[MAX_BOOKING_DAYS];

//end of booking struct

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
void staffLogo();

// Member
int memberMenu();
void addMember();
void searchMember();
void modifyMember();
void displayMember();
void deleteMember();
void passwordRecoveryMember(int* memberID);
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
void scheduleLogo();
int scheduleMode(int selection);
void scheduleMenu(int* mode);
void searchSchedule();
void modifySchedule();
int addSchedule(int trainIDCounter);
void displaySchedule();
void deleteSchedule();
void scheduleReport();
void availableSeats(int display);
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
void removeSeat(int trainID, int bookingNum, char coach, char seat[]);
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

		//system("color 06");

		printf("                               _____                     _                       ___     _  _            _\n");
		printf("                              |_   _|    _ _   __ _     (_)    _ _       o O O  / __|   | || |   ___    | |_     ___    _ __   \n");
		printf("                                | |     | '_| / _` |    | |   | ' \\     o       \\__ \\    \\_, |  (_-<    |  _|   / -_)  | '  \\  \n");
		printf("                               _|_|_   _|_|_  \\__,_|   _|_|_  |_|_|    TS__[O]  |___/   _|__/   /__/_   _\\__|   \\___|  |_|_|_| \n");
		printf("                             _|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"| {======|_|\"\"\"\"\"|_|\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|\n");
		printf("                             \"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'./o--000'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-' \n");

		printf("_____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ ____\n");
		printf("\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\___\\\n");

		printf("  __         ____  ____   __   ____  ____                                                 ____        _  _  ____  _  _  ____  ____  ____      \n");
		printf(" /  \\       / ___)(_  _) / _\\ (  __)(  __)                                               (___ \\      ( \\/ )(  __)( \\/ )(  _ \\(  __)(  _ \\\n");
		printf("(_/ /   _   \\___ \\  )(  /    \\ ) _)  ) _)                                                 / __/  _   / \\/ \\ ) _) / \\/ \\ ) _ ( ) _)  )   / \n");
		printf(" (__)  (_)  (____/ (__) \\_/\\_/(__)  (__)                                                 (____) (_)  \\_)(_/(____)\\_)(_/(____/(____)(__\\_)  \n");


		printf(" ____        ____   ___  _  _  ____  ____  _  _  __     __   __ _   ___                    ___        ____   __    __   __ _   __   __ _   ___\n");
		printf("(__  \\      / ___) / __)/ )( \\(  __)(    \\/ )( \\(  )   (  ) (  ( \\ / __)                  / _ \\      (  _ \\ /  \\  /  \\ (  / ) (  ) (  ( \\ / __)\n");
		printf(" (__ (  _   \\___ \\( (__ ) __ ( ) _)  ) D () \\/ (/ (_/\\  )(  /    /( (_ \\                 (__  (  _    ) _ ((  O )(  O ) )  (   )(  /    /( (_ \\\n");
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
		staffLogo();
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
	system("cls");
	staffLogo();
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
	system("cls");
	staffLogo();
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
	system("cls");
	staffLogo();
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
			printf("\n\nID             NAME             POSITION         PASSWORD \n");
			printf("-------------------------------------------------------------\n");
			printf("%c%-12d  %-15s  %-15s  %-15s\n", staff.frontID, staff.backID, staff.name, staff.position, staff.pass);
			do {

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
					fclose(stf);
					fclose(stf1);
					staffMain();
					return 0;
				
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
	system("cls");
	staffLogo();
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
	rewind(stdin);
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
	system("cls");
	staffLogo();
	int backid, num = 0;
	char frontid, ctn;

	FILE* stf;
	FILE* stf1;
	stf = fopen("staff.bin", "rb");
	stf1 = fopen("staffmotify.bin", "wb");

	if (stf == NULL && stf1 == NULL) {
		printf("Disable open file");
		return;
	}

	printf("Enter Staff ID need to delete : ");
	scanf("%c%d", &frontid, &backid); rewind(stdin);



	while (fread(&staff, sizeof(staffinfo), 1, stf) == 1)
	{
		if (backid == staff.backID) {
			num = 1;
			printf("\n\nID             NAME             POSITION         PASSWORD \n");
			printf("-------------------------------------------------------------\n");
			printf("%c%-12d  %-15s  %-15s  %-15s\n", staff.frontID, staff.backID, staff.name, staff.position, staff.pass);
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
			return;
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
	system("cls");
	staffLogo();
	int backid, ot, num = 0;
	char frontid;
	double  basic, allowance = 600.00, epf, socso, eis, othour = 0;
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
					scanf("%lf", &othour);
				} while (othour < 0 || othour>10000);

			}

			epf = basic * 0.11;
			socso = basic * 0.05;
			eis = basic * 0.02;
			othour = othour * 11.00;
			printf("\t\t     __________              ___        ___             __      __      __________\n");
			printf("\t\t    |   ____   |     /\\      \\  \\      /  /            |  |    |__|    |   ____   |\n");
			printf("\t\t    |  |    |  |    /  \\      \\  \\    /  /  ______     |  |     __     |  |    |  |   \n");
			printf("\t\t    |  |____|  |   / /\\ \\      \\  \\  /  /  /  __  \\    |  |    |  |    |  |____|  |    \n");
			printf("\t\t    |    ______|  / /  \\ \\      \\  \\/  /  /  /  \\__\\   |  |    |  |    |    ______|  \n");
			printf("\t\t    |   |        / /____\\ \\      \\    /   \\  \\_____    |  |    |  |    |   |       \n");
			printf("\t\t    |   |       /  ______  \\      |  |     \\_____  \\   |  |    |  |    |   | \n");
			printf("\t\t    |   |      /  /      \\  \\     |  |    ______/  /   |  |    |  |    |   |\n");
			printf("\t\t    |___|     /__/        \\__\\    |__|    \\_______/    |__|    |__|    |___|\n\n");

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
void staffLogo() {

	printf("   _____ _         __  __ \n");
	printf("  / ____| |       / _|/ _|\n");
	printf(" | (___ | |_ __ _| | | |_ \n");
	printf("  \\___ \\| __/ _` |  _|  _|\n");
	printf("  ____) | || (_| | | | |  \n");
	printf(" |_____/ \\__\\__,_|_| |_| \n\n");

}
// Member
Member member;
void memberMain() {
	loginStaffMem();

	while (1) {
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

}

// display the member menu
int memberMenu() {
	int mode;
	do {
		system("cls");
		memberLogo();

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
			return;
		}
	}

	if (!found) {
		printf("Member not found!\n");
		system("pause");
		return;
	}


	fclose(fp);
}

void modifyMember() {

	char frontID, ctn;
	int backID, found = 0, selection;

	FILE* fp, * fp1;
	fp = fopen("member.txt", "r");
	fp1 = fopen("memberModify.txt", "w");

	if (fp == NULL) {
		printf("Enable to open this file\n");
		return;
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

	system("pause");
	return;

}


void displayMember() {

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

void passwordRecoveryMember(int* memberID) {
	char frontID, cnt, passrecov[30];
	int found = 0;

	FILE* fp;
	fp = fopen("member.txt", "r");

	if (fp == NULL) {
		printf("Unable to open files for deletion.\n");
		return;
	}

	printf("\nEnter the favorite food that you like:");
	rewind(stdin);
	scanf("%[^\n]", &passrecov);
	rewind(stdin);

	while (fscanf(fp, "%c%d | %[^|]| %d | %[^|]| %c | %[^|]| %[^\n]\n", &member.frontMemberID, &member.backMemberID, &member.name, &member.password, &member.passRecovery, &member.gender, &member.IC, &member.contactNumber) != EOF) {
		if (*memberID == member.backMemberID && strcmp(passrecov, member.passRecovery) == 0) {
			found = 1;
			printf("This is your password : %d.\n", member.password);
			break;
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



// Schedule

int scheduleMode(int selection) {
	system("cls");
	scheduleLogo();
	printf("=================================\n");
	printf("       Select Schedule Mode\n");
	printf("=================================\n\n");
	printf("Staff ---------------- 1\n");
	printf("Member --------------- 2\n");
	printf("Back to main menu ---- 3\n\n");
	printf("Enter Number --------- ");
	rewind(stdin);
	scanf("%d", &selection);
	return selection;
}

void schedulingMain() {
	int select = 0, mode = 0;
	char choice;

	int currentTrainID = 1001;
	schedule.availableSeats = 400;

	FILE* fptr = fopen("train_schedule.txt", "a");
	if (fptr == NULL) {
		printf("Error opening file");
		system("pause");
		return;
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
						searchSchedule();
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
						printf("\n");
						system("pause");
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
						break;
					case 7:
						break;
					case 8:
						main();
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
		char frontMemberID, name[30], gender, IC[17], contactNumber[12], passRecovery[30];
		int password, backMemberID;
		Booking booking;
	};

	int memberID, password;
	struct Member member;
	char cnt = 'y';
	int found = 0;

	FILE* fp;
	fp = fopen("member.txt", "r");

	if (fp == NULL) {
		printf("No member record!\n");
		system("pause");
		return;
	}

	do {
		system("cls");
		scheduleLogo();
		printf("=================================\n");
		printf("         Member Mode\n");
		printf("=================================\n");
		printf("Enter Your Member ID: M");
		rewind(stdin);
		scanf("%d", &memberID);
		printf("Enter password (Enter 0 if forgot password): ");
		rewind(stdin);
		scanf("%d", &password);
		if (password == 0) {
			passwordRecoveryMember(&memberID);
			printf("\n");
			system("pause");
			continue;
		}

		rewind(fp); // reset file pointer to the beginning

		while (!feof(fp)) {
			fscanf(fp, "M%d | %[^|]| %d | %[^|]| %c | %[^|]| %[^\n]\n", &member.backMemberID, &member.name, &member.password, &member.passRecovery, &member.gender, &member.IC, &member.contactNumber);

			if (memberID == member.backMemberID && password == member.password) {
				found = 1;
				printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Member ID", "Name", "Password", "Gender", "IC", "Contact Number");
				printf("M%-13d %-14s %-14d %-14c %-14s %-14s\n", member.backMemberID, member.name, member.password, member.gender, member.IC, member.contactNumber);
				rewind(stdin);
				break;
			}
		}

		if (found == 1) {
			memberLogin(&mode);
			return;
		}
		else {
			printf("Invalid ID or Password, please try again\n\n");
			printf("Try again ----------- Y\n");
			printf("Back ---------------- N\n\n");
			printf("Enter your option --- ");
			rewind(stdin);
			scanf("%c", &cnt);
		}
	} while (cnt == 'y' || cnt == 'Y');

	fclose(fp);
}



void memberLogin(int* mode) {
	int choice;

	do {
		system("cls");
		scheduleLogo();
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
		printf("Main Menu ------------------ 4\n\n");
		printf("Enter Number --------------- ");
		rewind(stdin);
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			searchSchedule(&mode);
			break;
		case 2:
			displaySchedule();
			printf("\n");
			system("pause");
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

	} while (1); // infinity loop 
}



void staffVerify() {
	typedef struct {
		char  name[51], frontID, position[51], fatherName[51], pass[7];
		int  backID;

	}staffinfo;

	int staffID, mode;
	char password[7];
	int num = 0;
	char cont;
	staffinfo staff;

	FILE* stf;
	stf = fopen("staff.bin", "rb");

	if (stf == NULL) {
		printf("No staff record!\n");
		system("pause");
		schedulingMain();
	}

	system("cls");
	scheduleLogo();
	printf("=================================\n");
	printf("         Staff Mode\n");
	printf("=================================\n");
	printf("Enter Your Staff ID: S");
	rewind(stdin);
	scanf("%d", &staffID);
	rewind(stdin);
	printf("Enter password (Enter 0 if forgot password): ");
	scanf("%s", password);

	if (strcmp(password, "0") == 0) {
		passwordRecovery(staffID);
	}


	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
		if (staffID == staff.backID && strcmp(password, staff.pass) == 0) {
			num = 1;
		}
	}


	if (num == 0) {

		printf("Invalid ID or Password, please try again\n\n");
		printf("Try again ----------- Y\n");
		printf("Back ---------------- N\n\n");
		printf("Enter your option --- ");
		rewind(stdin);
		scanf("%c", &cont);
		rewind(stdin);
		if (cont == 'y' || cont == 'Y') {
			staffVerify();
		}
		else if (cont == 'n' || cont == 'N') {
			schedulingMain();
		}
		else {
			rewind(stdin);
			printf("Invalid option!\n");
			system("pause");
			staffVerify();
		}
	}

	rewind(stdin);
	num = 0;
}


void scheduleMenu(int* mode) {
	int selection;
	do {
		do {
			system("cls");
			scheduleLogo();
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
			rewind(stdin);
			scanf("%d", &selection);
		} while (selection < 1 || selection > 8);

		*mode = selection; // assign the value of selection to mode

	} while (*mode != 1 && *mode != 2 && *mode != 3 && *mode != 4 && *mode != 5 && *mode != 6 && *mode != 7 && *mode != 8);

	return;

}


int addSchedule(int currentTrainID) {
	system("cls");
	scheduleLogo();
	printf("==============================\n");
	printf("       Add Schedule\n");
	printf("==============================\n\n");

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

	schedule.trainID = 1000;

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
	scanf("%[^\n]", schedule.departureStation);
	printf("Enter Arrival Station: ");
	rewind(stdin);
	scanf("%[^\n]", schedule.arrivalStation);

	do {
		printf("Enter Departure Date (DD/MM/YYYY): ");
		rewind(stdin);

		// compares the return value of scanf with 3
		if (scanf("%d/%d/%d", &schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year) != 3) {
			printf("Invalid input format. Please try again.\n");
			rewind(stdin); // clear input buffer
			continue;
		}

		// validate day, month, and year individually
		if (schedule.departureDate.day < 1 || schedule.departureDate.day > 31 ||
			schedule.departureDate.month < 1 || schedule.departureDate.month > 12 ||
			schedule.departureDate.year != LATEST_YEAR) {
			printf("Invalid date. Please enter a valid date.\n");
			continue;
		}

		break;
	} while (1);

	do {
		printf("Enter Arrival Date (DD/MM/YYYY): ");
		rewind(stdin);
		if (scanf("%d/%d/%d", &schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year) != 3) {
			printf("Invalid input format. Please try again.\n");
			rewind(stdin); // clear input buffer
			continue;
		}

		// validate day, month, and year individually
		if (schedule.arrivalDate.day < 1 || schedule.arrivalDate.day > 31 ||
			schedule.arrivalDate.month < 1 || schedule.arrivalDate.month > 12 ||
			schedule.arrivalDate.year != LATEST_YEAR) {
			printf("Invalid date. Please enter a valid date.\n");
			continue;
		}

		break;
	} while (1);


	//initialize the time to 0
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

	//initialize the time to 0
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

	printf("Enter ticket price: RM");
	rewind(stdin);
	scanf("%f", &schedule.ticketPrice);

	char confirm; // check confirm
	printf("\nConfirm add schedule? (Y/N): ");
	scanf(" %c", &confirm);
	if (confirm != 'Y' && confirm != 'y') {
		printf("\nCancelled\n");
		fclose(fptr);
		return schedule.trainID;
	}

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
	int display = 0; //0 mean no need to display when do call the function availble seats, only do calculation
	availableSeats(display);
	int menu, departureDay, departureMonth, departureYear, arrivalDay, arrivalMonth, arrivalYear;
	char cont;
	char departureStation[50], arrivalStation[50];

	int found = 0;

	FILE* fptr = fopen("train_schedule.txt", "r");
	if (fptr == NULL) {
		printf("Error opening file\n");
		return;
	}

	system("cls");
	scheduleLogo();
	printf("==============================\n");
	printf("        Search Schedule\n");
	printf("==============================\n\n");
	printf("Select an option:\n");
	printf("1. Search By Train ID\n");
	printf("2. Search By Destination\n");
	printf("3. Search By Date\n");
	printf("4. Back\n\n");
	printf("Enter your choice: ");
	rewind(stdin);
	scanf("%d", &menu);

	switch (menu) {
	case 1:
		do {
			system("cls");
			scheduleLogo();
			printf("==============================\n");
			printf("       Schedule By Train ID\n");
			printf("==============================\n\n");
			int trainID;
			FILE* fptr = fopen("train_schedule.txt", "r");
			if (fptr == NULL) {
				printf("Error opening file\n");
				exit(-1);
			}

			printf("Enter Train ID to search: T");
			scanf("%d", &trainID);

			int found = 0;
			printf("\n");
			printf("===========================================================================================================\n");
			printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
			printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
			printf("===========================================================================================================\n");

			//reset the file pointer for reading from beginning
			rewind(fptr);

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

			fclose(fptr);

			if (!found) {
				printf("Train ID '%c%d' not found\n", TRAIN_FRONT_ID, trainID);
			}

			printf("\nDo you want continue search another schedule?(Y/N): ");
			rewind(stdin);
			cont = getchar();
			printf("\n");


		} while (cont == 'y' || cont == 'Y');

		if (cont == 'n' || cont == 'N') {
			searchSchedule();
		}

		break;
	case 2:
		do {
			system("cls");
			scheduleLogo();
			printf("===============================\n");
			printf("       Schedule By Destination\n");
			printf("===============================\n\n");
			printf("Enter the departure station: ");
			rewind(stdin);
			scanf("%[^\n]", departureStation);
			printf("Enter the arrival station: ");
			rewind(stdin);
			scanf("%[^\n]", arrivalStation);

			FILE* fptr = fopen("train_schedule.txt", "r");
			if (fptr == NULL) {
				printf("Error opening file\n");
				return;
			}

			int found = 0;

			printf("\n");
			printf("============================================================================================================\n");
			printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
			printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
			printf("============================================================================================================\n");

			rewind(fptr);

			while (!feof(fptr)) {
				fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
					&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
					&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
					&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
					&schedule.departureTime.hour, &schedule.departureTime.min,
					&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
					&schedule.availableSeats, &schedule.ticketPrice);

				if (strcmp(departureStation, schedule.departureStation) == 0 && strcmp(arrivalStation, schedule.arrivalStation) == 0) {
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

			fclose(fptr);

			if (!found) {
				printf("No record\n");
			}

			printf("\nDo you want continue search another schedule?(Y/N): ");
			rewind(stdin);
			cont = getchar();
			printf("\n");
		} while (cont == 'y' || cont == 'Y');

		if (cont == 'n' || cont == 'N') {
			searchSchedule();
		}

		break;
	case 3:
		do {
			system("cls");
			scheduleLogo();
			printf("==============================\n");
			printf("       Schedule By Date\n");
			printf("==============================\n\n");
			printf("Enter the departure date (DD/MM/YYYY): ");
			rewind(stdin);
			scanf("%d/%d/%d", &departureDay, &departureMonth, &departureYear);
			printf("Enter the arrival date (DD/MM/YYYY): ");
			rewind(stdin);
			scanf("%d/%d/%d", &arrivalDay, &arrivalMonth, &arrivalYear);

			FILE* fptr = fopen("train_schedule.txt", "r");
			if (fptr == NULL) {
				printf("Error opening file\n");
				return;
			}

			int found = 0;

			printf("\n");
			printf("============================================================================================================\n");
			printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
			printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
			printf("============================================================================================================\n");

			//reset the file pointer for reading from beginning
			rewind(fptr);

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
				if (schedule.departureDate.day == departureDay && schedule.departureDate.month == departureMonth && schedule.departureDate.year == departureYear
					&& schedule.arrivalDate.day == arrivalDay && schedule.arrivalDate.month == arrivalMonth && schedule.arrivalDate.year == arrivalYear) {
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

			fclose(fptr);

			if (!found) {
				printf("No record\n");
			}

			printf("\nDo you want continue search another schedule?(Y/N): ");
			rewind(stdin);
			cont = getchar();
			printf("\n");
		} while (cont == 'y' || cont == 'Y');

		if (cont == 'n' || cont == 'N') {
			searchSchedule();
		}
		break;
	case 4:
		//exit
		return;
	default:
		printf("Invalid choice. Please try again.\n");
		break;
	}
}

void modifySchedule() {
	int display = 0; //pass 0 to the available seats for only do calculation withou print anything
	availableSeats(display);
	system("cls");
	scheduleLogo();
	printf("==============================\n");
	printf("       Modify Schedule\n");
	printf("==============================\n\n");
	int trainID;
	printf("Enter Train ID to modify: T");
	rewind(stdin);
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
				schedule.trainID, schedule.departureStation, schedule.arrivalStation,
				schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
				schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
				schedule.departureTime.hour, schedule.departureTime.min,
				schedule.arrivalTime.hour, schedule.arrivalTime.min,
				schedule.availableSeats, schedule.ticketPrice);

			printf("\nEnter New Departure Station: ");
			rewind(stdin);
			scanf(" %[^\n]", schedule.departureStation);
			rewind(stdin);
			printf("Enter New Arrival Station: ");
			rewind(stdin);
			scanf(" %[^\n]", schedule.arrivalStation);
			rewind(stdin);
			do {
				printf("Enter New Departure Date (DD/MM/YYYY): ");
				rewind(stdin);

				// compares the return value of scanf with 3
				if (scanf("%d/%d/%d", &schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year) != 3) {
					printf("Invalid input format. Please try again.\n");
					rewind(stdin); // clear input buffer
					continue;
				}

				// validate day, month, and year individually
				if (schedule.departureDate.day < 1 || schedule.departureDate.day > 31 ||
					schedule.departureDate.month < 1 || schedule.departureDate.month > 12 ||
					schedule.departureDate.year != LATEST_YEAR) {
					printf("Invalid date. Please enter a valid date.\n");
					continue;
				}

				break;
			} while (1);

			do {
				printf("Enter New Arrival Date (DD/MM/YYYY): ");
				rewind(stdin);
				if (scanf("%d/%d/%d", &schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year) != 3) {
					printf("Invalid input format. Please try again.\n");
					rewind(stdin); // clear input buffer
					continue;
				}

				// validate day, month, and year individually
				if (schedule.arrivalDate.day < 1 || schedule.arrivalDate.day > 31 ||
					schedule.arrivalDate.month < 1 || schedule.arrivalDate.month > 12 ||
					schedule.arrivalDate.year != LATEST_YEAR) {
					printf("Invalid date. Please enter a valid date.\n");
					continue;
				}

				break;
			} while (1);

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
			rewind(stdin);
			scanf("%f", &schedule.ticketPrice);

			char confirm; // check confirm
			printf("\nConfirm modify (Y/N): ");
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

	if (found) {
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
	}

	if (!found) {
		printf("Train ID '%c%d' not found\n\n", TRAIN_FRONT_ID, trainID);
	}
	else {
		printf("\nSchedule modified successfully\n");
	}
	fclose(fptr);
	fclose(temp);
}

void displaySchedule() {
	FILE* fptr;
	fptr = fopen("train_schedule.txt", "r");
	int display = 1; // this is pass to available seats to do validation for display the schedule
	availableSeats(display);

	if (fptr == NULL) {
		printf("Error opening file\n");
		return;
	}

	system("cls");
	scheduleLogo();
	printf("==============================\n");
	printf("       Display Schedule\n");
	printf("==============================\n");
	printf("\nTrain Schedule:\n");
	printf("============================================================================================================\n");
	printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
	printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
	printf("============================================================================================================\n");

	if (fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
		&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
		&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
		&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
		&schedule.departureTime.hour, &schedule.departureTime.min,
		&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
		&schedule.availableSeats, &schedule.ticketPrice) == EOF) {
		printf("No record\n");
		return;
	}

	//reset the file pointer for reading from beginning
	rewind(fptr);

	if (fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
		&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
		&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
		&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
		&schedule.departureTime.hour, &schedule.departureTime.min,
		&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
		&schedule.availableSeats, &schedule.ticketPrice) == EOF) {
		printf("No record!\n");
		fclose(fptr);
		rewind(fptr);
		return;
	}
	else availableSeats(display);

}

void deleteSchedule() {
	int trainID;
	int display = 0; //pass 0 to the displaySchedule for only do calculation withou print anything
	availableSeats(display);
	system("cls");
	scheduleLogo();
	printf("==============================\n");
	printf("       Delete Schedule\n");
	printf("==============================\n\n");

	FILE* fptr = fopen("train_schedule.txt", "r");
	FILE* temp = fopen("temp.txt", "w");

	if (fptr == NULL || temp == NULL) {
		printf("Error opening file\n");
		return;
	}


	printf("Enter Train ID to delete: T");
	rewind(stdin);
	scanf("%d", &trainID);

	printf("\nTrain Schedule:\n");
	printf("============================================================================================================\n");
	printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
	printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
	printf("============================================================================================================\n");

	if (fscanf(fptr, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
		&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
		&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
		&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
		&schedule.departureTime.hour, &schedule.departureTime.min,
		&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
		&schedule.availableSeats, &schedule.ticketPrice) == EOF) {
		printf("No record\n\n");
		return;
	}

	//reset the file pointer for reading from beginning
	rewind(fptr);

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
			printf("\nConfirm delete (Y/N): ");
			rewind(stdin);
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
		//here is store the data type has been read to the integer variable
		int readAll = fscanf(temp, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice);

		//
		if (readAll != EOF) {
			fprintf(fptr, "T%d, %s, %s, %02d/%02d/%04d, %02d/%02d/%04d, %02d:%02d, %02d:%02d, %d, %.2f\n",
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
	remove("temp.txt");

	if (found) {
		printf("\nSchedule deleted successfully\n");
	}
	else {
		printf("Train ID '%c%d' not found\n", TRAIN_FRONT_ID, trainID);
	}
}

void availableSeats(int display) {
	FILE* scheduleFiles;
	FILE* bookingFiles;
	FILE* temp;

	scheduleFiles = fopen("train_schedule.txt", "r");
	bookingFiles = fopen("Booking.bin", "rb");
	temp = fopen("temp.txt", "w"); //this to update the available seat

	if (bookingFiles == NULL || scheduleFiles == NULL || temp == NULL) {
		printf("Error opening files.\n");
		return;
	}

	if (fscanf(scheduleFiles, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
		&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
		&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
		&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
		&schedule.departureTime.hour, &schedule.departureTime.min,
		&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
		&schedule.availableSeats, &schedule.ticketPrice) == EOF) {
		printf("No record\n");
		return;
	}

	//reset the file pointer for reading from beginning
	rewind(scheduleFiles);

	// initialize the total booked seats to 0 first
	int totalBookedSeats[MAX_BOOKING] = { 0 };
	int c = 0; // c = customer, array store infromation start from customer 0, and continue...
	while (fread(&memberTemp.backMemberID, sizeof(int), 1, bookingFiles) == 1 &&
		fread(&memberTemp.book[c], sizeof(Booking), 1, bookingFiles) == 1) {
		if (strcmp(memberTemp.book[c].ticketStatus, "Booked") == 0) {
			//this is calculate total booked seats for each train 
			//totalBookedSeats[T1001] values is 0 then += trainId.quantity
			totalBookedSeats[memberTemp.book[c].trains.trainID] += memberTemp.book[c].quantity;

			if (strcmp(memberTemp.book[c].ticketStatus, "Canceled") == 0) {
				//this is calculate total booked seats for each train minus for member who cancel booking
				totalBookedSeats[memberTemp.book[c].trains.trainID] -= memberTemp.book[c].quantity;
			}
			c++;
		}

	}
	fclose(bookingFiles);

	// Display schedule with updated available seats
	while (fscanf(scheduleFiles, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
		&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
		&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
		&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
		&schedule.departureTime.hour, &schedule.departureTime.min,
		&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
		&schedule.availableSeats, &schedule.ticketPrice) != EOF) {

		// Calculate available seats
		schedule.availableSeats = MAX_AVAILABLE_SEATS - totalBookedSeats[schedule.trainID];

		// Print schedule and update available seats if display is 1
		if (display == 1) {
			printf("%c%d\t    %-13s%-14s%02d/%02d/%04d   %02d/%02d/%04d\t   %02d:%02d\t%02d:%02d\t    %-9d %.2f\n",
				TRAIN_FRONT_ID,
				schedule.trainID, schedule.departureStation, schedule.arrivalStation,
				schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
				schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
				schedule.departureTime.hour, schedule.departureTime.min,
				schedule.arrivalTime.hour, schedule.arrivalTime.min,
				schedule.availableSeats, schedule.ticketPrice);
		}

		// Write schedule with available seats to file
		fprintf(temp, "%c%d, %s, %s, %02d/%02d/%04d, %02d/%02d/%04d, %02d:%02d, %02d:%02d, %d, %.2f\n",
			TRAIN_FRONT_ID,
			schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
			schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
			schedule.departureTime.hour, schedule.departureTime.min,
			schedule.arrivalTime.hour, schedule.arrivalTime.min,
			schedule.availableSeats, schedule.ticketPrice);
	}

	fclose(scheduleFiles);
	fclose(temp);

	scheduleFiles = fopen("train_schedule.txt", "w");
	temp = fopen("temp.txt", "r");

	while (!feof(temp)) {
		fscanf(temp, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice);
		fprintf(scheduleFiles, "%c%d, %s, %s, %02d/%02d/%04d, %02d/%02d/%04d, %02d:%02d, %02d:%02d, %d, %.2f\n",
			TRAIN_FRONT_ID,
			schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
			schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
			schedule.departureTime.hour, schedule.departureTime.min,
			schedule.arrivalTime.hour, schedule.arrivalTime.min,
			schedule.availableSeats, schedule.ticketPrice);
	}

	fclose(scheduleFiles);
	fclose(temp);
}


void scheduleReport() {
	int selection;
	int totalTrains = 0, totalSeats = 0, maxSeats = 0;
	float totalTicketPrice = 0, averageTicketPrice = 0;
	int month, year;
	char cont;

	int display = 0; // to call the available seats function and update the lates available seats without print any information
	availableSeats(display);

	FILE* scheduleFiles, * fptr;

	scheduleFiles = fopen("train_schedule.txt", "r");
	fptr = fopen("train_schedule_report.txt", "w");

	if (scheduleFiles == NULL || fptr == NULL) {
		printf("Error opening file\n");
		return;
	}

	system("cls");
	scheduleLogo();
	printf("==============================\n");
	printf("       Schedule Report\n");
	printf("==============================\n");
	printf("1. Overall Schedule Report\n");
	printf("2. Schedule Report By Month\n");
	printf("3. Back\n\n");
	printf("Enter your selection: ");
	rewind(stdin);
	scanf("%d", &selection);

	if (selection == 1) {
		system("cls");
		scheduleLogo();
		printf("================================================\n");
		printf("                 Overall Train Schedule Report\n");
		printf("============================================================================================================\n");
		printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
		printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
		printf("============================================================================================================\n");

		if (fscanf(scheduleFiles, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice) == EOF) {
			printf("No record\n\n");
			return;
		}

		//reset the file pointer for reading from beginning
		rewind(scheduleFiles);

		//initialize again the value before calculation
		totalTrains = 0, totalSeats = 0, maxSeats = 0;
		totalTicketPrice = 0, averageTicketPrice = 0;

		while (!feof(scheduleFiles)) {
			fscanf(scheduleFiles, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
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

			// calculate total ticket price and total seats
			totalTrains++;
			totalTicketPrice += schedule.ticketPrice;
			totalSeats += schedule.availableSeats;

		}

		// calculate average ticket price
		if (totalTrains > 0) {
			averageTicketPrice = totalTicketPrice / totalTrains;
		}

		printf("------------------------------------------------------------------------------------------------------------\n\n");
		printf("==================== Generated Report As Below ====================\n\n");
		printf("Overall Schedule Report\n");
		printf("----------------------\n");
		printf("Total Trains: %d\n", totalTrains);
		printf("Total Seats Available: %d\n", totalSeats);
		printf("Average Ticket Price: %.2f\n", averageTicketPrice);
		printf("Max Seats on a Train: %d\n\n", MAX_AVAILABLE_SEATS);

		printf("Save the report?\n");
		printf("Yes or No (Y/N): ");
		rewind(stdin);
		scanf("%c", &cont);
		if (cont == 'y' || cont == 'Y') {
			fprintf(fptr, "Overall Schedule Report\n");
			fprintf(fptr, "----------------------\n");
			fprintf(fptr, "Total Trains: %d\n", totalTrains);
			fprintf(fptr, "Total Seats Available: %d\n", totalSeats);
			fprintf(fptr, "Average Ticket Price: %.2f\n", averageTicketPrice);
			fprintf(fptr, "Max Seats on a Train: %d\n", MAX_AVAILABLE_SEATS);
			printf("Report Generated!\n\n");
			system("pause");
		}

		fclose(scheduleFiles);
		fclose(fptr);
	}
	else if (selection == 2) {
		system("cls");
		scheduleLogo();
		printf("==============================\n");
		printf("    Schedule Report By Month\n");
		printf("==============================\n");

		if (fscanf(scheduleFiles, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
			&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
			&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
			&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
			&schedule.departureTime.hour, &schedule.departureTime.min,
			&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
			&schedule.availableSeats, &schedule.ticketPrice) == EOF) {
			printf("No record\n\n");
			return;
		}

		//reset the file pointer for reading from beginning
		rewind(scheduleFiles);

		printf("Enter month and year (MM/YYYY): ");
		rewind(stdin);
		scanf("%d/%d", &month, &year);


		system("cls");
		printf("============================================================\n");
		printf("                  Train Schedule Report\n");
		printf("============================================================\n");
		printf("                  By %02d/%04d\n", month, year);
		printf("============================================================================================================\n");
		printf("Train ID    Departure    Arrival       Departure    Arrival       Departure    Arrival    Available   Ticket\n");
		printf("            Station      Station       Date         Date          Time         Time       Seats       Price\n");
		printf("============================================================================================================\n");

		//initialize again the value before calculation
		totalTrains = 0, totalSeats = 0, maxSeats = 0;
		totalTicketPrice = 0, averageTicketPrice = 0;

		while (!feof(scheduleFiles)) {
			fscanf(scheduleFiles, "T%d, %[^,], %[^,], %d/%d/%d, %d/%d/%d, %d:%d, %d:%d, %d, %f\n",
				&schedule.trainID, schedule.departureStation, schedule.arrivalStation,
				&schedule.departureDate.day, &schedule.departureDate.month, &schedule.departureDate.year,
				&schedule.arrivalDate.day, &schedule.arrivalDate.month, &schedule.arrivalDate.year,
				&schedule.departureTime.hour, &schedule.departureTime.min,
				&schedule.arrivalTime.hour, &schedule.arrivalTime.min,
				&schedule.availableSeats, &schedule.ticketPrice);

			if (month == schedule.departureDate.month && year == schedule.departureDate.year) {
				printf("%c%d\t    %-13s%-14s%02d/%02d/%04d   %02d/%02d/%04d\t   %02d:%02d\t%02d:%02d\t    %-9d %.2f\n",
					TRAIN_FRONT_ID,
					schedule.trainID, schedule.departureStation, schedule.arrivalStation,
					schedule.departureDate.day, schedule.departureDate.month, schedule.departureDate.year,
					schedule.arrivalDate.day, schedule.arrivalDate.month, schedule.arrivalDate.year,
					schedule.departureTime.hour, schedule.departureTime.min,
					schedule.arrivalTime.hour, schedule.arrivalTime.min,
					schedule.availableSeats, schedule.ticketPrice);

				// calculate total ticket price and total seats
				totalTrains++;
				totalTicketPrice += schedule.ticketPrice;
				totalSeats += schedule.availableSeats;

			}

			// calculate average ticket price
			if (totalTrains > 0) {
				averageTicketPrice = totalTicketPrice / totalTrains;
			}
		}

		printf("------------------------------------------------------------------------------------------------------------\n\n");
		printf("==================== Generated Report As Below ====================\n\n");
		printf("Schedule Report By %02d/%04d\n", month, year);
		printf("-----------------------------------------\n");
		printf("Total Trains: %d\n", totalTrains);
		printf("Total Seats Available: %d\n", totalSeats);
		printf("Average Ticket Price: %.2f\n", averageTicketPrice);
		printf("Max Seats on a Train: %d\n\n", MAX_AVAILABLE_SEATS);

		printf("Save the report?\n");
		printf("Yes or No (Y/N): ");
		rewind(stdin);
		scanf("%c", &cont);
		if (cont == 'y' || cont == 'Y') {
			fprintf(fptr, "Schedule Report By %02d/%04d\n", month, year);
			fprintf(fptr, "-----------------------------------------\n");
			fprintf(fptr, "Total Trains: %d\n", totalTrains);
			fprintf(fptr, "Total Seats Available: %d\n", totalSeats);
			fprintf(fptr, "Average Ticket Price: %.2f\n", averageTicketPrice);
			fprintf(fptr, "Max Seats on a Train: %d\n", MAX_AVAILABLE_SEATS);
			printf("Report Generated!\n\n");
			system("pause");
		}

		fclose(scheduleFiles);
		fclose(fptr);
	}
	else if (selection == 3) {
		return;
	}
	else {
		printf("Invalid option, please enter again\n");
		system("pause");
		scheduleReport();
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


void bookingMain() {
	int mode, loginMode, trainID, found = 0;
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
				system("cls");
				found = 0;
				do {
					printf("Enter Train ID to view seats (Enter 0 to view train schedule): T");
					scanf("%d", &trainID);
					rewind(stdin);
					printf("\n");

					// display train information
					if (trainID == 0 && found != 1) {
						found = 1;
						schedulingData(trainID, "display", 0, 0);
						printf("\n");
						continue;
					}

					if (trainID <= 1000 || trainID >= 10000) {
						continue;
					}
					else {
						break;
					}

				} while (1);

				system("cls");
				displaySeat(trainID);
				printf("Enter Any Key to continue...");
				rewind(stdin);
				while (getc(stdin) != '\n');
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
		printf("Log Out and Back to Main Menu ----------- 6\n\n");
		printf("Enter Number ---------------------------- ");
		scanf(" %d", mode);
		rewind(stdin);
	} while (*mode != 1 && *mode != 2 && *mode != 3 && *mode != 4 && *mode != 5 && *mode != 6);
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
		printf("Log Out and Back to Main Menu ------------ 6\n\n");
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
	while (1) {
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
	};

	// enter quntity of booking
	while (1) {
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
	};

	found = 0;

	// select seat
	printf("\n             Select Seat            \n");
	printf("<<< Enter 0 to view available seat >>>\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (int i = 0; i < member.book[bookingNum].quantity; i++) { // based on quantity
		while (1) {
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
				(member.book[bookingNum].trains.seats[i].seatNumber[2] >= 'A' &&
					member.book[bookingNum].trains.seats[i].seatNumber[2] <= 'D')) || repeat == 1);

			// check if repeat seat number with booked seats
			bool seatAvailability = seat(bookingNum, i, 0);
			if (seatAvailability) {
				break;
			}
			else {
				printf("\nSeat at %s, Coach %c has been booked.\nEnter again!\n", member.book[bookingNum].trains.seats[i].seatNumber, member.book[bookingNum].trains.seats[i].coach);
				continue;
			}

		};
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
			while (1) {
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
					printf("<<< Enter 0 to view available seat >>>\n");
					printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
					for (int i = 0; i < memberTemp.book[cnt].quantity; i++) { // based on quantity
						while (1) {
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
								memberTemp.book[cnt].trains.seats[i].seatNumber[2] >= 'A' &&
								memberTemp.book[cnt].trains.seats[i].seatNumber[2] <= 'D') || repeat == 1);

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

						};
					}
					break;
				case 2:

					oriQuantity = memberTemp.book[cnt].quantity;
					while (1) {
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
					};

					if (memberTemp.book[cnt].quantity > oriQuantity) {

						// select seat
						printf("\n        Select Additional Seat      \n");
						printf("<<< Enter 0 to view available seat >>>\n");
						printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
						for (int i = oriQuantity; i < memberTemp.book[cnt].quantity; i++) { // based on quantity
							while (1) {
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
									memberTemp.book[cnt].trains.seats[i].seatNumber[2] >= 'A' &&
									memberTemp.book[cnt].trains.seats[i].seatNumber[2] <= 'D') || repeat == 1);

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

							};
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
					return;
					break;
				}

				do {
					printf("\n1. Confirm modify\n");
					printf("2. Cancel modify\n");
					printf("Select number: ");
					scanf(" %d", &selection);
					rewind(stdin);
				} while (!(selection == 1 || selection == 2));

				if (selection == 1) {
					modifySeat(1, cnt, memberTemp.book[cnt].quantity, &valid);
					break;
				}
				else return;

			};
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

			if (strcmp(mode, "staff") == 0) for (int i = 0; i < 11; i++) printf("=");
			for (int i = 0; i < 133; i++)
				printf("=");
			printf("\n");
			if (strcmp(mode, "staff") == 0) printf("%-11s", "Member ID");
			printf("%-12s%-10s%-17s%-13s%-15s%-15s%-15s%-16s%-10s%-10s\n", "Booking ID", "Train ID", "Seat Number", "Coach", "Payment Info", "Ticket Status", "Booking Date", "Departure Date", "Quantity", "Amount");
			if (strcmp(mode, "staff") == 0) for (int i = 0; i < 11; i++) printf("=");
			for (int i = 0; i < 133; i++)
				printf("=");
			printf("\n");
		}

		printf("\n");

		// display data
		if (strcmp(mode, "staff") == 0) printf("%c%-10d", MEMBER_FRONT_ID, memberTemp.backMemberID);
		printf("%c%-11d%c%-9d", BOOKING_FRONT_ID, memberTemp.book[c].bookingID, TRAIN_FRONT_ID, memberTemp.book[c].trains.trainID);

		// seat and coach based on quantity
		// seat
		for (int i = 0; i < memberTemp.book[c].quantity; i++) {
			if (i < 3) {
				if (memberTemp.book[c].quantity >= 3) {
					if (i != 2) {
						printf("%s, ", memberTemp.book[c].trains.seats[i].seatNumber);
					}
					else printf("%-7s", memberTemp.book[c].trains.seats[i].seatNumber); // 15 - 5 - 5 = 5
				}
				else {
					switch (memberTemp.book[c].quantity)
					{
					case 1:
						printf("%-17s", memberTemp.book[c].trains.seats[i].seatNumber); // just 1 seat number
						break;
					case 2:
						if (i == 0) {
							printf("%s, ", memberTemp.book[c].trains.seats[i].seatNumber);
						}
						else
							printf("%-12s", memberTemp.book[c].trains.seats[i].seatNumber); // 15 - 5 = 10
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
					else printf("%-7c", memberTemp.book[c].trains.seats[i].coach); // 15 - 3 - 3 = 9
				}
				else {
					switch (memberTemp.book[c].quantity) {
					case 1:
						printf("%-13c", memberTemp.book[c].trains.seats[i].coach); // just 1 coach
						break;
					case 2:
						if (i == 0) {
							printf("%c, ", memberTemp.book[c].trains.seats[i].coach);
						}
						else
							printf("%-10c", memberTemp.book[c].trains.seats[i].coach); // 15 - 3 = 12
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
		printf("%-10d%-10.2f\n", memberTemp.book[c].quantity, memberTemp.book[c].amount);

		// 4-7
		if (memberTemp.book[c].quantity > 3) {
			if (strcmp(mode, "staff") == 0) printf("%11s", "");
			printf("%22s", "");
			// seat
			for (int i = 3; i < memberTemp.book[c].quantity; i++) {
				if (i >= 3 && i < 6) {
					if (memberTemp.book[c].quantity >= 6) {
						if (i != 5) {
							printf("%s, ", memberTemp.book[c].trains.seats[i].seatNumber);
						}
						else printf("%-7s", memberTemp.book[c].trains.seats[i].seatNumber);
					}
					else {
						switch (memberTemp.book[c].quantity) {
						case 4:
							printf("%-17s", memberTemp.book[c].trains.seats[i].seatNumber);
							break;
						case 5:
							if (i == 3) {
								printf("%s, ", memberTemp.book[c].trains.seats[i].seatNumber);
							}
							else
								printf("%-12s", memberTemp.book[c].trains.seats[i].seatNumber);
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
						else printf("%-7c", memberTemp.book[c].trains.seats[i].coach);
					}
					else {
						switch (memberTemp.book[c].quantity) {
						case 4:
							printf("%-13c", memberTemp.book[c].trains.seats[i].coach);
							break;
						case 5:
							if (i == 3) {
								printf("%c, ", memberTemp.book[c].trains.seats[i].coach);
							}
							else
								printf("%-10c", memberTemp.book[c].trains.seats[i].coach);
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
			if (strcmp(mode, "staff") == 0) printf("%11s", "");
			printf("%22s", "");
			// seat
			for (int i = 6; i < memberTemp.book[c].quantity; i++) {
				if (i >= 6 && i < 9) {
					if (memberTemp.book[c].quantity >= 9) {
						if (i != 8) {
							printf("%s, ", memberTemp.book[c].trains.seats[i].seatNumber);
						}
						else printf("%-7s", memberTemp.book[c].trains.seats[i].seatNumber);
					}
					else {
						switch (memberTemp.book[c].quantity) {
						case 7:
							printf("%-17s", memberTemp.book[c].trains.seats[i].seatNumber);
							break;
						case 8:
							if (i == 6) {
								printf("%s, ", memberTemp.book[c].trains.seats[i].seatNumber);
							}
							else
								printf("%-12s", memberTemp.book[c].trains.seats[i].seatNumber);
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
						else printf("%-7c", memberTemp.book[c].trains.seats[i].coach);
					}
					else {
						switch (memberTemp.book[c].quantity) {
						case 7:
							printf("%-13c", memberTemp.book[c].trains.seats[i].coach);
							break;
						case 8:
							if (i == 6) {
								printf("%c, ", memberTemp.book[c].trains.seats[i].coach);
							}
							else
								printf("%-10c", memberTemp.book[c].trains.seats[i].coach);
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
			if (strcmp(mode, "staff") == 0) printf("%11s", "");
			printf("%22s", "");
			printf("%-17s", memberTemp.book[c].trains.seats[9].seatNumber);
			printf("%-13c", memberTemp.book[c].trains.seats[9].coach);
		}
		c++;
	}


	if (c == 0) {
		printf("Record not found!\n");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return;
	}
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
				if (confirm == 'N' || confirm == 'n') {
					return;
				}
			} while (!(confirm == 'Y' || confirm == 'y'));

			removeSeat(memberTemp.book[cnt].trains.trainID, cnt, memberTemp.book[cnt].trains.seats[0].coach, memberTemp.book[cnt].trains.seats[0].seatNumber);

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
				if (confirm == 'N' || confirm == 'n') {
					return;
				}
			} while (!(confirm == 'Y' || confirm == 'y'));
			removeSeat(memberTemp.book[cnt].trains.trainID, cnt, memberTemp.book[cnt].trains.seats[0].coach, memberTemp.book[cnt].trains.seats[0].seatNumber);

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
	int selection, month, year, found = 0, select;
	const char* monthNames[] = { "Invalid", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	int totalBookings = 0;
	double totalRevenue = 0;
	int creditCardCount = 0, cashCount = 0, debitCardCount = 0, bankTransferCount = 0, touchNGoCount = 0;
	int bookedCount = 0, canceledCount = 0;
	double averageAmount;

	FILE* fp = fopen("Booking.bin", "rb");

	system("cls");

	if (fp == NULL) {
		printf("NO booking record!\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return;
	}

	while (1) {
		while (1) {
			printf(" Report Type\n");
			printf("=============\n");
			printf("[1] Monthly Report\n");
			printf("[2] Yearly Report\n");
			printf("[3] Back\n\n");
			printf("Enter your selection: ");
			scanf("%d", &selection);

			if (selection == 1) {
				do {
					printf("Enter the year (2020-2024): ");
					scanf("%d", &year);
				} while (!(year >= 2020 && year <= 2024));
				do {
					printf("Enter the month (1-12): ");
					scanf("%d", &month);
				} while (!(month >= 1 && month <= 12));
				break;
			}
			else if (selection == 2) {
				do {
					printf("Enter the year (2020-2024): ");
					scanf("%d", &year);
				} while (!(year >= 2020 && year <= 2024));
				break;
			}
			else if (selection == 3) return;
			else {
				printf("Invalid selection.\n\n");
				continue;
			}
		};


		while (fread(&memberTemp.backMemberID, sizeof(int), 1, fp) == 1 &&
			fread(&memberTemp.book[totalBookings], sizeof(Booking), 1, fp) == 1) {

			if (selection == 1 && memberTemp.book[totalBookings].bookingDate.month != month && memberTemp.book[totalBookings].bookingDate.year != year) {
				continue;
			}
			if (selection == 2 && memberTemp.book[totalBookings].bookingDate.year != year) {
				continue;
			}

			found = 1;

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
		averageAmount = totalRevenue / totalBookings;

		fclose(fp);
		if (found == 1) {
			break;
		}
		else {
			printf("No record for your selection date\n\n");
			continue;
		}
	}

	// Display the report
	system("cls");
	if (selection == 1) {
		printf(" Monthly Booking Summary Report for %s %d\n", monthNames[month], year);
	}
	else {
		printf(" Yearly Booking Summary Report for the year %d\n", year);
	}
	printf("=================================================\n\n");
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
		scanf(" %d", &select);
		rewind(stdin);
	} while (!(select == 1 || select == 2));

	if (select == 2) return;

	// report type
	char report[30];
	if (selection == 1) {
		strcpy(report, "MonthlyBookingReport.txt");
	}
	else {
		strcpy(report, "YearlyBookingReport.txt");
	}
	// write into file
	FILE* fp2 = fopen(report, "w");

	if (fp2 == NULL) {
		printf("Unable to open file\n");
		printf("Enter Any Key to continue...");
		rewind(stdin);
		while (getc(stdin) != '\n');
		return;
	}

	if (selection == 1) {
		fprintf(fp2, " Monthly Booking Summary Report for %s %d\n", monthNames[month], year);
	}
	else {
		fprintf(fp2, " Yearly Booking Summary Report for the year %d\n", year);
	}
	fprintf(fp2, "==================================================\n\n");
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


	printf("\nSuccessfuly generate a Text File Report: %s\n", report);

	fclose(fp2);
	printf("Enter Any Key to continue...");
	rewind(stdin);
	while (getc(stdin) != '\n');
	return;
}

bool schedulingData(int trainID, char purpose[], int bookingNum, double* price) {
	availableSeats(0);
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
	char contn = ' ';

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

	system("cls");
	bookingLogo();
	while (1) {

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
			passwordRecoveryMember(&backMemberID);
			printf("\n");
			continue;
		}

		// read all records
		fseek(fp, 0, SEEK_SET);
		while (!feof(fp)) {
			fscanf(fp, "%c%d | %[^|]| %d | %[^|]| %c | %[^|]| %[^\n]\n", &member.frontMemberID, &member.backMemberID, &member.name, &member.password, &member.passRecovery, &member.gender, &member.IC, &member.contactNumber);
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

		while (1) {
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
			else if (contn == 'Y' || contn == 'y') {
				break;
			}
		};

	}
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

	while (1) {
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
	};
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

	char coach;
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

void removeSeat(int trainID, int bookingNum, char coach, char seat[]) {
	// remove a record
	int found = 0;


	FILE* fpTemp = fopen("availableSeat_Modify.bin", "wb");
	FILE* fp = fopen("availableSeat.bin", "rb");
	while (fread(&memberTemp2.book[bookingNum].trains, sizeof(TrainSchedule), 1, fp) == 1) {
		// compare train ID and booking ID
		if (memberTemp2.book[bookingNum].trains.trainID == trainID &&
			memberTemp2.book[bookingNum].trains.seats[0].coach == coach &&
			strcmp(memberTemp2.book[bookingNum].trains.seats[0].seatNumber, seat) == 0) {
			found = 1;
			continue;

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
