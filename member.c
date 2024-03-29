#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable:4996)

int memberMenu();
void addMember();
void searchMember();
void modifyMember();
void displayMember();
void recordMemberBin(int cnt, int backMemberID, int pass);

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
	char conti;
	struct Member member;
	memberNum++;

	FILE* fp;
	fp = fopen("member.txt", "w");
	system("cls");


	member.backMemberID = 1000;

	do{
		// auto generate ID:
		member.frontMemberID = 'M';
		member.backMemberID++;

		// get user input
		printf("Enter your Name:");
		scanf("%s", &member.name);
		rewind(stdin);
		printf("Enter your password:");
		scanf("%d", &member.password);
		rewind(stdin);
		printf("Enter your gender (M/F):");
		scanf("%c", &member.gender);
		rewind(stdin);
		printf("Enter your IC:");
		scanf("%s", &member.IC);
		rewind(stdin);
		printf("Enter your contact number:");
		scanf("%s", &member.contactNumber);
		rewind(stdin);
		printf("Do you want to add more (Y/N): ");
		scanf("%c", &conti);
		rewind(stdin);

		printf("Success to create a acount!!!\nYour Member ID: %c%d\n", member.frontMemberID, member.backMemberID);

		// record in file
		fprintf(fp, "%c%d %s %d %c %s %s\n", member.frontMemberID, member.backMemberID, member.name, member.password, member.gender, member.IC, member.contactNumber);

		// record in booking file
		recordMemberBin(memberNum, member.backMemberID, member.password);
	} while (conti == 'y' || conti == 'Y');

	fclose(fp);
}

void searchMember() {

}

void modifyMember() {

}

void displayMember() {

}