#include "school.h"
#include "userInput.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_SCORE -1

void freeGrades(Grade_t *** grades)
{
    size_t gradeSize = sizeof(Grade_t);
    int numGrades = sizeof(**grades)/gradeSize;
    for (int i = 0; i < numGrades; i++)
    {
        free((*grades)[i]);
        grades[i] = NULL;
    }
    free(*grades);
    *grades = NULL;
}

void freeStudents(Student_t ** students)
{
    size_t studentSize = sizeof(Student_t);
    int numstudents = sizeof(*students)/studentSize;
    for (int i = 0; i < numstudents; i++)
    {
        free(students[i]);
        students[i] = NULL;
    }
    free(*students);
    *students = NULL;
}

void freeTeachers(Teacher_t ** teachers)
{
    size_t teacherSize = sizeof(Teacher_t);
    int numteachers = sizeof(**teachers)/teacherSize;
    for (int i = 0; i < numteachers; i++)
    {
        free(teachers[i]);
        teachers[i] = NULL;
    }
    free(*teachers);
    *teachers = NULL;
}

void addEmptyGrade(Grade_t ***grades, int *numGrades, int studentId, char *subject)
{
    // Add jsdoc to explain the arguments and code functionality
    // need triple pointer in order to change the reference to the pointer array
    size_t subjectLen = strlen(subject) + 1;
    size_t gradeSize = sizeof(Grade_t);
    Grade_t *newGrade = (Grade_t *)malloc(gradeSize);
    // Reallocate the memory storing all students to have enough space for another student
    Grade_t **tempGrades = realloc(*grades, gradeSize * ((*numGrades) + 1));
    // Allocate memory for the subject to be stored (+1 for the null terminator)
    newGrade->subject = (char *)malloc(subjectLen);
    // Ensure memory was allocated correctly
    if (newGrade == NULL || tempGrades == NULL || newGrade->subject == NULL)
    {
        // If memory was not allocated, cleanup any memory exit safely
        fprintf(stderr, "Could not allocate memory.\n");
        free(newGrade->subject);
        free(newGrade);
        freeGrades(tempGrades);
        free(tempGrades);
        exit(EXIT_FAILURE);
    }
    // Copy the contents of subject to newGrade subject
    strlcpy(newGrade->subject, subject, subjectLen);
    // Add student id to grade
    newGrade->studentID = studentId;
    // Set default value for the score that means it has not been assigned a grade
    newGrade->score = EMPTY_SCORE;
    // Add the new grade to the end of tempGrades
    tempGrades[(*numGrades) + 1] = newGrade;

    // Change the memory reference to the start of the newly allocated memory
    *grades = tempGrades;

    // Increment the number of grades stored in grades
    (*numGrades)++;
}

// Function to add a new student
void addStudent(Student_t ***students, int *numStudents, Grade_t ***grades, int *numGrades)
{
    // Allocate memory for a new student to be created and point to it
    Student_t *newStudent = (Student_t *)malloc(sizeof(Student_t));
    // Reallocate the memory storing all students to have enough space for another student
    Student_t **tempStudents = realloc(**students, sizeof(Student_t *) * ((*numStudents) + 1));

    // Get student and grade information
    printf("Enter student ID: ");
    int studentId = getIntInput();
    printf("Enter student name: ");
    char * studentName = getStringInput();
    printf("Enter subject studying by student: ");
    char * studentSubject = getStringInput();

    // Allocate memory for the new students name
    newStudent->name = (char *)malloc(strlen(studentName) + 1);

    // Ensure memory was allocated correctly
    if (newStudent == NULL || tempStudents == NULL || newStudent->name == NULL)
    {
        // If memory was not allocated, cleanup memory and exit
        fprintf(stderr, "Could not allocate memory.\n");
        free(newStudent->name);
        free(newStudent);
        freeStudents(tempStudents);
        exit(EXIT_FAILURE);
    }

    // Set student and subject information
    newStudent->studentID = studentId;
    strlcpy(newStudent->name, studentName, strlen(studentName) + 1);
    tempStudents[(*numStudents)+1] = newStudent;
    addEmptyGrade(grades, numGrades, studentId, studentSubject);

    // Add the new student to the end of the tempStudents array
    tempStudents[(*numStudents) + 1] = newStudent;

    // Change the memory reference to the start of the newly allocated memory
    *students = tempStudents;

    // Increment the number of students added by one
    (*numStudents)++;
}

// Function to add a new teacher
void addTeacher(Teacher_t ***teachers, int *numTeachers)
{
    // Get teacher information
    printf("Enter teacher ID: ");
    int teacherId = getIntInput();
    printf("Enter teacher name: ");
    char * teacherName = getStringInput();
    printf("Enter subject taught by the teacher: ");
    char * teacherSubject = getStringInput();

    // Teacher name and subject length
    size_t teacherNameLen = strlen(teacherName) + 1;
    size_t teacherSubjectLen = strlen(teacherSubject) + 1;

    // Allocate memory to store the teacher and teacher information
    Teacher_t **tempTeachers = (Teacher_t **)malloc(sizeof(Teacher_t*) * ((*numTeachers) + 1));
    Teacher_t *newTeacher = (Teacher_t *)malloc(sizeof(Teacher_t));
    newTeacher->name = (char *)malloc(teacherNameLen);
    newTeacher->subject = (char *)malloc(teacherSubjectLen);

    // Ensure memory was allocated correctly
    if (
        tempTeachers == NULL || 
        newTeacher == NULL || 
        newTeacher->name == NULL || 
        newTeacher->subject == NULL
        )
    {
        // If memory was not allocated, cleanup any memory exit safely
        fprintf(stderr, "Could not allocate memory.\n");
        free(newTeacher->name);
        free(newTeacher->name);
        free(newTeacher);
        exit(EXIT_FAILURE);
    }

    // Set the id of newTeacher
    newTeacher->teacherID = teacherId;

    // Set the values of newTeacher name and subject
    strlcpy(newTeacher->name, teacherName, teacherNameLen);
    strlcpy(newTeacher->subject, teacherSubject, teacherSubjectLen);

    // Add the new teacher to the teachers array
    tempTeachers[(*numTeachers)+1] = newTeacher;
    *teachers = tempTeachers;

    // Increment the number of teachers by one
    (*numTeachers)++;
}

// Function to handle assigning a grade
int handleAssignGrade(Grade_t *grades, int *gradeCount, Student_t *students, int studentCount)
{
    char *subject;
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
            strlcpy(newGrade.subject, subject, sizeof(newGrade.subject));
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
