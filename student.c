#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float maths, science, english;
    float total, average;
    char grade;
};

void calculateResult(struct Student *s) {
    s->total = s->maths + s->science + s->english;
    s->average = s->total / 3;

    if(s->average >= 90) s->grade = 'A';
    else if(s->average >= 75) s->grade = 'B';
    else if(s->average >= 50) s->grade = 'C';
    else s->grade = 'F';
}

void addStudent() {
    struct Student s;
    FILE *fp = fopen("student.dat", "ab");

    if(fp == NULL) {
        printf("File Error!\n");
        return;
    }

    printf("\nEnter Roll No: ");
    scanf("%d", &s.roll);
    getchar();

    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter Maths Marks: ");
    scanf("%f", &s.maths);

    printf("Enter Science Marks: ");
    scanf("%f", &s.science);

    printf("Enter English Marks: ");
    scanf("%f", &s.english);

    calculateResult(&s);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student Added Successfully!\n");
}

void displayStudent() {
    struct Student s;
    FILE *fp = fopen("student.dat", "rb");

    if(fp == NULL) {
        printf("No Records Found!\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");

    while(fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll No : %d", s.roll);
        printf("\nName    : %s", s.name);
        printf("\nMaths   : %.2f", s.maths);
        printf("\nScience : %.2f", s.science);
        printf("\nEnglish : %.2f", s.english);
        printf("\nTotal   : %.2f", s.total);
        printf("\nAverage : %.2f", s.average);
        printf("\nGrade   : %c", s.grade);
        printf("\n-----------------------------------\n");
    }

    fclose(fp);
}

void login() {
    char user[20], pass[20];

    printf("\n===== LOGIN =====\n");
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);

    if(strcmp(user, "admin") == 0 && strcmp(pass, "1234") == 0) {
        printf("Login Successful!\n");
    } else {
        printf("Invalid Login! Exiting...\n");
        exit(0);
    }
}

int main() {
    int choice;

    login();

    while(1) {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudent(); break;
            case 3: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }

    return 0;
}
