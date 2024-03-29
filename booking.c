#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int bookingMenu();
void addBooking();
void searchBooking();
void modifyBooking();
void displayBooking();
int loginMember();
void paymentMethod();
int bookingNumber();
void addBookingNumber();
void bookingID();

// 1. validation for every input
// 2. modify system pause to press enter to continue  -  while( cont != '\n')
// 3. add more 2 function(chatgpt)

struct Date {
	int day, month, year;
};

typedef struct {
	char frontBookingID, trainID[10], seatNumber[5], coach, paymentInfo[20], ticketStatus[10];
	struct Date bookingDate, departureDate;
	int quantity, backBookingID;
	double amount;
}Booking;


typedef struct {
	char frontMemberID;
	Booking book[100];
	int backMemberID, password;
}Member;
Member member[100];

int loginNum = 0, bookingNum = 0;
char ctn;

void bookingMain() {
	int mode;
	strcpy(member[0].book[0].trainID, "T1001");

	loginNum = loginMember();
	bookingNum = bookingNumber(); 
	
	while (1) {
		mode = bookingMenu();
		switch (mode) {
		case 1:
			addBooking();
			break;
		case 2:
			searchBooking();
			break;
		case 3:
			modifyBooking();
			break;
		case 4:
			displayBooking();
			break;
		default:
			return;
		}
	}
}

int bookingMenu() {
	int mode;
	do{
		system("cls");
		printf("==============================\n");
		printf("       Select Function\n");
		printf("==============================\n\n");

		printf("Add Booking ---------------- 1\n");
		printf("Search Booking ------------- 2\n");
		printf("Modify Booking ------------- 3\n");
		printf("Display Booking ------------ 4\n");
		printf("Back ----------------------- 5\n\n");
		printf("Enter Number --------------- ");
		scanf(" %d", &mode);
		rewind(stdin);
	} while (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5);

	return mode;
}

void addBooking() {
	char comfirm;
	FILE* fp = fopen("Booking.bin", "ab");

	if (fp == NULL) {
		printf("Unable to open file!");
		system("pause");
		return;
	}
	
	// generate a new booking ID (1000)
	bookingID();

	system("cls");

	// booking ID
	member[loginNum].book[bookingNum].frontBookingID = 'B';
	//if (member[loginNum].book[bookingNum].backBookingID != 1001)
	//	addBookingID();

		
	printf("Your Booking ID is %c%d\n", member[loginNum].book[bookingNum].frontBookingID,
		member[loginNum].book[bookingNum].backBookingID);

	// user input
	printf("Enter booking date (DD/MM/YYYY): ");
	scanf("%02d/%02d/%d", &member[loginNum].book[bookingNum].bookingDate.day,
		&member[loginNum].book[bookingNum].bookingDate.month,
		&member[loginNum].book[bookingNum].bookingDate.year);
	rewind(stdin);
	printf("Enter departure date (DD/MM/YYYY): ");
	scanf("%02d/%02d/%d", &member[loginNum].book[bookingNum].departureDate.day,
		&member[loginNum].book[bookingNum].departureDate.month,
		&member[loginNum].book[bookingNum].departureDate.year);
	rewind(stdin);

	// maybe can view the available seat
	printf("Enter seat number: ");
	gets(member[loginNum].book[bookingNum].seatNumber);
	printf("Enter coach: ");
	scanf(" %c", &member[loginNum].book[bookingNum].coach);
	rewind(stdin);
	printf("Enter quantity: ");
	scanf(" %d", &member[loginNum].book[bookingNum].quantity);
	rewind(stdin);

	// choose payment method
	paymentMethod();
		
	// auto calculate amount
	printf("Enter amount: ");
	scanf(" %lf", &member[loginNum].book[bookingNum].amount);
	rewind(stdin);
	strcpy(member[loginNum].book[bookingNum].ticketStatus, "Booked");

	do{
		printf("\nComfirm Booking (Y/N): ");
		scanf(" %c", &comfirm);

		// Comfirmed Booking
		if (comfirm == 'Y' || comfirm == 'y'){
			fwrite(&member[loginNum].book[bookingNum], sizeof(Booking), 1, fp);
			addBookingNumber();
		}
	} while (!(comfirm == 'N' || comfirm == 'n' || comfirm == 'Y' || comfirm == 'y'));
		

	fclose(fp);

	return;
}

