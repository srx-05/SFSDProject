
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char module[20];
    int coef;
    float note;
} Sub;

typedef struct {
    unsigned int id;
    char name[50];
    char fname[50];
    int birth;
    int group;
    Sub notes[4];
    float avg;
    int exist;
} Student;

void physicalDeletion(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "rb");
    FILE *out = fopen(outputFile, "wb");
    
    if (in == NULL || out == NULL) {
        printf("Error opening file!\n");
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    Student temp;
    while (fread(&temp, sizeof(Student), 1, in)) {
        if (temp.exist == 0) {
            fwrite(&temp, sizeof(Student), 1, out);
        }
    }

    fclose(in);
    fclose(out);

    remove(inputFile);
    rename(outputFile, inputFile);
}

int main() {
    const char *inputFile = "students.dat";
    const char *outputFile = "temp.dat";

    physicalDeletion(inputFile, outputFile);

    printf("Physical deletion completed successfully.\n");
    return 0;
}