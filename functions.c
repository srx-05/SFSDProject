#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "handlelist.h"
#include "tools.h"
#include "functions.h"



void displayByClass(student *head){
    char gvnclass[3];
    bool text=false,occures=false;
    student *class_list=NULL;

    printf("Enter the class you would like to display:\n");
    scanf("%s",gvnclass);

    while (head != NULL){
        if (strcmp(head->Class,gvnclass) == 0)
         {   occures=true;
            if(!text){
                printf("The students of the class %s:\n\n",gvnclass);
                text=true;
            };
            student* newnode=createnode(*head);
            append_node(&class_list,newnode);

        }
        head=head->next;
    };


    if (!occures)
    {
        printf("Class is empty or misspelled, check again!");
        return;
    };

    Decreasingorderlist(&class_list);
    Displaylist(class_list);

};

   

bool searchStudent(const char *FILENAME) {
     FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return false;
    }

    int id;
    printf("\nEnter Matricule to search: ");
    scanf("%d", &id);

    student s;
    bool found = false;
    while (fscanf(file,
            "%d %49s %49s %d %2s "
            "%9s %f %d "
            "%9s %f %d "
            "%9s %f %d "
            "%9s %f %d "
            "%f %d",
            &s.id, s.familyName, s.firstName, &s.yearOfBirth, s.Class,
            s.subjects[0].subj,  &s.subjects[0].note, &s.subjects[0].coeff,
            s.subjects[1].subj,  &s.subjects[1].note, &s.subjects[1].coeff,
            s.subjects[2].subj,  &s.subjects[2].note, &s.subjects[2].coeff,
            s.subjects[3].subj,  &s.subjects[3].note, &s.subjects[3].coeff,
            &s.avg, (int *)&s.exist) == 19) {

        if (s.id == id && s.exist == 0) {  // Make sure to use s.exist == false
            found = true;
            break;
        }
    }
    fclose(file);

    if (!found) {
        
        printf("Student not found.\n");
    } else {
        
        display_student(&s);
    }

    return found;
}


 
// Function to create and add a student to the linked list
void addStudent(student **head, int last_id) {
    student newStudent;

    // Input student details
    printf("Enter the first name: ");
    scanf("%s", newStudent.firstName);
    printf("Enter the family name: ");
    scanf("%s", newStudent.familyName);

    // Validate year of birth
    do {
        printf("Enter the year of birth (1900-2025): ");
        scanf("%d", &newStudent.yearOfBirth);
        if (newStudent.yearOfBirth < 1900 || newStudent.yearOfBirth > 2025) {
            printf("Invalid year. Please enter a year between 1900 and 2025.\n");
        }
    } while (newStudent.yearOfBirth < 1900 || newStudent.yearOfBirth > 2025);

    printf("Enter the class of the student : ");
    scanf("%s", newStudent.Class);

    // Input student marks with validation
    do {
        printf("Enter the mark of this student in SFSD (0-20): ");
        scanf("%f", &newStudent.subjects[0].note);
        printf("Enter the mark of this student in POO (0-20): ");
        scanf("%f", &newStudent.subjects[1].note);
        printf("Enter the mark of this student in ANALYSIS (0-20): ");
        scanf("%f", &newStudent.subjects[2].note);
        printf("Enter the mark of this student in Algebra (0-20): ");
        scanf("%f", &newStudent.subjects[3].note);

        // Validate marks
        if (newStudent.subjects[0].note < 0 || newStudent.subjects[0].note > 20 ||
            newStudent.subjects[1].note < 0 || newStudent.subjects[1].note > 20 ||
            newStudent.subjects[2].note < 0 || newStudent.subjects[2].note > 20 ||
            newStudent.subjects[3].note < 0 || newStudent.subjects[3].note > 20) {
            printf("Invalid marks. Please enter marks between 0 and 20.\n");
        }
    } while (newStudent.subjects[0].note < 0 || newStudent.subjects[0].note > 20 ||
             newStudent.subjects[1].note < 0 || newStudent.subjects[1].note > 20 ||
             newStudent.subjects[2].note < 0 || newStudent.subjects[2].note > 20 ||
             newStudent.subjects[3].note < 0 || newStudent.subjects[3].note > 20);

    // Assign subject names and coefficients
    strcpy(newStudent.subjects[0].subj, "SFSD");
    newStudent.subjects[0].coeff = 4;
    strcpy(newStudent.subjects[1].subj, "POO");
    newStudent.subjects[1].coeff = 3;
    strcpy(newStudent.subjects[2].subj, "ANMT");
    newStudent.subjects[2].coeff = 2;
    strcpy(newStudent.subjects[3].subj, "ALGE");
    newStudent.subjects[3].coeff = 5;

    // Set the student ID
    newStudent.id = last_id + 1;

    // Calculate the average
    newStudent.avg = calculateAverage(&newStudent);

    // Set the exist flag
    newStudent.exist = 0; // 0 means the student exists (not deleted)

    // Create a new node for the student
    student *std_node = createnode(newStudent);
    if (!std_node) {
        printf("Error: Failed to create a new student node.\n");
        return;
    }

    // Append the new student to the linked list
    append_node(head, std_node);

    // Save the updated list to the file
    ListToFile(*head, "studentlist.txt");

    printf("Student added successfully!\n");
}





