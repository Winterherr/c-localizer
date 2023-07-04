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

int get_line_length(){
  char line[24];
  printf("weed");
  //fgets(line, 23, language_index_file);
  printf("%ld", strlen(line));
  return strlen(line);
}

//set the path where the localized files are
void set_localizer_path(char* path){
  strcpy(locale_path, path);
}

void set_language_index_file(void){
  strcpy(language_index_path, locale_path);
  strcat(language_index_path, "language_index.yml");
  //printf("%s\n",language_index_path);
  language_index_file = fopen(language_index_path, "r");
  if(!language_index_file)
    perror("gefickt");
}

//check language_index.yaml for language ids
//return de_ or en_ ... return should be checked for NULL
char* get_language_id(char language){
  line_buffer=malloc(sizeof(char)*BUFSIZ);
  char c;
  int i = 0;
  int line_length = 6;
  printf("%d\n", line_length);
  if(!language_index_file)
    printf("hier ist was falsch bre");
  
  while(language != (c = fgetc(language_index_file))){
    printf("%c\t", c);
    if(feof(language_index_file))
      return NULL; 
    fseek(language_index_file, line_length*(i), SEEK_SET); //6 is the length of one line, will become problematic when more than 10 langauges exist, but I doubt that
    ++i;
  }
  printf("Schleife Ende\n");
  //return :ID_ because of fgetc() in the loop the pointer is set one forward    
  fseek(language_index_file, 6*(i)+2, SEEK_SET); //+2 = ignore x:
  fgets(line_buffer, 3, language_index_file); //3 : lenght of ISO code + \0
  strcat(line_buffer, "_");
  return line_buffer;
}

//name= main_menu / description
FILE* open_localised_file(char* name, char language_id){
  char file_path[100];
  append_localised_file_path(file_path,name,language_id);
  printf("%s\n", file_path);
  return fopen(file_path, "r");
}

char* get_localized_string(FILE* localized_file ,char* name, char category){
  strcpy(requested_string, name);
  strcat(requested_string, get_category(category));
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

