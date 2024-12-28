#include "student.h"
#include "course.h"
#include <stdlib.h>
#include "followCourse.h"
void parseCondition(const char *condition, char *attribute, char *operator, char *value) {
    sscanf(condition, "%10[^!=<>]%4[!=<>]%49s", attribute, operator, value);
}

void printHelp() {

    printf("\x1b[37m");printf("\n\n Available Commands:\n");
    printf("  help   - Display this help menu\n");
    printf("  load   - Load data from a file to memory\n");
    printf("  insert - Insert data into memory\n");
    printf("  select - Select data from memory\n");
    printf("  delete - Delete data from memory\n");
    printf("  save   - Save data from memory to a file\n");
    printf("  close  - Free memory and close the program\n\n");
}

void handleInsertCommand(const char *command,arbreStudent arbres[],arbreCourse arbresC[],int *studentIdCount,int *courseIdCount) {
    char type[10];  // Assuming a maximum length of 10 for the type (course or student)
    if (sscanf(command + 7, "%9s", type) == 1) {
        // Check if the type is "course" or "student"
        if (strcmp(type, "course") == 0) {
            insertCourse(command,arbresC,courseIdCount);
        } else if (strcmp(type, "student") == 0) {

            insertStudent(command,arbres,studentIdCount);
        } else {
            printf("Invalid type after 'insert'.\n");
        }
    } else {
        // Handle invalid input format
        printf("Invalid 'insert' command format.\n");
    }
}

