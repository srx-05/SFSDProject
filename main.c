#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


int main()
{
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
                int givId;
                char modf;
                printf("enter the ID of the student you are searching for : \n");
                scanf("%d\n",&givId);
                SearchStudent(givId);
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
                break;
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
                char gvnClass[2];
                printf("Enter the class you want to display : \n");
                scanf("%2s",gvnClass);
                DisplaybyClass(gvnClass);
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