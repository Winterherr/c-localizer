#include "localizer.h"
#include <stdio.h>

FILE* main_menu;

int main(){
  set_localizer_path("/home/tim/Dokumente/Informatikus/C/localizer/locale/");
  open_language_index_file("language_index.yml");
  printf("lang_in geöffnet\n");
  main_menu = open_localised_file("main_menu", '5');
  if(!main_menu)
    printf("basiert\n");
  printf("%s\n",get_localized_string_from_file(main_menu,"content_option", TITLE));
  close_files();
  fclose(main_menu);
}