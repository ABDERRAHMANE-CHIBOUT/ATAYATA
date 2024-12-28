#ifndef COURSE_H_INCLUDED
#define COURSE_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
//the same comment in student.h
typedef struct course{
    int course_id;
    char course_name[40];
    char instructor[30];
}course;
typedef struct maillonCourse{
    course value;
    struct maillonCourse *FG;
    struct maillonCourse *FD;
} maillonCourse;
typedef maillonCourse* arbreCourse;


void initArbreCourse(arbreCourse *a);

void allocateNodeCourse(arbreCourse *a);

arbreCourse FGCourse(arbreCourse a);
arbreCourse FDCourse(arbreCourse a);

void affFGCourse(arbreCourse a,arbreCourse b);
void affFDCourse(arbreCourse a,arbreCourse b);

void valueCourse(arbreCourse a,course *valeur);
void scanCourse(course *c);
void affValueCourse(arbreCourse a,course value);


arbreCourse insertNodeCourseId(arbreCourse a, course value);
arbreCourse insertNodeCourseName(arbreCourse a, course value);
arbreCourse insertNodeCourseInstructor(arbreCourse a, course value);


arbreCourse parse_course_csv_course_Id(char *inputFileName);
arbreCourse parse_course_csv_course_name(char *inputFileName);
arbreCourse parse_course_csv_course_instructor(char *inputFileName);


arbreCourse parcoureArbreCourse(arbreCourse Arbre,FILE *f);
bool serialize_course_csv_course_Id(char *inputFileName, arbreCourse Arbre, char *modeDAccee);
bool serialize_course_csv_course_name(char *inputFileName, arbreCourse Arbre, char *modeDAccee);
bool serialize_course_csv_instructor(char *inputFileName, arbreCourse Arbre, char *modeDAccee);

void rech_cour_node_id(arbreCourse a,int x);
void rech_cour_node_course_name(arbreCourse a,char x[]);
void rech_cour_node_instructor(arbreCourse a,char x[]);

void rech_cour_node_Not_id(arbreCourse a, int x);
void rech_cour_node_Not_course_name(arbreCourse a,char x[]);
void rech_cour_node_Not_instructor(arbreCourse a,char x[]);

void rech_cour_node_sup_id(arbreCourse a,int x);
void rech_cour_node_sup_course_name(arbreCourse a,char x[]);
void rech_cour_node_sup_instructor(arbreCourse a,char x[]);

void rech_cour_node_sup_eg_id(arbreCourse a,int x);
void rech_cour_node_sup_eg_course_name(arbreCourse a,char x[]);
void rech_cour_node_sup_eg_instructor(arbreCourse a,char x[]);

void rech_cour_node_inf_id(arbreCourse a,int x);
void rech_cour_node_inf_course_name(arbreCourse a,char x[]);
void rech_cour_node_inf_instructor(arbreCourse a,char x[]);

void rech_cour_node_inf_eg_id(arbreCourse a,int x);
void rech_cour_node_inf_eg_course_name(arbreCourse a,char x[]);
void rech_cour_node_inf_eg_instructor(arbreCourse a,char x[]);

void print_tree_course(arbreCourse Arbre);
void closeCourse(arbreCourse a);
#endif // COURSE_H_INCLUDED
