#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <functions.h>
<<<<<<< HEAD
#include <handlelist.h>



void Display(){

   struct student std;
   char class[3];
   bool occures=false,text=false;
   float temp_max;

   FILE* f=fopen("test.txt","r");
    if (f == NULL){
        printf("Error occured");
        return;
    };


    printf("Enter the class you would like to display:\n");
    scanf("%s",class);

    while (fscanf(f,"%d %19s %19s %d %2s",&std.ID,std.fname,std.name,&std.Ybirth,std.class) == 5){

        if (strcmp(std.class,class)==0)
        {
            if(!text){
                printf("The students of the class %s:\n\n",class);
                text=true;
            }
            occures=true;
            
            printf("ID:%d\nfamily name:%s\nname:%s\nyear:%d\n\t************\n",std.ID,std.fname,std.name,std.Ybirth);
        };  

    } ; 

    if (!occures)
    {
        printf("Class is empty or misspelled, check again!");
    };
      
      fclose(f);
=======
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

bool search_student(const char *FILENAME, int *position) {
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
>>>>>>> 1368c52496ce9a2a2837d2d979cfef4b349820e1
}




