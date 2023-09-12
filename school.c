#include "school.h"
#include "userInput.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_SCORE -1

void freeGrades(Grade_t *** grades, int numGrades)
{
    for (int i = 0; i < numGrades; i++)
    {
        free((*grades)[i]);
        grades[i] = NULL;
    }
    free(*grades);
    *grades = NULL;
}

void freeStudents(Student_t ** students, int numStudents)
{
    for (int i = 0; i < numStudents; i++)
    {
        free(students[i]);
        students[i] = NULL;
    }
    free(*students);
    *students = NULL;
}

void freeTeachers(Teacher_t ** teachers, int numTeachers)
{
    for (int i = 0; i < numTeachers; i++)
    {
        free(teachers[i]);
        teachers[i] = NULL;
    }
    free(*teachers);
    *teachers = NULL;
}

Student_t *findStudentById(Student_t **students, int numStudents, int id)
{
    // Loop through all students and compare the student id to the chosen id
    // If found, return that value otherwise return NULL
    for (int i = 0; i < numStudents; i++)
    {
        if (students[i]->studentID == id)
        {
            return students[i];
        }
    }
    printf("No student found with that ID.");
    return NULL;
}

Grade_t **findGradesByStudentId(Grade_t **grades, int numGrades, int id)
{
    // Initialise the grade storing a pointer to pointers
    Grade_t **foundGrades = NULL;
    // Set num grades counter to 0
    int numGradesFound = 0;
    // Go through all the grades stored in grades*
    for (int i = 0; i < numGrades; i++)
    {
        // If current grade is equal to the chosen id
        if (grades[i]->studentID == id)
        {
            // if the id matches, reallocate memory equal to the size of:
            // number of found grades + 2 = found grades + 1 new space + a null terminator needed for searching
            // multiplied by the size of a Grade_t pointer
            foundGrades = (Grade_t **)realloc(foundGrades, (numGradesFound + 2) * sizeof(Grade_t *));
            // Ensure the memory was allocated correctly
            if(foundGrades == NULL)
            {
                // If memory allocation failed, cleanup assigned memory and exit safely
                fprintf(stderr, "Could not allocate memory.\n");
                freeGrades(&foundGrades);
                foundGrades = NULL;
                exit(EXIT_FAILURE);
            }
            // Add the new grade to the end of the array
            foundGrades[numGradesFound] = grades[i];
            // Set the null terminator (memory has been saved for this)
            foundGrades[numGradesFound + 1] = NULL;
            // Grade has been set so increment the number of grades found
            numGradesFound++;
        }
    }
    // Output to the user the number of grades found
    if (numGradesFound == 0)
    {
        printf("No grades found related to the student ID: %d.\n", id);
    }
    else
    {
        printf("%d grades found for that student.\n", numGradesFound);
    }
    return foundGrades;
}

int findNumGradesByStudentId(Grade_t **grades, int numGrades, int id)
{
    // Find the number of occurences of a student id in the grades array
    int numGradesFound = 0;
    for (int i = 0; i < numGrades; i++)
    {
        if (grades[i]->studentID == id)
        {
            numGradesFound++;
        }
    }
    return numGradesFound;
}

int *findStudentsBySubject(Grade_t **grades, int numGrades, char *subject)
{
    // Initialise the found student ids and temp found student ids to NULL
    int *foundStudentIds = NULL, *tempFoundStudentIds = NULL;
    // Set counter to 0
    int numStudentsFound = 0;
    // Loop through all grades
    for (int i = 0; i < numGrades; i++)
    {
        // If the current grade has a subject equal to the chosen subject
        if (strncmp(grades[i]->subject, subject, strlen(grades[i]->subject)) == 0)
        {
            // Reallocate the memory to reflect a new item being added and a NULL terminator on the end
            tempFoundStudentIds = realloc(foundStudentIds, (numStudentsFound + 2) * sizeof(Student_t *));
            // Ensure memory was allocated correctly
            if(tempFoundStudentIds == NULL)
            {
                // If memory was not allocated correctly, cleanup the currently allocated variables
                fprintf(stderr, "Could not allocate memory.\n");
                free(foundStudentIds);
                free(tempFoundStudentIds);
                foundStudentIds = NULL;
                tempFoundStudentIds = NULL;
                exit(EXIT_FAILURE);
            }
            // Set the found student ids to the temp student ids so the temp student ids pointer can have realloacted memory
            // without affecting already stored values
            foundStudentIds = tempFoundStudentIds;
            // Set the penultimate value to the current value of grades id
            foundStudentIds[numStudentsFound] = grades[i]->studentID;
            // Set the final element of found students to -1 (terminator)
            foundStudentIds[numStudentsFound + 1] = -1;
            numStudentsFound++;
        }
    }
    if (numStudentsFound == 0)
    {
        printf("No students found studying %s.\n", subject);
    }
    else
    {
        printf("%d students found studying %s.\n", numStudentsFound, subject);
    }
    return foundStudentIds;
}


