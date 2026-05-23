#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll;
    char name[50];
    float marks[3];
    float total;
};

void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct Student s;

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    s.total = 0;
    for(int i = 0; i < 3; i++) {
        printf("Enter marks for subject %d: ", i+1);
        scanf("%f", &s.marks[i]);
        s.total += s.marks[i];
    }

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student added!\n");
}

void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    while(fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll: %d", s.roll);
        printf("\nName: %s", s.name);
        printf("\nTotal: %.2f\n", s.total);
    }

    fclose(fp);
}

void rankList() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s[100];
    int count = 0;

    while(fread(&s[count], sizeof(struct Student), 1, fp)) {
        count++;
    }
    fclose(fp);

    for(int i = 0; i < count-1; i++) {
        for(int j = i+1; j < count; j++) {
            if(s[i].total < s[j].total) {
                struct Student temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("\n--- Rank List ---\n");
    for(int i = 0; i < count; i++) {
        printf("Rank %d: %s (%.2f)\n", i+1, s[i].name, s[i].total);
    }
}

int main() {
    int choice;

    while(1) {
        printf("\n1. Add Student\n2. Display\n3. Rank List\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: rankList(); break;
            case 4: exit(0);
            default: printf("Invalid!\n");
        }
    }
}