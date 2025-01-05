#include <stdio.h> 
#include <stdbool.h> 
#include <stdlib.h> 
#include <string.h>

// Define struct for a subject 
typedef struct subject { 
    char subj[10]; 
    float note;
    int coeff;
} subject; 

// Define struct for student information (embedded next pointer)
typedef struct student { 
    int id; 
    char familyname[50]; 
    char firstname[50]; 
    int yearofbirth; 
    char classe[3]; 
    subject subjects[4]; 
    float avg;
    int exist;  
    struct student *next;  // Pointer to next student in linked list
} student; 

// Function to calculate a student's weighted average
float calculateAverage(student* Student) {
    float totalScore = 0;
    int totalCoeff = 0;

    for (int i = 0; i < 4; i++) {
        totalScore += Student->subjects[i].note * Student->subjects[i].coeff;
        totalCoeff += Student->subjects[i].coeff;
    }
    return totalScore / totalCoeff;
}

// Function to allocate and initialize a new student node
student *createStudent(student std) { 
    student *newStudent = (student *)malloc(sizeof(student));

    if (!newStudent) { 
        perror("Memory allocation failed"); 
        return NULL; 
    }

    *newStudent = std;
    newStudent->next = NULL;
    return newStudent;
}

// Function to append a student to the linked list
void appendStudent(student **head, student *newStudent) { 
    if (*head == NULL) { 
        *head = newStudent; 
        return; 
    } 

    student *temp = *head; 
    while (temp->next != NULL) { 
        temp = temp->next; 
    }

    temp->next = newStudent; 
}

// Function to find the last ID from the file
int getLastIDFromFile(FILE *file) { 
    file = fopen("Listes_Etudiants.txt", "r"); 
    if (!file) { 
        printf("Failed to open file for reading.\n"); 
        return 0; // Return 0 if the file doesn't exist or cannot be opened 
    } 

    int last_id = 0; 
    char buffer[512]; // Buffer to read lines from the file 

    // Read the file line by line to find the last ID 
    while (fgets(buffer, sizeof(buffer), file)) { 
        int temp_id; 
        if (sscanf(buffer, "id : %d", &temp_id) == 1) { 
            if (temp_id > last_id) { 
                last_id = temp_id; 
            } 
        } 
    } 

    fclose(file); 
    return last_id; 
}

// Function to create and add a student to the linked list
void addStudent(FILE *file, student **head) { 
    student newStudent; 

    // Input student details 
    printf("Enter the firstname and family name (use ';' to separate multiple names):\n"); 
    scanf("%s %s", newStudent.firstname, newStudent.familyname); 

    do { 
        printf("Enter the year of birth:\n"); 
        scanf("%d", &newStudent.yearofbirth); 
    } while((newStudent.yearofbirth < 1900) || (newStudent.yearofbirth > 2025)); 

    printf("Enter the class of the student:\n"); 
    scanf("%s", newStudent.classe); 

    // Input student marks
    do { 
        printf("Enter the mark of this student in SFSD:\n"); 
        scanf("%f", &newStudent.subjects[0].note); 
        printf("Enter the mark of this student in POO:\n"); 
        scanf("%f", &newStudent.subjects[1].note); 
        printf("Enter the mark of this student in ANALYSIS:\n"); 
        scanf("%f", &newStudent.subjects[2].note); 
        printf("Enter the mark of this student in Linear Algebra:\n"); 
        scanf("%f", &newStudent.subjects[3].note); 
    } while (((newStudent.subjects[0].note < 0) || (newStudent.subjects[0].note > 20)) ||
             ((newStudent.subjects[1].note < 0) || (newStudent.subjects[1].note > 20)) ||
             ((newStudent.subjects[2].note < 0) || (newStudent.subjects[2].note > 20)) ||
             ((newStudent.subjects[3].note < 0) || (newStudent.subjects[3].note > 20)));

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

    // Calculate average
    newStudent.avg = calculateAverage(&newStudent);

    // Get last ID and assign a new ID
    int last_id = getLastIDFromFile(file); 
    newStudent.id = last_id + 1; 

    // Create and add the new student to the list
    student *studentNode = createStudent(newStudent); 
    appendStudent(head, studentNode); 

    // Open the file to append new student's information 
    file = fopen("Listes_Etudiants.txt", "a"); 
    if (!file) { 
        printf("Failed to open file for writing.\n"); 
        return; 
    } 

    fprintf(file, "id : %d\t  family name : %s\t firstname: %s\t year of birth : %d\t class : %s\t "
                  "mark of %s : %.2f coeff : %d\t mark of %s : %.2f coeff : %d\t "
                  "mark of %s : %.2f coeff : %d\t mark of %s : %.2f coeff : %d\t "
                  "Average : %.2f\t FLAG : %d\n",
            newStudent.id, newStudent.familyname, newStudent.firstname, newStudent.yearofbirth, newStudent.classe,
            newStudent.subjects[0].subj, newStudent.subjects[0].note, newStudent.subjects[0].coeff, 
            newStudent.subjects[1].subj, newStudent.subjects[1].note, newStudent.subjects[1].coeff, 
            newStudent.subjects[2].subj, newStudent.subjects[2].note, newStudent.subjects[2].coeff, 
            newStudent.subjects[3].subj, newStudent.subjects[3].note, newStudent.subjects[3].coeff, 
            newStudent.avg, newStudent.exist); 

    fclose(file); 
}

int main() { 
    student *head = NULL;  // Head pointer for the linked list
    FILE *file = NULL;

    addStudent(file, &head); 

    return 0; 
}
