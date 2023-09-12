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

        switch (choice)
        {
        case 1:
            addStudent(&students, &numStudents, &grades, &numGrades);
            printf("Student: %d, %s, numStudents: %d\n", students[numStudents-1]->studentID, students[numStudents-1]->name, numStudents);
            printf("Grade: %d, %d, %s, numGrades: %d\n", grades[numGrades-1]->studentID, grades[numGrades-1]->score, grades[numGrades-1]->subject, numGrades);
            //printf("num grades found: %d\n", findNumGradesByStudentId(grades, numGrades, students[numStudents-1]->studentID));=
            Grade_t **foundGrades = findGradesByStudentId(grades, numGrades, students[numStudents-1]->studentID);
            int currInd = 0;
            while(foundGrades[currInd] != NULL)
            {
                printf("Subject %d -> %s\n", currInd, foundGrades[currInd]->subject);
                currInd++;
            }
            int *foundStudentIds = findStudentsBySubject(grades, numGrades, "cs");
            currInd = 0;
            while(foundStudentIds[currInd] != -1)
            {
                printf("%d: Student ID %d\n", currInd, foundStudentIds[currInd]);
                currInd++;
            }
            break;
        case 2:
            addTeacher(&teachers, &numTeachers);
            printf("Teacher number: %d, Teacher ID: %d, Teacher name: %s\n", numTeachers,teachers[0]->teacherID, teachers[0]->name);
            break;
        case 3:
            //handleAssignGrade(grades, &gradeCount, students, studentCount);
            break;
        case 4:
            // getInputSubject(subject);
            // findStudentBySubject(students, studentCount, subject);
            break;
        case 5:
            // getInputSubject(subject);
            // findTeacherBySubject(teachers, teacherCount, subject);
            break;
        case 6:
            // handleFindGradesByStudentAndSubject(grades, gradeCount);
            break;
        case 0:
            printf("Exiting the program.\n");
            return 0;
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
