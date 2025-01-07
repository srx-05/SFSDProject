#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include<ctype.h>
#include"handlelist.h"
#include"functions.h"
#include"tools.h"


int main()
{
    FILE *studentFile=fopen("studentlist.txt","r");

     if (studentFile== NULL) {
        printf("ERROR openning the file");
        return -1;
    }

    student *head_of_std_list = FileToList("studentlist.txt");
    int last_id=getLastID(head_of_std_list);

    int choice;

    update("studentlist.txt","updateDateFile.txt");

    do {

        printf("\t\tENSTA STUDENT MANAGEMENT SYSTEM\n");
        printf(" 1-Add a new student\n 2-searching for a student\n 3-modifing a student's information\n 4-logical deletion\n 5-display by class\n 6-reorganization (physical deletion)\n 0-exit\n");
        printf("\tenter your choice : ");
        scanf("%d",&choice);
        switch (choice) {
            case 1 :{
                addStudent(&head_of_std_list,last_id);
                break;
            }
            case 2 :{
                bool isexist=searchStudent("studentlist.txt");
                if (isexist){
                    printf("Student found");
                    break;
                }
                else {
                    printf("Student not found.\n");
                    break;
                }
            }
            case 3 :{
                int givId;
                printf("enter the ID of the student you want to modifie his information : \n");
                scanf("%d",&givId);
                modifyStudent(head_of_std_list,"studentlist.txt",givId);
                break;
            }
            case 4 :{
                printf("Loading students from file...\n");
                student *head_of_std_list = FileToList("studentlist.txt");
                if (!head_of_std_list) {
                    printf("No students found in the file.\n");
                    return 1;
                }
                printf("Students loaded successfully. Proceeding to logical deletion.\n");
                int id;
                printf("\nEnter id to search: ");
                scanf("%d", &id);
                if (SearchStudentToDelete(head_of_std_list, id)) {
                    logicalDelete(head_of_std_list, id);
                    printf("Saving updated list to file...\n");

                }
                ListToFile(head_of_std_list, "studentlist.txt");
                freeStudentList(head_of_std_list);
                break;
            }
            case 5 :{
                displayByClass(head_of_std_list);
                break;
            }
            case 6 :{
                FILE *updfile=fopen("updateDateFile.txt","r");
                if (updfile==NULL){
                    printf("ERROR, the update file can't be opened.\n");
                    return -1;
                }
                time_t lastupd;
                if (fscanf(updfile, "%ld", &lastupd) != 1) {
                    printf("ERROR, Failed to read the last update date from the file.\n");
                    fclose(updfile);
                    return -2;
                }
                struct tm *date = localtime(&lastupd);
                printf("your file is updated weekly.\n");
                printf("last update date : %s",asctime(date));
                printf("Do you want to update it again? (Y/N)\n");
                char userupd;
                do {
                    scanf(" %c",&userupd);
                    userupd = toupper(userupd);
                    if (userupd=='Y'){
                        printf("Physical deletion in progress ...\n");
                        physicalDelete("studentlist.txt");
                        break;
                    }
                    else if (userupd=='N') {
                        printf("operation canceled!\n");
                        break;
                    }
                    else{
                        printf("please answer with Y if yes, N otherwise\n");
                    }
                }while((userupd!='Y')&&(userupd!='N'));
                fclose(updfile);
                break;
            }
            case 0 :{
                printf("Exiting the system.\n");
                break;
            }
            default:
                printf("Invalid option, please try again.\n");
                break;
        }
    } while (choice!=0);



    return 0;
}