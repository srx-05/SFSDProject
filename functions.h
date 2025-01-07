#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED



void addStudent(student **head, int last_id);

bool searchStudent(const char *FILENAME);

void modifyStudent(student *student_list, const char *filename, int id);

void logicalDelete(student *head, int id);

void displayByClass(student *head); //Displays all students of a given class by their average in a decreasing order 

void physicalDelete(const char* filename);


#endif
