#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

// Function prototypes
student *createnode(student std);
int append_node(student **head, student *new_node);
student *FileToList(const char *file_name);
void ListToFile(student *head, const char *filename);
void LogicalDeleting(student *head);
void free_list(student *head);

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

bool SearchStudentToDelete(const char *FILENAME) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return false;
    }

    int matricule;
    printf("\nEnter Matricule to search: ");
    scanf("%d", &matricule);

    student s;
    bool found = false;
    int position = 0; // Moved to the inner scope.

    while (fscanf(file,
                  "%d %49s %49s %d %2s "
                  "%9s %f %d "
                  "%9s %f %d "
                  "%9s %f %d "
                  "%9s %f %d "
                  "%f %d",
                  &s.id, s.familyName, s.firstName, &s.yearOfBirth, s.Class,
                  s.subjects[0].subj, &s.subjects[0].note, &s.subjects[0].coeff,
                  s.subjects[1].subj, &s.subjects[1].note, &s.subjects[1].coeff,
                  s.subjects[2].subj, &s.subjects[2].note, &s.subjects[2].coeff,
                  s.subjects[3].subj, &s.subjects[3].note, &s.subjects[3].coeff,
                  &s.avg, (int *)&s.exist) == 19) {
        position++; // Increment position only within the loop.

        if (s.id == matricule) { // Match found.
            found = true;
            break;
        }
                  }
    fclose(file);

    if (!found) {
        printf("Student not found.\n");
    } else {
        display_student(&s);
    }

    return found;
}

student *createnode(student std) {
    student *newnode = (student *)malloc(sizeof(student));
    if (!newnode) {
        perror("Memory allocation failed");
        return NULL;
    }
    *newnode = std;
    newnode->next = NULL;
    return newnode;
}

int append_node(student **head, student *new_node) {
    if (new_node == NULL) {
        fprintf(stderr, "Error: new_node is NULL.\n");
        return -1;
    }
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return 0;
    }

    student *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    return 0;
}
student *FileToList(const char *file_name) {
    student std1;
    student *head = NULL;
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Error opening the file");
        return NULL;
    }
    while (fscanf(file,
                  "%d %49s %49s %d %2s "
                  "%9s %f %d "
                  "%9s %f %d "
                  "%9s %f %d "
                  "%9s %f %d "
                  "%f %d",
                  &std1.id, std1.familyName, std1.firstName, &std1.yearOfBirth, std1.Class,
                  std1.subjects[0].subj, &std1.subjects[0].note, &std1.subjects[0].coeff,
                  std1.subjects[1].subj, &std1.subjects[1].note, &std1.subjects[1].coeff,
                  std1.subjects[2].subj, &std1.subjects[2].note, &std1.subjects[2].coeff,
                  std1.subjects[3].subj, &std1.subjects[3].note, &std1.subjects[3].coeff,
                  &std1.avg, &std1.exist) == 19) {
        student *std_node = createnode(std1);
        if (!std_node) {
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
        return;
    }

    student *current = head;
    while (current != NULL) {
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
        current = current->next;
    }
    fclose(file);
}

void LogicalDeleting(student *head) {
    if (head == NULL) {
        printf("No students found in the list.\n");
        return;
    }

    student *current = head;
    while (current != NULL) {
        if (!current->exist) {
            printf("The student exists. Do you want to delete? [y/n]: ");
        } else {
            printf("The student is deleted. Recover? [y/n]: ");
        }

        char choice;
        do {
            choice = getchar();
        } while (choice == '\n');

        if ((choice == 'y' || choice == 'Y') && current->exist) {
            current->exist = 1;  // Mark as recovered
            printf("the existing flag is edited successfully!\n");
            break;
        } else if ((choice == 'y' || choice == 'Y') && !current->exist) {
            current->exist = 0;  // Mark as deleted
            printf("the existing flag is edited successfully!\n");
            break;
        } else {
            printf("Please enter a valid choice.\n");
        }
        current = current->next;
    }
}

void free_list(student *head) {
    while (head) {
        student *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    printf("Loading students from file...\n");
    student *students = FileToList("studentlist.txt");
    if (!students) {
        printf("No students found in the file.\n");
        return 1;
    }

    printf("Students loaded successfully. Proceeding to logical deletion.\n");
    if (SearchStudentToDelete("studentlist.txt")) {
      LogicalDeleting(students);
    }


    printf("Saving updated list to file...\n");
    ListToFile(students, "studentlist.txt");
    printf("File updated successfully.\n");

    free_list(students);
    return 0;
}
