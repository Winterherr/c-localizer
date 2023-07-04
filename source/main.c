#include "localizer.h"
#include <stdio.h>

FILE* main_menu;

int main(){
  set_localizer_path("/home/tim/Dokumente/Informatikus/C/localizer/locale/");
  set_language_index_file();
  main_menu = open_localised_file("main_menu", 1);
  if(!main_menu)
    printf("basiert\n");
  //printf("%s",get_localized_string(main_menu,"create_option", TITLE));
}