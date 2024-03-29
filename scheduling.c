#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996)

int scheduleMenu();
void searchSchedule();
void modifySchedule();
void addSchedule();
void displaySchedule();

struct Time{
    int departureHour, departureMin;
    int arrivalHour, arrivalMin;
};

typedef struct {
    char trainID[10], departureStation[50], arrivalStation[50];
    struct Time time;
    int availableSeats;
} TrainSchedule;


void schedulingMain() {
    int mode;
    char choice;
    FILE* fptr = fopen("train_schedule.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file");
        return;
    }

    mode = scheduleMenu();
    switch (mode) {
    case 1:

        do {
            addSchedule(fptr);

            printf("Do you want to add another schedule? (Y/N): ");
            scanf(" %c", &choice);
        } while (choice == 'Y' || choice == 'y');
        break;
    case 2:
        searchSchedule();
        break;
    case 3:
        modifySchedule();
        break;
    case 4:
        displaySchedule();
        break;
    default:
        break;
    }


    fclose(fptr);
}

int scheduleMenu() {
    int mode;
    do {
        system("cls");
        printf("==============================\n");
        printf("       Select Function\n");
        printf("==============================\n\n");

        printf("Add Schedule --------------- 1\n");
        printf("Search Schedule ------------ 2\n");
        printf("Modify Schedule ------------ 3\n");
        printf("Display Schedule ----------- 4\n");
        printf("Back ----------------------- 5\n\n");
        printf("Enter Number --------------- ");
        scanf("%d", &mode);
    } while (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5);

    return mode;

}

void addSchedule() {
    TrainSchedule schedule;
    FILE* fptr = fopen("train_schedule.txt", "a");
    printf("Enter Train ID: ");
    scanf("%s", schedule.trainID);
    printf("Enter Departure Station: ");
    rewind(stdin);
    scanf("%s", schedule.departureStation);
    printf("Enter Arrival Station: ");
    rewind(stdin);
    scanf("%s", schedule.arrivalStation);
    printf("Enter Departure Time (HH:MM): ");
    rewind(stdin);
    scanf("%d:%d", schedule.time.departureHour, schedule.time.departureMin);
    printf("Enter Arrival Time (HH:MM): ");
    rewind(stdin);
    scanf("%d:%d", schedule.time.arrivalHour, schedule.time.arrivalMin);
    printf("Enter Available Seats: ");
    rewind(stdin);
    scanf("%d", &schedule.availableSeats);

    fprintf(fptr, "%s, %s, %s, %d:%d, %d:%d, %d\n",
        schedule.trainID,
        schedule.departureStation,
        schedule.arrivalStation,
        schedule.time.departureHour, 
        schedule.time.departureMin,
        schedule.time.arrivalHour, 
        schedule.time.arrivalMin,
        schedule.availableSeats);

    fclose(fptr);
}

void searchSchedule() {

}

void modifySchedule() {

}

void displaySchedule() {
    
}