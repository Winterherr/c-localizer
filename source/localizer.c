#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>

#include "localizer.h"

#define TITLE '0'
#define DESCRIPTION '1'

#define SEPERATOR ':'
#define ENGLISH '0'
#define GERMAN '1'
#define FINNISH '2'

#define LANG_ID_MAX 2


char   locale_path[PATH_MAX];
char   language_index_path[PATH_MAX];
char   requested_string[BUFSIZ];
char*  line_buffer;

FILE* language_index_file;

//set the path where the localized files are
void set_localizer_path(char* path){
  strcpy(locale_path, path);
}

//return void because user doesnt need access to the file pointer
void open_language_index_file(char* index_file_name){
  char index_path[PATH_MAX];
  strcpy(index_path, locale_path);
  strcat(index_path, index_file_name);
  language_index_file = fopen(index_path, "r");
}

//check language_index.yaml for language ids, for custom languages use 'n' with n being a number
//return de_ or en_ ... return should be checked for NULL
char* get_language_id(char language){
  char* line_buffer = (char*) malloc(sizeof(char)*BUFSIZ);
  char c;
  int offset = 0;
  while(language != (c=fgetc(language_index_file)))
    ;
  fgetc(language_index_file);
  fgets(line_buffer, 3, language_index_file); //3 because 2 for ISO CODE and 1 for \0
  strcat(line_buffer, "_\0");
  return line_buffer;
}

//name: name of the file (main_menu/settings_menu e.c), language id: which language to use
FILE* open_localised_file(char* name, char language_id){
  char file_path[100];
  append_localised_file_path(file_path,name,language_id);
  return fopen(file_path, "r");
}
//return a \0 terminated string after the seperator in the line with the requested string
char* get_localized_string_from_file(FILE* localized_file ,char* name, char category){
  char name_buffer[BUFSIZ];
  char name_buffer_file[BUFSIZ];
  int line_offset = 0;

  strcpy(requested_string, name);
  strcat(requested_string, get_category(category));
  printf("requested string: %s\n", requested_string);
  while(1){
    fgets(name_buffer_file, BUFSIZ, localized_file);
    strcpy_to_char(name_buffer, name_buffer_file, SEPERATOR);
    printf("%s | %s \n", name_buffer, requested_string);
    if (strcmp(name_buffer, requested_string)){
      printf("gleich mit: %s | %s\n", name_buffer, requested_string);
      break;
    }
    line_offset+=strlen(name_buffer_file);
  }
  fgets(requested_string, BUFSIZ, localized_file);
  return requested_string;  
}

void free_line_buffer(void){
  free(line_buffer);
}

void append_localised_file_path(char* dest ,char* name, char language_id){
  strcpy(dest, locale_path);
  strcat(dest, get_language_id(language_id));
  strcat(dest,name);
  strcat(dest, ".yml");
  printf("%s\n",dest);;
}

char* get_category(char category){
  switch (category) {
    case TITLE:
      return "_title";
    case DESCRIPTION:
      return "_description";
    default:
      return "";
  }
}

void strcpy_to_char(char* dest, char* src, char stop){
  char* dest_start = dest;
  while (*src != stop && *src != '\0') {
    (*dest) = *(src);
    dest++;
    src++;
  }
  *(dest++) = '\0';
  dest = dest_start;
}
