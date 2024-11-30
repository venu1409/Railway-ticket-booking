#ifndef IRCTC_H
#define IRCTC_H
#include "irctc.h"
#include <stdio.h>
#include <stdlib.h>

void createTicketFile(int Train_Number, char from[], char to[], int day, int month, int year, int Seats, char names[][250], char Seat_Preference[], long long PNR) {
    char filename[50];
    sprintf(filename, "ticket.txt");
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error creating ticket file.\n");
        return;
    }

    fprintf(file, "PNR: %lld\n", PNR);
    fprintf(file, "Train Number: %d\n", Train_Number);
    fprintf(file, "From: %s\n", from);
    fprintf(file, "To: %s\n", to);
    fprintf(file, "Date of Journey: %02d-%02d-%d\n", day, month, year);
    fprintf(file, "Number of Seats: %d\n", Seats);
    for (int i = 0; i < Seats; i++) {
        fprintf(file, "Passenger %d: %s, Seat Preference: %c\n\n\n", i + 1, names[i], Seat_Preference[i]);
    }
    fclose(file);
    printf("Ticket file created: %s\n", filename);
}
#endif
