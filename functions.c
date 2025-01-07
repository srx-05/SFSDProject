#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <functions.h>
#include "handlelist.h"
#include "tools.h"



void displayByclass(student *head){
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

    decreasingorderlist(class_list);
    displaylist(class_list);
    
};

   

bool SearchStudent(const char *FILENAME, int *position) {
     FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return false;
    }
    
    int matricule;
    printf("\nEnter Matricule to search: ");
    scanf("%d", &matricule);

    student s;
    bool found = false;
    while (fscanf(file,
            "%d %49s %49s %d %2s "
            "%9s %f %d "
            "%9s %f %d "
            "%9s %f %d "
            "%9s %f %d "
            "%f %d",
            &s.id, s.familyname, s.firstname, &s.yearofbirth, s.classe,
            s.subjects[0].subj,  &s.subjects[0].note, &s.subjects[0].coeff,
            s.subjects[1].subj,  &s.subjects[1].note, &s.subjects[1].coeff,
            s.subjects[2].subj,  &s.subjects[2].note, &s.subjects[2].coeff,
            s.subjects[3].subj,  &s.subjects[3].note, &s.subjects[3].coeff,
            &s.avg, (int *)&s.exist) == 19) {
        
        if (s.id == matricule && s.exist == 0) {  // Make sure to use `s.exist == false`
            found = true;
            break;
        }
    }
    fclose(file);

    if (!found) {
        *position = 0;
        printf("Student not found.\n");
    } else {
        *position = matricule;
        display_student(&s);
    }

    return found;
}


 
// Function to create and add a student to the linked list
void addStudent(student **head,int last_id){ 

    student newStudent;

    // Input student details
    printf("Enter the firstname and family name (use ';' to separate multiple names):\n"); 
    scanf("%s %s", newStudent.firstName, newStudent.familyName); 

    do { 
        printf("Enter the year of birth:\n"); 
        scanf("%d", &newStudent.yearOfBirth); 
    } while (newStudent.yearOfBirth < 1900 || newStudent.yearOfBirth > 2025); 

    printf("Enter the class of the student:\n"); 
    scanf("%s", newStudent.Class); 

    // Input student marks
    do { 
        printf("Enter the mark of this student in SFSD:\n"); 
        scanf("%f", &newStudent.subjects[0].note); 
        printf("Enter the mark of this student in POO:\n"); 
        scanf("%f", &newStudent.subjects[1].note); 
        printf("Enter the mark of this student in ANALYSIS:\n"); 
        scanf("%f", &newStudent.subjects[2].note); 
        printf("Enter the mark of this student in Algebra:\n"); 
        scanf("%f", &newStudent.subjects[3].note); 
    } while ((newStudent.subjects[0].note < 0 || newStudent.subjects[0].note > 20) ||
             (newStudent.subjects[1].note < 0 || newStudent.subjects[1].note > 20) ||
             (newStudent.subjects[2].note < 0 || newStudent.subjects[2].note > 20) ||
             (newStudent.subjects[3].note < 0 || newStudent.subjects[3].note > 20));

    newStudent->exist = true; 

    // Assign subject names and coefficients
    strcpy(newStudent.subjects[0].subj, "SFSD");
    newStudent.subjects[0].coeff = 4;
    strcpy(newStudent.subjects[1].subj, "POO");
    newStudent.subjects[1].coeff = 3;
    strcpy(newStudent.subjects[2].subj, "ANMT");
    newStudent.subjects[2].coeff = 2;
    strcpy(newStudent->subjects[3].subj, "ALGE");
    newStudent.subjects[3].coeff = 5;

    // Calculate average
    newStudent.avg = calculateAverage(newStudent);
    newStudent.id = last_id + 1; 

    // Add the new student to the linked list
    student *std_node=createnode(newStudent);
    append_node(head,std_node);

    listofile(head);
  
}





//modify student function
void modifyStudent(node **head, const char *filename, int id) {
    // Load the list from the file first
    node *student_list = filetolist(filename);
    if (!student_list) {
        printf("Error loading the student list from file.\n");
        return;
    }

    // Search for the student in the list
    node *student_node = search_student(student_list, id);
    if (!student_node) {
        printf("Student with ID %d not found or is deleted.\n", id);
        return;
    }

    student *std = &student_node->studentData;
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
                scanf("%s", std->familyname);
                break;
            case 2:
                printf("New first name: ");
                scanf("%s", std->firstname);
                break;
            case 3:
                printf("New year of birth: ");
                scanf("%d", &std->yearofbirth);
                break;
            case 4:
                printf("New class: ");
                scanf("%s", std->classe);
                break;
            case 5:
                printf("Enter subject index (0-3): ");
                int index;
                scanf("%d", &index);
                if (index >= 0 && index < 4) {
                    printf("Enter new grade: ");
                    scanf("%f", &newGrade);
                    std->subjects[index].note = newGrade;
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

        // Write the updated list back to the file after modification
        list_to_file(student_list, filename);

    } while (choice != 0);
}

// Fonction de suppression physiquevoid physicalDeletion(const char* filename) {
    Student* studentList = FileToList(filename);    if (!studentList) {
        fprintf(stderr, "Erreur lors du chargement des étudiants depuis le fichier : %s\n", filename);        return;
    }
    // Filtrer les étudiants actifs (exist == 0)    Student* filteredList = NULL;
    Student* tail = NULL;
    for (Student* current = studentList; current; ) {        Student* next = current->next;
        if (current->exist == 0) { // Conserver uniquement les étudiants actifs
            if (!filteredList) {                filteredList = tail = current;
            } else {                tail->next = current;
                tail = current;            }
            tail->next = NULL; // S'assurer que le dernier élément est bien terminé        } else {
            free(current); // Libérer la mémoire pour les étudiants non actifs        }
        current = next;
    }
    // Sauvegarder la liste filtrée dans le fichier    ListToFile(filename, filteredList);
    // Libérer la liste filtrée
    freeStudentList(filteredList);}
// Fonction pour libérer la mémoire d'une liste d'étudiants
void freeStudentList(Student* head) {    Student* current = head;
    while (current) {        Student* temp = current;
        current = current->next;        free(temp);
    }}


void LogicalDeleting(student *head) {
    if (head == NULL) {
        printf("No students found in the list.\n");
        return;
    }

    student *current = head;
    while (current != NULL) {
        if (!current->exist) {
            printf("The student exists. Do you want to delete? [y/n]: ");
        } else {
            printf("The student is deleted. Recover? [y/n]: ");
        }

        char choice;
        do {
            choice = getchar();
        } while (choice == '\n');

        if ((choice == 'y' || choice == 'Y') && current->exist) {
            current->exist = 1;  // Mark as recovered
            printf("the existing flag is edited successfully!\n");
            break;
        } else if ((choice == 'y' || choice == 'Y') && !current->exist) {
            current->exist = 0;  // Mark as deleted
            printf("the existing flag is edited successfully!\n");
            break;
        } else {
            printf("Please enter a valid choice.\n");
        }
        current = current->next;
    }
}

