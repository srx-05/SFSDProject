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
node *filetolist(const char *file_name) {
    student std1;
    node *head = NULL;
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Error opening the file");
        printf("Ensure that the file '%s' exists in the correct directory.\n", file_name);
        return NULL;
    }
    while (fscanf(file,
                  "%d %s %s %d %s "
                  "%s %f %d "
                  "%s %f %d "
                  "%s %f %d "
                  "%s %f %d "
                  "%f %d",
                  &std1.id, std1.familyname, std1.firstname, &std1.yearofbirth, std1.classe,
                  std1.subjects[0].subj, &std1.subjects[0].note, &std1.subjects[0].coeff,
                  std1.subjects[1].subj, &std1.subjects[1].note, &std1.subjects[1].coeff,
                  std1.subjects[2].subj, &std1.subjects[2].note, &std1.subjects[2].coeff,
                  std1.subjects[3].subj, &std1.subjects[3].note, &std1.subjects[3].coeff,
                  &std1.avg, &std1.exist) == 19) {
        node *std_node = createnode(std1);
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
void list_to_file(node *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        printf("Ensure that the program has write permissions for '%s'.\n", filename);
        return;
    }
    node *current = head;
    while (current != NULL) {
        student s = current->studentData;
        fprintf(file,
                "%d %s %s %d %s "
                "%s %.2f %d "
                "%s %.2f %d "
                "%s %.2f %d "
                "%s %.2f %d "
                "%.2f %d\n",
                s.id, s.familyname, s.firstname, s.yearofbirth, s.classe,
                s.subjects[0].subj, s.subjects[0].note, s.subjects[0].coeff,
                s.subjects[1].subj, s.subjects[1].note, s.subjects[1].coeff,
                s.subjects[2].subj, s.subjects[2].note, s.subjects[2].coeff,
                s.subjects[3].subj, s.subjects[3].note, s.subjects[3].coeff,
                s.avg, s.exist);
        current = current->next;
    }
    fclose(file);
    printf("List successfully written to file: %s\n", filename);
}

// Function to search for a student by matricule
node *search_student(node *head, int id) {
    node *current = head;
    while (current != NULL) {
        if (current->studentData.id == id && current->studentData.exist == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
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
