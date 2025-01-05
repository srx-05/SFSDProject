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