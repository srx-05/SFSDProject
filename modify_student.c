void modifyStudent(node **head, const char *filename, int id) {
    // Load the list from the file first
    node *student_list = filetolist(filename);
    if (!student_list) {
        printf("Error loading the student list from file.\n");
        return;
    }

    // Search for the student in the list
    node *student_node = search_student(student_list, id);
    if (!student_node) {
        printf("Student with ID %d not found or is deleted.\n", id);
        return;
    }

    student *std = &student_node->studentData;
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
                scanf("%s", std->familyname);
                break;
            case 2:
                printf("New first name: ");
                scanf("%s", std->firstname);
                break;
            case 3:
                printf("New year of birth: ");
                scanf("%d", &std->yearofbirth);
                break;
            case 4:
                printf("New class: ");
                scanf("%s", std->classe);
                break;
            case 5:
                printf("Enter subject index (0-3): ");
                int index;
                scanf("%d", &index);
                if (index >= 0 && index < 4) {
                    printf("Enter new grade: ");
                    scanf("%f", &newGrade);
                    std->subjects[index].note = newGrade;
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

        // Write the updated list back to the file after modification
        list_to_file(student_list, filename);

    } while (choice != 0);
}
