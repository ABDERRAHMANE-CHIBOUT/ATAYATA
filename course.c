#include "course.h"
#include "followCourse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void initArbreCourse(arbreCourse *a) {
    *a = NULL;
}

void allocateNodeCourse(arbreCourse *a){
    *a = (arbreCourse)malloc(sizeof(maillonCourse));
}

arbreCourse FGCourse(arbreCourse a) {
    return a->FG;
}
arbreCourse FDCourse(arbreCourse a) {
    return a->FD;
}

void affFGCourse(arbreCourse a,arbreCourse b) {
    a->FG = b;
}
void affFDCourse(arbreCourse a,arbreCourse b) {
    a->FD = b;
}

void valueCourse(arbreCourse a,course *valeur) {
    valeur->course_id = a->value.course_id;
    strcpy(valeur->course_name , a->value.course_name);
    strcpy(valeur->instructor , a->value.instructor);
}

course valueC(arbreCourse a){
    return a->value;
}
void scanCourse(course *c){
    printf("Id= ");
    scanf("%d",&c->course_id);
    printf("Nom= ");
    fflush(stdin);
    gets(c->course_name);
    printf("Instructor= ");
    fflush(stdin);
    gets(c->instructor);
}
void affValueCourse(arbreCourse a,course valeur) {
    a->value.course_id = valeur.course_id ;
    strcpy(a->value.course_name , valeur.course_name);
    strcpy(a->value.instructor , valeur.instructor);
}


arbreCourse insertNodeCourseId(arbreCourse a, course value) {
    if (a == NULL) {
        arbreCourse p;

        allocateNodeCourse(&p);
        affValueCourse(p, value);
        affFDCourse(p, NULL);
        affFGCourse(p, NULL);
        a = p;
    }else{
        if ( a->value.course_id >= value.course_id ) {
            affFGCourse(a,insertNodeCourseId(FGCourse(a), value));
        } else {
            affFDCourse(a,insertNodeCourseId(FDCourse(a), value));
        }
    }
    return a;
}
arbreCourse insertNodeCourseName(arbreCourse a, course value) {
    if (a == NULL) {
        arbreCourse p;
        allocateNodeCourse(&p);
        affValueCourse(p, value);
        affFDCourse(p, NULL);
        affFGCourse(p, NULL);
        a = p;
    }else{
        if (strcmp(a->value.course_name, value.course_name) >= 0) {
            affFGCourse(a,insertNodeCourseName(FGCourse(a), value));
        } else {
            affFDCourse(a,insertNodeCourseName(FDCourse(a), value));
        }
    }
    return a;
}
arbreCourse insertNodeCourseInstructor(arbreCourse a, course value) {
    if (a == NULL) {
        arbreCourse p;
        allocateNodeCourse(&p);
        affValueCourse(p, value);
        affFDCourse(p, NULL);
        affFGCourse(p, NULL);
        a = p;
    }else{//يجب بدا المقارنة من الخانة4
        if (strcmp(a->value.instructor, value.instructor) >= 0) {
            affFGCourse(a,insertNodeCourseInstructor(FGCourse(a), value));
        } else {
            affFDCourse(a,insertNodeCourseInstructor(FDCourse(a), value));
        }
    }
    return a;
}


