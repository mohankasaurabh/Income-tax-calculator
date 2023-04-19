#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    float income;
    float tax;
} TaxPayer;

void addNewRecord() {
    TaxPayer taxpayer;
    FILE *fp;

    fp = fopen("taxpayers.dat", "ab");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter name: ");
    scanf("%s", taxpayer.name);

    printf("Enter income: ");
    scanf("%f", &taxpayer.income);

    if(taxpayer.income < 500000) {
        taxpayer.tax = 0;
    } else if(taxpayer.income >= 500000 && taxpayer.income < 1000000) {
        taxpayer.tax = (taxpayer.income - 500000) * 0.1;
    } else {
        taxpayer.tax = 50000 + (taxpayer.income - 1000000) * 0.2;
    }

    fwrite(&taxpayer, sizeof(TaxPayer), 1, fp);

    printf("Record added successfully.\n");

    fclose(fp);
}

void listAllTaxPayers() {
    TaxPayer taxpayer;
    FILE *fp;

    fp = fopen("taxpayers.dat", "rb");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("%-20s %-20s %-20s\n", "Name", "Income", "Tax");

    while(fread(&taxpayer, sizeof(TaxPayer), 1, fp)) {
        printf("%-20s %-20.2f %-20.2f\n", taxpayer.name, taxpayer.income, taxpayer.tax);
    }

    fclose(fp);
}

void search() {
    TaxPayer taxpayer;
    FILE *fp;
    char name[50];

    fp = fopen("taxpayers.dat", "rb");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter name to search: ");
    scanf("%s", name);

    while(fread(&taxpayer, sizeof(TaxPayer), 1, fp)) {
        if(strcmp(taxpayer.name, name) == 0) {
            printf("%-20s %-20s %-20s\n", "Name", "Income", "Tax");
            printf("%-20s %-20.2f %-20.2f\n", taxpayer.name, taxpayer.income, taxpayer.tax);
            fclose(fp);
            return;
        }
    }

    printf("Record not found.\n");

    fclose(fp);
}

void edit() {
    TaxPayer taxpayer;
    FILE *fp, *fpTemp;
    char name[50];

    fp = fopen("taxpayers.dat", "rb");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fpTemp = fopen("temp.dat", "wb");
    if(fpTemp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter name to edit: ");
    scanf("%s", name);

    while(fread(&taxpayer, sizeof(TaxPayer), 1, fp)) {
        if(strcmp(taxpayer.name, name) == 0) {
            printf("Enter new name: ");
            scanf("%s", taxpayer.name);

            printf("Enter new income: ");
            scanf("%f", &taxpayer.income);
            if(taxpayer.income < 500000) {
                taxpayer.tax = 0;
            } else if(taxpayer.income >= 500000 && taxpayer.income < 1000000) {
                taxpayer.tax = (taxpayer.income - 500000) * 0.1;
            } else {
                taxpayer.tax = 50000 + (taxpayer.income - 1000000) * 0.2;
            }

            fwrite(&taxpayer, sizeof(TaxPayer), 1, fpTemp);
        } else {
            fwrite(&taxpayer, sizeof(TaxPayer), 1, fpTemp);
        }
    }

    fclose(fp);
    fclose(fpTemp);

    remove("taxpayers.dat");
    rename("temp.dat", "taxpayers.dat");

    printf("Record updated successfully.\n");
}

void deleteRecord() {
    TaxPayer taxpayer;
    FILE *fp, *fpTemp;
    char name[50];

    fp = fopen("taxpayers.dat", "rb");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fpTemp = fopen("temp.dat", "wb");
    if(fpTemp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter name to delete: ");
    scanf("%s", name);

    while(fread(&taxpayer, sizeof(TaxPayer), 1, fp)) {
        if(strcmp(taxpayer.name, name) != 0) {
            fwrite(&taxpayer, sizeof(TaxPayer), 1, fpTemp);
        }
    }

    fclose(fp);
    fclose(fpTemp);

    remove("taxpayers.dat");
    rename("temp.dat", "taxpayers.dat");

    printf("Record deleted successfully.\n");
}

int main() {
    int choice;

    while(1) {
        printf("\n1. Add New Record\n");
        printf("2. List all Tax Payer along with income tax to be paid\n");
        printf("3. Search\n");
        printf("4. Edit\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addNewRecord();
                break;
            case 2:
                listAllTaxPayers();
                break;
            case 3:
                search();
                break;
            case 4:
                edit();
                break;
            case 5:
                deleteRecord();
                break;
            case 6:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}