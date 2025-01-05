#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <functions.h>
#include "handlelist.h"
#include "students.h"



void Displaybyclass(const char *filename){
    char gvnclass[3];
    bool text=false,occures=false;
    student *class_list=NULL;

    student *student_list=filetolist(filename);
    
    printf("Enter the class you would like to display:\n");
    scanf("%s",gvnclass);

    while (student_list != NULL){
        if (strcmp(student_list->classe,gvnclass) == 0)
         {   occures=true;
            if(!text){
                printf("The students of the class %s:\n\n",gvnclass);
                text=true;
            };
            student* newnode=createnode(student_list->studentData);
            append_node(&class_list,newnode);
            student_list=student_list->next;
        }
    };


    if (!occures)
    {
        printf("Class is empty or misspelled, check again!");
        return;
    };

    decreasingorderlist(&class_list);
    displaylist(&class_list);
    





     
};

   

bool SearchStudent(const char *FILENAME, int *position) {
     FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return false;
    }
    
    int matricule;
    *position = 0;  // Initialize position

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

        (*position)++;
        if (s.id == matricule && s.exist == 0) {  // Make sure to use `s.exist == false`
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



//physical deletion
void physicalDelet(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "rb");
    FILE *out = fopen(outputFile, "wb");
    
    if (in == NULL || out == NULL) {
        printf("Error opening file!\n");
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    Student temp;
    while (fread(&temp, sizeof(Student), 1, in)) {
        if (temp.exist == 0) {
            fwrite(&temp, sizeof(Student), 1, out);
        }
    }

    fclose(in);
    fclose(out);

    remove(inputFile);
    rename(outputFile, inputFile);
}
 
// Function to create and add a student to the linked list
void addStudent(FILE *file, student **head) { 
    student *newStudent = (student *)malloc(sizeof(student));

    if (!newStudent) {
        perror("Memory allocation failed");
        return;
    }

    // Input student details
    printf("Enter the firstname and family name (use ';' to separate multiple names):\n"); 
    scanf("%s %s", newStudent->firstname, newStudent->familyname); 

    do { 
        printf("Enter the year of birth:\n"); 
        scanf("%d", &newStudent->yearofbirth); 
    } while (newStudent->yearofbirth < 1900 || newStudent->yearofbirth > 2025); 

    printf("Enter the class of the student:\n"); 
    scanf("%s", newStudent->classe); 

    // Input student marks
    do { 
        printf("Enter the mark of this student in SFSD:\n"); 
        scanf("%f", &newStudent->subjects[0].note); 
        printf("Enter the mark of this student in POO:\n"); 
        scanf("%f", &newStudent->subjects[1].note); 
        printf("Enter the mark of this student in ANALYSIS:\n"); 
        scanf("%f", &newStudent->subjects[2].note); 
        printf("Enter the mark of this student in Linear Algebra:\n"); 
        scanf("%f", &newStudent->subjects[3].note); 
    } while ((newStudent->subjects[0].note < 0 || newStudent->subjects[0].note > 20) ||
             (newStudent->subjects[1].note < 0 || newStudent->subjects[1].note > 20) ||
             (newStudent->subjects[2].note < 0 || newStudent->subjects[2].note > 20) ||
             (newStudent->subjects[3].note < 0 || newStudent->subjects[3].note > 20));

    newStudent->exist = true; 

    // Assign subject names and coefficients
    strcpy(newStudent->subjects[0].subj, "SFSD");
    newStudent->subjects[0].coeff = 4;
    strcpy(newStudent->subjects[1].subj, "POO");
    newStudent->subjects[1].coeff = 3;
    strcpy(newStudent->subjects[2].subj, "ANMT");
    newStudent->subjects[2].coeff = 2;
    strcpy(newStudent->subjects[3].subj, "ALGE");
    newStudent->subjects[3].coeff = 5;

    // Calculate average
    newStudent->avg = calculateAverage(newStudent);

    // Get last ID and assign a new ID
    int last_id = getLastIDFromFile(file); 
    newStudent->id = last_id + 1; 

    // Add the new student to the linked list
    newStudent->next = *head;  
    *head = newStudent;  

    // Open the file to append new student's information
    file = fopen("Listes_Etudiants.txt", "a"); 
    if (!file) { 
        printf("Failed to open file for writing.\n"); 
        return; 
    } 

    fprintf(file, "id : %d\t  family name : %s\t firstname: %s\t year of birth : %d\t class : %s\t "
                  "mark of %s : %.2f coeff : %d\t mark of %s : %.2f coeff : %d\t "
                  "mark of %s : %.2f coeff : %d\t mark of %s : %.2f coeff : %d\t "
                  "Average : %.2f\t FLAG : %d\n",
            newStudent->id, newStudent->familyname, newStudent->firstname, newStudent->yearofbirth, newStudent->classe,
            newStudent->subjects[0].subj, newStudent->subjects[0].note, newStudent->subjects[0].coeff, 
            newStudent->subjects[1].subj, newStudent->subjects[1].note, newStudent->subjects[1].coeff, 
            newStudent->subjects[2].subj, newStudent->subjects[2].note, newStudent->subjects[2].coeff, 
            newStudent->subjects[3].subj, newStudent->subjects[3].note, newStudent->subjects[3].coeff, 
            newStudent->avg, newStudent->exist); 

    fclose(file); 
}