arbreCourse parse_course_csv_course_Id(char *inputFileName){
    FILE *f = fopen(inputFileName,"r");

    if (f == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    course temp;
    arbreCourse idArbre;

    initArbreCourse(&idArbre);
    while(fscanf(f, "%d,%40[^,],%30[^\n]%*c", &temp.course_id, temp.course_name, temp.instructor) == 3){
        idArbre=insertNodeCourseId(idArbre,temp);
    }
    fclose(f);
    return idArbre;
}
arbreCourse parse_course_csv_course_name(char *inputFileName){
    FILE *f = fopen(inputFileName,"r");

    if (f == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    course temp;
    arbreCourse nameArbre;

    initArbreCourse(&nameArbre);
    while(fscanf(f, "%d,%40[^,],%30[^\n]%*c", &temp.course_id , temp.course_name, temp.instructor) == 3){
        nameArbre=insertNodeCourseName(nameArbre,temp);
    }
    fclose(f);
    return nameArbre;
}
arbreCourse parse_course_csv_course_instructor(char *inputFileName){
    FILE *f = fopen(inputFileName,"r");

    if (f == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    course temp;
    arbreCourse instructorArbre;

    initArbreCourse(&instructorArbre);
    while(fscanf(f, "%d,%40[^,],%30[^\n]%*c", &temp.course_id , temp.course_name, temp.instructor) == 3){
        instructorArbre=insertNodeCourseInstructor(instructorArbre,temp);
    }
    fclose(f);
    return instructorArbre;
}


arbreCourse parcoureArbreCourse(arbreCourse Arbre,FILE *f){
    course temp;

    if(Arbre!=NULL){
        if(FGCourse(Arbre)!=NULL){
            parcoureArbreCourse(FGCourse(Arbre),f);
        }
        valueCourse(Arbre,&temp);
        fprintf(f, "%d,%s,%s\n", temp.course_id, temp.course_name, temp.instructor);
        if(FDCourse(Arbre)!=NULL){
            parcoureArbreCourse(FDCourse(Arbre),f);
        }
    }
    return Arbre;
}
bool serialize_course_csv_course_Id(char *inputFileName, arbreCourse Arbre, char *modeDAccee){
    FILE *f = fopen(inputFileName,modeDAccee);

    if (f == NULL) {
        printf("Error opening file\n");
        return false;
    }
    Arbre=parcoureArbreCourse(Arbre,f);
    fclose(f);
    return true;
}
bool serialize_course_csv_course_name(char *inputFileName, arbreCourse Arbre, char *modeDAccee){
    FILE *f = fopen(inputFileName,modeDAccee);

    if (f == NULL) {
        printf("Error opening file\n");
        return false;
    }
    Arbre=parcoureArbreCourse(Arbre,f);
    fclose(f);
    return true;
}
bool serialize_course_csv_instructor(char *inputFileName, arbreCourse Arbre, char *modeDAccee){
    FILE *f = fopen(inputFileName,modeDAccee);

    if (f == NULL) {
        printf("Error opening file\n");
        return false;
    }
    Arbre=parcoureArbreCourse(Arbre,f);
    fclose(f);
    return true;
}


void rech_cour_node_id(arbreCourse a,int x){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
    if(value.course_id==x){
        printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
        rech_cour_node_id(FDCourse(a),x);
    }
    else {
        if(value.course_id>x) rech_cour_node_id(FGCourse(a),x);
        else rech_cour_node_id(FDCourse(a),x);
        }
        }}
void rech_cour_node_course_name(arbreCourse a,char x[]){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
    if(strcmp(value.course_name,x)==0){
        printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
        rech_cour_node_course_name(FGCourse(a),x);
    }
    else{
        if(strcmp(value.course_name,x)>0) rech_cour_node_course_name(FGCourse(a),x);
        else rech_cour_node_course_name(FDCourse(a),x);
         }
}
}
void rech_cour_node_instructor(arbreCourse a,char x[]){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
    if(strcmp(value.instructor,x)==0){
        printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
    rech_cour_node_instructor(FGCourse(a),x);
    }
    else{
        if(strcmp(value.instructor,x)>0) rech_cour_node_instructor(FGCourse(a),x);
        else rech_cour_node_instructor(FDCourse(a),x);
        }
}
}

void rech_cour_node_Not_instructor(arbreCourse a,char x[]){
    if(a!=NULL){
        course value;
        valueCourse(a, &value);

        if (strcmp(value.instructor, x) != 0) {
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
        }

        rech_cour_node_Not_instructor(FGCourse(a), x);
        rech_cour_node_Not_instructor(FDCourse(a), x);
}
}
void rech_cour_node_Not_course_name(arbreCourse a,char x[]){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);

        if (strcmp(value.course_name, x) != 0) {
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
        }
    rech_cour_node_Not_course_name(FGCourse(a),x);
    rech_cour_node_Not_course_name(FDCourse(a),x);
}}
void rech_cour_node_Not_id(arbreCourse a, int x) {
    if (a != NULL) {
        course value;
        valueCourse(a, &value);

        if (value.course_id != x) {
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
        }

        rech_cour_node_Not_id(FGCourse(a), x);
        rech_cour_node_Not_id(FDCourse(a), x);
    }
}

void rech_cour_node_sup_id(arbreCourse a,int x){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
        if(value.course_id>x){
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
            rech_cour_node_sup_id(FGCourse(a),x);
            rech_cour_node_sup_id(FDCourse(a),x);
        }
        else {
            rech_cour_node_sup_id(FDCourse(a),x);
        }
}
}
void rech_cour_node_sup_instructor(arbreCourse a,char x[]){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
        if(strcmp(value.instructor,x)>0){
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
            rech_cour_node_sup_instructor(FGCourse(a),x);
            rech_cour_node_sup_instructor(FDCourse(a),x);
        }
        else {
            rech_cour_node_sup_instructor(FDCourse(a),x);
        }
}
}
void rech_cour_node_sup_course_name(arbreCourse a,char x[]){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
        if(strcmp(value.course_name,x)>0){
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
            rech_cour_node_sup_course_name(FGCourse(a),x);
            rech_cour_node_sup_course_name(FDCourse(a),x);
        }
        else {
            rech_cour_node_sup_course_name(FDCourse(a),x);
        }
}
}

