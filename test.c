#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct subject {
    char subj[10];
    float note;
    int coeff;
} subject;

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

student *createnode(student std) {
    student *newnode =(student *)malloc(sizeof(student));

    if (!newnode) {
        perror("Memory allocation failed");
        return NULL;
    };

    *newnode=std;
    newnode->next=NULL;

    return newnode;
} ;

// Function to append a node to the linked list
void append_node(student **head,student *new_node){
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    student *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    };

    temp->next = new_node;
};

//function to upload a file into a linked list
student *FileToList(const char *file_name) {
    student std1;
    student *head = NULL;
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Error opening the file");
        printf("Ensure that the file '%s' exists in the correct directory.\n", file_name);
        return NULL;
    }
    while (fscanf(file,
                  "%d %s %s %d %s "
                  "%s %f %d "
                  "%s %f %d "
                  "%s %f %d "
                  "%s %f %d "
                  "%f %d",
                  &std1.id, std1.familyName, std1.firstName, &std1.yearOfBirth, std1.Class,
                  std1.subjects[0].subj, &std1.subjects[0].note, &std1.subjects[0].coeff,
                  std1.subjects[1].subj, &std1.subjects[1].note, &std1.subjects[1].coeff,
                  std1.subjects[2].subj, &std1.subjects[2].note, &std1.subjects[2].coeff,
                  std1.subjects[3].subj, &std1.subjects[3].note, &std1.subjects[3].coeff,
                  &std1.avg, &std1.exist) == 19) {
        student *std_node = createnode(std1);
        if (!std_node) {
            printf("Error: importing a student failed!\n");
            fclose(file);
            return NULL;
        }
        append_node(&head, std_node);
    }
    fclose(file);
    return head;
}

void ListToFile(student *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        printf("Ensure that the program has write permissions for '%s'.\n", filename);
        return;
    }

    student *current = head;  // No need to dereference head
    while (current != NULL) {
        // Use -> to access members of the current pointer
        fprintf(file,
                "%d %s %s %d %s "
                "%s %.2f %d "
                "%s %.2f %d "
                "%s %.2f %d "
                "%s %.2f %d "
                "%.2f %d\n",
                current->id, current->familyName, current->firstName, current->yearOfBirth, current->Class,
                current->subjects[0].subj, current->subjects[0].note, current->subjects[0].coeff,
                current->subjects[1].subj, current->subjects[1].note, current->subjects[1].coeff,
                current->subjects[2].subj, current->subjects[2].note, current->subjects[2].coeff,
                current->subjects[3].subj, current->subjects[3].note, current->subjects[3].coeff,
                current->avg, current->exist);
        current = current->next;  // Move to the next node
    }

    fclose(file);
    printf("List successfully written to file: %s\n", filename);
}

// Function to calculate a student's weighted average
float calculateAverage(student* Student) {
    float totalScore = 0;

    for (int i = 0; i < 4; i++) {
        totalScore += (Student->subjects[i].note) * (Student->subjects[i].coeff);

    }
    return totalScore / 14;
}

// Function to find the last ID from the file
int getLastID(student *head){

    if (head == NULL) {
        return -1;
    }

    student* current = head;

    while (current->next != NULL) {
        current = current->next; // Traverse the list
    }

    return current->id;


}

//display function
void display_student(student *s) {

    printf("\nStudent Details:\n");
    printf("Matricule: %d\n", s->id);
    printf("Name: %s %s\n", s->familyName, s->firstName);
    printf("Year of Birth: %d\n", s->yearOfBirth);
    printf("Group: %s\n", s->Class);
    printf("Grades:\n");
    for (int i = 0; i < 4; i++) {
        printf("The subject %4s:\n \t %.2f (Coefficient: %d)\n", s->subjects[i].subj , s->subjects[i].note, s->subjects[i].coeff);
    }
    printf("Average: %.2f\n", s->avg);
}

void freeStudentList(student* head) {
    student* current = head;
    while (current) {
        student* temp = current;
        current = current->next;
        free(temp);
    }
}