void handleSelectcommand(const char *command,arbreStudent arbres[],arbreCourse arbresC[]){
    char attribute[50], op[10], value[50],type[10];

    if (sscanf(command + 7, "%9s", type) == 1) {
        // Check if the type is "course" or "student"
    if (strcmp(type, "student") == 0) {
        parseCondition(command+15,attribute, op, value);
        if (strncmp(attribute, "age", 3) == 0) {
            char *endptr;
            int num = strtol(value, &endptr, 10);

            if (*endptr != '\0') {
                printf("Wrong age format: %s\n", value);
            } else {

                if (strcmp(op, "=") == 0) {
                    print_student_table_header();
                    rech_stud_node_age(arbres[2], num);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if (strcmp(op, ">") == 0) {
                    print_student_table_header();
                    rech_stud_node_sup_age(arbres[2], num);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if (strcmp(op, "<") == 0) {
                    print_student_table_header();
                    rech_stud_node_inf_age(arbres[2], num);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if (strcmp(op, ">=") == 0) {
                    print_student_table_header();
                    rech_stud_node_sup_eg_age(arbres[2], num);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if(strcmp(op, "<=") == 0) {
                    print_student_table_header();
                    rech_stud_node_inf_eg_age(arbres[2], num);
                    printf("|____________|________________________________|____________|______________________|\n");
                }else if(strcmp(op, "!=") == 0){
                    print_student_table_header();
                    rech_stud_node_Not_age(arbres[2], num);
                    printf("|____________|________________________________|____________|______________________|\n");
                }else{
                    printf("Invalid operator for age attribute\n");
                }
            }
        }else if(strncmp(attribute, "id", 2) == 0){
            char *endptr;
            int num = strtol(value, &endptr, 10);

            if (*endptr != '\0') {
                printf("Wrong age format: %s\n", value);
            } else {

                if (strcmp(op, "=") == 0) {
                    print_student_table_header();
                    rech_stud_node_id(arbres[0], num);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if (strcmp(op, ">") == 0) {
                    print_student_table_header();
                    rech_stud_node_sup_id(arbres[0], num);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if (strcmp(op, "<") == 0) {
                    print_student_table_header();
                    rech_stud_node_inf_id(arbres[0], num);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if (strcmp(op, ">=") == 0) {
                    print_student_table_header();
                    rech_stud_node_sup_eg_id(arbres[0], num);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if(strcmp(op, "<=") == 0) {
                    print_student_table_header();
                    rech_stud_node_inf_eg_id(arbres[0], num);
                    printf("|____________|________________________________|____________|______________________|\n");
                }else if(strcmp(op, "!=") == 0){
                    print_student_table_header();
                    rech_stud_node_Not_id(arbres[0], num);
                    printf("|____________|________________________________|____________|______________________|\n");
                }else{
                    printf("Invalid operator for id attribute.\n");
                }
            }

        }else if(strncmp(attribute, "name", 4) == 0){
                int len = strlen(value);

                if (len >= 2 && value[0] == '"' && value[len - 1] == '"') {
                    // Remove double quotes
                    memmove(value, value + 1, len - 2);
                    value[len - 2] = '\0';
                }else{
                    printf("Invalid name format.\n");
                    return;
                }

                if (strcmp(op, "=") == 0) {
                    print_student_table_header();
                    rech_stud_node_name(arbres[1], value);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if (strcmp(op, ">") == 0) {
                    print_student_table_header();
                    rech_stud_node_sup_name(arbres[1], value);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if (strcmp(op, "<") == 0) {
                    print_student_table_header();
                    rech_stud_node_inf_name(arbres[1], value);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if (strcmp(op, ">=") == 0) {
                    print_student_table_header();
                    rech_stud_node_sup_eg_name(arbres[1], value);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if(strcmp(op, "<=") == 0) {
                    print_student_table_header();
                    rech_stud_node_inf_eg_name(arbres[1], value);
                    printf("|____________|________________________________|____________|______________________|\n");
                }else if(strcmp(op, "!=") == 0){
                    print_student_table_header();
                    rech_stud_node_Not_name(arbres[1], value);
                    printf("|____________|________________________________|____________|______________________|\n");
                }else{
                    printf("Invalid operator for name attribute.\n");
                }

        }else if(strncmp(attribute, "major", 5) == 0){
                int len = strlen(value);

                if (len >= 2 && value[0] == '"' && value[len - 1] == '"') {
                    // Remove double quotes
                    memmove(value, value + 1, len - 2);
                    value[len - 2] = '\0';
                }else{
                    printf("Invalid major format.\n");
                    return;
                }

                if (strcmp(op, "=") == 0) {
                    print_student_table_header();
                    rech_stud_node_major(arbres[3], value);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if (strcmp(op, ">") == 0) {
                    print_student_table_header();
                    rech_stud_node_sup_major(arbres[3], value);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if (strcmp(op, "<") == 0) {
                    print_student_table_header();
                    rech_stud_node_inf_major(arbres[3], value);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if (strcmp(op, ">=") == 0) {
                    print_student_table_header();
                    rech_stud_node_sup_eg_major(arbres[3], value);
                    printf("|____________|________________________________|____________|______________________|\n");
                } else if(strcmp(op, "<=") == 0) {
                    print_student_table_header();
                    rech_stud_node_inf_eg_major(arbres[3], value);
                    printf("|____________|________________________________|____________|______________________|\n");
                }else if(strcmp(op, "!=") == 0){
                    print_student_table_header();
                    rech_stud_node_Not_major(arbres[3], value);
                    printf("|____________|________________________________|____________|______________________|\n");
                }else{
                    printf("Invalid operator for major attribute.\n");
                }

        }else {
            printf("Invalid attribute.\n");
        }
    }else if (strcmp(type, "course") == 0){
        parseCondition(command+14,attribute, op, value);
        if (strncmp(attribute, "id", 2) == 0) {
            char *endptr;
            int num = strtol(value, &endptr, 10);

            if (*endptr != '\0') {
                printf("Wrong id format: %s\n", value);
            } else {
                if (strcmp(op, "=") == 0) {
                    print_course_table_header();
                    rech_cour_node_id(arbresC[0], num);
                    printf("|____________|________________________________|______________________|\n");
                } else if (strcmp(op, ">") == 0) {
                    print_course_table_header();
                    rech_cour_node_sup_id(arbresC[0], num);
                    printf("|____________|________________________________|______________________|\n");
                } else if (strcmp(op, "<") == 0) {
                    print_course_table_header();
                    rech_cour_node_inf_id(arbresC[0], num);
                    printf("|____________|________________________________|______________________|\n");
                } else if (strcmp(op, ">=") == 0) {
                    print_course_table_header();
                    rech_cour_node_sup_eg_id(arbresC[0], num);
                    printf("|____________|________________________________|______________________|\n");
                } else if(strcmp(op, "<=") == 0) {
                    print_course_table_header();
                    rech_cour_node_inf_eg_id(arbresC[0], num);
                    printf("|____________|________________________________|______________________|\n");
                }else if(strcmp(op, "!=") == 0){
                    print_course_table_header();
                    rech_cour_node_Not_id(arbresC[0], num);
                    printf("|____________|________________________________|______________________|\n");
                }else{
                    printf("Invalid operator for id attribute\n");
                }
            }
    }else if(strncmp(attribute, "name", 4) == 0){
                int len = strlen(value);

                if (len >= 2 && value[0] == '"' && value[len - 1] == '"') {
                    // Remove double quotes
                    memmove(value, value + 1, len - 2);
                    value[len - 2] = '\0';
                }else{
                    printf("Invalid name format.\n");
                    return;
                }
                if (strcmp(op, "=") == 0) {
                    print_course_table_header();
                    rech_cour_node_course_name(arbresC[1], value);
                    printf("|____________|________________________________|______________________|\n");
                } else if (strcmp(op, ">") == 0) {
                    print_course_table_header();
                    rech_cour_node_sup_course_name(arbresC[1], value);
                    printf("|____________|________________________________|______________________|\n");
                } else if (strcmp(op, "<") == 0) {
                    print_course_table_header();
                    rech_cour_node_inf_course_name(arbresC[1], value);
                    printf("|____________|________________________________|______________________|\n");
                } else if (strcmp(op, ">=") == 0) {
                    print_course_table_header();
                    rech_cour_node_sup_eg_course_name(arbresC[1], value);
                    printf("|____________|________________________________|______________________|\n");
                } else if(strcmp(op, "<=") == 0) {
                    print_course_table_header();
                    rech_cour_node_inf_eg_course_name(arbresC[1], value);
                    printf("|____________|________________________________|______________________|\n");
                }else if(strcmp(op, "!=") == 0){
                    print_course_table_header();
                    rech_cour_node_Not_course_name(arbresC[1], value);
                    printf("|____________|________________________________|______________________|\n");
                }else{
                    printf("Invalid operator for name attribute.\n");
                }
    }else if(strncmp(attribute, "instructor", 10) == 0){
                int len = strlen(value);

                if (len >= 2 && value[0] == '"' && value[len - 1] == '"') {
                    // Remove double quotes
                    memmove(value, value + 1, len - 2);
                    value[len - 2] = '\0';
                }else{
                    printf("Invalid instructor format.\n");
                    return;
                }

                if (strcmp(op, "=") == 0) {
                    print_course_table_header();
                    rech_cour_node_instructor(arbresC[2], value);
                    printf("|____________|________________________________|______________________|\n");
                } else if (strcmp(op, ">") == 0) {
                    print_course_table_header();
                    rech_cour_node_sup_instructor(arbresC[2], value);
                    printf("|____________|________________________________|______________________|\n");
                } else if (strcmp(op, "<") == 0) {
                    print_course_table_header();
                    rech_cour_node_inf_instructor(arbresC[2], value);
                    printf("|____________|________________________________|______________________|\n");
                } else if (strcmp(op, ">=") == 0) {
                    print_course_table_header();
                    rech_cour_node_sup_eg_instructor(arbresC[2], value);
                    printf("|____________|________________________________|______________________|\n");
                } else if(strcmp(op, "<=") == 0) {
                    print_course_table_header();
                    rech_cour_node_inf_eg_instructor(arbresC[2], value);
                    printf("|____________|________________________________|______________________|\n");
                }else if(strcmp(op, "!=") == 0){
                    print_course_table_header();
                    rech_cour_node_Not_instructor(arbresC[2], value);
                    printf("|____________|________________________________|______________________|\n");
                }else{
                    printf("Invalid operator for instructor attribute.\n");
                }
    }else{
        printf("Invalid attribute.\n");
    }
    }else{
        printf("Invalid command.\n");
    }
    }
}

void handleClose(arbreStudent arbres[],arbreCourse arbresC[]){
    closeStudent(arbres[0]);
    closeStudent(arbres[1]);
    closeStudent(arbres[2]);
    closeStudent(arbres[3]);
    closeCourse(arbresC[0]);
    closeCourse(arbresC[1]);
    closeCourse(arbresC[2]);
}

void Delete(char* command,arbreStudent *s_id,arbreStudent *s_age,arbreStudent *s_name,arbreStudent *s_major,arbreCourse *c_id,arbreCourse *c_name,arbreCourse *c_instr,arbreFollowCourse *f_s,arbreFollowCourse *f_c){
    printf("-----------------------------------------------------------------------\ncmd:delete part1 part2[=|!=|<|>|<=|>=]part3\npart1:[student,course,follow]\npart2:[age,id,name,major|course,id,instructor|student_id,course_id]\n-----------------------------------------------------------------------\n");
    int b=0;char part1[40],part2[40],part3[40],part4[40];
    if (sscanf(command, "%39s %39[^!]!=%39s", part1, part2,part3,part4) == 4) b=2;
    else if (sscanf(command, "%39s %39s %39[^<]<=%39s", part1, part2,part3,part4) == 4) b=5;
    else if (sscanf(command, "%39s %39s %39[^>]>=%39s", part1, part2,part3,part4) == 4) b=6;
    else if (sscanf(command, "%39s %39s %39[^<]<%39s", part1, part2,part3,part4) == 4) b=3;
    else if (sscanf(command, "%39s %39s %39[^>]>%39s", part1, part2,part3,part4) == 4) b=4;
    else if (sscanf(command, "%39s %39s %39[^=]=%39s", part1, part2,part3,part4) == 4) b=1;
    else printf("\n!! commande incorrecte !!\n");
    if(strcmp(part1,"delete")!=0)printf("\n!!! not a delete command !!!\n");
    else{
        int length = strlen(part4);
        if (length <= 2) {
            printf("Invalid input format.\n");
            return;
        }
        // Remove quotes from string
        if (part4[0] == '\"' && part4[length - 1] == '\"') {
            memmove(part4, part4 + 1, length - 2);
            part4[length - 2] = '\0';
        }
        if(strcmp(part2,"student")==0)del_student(part3,part4,b,s_id,s_age,s_name,s_major,f_s,f_c);
        else if(strcmp(part2,"course")==0)del_course(part3,part4,b,c_id,c_name,c_instr,f_s,f_c);
            else if(strcmp(part2,"follow")==0)del_follow(part3,part4,b,f_s,f_c);
                 else printf("\n!!! part2 not valid !!!\n");

    }
}
