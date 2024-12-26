#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <functions.h>
void display_student(student *s) {
    printf("\nStudent Details:\n");
    printf("Matricule: %d\n", s->id);
    printf("Name: %s %s\n", s->familyname, s->firstname);
    printf("Year of Birth: %d\n", s->yearofbirth);
    printf("Group: %s\n", s->classe);
    printf("Grades:\n");
    for (int i = 0; i < 4; i++) {
        printf("The subject %4s:\n \t %.2f (Coefficient: %d)\n",s->subjects[i].subj , s->subjects[i].note, s->subjects[i].coeff);
    }
    printf("Average: %.2f\n", s->avg);
}
bool search_student(const char *FILENAME, int *i ) {
    int matricule;
    *i=0;
    printf("\nEnter Matricule to search: ");
    scanf("%d", &matricule);

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    student s;
    bool found = false;
    while (fscanf(file,
            "%d %49s %49s %d %19s "
            "%4s %d %f "
            "%4s %d %f "
            "%4s %d %f "
            "%4s %d %f "
            "%f %d",
            &s.id, s.familyname, s.firstname, &s.yearofbirth, s.classe,
            s.subjects[0].subj,  &s.subjects[0].coeff, &s.subjects[0].note,
            s.subjects[1].subj,  &s.subjects[1].coeff, &s.subjects[1].note,
            s.subjects[2].subj,  &s.subjects[2].coeff, &s.subjects[2].note,
            s.subjects[3].subj,  &s.subjects[3].coeff, &s.subjects[3].note,
            &s.avg, (int *)&s.exist)==19 ) {
                      (*i)++;
        if (s.id == matricule && !s.exist) {

            found = true;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("Student not found.\n");

    }
    else {
        display_student(&s);
    }
    return found;
}