/*void addStudent(student **head,int last_id){

    student newStudent;

    // Input student details
    printf("Enter the firstname and family name (use ';' to separate multiple names):\n");
    scanf("%s %s", newStudent.firstName, newStudent.familyName);

    do {
        printf("Enter the year of birth:\n");
        scanf("%d", &newStudent.yearOfBirth);
    } while (newStudent.yearOfBirth < 1900 || newStudent.yearOfBirth > 2025);

    printf("Enter the class of the student:\n");
    scanf("%s", newStudent.Class);

    // Input student marks
    do {
        printf("Enter the mark of this student in SFSD:\n");
        scanf("%f", &newStudent.subjects[0].note);
        printf("Enter the mark of this student in POO:\n");
        scanf("%f", &newStudent.subjects[1].note);
        printf("Enter the mark of this student in ANALYSIS:\n");
        scanf("%f", &newStudent.subjects[2].note);
        printf("Enter the mark of this student in Algebra:\n");
        scanf("%f", &newStudent.subjects[3].note);
    } while ((newStudent.subjects[0].note < 0 || newStudent.subjects[0].note > 20) ||
             (newStudent.subjects[1].note < 0 || newStudent.subjects[1].note > 20) ||
             (newStudent.subjects[2].note < 0 || newStudent.subjects[2].note > 20) ||
             (newStudent.subjects[3].note < 0 || newStudent.subjects[3].note > 20));

    newStudent.exist = true;

    // Assign subject names and coefficients
    strcpy(newStudent.subjects[0].subj, "SFSD");
    newStudent.subjects[0].coeff = 4;
    strcpy(newStudent.subjects[1].subj, "POO");
    newStudent.subjects[1].coeff = 3;
    strcpy(newStudent.subjects[2].subj, "ANMT");
    newStudent.subjects[2].coeff = 2;
    strcpy(newStudent.subjects[3].subj, "ALGE");
    newStudent.subjects[3].coeff = 5;

    newStudent.id = last_id + 1;

    // Add the new student to the linked list
    student *std_node=createnode(newStudent);
    // Calculate average
    newStudent.avg = calculateAverage(std_node);

    append_node(head,std_node);

    ListToFile(head,"studentlist.txt");

}*/
void addStudent(student **head, int last_id) {
    student newStudent;

    // Input student details
    printf("Enter the first name: ");
    scanf("%s", newStudent.firstName);
    printf("Enter the family name: ");
    scanf("%s", newStudent.familyName);

    // Validate year of birth
    do {
        printf("Enter the year of birth (1900-2025): ");
        scanf("%d", &newStudent.yearOfBirth);
        if (newStudent.yearOfBirth < 1900 || newStudent.yearOfBirth > 2025) {
            printf("Invalid year. Please enter a year between 1900 and 2025.\n");
        }
    } while (newStudent.yearOfBirth < 1900 || newStudent.yearOfBirth > 2025);

    printf("Enter the class of the student (e.g., 1A, 2B): ");
    scanf("%s", newStudent.Class);

    // Input student marks with validation
    do {
        printf("Enter the mark of this student in SFSD (0-20): ");
        scanf("%f", &newStudent.subjects[0].note);
        printf("Enter the mark of this student in POO (0-20): ");
        scanf("%f", &newStudent.subjects[1].note);
        printf("Enter the mark of this student in ANALYSIS (0-20): ");
        scanf("%f", &newStudent.subjects[2].note);
        printf("Enter the mark of this student in Algebra (0-20): ");
        scanf("%f", &newStudent.subjects[3].note);

        // Validate marks
        if (newStudent.subjects[0].note < 0 || newStudent.subjects[0].note > 20 ||
            newStudent.subjects[1].note < 0 || newStudent.subjects[1].note > 20 ||
            newStudent.subjects[2].note < 0 || newStudent.subjects[2].note > 20 ||
            newStudent.subjects[3].note < 0 || newStudent.subjects[3].note > 20) {
            printf("Invalid marks. Please enter marks between 0 and 20.\n");
        }
    } while (newStudent.subjects[0].note < 0 || newStudent.subjects[0].note > 20 ||
             newStudent.subjects[1].note < 0 || newStudent.subjects[1].note > 20 ||
             newStudent.subjects[2].note < 0 || newStudent.subjects[2].note > 20 ||
             newStudent.subjects[3].note < 0 || newStudent.subjects[3].note > 20);

    // Assign subject names and coefficients
    strcpy(newStudent.subjects[0].subj, "SFSD");
    newStudent.subjects[0].coeff = 4;
    strcpy(newStudent.subjects[1].subj, "POO");
    newStudent.subjects[1].coeff = 3;
    strcpy(newStudent.subjects[2].subj, "ANMT");
    newStudent.subjects[2].coeff = 2;
    strcpy(newStudent.subjects[3].subj, "ALGE");
    newStudent.subjects[3].coeff = 5;

    // Set the student ID
    newStudent.id = last_id + 1;

    // Calculate the average
    newStudent.avg = calculateAverage(&newStudent);

    // Set the exist flag
    newStudent.exist = 0; // 0 means the student exists (not deleted)

    // Create a new node for the student
    student *std_node = createnode(newStudent);
    if (!std_node) {
        printf("Error: Failed to create a new student node.\n");
        return;
    }

    // Append the new student to the linked list
    append_node(head, std_node);

    // Save the updated list to the file
    ListToFile(*head, "studentlist.txt");

    printf("Student added successfully!\n");
}
//function to order a list of students in a decreasing order
student *Decreasingorderlist(student **head){

      if (*head == NULL || (*head)->next == NULL) {
        printf("Nothing to sort\n");
        return *head;
    }

    student *sorted = NULL;
    while (*head != NULL) {
        student *current = *head;
        *head = (*head)->next;

        if (sorted == NULL || current->avg > sorted->avg) {
            current->next = sorted;
            sorted = current;
        } else {
            student *temp = sorted;
            while (temp->next != NULL && temp->next->avg >= current->avg) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    *head = sorted;
    return sorted;
}

void Displaylist(student *head){
    student* current=head;

    while ( current != NULL){
        printf("ID:%d\nFull name:%s %s\nClass:%s\nAverage:%f\n",current->id,current->familyName,current->firstName,current->Class,current->avg);
        current=current->next;
    }

}
void displayByClass(student *head){
    char gvnclass[3];
    bool text=false,occures=false;
    student *class_list=NULL;

    printf("Enter the class you would like to display:\n");
    scanf("%s",gvnclass);

    while (head != NULL){
        if (strcmp(head->Class,gvnclass) == 0)
         {   occures=true;
            if(!text){
                printf("The students of the class %s:\n\n",gvnclass);
                text=true;
            };
            student* newnode=createnode(*head);
            append_node(&class_list,newnode);

        }
        head=head->next;
    };


    if (!occures)
    {
        printf("Class is empty or misspelled, check again!");
        return;
    };

    Decreasingorderlist(&class_list);
    Displaylist(class_list);

};


bool SearchStudentToDelete(student *head, int id) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return false;
    }

    student *current = head;
    bool found = false;

    // Traverse the linked list
    while (current != NULL) {
        if (current->id == id) { // Match found
            found = true;
            display_student(current);
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Student not found.\n");
    }

    return found;
}

void logicalDelete(student *head, int id) {
    if (head == NULL) {
        printf("No students found in the list.\n");
        return;
    }

    student *current = head;
    char choice;
    while (current != NULL) {
        if (!current->exist && current->id == id) {
            printf("The student exists. Do you want to delete? [y/n]: ");
            do {
                choice = getchar();
            } while (choice == '\n' || (toupper(choice) != 'Y' && toupper(choice) != 'N'));
            if (toupper(choice) == 'Y') {
                current->exist = 1;  // Mark as deleted
                printf("the existing flag is edited successfully!\n");
                break;
            }
            if (toupper(choice) == 'N') {
                printf("operation canceled!\n");
                break;
            }
        } else if (current->exist && current->id == id){
            printf("The student is deleted. Recover? [y/n]: ");
            do {
                choice = getchar();
            } while (choice == '\n' || (toupper(choice) != 'Y' && toupper(choice) != 'N'));
            if (toupper(choice) == 'Y') {
                current->exist = 0;  // Mark as recovered
                printf("the existing flag is edited successfully!\n");
                break;
            }
            if (toupper(choice) == 'N') {
                printf("operation canceled!\n");
                break;
            }
        }

        current = current->next;
    }
}

void physicalDeletion(const char* filename) {
    student* studentList = FileToList(filename);
    if (!studentList) {
        fprintf(stderr, "Erreur lors du chargement des étudiants depuis le fichier : %s\n", filename);
        return;
    }

    // Filtrer les étudiants actifs (exist == 0)
    student* filteredList = NULL;
    student* tail = NULL;

    for (student* current = studentList; current; ) {
        student* next = current->next;

        if (current->exist == 0) { // Conserver uniquement les étudiants actifs
            if (!filteredList) {
                filteredList = tail = current;
            } else {
                tail->next = current;
                tail = current;
            }
            tail->next = NULL; // S'assurer que le dernier élément est bien terminé
        } else {
            free(current); // Libérer la mémoire pour les étudiants non actifs
        }

        current = next;
    }

    // Sauvegarder la liste filtrée dans le fichier
    ListToFile(filteredList ,filename );

    // Libérer la liste filtrée
    freeStudentList(filteredList);
}
bool searchStudent(const char *FILENAME, int *position) {
     FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return false;
    }

    int id;
    printf("\nEnter Matricule to search: ");
    scanf("%d", &id);



    student s;
    bool found = false;
    while (fscanf(file,
            "%d %49s %49s %d %2s "
            "%9s %f %d "
            "%9s %f %d "
            "%9s %f %d "
            "%9s %f %d "
            "%f %d",
            &s.id, s.familyName, s.firstName, &s.yearOfBirth, s.Class,
            s.subjects[0].subj,  &s.subjects[0].note, &s.subjects[0].coeff,
            s.subjects[1].subj,  &s.subjects[1].note, &s.subjects[1].coeff,
            s.subjects[2].subj,  &s.subjects[2].note, &s.subjects[2].coeff,
            s.subjects[3].subj,  &s.subjects[3].note, &s.subjects[3].coeff,
            &s.avg, (int *)&s.exist) == 19) {

        if (s.id == id && s.exist == 0) {  // Make sure to use s.exist == false
            found = true;
            break;
        }
    }
    fclose(file);

    if (!found) {
        *position = 0;
        printf("Student not found.\n");
    } else {
        *position = id;
        display_student(&s);
    }

    return found;
}

