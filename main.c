#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include "followCourse.h"
#include "course.h"
#include "student.h"
#include "commandHandlers.h"

int main()
{
    int idCount = -1;
    int idCourseCount = -1;
    char command[30];
    arbreStudent idStudent = NULL;
    arbreStudent nameStudent = NULL;
    arbreStudent ageStudent = NULL;
    arbreStudent majorStudent = NULL;
    arbreCourse idCourse,nameCourse,instructorCourse;
    arbreFollowCourse idStudentFC,idCourseFC;

    initArbreStudent(&idStudent);
    initArbreStudent(&nameStudent);
    initArbreStudent(&ageStudent);
    initArbreStudent(&majorStudent);

    initArbreCourse(&idCourse);
    initArbreCourse(&nameCourse);
    initArbreCourse(&instructorCourse);
    printf("\t\t\t\t\x1b[31m     _  _____  _ __   __ _  _____  _\n"
           "\t\t\t\t\x1b[33m    / \\|_   _|/ \\\\ \\ / // \\|_   _|/ \\\n"
           "\t\t\t\t\x1b[32m   / _ \\ | | / _ \\\\ V // _ \\ | | / _ \\\n"
           "\t\t\t\t\x1b[36m  / ___ \\| |/ ___ \\| |/ ___ \\| |/ ___ \\\n"
           "\t\t\t\t\x1b[34m /_/   \\_\\_/_/   \\_\\_/_/   \\_\\_/_/   \\_\\\n");
    printHelp();
    initArbreFollowCourse(&idStudentFC);
    initArbreFollowCourse(&idCourseFC);
    do{
        printf("\033[1;32m");
        fflush(stdin);
        printf("> ");
        gets(command);
        printf("\033[1;37m");
        if(strcmp(command,"load")==0){
            char nomFichier[21];
            /*printf("Donner le nom de fichier avec l'extension csv (nom.csv): ");
            fflush(stdin);
            gets(nomFichier);
            //puts(nomFichier);*/

            strcpy(nomFichier,"students.csv");

            idStudent=parse_students_csv_student_Id(nomFichier);
            nameStudent=parse_students_csv_name(nomFichier);
            ageStudent=parse_students_csv_age(nomFichier);
            majorStudent=parse_students_csv_major(nomFichier);
            print_student_table_header();
            print_tree_student(idStudent);
            printf("|____________|________________________________|____________|______________________|\n");
            printf("\nSuccessfully loaded.\n");
            system("pause");

            strcpy(nomFichier,"courses.csv");

            idCourse=parse_course_csv_course_Id(nomFichier);
            nameCourse=parse_course_csv_course_name(nomFichier);
            instructorCourse=parse_course_csv_course_instructor(nomFichier);
            countCourseId(idCourse,&idCourseCount);
            print_course_table_header();
            print_tree_course(idCourse);
            printf("|____________|________________________________|______________________|\n");
            printf("\nSuccessfully loaded.\n");
            system("pause");

            strcpy(nomFichier,"follow_course.csv");
            idStudentFC=parse_follow_course_csv_student_Id(nomFichier);
            idCourseFC=parse_follow_course_csv_course_Id(nomFichier);
            print_follow_course_table_header();
            print_tree_follow_course(idStudentFC);
            printf("|______________|______________|\n");
            system("pause");
            countCourseId(idCourse,&idCourseCount);
            countStudentId(idStudent,&idCount);
        }else if(strcmp(command,"save")==0){
            char nomFichier[21];
            char modeDAccee[4] = "w";
            char choisir[4];

          /*  printf("Donner le nom de fichier avec l'extension csv (nom.csv) : ");
            fflush(stdin);
            gets(nomFichier);
            //puts(nomFichier);*/
            printf("Voulez vous supprimer le contunue s'il existe ou non \n(ecrire oui si oui sinon tapper autre mot) : ");
            fflush(stdin);
            gets(choisir);/*
            if(strcmp(choisir,"oui")==0){
                strcpy(modeDAccee,"w");
            }else{
                strcpy(modeDAccee,"a");
            }*/
            strcpy(nomFichier,"students.csv");
            if(!serialize_students_csv_student_Id(nomFichier,idStudent,modeDAccee)){
                printf("ERROR NOT SAVED the work in file: %s\n",nomFichier);
            }
            system("pause");
            strcpy(nomFichier,"courses.csv");
            if(!serialize_course_csv_course_Id(nomFichier,idCourse,modeDAccee)){
                printf("ERROR NOT SAVED the work in file: %s\n",nomFichier);
            }

            strcpy(nomFichier,"follow_course.csv");
            if(!serialize_follow_course_csv_student_Id(nomFichier,idStudentFC,modeDAccee)){
                printf("ERROR NOT SAVED the work in file: %s\n",nomFichier);
            }
        }else if(strncmp(command, "insert", 6) == 0){
            if(idCount == -1){
                printf("You should type command load before inserting.\n");
            }else{
            arbreStudent arbres[4] = {idStudent,nameStudent,ageStudent,majorStudent};
            arbreCourse arbresC[3] = {idCourse,nameCourse,instructorCourse};
            handleInsertCommand(command,arbres,arbresC,&idCount,&idCourseCount);
            }
    }else if(strncmp(command, "select", 6) == 0){
        if(idCount == -1){
                printf("You should type command load before selecting.\n");
        }else{
            arbreStudent arbres[4] = {idStudent,nameStudent,ageStudent,majorStudent};
            arbreCourse arbresC[3] = {idCourse,nameCourse,instructorCourse};
            handleSelectcommand(command,arbres,arbresC);
        }
    }else if(strncmp(command, "clear", 5) == 0){
        system("cls");
    }else if(strncmp(command, "close", 5) == 0){
        arbreStudent arbres[4] = { idStudent,nameStudent,ageStudent,majorStudent };
        arbreCourse arbresC[3] = { idCourse,nameCourse,instructorCourse };
        handleClose(arbres,arbresC);
        exit(0);
    } else if(strncmp(command, "help", 4) == 0){
        printHelp();
    }else if(strncmp(command, "delete", 6) == 0){
        Delete(command,&idStudent,&ageStudent,&nameStudent,&majorStudent,&idCourse,&nameCourse,&instructorCourse,&idStudentFC,&idCourseFC);
    } else{
        printf("Invalid command. 42\n");
    }

        }
    while(1);
    return 0;
}

