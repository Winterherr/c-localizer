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
void set_language_index_file(void);
void free_line_buffer(void);
void append_localised_file_path(char* dest ,char* name, char language_id);

//return de_ or en_ ... return should be checked for NULL ; check language_index.yaml for language ids
char* get_language_id(char language);
char* get_localized_string(FILE* localized_file ,char* name, char category);
char* get_category(char category);
//name= main_menu / description
FILE* open_localised_file(char* name, char language_id);

#endif