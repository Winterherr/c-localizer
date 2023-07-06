#include "localizer.h"
#include <stdio.h>

FILE* main_menu;

int main(){
  
  init_localizer("/home/tim/Dokumente/Informatikus/C/localizer/locale/", "language_index.yml");
  main_menu = open_localised_file("main_menu", FINNISH);
  if(!main_menu)
    printf("basiert\n");
  printf("%s\n",get_localized_string_from_file(main_menu,"content_option", TITLE));
  close_files();
  fclose(main_menu);
}