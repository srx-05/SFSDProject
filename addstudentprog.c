#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Define struct for a subject
typedef struct subject {
    char module[5];
    float avg;
    int coeff;
} subject;

// Define struct for student information
typedef struct student {
    int id;
    char firstname[50];
    char familyname[50];
    int yearofbirth;
    char classe[3];
    subject subjects[4];
    float avg;
    bool exist;
} student;

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

// Function to append a node to the linked list
void append_node(node **head, student content) {
    node *new_node = createnode(content);
    if (!new_node) return;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

// Function to initialize students and return the head of the list
node *initialize_students() {
    node *head = NULL;
   student students[40] = {
    {1, "Ali", "Ahmed", 2001, "3A", {{"SFSD", 15.5, 4}, {"POO", 12.0, 3}, {"ANMT", 14.0, 2}, {"ALGE", 16.5, 5}}, true},
    {2, "Moulay", "Sarah", 2000, "2B", {{"SFSD", 18.0, 4}, {"POO", 16.5, 3}, {"ANMT", 17.0, 2}, {"ALGE", 19.0, 5}}, true},
    {3, "Zouaoui", "Sarah", 1999, "3A", {{"SFSD", 13.0, 4}, {"POO", 11.0, 3}, {"ANMT", 15.5, 2}, {"ALGE", 14.0, 5}}, true},
    {4, "Benmoussa", "Karim", 2002, "1C", {{"SFSD", 10.0, 4}, {"POO", 9.5, 3}, {"ANMT", 12.0, 2}, {"ALGE", 11.0, 5}}, true},
    {5, "Cherif", "Yasmine", 2003, "2B", {{"SFSD", 19.0, 4}, {"POO", 18.5, 3}, {"ANMT", 17.5, 2}, {"ALGE", 20.0, 5}}, true},
    {6, "Haddad", "Amine", 2001, "3A", {{"SFSD", 14.0, 4}, {"POO", 13.0, 3}, {"ANMT", 15.0, 2}, {"ALGE", 16.0, 5}}, false},
    {7, "Mezouar", "Fatima", 2002, "1A", {{"SFSD", 16.0, 4}, {"POO", 15.0, 3}, {"ANMT", 14.5, 2}, {"ALGE", 18.0, 5}}, true},
    {8, "Khellaf", "Mourad", 2000, "2B", {{"SFSD", 12.0, 4}, {"POO", 10.5, 3}, {"ANMT", 11.0, 2}, {"ALGE", 13.0, 5}}, true},
    {9, "Saidi", "Lila", 2003, "1C", {{"SFSD", 8.0, 4}, {"POO", 9.0, 3}, {"ANMT", 7.5, 2}, {"ALGE", 10.0, 5}}, true},
    {10, "Djebbar", "Hamid", 2002, "3A", {{"SFSD", 20.0, 4}, {"POO", 19.5, 3}, {"ANMT", 18.0, 2}, {"ALGE", 17.0, 5}}, true},
    {11, "Belarbi", "Malek", 1998, "3B", {{"SFSD", 15.0, 4}, {"POO", 14.0, 3}, {"ANMT", 12.5, 2}, {"ALGE", 13.0, 5}}, false},
    {12, "Guerfi", "Yacine", 2000, "2A", {{"SFSD", 17.0, 4}, {"POO", 18.0, 3}, {"ANMT", 16.5, 2}, {"ALGE", 19.0, 5}}, true},
    {13, "Amrani", "Samira", 2001, "3A", {{"SFSD", 13.5, 4}, {"POO", 12.0, 3}, {"ANMT", 11.0, 2}, {"ALGE", 14.0, 5}}, false},
    {14, "Rahmouni", "Nadia", 1999, "1B", {{"SFSD", 9.0, 4}, {"POO", 8.5, 3}, {"ANMT", 10.0, 2}, {"ALGE", 9.0, 5}}, true},
    {15, "Kaci", "Lina", 2003, "2B", {{"SFSD", 20.0, 4}, {"POO", 19.5, 3}, {"ANMT", 18.5, 2}, {"ALGE", 20.0, 5}}, true},
    {16, "Boukhelfa", "Adam", 2002, "1C", {{"SFSD", 11.0, 4}, {"POO", 10.5, 3}, {"ANMT", 12.0, 2}, {"ALGE", 10.0, 5}}, false},
    {17, "Saadallah", "Amina", 2001, "3B", {{"SFSD", 14.0, 4}, {"POO", 13.5, 3}, {"ANMT", 14.0, 2}, {"ALGE", 15.0, 5}}, true},
    {18, "Hamdi", "Khaled", 2002, "2A", {{"SFSD", 18.0, 4}, {"POO", 17.0, 3}, {"ANMT", 16.0, 2}, {"ALGE", 19.0, 5}}, true},
    {19, "Belhadi", "Amel", 1998, "1A", {{"SFSD", 10.0, 4}, {"POO", 9.5, 3}, {"ANMT", 8.0, 2}, {"ALGE", 11.0, 5}}, true},
    {20, "Larbi", "Nassim", 2001, "2B", {{"SFSD", 12.5, 4}, {"POO", 13.0, 3}, {"ANMT", 14.0, 2}, {"ALGE", 15.0, 5}}, true},
    {21, "Aouini", "Salima", 2003, "3A", {{"SFSD", 16.5, 4}, {"POO", 17.0, 3}, {"ANMT", 15.0, 2}, {"ALGE", 18.5, 5}}, true},
    {22, "Chikhi", "Reda", 1999, "1B", {{"SFSD", 10.5, 4}, {"POO", 9.0, 3}, {"ANMT", 8.0, 2}, {"ALGE", 12.0, 5}}, false},
    {23, "Medjahdi", "Farid", 2002, "1C", {{"SFSD", 14.0, 4}, {"POO", 13.5, 3}, {"ANMT", 14.0, 2}, {"ALGE", 15.0, 5}}, true},
    {24, "Dib", "Leila", 2003, "3B", {{"SFSD", 19.0, 4}, {"POO", 18.5, 3}, {"ANMT", 17.0, 2}, {"ALGE", 20.0, 5}}, true},
    {25, "Nezzar", "Fouad", 2001, "2A", {{"SFSD", 15.0, 4}, {"POO", 14.5, 3}, {"ANMT", 13.0, 2}, {"ALGE", 14.0, 5}}, false},
    {26, "Belaid", "Amine", 1999, "2B", {{"SFSD", 10.0, 4}, {"POO", 11.0, 3}, {"ANMT", 12.0, 2}, {"ALGE", 13.0, 5}}, true},
    {27, "Cherrad", "Wafa", 2000, "1A", {{"SFSD", 18.0, 4}, {"POO", 19.0, 3}, {"ANMT", 17.5, 2}, {"ALGE", 20.0, 5}}, true},
    {28, "Fekir", "Imane", 2001, "2C", {{"SFSD", 13.0, 4}, {"POO", 14.0, 3}, {"ANMT", 12.5, 2}, {"ALGE", 15.0, 5}}, true},
    {29, "Khir", "Redouane", 2003, "3A", {{"SFSD", 17.0, 4}, {"POO", 16.0, 3}, {"ANMT", 15.5, 2}, {"ALGE", 18.0, 5}}, true},
    {30, "Selmani", "Hiba", 1998, "1B", {{"SFSD", 9.0, 4}, {"POO", 8.5, 3}, {"ANMT", 10.0, 2}, {"ALGE", 9.5, 5}}, false},
    {31, "Abdi", "Oussama", 2002, "2A", {{"SFSD", 14.0, 4}, {"POO", 13.0, 3}, {"ANMT", 12.5, 2}, {"ALGE", 15.0, 5}}, true},
    {32, "Ziani", "Malika", 1999, "3B", {{"SFSD", 19.5, 4}, {"POO", 20.0, 3}, {"ANMT", 18.5, 2}, {"ALGE", 19.0, 5}}, true},
    {33, "Zerouki", "Tarek", 2003, "1C", {{"SFSD", 11.0, 4}, {"POO", 10.0, 3}, {"ANMT", 9.5, 2}, {"ALGE", 12.0, 5}}, true},
    {34, "Mekki", "Soraya", 2000, "3A", {{"SFSD", 16.0, 4}, {"POO", 14.5, 3}, {"ANMT", 15.0, 2}, {"ALGE", 18.0, 5}}, true},
    {35, "Rami", "Omar", 1998, "2C", {{"SFSD", 13.0, 4}, {"POO", 14.0, 3}, {"ANMT", 12.5, 2}, {"ALGE", 15.0, 5}}, true},
    {36, "Bensalem", "Sofia", 2003, "1B", {{"SFSD", 10.0, 4}, {"POO", 9.5, 3}, {"ANMT", 8.5, 2}, {"ALGE", 12.0, 5}}, false},
    {37, "Kamel", "Nadia", 1999, "3C", {{"SFSD", 18.5, 4}, {"POO", 19.0, 3}, {"ANMT", 17.0, 2}, {"ALGE", 20.0, 5}}, true},
    {38, "Hassan", "Samir", 2000, "2A", {{"SFSD", 15.0, 4}, {"POO", 14.0, 3}, {"ANMT", 13.0, 2}, {"ALGE", 16.0, 5}}, true},
    {39, "Merabet", "Nour", 2001, "3B", {{"SFSD", 19.0, 4}, {"POO", 18.5, 3}, {"ANMT", 17.5, 2}, {"ALGE", 20.0, 5}}, false},
    {40, "Saadi", "Riad", 2002, "1C", {{"SFSD", 14.5, 4}, {"POO", 13.0, 3}, {"ANMT", 12.5, 2}, {"ALGE", 15.5, 5}}, true}
};

    for (int i = 0; i < 40; i++) {
        append_node(&head, students[i]);
    }

    return head;
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
        scanf("%f", &content.subjects[0].avg);
        printf("Enter the mark of this student in POO:\n");
        scanf("%f", &content.subjects[1].avg);
        printf("Enter the mark of this student in ANALYSIS:\n");
        scanf("%f", &content.subjects[2].avg);
        printf("Enter the mark of this student in Linear Algebra:\n");
        scanf("%f", &content.subjects[3].avg);
    }
    while (((content.subjects[0].avg<0)||(content.subjects[0].avg>20))||((content.subjects[1].avg<0)||(content.subjects[1].avg>20))||((content.subjects[2].avg<0)||(content.subjects[2].avg>20))||((content.subjects[3].avg<0)||(content.subjects[3].avg>20)));
    content.exist = true;

    // Get the last ID from the file and assign the next ID
    int last_id = get_last_id_from_file(file);
    content.id = last_id + 1;
    strcpy(content.subjects[0].module,"SFSD");
    content.subjects[0].coeff=4;
    strcpy(content.subjects[1].module,"POO");
    content.subjects[1].coeff=3;
    strcpy(content.subjects[2].module,"ANMT");
    content.subjects[2].coeff=2;
    strcpy(content.subjects[3].module,"ALGE");
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

    fprintf(file, "id : %d\t  family name : %s\t firstname: %s\t year of birth : %d\t group : %s\t mark of %s : %.2f \t  coeff : %d \tmark of %s : %.2f coeff : %d\t mark of %s : %.2f coeff : %d \t mark of %s : %.2f coeff : %d \t FLAG : %d\n",
            content.id, content.familyname, content.firstname, content.yearofbirth, content.classe,
            content.subjects[0].module, content.subjects[0].avg,content.subjects[0].coeff,
            content.subjects[1].module, content.subjects[1].avg,content.subjects[1].coeff,
            content.subjects[2].module, content.subjects[2].avg,content.subjects[2].coeff,
            content.subjects[3].module, content.subjects[3].avg, content.subjects[3].coeff,
            content.exist);

    fclose(file);
}



