#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED


//file weekly update function
void  update(const char *studentfile,const char *updatefile);

//average calculation function
float calculateAverage(Student* student);

//display function
void display_student(student *s);


// Function to find the last ID from the file 
int get_last_id_from_file(FILE *file);

#endif