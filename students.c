#include <stdio.h>
#include "handlelist.h"

void display_student(student *s) {
    
    printf("\nStudent Details:\n");
    printf("Matricule: %d\n", s->id);
    printf("Name: %s %s\n", s->familyname, s->firstname);
    printf("Year of Birth: %d\n", s->yearofbirth);
    printf("Group: %s\n", s->classe);
    printf("Grades:\n");
    for (int i = 0; i < 4; i++) {
        printf("The subject %4s:\n \t %.2f (Coefficient: %d)\n", s->subjects[i].subj , s->subjects[i].note, s->subjects[i].coeff);
    }
    printf("Average: %.2f\n", s->avg);
}





