#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>

#include "localizer.h"
//! IT IS ADVISED TO CHANGE THESE DEFINES WHEN USING YOUR OWN FILES AND TO MODIFY get_category ACCORDINGLY
#define TITLE 0
#define DESCRIPTION 1

#define SEPERATOR ':'

#define LANG_ID_MAX 2

char   locale_path[PATH_MAX];
char   language_index_path[PATH_MAX];
char   requested_string[BUFSIZ];
char*  line_buffer;

FILE* language_index_file;

void init_localizer(char *path, char *index_file_name){
  set_localizer_path(path);
  open_language_index_file(index_file_name);
}

void strcpy_to_char(char* dest, char* src, char stop){
  char* dest_start = dest;
  while (*src != stop && *src != '\0') {
    (*dest) = *(src);
    dest++; src++;
  }
  *(dest++) = '\0';
  dest = dest_start;
}
//extract a part of the src string and put it into the dest string, extracted part does NOT include the start and stop chars, you have to make sure both start and stop exist
//dest string is null-terminated
void strxtrc(char* dest, char* src, char start, char stop){
  char* src_start =src; 
  char* dest_start=dest;
  int is_escape=0;
  
  //first, locate the beginning by searching for start char
  while (*src != start) 
    ++src;

  ++src; //get to next char to not include start char

  while (1) {
    if(*src=='\\'){
      is_escape=1;
      ++src;
      continue;
    }
    if(*src==stop && !is_escape)
      break;
    *dest=*src;
    ++src; ++dest;
    is_escape=0;
  }
  *dest ='\0';
  dest  =dest_start;
  src   =src_start;
}


void set_localizer_path(char* path){
  strcpy(locale_path, path);
}

//returns void because user doesnt need access to the index_file pointer
void open_language_index_file(char* index_file_name){
  char index_path[PATH_MAX];
  strcpy(index_path, locale_path);
  strcat(index_path, index_file_name);
  language_index_file = fopen(index_path, "r");
  if(!language_index_file)
    printf("borked!\n");
}

//returns de_ or en_ ... return should be checked for NULL
//check language_index.yaml for language ids, for custom languages use 'n' with n being a number
char* get_language_id(char language){
  char* line_buffer = (char*) malloc(sizeof(char)*BUFSIZ);
  char c;
  
  while(language != (c=fgetc(language_index_file)))
    ;
  fgetc(language_index_file);
  //printf("%c", c);
  fgets(line_buffer, 3, language_index_file); //3 because 2 for ISO CODE and 1 for \0
  strcat(line_buffer, "_\0");
  return line_buffer;
}

//return the filepointer for one localized file
//name: name of the file (main_menu/settings_menu e.c), language id: which language to use
FILE* open_localised_file(char* name, char language_id){
  char file_path[100];
  append_localised_file_path(file_path, name, language_id);
  return fopen(file_path, "r");
}
//return a \0 terminated string after the seperator in the line with the requested string
char* get_localized_string_from_file(FILE* localized_file ,char* name, char category){
  char name_buffer[BUFSIZ];
  char name_buffer_file[BUFSIZ];
  int offset = 0;
  strcpy(requested_string, name);
  strcat(requested_string, get_category(category));

  while(!feof(localized_file)){
    fgets(name_buffer_file, BUFSIZ, localized_file); //get line
    strcpy_to_char(name_buffer, name_buffer_file, SEPERATOR); //copy to SEPERATOR and comppare the names
    if(strcmp(name_buffer, requested_string) == 0)
      break;
    offset+=strlen(name_buffer_file);
  }

  fseek(localized_file, offset, SEEK_SET);
  fgets(name_buffer, BUFSIZ, localized_file); //name_buffer now contains the whole line
  strxtrc(requested_string, name_buffer, '"', '"');
  return requested_string;  
}

void free_line_buffer(void){
  free(line_buffer);
}

void append_localised_file_path(char* dest ,char* name, char language_id){
  strcpy(dest, locale_path);
  strcat(dest, get_language_id(language_id));
  free_line_buffer();
  strcat(dest,name);
  strcat(dest, ".yml");
}

char* get_category(int category){
  switch (category) {
    case TITLE:
      return "_title";
    case DESCRIPTION:
      return "_description";
    default:
      return "";
  }
}

void close_files(void){
  fclose(language_index_file);
}