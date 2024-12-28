#include "student.h"
#include "followCourse.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void initArbreStudent(arbreStudent *a) {
    *a = NULL;
}

void allocateNodeStudent(arbreStudent *a){
    *a = (arbreStudent)malloc(sizeof(maillonStudent));
}

arbreStudent FGStudent(arbreStudent a) {
    return a->FG;
}
arbreStudent FDStudent(arbreStudent a) {
    return a->FD;
}

void affFGStudent(arbreStudent a,arbreStudent b) {
    a->FG = b;
}
void affFDStudent(arbreStudent a,arbreStudent b) {
    a->FD = b;
}

/**/void valueStudent(arbreStudent a,student *valeur){
    valeur->student_id = a->value.student_id;
    strcpy(valeur->name,a->value.name);
    valeur->age = a->value.age;
    strcpy(valeur->major,a->value.major);
}
student valueS(arbreStudent a){
    return a->value;
}

void scanStudent(student *s){
    printf("Id= ");
    scanf("%d",&s->student_id);
    printf("Nom= ");
    fflush(stdin);
    gets(s->name);
    printf("Age= ");
    scanf("%d",&s->age);
    printf("Major= ");
    fflush(stdin);
    gets(s->major);
}
/**/void affValueStudent(arbreStudent a, student valeur) {
    a->value.student_id = valeur.student_id;
    strcpy(a->value.name , valeur.name);
    a->value.age = valeur.age;
    strcpy(a->value.major , valeur.major);
}


/**/arbreStudent insertNodeStudentId(arbreStudent a, student value){
   if (a == NULL) {
        arbreStudent p;
        allocateNodeStudent(&p);
        affValueStudent(p,value);
        affFDStudent(p, NULL);
        affFGStudent(p, NULL);
        a = p;
    }else{
        if ( a->value.student_id >= value.student_id) {
            affFGStudent(a,insertNodeStudentId(FGStudent(a), value));
        } else {
            affFDStudent(a,insertNodeStudentId(FDStudent(a), value));
        }
    }
    return a;
}
arbreStudent insertNodeName(arbreStudent a, student value) {
    if (a == NULL) {
        arbreStudent p;

        allocateNodeStudent(&p);
        affValueStudent(p,value);
        affFDStudent(p, NULL);
        affFGStudent(p, NULL);
        a = p;
    }else{
        if ( strcmp(a->value.name , value.name) >= 0) {
            affFGStudent(a,insertNodeName(FGStudent(a), value));
        } else {
            affFDStudent(a,insertNodeName(FDStudent(a), value));
        }
    }
    return a;
}
arbreStudent insertNodeAge(arbreStudent a, student value) {
    if (a == NULL) {
        arbreStudent p;

        allocateNodeStudent(&p);
        affValueStudent(p,value);
        affFDStudent(p, NULL);
        affFGStudent(p, NULL);
        a = p;
    }else{
        if (a->value.age >= value.age) {//still have bad feelings about that '>='
            affFGStudent(a,insertNodeAge(FGStudent(a), value));
        } else{
            affFDStudent(a,insertNodeAge(FDStudent(a), value));
        }
    }
    return a;
}
arbreStudent insertNodeMajor(arbreStudent a, student value) {
    if (a == NULL) {
        arbreStudent p;

        allocateNodeStudent(&p);
        affValueStudent(p, value);
        affFDStudent(p, NULL);
        affFGStudent(p, NULL);
        a = p;
    }else{
        if (strcmp(a->value.major, value.major) >= 0) {//still have bad feelings about that '>='
            affFGStudent(a,insertNodeMajor(FGStudent(a), value));
        } else{
            affFDStudent(a,insertNodeMajor(FDStudent(a), value));
        }
    }
    return a;
}