int main()
{
    FILE *file;
    node *head = initialize_students();


   /* //I EXECUTE THIS SECTION ONLY ONE TIME JUST TO FILL UP THE ORIGINAL INFOSSSS

    FILE *file=fopen("Listes_Etudiants.txt","w");
    if(file==NULL)
    {
        printf("didnt oppen sorry :(/n");
    }
    node *parcour=head;
    while(parcour!=NULL)
        {
            fprintf(file,"id : %d\t  family name : %s\t firstname: %s\t year of birth : %d\t group : %s\t mark of %s : %.2f \t  coeff : %d \tmark of %s : %.2f coeff : %d\t mark of %s : %.2f coeff : %d \t mark of %s : %.2f coeff : %d \t FLAG : %d\n",
                parcour->infos.id,parcour->infos.familyname,parcour->infos.firstname,parcour->infos.yearofbirth,
                parcour->infos.classe,
                parcour->infos.subjects[0].module,parcour->infos.subjects[0].avg,parcour->infos.subjects[0].coeff,
                parcour->infos.subjects[1].module,parcour->infos.subjects[1].avg,parcour->infos.subjects[1].coeff,
                parcour->infos.subjects[2].module,parcour->infos.subjects[2].avg,parcour->infos.subjects[2].coeff,
                parcour->infos.subjects[3].module,parcour->infos.subjects[3].avg,parcour->infos.subjects[3].coeff,
                parcour->infos.exist);
        parcour=parcour->next;
        }
    fclose(file);
    */


    addstudent(file,head);

}
