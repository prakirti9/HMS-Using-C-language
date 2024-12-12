#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
};

void addPatient(FILE* file) {
    struct Patient p;
    printf("Enter Patient ID: ");
    scanf_s("%d", &p.id);
    printf("Enter Patient Name: ");
    getchar();  // To consume newline character
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;  // Removing the newline character
    printf("Enter Age: ");
    scanf_s("%d", &p.age);
    printf("Enter Disease: ");
    getchar();  // To consume newline character
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;

    fwrite(&p, sizeof(struct Patient), 1, file);
    printf("Patient added successfully!\n");
}

void viewPatients(FILE* file) {
    struct Patient p;
    fseek(file, 0, SEEK_SET);
    printf("\nList of Patients:\n");
    while (fread(&p, sizeof(struct Patient), 1, file)) {
        printf("ID: %d, Name: %s, Age: %d, Disease: %s\n", p.id, p.name, p.age, p.disease);
    }
}

int main() {
    FILE* file = fopen("patients.dat", "ab+");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    int choice;
    while (1) {
        printf("\nHospital Management System\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            addPatient(file);
            break;
        case 2:
            viewPatients(file);
            break;
        case 3:
            fclose(file);
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
