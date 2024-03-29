#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int menu();
void staffMain();
void memberMain();
void schedulingMain();
void bookingMain();

void main() {
	
	int mode;
	while (1) {
		mode = menu();
		switch (mode) {
		case 1:
			//staffMain();
			break;
		case 2:
			memberMain();
			break;
		case 3:
			schedulingMain();
			break;
		case 4:
			bookingMain();
			break;
		default:
			exit(-1);
			break;
		}
	}
}

int menu() {
	int mode;
	do {
		system("cls");
		printf("==============================\n");
		printf("         Select Mode\n");
		printf("==============================\n\n");

		printf("Staff Mode ----------------- 1\n");
		printf("Member Mode ---------------- 2\n");
		printf("Train Scheduling Mode ------ 3\n");
		printf("Ticket Booking Mode -------- 4\n");
		printf("Exit ----------------------- 5\n\n");
		printf("Enter Mode ----------------- ");
		scanf("%d", &mode);
		rewind(stdin);
	} while (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5);
	return mode;
}