void rech_cour_node_sup_eg_id(arbreCourse a,int x){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
        if(value.course_id>=x){
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
            rech_cour_node_sup_eg_id(FGCourse(a),x);
            rech_cour_node_sup_eg_id(FDCourse(a),x);
        }
        else {
            rech_cour_node_sup_eg_id(FDCourse(a),x);
        }
}
}
void rech_cour_node_sup_eg_instructor(arbreCourse a,char x[]){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
        if(strcmp(value.instructor,x)>=0){
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
            rech_cour_node_sup_eg_instructor(FGCourse(a),x);
            rech_cour_node_sup_eg_instructor(FDCourse(a),x);
        }
        else {
            rech_cour_node_sup_eg_instructor(FDCourse(a),x);
        }
}
}
void rech_cour_node_sup_eg_course_name(arbreCourse a,char x[]){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
        if(strcmp(value.course_name,x)>=0){
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
            rech_cour_node_sup_eg_course_name(FGCourse(a),x);
            rech_cour_node_sup_eg_course_name(FDCourse(a),x);
        }
        else {
            rech_cour_node_sup_eg_course_name(FDCourse(a),x);
        }
}
}

void rech_cour_node_inf_id(arbreCourse a,int x){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
        if(value.course_id<x){
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
            rech_cour_node_inf_id(FGCourse(a),x);
            rech_cour_node_inf_id(FDCourse(a),x);
        }
        else {
            rech_cour_node_inf_id(FDCourse(a),x);
        }
}
}
void rech_cour_node_inf_instructor(arbreCourse a,char x[]){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
        if(strcmp(value.instructor,x)<0){
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
            rech_cour_node_inf_instructor(FGCourse(a),x);
            rech_cour_node_inf_instructor(FDCourse(a),x);
        }
        else {
            rech_cour_node_inf_instructor(FDCourse(a),x);
        }
}
}
void rech_cour_node_inf_course_name(arbreCourse a,char x[]){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
        if(strcmp(value.course_name,x)<0){
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
            rech_cour_node_inf_course_name(FGCourse(a),x);
            rech_cour_node_inf_course_name(FDCourse(a),x);
        }
        else {
            rech_cour_node_inf_course_name(FDCourse(a),x);
        }
}
}

void rech_cour_node_inf_eg_id(arbreCourse a,int x){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
        if(value.course_id<=x){
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
            rech_cour_node_inf_eg_id(FGCourse(a),x);
            rech_cour_node_inf_eg_id(FDCourse(a),x);
        }
        else {
            rech_cour_node_inf_eg_id(FDCourse(a),x);
        }
}
}
void rech_cour_node_inf_eg_instructor(arbreCourse a,char x[]){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
        if(strcmp(value.instructor,x)<=0){
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
            rech_cour_node_inf_eg_instructor(FGCourse(a),x);
            rech_cour_node_inf_eg_instructor(FDCourse(a),x);
        }
        else {
            rech_cour_node_inf_eg_instructor(FDCourse(a),x);
        }
}
}
void rech_cour_node_inf_eg_course_name(arbreCourse a,char x[]){
    if(a!=NULL){
        course value;
        valueCourse(a,&value);
        if(strcmp(value.course_name,x)<=0){
            printf("| %-10d | %-30s | %-20s |\n", value.course_id, value.course_name, value.instructor);
            rech_cour_node_inf_eg_course_name(FGCourse(a),x);
            rech_cour_node_inf_eg_course_name(FDCourse(a),x);
        }
        else {
            rech_cour_node_inf_eg_course_name(FDCourse(a),x);
        }
}
}

void countCourseId(arbreCourse a,int *counter){
    while(a!=NULL && FDCourse(a)!=NULL){
        a = FDCourse(a);
    }

    valueCourse(a,counter);
}

