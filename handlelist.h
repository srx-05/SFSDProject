#ifndef HANDLELIST_H_INCLUDED
#define HANDLELIST_H_INCLUDED

// Define struct for a subject 
typedef struct subject { 
    char subj[10]; 
    float note;
    int coeff;
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
    int exist; 
} student; 
 
// Define struct for a node in the linked list 
typedef struct node { 
    student studentData; 
    struct node *next;
} node; 
 
// Function to allocate and initialize a new node 
node *createnode(student std); 
 
// Function to append a node to the linked list 
void append_node(node **head,node *new_node);


// Function to fill the file content into a linked list
node *filetolist(const char *file_name)

//Function to fill the file with a linked list content
void listofile(node **head_of_std_list)




#endif
