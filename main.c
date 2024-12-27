#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
#include"handlelist.h"
#include"functions.h"
#include"students.h"


int main()
{
    // node *head_of_std_list=filetolist("students.txt");
    //not sure of this

    int choice;
    
    do {

        printf("\t\tENSTA STUDENT MANAGEMENT SYSTEM\n");
        printf(" 1-Add a new student\n 2-searching for a student\n 3-modifing a student's information\n 4-logical deletion\n 5-data extraction\n 6-reorganization (physical deletion)\n");
        printf("\tenter your choice : ");
        scanf("%d",&choice);


        switch (choice) {
            case 1 :{
                AddStudent();
                break;
            } 
            case 2 :{
                int i;
                bool isexist=SearchStudent("students_file.txt",&i);
                if (isexist){
                    char modf;
                    printf("The position : %d",i);
                    printf("do you want to modify the student's information? (Y/N)\n");
                    scanf("%c",&modf);
                    do {
                        if (strcmp(modf,"Y")==0)
                        ModifyStudentData(givId);
                    else if (strcmp(modf,"N")==0)
                        break;
                    else
                        printf("please answer with Y if yes, N otherwise\n");
                    }while((strcmp(modf,"Y")!=0)&&(strcmp(modf,"N")!=0));
                }
                else {
                    printf("Student not found.\n");
                    break;
                }
            }
            case 3 :{
                int givId;
                printf("enter the ID of the student you want to modifie his information : \n");
                scanf("%d\n",&givId);
                ModifyStudentData(givId);
                break;
            }
            case 4 :{
                int givId;
                printf("enter the ID of the student you want to delete : \n");
                scanf("%d\n",&givId);
                LogicalDelet(givId);
                break;
            }
            case 5 :{
                DisplaybyClass();
                break;
            }
            case 6 :{
                PhysicalDelet();
                break;
            }
            default:
                printf("Invalid option, please try again\n");
        }
    } while (choice>0);



    return 0;
}