#ifndef COMMANDHANDLERS_H_INCLUDED
#define COMMANDHANDLERS_H_INCLUDED

void printHelp();
void parseCondition(const char *condition, char *attribute, char *operator, char *value);
void handleInsertCommand(const char *command,arbreStudent arbres[],arbreCourse arbresC[],int *studentIdCount,int *courseIdCount);
void handleSelectcommand(const char *command,arbreStudent arbres[],arbreCourse arbresC[]);
void handleClose(arbreStudent arbres[],arbreCourse arbresC[]);

#endif // COMMANDHANDLERS_H_INCLUDED
