#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include<ctype.h>
#include"handlelist.h"
#include"functions.h"
#include"tools.h"



 
// Function to allocate and initialize a new node 
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
student *FileToList(const char *file_name) {
    student std1;
    student *head = NULL;
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





void ListToFile(student *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        printf("Ensure that the program has write permissions for '%s'.\n", filename);
        return;
    }

    student *current = head;  // No need to dereference head
    while (current != NULL) {
        // Use -> to access members of the current pointer
        fprintf(file,
                "%d %s %s %d %s "
                "%s %.2f %d "
                "%s %.2f %d "
                "%s %.2f %d "
                "%s %.2f %d "
                "%.2f %d\n",
                current->id, current->familyName, current->firstName, current->yearOfBirth, current->Class,
                current->subjects[0].subj, current->subjects[0].note, current->subjects[0].coeff,
                current->subjects[1].subj, current->subjects[1].note, current->subjects[1].coeff,
                current->subjects[2].subj, current->subjects[2].note, current->subjects[2].coeff,
                current->subjects[3].subj, current->subjects[3].note, current->subjects[3].coeff,
                current->avg, current->exist);
        current = current->next;  // Move to the next node
    }

    fclose(file);
    printf("List successfully written to file: %s\n", filename);
}


//function to order a list of students in a decreasing order 
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


void freeStudentList(student* head) {
    student* current = head;
    while (current) {
        student* temp = current;
        current = current->next;
        free(temp);
    }
}


int getLastID(student *head){

    if (head == NULL) {
        return -1; 
    }

    student* current = head;

    while (current->next != NULL) {
        current = current->next; // Traverse the list
    }

    return current->id;


}