arbreStudent parse_students_csv_student_Id(char *inputFileName){
    FILE *f = fopen(inputFileName,"r");

    if (f == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    student temp;
    arbreStudent idArbre;

    initArbreStudent(&idArbre);
    while(fscanf(f,"%d,%30[^,],%d,%40[^\n]%*c",&temp.student_id,temp.name,&temp.age,temp.major) == 4){
        idArbre=insertNodeStudentId(idArbre,temp);
    }
    fclose(f);
    return idArbre;
}
arbreStudent parse_students_csv_name(char *inputFileName){
    FILE *f = fopen(inputFileName,"r");

    if (f == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    student temp;
    arbreStudent nameArbre;

    initArbreStudent(&nameArbre);
    /* print_tree_student(idArbre);
        printf("**********\n");*/

    while(fscanf(f,"%d,%30[^,],%d,%40[^\n]%*c",&temp.student_id,temp.name,&temp.age,temp.major) == 4){
        nameArbre=insertNodeName(nameArbre,temp);
    }
    fclose(f);
    return nameArbre;
}
arbreStudent parse_students_csv_age(char *inputFileName){
    FILE *f = fopen(inputFileName,"r");

    if (f == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    student temp;
    arbreStudent ageArbre;

    initArbreStudent(&ageArbre);
    while(fscanf(f, "%d,%30[^,],%d,%40[^\n]%*c", &temp.student_id, temp.name, &temp.age , temp.major) == 4){
        ageArbre=insertNodeAge(ageArbre,temp);
    }
    fclose(f);
    return ageArbre;
}
arbreStudent parse_students_csv_major(char *inputFileName){
    FILE *f = fopen(inputFileName,"r");

    if (f == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    student temp;
    arbreStudent majorArbre;

    initArbreStudent(&majorArbre);
    while(fscanf(f, "%d,%30[^,],%d,%40[^\n]%*c", &temp.student_id, temp.name, &temp.age , temp.major) == 4){
        majorArbre=insertNodeMajor(majorArbre,temp);
    }
    fclose(f);
    return majorArbre;
}


void parcoureArbre(arbreStudent Arbre,FILE *f){
    student temp;

    if(Arbre!=NULL){
        if(FGStudent(Arbre)!=NULL){
            parcoureArbre(FGStudent(Arbre),f);
        }
        valueStudent(Arbre,&temp);
        fprintf(f, "%d,%s,%d,%s\n", temp.student_id, temp.name, temp.age, temp.major);
        if(FDStudent(Arbre)!=NULL){
            parcoureArbre(FDStudent(Arbre),f);
        }
    }
}
bool serialize_students_csv_student_Id(char *inputFileName, arbreStudent Arbre,char *modeDAccee){
    FILE *f = fopen(inputFileName,modeDAccee);

    if (f == NULL) {
        printf("Error opening file\n");
        return false;
    }
    parcoureArbre(Arbre,f);
    fclose(f);
    return true;
}
bool serialize_students_csv_age(char *inputFileName, arbreStudent Arbre, char *modeDAccee){
    FILE *f = fopen(inputFileName,modeDAccee);

    if (f == NULL) {
        printf("Error opening file\n");
        return false;
    }
    parcoureArbre(Arbre,f);
    fclose(f);
    return true;
}
bool serialize_students_csv_name(char *inputFileName, arbreStudent Arbre, char *modeDAccee){
    FILE *f = fopen(inputFileName,modeDAccee);

    if (f == NULL) {
        printf("Error opening file\n");
        return false;
    }
    parcoureArbre(Arbre,f);
    fclose(f);
    return true;
}
bool serialize_students_csv_major(char *inputFileName, arbreStudent Arbre, char *modeDAccee){
    FILE *f = fopen(inputFileName,modeDAccee);

    if (f == NULL) {
        printf("Error opening file\n");
        return false;
    }
    parcoureArbre(Arbre,f);
    fclose(f);
    return true;
}


void rech_stud_node_id(arbreStudent a,int x){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(value.student_id==x){
                    printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_id(FGStudent(a),x);
    }
    else{
        if(value.student_id>x) rech_stud_node_id(FGStudent(a),x);
        else rech_stud_node_id(FDStudent(a),x);
        }
}}
void rech_stud_node_age(arbreStudent a,int x){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(value.age==x){
                  printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
      rech_stud_node_age(FGStudent(a),x);
    }
    else{
        if(value.age>x) rech_stud_node_age(FGStudent(a),x);
        else rech_stud_node_age(FDStudent(a),x);
        }
}}
void rech_stud_node_major(arbreStudent a,char x[]){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(strcmp(value.major,x)==0){
                 printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
     rech_stud_node_major(FGStudent(a),x);
    }
   else{
        if(strcmp(value.major,x)>0) rech_stud_node_major(FGStudent(a),x);
        else rech_stud_node_major(FDStudent(a),x);
        }
}}
void rech_stud_node_name(arbreStudent a,char x[]){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(strcmp(value.name,x)==0){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_name(FGStudent(a),x);
    }
    else{
        if(strcmp(value.name,x)>0) rech_stud_node_name(FGStudent(a),x);
        else rech_stud_node_name(FDStudent(a),x);
        }
}}
void rech_stud_node_Not_name(arbreStudent a,char x[]){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(strcmp(value.name,x)!=0){printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);}
    rech_stud_node_Not_name(FGStudent(a),x);
    rech_stud_node_Not_name(FDStudent(a),x);
}}
void rech_stud_node_Not_major(arbreStudent a,char x[]){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(strcmp(value.major,x)!=0){printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);}
    rech_stud_node_Not_major(FGStudent(a),x);
    rech_stud_node_Not_major(FDStudent(a),x);
}}
void rech_stud_node_Not_id(arbreStudent a,int x){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(value.student_id!=x){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
    }
    rech_stud_node_Not_id(FGStudent(a),x);
    rech_stud_node_Not_id(FDStudent(a),x);
}}
void rech_stud_node_Not_age(arbreStudent a,int x){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(value.age!=x){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
    }
    rech_stud_node_Not_age(FGStudent(a),x);
    rech_stud_node_Not_age(FDStudent(a),x);
}}
void rech_stud_node_sup_id(arbreStudent a,int x){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(value.student_id>x){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_sup_id(FGStudent(a),x);
        rech_stud_node_sup_id(FDStudent(a),x);
    }
    else{rech_stud_node_sup_id(FDStudent(a),x);}
}}
void rech_stud_node_sup_age(arbreStudent a,int x){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(value.age>x){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_sup_age(FGStudent(a),x);
        rech_stud_node_sup_age(FDStudent(a),x);
    }
    else{rech_stud_node_sup_age(FDStudent(a),x);}
}}
void rech_stud_node_sup_major(arbreStudent a,char x[]){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(strcmp(value.major,x)> 0){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_sup_major(FGStudent(a),x);
        rech_stud_node_sup_major(FDStudent(a),x);
    }
    else{rech_stud_node_sup_major(FDStudent(a),x);}
}}
void rech_stud_node_sup_name(arbreStudent a,char x[]){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(strcmp(value.name,x)> 0){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_sup_name(FGStudent(a),x);
        rech_stud_node_sup_name(FDStudent(a),x);
    }
    else{rech_stud_node_sup_name(FDStudent(a),x);}
}}
void rech_stud_node_sup_eg_id(arbreStudent a,int x){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(value.student_id>=x){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_sup_eg_id(FGStudent(a),x);
        rech_stud_node_sup_eg_id(FDStudent(a),x);
    }
    else{rech_stud_node_sup_eg_id(FDStudent(a),x);}
}}
void rech_stud_node_sup_eg_age(arbreStudent a,int x){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(value.age>=x){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_sup_eg_age(FGStudent(a),x);
        rech_stud_node_sup_eg_age(FDStudent(a),x);
    }
    else{rech_stud_node_sup_eg_age(FDStudent(a),x);}
}}
void rech_stud_node_sup_eg_major(arbreStudent a,char x[]){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(strcmp(value.major,x)>= 0){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_sup_eg_major(FGStudent(a),x);
        rech_stud_node_sup_eg_major(FDStudent(a),x);
    }
    else{rech_stud_node_sup_eg_major(FDStudent(a),x);}
}}
void rech_stud_node_sup_eg_name(arbreStudent a,char x[]){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(strcmp(value.name,x)>= 0){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_sup_eg_name(FGStudent(a),x);
        rech_stud_node_sup_eg_name(FDStudent(a),x);
    }
    else{rech_stud_node_sup_eg_name(FDStudent(a),x);}
}}
void rech_stud_node_inf_id(arbreStudent a,int x){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(value.student_id<x){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_inf_id(FGStudent(a),x);
        rech_stud_node_inf_id(FDStudent(a),x);
    }
    else{rech_stud_node_inf_id(FGStudent(a),x);}
}}
void rech_stud_node_inf_age(arbreStudent a,int x){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(value.age<x){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_inf_age(FGStudent(a),x);
        rech_stud_node_inf_age(FDStudent(a),x);
    }
    else{rech_stud_node_inf_age(FGStudent(a),x);}
}}
void rech_stud_node_inf_major(arbreStudent a,char x[]){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(strcmp(value.major,x) < 0){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_inf_major(FGStudent(a),x);
        rech_stud_node_inf_major(FDStudent(a),x);
    }
    else{rech_stud_node_inf_major(FGStudent(a),x);}
}}
void rech_stud_node_inf_name(arbreStudent a,char x[]){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(strcmp(value.name,x) < 0){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_inf_name(FGStudent(a),x);
        rech_stud_node_inf_name(FDStudent(a),x);
    }
    else{rech_stud_node_inf_name(FGStudent(a),x);}
}}
void rech_stud_node_inf_eg_id(arbreStudent a,int x){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(value.student_id<=x){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_inf_eg_id(FGStudent(a),x);
        rech_stud_node_inf_eg_id(FDStudent(a),x);
    }
    else{rech_stud_node_inf_eg_id(FGStudent(a),x);}
}}
void rech_stud_node_inf_eg_age(arbreStudent a,int x){
    student value;
    if(a!=NULL){
    valueStudent(a,&value);

    if(value.age<=x){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_inf_eg_age(FGStudent(a),x);
        rech_stud_node_inf_eg_age(FDStudent(a),x);
    }
    else{rech_stud_node_inf_eg_age(FGStudent(a),x);}
}}
void rech_stud_node_inf_eg_major(arbreStudent a,char x[]){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(strcmp(value.major,x) <= 0){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_inf_eg_major(FGStudent(a),x);
        rech_stud_node_inf_eg_major(FDStudent(a),x);
    }
    else{rech_stud_node_inf_eg_major(FGStudent(a),x);}
}}
void rech_stud_node_inf_eg_name(arbreStudent a,char x[]){
    if(a!=NULL){
    student value;
    valueStudent(a,&value);

    if(strcmp(value.name,x) <= 0){
        printf("| %-10d | %-30s | %-10d | %-20s |\n", value.student_id, value.name, value.age, value.major);
        rech_stud_node_inf_eg_name(FGStudent(a),x);
        rech_stud_node_inf_eg_name(FDStudent(a),x);
    }
    else{rech_stud_node_inf_eg_name(FGStudent(a),x);}
}}

