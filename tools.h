#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
 

//file weekly update function
void  update(const char *studentfile,const char *updatefile);

//average calculation function
float calculateAverage(student* student);

//display function
void display_student(student *s);


#endif