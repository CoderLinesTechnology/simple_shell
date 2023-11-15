#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <ctype.h>



extern char **environ;


char *get_file_path(char *file_name);
char *get_file_loc(char *path, char *file_name);
int check_full_path(const char *str);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
bool handle_exit(char *command);
void handle_env(void);
void cleanup(char **array, char *buffer);



#endif