void countStudentId(arbreStudent a,int *counter){
    while(a!=NULL && FDStudent(a)!=NULL){
        a = FDStudent(a);
    }

    valueStudent(a,counter);
}

void insertStudent(const char *input ,arbreStudent arbres[],int *studentIdCount) {
    student s;
    *studentIdCount += 1;
    s.student_id = *studentIdCount;
    // Get the inputs from the command
    int result = sscanf(input, "insert student \"%31[^\"]\" %d \"%41[^\"]\"", s.name, &s.age, s.major);
    // Check if it was successfully scanned
    if (result == 3) {
        int length = strlen(s.name);
        if(length <= 2){
            printf("Invalid input format.\n");
            return;
        }
        if(s.name[0] == '\"' && s.name[length - 1] == '\"'){
            memmove(s.name, s.name + 1, length - 2);
            s.name[length - 2] = '\0';
        }
        length = strlen(s.major);
        if(length<=2){
            printf("Invalid input format.\n");
            return;
        }
        // Remove quotes from string
        if(s.major[0] == '\"' && s.major[length - 1] == '\"'){
            memmove(s.major, s.major + 1, length - 2);
            s.major[length - 2] = '\0';
        }

        printf("successfully inserted : %d %s %d %s .\n",*studentIdCount,s.name,s.age,s.major);

        for (int i = 0; i < 4; i++) {
            // Insert the student into the tree
            switch (i) {
                case 0:
                    insertNodeStudentId(arbres[i], s);
                    break;
                case 1:
                    insertNodeName(arbres[i], s);
                    break;
                case 2:
                    insertNodeAge(arbres[i], s);
                    break;
                case 3:
                    insertNodeMajor(arbres[i], s);
                    break;
            }
        }

    } else {
        printf("Invalid input format\n");
    }
    }

