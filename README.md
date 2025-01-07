# ENSTA Student Management System

## Overview
This project implements a **ENSTA Student Management System** for academic institutions to organize and manage student data effectively. The system handles operations such as adding, searching, modifying, and logically deleting student records while ensuring data integrity and efficient file manipulation.

## Features
The Student Management System offers the following functionalities:
1. **Add a Student**: Input new student details, including their grades, and automatically calculate their weighted average.
2. **Search for a Student**: Retrieve and display complete student information based on their unique ID.
3. **Modify Student Details**: Update a student's information, including their grades, and recalculate the weighted average.
4. **Logical Deletion**: Mark a student as deleted without physically removing their data.
5. **Data Extraction by Class**: Extract and display students in a specific class, sorted by their averages in descending order.
6. **Reorganization and Physical Deletion**: Remove logically deleted records from the file, optimizing storage.

## Data Structure
Student data is stored in a structured text file where each line represents a student. The format includes:
- Unique Registration Number
- Name and Surname
- Year of Birth
- Class (e.g., "3A", "2B")
- Grades and coefficients for four subjects:
  - SFSD (4)
  - POO (3)
  - Mathematical Analysis (2)
  - Linear Algebra (5)
- Weighted Average
- Deletion Flag (0 = Active, 1 = Deleted)

## Technical Specifications
- **Programming Language**: C
- **File Handling**: All operations are performed on structured text files with validations to ensure data integrity.

### Validation Rules:
- **Year of Birth**: Must be between 1990 and 2020.
- **Grades**: Must be between 0 and 20.

## Contributors
- SACI Zhour
- ARZIM Sara
- DJEBIR Raounak
- ZEDDOUN Aya
- ABDELKRIM Jazia
- BELOUAHAR Sofia
- DIFFALLAH Imene
**MI2**
