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
    node *class_list=NULL;

    node* student_list=filetolist(filename);
    
    printf("Enter the class you would like to display:\n");
    scanf("%s",gvnclass);

    while (student_list != NULL){
        if (strcmp(student_list->studentData.classe,gvnclass) == 0)
         {   occures=true;
            if(!text){
                printf("The students of the class %s:\n\n",gvnclass);
                text=true;
            };
            node* newnode=createnode(student_list->studentData);
            append_node(&class_list,newnode);
            student_list=student_list->next;
            }
        };

    // decreasingorderlist(&class_list);
    // displaylist(),
    //  i will create this functions later dw




 if (!occures)
    {
        printf("Class is empty or misspelled, check again!");
    };
     
};

   

bool SearchStudent(const char *FILENAME, int *position) {
    int matricule;
    *position = 0;  // Initialize position

    printf("\nEnter Matricule to search: ");
    scanf("%d", &matricule);

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return false;
    }

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




