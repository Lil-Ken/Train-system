#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#pragma warning(disable:4996)

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

// Schldule
void scheduleMenu(int* mode);
void searchSchedule();
void modifySchedule();
int addSchedule(int trainIDCounter);
void displaySchedule();
void deleteSchedule();
void scheduleReport();

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
bool schedulingData(int trainID, char purpose[], int bookingNum, double *price);
void paymentMethod(int bookingNum);
int bookingID_Num(int* id);
void displaySeat(int trainID);
bool seat(int bookingNum, int count, int mode);
void modifySeat(int mode, int bookingNum, int count, bool* valid);
void bookingLogo();

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
				do{
					system("cls");
					printf("Enter Train ID that you want to view seats (Enter 0 to view train schedule): T");
					scanf("%d", &trainID);
					rewind(stdin);

					if (trainID <= 1000 || trainID >= 10000){
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
	else if (loginMode == 2){
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
void bookingMenu(int *loginMode) {
	do{
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
	do{
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

void bookingMenuMember(int *mode) {
	do{
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
	do{
		printf("Enter Train ID");
		if (found != 1) {
			printf(" (Enter 0 to view train schedule): T");
		}
		else printf(": T");
		scanf(" %d", &member.book[bookingNum].trains.trainID);
		rewind(stdin);

		// display train information
		if (member.book[bookingNum].trains.trainID == 0 && found != 1){
			found = 1;
			valid = schedulingData(member.book[bookingNum].trains.trainID, "display", bookingNum, &price);
			printf("\n");
			continue;
		}
		// validate train ID
		else if (member.book[bookingNum].trains.trainID > 1000 || member.book[bookingNum].trains.trainID < 10000){
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
	do{
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
	for (int i = 0; i < member.book[bookingNum].quantity; i++){ // based on quantity
		do{ 
			printf("\n");

			// Coach
			do{ 
				printf("[%d] Enter coach: ", i+1);
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
			do{ 
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
				for (int d = 0; d < i; d++){
					if (strcmp(member.book[bookingNum].trains.seats[d].seatNumber, member.book[bookingNum].trains.seats[i].seatNumber) == 0 &&
						member.book[bookingNum].trains.seats[d].coach == member.book[bookingNum].trains.seats[i].coach){
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

	do{
		printf("\nConfirm Booking (Y/N): ");
		scanf(" %c", &confirm);
		rewind(stdin);
		// Confirmed Booking
		if (confirm == 'Y' || confirm == 'y'){
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
					else{
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
		   fread(&memberTemp.book[cnt], sizeof(Booking), 1, fp) == 1){

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

				do{
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
		if (strcmp(mode, "staff") == 0) printf("%c%-14d", MEMBER_FRONT_ID ,memberTemp.backMemberID);
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

void cancelBooking(){
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

			do{
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

	do{
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

bool schedulingData(int trainID, char purpose[], int bookingNum, double *price) {

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

bool loginMember(int * ID) {
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

	do{
		system("cls");
		bookingLogo();
		do{
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

		if (pass == 0){
			if (found == 1){
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
			if (contn == 'N' || contn == 'n'){
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
			if (!(staffID > 1000 && staffID < 10000)){
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
			if (found == 1){
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
			if (staffID == staffs.backID && strcmp(pass, staffs.pass) == 0){
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

	do{
		printf("Select payment method: ");
		scanf(" %d", &method);
		rewind(stdin);
		if (!(method == 1 || method == 2 || method == 3 || method == 4 || method == 5)) {
			printf("\n***Invalid Number***\n");
		}
	} while (!(method == 1 || method == 2 || method == 3 || method == 4 || method == 5));


	// assign value
	switch (method){
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


int bookingID_Num(int *id) {
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
		switch (d){
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
			if (valid == 1){
				int bookingNum = 0;
				rewind(fp);
				while (fread(&memberTemp2.book[bookingNum].trains, sizeof(TrainSchedule), 1, fp) == 1) {
					for (int count = 0; count < (sizeof(memberTemp2.book[bookingNum].trains.seats)/sizeof(memberTemp2.book[bookingNum].trains.seats[0])); count++) {
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

	if (fp2 == NULL || fp == NULL){
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

	if (mode == 0){
		// compare all data (seat availability)
		fseek(fp, 0, SEEK_SET);
		while (fread(&memberTemp.book[bookingNum].trains, sizeof(TrainSchedule), 1, fp) == 1) {
			// compare train id
			if (member.book[bookingNum].trains.trainID == memberTemp.book[bookingNum].trains.trainID) {
				for (int i = 0; i < member.book[bookingNum].quantity; i++){
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
	if (mode == 1){
		fwrite(&member.book[bookingNum].trains, sizeof(TrainSchedule), 1, fp2);
		fclose(fp);
		fclose(fp2);
		return true;
	}

	return true;
}

void modifySeat(int mode, int bookingNum, int seatNum, bool *valid) {
	// mode 0 = check
	// mode 1 = modify
	int found = 0;

	if (mode == 0){
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
