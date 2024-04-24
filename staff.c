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
	char  name[51], frontID, position[51], fatherName[51], pass[7];
	int  backID;

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
		printf("Back -------------------- 7\n\n");
		printf("Enter Number --------------- ");
		scanf("%d", &mode); rewind(stdin);
	} while (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5 && mode != 6 && mode != 7);

	return mode;

}


int addStaff() {
	staffinfo staff;
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
	staffinfo staff;
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
	staffinfo staff;
	char frontid, ctn;
	int backid, selection, num = 0,valid=0;

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
	staffinfo staff;
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

int passwordRecovery() {
	staffinfo staff;
	int backid, num1 = 0;
	char frontid, passrec[51];
	FILE* stf;
	stf = fopen("staff.bin", "rb");

	if (stf == NULL) {
		printf("Disable to open file");
		return;
	}

	printf("Enter  staff ID :S ");
	scanf("%c%d", &frontid, &backid); rewind(stdin);
	printf("Please enter your father name : ");
	scanf("%[^\n]", passrec);



	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0) {
		if (backid == staff.backID) {
			if (strcmp(passrec, staff.fatherName) == 0) {
				num1 = 1;

				printf("Your password is %s\n\n", staff.pass);

			}
		}

	}
	if (num1 == 0) {
		int try;
		printf("Invalid ID, please try again\n");

	}

	fclose(stf);
	system("pause");

}

int deleteStaff() {
	staffinfo staff;
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



	while (fread(&staff, sizeof(staffinfo), 1, stf) != 0)
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
	staffinfo staff;

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
	staffinfo staff;
	int backid, ot, othour = 0, num = 0;
	char frontid;
	double basic, allowance = 600.00, epf, socso, eis;
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
				do {
					printf("Please enter your basic pay : "); rewind(stdin);
					scanf("%lf", &basic);
				} while (basic < 0 || basic>10000000000000);

			} while (isdigit(basic) != 0);


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
		staffMain();

	}
	staffMain();

}