void insertCourse(const char *input ,arbreCourse arbres[],int *courseIdCount) {
    course c;
    *courseIdCount += 1;
    c.course_id = *courseIdCount;
    // Get the inputs from the command
    int result = sscanf(input, "insert course \"%31[^\"]\" \"%31[^\"]\"", c.course_name, c.instructor);
    // Check if it was successfully scanned
    if (result == 2) {
        int length = strlen(c.course_name);
        if (length <= 2) {
            printf("Invalid input format.\n");
            return 1;
        }

        if (c.course_name[0] == '\"' && c.course_name[length - 1] == '\"') {
            memmove(c.course_name, c.course_name + 1, length - 2);
            c.course_name[length - 2] = '\0';
        }

        length = strlen(c.instructor);
        if (length <= 2) {
            printf("Invalid input format.\n");
            return 1;
        }

        if (c.instructor[0] == '\"' && c.instructor[length - 1] == '\"') {
            memmove(c.instructor, c.instructor + 1, length - 2);
            c.instructor[length - 2] = '\0';
        }
                printf("successfully inserted : %s %s .\n",c.course_name,c.instructor);
        for (int i = 0; i < 3; i++) {
            // Insert the student into the tree
            switch (i) {
                case 0:
                    insertNodeCourseId(arbres[i], c);
                    break;
                case 1:
                    insertNodeCourseName(arbres[i], c);
                    break;
                case 2:
                    insertNodeCourseInstructor(arbres[i], c);
                    break;
            }
        }
        return; // Indicates successful execution
    } else {
        printf("Invalid input format\n");
        return ; // Return a non-zero value to indicate an error
    }
}

void print_course_table_header() {
    printf(" ____________ ________________________________ ______________________ \n");
    printf("| %-10s | %-30s | %-20s |\n", "ID", "Nom", "Instructeur");
    printf("|------------|--------------------------------|----------------------|\n");
}

void print_tree_course(arbreCourse Arbre) {
    course c;

    if (Arbre != NULL) {
        if (FGCourse(Arbre) != NULL) {
            print_tree_course(FGCourse(Arbre));
        }

        valueCourse(Arbre, &c);
        printf("| %-10d | %-30s | %-20s |\n", c.course_id, c.course_name, c.instructor);

        if (FDCourse(Arbre) != NULL) {
            print_tree_course(FDCourse(Arbre));
        }
    }
}

void closeCourse(arbreCourse a){
    if (a == NULL) {
        return;
    }
    closeCourse(FGStudent(a));
    closeCourse(FDStudent(a));
    free(a);
}


void deltree_c_id(arbreCourse *c_id,arbreCourse *c_name,arbreCourse *c_instr,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    if(*c_id!=NULL){arbreCourse d=FDCourse(*c_id),g=FGCourse(*c_id);deltree_c_id(&d,c_name,c_instr,f_s,f_c) ; deltree_c_id(&g,c_name,c_instr,f_s,f_c);
    del_c_name(valueC(*c_id),1,c_id,c_name,c_instr,f_s,f_c);del_c_instr(valueC(*c_id),1,c_id,c_name,c_instr,f_s,f_c);
    followCourse f;f.course_id=valueC(*c_id).course_id;del_f_c(f,0,f_s,f_c);free(*c_id);}
}
void deltree_c_name(arbreCourse *c_id,arbreCourse *c_name,arbreCourse *c_instr,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    if(*c_name!=NULL){arbreCourse d=FDCourse(*c_name),g=FGCourse(*c_name);deltree_c_name(c_id,&d,c_instr,f_s,f_c) ; deltree_c_name(c_id,&g,c_instr,f_s,f_c);
    del_c_id(valueC(*c_name),1,c_id,c_name,c_instr,f_s,f_c);del_c_instr(valueC(*c_name),1,c_id,c_name,c_instr,f_s,f_c);
    followCourse f;f.course_id=valueC(*c_name).course_id;del_f_c(f,0,f_s,f_c);free(*c_name);}
}
void deltree_c_instr(arbreCourse *c_id,arbreCourse *c_name,arbreCourse *c_instr,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    if(*c_instr!=NULL){arbreCourse d=FDCourse(*c_instr),g=FGCourse(*c_instr);deltree_c_instr(c_id,c_name,&d,f_s,f_c) ; deltree_c_instr(c_id,c_name,&g,f_s,f_c);
    del_c_id(valueC(*c_instr),1,c_id,c_name,c_instr,f_s,f_c);del_c_name(valueC(*c_instr),1,c_id,c_name,c_instr,f_s,f_c);
    followCourse f;f.course_id=valueC(*c_instr).course_id;del_f_c(f,0,f_s,f_c);free(*c_instr);}
}

