#include "followCourse.h"
#include "course.h"
#include "student.h"
#include <stdlib.h>

void initArbreFollowCourse(arbreFollowCourse *a) {
    *a = NULL;
}

void allocateNodeFollowCourse(arbreFollowCourse *a){
    *a = (arbreFollowCourse)malloc(sizeof(maillonFollowCourse));
}

arbreFollowCourse FGFollowCourse(arbreFollowCourse a) {
    return a->FG;
}
arbreFollowCourse FDFollowCourse(arbreFollowCourse a) {
    return a->FD;
}

void affFGFollowCourse(arbreFollowCourse a,arbreFollowCourse b) {
    a->FG = b;
}
void affFDFollowCourse(arbreFollowCourse a,arbreFollowCourse b) {
    a->FD = b;
}

void scanFollowCourse(followCourse *fc){
    printf("Id student= ");
    scanf("%d",&fc->student_id);
    printf("Id course= ");
    scanf("%d",&fc->course_id);
}
followCourse valueFollowCourse(arbreFollowCourse a) {
    return a->value;
}
void affValueFollowCourse(arbreFollowCourse a,followCourse value) {
    a->value = value;
}


/**/arbreFollowCourse insertNodeFollowCourseIdStudent(arbreFollowCourse a, followCourse value) {
    if (a == NULL) {
        arbreFollowCourse p;

        allocateNodeFollowCourse(&p);
        affValueFollowCourse(p, value);
        affFDFollowCourse(p, NULL);
        affFGFollowCourse(p, NULL);
        a = p;
    }else{
        if (a->value.student_id >= value.student_id ) {
            affFGFollowCourse(a,insertNodeFollowCourseIdStudent(FGFollowCourse(a), value));
        } else{
            affFDFollowCourse(a,insertNodeFollowCourseIdStudent(FDFollowCourse(a), value));
        }
    }
    return a;
}
/**/arbreFollowCourse insertNodeFollowCourseIdCourse(arbreFollowCourse a, followCourse value){
    if (a == NULL) {
        arbreFollowCourse p;

        allocateNodeFollowCourse(&p);
        affValueFollowCourse(p, value);
        affFDFollowCourse(p, NULL);
        affFGFollowCourse(p, NULL);
        a = p;
    }else{
        if (a->value.course_id >= value.course_id ) {
            affFGFollowCourse(a,insertNodeFollowCourseIdCourse(FGFollowCourse(a), value));
        } else{
            affFDFollowCourse(a,insertNodeFollowCourseIdCourse(FDFollowCourse(a), value));
        }
    }
    return a;
}


