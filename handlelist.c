#include <stdio.h>
#include "handlelist.h"



 
// Function to allocate and initialize a new node 
node *createnode(student std) { 
    node *newnode =(node *)malloc(sizeof(node));

    if (!newnode) { 
        perror("Memory allocation failed"); 
        return NULL; 
    };

    newnode->studentData=std;
    newnode->next=NULL;

    return newnode;
} ;
 
// Function to append a node to the linked list 
void append_node(node **head,node *new_node){ 

    if (*head == NULL) { 
        *head = new_node; 
        return; 
    } 
 
    node *temp = *head; 
    while (temp->next != NULL) { 
        temp = temp->next; 
    };

    temp->next = new_node; 
}; 

//function to upload a file into a linked list
node *filetolist(const char *file_name){
    student std1;
    node *head=NULL;
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
       node *std_node=createnode(std1);//creating node for each imported student

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

