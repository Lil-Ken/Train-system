//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#pragma warning(disable:4996)
//
//
//int staffMenu();
//int addStaff();
//int searchStaff();
//int modifyStaff();
//int displayStaff();
//
//typedef struct {
//	char staffID[10], name[30], position[30], passwordrec[10];
//	int password;
//}staffinfo;
//
//
//
//void main() {
//	int mode;
//	mode = staffMenu();
//	switch (mode) {
//	case 1:
//		addStaff();
//		break;
//	case 2:
//		searchStaff();
//		break;
//	case 3:
//		modifyStaff();
//		break;
//	case 4:
//		displayStaff();
//		break;
//	default:
//		break;
//	}
//
//}
//
//
//int staffMenu() {
//	int mode;
//	do {
//		system("cls");
//		printf("==============================\n");
//		printf("       Select Function\n");
//		printf("==============================\n\n");
//
//		printf("Add Staff --------------- 1\n");
//		printf("Search Staff ------------ 2\n");
//		printf("Modify Staff ------------ 3\n");
//		printf("Display Staff ----------- 4\n");
//		printf("Back ----------------------- 5\n\n");
//		printf("Enter Number --------------- ");
//		scanf("%d", &mode);
//	} while (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5);
//
//	return mode;
//
//}
//
//int addStaff() {
//	staffinfo staff;
//	int exit;
//
//	printf("Staff ID :");
//	scanf("%s", &staff.ID);
//	printf("Staff Name :");
//	scanf("%s", &staff.name);
//	printf("Staff position :");
//	scanf("%s", &staff.position);
//	printf("Password :");
//	scanf("%d", &staff.pass);
//
//	printf("\n==============================\n");
//	printf("     Add staff completed\n");
//	printf("==============================\n\n");
//	printf("[1] Countinue \n");
//	printf("[2] Exit\n :");
//	scanf("%d", &exit);
//
//	while (exit != 1 && exit != 2) {
//
//		printf("Input not valid,please try again : ");
//		scanf("%d", &exit);
//	}
//	if (exit == 1) {
//		main();
//	}
//	else if (exit == 2) {
//		system("pause");
//	}
//
//}
//
//
//int searchStaff() {
//
//}
//
//
//int modifyStaff() {
//
//}
//
//int displayStaff() {
//
//}