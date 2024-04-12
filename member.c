#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable:4996)

int memberMenu();
void addMember();
void searchMember();
void modifyMember();
void displayMember();
void recordMemberBin(int cnt, int backMemberID);

typedef struct {
	char bookingId[10], trainID[10];

}Booking;

struct Member {
	char frontMemberID, name[30], passwordrec[10], gender, IC[15], contactNumber[12];
	int password, backMemberID;
	Booking booking;
};

memberNum = 0;

void memberMain() {
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
		printf("Back --------------------- 5\n\n");
		printf("Enter Number ------------- ");
		scanf(" %d", &mode);
	} while (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5);

	return mode;

}

void addMember() {
	char cont;
	struct Member member;
	memberNum++;

	FILE* fp;
	fp = fopen("member.txt", "w");
	system("cls");


	member.backMemberID = 1000;

	do {
		// auto generate ID:
		member.frontMemberID = 'M';
		member.backMemberID++;

		// get user input
		printf("Enter your Name:");
		rewind(stdin);
		scanf("%[^\n]", &member.name);
		printf("Enter your password:");
		rewind(stdin);
		scanf("%d", &member.password);
		printf("Enter your gender (M/F):");
		rewind(stdin);
		scanf("%c", & member.gender);
		printf("Enter your IC:");
		rewind(stdin);
		scanf("%s", &member.IC);
		printf("Enter your contact number:");
		rewind(stdin);
		scanf("%s", &member.contactNumber);
		printf("Do you want to add more (Y to add more): ");
		rewind(stdin);
		scanf("%c", &cont);

		printf("Success to create a account!!!\nYour Member ID: %c%d\n\n", member.frontMemberID, member.backMemberID);

		// record in file
		fprintf(fp, "%c%d | %s | %d | %c | %s | %s\n", member.frontMemberID, member.backMemberID, member.name, member.password, member.gender, member.IC, member.contactNumber);

		// record in booking file
		
	} while (cont == 'y' || cont == 'Y');

	fclose(fp);
}

void searchMember() {
	struct Member member;

	FILE* fp;
	fp = fopen("member.txt", "w");
	system("cls");

	while (!feof(fp)) {
		fscanf(fp, "%[^|]%d %[^|] %d %c %[^|] %[^|]\n", &member.frontMemberID, &member.backMemberID, &member.name, &member.password, &member.gender, &member.IC, &member.contactNumber);	
	}
}

void modifyMember() {
	
	char frontID, ctn;
	int backID, found = 0, selection;
	struct Member member;

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
	scanf("%c%d", &frontID, &backID);

	while (!feof(fp)){
		fscanf(fp, "%c%d | %[^|]| %d | %c | %[^|]| %[^\n]\n", &member.frontMemberID, &member.backMemberID, &member.name, &member.password, &member.gender, &member.IC, &member.contactNumber);
		if (frontID == 'M' && backID == member.backMemberID){
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
					scanf("%[\n]", member.name);
					rewind(stdin);
					break;
				case 2:
					printf("Enter the new password:");
					scanf("%d", member.password);
					rewind(stdin);
					break;
				case 3:
					printf("Enter the new gender:");
					scanf("%c", member.gender);
					rewind(stdin);
					break;
				case 4:
					printf("Enter the new IC:");
					scanf("%s", member.IC);
					rewind(stdin);
					break;
				case 5:
					printf("Enter the new contact number:");
					scanf("%s", member.contactNumber);
					rewind(stdin);
				default:
					break;
				}

				// write modified data into the temporary file


				printf("Modify more (Y/N): ");
				scanf(" %c", &ctn);
			} while (ctn == 'Y' || ctn == 'y');
			fprintf(fp1, "%c%d | %s | %d | %c | %s | %s\n", member.frontMemberID, member.backMemberID, member.name, member.password, member.gender, member.IC, member.contactNumber);
		}
		else {
			fprintf(fp1, "%c%d | %s | %d | %c | %s | %s\n", member.frontMemberID, member.backMemberID, member.name, member.password, member.gender, member.IC, member.contactNumber);
		}

	}
	fclose(fp);
	fclose(fp1);

	fp = fopen("member.txt", "w");
	fp1 = fopen("memberModify.txt", "r");

	while (!feof(fp1)){
		fscanf(fp1, "%c%d | %[^|]| %d | %c | %[^|]| %[^\n]\n", &member.frontMemberID, &member.backMemberID, &member.name, &member.password, &member.gender, &member.IC, &member.contactNumber);
		fprintf(fp, "%c%d | %s | %d | %c | %s | %s\n", member.frontMemberID, member.backMemberID, member.name, member.password, member.gender, member.IC, member.contactNumber);
	}

	fclose(fp);
	fclose(fp1);
}


void displayMember() {

	struct Member member;

	FILE* fp;
	fp = fopen("member.txt", "r");
	system("cls");
	
	if (fp == NULL) {
		printf("Enable to open the file\n");
		return;
	}

	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Member ID", "Name", "Password", "Gender", "IC", "Contact Number");


	while (!feof(fp)) {
		fscanf(fp, "%c%d | %[^|]| %d | %c | %[^|]| %[^\n]\n", &member.frontMemberID, &member.backMemberID, &member.name, &member.password, &member.gender, &member.IC, &member.contactNumber);
		printf("%c%-13d %-14s %-14d %-14c %-14s %-14s\n", member.frontMemberID, member.backMemberID, member.name, member.password, member.gender, member.IC, member.contactNumber);

	}
	

	while (!feof(fp)){
		printf("%c%d %s %d %c %s %s\n", member.frontMemberID, member.backMemberID, member.name, member.password, member.gender, member.IC, member.contactNumber);
	}

	fclose(fp);

}
