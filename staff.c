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
int staffPayslip();

typedef struct {
	char  name[51], frontID, position[51];
	int pass, backID;

}staffinfo;



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
	case 7:
		passwordRecovery();
		break;
	default:
		break;
	}

}


int staffMenu() {
	int mode, num;


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
		printf("Forgot Password --------- 7\n");
		printf("Back -------------------- 8\n\n");
		printf("Enter Number --------------- ");
		scanf("%d", &mode); rewind(stdin);
	} while (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5 && mode != 6 && mode != 7 && mode!= 8);

	return mode;

}


int addStaff() {
	staffinfo staff;
	int exit ;
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
			printf("Password (6 degit number) :");
			scanf("%d", &staff.pass); rewind(stdin);
		} while (staff.pass <=99999 && staff.pass >= 1000000);

		fwrite(&staff, sizeof(staffinfo), 1, stf);

		fclose(stf);

		printf("\n==============================\n");
		printf("     Add staff completed\n");
		printf("==============================\n\n");
		printf("[1] Countinue add staff\n");
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


	printf("Please enter your id : ");
	scanf("%c%d", &frontid, &backid);

	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
		if (backid == staff.backID) {

			printf("\n\nID             NAME             POSITION    \n");
			printf("------------------------------------------------\n");
			printf("%c%-12d  %-15s  %-15s \n", staff.frontID, staff.backID, staff.name, staff.position);
			

		}

	}
	system("pause");
	return;

}


int modifyStaff() {
	staffinfo staff;
	char frontid, ctn;
	int backid, selection, num = 0;

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
				printf("%c%-12d  %-15s  %-15s  %-15d\n", staff.frontID, staff.backID, staff.name, staff.position, staff.pass);


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
				do {
					printf("Need to modify more (Y/N) : ");
					scanf("%c", &ctn);
				}while(ctn != 'Y' && ctn != 'y' && ctn != 'N' && ctn != 'n');
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
		printf("Unable to open file");
		system("pause");
		return;
	}

	printf("\n\nID             NAME             POSITION    \n");
	printf("------------------------------------------------\n");
	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
		printf("%c%-12d  %-15s  %-15s \n", staff.frontID, staff.backID, staff.name, staff.position);
	}
	fclose(stf);
	system("pause");
	return;
}

int passwordRecovery() {
	staffinfo staff;
	int backid, num1 = 0;
	char frontid;
	FILE* stf;
	stf = fopen("staff.bin", "rb");

	if (stf == NULL) {
		printf("Disable to open file");
		return;
	}


	printf("Enter your staff ID : ");
	scanf("%c%d", &frontid, &backid); rewind(stdin);
	

	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
		if (backid == staff.backID) {
			num1 = 1;
			printf("\n\nID             NAME             POSITION         PASSWORD \n");
			printf("-------------------------------------------------------------\n");
			printf("%c%-12d  %-15s  %-15s  %-15d\n", staff.frontID, staff.backID, staff.name, staff.position, staff.pass);
			system("pause");
		}

	}
	if (num1 == 0) {
		printf("Invalid, please try again");
	}

	fclose(stf);

}

int deleteStaff() {
	staffinfo staff;
	int backid, passw, num = 0;
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

		printf("\n\n\nDone Delete staff\n\n\n");

	}
	else printf("Invalid, please try again");

	fclose(stf);
	fclose(stf1);
}

int staffid() {
	staffinfo staff;
	
	int num=0;
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
	staffinfo staff;
	int backid,ot,othour=0,num=0;
	char frontid;
	double basic,allowance=600.00,epf,socso,eis;
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
		
				printf("Please enter your basic pay : "); rewind(stdin);
				scanf("%lf", &basic);

			
			
			do {
				printf("Do you OT in this month :\n"); rewind(stdin);
				printf("[1] YES\n");
				printf("[2] NO\n");
				scanf("%d", &ot);
			} while (ot != 1 && ot != 2);
			
			if (ot == 1) {
				printf("how many hour you OT : ");
				scanf("%d", &othour);
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
			printf("\t\t    |___|     /  /        \\  \\    |__|    \\_______/    |__|    |__|    |___|\n\n");

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
	}
}


