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
 
// Define struct for student information 
typedef struct student { 
    int id; 
    char familyname[50]; 
    char firstname[50]; 
    int yearofbirth; 
    char classe[3]; 
    subject subjects[4];
    float avg;
    int exist; 
} student; 
 
// Define struct for a node in the linked list 
typedef struct node { 
    student studentData; 
    struct node *next;
}  
 
float calculateAverage(student* Student) {
    return (Student->subjects[1]->note * 4 + Student->subjects[2]->note * 3 + Student->subjects[3]->note * 2 + Student->subjects[4]->note * 5) / 14.0; 
}
 
// Define struct for a node in the linked list 
typedef struct listnode { 
    student infos; 
    struct listnode *next; 
} node; 
 
// Function to allocate and initialize a new node 
node *createnode(student content) { 
    node *newnode = (node *)malloc(sizeof(node)); 
    if (!newnode) { 
        perror("Memory allocation failed"); 
        return NULL; 
    } 
    newnode->infos = content; 
    newnode->next = NULL; 
    return newnode; 
} 
 
 
 
void modifylistaddnode(node *head, node *newnode) { 
    node *parcour = head; 
 
    // Traverse to the last node in the list 
    while (parcour->next != NULL) { 
        parcour = parcour->next; 
    } 
 
    // Set the new node's ID as the next ID in sequence 
    newnode->infos.id = parcour->infos.id + 1; 
 
    // Link the new node to the end of the list 
    parcour->next = newnode; 
} 
 
 
// Function to find the last ID from the file 
int get_last_id_from_file(FILE *file) { 
   file = fopen( "Listes_Etudiants.txt", "r"); 
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
 
// Procedure to create and add a node with content 
void addstudent(FILE *file, node *head) { 
    subject subjects[4]; 
    student content; 
 
    // Input student details 
    printf("Enter the firstname, family name ,if multiple names or composed family names separe them with the character';':\n"); 
    scanf("%s %s", content.firstname, content.familyname); 
    do { 
        printf("Enter the year of birth:\n"); 
        scanf("%d", &content.yearofbirth); 
       } 
    while((content.yearofbirth<1900 ) || (content.yearofbirth>2025)); 
 
    printf("Enter the class of the student:\n"); 
    scanf("%s", content.classe); 
 
    do 
    { 
        printf("Enter the mark of this student in SFSD:\n"); 
        scanf("%f", &content.subjects[0].note); 
        printf("Enter the mark of this student in POO:\n"); 
        scanf("%f", &content.subjects[1].note); 
        printf("Enter the mark of this student in ANALYSIS:\n"); 
        scanf("%f", &content.subjects[2].note); 
        printf("Enter the mark of this student in Linear Algebra:\n"); 
        scanf("%f", &content.subjects[3].note); 
    } 
    while (((content.subjects[0].note<0)||(content.subjects[0].note>20))||((content.subjects[1].note<0)||(content.subjects[1].note>20))||((content.subjects[2].note<0)||(content.subjects[2].note>20))||((content.subjects[3].note<0)||(content.subjects[3].note>20))); 
    content.exist = true; 
    content.avg = calculateAverag(content);
    
    // Get the last ID from the file and assign the next ID 
    int last_id = get_last_id_from_file(file); 
    content.id = last_id + 1; 
    strcpy(content.subjects[0].subj,"SFSD"); 
    content.subjects[0].coeff=4; 
    strcpy(content.subjects[1].subj,"POO"); 
    content.subjects[1].coeff=3; 
    strcpy(content.subjects[2].subj,"ANMT"); 
    content.subjects[2].coeff=2; 
    strcpy(content.subjects[3].subj,"ALGE"); 
    content.subjects[3].coeff=5; 
 
 
    // Create and add the new node to the list
node *liststud = createnode(content); 
    modifylistaddnode(head, liststud); 
 
    // Open the file to append the new student's information 
    file = fopen("Listes_Etudiants.txt", "a"); 
    if (!file) { 
        printf("Failed to open file for writing.\n"); 
        return; 
    } 
 
    fprintf(file, "id : %d\t  family name : %s\t firstname: %s\t year of birth : %d\t group : %s\t mark of %s : %.2f \t  coeff : %d \tmark of %s : %.2f coeff : %d\t mark of %s : %.2f coeff : %d \t mark of %s : %.2f coeff : %d \t Average : %f \t  FLAG : %d\n", 
            content.id, content.familyname, content.firstname, content.yearofbirth, content.classe, 
            content.subjects[0].subj, content.subjects[0].avg,content.subjects[0].coeff, 
            content.subjects[1].subj, content.subjects[1].avg,content.subjects[1].coeff, 
            content.subjects[2].subj, content.subjects[2].avg,content.subjects[2].coeff, 
            content.subjects[3].subj, content.subjects[3].avg, content.subjects[3].coeff, 
            content.avg,content.exist); 
            
 
    fclose(file); 
} 
 
 
 
int main() 
{ 
    FILE *file; 
    node *head = 
 
 
    
 
 
}
