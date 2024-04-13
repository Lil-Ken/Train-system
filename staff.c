#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)


int staffMenu();
int addStaff();
int searchStaff();
int modifyStaff();
int displayStaff();
int passwordRecovery();
int deleteStaff();
int staffid();

typedef struct {
	char  name[51], frontID, position[51];
	int pass, passwrec, backID;

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
	case 5:
		deleteStaff();
		break;
	case 7:
		passwordRecovery();
		break;
	default:
		break;
	}

}


int staffMenu() {
	int mode,num;


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
		printf("Back -------------------- 6\n");
		printf("Forgot Password --------- 7\n\n");
		printf("Enter Number --------------- ");
		scanf("%d", &mode); rewind(stdin);
	} while (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5 && mode != 6 && mode != 7);

	return mode;

}


int addStaff() {
	staffinfo staff;
	int exit,recovery;
	staff.frontID = 'S';
	
	
	
	do {
	
	
		
		FILE* stf;
		stf = fopen("staff.bin", "ab");

		if (stf == NULL) {
			printf("disable to open file");
			
			return;
		}
		staff.backID = staffid();
		
		printf("Your staff id is %c%d\n", staff.frontID,staff.backID);
		printf("Staff Name :");
		scanf("%[^\n]", staff.name);	rewind(stdin);
		printf("Staff position :");
		scanf("%s", staff.position);	rewind(stdin);
		printf("Password :");
		scanf("%d", &staff.pass);
		rewind(stdin);
		printf("Set a 6 number be your password recovery : ");
		scanf("%d", &staff.passwrec);
		printf("Enter again the 6 number : ");
		scanf("%d", &recovery);
		while (staff.passwrec != recovery) {
			printf("Enter wrong,please enter again\n");
			printf("Set a 6 number be your password recovery : ");
			scanf("%d", &staff.passwrec);
			printf("Enter again the 6 number : ");
			scanf("%d", &recovery);
		}

		fwrite(&staff, sizeof(staffinfo), 1, stf);

		fclose(stf);

		printf("\n==============================\n");
		printf("     Add staff completed\n");
		printf("==============================\n\n");
		printf("[1] Countinue \n");
		printf("[2] Exit\n :");
		scanf("%d", &exit); rewind(stdin);
		if (exit != 1 && exit != 2) {
			printf("Input not valid,please try again : ");
			scanf("%d", &exit); rewind(stdin);
		}
	} while (exit == 1);

	
		system("pause");

}


int searchStaff() {
	char frontid;
	int backid;
	staffinfo staff;
	FILE* stf;
	stf = fopen("staff.bin", "rb");

	if (stf == NULL) {
		printf("Unabale to open file");
		return;
	}


	printf("Please enter your id ");
	scanf("%c%d",&frontid,&backid);

	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
		if (backid == staff.backID) {
			printf("\n\nID \t NAME \t\t POSITION \t PASSWORD \n");
			printf("---------------------------------------\n");
			printf("%c%d \t %s \t\t %s \t %d\n", staff.frontID, staff.backID, staff.name, staff.position, staff.pass);
		}
		
	}


}



int modifyStaff() {
	staffinfo staff;
	char frontid, ctn;
	int backid,selection,num=0;

	FILE* stf;
	FILE* stf1;
	stf = fopen("staff.bin", "rb");
	stf1 = fopen("staffmodify.bin", "wb");
	if (stf == NULL || stf1 ==NULL) {
		printf("Unabale to open file");
		return;
	}
	printf("Enter the staff ID need to modify : ");
	scanf("%c%d", &frontid, &backid); rewind(stdin);


	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
		if (staff.backID == backid) {
			num = 1;
			do {
			printf("\n\nID \t NAME \t\t POSITION \t PASSWORD \n");
			printf("---------------------------------------\n");
			printf("%c%d \t %s \t\t %s \t %d\n", staff.frontID, staff.backID, staff.name, staff.position, staff.pass);
			
			
				printf("\nName -------------------- 1\n");
				printf("password ---------------- 2\n");
				printf("position ---------------- 3\n");
				printf("Cancel modify ----------- 4\n");
				printf("\nSelect a field to modify: ");
				scanf(" %d", &selection); rewind(stdin);

				switch (selection) {
				case 1:
					printf("Enter new name : ");
					scanf("%[^\n]", &staff.name);
					rewind(stdin);
					break;
				case 2:
					printf("Enter new password : ");
					scanf("%d", &staff.pass);
					rewind(stdin);
					break;
				case 3:
					printf("Enter new position : ");
					scanf("%s", &staff.position);
					rewind(stdin);
					break;
				default:
					break;
				}
				printf("Need to modify more (Y/N) : ");
				scanf("%c", &ctn);
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
	}

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

int passwordRecovery() {
	staffinfo staff;
	int backid, num,num1=0;
	char frontid;
	FILE* stf;
	stf = fopen("staff.bin", "rb");

	if (stf == NULL) {
		printf("Disable to open file");
		return;
	}

	
		printf("Enter your staff ID : ");
		scanf("%c%d", &frontid, &backid); rewind(stdin);

		printf("Enter your 6 digit number : ");
		scanf("%d", &num); rewind(stdin);

		while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
			if (num == staff.passwrec && backid==staff.backID) {
				num1 = 1;
				printf("\n\nID \t NAME \t\t POSITION \t PASSWORD \n");
				printf("%c%d \t %s \t %s \t\t %d\n", staff.frontID, staff.backID, staff.name, staff.position, staff.pass);
			}

		}
		if (num1 == 0) {
			printf("Invalid, please try again");
		}

	fclose(stf);

}

int deleteStaff() {
	staffinfo staff;
	int backid, passw,num=0;
	char frontid,ctn;

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

	printf("Enter Staff password : ");
	scanf("%d", &passw); rewind(stdin);

	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0)
	{
		if (backid == staff.backID && passw == staff.pass) {
			num = 1;
			printf("Comfirm delete (Y/N) : ");
			scanf("%c", &ctn); rewind(stdin);

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


	}
	else printf("Invalid ID please try again");

	fclose(stf);
	fclose(stf1);
}

int staffid() {
	staffinfo staff;
	int num,num2;
	
	/*FILE* stf2;
	stf2 = fopen("staddid.bin", "wb");
	if (stf2 == NULL) {
		printf("Unable to open file");
		system("pause");
		return;
	}
	num2 = 0;
	fwrite(&num2, sizeof(num2), 1, stf2);

	fclose(stf2);*/


	FILE* stf;
	
	stf = fopen("staddid.bin", "rb");
	if (stf == NULL) {
		printf("Unable to open file");
		system("pause");
		return;
	}
	fread(&num, sizeof(int), 1, stf);
	
	;
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
	stf1 = fopen("staddid.bin", "wb");
	if (stf1 == NULL) {
		printf("Unable to open file");
		system("pause");
		return;
	}
	fwrite(&num, sizeof(num), 1, stf1);
	
	fclose(stf1);
	return staff.backID;
}