void print_student_table_header() {
    printf(" ____________ ________________________________ ____________ ______________________\n");
    printf("| %-10s | %-30s | %-10s | %-20s |\n", "ID", "Nom", "Age", "Major");
    printf("|------------|--------------------------------|------------|----------------------|\n");
}

void print_tree_student(arbreStudent Arbre) {
    student s;

    if (Arbre != NULL) {
        if (FGStudent(Arbre) != NULL) {
            print_tree_student(FGStudent(Arbre));
        }
        valueStudent(Arbre, &s);
        printf("| %-10d | %-30s | %-10d | %-20s |\n", s.student_id, s.name, s.age, s.major);

        if (FDStudent(Arbre) != NULL) {
            print_tree_student(FDStudent(Arbre));
        }
    }
}

void closeStudent(arbreStudent a){
    if (a == NULL) {
        return;
    }
    closeStudent(FGStudent(a));
    closeStudent(FDStudent(a));
    free(a);
}

// supprimer tout les elements de l'arbre originalle , et ces derniers dans les autres arbre
void deltree_s_id(arbreStudent *s_id,arbreStudent *s_age,arbreStudent *s_name,arbreStudent *s_major,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    if(*s_id!=NULL){arbreStudent d=FDStudent(*s_id),g=FGStudent(*s_id);

    deltree_s_id(&d,s_age,s_name,s_major,f_s,f_c) ;
    deltree_s_id(&g,s_age,s_name,s_major,f_s,f_c);
    del_s_age(valueS(*s_id),1,s_id,s_age,s_name,s_major,f_s,f_c);
    del_s_name(valueS(*s_id),1,s_id,s_age,s_name,s_major,f_s,f_c);
    del_s_major(valueS(*s_id),1,s_id,s_age,s_name,s_major,f_s,f_c);
    followCourse f;f.student_id=valueS(*s_id).student_id;del_f_s(f,0,f_s,f_c);
    free(*s_id);}
}
void deltree_s_age(arbreStudent *s_id,arbreStudent *s_age,arbreStudent *s_name,arbreStudent *s_major,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    if(*s_age!=NULL){arbreStudent d=FDStudent(*s_age),g=FGStudent(*s_age);deltree_s_age(s_id,&d,s_name,s_major,f_s,f_c) ; deltree_s_age(s_id,&g,s_name,s_major,f_s,f_c);
    del_s_id(valueS(*s_age),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_name(valueS(*s_age),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_major(valueS(*s_age),1,s_id,s_age,s_name,s_major,f_s,f_c);
    followCourse f;f.student_id=valueS(*s_age).student_id;del_f_s(f,0,f_s,f_c);free(*s_age);}
}
void deltree_s_name(arbreStudent *s_id,arbreStudent *s_age,arbreStudent *s_name,arbreStudent *s_major,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    if(*s_name!=NULL){arbreStudent d=FDStudent(*s_name),g=FGStudent(*s_name);deltree_s_name(s_id,s_age,&d,s_major,f_s,f_c) ; deltree_s_name(s_id,s_age,&g,s_major,f_s,f_c);
    del_s_id(valueS(*s_name),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_age(valueS(*s_name),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_major(valueS(*s_name),1,s_id,s_age,s_name,s_major,f_s,f_c);
    followCourse f;f.student_id=valueS(*s_name).student_id;del_f_s(f,0,f_s,f_c);free(*s_name);}
}
void deltree_s_major(arbreStudent *s_id,arbreStudent *s_age,arbreStudent *s_name,arbreStudent *s_major,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    if(*s_major!=NULL){arbreStudent d=FDStudent(*s_major),g=FGStudent(*s_major);deltree_s_major(s_id,s_age,s_name,&d,f_s,f_c) ; deltree_s_major(s_id,s_age,s_name,&g,f_s,f_c);
    del_s_id(valueS(*s_major),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_age(valueS(*s_major),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_name(valueS(*s_major),1,s_id,s_age,s_name,s_major,f_s,f_c);
    followCourse f;f.student_id=valueS(*s_major).student_id;del_f_s(f,0,f_s,f_c);free(*s_major);}
}

// supprimer selon "..= s" , b!=0 selon "=id" de s aussi ,b=0 supprimer dans les autres arbres ce qui a supprimer dont l'arbre originalle
void del_s_id(student s,int b,arbreStudent *s_id,arbreStudent *s_age,arbreStudent *s_name,arbreStudent *s_major,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    arbreStudent q=*s_id,prec=NULL,p;
    while(q!=NULL){
    if(valueS(q).student_id==s.student_id){
        if(FGStudent(q)==NULL){
        if(prec==NULL)*s_id=FDStudent(q);else{
            if(q==FDStudent(prec))affFDStudent(prec,FDStudent(q));else affFGStudent(prec,FDStudent(q));
        }
        if(b==0){followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);}
        free(q);q=NULL;
        }else{
            if((FGStudent(q)!=NULL)&&((FDStudent(q)==NULL))){
                if(prec==NULL)*s_id=FGStudent(q);else{
                if(q==FDStudent(prec))affFDStudent(prec,FGStudent(q));else affFGStudent(prec,FGStudent(q));}
                p=FGStudent(q);
                if(b==0){followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);}
                free(q);q=p;
            }else{
                p=FDStudent(q);
                while(FGStudent(p)!=NULL)p=FGStudent(p);
                if(prec==NULL)*s_id=FDStudent(q);else{
                if(q==FDStudent(prec))affFDStudent(prec,FDStudent(q));else affFGStudent(prec,FDStudent(q));}
                affFGStudent(p,FGStudent(q));
                if(b==0){followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                        del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);}
                free(q);q=FGStudent(p);prec=p;
            }
        }
    }else{prec=q;if(valueS(q).student_id<s.student_id)q=FDStudent(q);else q=FGStudent(q);}
    }
}
void del_s_age(student s,int b,arbreStudent *s_id,arbreStudent *s_age,arbreStudent *s_name,arbreStudent *s_major,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    arbreStudent q=*s_age,prec=NULL,p;
    while(q!=NULL){
    if((valueS(q).age==s.age)&&((valueS(q).student_id==s.student_id)||(b==0))){
        if(FGStudent(q)==NULL){
        if(prec==NULL)*s_age=FDStudent(q);else{
            if(q==FDStudent(prec))affFDStudent(prec,FDStudent(q));else affFGStudent(prec,FDStudent(q));
        }
        if(b==0){followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);}
        free(q);q=NULL;
        }else{
            if((FGStudent(q)!=NULL)&&((FDStudent(q)==NULL))){
                if(prec==NULL)*s_age=FGStudent(q);else{
                if(q==FDStudent(prec))affFDStudent(prec,FGStudent(q));else affFGStudent(prec,FGStudent(q));}
                p=FGStudent(q);
                if(b==0){followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);}
                free(q);q=p;
            }else{
                p=FDStudent(q);
                while(FGStudent(p)!=NULL)p=FGStudent(p);
                if(prec==NULL)*s_age=FDStudent(q);else{
                if(q==FDStudent(prec))affFDStudent(prec,FDStudent(q));else affFGStudent(prec,FDStudent(q));}
                affFGStudent(p,FGStudent(q));
                if(b==0){followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);}
                free(q);q=FGStudent(p);prec=p;
            }
        }
    }else{prec=q;if(valueS(q).age<s.age)q=FDStudent(q);else q=FGStudent(q);}
    }
}
void del_s_name(student s,int b,arbreStudent *s_id,arbreStudent *s_age,arbreStudent *s_name,arbreStudent *s_major,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    arbreStudent q=*s_name,prec=NULL,p;
    while(q!=NULL){
    if((strcmp(valueS(q).name,s.name)==0)&&((valueS(q).student_id==s.student_id)||(b==0))){
        if(FGStudent(q)==NULL){
        if(prec==NULL)*s_name=FDStudent(q);else{
            if(q==FDStudent(prec))affFDStudent(prec,FDStudent(q));else affFGStudent(prec,FDStudent(q));
        }
        if(b==0){followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
        del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
        del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);}
        free(q);q=NULL;
        }else{
            if((FGStudent(q)!=NULL)&&((FDStudent(q)==NULL))){
                if(prec==NULL)*s_name=FGStudent(q);else{
                if(q==FDStudent(prec))affFDStudent(prec,FGStudent(q));else affFGStudent(prec,FGStudent(q));}
                p=FGStudent(q);
                if(b==0){followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);}
                free(q);q=p;
            }else{
                p=FDStudent(q);
                while(FGStudent(p)!=NULL)p=FGStudent(p);
                if(prec==NULL)*s_name=FDStudent(q);else{
                if(q==FDStudent(prec))affFDStudent(prec,FDStudent(q));else affFGStudent(prec,FDStudent(q));}
                affFGStudent(p,FGStudent(q));
                if(b==0){followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);}
                free(q);q=FGStudent(p);prec=p;
            }
        }
    }else{prec=q;if(strcmp(valueS(q).name,s.name)<0)q=FDStudent(q);else q=FGStudent(q);}
    }
}
void del_s_major(student s,int b,arbreStudent *s_id,arbreStudent *s_age,arbreStudent *s_name,arbreStudent *s_major,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    arbreStudent q=*s_major,prec=NULL,p;
    while(q!=NULL){
    if((strcmp(valueS(q).major,s.major)==0)&&((valueS(q).student_id==s.student_id)||(b==0))){
        if(FGStudent(q)==NULL){
        if(prec==NULL)*s_major=FDStudent(q);else{
            if(q==FDStudent(prec))affFDStudent(prec,FDStudent(q));else affFGStudent(prec,FDStudent(q));
        }
        if(b==0){followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);}
        free(q);q=NULL;
        }else{
            if((FGStudent(q)!=NULL)&&((FDStudent(q)==NULL))){
                if(prec==NULL)*s_major=FGStudent(q);else{
                if(q==FDStudent(prec))affFDStudent(prec,FGStudent(q));else affFGStudent(prec,FGStudent(q));}
                p=FGStudent(q);
                if(b==0){followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);}
                free(q);q=p;
            }else{
                p=FDStudent(q);
                while(FGStudent(p)!=NULL)p=FGStudent(p);
                if(prec==NULL)*s_major=FDStudent(q);else{
                if(q==FDStudent(prec))affFDStudent(prec,FDStudent(q));else affFGStudent(prec,FDStudent(q));}
                affFGStudent(p,FGStudent(q));
                if(b==0){followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);}
                free(q);q=FGStudent(p);prec=p;
            }
        }
    }else{prec=q;if(strcmp(valueS(q).major,s.major)<0)q=FDStudent(q);else q=FGStudent(q);}
    }
}