void addEmptyGrade(Grade_t ***grades, int *numGrades, int studentId, char *subject)
{
    // Add jsdoc to explain the arguments and code functionality
    // need triple pointer in order to change the reference to the pointer array
    size_t subjectLen = strlen(subject);
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
        freeGrades(&tempGrades);
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
    tempGrades[*numGrades] = newGrade;

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
    Student_t **tempStudents = realloc(*students, sizeof(Student_t *) * ((*numStudents) + 1));

    // Get student and grade information
    printf("Enter student ID: ");
    int studentId = getIntInput();
    printf("Enter student name: ");
    char * studentName = getStringInput();
    printf("Enter subject studying by student: ");
    char * studentSubject = getStringInput();

    // Allocate memory for the new students name
    newStudent->name = (char *)malloc(strlen(studentName));

    // Ensure memory was allocated correctly
    if (newStudent == NULL || tempStudents == NULL || newStudent->name == NULL)
    {
        // If memory was not allocated, cleanup memory and exit
        fprintf(stderr, "Could not allocate memory.\n");
        free(newStudent->name);
        free(newStudent);
        freeStudents(tempStudents, numStudents + 1);
        exit(EXIT_FAILURE);
    }

    // Set student and subject information
    newStudent->studentID = studentId;
    strlcpy(newStudent->name, studentName, sizeof(newStudent->name));
    addEmptyGrade(grades, numGrades, studentId, studentSubject);

    // Add the new student to the end of the tempStudents array
    tempStudents[*numStudents] = newStudent;

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
    size_t teacherNameLen = strlen(teacherName);
    size_t teacherSubjectLen = strlen(teacherSubject);

    // Allocate memory to store the teacher and teacher information
    Teacher_t **tempTeachers = realloc(*teachers, sizeof(Teacher_t*) * ((*numTeachers) + 1));
    printf("Sizeof tempTeachers: %lu, Numteachers: %d\n", sizeof(*tempTeachers), *numTeachers);
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
        free(newTeacher->subject);
        free(newTeacher);
        freeTeachers(tempTeachers);
        exit(EXIT_FAILURE);
    }

    // Set the id of newTeacher
    newTeacher->teacherID = teacherId;

    // Set the values of newTeacher name and subject
    strlcpy(newTeacher->name, teacherName, teacherNameLen);
    strlcpy(newTeacher->subject, teacherSubject, teacherSubjectLen);

    // Add the new teacher to the teachers array
    tempTeachers[*numTeachers] = newTeacher;
    *teachers = tempTeachers;

    // Increment the number of teachers by one
    (*numTeachers)++;
}

// Function to assign a grade to a student
void assignGrade(Grade_t *grades, int *gradeCount, Student_t *students, int studentID, int studentCount, const char *subject, int score)
{
    // printf("Enter the student ID: ");
    // int studentId = getIntInput();
    // // Add check for student exists
    // printf("Enter the subject: ");
    // char *subject = getStringInput();
    // // Add check for subject extisting
    // printf("Enter the student score: ");
    // int studentScore = getIntInputInRange(0, 100);
    // // Check if there's space in the grades array

    //     if (studentIndex != -1)
    //     {
    //         // Assign the grade
    //         Grade_t newGrade;
    //         newGrade.studentID = studentID;
    //         strlcpy(newGrade.subject, subject, sizeof(newGrade.subject));
    //         newGrade.score = score;
    //         grades[*gradeCount] = newGrade;
    //         (*gradeCount)++;
    //         printf("Grade assigned successfully.\n");
    //         return *gradeCount;
    //     }
    //     else
    //     {
    //         printf("Student not found with ID %d studying %s. Cannot assign grade.\n", studentID, subject);
    //         return *gradeCount;
    //     }
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
    // char subject[MAX_STRING_LENGTH];
    // int studentID;
    // getInputSubject(subject);
    // printf("Enter the student ID: ");
    // scanf("%d", &studentID);
    // findGradesByStudentAndSubject(grades, gradeCount, studentID, subject);
}

// Function to find grades by student and subject
void findGradesByStudentAndSubject(Grade_t *grades, int gradeCount, int studentID, const char *subject)
{
    // Implement the logic to find grades by student and subject
  
}