void searchBooking() {
	char frontBookingID;
	int backBookingID;
	system("cls");
	printf("Enter Booking ID to search: ");
	scanf(" %c%d", &frontBookingID, &backBookingID);

	FILE* fp;
	fp = fopen("Booking.bin", "rb");

	if (fp == NULL) {
		printf("Unable to open file!\n");
		system("pause");
		return;
	}
	
	int cnt = 0;
	while (fread(&member[loginNum].book[cnt], sizeof(Booking), 1, fp) == 1) {

		if (member[loginNum].book[cnt].frontBookingID == frontBookingID && member[loginNum].book[cnt].backBookingID == backBookingID) {

			printf("\n");
			for (int i = 0; i < 135; i++)
				printf("=");
			printf("\n");
			printf("%-15s%-15s%-15s%-15s%-15s%-15s%-16s%-16s%-16s\n", "Train ID", "Seat Number", "Coach", "Payment Info", "Ticket Status", "Booking Date", "Departure Date", "Quantity", "Amount");
			for (int i = 0; i < 135; i++)
				printf("=");
			printf("\n");

			printf("\n%-15s%-15s", member[loginNum].book[cnt].trainID, member[loginNum].book[cnt].seatNumber);
			printf("%-15c%-15s%-15s", member[loginNum].book[cnt].coach, member[loginNum].book[cnt].paymentInfo,
				member[loginNum].book[cnt].ticketStatus);
			printf("%02d/%02d/%04d     %02d/%02d/%04d      ", member[loginNum].book[cnt].bookingDate.day, member[loginNum].book[cnt].bookingDate.month,
				member[loginNum].book[cnt].bookingDate.year, member[loginNum].book[cnt].departureDate.day, member[loginNum].book[cnt].departureDate.month,
				member[loginNum].book[cnt].departureDate.year);
			printf("%-16d%-16.2f\n", member[loginNum].book[cnt].quantity, member[loginNum].book[cnt].amount);
			system("pause");
			return;
		}
		cnt++;
	}
	printf("Ticket not found\n");
	system("pause");

	fclose(fp);
	return;
}

void modifyBooking() {
	int selection, backBookingID;
	char frontBookingID;
	int cnt = 0, found = 0;

	FILE* fp = fopen("Booking.bin", "rb");
	FILE* fp2 = fopen("Booking_Modify.bin", "wb");


	if (fp == NULL || fp2 == NULL) {
		printf("Unable to open file!\n");
		system("pause");
		return;
	}

	// display all data of booking
	displayBooking();

	printf("\n\nEnter Booking ID to modify: ");
	scanf(" %c%d", &frontBookingID, &backBookingID);

	// read all data in the file
	while (fread(&member[loginNum].book[cnt], sizeof(Booking), 1, fp) == 1){

		// check whether booking id correct or not
		if (member[loginNum].book[cnt].frontBookingID == frontBookingID && member[loginNum].book[cnt].backBookingID == backBookingID) {
			found = 1;

			// loop for modify more data
			do {
				// loop for validation
				do {
					printf("\nDate -------------------- 1\n");
					printf("Seat -------------------- 2\n");
					printf("Coach ------------------- 3\n");
					printf("Quantity ---------------- 4\n");
					printf("Cancel modify ----------- 5\n");
					printf("\nSelect a field to modify: ");
					scanf(" %d", &selection);

				} while (!(selection == 1 || selection == 2 || selection == 3 || selection == 4 || selection == 5));

				switch (selection) {
				case 1:
					printf("Enter booking date (DD/MM/YYYY): ");
					scanf("%02d/%02d/%d", &member[loginNum].book[cnt].bookingDate.day,
						&member[loginNum].book[cnt].bookingDate.month,
						&member[loginNum].book[cnt].bookingDate.year);
					rewind(stdin);
					printf("Enter departure date (DD/MM/YYYY): ");
					scanf("%02d/%02d/%d", &member[loginNum].book[cnt].departureDate.day,
						&member[loginNum].book[cnt].departureDate.month,
						&member[loginNum].book[cnt].departureDate.year);
					rewind(stdin);
					break;
				case 2:
					printf("Enter seat number: ");
					scanf("%s", member[loginNum].book[cnt].seatNumber);
					rewind(stdin);
					break;
				case 3:
					printf("Enter coach: ");
					scanf(" %c", &member[loginNum].book[cnt].coach);
					rewind(stdin);
					break;
				case 4:
					printf("Enter quantity: ");
					scanf(" %d", &member[loginNum].book[cnt].quantity);
					rewind(stdin);
					break;
				default:
					break;
				}

				// write modified data into the temporary file
				fwrite(&member[loginNum].book[cnt], sizeof(Booking), 1, fp2);

				printf("Modify more (Y/N): ");
				scanf(" %c", &ctn);
			} while (ctn == 'Y' || ctn == 'y');
		}
		else {
			// write the original data into temporary file
			fwrite(&member[loginNum].book[cnt], sizeof(Booking), 1, fp2);
		}

		cnt++;
	}
	
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
	while (fread(&member[loginNum].book[cnt], sizeof(Booking), 1, fpt) == 1){
		// write it into original file
		fwrite(&member[loginNum].book[cnt], sizeof(Booking), 1, fpt2);
		cnt++;
	}

	fclose(fpt);
	fclose(fpt2);

	return;
}

