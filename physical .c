#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Définition des structures
typedef struct {
    char module[20];
    int coef;
    float note;
} Sub;

typedef struct Student {
    int id;
    char name[50];
    char fname[50];
    int birth;
    int group;
    Sub notes[4];
    float avg;
    bool exist;
    struct Student* next;
} Student;

// Fonction FileToList : Charger les étudiants depuis un fichier
Student* FileToList(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

    Student* head = NULL;
    Student* tail = NULL;

    while (1) {
        Student* newStudent = (Student*)malloc(sizeof(Student));
        if (!newStudent) {
            perror("Erreur d'allocation mémoire");
            break;
        }

        if (fscanf(file, "%d %s %s %d %d", &newStudent->id, newStudent->name, newStudent->fname,
                   &newStudent->birth, &newStudent->group) != 5) {
            free(newStudent);
            break;
        }

        for (int i = 0; i < 4; i++) {
            fscanf(file, "%s %d %f", newStudent->notes[i].module, &newStudent->notes[i].coef,
                   &newStudent->notes[i].note);
        }

        fscanf(file, "%f %d", &newStudent->avg, (int*)&newStudent->exist);

        newStudent->next = NULL;

        if (!head) {
            head = tail = newStudent;
        } else {
            tail->next = newStudent;
            tail = newStudent;
        }
    }

    fclose(file);
    return head;
}

// Fonction ListToFile : Sauvegarder les étudiants actifs
void ListToFile(const char* filename, Student* head) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    Student* current = head;
    while (current) {
        if (current->exist) {
            fprintf(file, "%d %s %s %d %d ", current->id, current->name, current->fname,
                    current->birth, current->group);
            for (int i = 0; i < 4; i++) {
                fprintf(file, "%s %d %.2f ", current->notes[i].module,
                        current->notes[i].coef, current->notes[i].note);
            }
            fprintf(file, "%.2f %d\n", current->avg, current->exist);
        }
        current = current->next;
    }

    fclose(file);
}

// Fonction pour libérer la mémoire
void freeStudentList(Student* head) {
    Student* current = head;
    while (current) {
        Student* temp = current;
        current = current->next;
        free(temp);
    }
}

// Fonction de suppression physique
void physicalDeletion(const char* filename) {
    Student* studentList = FileToList(filename);
    if (!studentList) {
        printf("Erreur lors du chargement des étudiants.\n");
        return;
    }

    ListToFile(filename, studentList);

    freeStudentList(studentList);
}

// Fonction principale
int main() {
    const char* filename = "students.txt";

    physicalDeletion(filename);

    printf("Suppression physique effectuée avec succès.\n");
    return 0;
}