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
			staffMain();
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
		
		system("color 06");

		printf("                                ___________                .__            _________                  __                    \n");
		printf("                                \\__    ___/_______ _____   |__|  ____    /   _____/ ___.__.  _______/  |_   ____    _____  \n");
		printf("                                  |    |   \\_  __ \\ \\__ \\  |  | /    \\   \\_____  \\ <   |  | /  ___/\\   __\\_/ __ \\  /     \\ \n");
		printf("                                  |    |    |  | \\/ / __ \\_|  ||   |  \\  /        \\ \\___  | \\___ \\  |  |  \\  ___/ |  Y Y  \\ \n");
		printf("                                  |____|    |__|   (____  /|__||___|  / /_______  / / ____|/____  > |__|   \\___  >|__|_|  / \n");
		printf("                                                        \\/          \\/          \\/  \\/          \\/             \\/       \\/  \n");

		printf("_____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ ____\n");
		printf("\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\____\\\\___\\\n");

		printf("  __         ____  ____   __   ____  ____                                                 ____        _  _  ____  _  _  ____  ____  ____      \n");
		printf(" /  \\       / ___)(_  _) / _\\ (  __)(  __)                                               (___ \\      ( \\/ )(  __)( \\/ )(  _ \\(  __)(  _ \\\n");
		printf("(_/ /   _   \\___ \\  )(  /    \\ ) _)  ) _)                                                 / __/  _   / \\/ \\ ) _) / \\/ \\ ) _ ( ) _)  )   / \n");
		printf(" (__)  (_)  (____/ (__) \\_/\\_/(__)  (__)                                                 (____) (_)  \\_)(_/(____)\\_)(_/(____/(____)(__\\_)  \n");


		printf(" ____        ____   ___  _  _  ____  ____  _  _  __     __   __ _   ___                    ___        ____   __    __   __ _   __   __ _   ___      \n");
		printf("(__  \\      / ___) / __)/ )( \\(  __)(    \\/ )( \\(  )   (  ) (  ( \\ / __)                  / _ \\      (  _ \\ /  \\  /  \\ (  / ) (  ) (  ( \\ / __)\n");
		printf(" (__ (  _   \\___ \\( (__ ) __ ( ) _)  ) D () \\/ (/ (_/\\  )(  /    /( (_ \\                 (__  (  _    ) _ ((  O )(  O ) )  (   )(  /    /( (_ \\    \n");
		printf("(____/ (_)  (____/ \\___)\\_)(_/(____)(____/\\____/\\____/ (__) \\_)__) \\___/                   (__/ (_)  (____/ \\__/  \\__/ (__\\_) (__) \\_)__) \\___/\n");


		printf("  ___        ____  _  _   __   ____ \n");
		printf(" / __)      (  __)( \\/ ) (  ) (_  _)\n");
		printf("(___ \\  _    ) _)  )  (   )(    )(  \n");
		printf("(____/ (_)  (____)(_/\\_) (__)  (__) \n");

		//printf("Staff Mode ------------------------------------------------------------------- 1\n");
		//printf("Member Mode ------------------------------------------------------------------ 2\n");
		//printf("Train Scheduling Mode -------------------------------------------------------- 3\n");
		//printf("Ticket Booking Mode ---------------------------------------------------------- 4\n");
		//printf("Exit ------------------------------------------------------------------------- 5\n\n");

		printf("\nEnter Mode: ");
		scanf(" %d", &mode);
		rewind(stdin);


	} while (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5);
	return mode;
}
