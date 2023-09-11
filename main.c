#include "school.h"
#include "userInput.h"
#include <stdio.h>
#include <string.h>

int main()
{
    // Up to handle assign grade

    Student_t ** students = NULL;
    Teacher_t ** teachers = NULL;
    Grade_t ** grades = NULL;

    int numStudents = 0, numTeachers = 0, numGrades = 0;

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
            addStudent(&students, &numStudents, &grades, &numGrades);
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
    freeGrades(&grades);
    freeStudents(students);
    freeTeachers(teachers);
    return 0;
}