void displayBooking() {
	int c = 0;
	FILE* fp;
	fp = fopen("Booking.bin", "rb");

	if (fp == NULL) {
		printf("Unable to open file!\n");
		system("pause");
		return;
	}

	system("cls");


	// read data and display 
	while (fread(&member[loginNum].book[c], sizeof(Booking), 1, fp) == 1) {

		// display header
		if (member[loginNum].book[c].backBookingID != 0 && c == 0) {
			printf("Member ID: %c%d\n\n", member[loginNum].frontMemberID, member[loginNum].backMemberID);

			for (int i = 0; i < 150; i++)
				printf("=");
			printf("\n");
			printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-16s%-16s%-16s\n", "Booking ID", "Train ID", "Seat Number", "Coach", "Payment Info", "Ticket Status", "Booking Date", "Departure Date", "Quantity", "Amount");
			for (int i = 0; i < 150; i++)
				printf("=");
			printf("\n");
		}
		
		// display data
		printf("\n%c%-14d%-15s%-15s", member[loginNum].book[c].frontBookingID, member[loginNum].book[c].backBookingID, member[loginNum].book[c].trainID,
			member[loginNum].book[c].seatNumber);
		printf("%-15c%-15s%-15s", member[loginNum].book[c].coach, member[loginNum].book[c].paymentInfo,
			member[loginNum].book[c].ticketStatus);
		printf("%02d/%02d/%04d     %02d/%02d/%04d      ", member[loginNum].book[c].bookingDate.day, member[loginNum].book[c].bookingDate.month, 
			member[loginNum].book[c].bookingDate.year, member[loginNum].book[c].departureDate.day, member[loginNum].book[c].departureDate.month, 
			member[loginNum].book[c].departureDate.year);
		printf("%-16d%-16.2f\n", member[loginNum].book[c].quantity, member[loginNum].book[c].amount);
		c++;
	}
	if (c == 0) 
		printf("Record not found!\n");
	

	system("pause");
	fclose(fp);
	return;
}

int loginMember() {
	int cnt = 0, backMemberID, pass;
	char frontMemberID;

	FILE* fp;
	fp = fopen("Member_Login.bin", "rb");

	if (fp == NULL) {
		printf("Record not found!\n");
		system("pause");
		return;
	}

	system("cls");
	printf("Enter your Member ID: ");
	scanf(" %c%d", &frontMemberID, &backMemberID);
	printf("Enter your password: ");
	scanf(" %d", &pass);

	while (fread(&member[cnt].frontMemberID, sizeof(char), 1, fp) == 1
		&& fread(&member[cnt].backMemberID, sizeof(int), 1, fp) == 1
		&& fread(&member[cnt].password, sizeof(int), 1, fp) == 1)
	{
		
		if (member[cnt].frontMemberID == frontMemberID && member[cnt].backMemberID == backMemberID && member[cnt].password == pass) {
			printf("Successful login!\n");
			system("pause");
			return cnt;
		}
		cnt++;
	}
	if (!(member[cnt].frontMemberID == frontMemberID && member[cnt].backMemberID == backMemberID && member[cnt].password == pass)) {
		printf("\n*** Invalid MEMBER ID or PASSWORD ***\n");
		system("pause");
		main();
	}
	
	fclose(fp);
	return cnt;
}

