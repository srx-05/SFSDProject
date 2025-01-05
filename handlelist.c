#include <stdio.h>
#include "handlelist.h"



 
// Function to allocate and initialize a new node 
student *createnode(student std) { 
    student *newnode =(student *)malloc(sizeof(student));

    if (!newnode) { 
        perror("Memory allocation failed"); 
        return NULL; 
    };

    newnode=std;
    newnode->next=NULL;

    return newnode;
} ;
 
// Function to append a node to the linked list 
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

//function to upload a file into a linked list
student *filetolist(const char *file_name){
    student std1;
    student *head=NULL;
    FILE *file=fopen(file_name,"r");

    if (file == NULL){
        printf("Error opening the file");
        return NULL;
    };


    while (fscanf(file,"%d %s %s %d %s %s %f %d %s %f %d %s %f %d %s %f %d %f %d",
    &std1.id,std1.familyname,std1.firstname,&std1.yearofbirth,std1.classe,
    std1.subjects[0].module,&std1.subjects[0].note,&std1.subjects[0].coeff,
    std1.subjects[1].module,&std1.subjects[1].note,&std1.subjects[1].coeff,
    std1.subjects[2].module,&std1.subjects[2].note,&std1.subjects[2].coeff,
    std1.subjects[3].module,&std1.subjects[3].note,&std1.subjects[3].coeff,
    &std1.avg,&std1.exist ) == 19)//students and their data are imported one by one from the desired file
    {
       student *std_node=createnode(std1);//creating node for each imported student

       if (!std_node) { // If memory allocation failed
            printf("Error:importing a student failed!");
            fclose(file);
            return NULL;
        }

       append_node(&head, std_node);//linking the imported student to the previously created list

    };

   if (head == NULL) {
        printf("Error: No data uploaded to the linked list!\n");
        fclose(file);
        return NULL;
    };

    printf("The file was successfuly uploaded to a list")

   
    fclose(file);

    return head;  


}

//function to order a list of students in a decreasing order 
student *Decreasingorderlist(student **head){

    if (*head==NULL || (*head)->next==NULL)//list is empty or has only one student
    {
        printf("Nothing to sort");
        return;
    }

    student *sorted=NULL;

    student *current= *head;

    while (current!=NULL)
    {
        student *next=current->next;

        if (sorted == NULL || current->average > sorted->average) {
            current->next = sorted;
            sorted = current;
        } else {
            student* temp = sorted;
            while (temp->next != NULL && temp->next->average >= current->average) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    *head = sorted;    
}

void Displaylist(student *head){
    student* current=head;

    while ( current != NULL){
        printf("ID:%d\nFull name:%s %s\nClass:%s\nAverage:%f\n",current->id,current->familyname,current->firstname,current->classe,current->avg);
        current=current->next;
    }

}
