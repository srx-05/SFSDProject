#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"functions.h"

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
        PhysicalDelet();
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
        PhysicalDelet();
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


//average function
float calculateAverage(student* Student) {
    return (Student->subjects[1]->note * 4 + Student->subjects[2]->note * 3 + Student->subjects[3]->note * 2 + Student->subjects[4]->note * 5) / 14.0; 
}


// Function to find the last ID from the file 
int get_last_id_from_file(FILE *file) { 
   file = fopen( "Listes_Etudiants.txt", "r"); 
    if (!file) { 
        printf("Failed to open file for reading.\n"); 
        return 0; // Return 0 if the file doesn't exist or cannot be opened 
    } 
 
    int last_id = 0; 
    char buffer[512]; // Buffer to read lines from the file 
 
    // Read the file line by line to find the last ID 
    while (fgets(buffer, sizeof(buffer), file)) { 
        int temp_id; 
        if (sscanf(buffer, "id : %d", &temp_id) == 1) { 
            if (temp_id > last_id) { 
                last_id = temp_id; 
            } 
        } 
    } 
 
    fclose(file); 
    return last_id; 
} 
 

//display function
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

