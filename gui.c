#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "your_structs_and_functions.h" // Replace with your file containing the student-related functions and structures

// Global variables
HINSTANCE hInst;
student *studentList = NULL;
HWND inputBox, infoBox, yesButton, noButton;

// Function prototypes
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateMainMenu(HWND hwnd);
void LoadStudentList();
void ShowLogicalDeletionPrompt(HWND hwnd);
void HandleLogicalDeletion(HWND hwnd, int id);

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    HWND hwnd;
    MSG msg;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "StudentManagementSystem";

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Failed to register window class.", "Error", MB_ICONERROR);
        return 1;
    }

    hwnd = CreateWindow(
        wc.lpszClassName,
        "Student Management System",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) {
        MessageBox(NULL, "Failed to create window.", "Error", MB_ICONERROR);
        return 1;
    }

    hInst = hInstance;

    // Load the student list from the file
    LoadStudentList();

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

// Window procedure (handles user interactions)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND logicalDelButton;

    switch (msg) {
        case WM_CREATE:
            CreateMainMenu(hwnd);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 1: // Logical Deletion button
                    ShowLogicalDeletionPrompt(hwnd);
                    break;

                case 2: { // Confirm ID entered
                    char buffer[10];
                    GetWindowText(inputBox, buffer, sizeof(buffer));
                    int id = atoi(buffer);
                    if (id > 0) {
                        HandleLogicalDeletion(hwnd, id);
                    } else {
                        MessageBox(hwnd, "Please enter a valid ID.", "Error", MB_ICONERROR);
                    }
                    break;
                }

                case 3: // Yes button (modify exist flag)
                    MessageBox(hwnd, "Student's status has been successfully updated.", "Success", MB_OK | MB_ICONINFORMATION);
                    ShowWindow(yesButton, SW_HIDE);
                    ShowWindow(noButton, SW_HIDE);
                    ShowWindow(infoBox, SW_HIDE);
                    ShowWindow(inputBox, SW_HIDE);
                    break;

                case 4: // No button (cancel modification)
                    MessageBox(hwnd, "Operation canceled.", "Info", MB_OK | MB_ICONINFORMATION);
                    ShowWindow(yesButton, SW_HIDE);
                    ShowWindow(noButton, SW_HIDE);
                    ShowWindow(infoBox, SW_HIDE);
                    ShowWindow(inputBox, SW_HIDE);
                    break;
            }
            break;

        case WM_DESTROY:
            freeStudentList(studentList);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

// Create main menu with buttons
void CreateMainMenu(HWND hwnd) {
    CreateWindow("button", "Logical Deletion",
                 WS_VISIBLE | WS_CHILD,
                 50, 50, 200, 40,
                 hwnd, (HMENU)1, hInst, NULL);
}

// Load student list from file
void LoadStudentList() {
    studentList = FileToList("studentlist.txt");
    if (!studentList) {
        MessageBox(NULL, "Failed to load student list from file.", "Error", MB_ICONERROR);
    }
}

// Show prompt to input student ID for logical deletion
void ShowLogicalDeletionPrompt(HWND hwnd) {
    CreateWindow("static", "Enter Student ID:",
                 WS_VISIBLE | WS_CHILD,
                 50, 100, 200, 20,
                 hwnd, NULL, hInst, NULL);

    inputBox = CreateWindow("edit", "",
                            WS_VISIBLE | WS_CHILD | WS_BORDER,
                            50, 130, 100, 20,
                            hwnd, NULL, hInst, NULL);

    CreateWindow("button", "Submit",
                 WS_VISIBLE | WS_CHILD,
                 160, 130, 80, 20,
                 hwnd, (HMENU)2, hInst, NULL);
}

// Handle logical deletion process
void HandleLogicalDeletion(HWND hwnd, int id) {
    student *current = studentList;

    while (current != NULL) {
        if (current->id == id) {
            char info[256];
            sprintf(info, "ID: %d\nName: %s %s\nClass: %s\nAverage: %.2f\nExist: %s\n\nModify status?",
                    current->id, current->familyName, current->firstName, current->Class, current->avg,
                    current->exist ? "Deleted" : "Active");

            infoBox = CreateWindow("static", info,
                                   WS_VISIBLE | WS_CHILD,
                                   50, 170, 300, 80,
                                   hwnd, NULL, hInst, NULL);

            yesButton = CreateWindow("button", "Yes",
                                     WS_VISIBLE | WS_CHILD,
                                     50, 260, 80, 30,
                                     hwnd, (HMENU)3, hInst, NULL);

            noButton = CreateWindow("button", "No",
                                    WS_VISIBLE | WS_CHILD,
                                    150, 260, 80, 30,
                                    hwnd, (HMENU)4, hInst, NULL);
            return;
        }
        current = current->next;
    }
    MessageBox(hwnd, "Student not found.", "Error", MB_ICONERROR);
}