//modify student function
void modifyStudent(student *student_list, const char *filename, int id) {
    if (!student_list) {
        printf("The student list is empty.\n");
        return;
    }
    printf("modifying works");
    // Search for the student node by ID
    student *current = student_list;
    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (!current) {
        printf("Student with ID %d not found.\n", id);
        return;
    }
    printf("Student with ID %d found. Starting modification.\n", id);

    int choice;
    float newGrade;

    do {
        printf("\nWhat would you like to modify?\n");
        printf("1. Family name\n");
        printf("2. First name\n");
        printf("3. Year of birth\n");
        printf("4. Class\n");
        printf("5. Subject grade\n");
        printf("0. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("New family name: ");
                scanf("%s", current->familyName);
                break;
            case 2:
                printf("New first name: ");
                scanf("%s", current->firstName);
                break;
            case 3:
                printf("New year of birth: ");
                scanf("%d", &current->yearOfBirth);
                break;
            case 4:
                printf("New class: ");
                scanf("%s", current->Class);
                break;
            case 5:
                printf("Enter subject index (1-4) \n1-SFSD\n2-OOP\n3-ANALYSIS\n4-ALGEBRA \n: ");
                int index;
                scanf("%d", &index);
                if (index >= 1 && index <= 4) {
                    printf("Enter new grade: ");
                    scanf("%f", &newGrade);
                    current->subjects[index-1].note = newGrade;
                    float average = calculateAverage(current);
                    printf("New average: %.2f\n", average);
                } else {
                    printf("Invalid subject index.\n");
                }
                break;
            case 0:
                printf("Modification complete.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    // Write the updated list back to the file
    ListToFile(student_list, filename);
    printf("Student list successfully updated in the file.\n");
}

// Fonction de suppression physique
void physicalDelete(const char* filename) {
    student* studentList = FileToList(filename);
    if (!studentList) {
        fprintf(stderr, "Erreur lors du chargement des étudiants depuis le fichier : %s\n", filename);
        return;
    }

    // Filtrer les étudiants actifs (exist == 0)
    student* filteredList = NULL;
    student* tail = NULL;

    for (student* current = studentList; current; ) {
        student* next = current->next;

        if (current->exist == 0) { // Conserver uniquement les étudiants actifs
            if (!filteredList) {
                filteredList = tail = current;
            } else {
                tail->next = current;
                tail = current;
            }
            tail->next = NULL; // S'assurer que le dernier élément est bien terminé
        } else {
            free(current); // Libérer la mémoire pour les étudiants non actifs
        }

        current = next;
    }

    // Sauvegarder la liste filtrée dans le fichier
    ListToFile(filteredList ,filename );

    // Libérer la liste filtrée
    freeStudentList(filteredList);
}

void logicalDelete(student *head, int id) {
    if (head == NULL) {
        printf("No students found in the list.\n");
        return;
    }

    student *current = head;
    char choice;
    while (current != NULL) {
        if (!current->exist && current->id == id) {
            printf("The student exists. Do you want to delete? [y/n]: ");
            do {
                choice = getchar();
            } while (choice == '\n' || (toupper(choice) != 'Y' && toupper(choice) != 'N'));
            if (toupper(choice) == 'Y') {
                current->exist = 1;  // Mark as deleted
                printf("the existing flag is edited successfully!\n");
                break;
            }
            if (toupper(choice) == 'N') {
                printf("operation canceled!\n");
                break;
            }
        } else if (current->exist && current->id == id){
            printf("The student is deleted. Recover? [y/n]: ");
            do {
                choice = getchar();
            } while (choice == '\n' || (toupper(choice) != 'Y' && toupper(choice) != 'N'));
            if (toupper(choice) == 'Y') {
                current->exist = 0;  // Mark as recovered
                printf("the existing flag is edited successfully!\n");
                break;
            }
            if (toupper(choice) == 'N') {
                printf("operation canceled!\n");
                break;
            }
        }

        current = current->next;
    }
}

