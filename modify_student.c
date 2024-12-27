float calculateAverage(Student* student) {
    return (student->g_sfsd * 4 + student->g_oop * 3 + student->g_ana * 2 + student->g_alg * 5) / 14.0; 
}









void modifyStudent(Student* head, int position) {
    int i = 0;
    Student* current = head;

    // Traverse the linked list to reach the desired position
    while (current != NULL && i < position - 1) { 
        current = current->next; 
        i++;
    }

    if (current != NULL) { // Check if the position is valid
        printf("Modification of student:\n");

        int choice;
        float newGrade;

        do {
            printf("\nWhat would you like to modify?\n");
            printf("1. First name\n");
            printf("2. Last name\n");
            printf("3. Year of birth\n");
            printf("4. Class\n");
            printf("5. Grade of SFSD\n");
            printf("6. Grade of OOP\n");
            printf("7. Grade of Mathematical Analysis\n");
            printf("8. Grade of Linear Algebra\n");
            printf("0. Exit\n");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("New first name: ");
                    scanf("%s", current->first_name);
                    break;
                case 2:
                    printf("New last name: ");
                    scanf("%s", current->last_name);
                    break;
                case 3:
                    printf("New year of birth: ");
                    scanf("%d", &current->year_of_birth);
                    break;
                case 4:
                    printf("New class: ");
                    scanf("%s", current->class);
                    break;
                case 5:
                    printf("Enter the new grade of SFSD: ");
                    scanf("%f", &newGrade);
                    if (newGrade >= 0 && newGrade <= 100) { // Validate grade
                        current->g_sfsd = newGrade;
                        current->average = calculateAverage(current);
                    } else {
                        printf("Invalid grade. Please enter a value between 0 and 100.\n");
                    }
                    break;
                case 6:
                    printf("Enter the new grade of OOP: ");
                    scanf("%f", &newGrade);
                    if (newGrade >= 0 && newGrade <= 100) {
                        current->g_oop = newGrade;
                        current->average = calculateAverage(current);
                    } else {
                        printf("Invalid grade. Please enter a value between 0 and 100.\n");
                    }
                    break;
                case 7:
                    printf("Enter the new grade of Mathematical Analysis: ");
                    scanf("%f", &newGrade);
                    if (newGrade >= 0 && newGrade <= 100) {
                        current->g_ana = newGrade;
                        current->average = calculateAverage(current);
                    } else {
                        printf("Invalid grade. Please enter a value between 0 and 100.\n");
                    }
                    break;
                case 8:
                    printf("Enter the new grade of Linear Algebra: ");
                    scanf("%f", &newGrade);
                    if (newGrade >= 0 && newGrade <= 100) {
                        current->g_alg = newGrade;
                        current->average = calculateAverage(current);
                    } else {
                        printf("Invalid grade. Please enter a value between 0 and 100.\n");
                    }
                    break;
                case 0:
                    printf("Modification complete.\n");
                    break;
                default:
                    printf("Invalid choice.\n");
            }
        } while (choice != 0);
    } else {
        printf("Invalid position.\n");
    }
}
