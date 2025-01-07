#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED



void addStudent(student **head,int *last_id);

bool searchStudent(const char *FILENAME, int *position);

void modifyStudent(student *head, const char *filename, int id);

void logicalDelet(student *head, int id);

void displayByClass(student *head); //Displays all students of a given class by their average in a decreasing order 

void physicalDelet(const char *filename);


#endif
