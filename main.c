#include "school.h"
#include "userInput.h"
#include <stdio.h>

int main()
{
    Student_t * students;
    Teacher_t * teachers;
    Grade_t * grades;

    while (1)
    {
        printf("Schools Management System\n");
        printf("Select One of the Options below:\n");
        printf("1. Add Student\n");
        printf("2. Add Teacher\n");
        printf("3. Assign Grade\n");
        printf("4. Find Students by Subject\n");
        printf("5. Find Teacher by Subject\n");
        printf("6. Find Grades by Student and Subject\n");
        printf("0. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent(&students, &grades);
            break;
        case 2:
            addTeacher(&teachers);
            break;
        case 3:
            handleAssignGrade(grades, &gradeCount, students, studentCount);
            break;
        case 4:
            getInputSubject(subject);
            findStudentBySubject(students, studentCount, subject);
            break;
        case 5:
            getInputSubject(subject);
            findTeacherBySubject(teachers, teacherCount, subject);
            break;
        case 6:
            handleFindGradesByStudentAndSubject(grades, gradeCount);
            break;
        case 0:
            printf("Exiting the program.\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
