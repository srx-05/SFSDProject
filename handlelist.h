#ifndef HANDLELIST_H_INCLUDED
#define HANDLELIST_H_INCLUDED



// Define struct for a subject 
typedef struct subject { 
    char subj[5]; 
    int coeff;
    float note;
} subject; 
 
// Define struct for student information 
typedef struct student { 
    int id; 
    char familyname[50]; 
    char firstname[50]; 
    int yearofbirth; 
    char classe[3]; 
    subject subjects[4];
    float avg;
    bool exist; 
} student; 
 
// Define struct for a node in the linked list 
typedef struct node { 
    student studentData; 
    struct node *next;
} node; 
 
// Function to allocate and initialize a new node 
node *createnode(student data); 
 
// Function to append a node to the linked list 
void append_node(node **head, student data);




#endif
