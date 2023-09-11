#include "school.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to get user input for subject
void getInputSubject(char *subject)
{
    printf("Enter the subject: ");
    scanf("%s", subject);
}

// Function to add a new student
void addStudent(Student_t **students, Grade_t **grades)
{
    
    size_t studentSize = sizeof(Student_t);
    int numStudents = sizeof(students)/studentSize;
    // Ensure array size is correct
    printf("%d, %d, %d\n", studentSize, numStudents, studentSize * numStudents);
    // Allocate memory for a new student to be created and point to it
    Student_t *newStudent = (Student_t *)malloc(studentSize);
    // Reallocate the memory storing all students to have enough space for another student
    Student_t *tempStudents = reallocf(*students, studentSize * numStudents);
    // Ensure memory was allocated correctly
    if (newStudent == NULL || tempStudents == NULL)
    {
        // If memory was not allocated, exit safely
        fprintf(stderr, "Could not allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter student ID: ");
    scanf("%d", &newStudent.studentID);
    printf("Enter student name: ");
    scanf("%s", newStudent.name);
    printf("Enter subject studying by student: ");
    scanf("%s", newGrade.subject);
    newGrade.studentID = newStudent.studentID;
    newGrade.score = -1;
    students[*studentCount] = newStudent;
    (*studentCount)++;

    grades[*gradeCount] = newGrade;
    (*gradeCount)++;
    // printf("Student added successfully.\n");
    int remainingSize = 100 - *studentCount;
    printf("Remaining array size for students: %d\n", remainingSize);

    return *studentCount;
}

// Function to add a new teacher
int addTeacher(Teacher_t *teachers, int *teacherCount)
{
    // Implement the logic to add a new teacher
    if (*teacherCount < 100)
    {
        Teacher_t newTeacher;
        printf("Enter teacher ID: ");
        scanf("%d", &newTeacher.teacherID);
        printf("Enter teacher name: ");
        scanf("%s", newTeacher.name);
        printf("Enter subject taught by the teacher: ");
        scanf("%s", newTeacher.subject);
        teachers[*teacherCount] = newTeacher;
        (*teacherCount)++;
        // printf("Teacher added successfully.\n");
        int remainingSize = 100 - *teacherCount;
        printf("Remaining array size for teachers: %d\n", remainingSize);

        return *teacherCount;
    }
    else
    {
        printf("Teacher array is full. Cannot add more teachers.\n");
        return *teacherCount;
    }
}

// Function to handle assigning a grade
int handleAssignGrade(Grade_t *grades, int *gradeCount, Student_t *students, int studentCount)
{
    char subject[MAX_STRING_LENGTH];
    int studentID, score;
    getInputSubject(subject);
    printf("Enter the student ID: ");
    scanf("%d", &studentID);
    printf("Enter the student score: ");
    scanf("%d", &score);
    return assignGrade(grades, gradeCount, students, studentID, studentCount, subject, score);
}

// Function to assign a grade to a student
int assignGrade(Grade_t *grades, int *gradeCount, Student_t *students, int studentID, int studentCount, const char *subject, int score)
{
    // Check if there's space in the grades array
    if (*gradeCount < 100)
    {
        // Check if the student exists
        int studentIndex = -1;
        for (int i = 0; i < studentCount; i++)
        {
            if (students[i].studentID == studentID && strcmp(students[i].subject, subject) == 0)
            {
                studentIndex = i;
                break;
            }
        }

        if (studentIndex != -1)
        {
            // Assign the grade
            Grade_t newGrade;
            newGrade.studentID = studentID;
            strncpy(newGrade.subject, subject, sizeof(newGrade.subject));
            newGrade.score = score;
            grades[*gradeCount] = newGrade;
            (*gradeCount)++;
            printf("Grade assigned successfully.\n");
            return *gradeCount;
        }
        else
        {
            printf("Student not found with ID %d studying %s. Cannot assign grade.\n", studentID, subject);
            return *gradeCount;
        }
    }
    else
    {
        printf("Grade database is full. Cannot assign more grades.\n");
        return *gradeCount;
    }
}

// Function to find students by subject
void findStudentBySubject(Student_t *students, int studentCount, const char *subject)
{
    // Implement the logic to find students by subject
   
}

// Function to find teachers by subject
void findTeacherBySubject(Teacher_t *teachers, int teacherCount, const char *subject)
{
    // Implement the logic to find teachers by subject
   
}

// Function to handle finding grades by student and subject
void handleFindGradesByStudentAndSubject(Grade_t *grades, int gradeCount)
{
    char subject[MAX_STRING_LENGTH];
    int studentID;
    getInputSubject(subject);
    printf("Enter the student ID: ");
    scanf("%d", &studentID);
    findGradesByStudentAndSubject(grades, gradeCount, studentID, subject);
}

// Function to find grades by student and subject
void findGradesByStudentAndSubject(Grade_t *grades, int gradeCount, int studentID, const char *subject)
{
    // Implement the logic to find grades by student and subject
  
}
