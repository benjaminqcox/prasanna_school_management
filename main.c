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

    // This value will be n so to access final array element, you need n-1
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

        printf("Enter your choice: ");
        int choice = getIntInputInRange(0, 6);

        char * chosenSubject = NULL;
        int * studentIds = NULL;
        int studentId;
        Grade_t **foundGrades = NULL;
        Grade_t *finalGrade = NULL;


        switch (choice)
        {
        case 1:
            addStudent(&students, &numStudents, &grades, &numGrades);
            break;
        case 2:
            addTeacher(&teachers, &numTeachers);
            printf("Teacher number: %d, Teacher ID: %d, Teacher name: %s\n", numTeachers,teachers[numTeachers-1]->teacherID, teachers[numTeachers-1]->name);
            break;
        case 3:
            assignGrade(&grades, &numGrades);
            break;
        case 4:
            chosenSubject = getStringInput();
            studentIds = findStudentIdsBySubject(grades, numGrades, chosenSubject);
            printStudentsFromIds(students, numStudents, studentIds);
            break;
        case 5:
            // getInputSubject(subject);
            // findTeacherBySubject(teachers, teacherCount, subject);
            break;
        case 6:
            studentId = getIntInput(); // Need to verify this student exists
            chosenSubject = getStringInput(); // Need to verify subject exists
            foundGrades = findGradesByStudentId(grades, numGrades, studentId);
            finalGrade = findStudentsGradeBySubject(foundGrades, chosenSubject);
            // Ensure final grade is not null before print
            printf("Student ID: %d, Subject: %s, Score: %d\n", finalGrade->studentID, finalGrade->subject, finalGrade->score);
            break;
        case 0:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
    freeGrades(&grades, numGrades);
    freeStudents(students, numStudents);
    freeTeachers(teachers, numTeachers);
    grades = NULL;
    students = NULL;
    teachers = NULL;
    return 0;
}
