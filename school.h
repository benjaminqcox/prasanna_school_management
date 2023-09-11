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
void freeGrades(Grade_t *** grades);
void freeStudents(Student_t ** students);
void freeTeachers(Teacher_t ** teachers);
void addEmptyGrade(Grade_t ***grades, int *numGrades,  int studentId, char * subject);
void addStudent(Student_t ***students, int *numStudents, Grade_t ***grades, int *numGrades);
void addTeacher(Teacher_t ***teachers, int *numTeachers);
void handleAssignGrade(Grade_t *grades, int *gradeCount, Student_t *students, int studentCount);
void assignGrade(Grade_t *grades, int *gradeCount, Student_t *students, int studentID, int studentCount, const char *subject, int score);
void findStudentBySubject(Student_t *students, int studentCount, const char *subject);
void findTeacherBySubject(Teacher_t *teachers, int teacherCount, const char *subject);
void findGradesByStudentAndSubject(Grade_t *grades, int gradeCount, int studentID, const char *subject);
void handleFindGradesByStudentAndSubject(Grade_t *grades, int gradeCount);

#endif // SCHOOL_H
