`
## Localizer
Localizer is a small library written in C which is supposed to help users with localization in their own projects.
The project is still in it's beginning. Featuring currently only a basic usage of the localization.
## Usage
To use this library, simply drag the header and .c file into your project and include the header file with 
``#include <localizer.h>`` and when compiling make sure to list the localizer.c in the files.
First, lets get over the necessary structure for localisation:
#### The language index file
The language index file is a file which contains all the language codes with their corresponding index. As of now, the language index file **has** to be in the same directory as the `path`. The format of the file is as follows:
```
n:ab
```
`n`is the index of the language, in our example, 0 is assigned to en. `ab` is the [ISO 639-1 Code](https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes) of the language you want to use. To put it in an actual file:
```
#language_index.yml
0:en
1:de
2:fi
3:fr
```
This format **HAS** to be followed, as the programm depends on it when choosing the localized file.
#### The localized files
In the same directory (preferably something named like /locale/) you have your localized .yml files. The naming should be as following:
`ab_name.yml` with `ab` again being the ISO Code of the language.
The structure of your .yml file has to be a key-value list, meaning that each key, which is the name of the localized string, has only one corresponding value, the localized string:
```
key:"value"
```
As of now, it's also possible to add a `title` and `description` string:
```
key_title:"value"
key_description:"value"
```
It is planned to make it possible to configure these "sub categories" in your own program.
As of now, no inline `"`are supported, but may be possible in the future with the `\`. An example would look something like this:
```
#en_main_menu.yml
new_file_title:"New file"
new_file_description:"Create a new file."
load_file_title:"Load file"
load_file_description:"Load an existing file"
settings_option:"Settings"
quit_option_title:"Quit"
quit_option_description:"Quit the programm."
```
It's possible to leave out the substring anytime, as when no specification given the programm will return an empty string when there is no matching substring to return.

#### Programming
To start, you first have to call `ìnit_localizer(char* path, char* index_file_name)`, the functions takes two arguments: the first one is the path where all the localised files are, the second is the so-called language index file.
```
file.c
init_localizer(".../locale/" , "language_index.yml"); //VERY IMPORTANT! ATTACH THE / AT THE END OF THE PATH IF IT ISNT THERE! Will get fixed soon
```
When opening that file with `open_localized_file(char* name, char language_id)`, you only have to write the `name` of the file in `char* name` and the index (as a **char**!!) for the language you want to use in `char language_id`.
Example with our previous files:
```
file.c :
//recommended for your own usage
#define ENGLISH '0'
...
FILE* main_menu_text;
init_localizer(...);
main_menu_text = open_localized_file("main_menu", ENGLISH);
```
This function call will return a file pointer to `en_main_menu.yml` which will be used to access the localized strings. This file pointer will be used with `char* get_localized_string_from_file(FILE* localized_file ,char* name, char category);`, which returns the localized, null-terminated string. It is also planned to implement a `FILE* DEFAULT_FILE` which is used for `char* get_localized_string(char* name, char category)` and retrieves a string from a "default file" which has been set by you before. 
Some functions in `localizer.c` aren't listed in the header file in order to not cause any conflicting problems with other, string-manipulating functions.
So let's see how it looks in the end:
```
#include <stdio.h>
#include "localizer.h"
#define ENGLISH '0'

FILE* main_menu;

int main(){
  init_localizer("...", "language_index.yml");
  main_menu = open_localised_file("main_menu", ENGLISH);
  printf("%s\n", get_localized_string_from_file(main_menu,"new_file", TITLE));
  close_files();
  fclose(main_menu);
  return 0;
}
```

## License
This project is licensed under the GNU General Public License v3.0
## Roadmap
1. Adding documentation
2. Configuring install script
3. Improving code / fixing bugs
4. More features like special character support and usage of escape characters
