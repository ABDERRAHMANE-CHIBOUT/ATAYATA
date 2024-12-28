#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

typedef struct student{
    int student_id;
    char name[30];
    int age;
    char major[40];
}student;
typedef struct maillonStudent{
    student value;
    struct maillonStudent *FG;
    struct maillonStudent *FD;
} maillonStudent;
typedef maillonStudent* arbreStudent;


void initArbreStudent(arbreStudent *a);

void allocateNodeStudent(arbreStudent *a);

arbreStudent FGStudent(arbreStudent a);
arbreStudent FDStudent(arbreStudent a);

void affFGStudent(arbreStudent a,arbreStudent b);
void affFDStudent(arbreStudent a,arbreStudent b);

void valueStudent(arbreStudent a,student *valeur);
void scanStudent(student *s);//scan les valeurs avec le clavier
void affValueStudent(arbreStudent a,student value);


//on met le neude dans sa place avec tester son id (cree l'arbre si n'existe pas)
arbreStudent insertNodeStudentId(arbreStudent a, student value);
//on met le neude dans sa place avec tester son nom (cree l'arbre si n'existe pas)
arbreStudent insertNodeName(arbreStudent a,student value);
//on met le neude dans sa place avec tester son age (cree l'arbre si n'existe pas)
arbreStudent insertNodeAge(arbreStudent a ,student value);
//on met le neude dans sa place avec tester son major (cree l'arbre si n'existe pas)
arbreStudent insertNodeMajor(arbreStudent a ,student value);


//cree des arbre apartir d'un fichier(on met en considiration id ou age ou ...)
//il return un arbre trier par le Id
arbreStudent parse_students_csv_student_Id(char *inputFileName);
//il return un arbre trier par le Nom
arbreStudent parse_students_csv_name(char *inputFileName);
//il return un arbre trier par l'Age
arbreStudent parse_students_csv_age(char *inputFileName);
//il return un arbre trier par la Major
arbreStudent parse_students_csv_major(char *inputFileName);


//parcoure l'arbre pour ecrire dans le fichier; On va l'utiliser dans les serialize
void parcoureArbre(arbreStudent Arbre,FILE *f);
//les fonctions serialize are the same (only the name of function is deffrent)
//il faux Arbre==un arbre etre cree par insertId
bool serialize_students_csv_student_Id(char *inputFileName, arbreStudent Arbre, char *modeDAccee);
//il faux Arbre==un arbre etre cree par insertAge
bool serialize_students_csv_age(char *inputFileName, arbreStudent Arbre, char *modeDAccee);
//il faux Arbre==un arbre etre cree par insertName
bool serialize_students_csv_name(char *inputFileName, arbreStudent Arbre, char *modeDAccee);
//il faux Arbre==un arbre etre cree par insertMajor
bool serialize_students_csv_major(char *inputFileName, arbreStudent Arbre, char *modeDAccee);

void rech_stud_node_id(arbreStudent a,int x);
void rech_stud_node_age(arbreStudent a,int x);
void rech_stud_node_major(arbreStudent a,char x[]);
void rech_stud_node_name(arbreStudent a,char x[]);
void rech_stud_node_Not_id(arbreStudent a,int x);
void rech_stud_node_Not_age(arbreStudent a,int x);
void rech_stud_node_Not_major(arbreStudent a,char x[]);
void rech_stud_node_Not_name(arbreStudent a,char x[]);
void rech_stud_node_sup_id(arbreStudent a,int x);
void rech_stud_node_sup_age(arbreStudent a,int x);
void rech_stud_node_sup_name(arbreStudent a,char x[]);
void rech_stud_node_sup_major(arbreStudent a,char x[]);
void rech_stud_node_sup_eg_id(arbreStudent a,int x);
void rech_stud_node_sup_eg_age(arbreStudent a,int x);
void rech_stud_node_sup_eg_major(arbreStudent a,char x[]);
void rech_stud_node_sup_eg_name(arbreStudent a,char x[]);
void rech_stud_node_inf_id(arbreStudent a,int x);
void rech_stud_node_inf_age(arbreStudent a,int x);
void rech_stud_node_inf_major(arbreStudent a,char x[]);
void rech_stud_node_inf_name(arbreStudent a,char x[]);
void rech_stud_node_inf_eg_id(arbreStudent a,int x);
void rech_stud_node_inf_eg_age(arbreStudent a,int x);
void rech_stud_node_inf_eg_major(arbreStudent a,char x[]);
void rech_stud_node_inf_eg_name(arbreStudent a,char x[]);
void countStudentId(arbreStudent a,int *counter);
void print_tree_student(arbreStudent Arbre);
void closeStudent(arbreStudent a);
#endif // STUDENT_H_INCLUDED
