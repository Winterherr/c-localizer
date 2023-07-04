#include "localizer.h"
#include <stdio.h>

FILE* main_menu;

int main(){
  set_localizer_path("/home/tim/Dokumente/Informatikus/C/localizer/locale/");
  open_language_index_file("language_index.yml");
  main_menu = open_localised_file("main_menu", GERMAN);
  if(!main_menu)
    printf("basiert\n");
  printf("%s\n",get_localized_string_from_file(main_menu,"content_option", TITLE));
}