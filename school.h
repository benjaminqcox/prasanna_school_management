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
void freeGrades(Grade_t *** grades, int numGrades);
void freeStudents(Student_t ** students, int numStudents);
void freeTeachers(Teacher_t ** teachers, int numTeachers);
Student_t *findStudentById(Student_t **students, int numStudents, int id);
Grade_t **findGradesByStudentId(Grade_t **grades, int numGrades, int id);
int countFoundGrades(Grade_t **grades);
Grade_t *findStudentsGradeBySubject(Grade_t **grades, char *subject);
int *findStudentIdsBySubject(Grade_t **grades, int numGrades, char *subject);
void addEmptyGrade(Grade_t ***grades, int *numGrades,  int studentId, char * subject);
void addStudent(Student_t ***students, int *numStudents, Grade_t ***grades, int *numGrades);
void addTeacher(Teacher_t ***teachers, int *numTeachers);
void assignGrade(Grade_t ***grades, int *numGrades);
void printStudentsFromIds(Student_t **students, int numStudents, int *studentIds);
void printGrades(Grade_t **grades);
void findTeacherBySubject(Teacher_t *teachers, int teacherCount, const char *subject);
void findGradesByStudentAndSubject(Grade_t *grades, int gradeCount, int studentID, const char *subject);
void handleFindGradesByStudentAndSubject(Grade_t *grades, int gradeCount);

#endif // SCHOOL_H