arbreFollowCourse parse_follow_course_csv_student_Id(char *inputFileName){
    FILE *f = fopen(inputFileName,"r");

    if (f == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    followCourse temp;
    arbreFollowCourse idSArbre;

    initArbreFollowCourse(&idSArbre);
    while(fscanf(f, "%d,%d%*c", &temp.student_id, &temp.course_id) == 2){
        idSArbre=insertNodeFollowCourseIdStudent(idSArbre,temp);
    }
    fclose(f);
    return idSArbre;
}
arbreFollowCourse parse_follow_course_csv_course_Id(char *inputFileName){
    FILE *f = fopen(inputFileName,"r");

    if (f == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    followCourse temp;
    arbreFollowCourse idCArbre;

    initArbreFollowCourse(&idCArbre);
    while(fscanf(f, "%d,%d%*c", &temp.student_id, &temp.course_id) == 2){
        idCArbre=insertNodeFollowCourseIdCourse(idCArbre,temp);
    }
    fclose(f);
    return idCArbre;
}


arbreFollowCourse parcoureArbreFollowCourse(arbreFollowCourse Arbre,FILE *f){
    followCourse temp;

    if(Arbre!=NULL){
        if(FGFollowCourse(Arbre)!=NULL){
            parcoureArbreFollowCourse(FGFollowCourse(Arbre),f);
        }
        temp=valueFollowCourse(Arbre);
        fprintf(f, "%d,%d\n", temp.student_id, temp.course_id);
        if(FDFollowCourse(Arbre)!=NULL){
            parcoureArbreFollowCourse(FDFollowCourse(Arbre),f);
        }
    }
    return Arbre;
}
bool serialize_follow_course_csv_student_Id(char *inputFileName, arbreFollowCourse Arbre, char *modeDAccee){
    FILE *f = fopen(inputFileName,modeDAccee);

    if (f == NULL) {
        printf("Error opening file\n");
        return false;
    }
    Arbre=parcoureArbreFollowCourse(Arbre,f);
    fclose(f);
    return true;
}
bool serialize_follow_course_csv_course_Id(char *inputFileName, arbreFollowCourse Arbre, char *modeDAccee){
    FILE *f = fopen(inputFileName,modeDAccee);

    if (f == NULL) {
        printf("Error opening file\n");
        return false;
    }
    Arbre=parcoureArbreFollowCourse(Arbre,f);
    fclose(f);
    return true;
}

void print_follow_course_table_header() {
    printf(" ______________ ______________  \n");
    printf("| %-12s | %-12s |\n", "Student ID", "Course ID");
    printf("|--------------|--------------|\n");
}

void print_tree_follow_course(arbreFollowCourse Arbre){
    followCourse fc;

    if(Arbre!=NULL){
        if(FGFollowCourse(Arbre)!=NULL){
            print_tree_follow_course(FGFollowCourse(Arbre));
        }
        fc=valueFollowCourse(Arbre);
        printf("| %-12d | %-12d |\n", fc.student_id, fc.course_id);
        if(FDFollowCourse(Arbre)!=NULL){
            print_tree_follow_course(FDFollowCourse(Arbre));
        }
    }
}

void deltree_f_s(arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    if(*f_s!=NULL){arbreFollowCourse d=FDFollowCourse(*f_s),g=FGFollowCourse(*f_s);
    deltree_f_s(&d,f_c) ;
    deltree_f_s(&g,f_c);
    del_f_c(valueFollowCourse(*f_s),1,f_s,f_c);
    free(*f_s);}
}
void deltree_f_c(arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    if(*f_c!=NULL){arbreFollowCourse d=FDFollowCourse(*f_c),g=FGFollowCourse(*f_c);
    deltree_f_c(f_s,&d) ;
    deltree_f_c(f_s,&g);
    del_f_s(valueFollowCourse(*f_c),1,f_s,f_c);
    free(*f_c);}
}

void del_f_s(followCourse f,int b,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    arbreFollowCourse q=*f_s,prec=NULL,p;
    while(q!=NULL){
    if((valueFollowCourse(q).student_id==f.student_id)&&((valueFollowCourse(q).course_id==f.course_id)||(b==0))){
        if(FGFollowCourse(q)==NULL){
        if(prec==NULL)*f_s=FDFollowCourse(q);else{
            if(q==FDFollowCourse(prec))affFDFollowCourse(prec,FDFollowCourse(q));else affFGFollowCourse(prec,FDFollowCourse(q));
        }
        if(b==0)del_f_c(valueFollowCourse(q),1,f_s,f_c);
        free(q);q=NULL;
        }else{
            if((FGFollowCourse(q)!=NULL)&&((FDFollowCourse(q)==NULL))){
                if(prec==NULL)*f_s=FGFollowCourse(q);else{
                if(q==FDFollowCourse(prec))affFDFollowCourse(prec,FGFollowCourse(q));else affFGFollowCourse(prec,FGFollowCourse(q));}
                p=FGFollowCourse(q);
                if(b==0)del_f_c(valueFollowCourse(q),1,f_s,f_c);
                free(q);q=p;
            }else{
                p=FDFollowCourse(q);
                while(FGFollowCourse(p)!=NULL)p=FGFollowCourse(p);
                if(prec==NULL)*f_s=FDFollowCourse(q);else{
                if(q==FDFollowCourse(prec))affFDFollowCourse(prec,FDFollowCourse(q));else affFGFollowCourse(prec,FDFollowCourse(q));}
                affFGFollowCourse(p,FGFollowCourse(q));
                if(b==0)del_f_c(valueFollowCourse(q),1,f_s,f_c);
                free(q);q=FGFollowCourse(p);prec=p;
            }
        }
    }else{prec=q;if(valueFollowCourse(q).student_id<f.student_id)q=FDFollowCourse(q);else q=FGFollowCourse(q);}
    }
}
void del_f_c(followCourse f,int b,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    arbreFollowCourse q=*f_c,prec=NULL,p;
    while(q!=NULL){
    if((valueFollowCourse(q).course_id==f.course_id)&&((valueFollowCourse(q).student_id==f.student_id)||(b==0))){
        if(FGFollowCourse(q)==NULL){
        if(prec==NULL)*f_c=FDFollowCourse(q);else{
            if(q==FDFollowCourse(prec))affFDFollowCourse(prec,FDFollowCourse(q));else affFGFollowCourse(prec,FDFollowCourse(q));
        }
        if(b==0)del_f_s(valueFollowCourse(q),1,f_s,f_c);
        free(q);q=NULL;
        }else{
            if((FGFollowCourse(q)!=NULL)&&((FDFollowCourse(q)==NULL))){
                if(prec==NULL)*f_c=FGFollowCourse(q);else{
                if(q==FDFollowCourse(prec))affFDFollowCourse(prec,FGFollowCourse(q));else affFGFollowCourse(prec,FGFollowCourse(q));}
                p=FGFollowCourse(q);
                if(b==0)del_f_s(valueFollowCourse(q),1,f_s,f_c);
                free(q);q=p;
            }else{
                p=FDFollowCourse(q);
                while(FGFollowCourse(p)!=NULL)p=FGFollowCourse(p);
                if(prec==NULL)*f_c=FDFollowCourse(q);else{
                if(q==FDFollowCourse(prec))affFDFollowCourse(prec,FDFollowCourse(q));else affFGFollowCourse(prec,FDFollowCourse(q));}
                affFGFollowCourse(p,FGFollowCourse(q));
                if(b==0)del_f_s(valueFollowCourse(q),1,f_s,f_c);
                free(q);q=FGFollowCourse(p);prec=p;
            }
        }
    }else{prec=q;if(valueFollowCourse(q).course_id<f.course_id)q=FDFollowCourse(q);else q=FGFollowCourse(q);}
    }
}

void del_follow(char* part1,char* part2,int b,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    followCourse f;arbreFollowCourse q,prec=NULL,p;
    f.course_id=atoi(part2);
    f.student_id=atoi(part2);
    switch(b){
        case 0:printf("\nChoix non valide!\n");break;
        case 1:
            if (strcmp(part1,"student_id")==0)del_f_s(f,0,f_s,f_c);
            else if(strcmp(part1,"course_id" )==0)del_f_c(f,0,f_s,f_c);
            else printf("\nChoix de la partie 3 non valide!\n");break;
        case 2:
            if (strcmp(part1,"student_id")==0){q=*f_s;
            while(q!=NULL){
                if(valueFollowCourse(q).student_id==f.student_id){
                        p=FDFollowCourse(q);
                    deltree_f_s(&p,f_c);
                        affFDFollowCourse(q,NULL);prec=q;q=FGFollowCourse(q);
                }else{
                     if(valueFollowCourse(q).student_id>f.student_id){p=FDFollowCourse(q);deltree_f_s(&p,f_c);affFDFollowCourse(q,NULL);p=FGFollowCourse(q);}
                     else{p=FGFollowCourse(q);deltree_f_s(&p,f_c);p=FDFollowCourse(q);affFGFollowCourse(q,NULL);}
                     if(prec==NULL)*f_s=p;else if(q==FDFollowCourse(prec))affFDFollowCourse(prec,p);else affFGFollowCourse(prec,p);
                     del_f_c(valueFollowCourse(q),1,f_s,f_c);
                     free(q);q=p;
                }
            }
            }
            else if(strcmp(part1,"course_id" )==0){q=*f_c;
            while(q!=NULL){
                if(valueFollowCourse(q).course_id==f.course_id){
                        p=FDFollowCourse(q);
                    deltree_f_c(f_s,&p);
                        affFDFollowCourse(q,NULL);prec=q;q=FGFollowCourse(q);
                }else{
                     if(valueFollowCourse(q).course_id>f.course_id){p=FDFollowCourse(q);deltree_f_c(f_s,&p);affFDFollowCourse(q,NULL);p=FGFollowCourse(q);}
                     else{p=FGFollowCourse(q);deltree_f_c(f_s,&p);p=FDFollowCourse(q);affFGFollowCourse(q,NULL);}
                     if(prec==NULL)*f_c=p;else if(q==FDFollowCourse(prec))affFDFollowCourse(prec,p);else affFGFollowCourse(prec,p);
                     del_f_s(valueFollowCourse(q),1,f_s,f_c);
                     free(q);q=p;
                }
              }
            }
            else printf("\nChoix de la partie 3 non valide!\n");break;
        case 3:
            if (strcmp(part1,"student_id")==0){q=*f_s;
                while(q!=NULL ){
                    if(valueFollowCourse(q).student_id<f.student_id){
                          p=FGFollowCourse(q);
                          deltree_f_s(&p,f_c);p=FDFollowCourse(q);
                        if(prec==NULL)*f_s=p;
                        else if (FGFollowCourse(prec)==q)affFGFollowCourse(prec,p);
                             else affFDFollowCourse(prec,p);
                    del_f_c(valueFollowCourse(q),1,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueFollowCourse(q).student_id>f.student_id){prec=q;q=FGFollowCourse(q);}
                    else{if(FGFollowCourse(q)!=NULL){
                            if(valueFollowCourse(FGFollowCourse(q)).student_id==f.student_id){prec=q;q=FGFollowCourse(q);}
                            else {p=FGFollowCourse(q);deltree_f_s(&p,f_c);
                            affFGFollowCourse(q,NULL);q=NULL;}
                    }else q=NULL;}}
                }
            }
            else if(strcmp(part1,"course_id" )==0){q=*f_c;
                while(q!=NULL ){
                    if(valueFollowCourse(q).course_id<f.course_id){
                          p=FGFollowCourse(q);
                          deltree_f_c(f_s,&p);p=FDFollowCourse(q);
                        if(prec==NULL)*f_c=p;
                        else if (FGFollowCourse(prec)==q)affFGFollowCourse(prec,p);
                             else affFDFollowCourse(prec,p);
                    del_f_s(valueFollowCourse(q),1,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueFollowCourse(q).course_id>f.course_id){prec=q;q=FGFollowCourse(q);}
                    else{if(FGFollowCourse(q)!=NULL){
                            if(valueFollowCourse(FGFollowCourse(q)).course_id==f.course_id){prec=q;q=FGFollowCourse(q);}
                            else {p=FGFollowCourse(q);deltree_f_c(f_s,&p);
                            affFGFollowCourse(q,NULL);q=NULL;}
                    }else q=NULL;}}
                }
            }
            else printf("\nChoix de la partie 3 non valide!\n");break;
        case 4:
            if (strcmp(part1,"student_id")==0){q=*f_s;
                while(q!=NULL ){
                    if(valueFollowCourse(q).student_id>f.student_id){
                          p=FDFollowCourse(q);
                          deltree_f_s(&p,f_c);p=FGFollowCourse(q);
                        if(prec==NULL)*f_s=p;
                        else if (FGFollowCourse(prec)==q)affFGFollowCourse(prec,p);
                             else affFDFollowCourse(prec,p);
                    del_f_c(valueFollowCourse(q),1,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueFollowCourse(q).student_id<f.student_id){prec=q;q=FDFollowCourse(q);}
                    else{p=FDFollowCourse(q);deltree_f_s(&p,f_c);affFDFollowCourse(q,NULL);q=NULL;}
                    }
                }
            }
            else if(strcmp(part1,"course_id" )==0){q=*f_c;
                while(q!=NULL ){
                    if(valueFollowCourse(q).course_id>f.course_id){
                          p=FDFollowCourse(q);
                          deltree_f_c(f_s,&p);p=FGFollowCourse(q);
                        if(prec==NULL)*f_c=p;
                        else if (FGFollowCourse(prec)==q)affFGFollowCourse(prec,p);
                             else affFDFollowCourse(prec,p);
                    del_f_s(valueFollowCourse(q),1,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueFollowCourse(q).course_id<f.course_id){prec=q;q=FDFollowCourse(q);}
                    else{p=FDFollowCourse(q);deltree_f_c(f_s,&p);affFDFollowCourse(q,NULL);q=NULL;}
                    }
                }
            }
            else printf("\n!! Choix de la partie 3 non valide !!\n");break;
        case 5:
            if (strcmp(part1,"student_id")==0){q=*f_s;
                while(q!=NULL){
                    if(valueFollowCourse(q).student_id<f.student_id){
                          p=FGFollowCourse(q);
                          deltree_f_s(&p,f_c);p=FDFollowCourse(q);
                        if(prec==NULL)*f_s=p;
                        else if (FGFollowCourse(prec)==q)affFGFollowCourse(prec,p);
                             else affFDFollowCourse(prec,p);
                    del_f_c(valueFollowCourse(q),1,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueFollowCourse(q).student_id>f.student_id){prec=q;q=FGFollowCourse(q);}
                    else{p=FGFollowCourse(q);deltree_f_s(&p,f_c);p=FDFollowCourse(q);
                        if(prec==NULL)*f_s=p;
                        else if (FGFollowCourse(prec)==q)affFGFollowCourse(prec,p);
                             else affFDFollowCourse(prec,p);
                        del_f_c(valueFollowCourse(q),1,f_s,f_c);
                        free(q);q=NULL;}}
                }
            }
            else if(strcmp(part1,"course_id" )==0){q=*f_c;
                while(q!=NULL){
                    if(valueFollowCourse(q).course_id<f.course_id){
                          p=FGFollowCourse(q);
                          deltree_f_c(f_s,&p);p=FDFollowCourse(q);
                        if(prec==NULL)*f_c=p;
                        else if (FGFollowCourse(prec)==q)affFGFollowCourse(prec,p);
                             else affFDFollowCourse(prec,p);
                    del_f_s(valueFollowCourse(q),1,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueFollowCourse(q).course_id>f.course_id){prec=q;q=FGFollowCourse(q);}
                    else{p=FGFollowCourse(q);deltree_f_c(f_s,&p);p=FDFollowCourse(q);
                        if(prec==NULL)*f_c=p;
                        else if (FGFollowCourse(prec)==q)affFGFollowCourse(prec,p);
                             else affFDFollowCourse(prec,p);
                        del_f_s(valueFollowCourse(q),1,f_s,f_c);
                        free(q);q=NULL;}}
                }
            }
            else printf("\n!! Choix de la partie 3 non valide !!\n");break;
        case 6:
            if (strcmp(part1,"student_id")==0){q=*f_s;
                while(q!=NULL){
                    if(valueFollowCourse(q).student_id>f.student_id){
                          p=FDFollowCourse(q);
                          deltree_f_s(&p,f_c);p=FGFollowCourse(q);
                        if(prec==NULL)*f_s=p;
                        else if (FGFollowCourse(prec)==q)affFGFollowCourse(prec,p);
                             else affFDFollowCourse(prec,p);
                    del_f_c(valueFollowCourse(q),1,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueFollowCourse(q).student_id<f.student_id){prec=q;q=FDFollowCourse(q);}
                    else{p=FDFollowCourse(q);deltree_f_s(&p,f_c);p=FGFollowCourse(q);
                        if(prec==NULL)*f_s=p;
                        else if (FGFollowCourse(prec)==q)affFGFollowCourse(prec,p);
                             else affFDFollowCourse(prec,p);
                        del_f_c(valueFollowCourse(q),1,f_s,f_c);
                        free(q);q=p;}}
                }
            }
            else if(strcmp(part1,"course_id")==0){q=*f_c;
                while(q!=NULL){
                    if(valueFollowCourse(q).course_id>f.course_id){
                          p=FDFollowCourse(q);
                          deltree_f_c(f_s,&p);p=FGFollowCourse(q);
                        if(prec==NULL)*f_c=p;
                        else if (FGFollowCourse(prec)==q)affFGFollowCourse(prec,p);
                             else affFDFollowCourse(prec,p);
                    del_f_s(valueFollowCourse(q),1,f_s,f_c);
                    free(q);q=p;

                    }else{if(valueFollowCourse(q).course_id<f.course_id){prec=q;q=FDFollowCourse(q);}
                    else{p=FDFollowCourse(q);deltree_f_c(f_s,&p);p=FGFollowCourse(q);
                        if(prec==NULL)*f_c=p;
                        else if (FGFollowCourse(prec)==q)affFGFollowCourse(prec,p);
                             else affFDFollowCourse(prec,p);
                        del_f_s(valueFollowCourse(q),1,f_s,f_c);
                        free(q);q=p;}}
                }
            }
            else printf("\n!! Choix de la partie 3 non valide !!\n");break;}

}

