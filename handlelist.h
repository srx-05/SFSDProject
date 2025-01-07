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
    char familyName[50];
    char firstName[50];
    int yearOfBirth;
    char Class[3];
    subject subjects[4];
    float avg;
    int exist;
    struct student *next;
} student; 
  
 
// Function to allocate and initialize a new node 
student *createnode(student std)
 
// Function to append a node to the linked list 
void append_node(student **head,student *new_node)


// Function to fill the file content into a linked list
student *FileToList(const char *file_name)

//Function to fill the file with a linked list content
void ListToFile(student *head, const char *filename)


// Function to display list
void Displaylist(student *head)

//Funcion to order a list of students by their in a decreasing order 
student *Decreasingorderlist(student **head)

//Function to get ID of the last student in the list
int getLastID(student *head)

void freeStudentList(student* head)


#endif
