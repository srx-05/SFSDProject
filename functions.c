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
// Procedure to create and add a node with content 
void addstudent(FILE *file, node *head) { 
    subject subjects[4]; 
    student content; 
 
    // Input student details 
    printf("Enter the firstname, family name ,if multiple names or composed family names separe them with the character';':\n"); 
    scanf("%s %s", content.firstname, content.familyname); 
    do { 
        printf("Enter the year of birth:\n"); 
        scanf("%d", &content.yearofbirth); 
       } 
    while((content.yearofbirth<1900 ) || (content.yearofbirth>2025)); 
 
    printf("Enter the class of the student:\n"); 
    scanf("%s", content.classe); 
 
    do 
    { 
        printf("Enter the mark of this student in SFSD:\n"); 
        scanf("%f", &content.subjects[0].note); 
        printf("Enter the mark of this student in POO:\n"); 
        scanf("%f", &content.subjects[1].note); 
        printf("Enter the mark of this student in ANALYSIS:\n"); 
        scanf("%f", &content.subjects[2].note); 
        printf("Enter the mark of this student in Linear Algebra:\n"); 
        scanf("%f", &content.subjects[3].note); 
    } 
    while (((content.subjects[0].note<0)||(content.subjects[0].note>20))||((content.subjects[1].note<0)||(content.subjects[1].note>20))||((content.subjects[2].note<0)||(content.subjects[2].note>20))||((content.subjects[3].note<0)||(content.subjects[3].note>20))); 
    content.exist = true; 
    content.avg = calculateAverag(content);
    
    // Get the last ID from the file and assign the next ID 
    int last_id = get_last_id_from_file(file); 
    content.id = last_id + 1; 
    strcpy(content.subjects[0].subj,"SFSD"); 
    content.subjects[0].coeff=4; 
    strcpy(content.subjects[1].subj,"POO"); 
    content.subjects[1].coeff=3; 
    strcpy(content.subjects[2].subj,"ANMT"); 
    content.subjects[2].coeff=2; 
    strcpy(content.subjects[3].subj,"ALGE"); 
    content.subjects[3].coeff=5; 
 
 
    // Create and add the new node to the list
node *liststud = createnode(content); 
    modifylistaddnode(head, liststud); 
 
    // Open the file to append the new student's information 
    file = fopen("Listes_Etudiants.txt", "a"); 
    if (!file) { 
        printf("Failed to open file for writing.\n"); 
        return; 
    } 
 
    fprintf(file, "id : %d\t  family name : %s\t firstname: %s\t year of birth : %d\t group : %s\t mark of %s : %.2f \t  coeff : %d \tmark of %s : %.2f coeff : %d\t mark of %s : %.2f coeff : %d \t mark of %s : %.2f coeff : %d \t Average : %f \t  FLAG : %d\n", 
            content.id, content.familyname, content.firstname, content.yearofbirth, content.classe, 
            content.subjects[0].subj, content.subjects[0].avg,content.subjects[0].coeff, 
            content.subjects[1].subj, content.subjects[1].avg,content.subjects[1].coeff, 
            content.subjects[2].subj, content.subjects[2].avg,content.subjects[2].coeff, 
            content.subjects[3].subj, content.subjects[3].avg, content.subjects[3].coeff, 
            content.avg,content.exist); 
            
 
    fclose(file); 
} 

