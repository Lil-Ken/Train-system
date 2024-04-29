#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#pragma warning (disable:4996)

int memberMenu();
void addMember();
void searchMember();
void modifyMember();
void displayMember();
void deleteMember();
void passwordRecoveryMember();
void memberID(int* id);
void rewardPointVoucher(double quantity, int* point);
bool loginStaffMem();
int validateName(const char* name);
int validatePassword(int password);
int validateGender(char gender);
int validateIC(const char* IC);
int validateContactNumber(const char* contactNumber);
int validatePassRec(const char* passRec);

typedef struct {
	char  name[51], frontID, position[51], fatherName[51], pass[7];
	int  backID;

}staffinfo;

typedef struct {
	char bookingId[10], trainID[10];

}Booking;

struct Member {
	char frontMemberID, name[30], gender, IC[17], contactNumber[12], passRecovery[30];
	int password, backMemberID;
	Booking booking;
};

staffinfo staffs;

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
	struct Member member;
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
	struct Member member;

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
	struct Member member;
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
	struct Member member;

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
	struct Member member;
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
	struct Member member;
	char frontID, cnt, passrecov[30];
	int backID, found = 0;

	FILE* fp;
	fp = fopen("member.txt", "r");

	if (fp == NULL ) {
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
		if (frontID == member.frontMemberID && backID == member.backMemberID && strcmp(passrecov, member.passRecovery)  == 0){
			found = 1;
			printf("This is your password : %d.\n", member.password);
		}
	}
	
	if (found == 0) {
		printf("\nInvalid Member, Please try again.\n");
	}

	fclose(fp);

}

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
	struct Member member;
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
