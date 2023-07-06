#ifndef LOCALIZER_H_
#define LOCALIZER_H_

#include <linux/limits.h>
#include <stdio.h>

#define TITLE '0'
#define DESCRIPTION '1'

#define ENGLISH '0'
#define GERMAN '1'
#define FINNISH '2'


//extern char language_index_path[PATH_MAX];

//Should be ../locale/
void set_localizer_path(char* path);
void open_language_index_file(char* index_file_name);
void free_line_buffer(void);
void append_localised_file_path(char* dest ,char* name, char language_id);
void strcpy_to_char(char* dest, char* src, char stop);
void close_files(void);
//return de_ or en_ ... return should be checked for NULL ; check language_index.yaml for language ids
char* get_language_id(char language);
//get a localized string from any file
char* get_localized_string_from_file(FILE* localized_file ,char* name, char category);
// get a localized string from a the SET_FILE
char* get_localized_string(char* name, char category);
char* get_category(char category);
//name= main_menu / description
FILE* open_localised_file(char* name, char language_id);

#endif