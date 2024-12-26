#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct {
    char subjname[20];
    float note;
    int coefficient;

}subject;
typedef struct{ int matricule;
    char name[50];
    char surname[50];
    int birthyear;
    char group[20];
    subject notes[4];
    float total_average;
    bool exit_status;
}student;
/*void fill_coefficients(student *s) {
    float coefficients[4] = {4, 3, 2, 5};
    for (int i = 0; i < 4; i++) {
        s->notes[i].coefficient = coefficients[i];
    }
}*/
void display_student(student *s) {
    printf("\nStudent Details:\n");
    printf("Matricule: %d\n", s->matricule);
    printf("Name: %s %s\n", s->name, s->surname);
    printf("Year of Birth: %d\n", s->birthyear);
    printf("Group: %s\n", s->group);
    printf("Grades:\n");
    for (int i = 0; i < 4; i++) {
        printf("The subject %7s:\n \t %.2f (Coefficient: %d)\n",s->notes[i].subjname , s->notes[i].note, s->notes[i].coefficient);
    }
    printf("Average: %.2f\n", s->total_average);
    printf("Exit Status: %s\n", s->exit_status ? "Deleted" : "Active");
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
            "%19s %f %d "
            "%19s %f %d "
            "%19s %f %d "
            "%19s %f %d "
            "%f %d",
            &s.matricule, s.name, s.surname, &s.birthyear, s.group,
            s.notes[0].subjname, &s.notes[0].note, &s.notes[0].coefficient,
            s.notes[1].subjname, &s.notes[1].note, &s.notes[1].coefficient,
            s.notes[2].subjname, &s.notes[2].note, &s.notes[2].coefficient,
            s.notes[3].subjname, &s.notes[3].note, &s.notes[3].coefficient,
            &s.total_average, (int *)&s.exit_status)==19 ) {
                      (*i)++;
        if (s.matricule == matricule && !s.exit_status) {

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
int main()
{
    int i;
    bool my_bool=search_student("students_file.txt",&i);
    if(my_bool){
        printf("The position : %d",i);
    }
    else{
        printf("Student not found.\n");
    }

    return 0;
}