// supprimer selon "..= s" , b!=0 selon "=id" de s aussi ,b=0 supprimer dans les autres arbres ce qui a supprimer dont l'arbre originalle
void del_c_id(course c,int b,arbreCourse *c_id,arbreCourse *c_name,arbreCourse *c_instr,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    arbreCourse q=*c_id,prec=NULL,p;
    while(q!=NULL){
    if(valueC(q).course_id==c.course_id){
        if(FGCourse(q)==NULL){
        if(prec==NULL)*c_id=FDCourse(q);else{
            if(q==FDCourse(prec))affFDCourse(prec,FDCourse(q));else affFGCourse(prec,FDCourse(q));
        }
        if(b==0){followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);}
        free(q);q=NULL;
        }else{
            if((FGCourse(q)!=NULL)&&((FDCourse(q)==NULL))){
                if(prec==NULL)*c_id=FGCourse(q);else{
                if(q==FDCourse(prec))affFDCourse(prec,FGCourse(q));else affFGCourse(prec,FGCourse(q));}
                p=FGCourse(q);
                if(b==0){followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);}
                free(q);q=p;
            }else{
                p=FDCourse(q);
                while(FGCourse(p)!=NULL)p=FGCourse(p);
                if(prec==NULL)*c_id=FDCourse(q);else{
                if(q==FDCourse(prec))affFDCourse(prec,FDCourse(q));else affFGCourse(prec,FDCourse(q));}
                affFGCourse(p,FGCourse(q));
                if(b==0){followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);}
                free(q);q=FGCourse(p);prec=p;
            }
        }
    }else{prec=q;if(valueC(q).course_id<c.course_id)q=FDCourse(q);else q=FGCourse(q);}
    }
}
void del_c_name(course c,int b,arbreCourse *c_id,arbreCourse *c_name,arbreCourse *c_instr,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    arbreCourse q=*c_name,prec=NULL,p;
    while(q!=NULL){
    if((strcmp(valueC(q).course_name,c.course_name)==0)&&((valueC(q).course_id==c.course_id)||(b==0))){
        if(FGCourse(q)==NULL){
        if(prec==NULL)*c_name=FDCourse(q);else{
            if(q==FDCourse(prec))affFDCourse(prec,FDCourse(q));else affFGCourse(prec,FDCourse(q));
        }
        if(b==0){followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);}
        free(q);q=NULL;
        }else{
            if((FGCourse(q)!=NULL)&&((FDCourse(q)==NULL))){
                if(prec==NULL)*c_name=FGCourse(q);else{
                if(q==FDCourse(prec))affFDCourse(prec,FGCourse(q));else affFGCourse(prec,FGCourse(q));}
                p=FGCourse(q);
                if(b==0){followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);}
                free(q);q=p;
            }else{
                p=FDCourse(q);
                while(FGCourse(p)!=NULL)p=FGCourse(p);
                if(prec==NULL)*c_name=FDCourse(q);else{
                if(q==FDCourse(prec))affFDCourse(prec,FDCourse(q));else affFGCourse(prec,FDCourse(q));}
                affFGCourse(p,FGCourse(q));
                if(b==0){followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);}
                free(q);q=FGCourse(p);prec=p;
            }
        }
    }else{prec=q;if(strcmp(valueC(q).course_name,c.course_name)<0)q=FDCourse(q);else q=FGCourse(q);}
    }
}
void del_c_instr(course c,int b,arbreCourse *c_id,arbreCourse *c_name,arbreCourse *c_instr,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    arbreCourse q=*c_instr,prec=NULL,p;
    while(q!=NULL){
    if((strcmp(valueC(q).instructor,c.instructor)==0)&&((valueC(q).course_id==c.course_id)||(b==0))){
        if(FGCourse(q)==NULL){
        if(prec==NULL)*c_instr=FDCourse(q);else{
            if(q==FDCourse(prec))affFDCourse(prec,FDCourse(q));else affFGCourse(prec,FDCourse(q));
        }
        if(b==0){followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);}
        free(q);q=NULL;
        }else{
            if((FGCourse(q)!=NULL)&&((FDCourse(q)==NULL))){
                if(prec==NULL)*c_instr=FGCourse(q);else{
                if(q==FDCourse(prec))affFDCourse(prec,FGCourse(q));else affFGCourse(prec,FGCourse(q));}
                p=FGCourse(q);
                if(b==0){followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);}
                free(q);q=p;
            }else{
                p=FDCourse(q);
                while(FGCourse(p)!=NULL)p=FGCourse(p);
                if(prec==NULL)*c_instr=FDCourse(q);else{
                if(q==FDCourse(prec))affFDCourse(prec,FDCourse(q));else affFGCourse(prec,FDCourse(q));}
                affFGCourse(p,FGCourse(q));
                if(b==0){followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);}
                free(q);q=FGCourse(p);prec=p;
            }
        }
    }else{prec=q;if(strcmp(valueC(q).instructor,c.instructor)<0)q=FDCourse(q);else q=FGCourse(q);}
    }
}



