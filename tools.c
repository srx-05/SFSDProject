#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<tools.h>
#include"functions.h"
#include"handllist.h"

//file weekly update function
void  update(const char *studentfile,const char *updatefile){
    FILE *f=fopen(studentfile,"r");
    FILE *upd=fopen(updatefile,"r+");

    //make usre both files exist
    if (f==NULL){
        printf("ERROR, %s doesn't exist.\n",studentfile);
        exit(-1);
    }
    if (upd==NULL){
        printf("ERROR, %s doesn't exist.\n",updatefile);
        fclose(f);
        exit(-2);
    }

    time_t lastupd;
    if (fscanf(upd,"%ld",&lastupd)!=1){
        //first run case
        physicalDelete("studentlist.txt");
        lastupd = time(NULL);
        fprintf(upd,"%ld",lastupd);
        printf("%s updated successfully for the first time!!\n",studentfile);
        fclose(f);
        fclose(upd);
        return;
    }

    time_t now=time(NULL);

    //check if the difference between now and last update date is a week
    if (difftime(now,lastupd)>=7*24*60*60){
        physicalDelete(studentfile);
        printf("%s upddated successfully!\n",studentfile);
        fclose(upd);
        upd=fopen(updatefile,"w");
        if (upd==NULL){
            printf("ERROR, impossible to open %s for writing.\n",updatefile);
            fclose(f);
            exit(-4);
        }
        fprintf(upd,"%ld",now);
    }

    fclose(upd);
    fclose(f);
}


// Function to calculate a student's weighted average
float calculateAverage(student* Student) {
    float totalScore = 0;
    int totalCoeff = 0;

    for (int i = 0; i < 4; i++) {
        totalScore += Student->subjects[i].note * Student->subjects[i].coeff;
        totalCoeff += Student->subjects[i].coeff;
    }
    return totalScore / totalCoeff;
}

//display function
void display_student(student *s) {

    printf("\nStudent Details:\n");
    printf("Matricule: %d\n", s->id);
    printf("Name: %s %s\n", s->familyName, s->firstName);
    printf("Year of Birth: %d\n", s->yearOfBirth);
    printf("Group: %s\n", s->Class);
    printf("Grades:\n");
    for (int i = 0; i < 4; i++) {
        printf("The subject %4s:\n \t %.2f (Coefficient: %d)\n", s->subjects[i].subj , s->subjects[i].note, s->subjects[i].coeff);
    }
    printf("Average: %.2f\n", s->avg);
}




bool SearchStudentToDelete(student *head, int id) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return false;
    }

    student *current = head;
    bool found = false;

    // Traverse the linked list
    while (current != NULL) {
        if (current->id == id) { // Match found
            found = true;
            display_student(current);
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Student not found.\n");
    }

    return found;
}