void recordMemberBin(int cnt, int backMemberID, int pass) {
	FILE* fp;
	fp = fopen("Member_Login.bin", "wb");

	if (fp == NULL) {
		printf("Unable to open file!\n");
		system("pause");
		return;
	}

	member[cnt].frontMemberID = 'M';
	member[cnt].backMemberID = backMemberID;
	member[cnt].password = pass;

	fwrite(&member[cnt].frontMemberID, sizeof(char), 1, fp);
	fwrite(&member[cnt].backMemberID, sizeof(int), 1, fp);
	fwrite(&member[cnt].password, sizeof(int), 1, fp);

	fclose(fp);
	return;
}

void paymentMethod() {
	int method;

	printf("\n1. Credit Card\n");
	printf("2. Debit Card\n");
	printf("3. Cash\n");
	printf("4. Bank Transfer\n");
	printf("5. Touch n Go\n");

	do{
		printf("Select payment method: ");
		scanf(" %d", &method);
		if (!(method == 1 || method == 2 || method == 3 || method == 4 || method == 5)) {
			printf("\n***Invalid Number***\n");
			printf("Select payment method again: ");
			scanf(" %c", &ctn);
		}
	} while (ctn == '\n');


	switch (method){
	case 1:
		strcpy(member[loginNum].book[bookingNum].paymentInfo, "Credit Card");
		break;
	case 2:
		strcpy(member[loginNum].book[bookingNum].paymentInfo, "Debit Card");
		break;
	case 3:
		strcpy(member[loginNum].book[bookingNum].paymentInfo, "Cash");
		break;
	case 4:
		strcpy(member[loginNum].book[bookingNum].paymentInfo, "Bank Transfer");
		break;
	case 5:
		strcpy(member[loginNum].book[bookingNum].paymentInfo, "Touch n Go");
		break;
	default:
		break;
	}
	
	return;
}

int bookingNumber() {
	int number;

	FILE* fpt = fopen("Booking.bin", "rb");
	FILE* fp, *fp1;

	// if doesn't any booking record
	if (fpt == NULL || fread(&member[loginNum].book[bookingNum], sizeof(Booking), 1, fpt) != 1){
		fp = fopen("booking_Number.bin", "wb");

		if (fp == NULL) {
			printf("Unable to open file\n");
			system("pause");
			return;
		}

		number = 0;
		fwrite(&number, sizeof(int), 1, fp); // write the booking number

		fclose(fp);
		return number;
	}
	else {
		fp1 = fopen("booking_Number.bin", "rb");

		if (fp1 == NULL) {
			printf("Unable to open file\n");
			system("pause");
			return;
		}

		fread(&number, sizeof(int), 1, fp1);

		fclose(fpt);
		fclose(fp1);
		return number;
	}

	return;
}

void addBookingNumber() {
	int number;
	FILE* fp, * fp1;

	// if booking record already exist
	fp = fopen("booking_Number.bin", "rb");

	if (fp == NULL) {
		printf("Unable to open file\n");
		system("pause");
		return;
	}

	fread(&number, sizeof(int), 1, fp); // read the current booking number

	fclose(fp);


	fp1 = fopen("booking_Number.bin", "wb");

	if (fp1 == NULL) {
		printf("Unable to open file\n");
		system("pause");
		return;
	}

	number++;
	fwrite(&number, sizeof(int), 1, fp1); // write increased number

	fclose(fp1);
			
	return;
}

void bookingID() {
	int number;
	FILE* fp = fopen("booking_Number.bin", "rb");

	if (fp == NULL) {
		printf("Unable to open file");
		system("pause");
		return;
	}

	fread(&number, sizeof(int), 1, fp);

	// if don't have records
	if (number == 0)
		member[loginNum].book[number].backBookingID = 1001;
	else member[loginNum].book[number].backBookingID = 1001 + number;

	fclose(fp);
	return;
}

//void addBookingID() {
//	FILE* fp;
//	fp = fopen("Booking.bin", "rb");
//
//
//	if (fp == NULL) {
//		printf("Unable to open file");
//		system("pause");
//		return;
//	}
//
//	fread(&member[loginNum].book[bookingNum], sizeof(Booking), 1, fp);
//
//	member[loginNum].book[bookingNum].backBookingID++;
//
//	fclose(fp);
//
//	return;
//}