void del_course(char* part1,char* part2,int b,arbreCourse *c_id,arbreCourse *c_name,arbreCourse *c_instr,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    course c;arbreCourse q,prec=NULL,p;
    c.course_id=atoi(part2);
    strcpy(c.course_name,part2);
    strcpy(c.instructor,part2);
    switch(b){
        case 0:printf("\nChoix non valide!\n");break;
        case 1:
            if(strcmp(part1,"id" )==0)del_c_id(c,0,c_id,c_name,c_instr,f_s,f_c);
            else if(strcmp(part1,"name")==0)del_c_name(c,0,c_id,c_name,c_instr,f_s,f_c);
            else if(strcmp(part1,"instructor")==0)del_c_instr(c,0,c_id,c_name,c_instr,f_s,f_c);
            else printf("\nChoix de la partie 3 non valide!\n");break;
        case 2:
            if(strcmp(part1,"id" )==0){q=*c_id;
            while(q!=NULL){
                if(valueC(q).course_id==c.course_id){
                        p=FDCourse(q);
                    deltree_c_id(&p,c_name,c_instr,f_s,f_c);
                        affFDCourse(q,NULL);prec=q;q=FGCourse(q);
                }else{
                     if(valueC(q).course_id>c.course_id){p=FDCourse(q);deltree_c_id(&p,c_name,c_instr,f_s,f_c);affFDCourse(q,NULL);p=FGCourse(q);}
                     else{p=FGCourse(q);deltree_c_id(&p,c_name,c_instr,f_s,f_c);p=FDCourse(q);affFGCourse(q,NULL);}
                     if(prec==NULL)*c_id=p;else if(q==FDCourse(prec))affFDCourse(prec,p);else affFGCourse(prec,p);
                     del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                     del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                     followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                     free(q);q=p;
                }
              }
            }
            else if(strcmp(part1,"name")==0){q=*c_name;
            while(q!=NULL){
                if(strcmp(valueC(q).course_name,c.course_name)==0){
                        p=FDCourse(q);
                    deltree_c_name(c_id,&p,c_instr,f_s,f_c);
                        affFDCourse(q,NULL);prec=q;q=FGCourse(q);
                }else{
                     if(strcmp(valueC(q).course_name,c.course_name)>0){p=FDCourse(q);deltree_c_name(c_id,&p,c_instr,f_s,f_c);affFDCourse(q,NULL);p=FGCourse(q);}
                     else{p=FGCourse(q);deltree_c_name(c_id,&p,c_instr,f_s,f_c);p=FDCourse(q);affFGCourse(q,NULL);}
                     if(prec==NULL)*c_name=p;else if(q==FDCourse(prec))affFDCourse(prec,p);else affFGCourse(prec,p);
                     del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                     del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                     followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                     free(q);q=p;
                }
              }
            }
            else if(strcmp(part1,"instructor")==0){q=*c_instr;
            while(q!=NULL){
                if(strcmp(valueC(q).instructor,c.instructor)==0){
                        p=FDCourse(q);
                    deltree_c_instr(c_id,c_name,&p,f_s,f_c);
                        affFDCourse(q,NULL);prec=q;q=FGCourse(q);
                }else{
                     if(strcmp(valueC(q).instructor,c.instructor)>0){p=FDCourse(q);deltree_c_instr(c_id,c_name,&p,f_s,f_c);affFDCourse(q,NULL);p=FGCourse(q);}
                     else{p=FGCourse(q);deltree_c_instr(c_id,c_name,&p,f_s,f_c);p=FDCourse(q);affFGCourse(q,NULL);}
                     if(prec==NULL)*c_instr=p;else if(q==FDCourse(prec))affFDCourse(prec,p);else affFGCourse(prec,p);
                     del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                     del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                     followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                     free(q);q=p;
                }
              }
            }
            else printf("\nChoix de la partie 3 non valide!\n");break;
        case 3:
            if(strcmp(part1,"id" )==0){q=*c_id;
                while(q!=NULL ){
                    if(valueC(q).course_id<c.course_id){
                          p=FGCourse(q);
                          deltree_c_id(&p,c_name,c_instr,f_s,f_c);p=FDCourse(q);
                        if(prec==NULL)*c_id=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                    del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueC(q).course_id>c.course_id){prec=q;q=FGCourse(q);}
                    else{if(FGCourse(q)!=NULL){
                            if(valueC(FGCourse(q)).course_id==c.course_id){prec=q;q=FGCourse(q);}
                            else {p=FGCourse(q);deltree_c_id(&p,c_name,c_instr,f_s,f_c);
                            affFGCourse(q,NULL);q=NULL;}
                    }else q=NULL;}}
                }
            }
            else if(strcmp(part1,"name")==0){q=*c_name;
                while(q!=NULL ){
                    if(strcmp(valueC(q).course_name,c.course_name)<0){
                          p=FGCourse(q);
                          deltree_c_name(c_id,&p,c_instr,f_s,f_c);p=FDCourse(q);
                        if(prec==NULL)*c_name=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                    del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueC(q).course_name,c.course_name)>0){prec=q;q=FGCourse(q);}
                    else{if(FGCourse(q)!=NULL){
                            if(strcmp(valueC(FGCourse(q)).course_name,c.course_name)>0){prec=q;q=FGCourse(q);}
                            else {p=FGCourse(q);deltree_c_name(c_id,&p,c_instr,f_s,f_c);
                            affFGCourse(q,NULL);q=NULL;}
                    }else q=NULL;}}
                }
            }
            else if(strcmp(part1,"instructor")==0){q=*c_instr;
                while(q!=NULL ){
                    if(strcmp(valueC(q).instructor,c.instructor)<0){
                          p=FGCourse(q);
                          deltree_c_instr(c_id,c_name,&p,f_s,f_c);p=FDCourse(q);
                        if(prec==NULL)*c_instr=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                    del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueC(q).instructor,c.instructor)>0){prec=q;q=FGCourse(q);}
                    else{if(FGCourse(q)!=NULL){
                            if(strcmp(valueC(FGCourse(q)).instructor,c.instructor)>0){prec=q;q=FGCourse(q);}
                            else {p=FGCourse(q);deltree_c_instr(c_id,c_name,&p,f_s,f_c);
                            affFGCourse(q,NULL);q=NULL;}
                    }else q=NULL;}}
                }
            }
            else printf("\nChoix de la partie 3 non valide!\n");break;
        case 4:
            if(strcmp(part1,"id" )==0){q=*c_id;
                while(q!=NULL ){
                    if(valueC(q).course_id>c.course_id){
                          p=FDCourse(q);
                          deltree_c_id(&p,c_name,c_instr,f_s,f_c);p=FGCourse(q);
                        if(prec==NULL)*c_id=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                    del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueC(q).course_id<c.course_id){prec=q;q=FDCourse(q);}
                    else{p=FDCourse(q);deltree_c_id(&p,c_name,c_instr,f_s,f_c);affFDCourse(q,NULL);q=NULL;}
                    }
                }
            }
            else if(strcmp(part1,"name")==0){q=*c_name;
                while(q!=NULL ){
                    if(strcmp(valueC(q).course_name,c.course_name)>0){
                          p=FDCourse(q);
                          deltree_c_name(c_id,&p,c_instr,f_s,f_c);p=FGCourse(q);
                        if(prec==NULL)*c_name=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                    del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueC(q).course_name,c.course_name)<0){prec=q;q=FDCourse(q);}
                    else{p=FDCourse(q);deltree_c_name(c_id,&p,c_instr,f_s,f_c);affFDCourse(q,NULL);q=NULL;}
                    }
                }
            }
            else if(strcmp(part1,"instructor")==0){q=*c_instr;
                while(q!=NULL ){
                    if(strcmp(valueC(q).instructor,c.instructor)>0){
                          p=FDCourse(q);
                          deltree_c_instr(c_id,c_name,&p,f_s,f_c);p=FGCourse(q);
                        if(prec==NULL)*c_instr=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                    del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueC(q).instructor,c.instructor)<0){prec=q;q=FDCourse(q);}
                    else{p=FDCourse(q);deltree_c_instr(c_id,c_name,&p,f_s,f_c);affFDCourse(q,NULL);q=NULL;}
                    }
                }
            }
            else printf("\n!! Choix de la partie 3 non valide !!\n");break;
        case 5:
            if(strcmp(part1,"id" )==0){q=*c_id;
                while(q!=NULL){
                    if(valueC(q).course_id<c.course_id){
                          p=FGCourse(q);
                          deltree_c_id(&p,c_name,c_instr,f_s,f_c);p=FDCourse(q);
                        if(prec==NULL)*c_id=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                    del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueC(q).course_id>c.course_id){prec=q;q=FGCourse(q);}
                    else{p=FGCourse(q);deltree_c_id(&p,c_name,c_instr,f_s,f_c);p=FDCourse(q);
                        if(prec==NULL)*c_id=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                        del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                        del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                        free(q);q=NULL;}}
                }
            }
            else if(strcmp(part1,"name")==0){q=*c_name;
                while(q!=NULL){
                    if(strcmp(valueC(q).course_name,c.course_name)<0){
                          p=FGCourse(q);
                          deltree_c_name(c_id,&p,c_instr,f_s,f_c);p=FDCourse(q);
                        if(prec==NULL)*c_name=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                    del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueC(q).course_name,c.course_name)>0){prec=q;q=FGCourse(q);}
                    else{p=FGCourse(q);deltree_c_name(c_id,&p,c_instr,f_s,f_c);p=FDCourse(q);
                        if(prec==NULL)*c_name=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                        del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                        del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                        free(q);q=NULL;}}
                }
            }
            else if(strcmp(part1,"instructor")==0){q=*c_instr;
                while(q!=NULL){
                    if(strcmp(valueC(q).instructor,c.instructor)<0){
                          p=FGCourse(q);
                          deltree_c_instr(c_id,c_name,&p,f_s,f_c);p=FDCourse(q);
                        if(prec==NULL)*c_instr=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                    del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueC(q).instructor,c.instructor)>0){prec=q;q=FGCourse(q);}
                    else{p=FGCourse(q);deltree_c_instr(c_id,c_name,&p,f_s,f_c);p=FDCourse(q);
                        if(prec==NULL)*c_instr=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                        del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                        del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                        free(q);q=NULL;}}
                }
            }
            else printf("\n!! Choix de la partie 3 non valide !!\n");break;
        case 6:
            if(strcmp(part1,"id")==0){q=*c_id;
                while(q!=NULL){
                    if(valueC(q).course_id>c.course_id){
                          p=FDCourse(q);
                          deltree_c_id(&p,c_name,c_instr,f_s,f_c);p=FGCourse(q);
                        if(prec==NULL)*c_id=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                    del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueC(q).course_id<c.course_id){prec=q;q=FDCourse(q);}
                    else{p=FDCourse(q);deltree_c_id(&p,c_name,c_instr,f_s,f_c);p=FGCourse(q);
                        if(prec==NULL)*c_id=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                        del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                        del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                        free(q);q=p;}}
                }
            }
            else if(strcmp(part1,"name")==0){q=*c_name;
                while(q!=NULL){
                    if(strcmp(valueC(q).course_name,c.course_name)>0){
                          p=FDCourse(q);
                          deltree_c_name(c_id,&p,c_instr,f_s,f_c);p=FGCourse(q);
                        if(prec==NULL)*c_name=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                    del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueC(q).course_name,c.course_name)<0){prec=q;q=FDCourse(q);}
                    else{p=FDCourse(q);deltree_c_name(c_id,&p,c_instr,f_s,f_c);p=FGCourse(q);
                        if(prec==NULL)*c_name=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                        del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                        del_c_instr(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                        free(q);q=p;}}
                }
            }
            else if(strcmp(part1,"instructor")==0){q=*c_instr;
                while(q!=NULL){
                    if(strcmp(valueC(q).instructor,c.instructor)>0){
                          p=FDCourse(q);
                          deltree_c_instr(c_id,c_name,&p,f_s,f_c);p=FGCourse(q);
                        if(prec==NULL)*c_instr=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                    del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueC(q).instructor,c.instructor)<0){prec=q;q=FDCourse(q);}
                    else{p=FDCourse(q);deltree_c_instr(c_id,c_name,&p,f_s,f_c);p=FGCourse(q);
                        if(prec==NULL)*c_instr=p;
                        else if (FGCourse(prec)==q)affFGCourse(prec,p);
                             else affFDCourse(prec,p);
                        del_c_id(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                        del_c_name(valueC(q),1,c_id,c_name,c_instr,f_s,f_c);
                    followCourse f;f.course_id=valueC(q).course_id;del_f_c(f,0,f_s,f_c);
                        free(q);q=p;}}
                }
            }
            else printf("\n!! Choix de la partie 3 non valide !!\n");break;}

}
