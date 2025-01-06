#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED



void addstudent(FILE *file, student *head);

bool SearchStudent(const char *FILENAME, int *position);

void modifyStudent(student *head, const char *filename, int id);

void LogicalDelet(student *head, int id);

void DisplaybyClass(const char *filename); //Displays all students of a given class by their average in a decreasing order 

void PhysicalDelet(const char *filename);


#endif
