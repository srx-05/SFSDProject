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

