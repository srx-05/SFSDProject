#ifndef HANDLELIST_H_INCLUDED
#define HANDLELIST_H_INCLUDED

  #include <stdbool.h>

// Define struct for a subject 
typedef struct subject { 
    char module[5]; 
    int coeff;
    float note;
} subject; 
 
// Define struct for student information 
typedef struct student {
    int id;
    char firstname[50]; 
    char familyname[50];
    int yearofbirth; 
    char classe[3]; 
    subject subjects[4];
    float avg;
    int exist; 
} student; 
 
// Define struct for a node in the linked list 
typedef struct node { 
    student studentData; 
    struct node *next;
} node; 
 
// Function to allocate and initialize a new node 
node *createnode(); 
 
// Function to append a node to the linked list 
void append_node(node **head, student data);


// Function to fill the file content into a linked list
void filetolist()

// Funt



#endif