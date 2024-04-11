#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)


int staffMenu();
int addStaff();
int searchStaff();
int modifyStaff();
int displayStaff();
typedef struct {
	char  name[51], frontID, position[51];
	int pass, passwrec,backID;
}staffinfo;



void main() {
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
		printf("Back -------------------- 5\n\n");
		printf("Enter Number --------------- ");
		scanf("%d", &mode); rewind(stdin);
	} while (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5);

	return mode;

}

int addStaff() {
	staffinfo staff;
	int exit;
	staff.frontID = 'S';
	staff.backID = 1000;
	staff.backID++;

	FILE*stf;
	stf = fopen("staff.bin", "wb");
	
	if (stf == NULL) {
		printf("disable to open file");
		return;
	}

	
	
	printf("Staff Name :");
	scanf("%[^\n]", staff.name);	rewind(stdin); 
	printf("Staff position :");
	scanf("%s", staff.position);	rewind(stdin); 
	printf("Password :");
	scanf("%d", &staff.pass);
	rewind(stdin);

	fwrite(&staff, sizeof(staffinfo), 1, stf);

	fclose(stf);

	printf("\n==============================\n");
	printf("     Add staff completed\n");
	printf("==============================\n\n");
	printf("[1] Countinue \n");
	printf("[2] Exit\n :");
	scanf("%d", &exit); rewind(stdin); 

	while (exit != 1 && exit != 2) {

		printf("Input not valid,please try again : ");
		scanf("%d", &exit); rewind(stdin);
	}
	if (exit == 1) {
		addStaff();
	}

	else if (exit == 2) {
		system("pause");
	}

}


int searchStaff() {
	int id;
	staffinfo staff;
	FILE* stf;
	stf = fopen("staff.bin", "rb");

	if (stf == NULL) {
		printf("Unabale to open file");
		return;
	}


	printf("Please enter your id ");
	scanf("%d", &id);



}


int modifyStaff() {

}

int displayStaff() {
	staffinfo staff;
	FILE* stf;
	stf = fopen("staff.bin", "rb");

	if (stf == NULL) {
		printf("Unabale to open file");
		return;
	}

	printf("\n\nID \t NAME \t\t POSITION \t PASSWORD \n");
	printf("---------------------------------------\n");
	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
		printf("%c%d \t %s \t %s \t\t %d\n", staff.frontID,staff.backID,staff.name,staff.position,staff.pass);
	}
	fclose(stf);

}
