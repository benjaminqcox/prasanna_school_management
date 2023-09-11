#ifndef SCHOOL_H
#define SCHOOL_H

typedef struct Student
{
    int studentID;
    char * name;
    //char subject[MAX_STRING_LENGTH];
    // May Add more student-related data if needed
} Student_t;

typedef struct Teacher
{
    int teacherID;
    char * name;
    char * subject;
    // May Add more teacher-related data if needed
} Teacher_t;

typedef struct Grade
{
    int studentID;
    char * subject;
    int score;
    // May Add more grade-related data if needed
} Grade_t;

// Function prototypes
int addStudent(Student_t **students, Grade_t **grades)
int addTeacher(Teacher_t *teachers, int *teacherCount);
int assignGrade(Grade_t *grades, int *gradeCount, Student_t *students, int studentID, int studentCount, const char *subject, int score);
void findStudentBySubject(Student_t *students, int studentCount, const char *subject);
void findTeacherBySubject(Teacher_t *teachers, int teacherCount, const char *subject);
void findGradesByStudentAndSubject(Grade_t *grades, int gradeCount, int studentID, const char *subject);

// Function to get user input for subject
void getInputSubject(char *subject);

int handleAssignGrade(Grade_t *grades, int *gradeCount, Student_t *students, int studentCount);
void handleFindGradesByStudentAndSubject(Grade_t *grades, int gradeCount);

#endif // SCHOOL_H
