#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Subj {
    char SubjName[20];
    int coef;
    double note;
} Subj;

typedef struct Student {
    char Name[30];
    char FamilyName[30];
    int ID;
    int YearOfBith;
    int group;
    Subj Notes[4];
    bool exist;
    double Average;
    struct Student *next;
} Student;

FILE* ListToFile(Student *Std) {
    // Validate input
    if (Std == NULL) {
        printf("Error: Student list is empty.\n");
        return NULL;
    }
    // Open the file for writing
    FILE *file = fopen("listes_etudiants.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    // Traverse the linked list and write to the file
    Student *temp = Std;
    while (temp != NULL) {
        // Create a list
        Student *newStudent = (Student *)malloc(sizeof(Student));
        if (newStudent == NULL) {
            perror("Failed to allocate memory for student");
            exit(1);
        }
        // Write student data
        strcpy(newStudent->Name, temp->Name);
        strcpy(newStudent->FamilyName, temp->FamilyName);
        newStudent->ID = temp->ID;
        newStudent->YearOfBith = temp->YearOfBith;
        newStudent->group = temp->group;
        // Write notes information
        for (int i = 0; i < 4; i++) {
            strcpy(newStudent->Notes[i].SubjName, temp->Notes[i].SubjName);
            newStudent->Notes[i].coef = temp->Notes[i].coef;
            newStudent->Notes[i].note = temp->Notes[i].note;
        }
        // Write existence and average information and next student &
        newStudent->exist = temp->exist;
        newStudent->Average = temp->Average;
        newStudent->next = temp->next;
        temp = temp->next;
    }
    fclose(file);
    return file;

char choice;
Student *FileToList(struct Student *Stdnt){
    struct Student *temp = Stdnt;
    file = fopen("listes_etudiants.txt", "r");
    if (file == NULL) {
        printf("File not found!\n");
        exit(1);
    }
    while (fscanf(file, "%s %s %d %d %d", temp->Name, temp->FamilyName, &temp->ID, &temp->YearOfBith, &temp->group) != EOF) {
        for (int i = 0; i < 4; i++) {
            fscanf(file, " %s %d %f", temp->Notes[i].SubjName, &temp->Notes[i].coef, &temp->Notes[i].note);
        }
        fscanf(file, " %d %f", &temp->exist, &temp->Average);
        temp->next = (Student *) malloc(sizeof(Student));
        temp = temp->next;
    }
}

//using research function, if the id not found than it's looping, else it runs the next function
// false=exist, true=logically deleted
void LogicalDeleting (struct Student *Stdnt){
    struct Student *Std = FileToList(Stdnt);
    if (!Std->exist){ // the student is existing and want to delete it
        do {
            printf("The student \"%s  %s  %d\" exists, you want to delete this student logically ? [y/n] :", Std->Name, Std->FamilyName, Std->ID);
            scanf(" %c", &choice);
            if (choice=='y' || choice=='Y'){
                Std->exist=true;  //edit existing flag
                printf("student's existing flag edited successfully!\n");
                break;
            } else if(choice=='n' || choice=='N'){
                      printf("Operation canceled.\n");
                      break;
            } else {
                printf("Invalid input. Please enter 'y' or 'n'!\n");
            }
        } while (1);
    } else { // the student is deleted and want to recover it
        do {
            printf("The student \"%s  %s  %d\" is deleted logically, you want to recover this student ? [y/n] :", Std->Name, Std->FamilyName, Std->ID);
            scanf(" %c", &choice);
            if (choice=='y' || choice=='Y'){
                Std->exist=false;
                printf("student's existing flag edited successfully!\n");
                break;
            } else if(choice=='n' || choice=='N'){
                printf("Operation canceled.\n");
                break;
            } else {
                printf("Invalid input. Please enter 'y' or 'n'!\n");
            }
        } while (1);
    }
    file = ListToFile(Std);
}
// comment add in the line number 59
int main(){
    Student std1 = {"John", "Doe", 12345, 2002, 1, {{0}}, true, 0.0, NULL};
    printf("Testing Logical Deleting Function:\n");
    LogicalDeleting(*std1);
    printf("Student Exist Flag: %d\n", std1.exist);
    return 0;
}
