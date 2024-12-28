#ifndef FOLLOWCOURSE_H_INCLUDED
#define FOLLOWCOURSE_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

typedef struct followCourse {
    int student_id;
    int course_id;
} followCourse;

typedef struct maillonFollowCourse{
    followCourse value;
    struct maillonFollowCourse *FG;
    struct maillonFollowCourse *FD;
} maillonFollowCourse;
typedef maillonFollowCourse* arbreFollowCourse;


void initArbreFollowCourse(arbreFollowCourse *a) ;

void allocateNodeFollowCourse(arbreFollowCourse *a);

arbreFollowCourse FGFollowCourse(arbreFollowCourse a);
arbreFollowCourse FDFollowCourse(arbreFollowCourse a);

void affFGFollowCourse(arbreFollowCourse a,arbreFollowCourse b);
void affFDFollowCourse(arbreFollowCourse a,arbreFollowCourse b);

void scanFollowCourse(followCourse *fc);
followCourse valueFollowCourse(arbreFollowCourse a);
void affValueFollowCourse(arbreFollowCourse a,followCourse value);


arbreFollowCourse insertNodeFollowCourseIdStudent(arbreFollowCourse a, followCourse value);
arbreFollowCourse insertNodeFollowCourseIdCourse(arbreFollowCourse a, followCourse value);


arbreFollowCourse parse_follow_course_csv_student_Id(char *inputFileName);
arbreFollowCourse parse_follow_course_csv_course_Id(char *inputFileName);


arbreFollowCourse parcoureArbreFollowCourse(arbreFollowCourse Arbre,FILE *f);
bool serialize_follow_course_csv_student_Id(char *inputFileName, arbreFollowCourse Arbre, char *modeDAccee);
bool serialize_follow_course_csv_course_Id(char *inputFileName, arbreFollowCourse Arbre, char *modeDAccee);

void print_follow_course_table_header() ;
void print_tree_follow_course(arbreFollowCourse Arbre);
#endif // FOLLOWCOURSE_H_INCLUDED
