#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>




// Define struct for a subject
typedef struct subject {
    char subj[10];
    float note;
    int coeff;
} subject;

// Define struct for student information
typedef struct student {
    int id;
    char familyName[50];
    char firstName[50];
    int yearOfBirth;
    char Class[3];
    subject subjects[4];
    float avg;
    int exist;
    struct student *next;
} student;


student *createnode(student std) {
    student *newnode =(student *)malloc(sizeof(student));

    if (!newnode) {
        perror("Memory allocation failed");
        return NULL;
    };

    *newnode=std;
    newnode->next=NULL;

    return newnode;
} ;

void append_node(student **head,student *new_node){

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    student *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    };

    temp->next = new_node;
};
student *filetolist(FILE *file) {
    student std1;
    student *head = NULL;

    while (fscanf(file,
                  "%d %s %s %d %s "
                  "%s %f %d "
                  "%s %f %d "
                  "%s %f %d "
                  "%s %f %d "
                  "%f %d",
                  &std1.id, std1.familyName, std1.firstName, &std1.yearOfBirth, std1.Class,
                  std1.subjects[0].subj, &std1.subjects[0].note, &std1.subjects[0].coeff,
                  std1.subjects[1].subj, &std1.subjects[1].note, &std1.subjects[1].coeff,
                  std1.subjects[2].subj, &std1.subjects[2].note, &std1.subjects[2].coeff,
                  std1.subjects[3].subj, &std1.subjects[3].note, &std1.subjects[3].coeff,
                  &std1.avg, &std1.exist) == 19) {
        student *std_node = createnode(std1);
        if (!std_node) {
            printf("Error: importing a student failed!\n");
            fclose(file);
            return NULL;
        }
        append_node(&head, std_node);
    }
    fclose(file);
    return head;
}

student *Decreasingorderlist(student **head){

      if (*head == NULL || (*head)->next == NULL) {
        printf("Nothing to sort\n");
        return *head;
    }

    student *sorted = NULL;
    while (*head != NULL) {
        student *current = *head;
        *head = (*head)->next;

        if (sorted == NULL || current->avg > sorted->avg) {
            current->next = sorted;
            sorted = current;
        } else {
            student *temp = sorted;
            while (temp->next != NULL && temp->next->avg >= current->avg) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    *head = sorted;
    return sorted;
}

void Displaylist(student *head){
    student* current=head;

    while ( current != NULL){
        printf("ID:%d\nFull name:%s %s\nClass:%s\nAverage:%.2f\n",current->id,current->familyName,current->firstName,current->Class,current->avg);
        current=current->next;
    }

}




void displayByclass(student *head){
    char gvnclass[3];
    bool text=false,occures=false;
    student *class_list=NULL;

    printf("Enter the class you would like to display:\n");
    scanf("%s",gvnclass);

    while (head != NULL){
        if (strcmp(head->Class,gvnclass) == 0)
         {   occures=true;
            if(!text){
                printf("The students of the class %s:\n\n",gvnclass);
                text=true;
            };
            student* newnode=createnode(*head);
            append_node(&class_list,newnode);

        }
        head=head->next;
    };


    if (!occures)
    {
        printf("Class is empty or misspelled, check again!");
        return;
    };

    Decreasingorderlist(&class_list);
    Displaylist(class_list);

};

int main()
{
    FILE *file=fopen("studentlist.txt","r");

    if (file==NULL){
        printf("error opening the file");
    }

    student* stdList=filetolist(file);

    if(stdList==NULL){
        printf("List was not uploaded");
        return 1;
    }


    displayByclass(stdList);
    return 0;
}
