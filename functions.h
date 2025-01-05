#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED



void addstudent(FILE *file, node *head);

bool SearchStudent(const char *FILENAME, int *position);

void ModifyStudentData();

void LogicalDelet();

void DisplaybyClass(const char *filename); //Displays all students of a given class by their average in a decreasing order 

void PhysicalDelet(const char *inputFile, const char *outputFile);


#endif