void del_student(char* part1,char* part2,int b,arbreStudent *s_id,arbreStudent *s_age,arbreStudent *s_name,arbreStudent *s_major,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    student s;arbreStudent q,prec=NULL,p;
    s.age=atoi(part2);
    s.student_id=atoi(part2);
    strcpy(s.name,part2);
    strcpy(s.major,part2);
    switch(b){
        case 0:printf("\n!!!operation non valide!!!\n");break;
        case 1:
            if (strcmp(part1,"id")==0)del_s_id(s,0,s_id,s_age,s_name,s_major,f_s,f_c);
            else if(strcmp(part1,"age" )==0)del_s_age(s,0,s_id,s_age,s_name,s_major,f_s,f_c);
            else if(strcmp(part1,"name")==0)del_s_name(s,0,s_id,s_age,s_name,s_major,f_s,f_c);
            else if(strcmp(part1,"major")==0)del_s_major(s,0,s_id,s_age,s_name,s_major,f_s,f_c);
            else printf("\nChoix de la partie 3 non valide!\n");break;
        case 2:
            if (strcmp(part1,"id")==0){q=*s_id;
            while(q!=NULL){
                if(valueS(q).student_id==s.student_id){
                        p=FDStudent(q);
                    deltree_s_id(&p,s_age,s_name,s_major,f_s,f_c);
                        affFDStudent(q,NULL);prec=q;q=FGStudent(q);
                }else{
                     if(valueS(q).student_id>s.student_id){p=FDStudent(q);deltree_s_id(&p,s_age,s_name,s_major,f_s,f_c);affFDStudent(q,NULL);p=FGStudent(q);}
                     else{p=FGStudent(q);deltree_s_id(&p,s_age,s_name,s_major,f_s,f_c);p=FDStudent(q);affFGStudent(q,NULL);}
                     if(prec==NULL)*s_id=p;else if(q==FDStudent(prec))affFDStudent(prec,p);else affFGStudent(prec,p);
                     followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                     del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                     del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                     del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                     free(q);q=p;
                }
            }
            }
            else if(strcmp(part1,"age" )==0){q=*s_age;
            while(q!=NULL){
                if(valueS(q).age==s.age){
                        p=FDStudent(q);
                    deltree_s_age(s_id,&p,s_name,s_major,f_s,f_c);
                        affFDStudent(q,NULL);prec=q;q=FGStudent(q);
                }else{
                     if(valueS(q).age>s.age){p=FDStudent(q);deltree_s_age(s_id,&p,s_name,s_major,f_s,f_c);affFDStudent(q,NULL);p=FGStudent(q);}
                     else{p=FGStudent(q);deltree_s_age(s_id,&p,s_name,s_major,f_s,f_c);p=FDStudent(q);affFGStudent(q,NULL);}
                     if(prec==NULL)*s_age=p;else if(q==FDStudent(prec))affFDStudent(prec,p);else affFGStudent(prec,p);
                     del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                     del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                     del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                     followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                     free(q);q=p;
                }
              }
            }
            else if(strcmp(part1,"name")==0){q=*s_name;
            while(q!=NULL){
                if(strcmp(valueS(q).name,s.name)==0){
                        p=FDStudent(q);
                    deltree_s_name(s_id,s_age,&p,s_major,f_s,f_c);
                        affFDStudent(q,NULL);prec=q;q=FGStudent(q);
                }else{
                     if(strcmp(valueS(q).name,s.name)>0){p=FDStudent(q);deltree_s_name(s_id,s_age,&p,s_major,f_s,f_c);affFDStudent(q,NULL);p=FGStudent(q);}
                     else{p=FGStudent(q);deltree_s_name(s_id,s_age,&p,s_major,f_s,f_c);p=FDStudent(q);affFGStudent(q,NULL);}
                     if(prec==NULL)*s_name=p;else if(q==FDStudent(prec))affFDStudent(prec,p);else affFGStudent(prec,p);
                     del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                     del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                     del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                     followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                     free(q);q=p;
                }
              }
            }
            else if(strcmp(part1,"major")==0){q=*s_major;
            while(q!=NULL){
                if(strcmp(valueS(q).major,s.major)==0){
                        p=FDStudent(q);
                    deltree_s_major(s_id,s_age,s_name,&p,f_s,f_c);
                        affFDStudent(q,NULL);prec=q;q=FGStudent(q);
                }else{
                     if(strcmp(valueS(q).major,s.major)>0){p=FDStudent(q);deltree_s_major(s_id,s_age,s_name,&p,f_s,f_c);affFDStudent(q,NULL);p=FGStudent(q);}
                     else{p=FGStudent(q);deltree_s_major(s_id,s_age,s_name,&p,f_s,f_c);p=FDStudent(q);affFGStudent(q,NULL);}
                     if(prec==NULL)*s_major=p;else if(q==FDStudent(prec))affFDStudent(prec,p);else affFGStudent(prec,p);
                     del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                     del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                     del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                     followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                     free(q);q=p;
                }
              }
            }
            else printf("\nChoix de la partie 3 non valide!\n");break;
        case 3:
            if (strcmp(part1,"id")==0){q=*s_id;
                while(q!=NULL ){
                    if(valueS(q).student_id<s.student_id){
                          p=FGStudent(q);
                          deltree_s_id(&p,s_age,s_name,s_major,f_s,f_c);p=FDStudent(q);
                        if(prec==NULL)*s_id=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueS(q).student_id>s.student_id){prec=q;q=FGStudent(q);}
                    else{if(FGStudent(q)!=NULL){
                            if(valueS(FGStudent(q)).student_id==s.student_id){prec=q;q=FGStudent(q);}
                            else {p=FGStudent(q);deltree_s_id(&p,s_age,s_name,s_major,f_s,f_c);
                            affFGStudent(q,NULL);q=NULL;}
                    }else q=NULL;}}
                }
            }
            else if(strcmp(part1,"age" )==0){q=*s_age;
                while(q!=NULL ){
                    if(valueS(q).age<s.age){
                          p=FGStudent(q);
                          deltree_s_age(s_id,&p,s_name,s_major,f_s,f_c);p=FDStudent(q);
                        if(prec==NULL)*s_age=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueS(q).age>s.age){prec=q;q=FGStudent(q);}
                    else{if(FGStudent(q)!=NULL){
                            if(valueS(FGStudent(q)).age==s.age){prec=q;q=FGStudent(q);}
                            else {p=FGStudent(q);deltree_s_age(s_id,&p,s_name,s_major,f_s,f_c);
                            affFGStudent(q,NULL);q=NULL;}
                    }else q=NULL;}}
                }
            }
            else if(strcmp(part1,"name")==0){q=*s_name;
                while(q!=NULL ){
                    if(strcmp(valueS(q).name,s.name)<0){
                          p=FGStudent(q);
                          deltree_s_name(s_id,s_age,&p,s_major,f_s,f_c);p=FDStudent(q);
                        if(prec==NULL)*s_name=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueS(q).name,s.name)>0){prec=q;q=FGStudent(q);}
                    else{if(FGStudent(q)!=NULL){
                            if(strcmp(valueS(FGStudent(q)).name,s.name)>0){prec=q;q=FGStudent(q);}
                            else {p=FGStudent(q);deltree_s_name(s_id,s_age,&p,s_major,f_s,f_c);
                            affFGStudent(q,NULL);q=NULL;}
                    }else q=NULL;}}
                }
            }
            else if(strcmp(part1,"major")==0){q=*s_major;
                while(q!=NULL ){
                    if(strcmp(valueS(q).major,s.major)<0){
                          p=FGStudent(q);
                          deltree_s_major(s_id,s_age,s_name,&p,f_s,f_c);p=FDStudent(q);
                        if(prec==NULL)*s_major=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueS(q).major,s.major)>0){prec=q;q=FGStudent(q);}
                    else{if(FGStudent(q)!=NULL){
                            if(strcmp(valueS(FGStudent(q)).major,s.major)>0){prec=q;q=FGStudent(q);}
                            else {p=FGStudent(q);deltree_s_major(s_id,s_age,s_name,&p,f_s,f_c);
                            affFGStudent(q,NULL);q=NULL;}
                    }else q=NULL;}}
                }
            }
            else printf("\nChoix de la partie 3 non valide!\n");break;
        case 4:
            if (strcmp(part1,"id")==0){q=*s_id;
                while(q!=NULL ){
                    if(valueS(q).student_id>s.student_id){
                          p=FDStudent(q);
                          deltree_s_id(&p,s_age,s_name,s_major,f_s,f_c);p=FGStudent(q);
                        if(prec==NULL)*s_id=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueS(q).student_id<s.student_id){prec=q;q=FDStudent(q);}
                    else{p=FDStudent(q);deltree_s_id(&p,s_age,s_name,s_major,f_s,f_c);affFDStudent(q,NULL);q=NULL;}
                    }
                }
            }
            else if(strcmp(part1,"age" )==0){q=*s_age;
                while(q!=NULL ){
                    if(valueS(q).age>s.age){
                          p=FDStudent(q);
                          deltree_s_age(s_id,&p,s_name,s_major,f_s,f_c);p=FGStudent(q);
                        if(prec==NULL)*s_age=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueS(q).age<s.age){prec=q;q=FDStudent(q);}
                    else{p=FDStudent(q);deltree_s_age(s_id,&p,s_name,s_major,f_s,f_c);affFDStudent(q,NULL);q=NULL;}
                    }
                }
            }
            else if(strcmp(part1,"name")==0){q=*s_name;
                while(q!=NULL ){
                    if(strcmp(valueS(q).name,s.name)>0){
                          p=FDStudent(q);
                          deltree_s_name(s_id,s_age,&p,s_major,f_s,f_c);p=FGStudent(q);
                        if(prec==NULL)*s_name=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueS(q).name,s.name)<0){prec=q;q=FDStudent(q);}
                    else{p=FDStudent(q);deltree_s_name(s_id,s_age,&p,s_major,f_s,f_c);affFDStudent(q,NULL);q=NULL;}
                    }
                }
            }
            else if(strcmp(part1,"major")==0){q=*s_major;
                while(q!=NULL ){
                    if(strcmp(valueS(q).major,s.major)>0){
                          p=FDStudent(q);
                          deltree_s_major(s_id,s_age,s_name,&p,f_s,f_c);p=FGStudent(q);
                        if(prec==NULL)*s_major=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueS(q).major,s.major)<0){prec=q;q=FDStudent(q);}
                    else{p=FDStudent(q);deltree_s_major(s_id,s_age,s_name,&p,f_s,f_c);affFDStudent(q,NULL);q=NULL;}
                    }
                }
            }
            else printf("\n!! Choix de la partie 3 non valide !!\n");break;
        case 5:
            if (strcmp(part1,"id")==0){q=*s_id;
                while(q!=NULL){
                    if(valueS(q).student_id<s.student_id){
                          p=FGStudent(q);
                          deltree_s_id(&p,s_age,s_name,s_major,f_s,f_c);p=FDStudent(q);
                        if(prec==NULL)*s_id=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueS(q).student_id>s.student_id){prec=q;q=FGStudent(q);}
                    else{p=FGStudent(q);deltree_s_id(&p,s_age,s_name,s_major,f_s,f_c);p=FDStudent(q);
                        if(prec==NULL)*s_id=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                        del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                        free(q);q=NULL;}}
                }
            }
            else if(strcmp(part1,"age" )==0){q=*s_age;
                while(q!=NULL){
                    if(valueS(q).age<s.age){
                          p=FGStudent(q);
                          deltree_s_age(s_id,&p,s_name,s_major,f_s,f_c);p=FDStudent(q);
                        if(prec==NULL)*s_age=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueS(q).age>s.age){prec=q;q=FGStudent(q);}
                    else{p=FGStudent(q);deltree_s_age(s_id,&p,s_name,s_major,f_s,f_c);p=FDStudent(q);
                        if(prec==NULL)*s_age=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                        del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                        free(q);q=NULL;}}
                }
            }
            else if(strcmp(part1,"name")==0){q=*s_name;
                while(q!=NULL){
                    if(strcmp(valueS(q).name,s.name)<0){
                          p=FGStudent(q);
                          deltree_s_name(s_id,s_age,&p,s_major,f_s,f_c);p=FDStudent(q);
                        if(prec==NULL)*s_name=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueS(q).name,s.name)>0){prec=q;q=FGStudent(q);}
                    else{p=FGStudent(q);deltree_s_name(s_id,s_age,&p,s_major,f_s,f_c);p=FDStudent(q);
                        if(prec==NULL)*s_name=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                        del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                        free(q);q=NULL;}}
                }
            }
            else if(strcmp(part1,"major")==0){q=*s_major;
                while(q!=NULL){
                    if(strcmp(valueS(q).major,s.major)<0){
                          p=FGStudent(q);
                          deltree_s_major(s_id,s_age,s_name,&p,f_s,f_c);p=FDStudent(q);
                        if(prec==NULL)*s_major=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueS(q).major,s.major)>0){prec=q;q=FGStudent(q);}
                    else{p=FGStudent(q);deltree_s_major(s_id,s_age,s_name,&p,f_s,f_c);p=FDStudent(q);
                        if(prec==NULL)*s_major=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                        del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                        free(q);q=NULL;}}
                }
            }
            else printf("\n!! Choix de la partie 3 non valide !!\n");break;
        case 6:
            if (strcmp(part1,"id")==0){q=*s_id;
                while(q!=NULL){
                    if(valueS(q).student_id>s.student_id){
                          p=FDStudent(q);
                          deltree_s_id(&p,s_age,s_name,s_major,f_s,f_c);p=FGStudent(q);
                        if(prec==NULL)*s_id=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueS(q).student_id<s.student_id){prec=q;q=FDStudent(q);}
                    else{p=FDStudent(q);deltree_s_id(&p,s_age,s_name,s_major,f_s,f_c);p=FGStudent(q);
                        if(prec==NULL)*s_id=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                        del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                        free(q);q=p;}}
                }
            }
            else if(strcmp(part1,"age")==0){q=*s_age;
                while(q!=NULL){
                    if(valueS(q).age>s.age){
                          p=FDStudent(q);
                          deltree_s_age(s_id,&p,s_name,s_major,f_s,f_c);p=FGStudent(q);
                        if(prec==NULL)*s_age=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueS(q).age<s.age){prec=q;q=FDStudent(q);}
                    else{p=FDStudent(q);deltree_s_age(s_id,&p,s_name,s_major,f_s,f_c);p=FGStudent(q);
                        if(prec==NULL)*s_age=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                        del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                        free(q);q=p;}}
                }
            }
            else if(strcmp(part1,"name")==0){q=*s_name;
                while(q!=NULL){
                    if(strcmp(valueS(q).name,s.name)>0){
                          p=FDStudent(q);
                          deltree_s_name(s_id,s_age,&p,s_major,f_s,f_c);p=FGStudent(q);
                        if(prec==NULL)*s_name=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueS(q).name,s.name)<0){prec=q;q=FDStudent(q);}
                    else{p=FDStudent(q);deltree_s_name(s_id,s_age,&p,s_major,f_s,f_c);p=FGStudent(q);
                        if(prec==NULL)*s_name=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                        del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_major(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                        free(q);q=p;}}
                }
            }
            else if(strcmp(part1,"major")==0){q=*s_major;
                while(q!=NULL){
                    if(strcmp(valueS(q).major,s.major)>0){
                          p=FDStudent(q);
                          deltree_s_major(s_id,s_age,s_name,&p,f_s,f_c);p=FGStudent(q);
                        if(prec==NULL)*s_major=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                    del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                    free(q);q=p;

                    }else{if(strcmp(valueS(q).major,s.major)<0){prec=q;q=FDStudent(q);}
                    else{p=FDStudent(q);deltree_s_major(s_id,s_age,s_name,&p,f_s,f_c);p=FGStudent(q);
                        if(prec==NULL)*s_major=p;
                        else if (FGStudent(prec)==q)affFGStudent(prec,p);
                             else affFDStudent(prec,p);
                        del_s_id(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_age(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                        del_s_name(valueS(q),1,s_id,s_age,s_name,s_major,f_s,f_c);
                    followCourse f;f.student_id=valueS(q).student_id;del_f_s(f,0,f_s,f_c);
                        free(q);q=p;}}
                }
            }
            else printf("\n!! Choix de la partie 3 non valide !!\n");break;}

}