void modifyStudent(student *student_list, const char *filename, int id) {
    if (!student_list) {
        printf("The student list is empty.\n");
        return;
    }

    // Search for the student node by ID
    student *current = student_list;
    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (!current) {
        printf("Student with ID %d not found.\n", id);
        return;
    }
    printf("Student with ID %d found. Starting modification.\n", id);

    int choice;
    float newGrade;

    do {
        printf("\nWhat would you like to modify?\n");
        printf("1. Family name\n");
        printf("2. First name\n");
        printf("3. Year of birth\n");
        printf("4. Class\n");
        printf("5. Subject grade\n");
        printf("0. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("New family name: ");
                scanf("%s", current->familyName);
                break;
            case 2:
                printf("New first name: ");
                scanf("%s", current->firstName);
                break;
            case 3:
                printf("New year of birth: ");
                scanf("%d", &current->yearOfBirth);
                break;
            case 4:
                printf("New class: ");
                scanf("%s", current->Class);
                break;
            case 5:
                printf("Enter subject index (1-4) \n1-SFSD\n2-OOP\n3-ANALYSIS\n4-ALGEBRA \n: ");
                int index;
                scanf("%d", &index);
                if (index >= 1 && index <= 4) {
                    printf("Enter new grade: ");
                    scanf("%f", &newGrade);
                    current->subjects[index-1].note = newGrade;
                    float average = calculateAverage(current);
                    printf("New average: %.2f\n", average);
                } else {
                    printf("Invalid subject index.\n");
                }
                break;
            case 0:
                printf("Modification complete.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    // Write the updated list back to the file
    ListToFile(student_list, filename);
    printf("Student list successfully updated in the file.\n");
}

void  update(const char *studentfile,const char *updatefile){
    FILE *f=fopen(studentfile,"r");
    FILE *upd=fopen(updatefile,"r+");

    //make usre both files exist
    if (f==NULL){
        printf("ERROR, %s doesn't exist.\n",studentfile);
        exit(-1);
    }
    if (upd==NULL){
        printf("ERROR, %s doesn't exist.\n",updatefile);
        fclose(f);
        exit(-2);
    }

    time_t lastupd;
    if (fscanf(upd,"%ld",&lastupd)!=1){
        //first run case
        physicalDeletion("studentlist.txt");
        lastupd = time(NULL);
        fprintf(upd,"%ld",lastupd);
        printf("%s updated successfully for the first time!!\n",studentfile);
        fclose(f);
        fclose(upd);
        return;
    }

    time_t now=time(NULL);

    //check if the difference between now and last update date is a week
    if (difftime(now,lastupd)>=7*24*60*60){
        physicalDeletion(studentfile);
        printf("%s upddated successfully!\n",studentfile);
        fclose(upd);
        upd=fopen(updatefile,"w");
        if (upd==NULL){
            printf("ERROR, impossible to open %s for writing.\n",updatefile);
            fclose(f);
            exit(-4);
        }
        fprintf(upd,"%ld",now);
    }

    fclose(upd);
    fclose(f);
}


int main()
{
     FILE *studentFile = fopen("studentlist.txt","r");

     if (studentFile== NULL) {
        printf("ERROR openning the file");
        return -1;
    }

    student *head_of_std_list = FileToList(studentFile);
    int last_id=getLastID(&head_of_std_list);

    int choice;

    update("studentlist.txt","updateDateFile.txt");

    do {

        printf("\t\tENSTA STUDENT MANAGEMENT SYSTEM\n");
        printf(" 1-Add a new student\n 2-searching for a student\n 3-modifing a student's information\n 4-logical deletion\n 5-data extraction\n 6-reorganization (physical deletion)\n 0-exit\n");
        printf("\tenter your choice : ");
        scanf("%d",&choice);
        switch (choice) {
            case 1 :{
                addStudent(&head_of_std_list,last_id);
                break;
            }
            case 2 :{
                int i;
                bool isexist=searchStudent("studentlist.txt",&i);
                if (isexist){
                    char modf;
                    printf("The position : %d",i);
                    printf("do you want to modify the student's information? (Y/N)\n");
                    do {
                        scanf(" %c",&modf);
                        modf = toupper(modf);
                        if (modf=='Y'){
                            modifyStudent(&head_of_std_list,"studentlist.txt",i);
                            break;
                        }
                        else if (modf=='N')
                            break;
                        else
                            printf("please answer with Y if yes, N otherwise\n");
                    }while((modf!='Y')&&(modf!='N'));
                }
                else {
                    printf("Student not found.\n");
                    break;
                }
            }
            case 3 :{
                int givId;
                printf("enter the ID of the student you want to modifie his information : \n");
                scanf("%d",&givId);
                modifyStudent(head_of_std_list,"studentlist.txt",givId);
                break;
            }
            case 4 :{
                printf("Loading students from file...\n");
                student *head_of_std_list = FileToList("studentlist.txt");
                if (!head_of_std_list) {
                    printf("No students found in the file.\n");
                    return 1;
                }
                printf("Students loaded successfully. Proceeding to logical deletion.\n");
                int id;
                printf("\nEnter id to search: ");
                scanf("%d", &id);
                if (SearchStudentToDelete(head_of_std_list, id)) {
                    logicalDelete(head_of_std_list, id);
                    printf("Saving updated list to file...\n");

                }
                ListToFile(head_of_std_list, "studentlist.txt");
                freeStudentList(head_of_std_list);
                break;
            }
            case 5 :{
                displayByClass(&head_of_std_list);
                break;
            }
            case 6 :{
                FILE *updfile=fopen("updateDateFile.txt","r");
                if (updfile==NULL){
                    printf("ERROR, the update file can't be opened.\n");
                    return -1;
                }
                time_t lastupd;
                if (fscanf(updfile, "%ld", &lastupd) != 1) {
                    printf("ERROR, Failed to read the last update date from the file.\n");
                    fclose(updfile);
                    return -2;
                }
                struct tm *date = localtime(&lastupd);
                printf("your file is updated weekly.\n");
                printf("last update date : %s",asctime(date));
                printf("Do you want to update it again? (Y/N)\n");
                char userupd;
                do {
                    scanf(" %c",&userupd);
                    userupd = toupper(userupd);
                    if (userupd=='Y'){
                        physicalDeletion("studentlist.txt");
                        break;
                    }
                    else if (userupd=='N')
                        break;
                    else
                        printf("please answer with Y if yes, N otherwise\n");
                }while((userupd!='Y')&&(userupd!='N'));
                fclose(updfile);
                break;
            }
            case 0 :{
                printf("Exiting the system.\n");
                break;
            }
            default:
                printf("Invalid option, please try again.\n");
                break;
        }
    } while (choice!=0);



    return 0;
}
