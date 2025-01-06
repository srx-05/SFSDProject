#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Définition des structures
typedef struct Subject {
    char subj[10];
    float note;
    int coeff;
} Subject;

typedef struct Student {
    int id;
    char familyName[50];
    char firstName[50];
    int yearOfBirth;
    char Class[3];
    Subject subjects[4];
    float avg;
    int exist;
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

        // Lire les données selon le format correct
        int readItems = fscanf(file,
                               "%d %49s %49s %d %2s "
                               "%9s %f %d "
                               "%9s %f %d "
                               "%9s %f %d "
                               "%9s %f %d "
                               "%f %d",
                               &newStudent->id, newStudent->familyName, newStudent->firstName, &newStudent->yearOfBirth, newStudent->Class,
                               newStudent->subjects[0].subj, &newStudent->subjects[0].note, &newStudent->subjects[0].coeff,
                               newStudent->subjects[1].subj, &newStudent->subjects[1].note, &newStudent->subjects[1].coeff,
                               newStudent->subjects[2].subj, &newStudent->subjects[2].note, &newStudent->subjects[2].coeff,
                               newStudent->subjects[3].subj, &newStudent->subjects[3].note, &newStudent->subjects[3].coeff,
                               &newStudent->avg, &newStudent->exist);

        if (readItems == EOF) {
            free(newStudent); // Libérer l'allocation inutilisée
            break;
        }

        if (readItems != 19) {
            fprintf(stderr, "Erreur de lecture des données d'un étudiant. Entrées lues : %d\n", readItems);
            free(newStudent);
            continue;
        }

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

    for (Student* current = head; current; current = current->next) {
        if (current->exist == 0) { // Garder seulement les étudiants où exist == 0
            fprintf(file, "%d %s %s %d %s ",
                    current->id, current->familyName, current->firstName,
                    current->yearOfBirth, current->Class);
            for (int i = 0; i < 4; i++) {
                fprintf(file, "%s %.2f %d ",
                        current->subjects[i].subj, current->subjects[i].note, current->subjects[i].coeff);
            }
            fprintf(file, "%.2f %d\n", current->avg, current->exist);
        }
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
        fprintf(stderr, "Erreur lors du chargement des étudiants depuis le fichier : %s\n", filename);
        return;
    }

    ListToFile(filename, studentList);

    freeStudentList(studentList);
}

// Fonction principale
int main() {
    const char* filename = "camarche.txt";

    printf("Chargement des étudiants...\n");
    Student* studentList = FileToList(filename);
    if (studentList) {
        freeStudentList(studentList);
    }

    printf("Suppression physique...\n");
    physicalDeletion(filename);

    printf("Suppression physique effectuée avec succès.\n");
    return 0;
}