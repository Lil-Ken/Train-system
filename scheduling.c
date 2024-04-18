#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable: 4996)

int scheduleMenu();
void searchSchedule();
void modifySchedule();
int addSchedule(int trainIDCounter);
void displaySchedule();

int updateSeats = 500;

struct Time {
    int departureHour, departureMin;
    int arrivalHour, arrivalMin;
};

typedef struct {
    int trainID;
    char departureStation[50], arrivalStation[50];
    struct Time time;
    int availableSeats;
} TrainSchedule;


void main() {
    int mode;
    char choice;
    int updateTrainID = 1001;
    FILE* fptr = fopen("train_schedule.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file");
        return;
    }

    mode = scheduleMenu();
    switch (mode) {
    case 1:

        do {
            updateTrainID = addSchedule(updateTrainID);
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

int addSchedule(int updateTrainID) {
    FILE* fptr = fopen("train_schedule.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file\n");
        return updateTrainID;
    }
    TrainSchedule schedule;
    schedule.trainID = updateTrainID++;
    
    schedule.availableSeats = updateSeats;

    printf("Train ID: T%d\n", schedule.trainID);

    printf("Enter Departure Station: ");
    scanf("%s", schedule.departureStation);
    printf("Enter Arrival Station: ");
    scanf("%s", schedule.arrivalStation);
    printf("Enter Departure Time (HH:MM): ");
    scanf("%d:%d", &schedule.time.departureHour, &schedule.time.departureMin);
    printf("Enter Arrival Time (HH:MM): ");
    scanf("%d:%d", &schedule.time.arrivalHour, &schedule.time.arrivalMin);

    if (schedule.availableSeats <= 0) {
        printf("No available seats.\n");
        return updateTrainID;
    }

    printf("Available Seats: %d\n", schedule.availableSeats);

    

    fprintf(fptr, "T%d, %s, %s, %02d:%02d, %02d:%02d, %d\n",
        schedule.trainID,
        schedule.departureStation,
        schedule.arrivalStation,
        schedule.time.departureHour,
        schedule.time.departureMin,
        schedule.time.arrivalHour,
        schedule.time.arrivalMin,
        schedule.availableSeats);

    updateSeats--;

    fclose(fptr);
    return updateTrainID;
}



void searchSchedule() {
    int trainID;
    printf("Enter Train ID to search: T");
    scanf("%d", &trainID);

    FILE* fptr = fopen("train_schedule.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file\n");
        return;
    }

    TrainSchedule schedule;
    int found = 0;

    printf("\nSearch Results:\n");
    printf("=============================================================\n");
    printf("Train ID    Departure Station    Arrival Station   Departure Time    Arrival Time    Available Seats\n");
    printf("=============================================================\n");

    while (!feof(fptr)) {
        fscanf(fptr, "T%d, %[^,], %[^,], %d:%d, %d:%d, %d\n",
            &schedule.trainID, schedule.departureStation, schedule.arrivalStation,
            &schedule.time.departureHour, &schedule.time.departureMin,
            &schedule.time.arrivalHour, &schedule.time.arrivalMin,
            &schedule.availableSeats);
        if (trainID==schedule.trainID) { 
            found = 1;
            printf("T%d\t%-32s%-32s%02d:%02d\t\t%02d:%02d\t\t%-15d\n",
                schedule.trainID, schedule.departureStation,
                schedule.arrivalStation, schedule.time.departureHour,
                schedule.time.departureMin, schedule.time.arrivalHour,
                schedule.time.arrivalMin, schedule.availableSeats);
        }
    }

    if (!found) {
        printf("Train ID '%s' not found\n", trainID);
    }

    fclose(fptr);
}



void modifySchedule() {
    int trainID;
    printf("Enter Train ID to modify: T");
    scanf("%d", &trainID);

    FILE* fptr = fopen("train_schedule.txt", "r");
    FILE* edit = fopen("edit.txt", "w");

    if (fptr == NULL|| edit == NULL) {
        printf("Error opening file\n");
        exit(-1);
    }

    
    TrainSchedule schedule;
    int found = 0;

    while (!feof(fptr)) {
        fscanf(fptr, "T%d, %[^,], %[^,], %d:%d, %d:%d, %d\n",
            &schedule.trainID, schedule.departureStation, schedule.arrivalStation,
            &schedule.time.departureHour, &schedule.time.departureMin,
            &schedule.time.arrivalHour, &schedule.time.arrivalMin,
            &schedule.availableSeats);

        if (trainID == schedule.trainID) {
            found = 1;
            printf("Enter New Departure Station: ");
            scanf(" %[^\n]", schedule.departureStation);
            printf("Enter New Arrival Station: ");
            scanf(" %[^\n]", schedule.arrivalStation);
            printf("Enter New Departure Time (HH:MM): ");
            scanf("%d:%d", &schedule.time.departureHour, &schedule.time.departureMin);
            printf("Enter New Arrival Time (HH:MM): ");
            scanf("%d:%d", &schedule.time.arrivalHour, &schedule.time.arrivalMin);
        }

        fprintf(edit, "T%d, %s, %s, %02d:%02d, %02d:%02d, %d\n",
            schedule.trainID, schedule.departureStation, schedule.arrivalStation,
            schedule.time.departureHour, schedule.time.departureMin, schedule.time.arrivalHour, schedule.time.arrivalMin,
            schedule.availableSeats);
    }

    fclose(fptr);
    fclose(edit);

    fptr = fopen("train_schedule.txt", "w");
    edit = fopen("edit.txt", "r");

    while (!feof(edit)) {
        fscanf(edit, "T%d, %[^,], %[^,], %d:%d, %d:%d, %d\n",
            &schedule.trainID, schedule.departureStation, schedule.arrivalStation,
            &schedule.time.departureHour, &schedule.time.departureMin,
            &schedule.time.arrivalHour, &schedule.time.arrivalMin,
            &schedule.availableSeats);
       
        fprintf(fptr, "T%d, %s, %s, %02d:%02d, %02d:%02d, %d\n",
            schedule.trainID, schedule.departureStation, schedule.arrivalStation,
            schedule.time.departureHour, schedule.time.departureMin, schedule.time.arrivalHour, schedule.time.arrivalMin,
            schedule.availableSeats);
    }
    
    if (!found) {
        printf("Train ID '%s' not found\n", trainID);
    }
    printf("Schedule modified successfully\n");
    fclose(fptr);
    fclose(edit);
}



void displaySchedule() {
    FILE* fptr = fopen("train_schedule.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file\n");
        return;
    }

    TrainSchedule schedule;

    printf("\nTrain Schedule:\n");
    printf("============================================================================================================================\n");
    printf("Train ID    Departure Station                Arrival Station                  Departure Time    Arrival Time    Available Seats\n");
    printf("============================================================================================================================\n");

    while (!feof(fptr)) {
        fscanf(fptr, "T%d, %[^,], %[^,], %d:%d, %d:%d, %d\n",
            &schedule.trainID, schedule.departureStation, schedule.arrivalStation,
            &schedule.time.departureHour, &schedule.time.departureMin,
            &schedule.time.arrivalHour, &schedule.time.arrivalMin,
            &schedule.availableSeats);
        printf("T%d\t%-32s%-32s%02d:%02d\t\t%02d:%02d\t\t%-15d\n",
            schedule.trainID, schedule.departureStation,
            schedule.arrivalStation, schedule.time.departureHour,
            schedule.time.departureMin, schedule.time.arrivalHour,
            schedule.time.arrivalMin, schedule.availableSeats);
    }

    fclose(fptr);
    system("pause");
}

