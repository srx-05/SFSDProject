#include <stdio.h>
#include <functions.h>
#include <handlelist.h>



void Display(){

   struct student std;
   char class[3];
   bool occures=false,text=false;
   float temp_max;

   FILE* f=fopen("test.txt","r");
    if (f == NULL){
        printf("Error occured");
        return;
    };


    printf("Enter the class you would like to display:\n");
    scanf("%s",class);

    while (fscanf(f,"%d %19s %19s %d %2s",&std.ID,std.fname,std.name,&std.Ybirth,std.class) == 5){

        if (strcmp(std.class,class)==0)
        {
            if(!text){
                printf("The students of the class %s:\n\n",class);
                text=true;
            }
            occures=true;
            
            printf("ID:%d\nfamily name:%s\nname:%s\nyear:%d\n\t************\n",std.ID,std.fname,std.name,std.Ybirth);
        };  

    } ; 

    if (!occures)
    {
        printf("Class is empty or misspelled, check again!");
    };
      
      fclose(f);
}




