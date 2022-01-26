/*
Ana Baide
UID: 118441368
Grace: abaide
*/

#include "document.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

/*Checkes if the empty line has space on it to make it valid*/
int not_only_space_checker(char *s) {
  int i;
  for (i = 0; i < strlen(s); i++) {
    /*Return false if one none space found*/
    if (isspace(s[i]) == 0) {
      return FAILURE;
    }
  }
  return SUCCESS;
}

/*Gets the line for the commands*/
int line_getter(char *line, char *output) {
  int size = strlen(line), i, k, bool = 0, start = 0;

  /*Iterate over the command*/
  for (i = 0; line[i] != '\0'; i++) {
    /*Check for the star*/
    if (line[i] == '*') {
      bool = 1;
      start = i + 1;
    }
    if (bool) {
      break;
    }
  }

  /*If bool is true copy the string*/
  if (bool) {
    for (i = start, k = 0; line[i] != '\0'; i++, k++) {
      output[k] = line[i];
    }
    output[k] = '\0';
    return 1;
  }
  return 0;
}
/*This command adds a paragraph to the document. The ”Invalid Command”
message is generated if:
a. PARAGRAPH NUMBER does not represent a number
b. PARAGRAPH NUMBER is a negative value
c. PARAGRAPH NUMBER is missing
d. Additional information is provided after the PARAGRAPH NUMBER
If the command is (valid but) not successfully executed, the message ”add
paragraph after failed” is generated.*/
int add_paragraph_after_cmd(Document *doc, char *command) {
  int paragraph_number;
  char arg1[MAX_PARAGRAPH_LINES + 1], arg2[MAX_PARAGRAPH_LINES + 1];

  /*Scan the user input*/
  if (sscanf(command, "%s%d%s", arg1, &paragraph_number, arg2) != 2) {
    return FAILURE;
  }

  /*Check for the paragraph number*/
  if (paragraph_number < 0) {
    return FAILURE;
  }

  /*Print error if not successful*/
  if (add_paragraph_after(doc, paragraph_number) == FAILURE) {
    printf("add_paragraph_after failed\n");
  }

  return SUCCESS;
}

/*This command adds a line after the line with the specified line number.
The line to add appears after the
* character. The ”Invalid Command” message is generated if:
a. PARAGRAPH NUMBER does not represent a number
3b. PARAGRAPH NUMBER is a negative value or 0
c. PARAGRAPH NUMBER is missing
d. LINE NUMBER does not represent a number
e. LINE NUMBER is a negative value
f. LINE NUMBER is missing
g. * is missing
If the command is not successfully executed, the message ”add line after
failed” is generated.*/
int add_line_after_cmd(Document *doc, char *command) {
  int paragraph_number, line_number;
  char arg1[MAX_STR_SIZE + 1], line[MAX_STR_SIZE + 1];

  /*Scan the user input*/
  if (sscanf(command, "%s%d%d", arg1, &paragraph_number, &line_number) != 3) {
    return FAILURE;
  }
  /*Check for paragraph number or line number sign*/
  if (paragraph_number < 0 || line_number < 0) {
    return FAILURE;
  }

  /*Get line*/
  line_getter(command, line);

  if (line == 0) {
    return FAILURE;
  }

  /*Print error if not successful*/
  if (add_line_after(doc, paragraph_number, line_number, line) == FAILURE) {
    printf("add_line_after failed\n");
  }

  return SUCCESS;
}

/*
This command prints the document information (print document function output).
The ”Invalid Command” message is generated if any data appears after print
document.
*/
int print_document_cmd(Document *doc, char *command) {
  char arg1[MAX_STR_SIZE + 1], arg2[MAX_STR_SIZE + 1];

  /*Scan the user input*/
  if (sscanf(command, "%s%s", arg1, arg2) != 1) {
    return FAILURE;
  }

  /*Print error if not successful*/
  if (print_document(doc) == FAILURE) {
    return FAILURE;
  }

  return SUCCESS;
}

/*
This command appends a line to the specified paragraph. The line to add appears
after the * character.
The ”Invalid Command” message is generated if:
a. PARAGRAPH NUMBER does not represent a number
b. PARAGRAPH NUMBER is a negative value or 0
c. PARAGRAPH NUMBER is missing
d. * is missing
If the command is not successfully executed, the message ”append line failed”
is generated.
*/
int append_line_cmd(Document *doc, char *command) {
  int paragraph_number;
  char arg1[MAX_STR_SIZE + 1], line[MAX_STR_SIZE + 1];

  /*Scan the user input*/
  if (sscanf(command, "%s%d", arg1, &paragraph_number) != 2) {
    return FAILURE;
  }

/*Check if paragraph number valid*/
  if (paragraph_number <= 0) {
    return FAILURE;
  }

/*Get line of the code*/
  line_getter(command, line);

  if (line == 0) {
    return FAILURE;
  }

 /*Print error if not successful*/
  if (append_line(doc, paragraph_number, line) == FAILURE) {
    printf("append_line failed");
  }
  return SUCCESS;
}

/*
This command removes the specified line from the paragraph. The ”Invalid
Command” message is generated if:
a. PARAGRAPH NUMBER does not represent a number
b. PARAGRAPH NUMBER is a negative value or 0
c. PARAGRAPH NUMBER is missing
d. LINE NUMBER does not represent a number
e. LINE NUMBER is a negative value or 0
f. LINE NUMBER is missing
g. Any data appears after the line number
If the command is not successfully executed, the message ”remove line failed”
is generated.
*/
int remove_line_cmd(Document *doc, char *command) {
  int paragraph_number, line_number;
  char arg1[MAX_STR_SIZE + 1], arg2[MAX_STR_SIZE + 1];

  if (sscanf(command, "%s%d%d%s", arg1, &paragraph_number, &line_number,
             arg2) != 3) {
    return FAILURE;
  }

  if (paragraph_number <= 0 || line_number <= 0) {
    return FAILURE;
  }

  if (remove_line(doc, paragraph_number, line_number) == FAILURE) {
    printf("removed_line failed");
  }
  return SUCCESS;
}

/*
This command loads the specified file into the current document. The ”Invalid
Command” message is generated if:
a. FILENAME is missing
b. Any data appears after FILENAME
Assume that if FILENAME is present, it refers to a file that can be opened.
If the command is not successfully executed, the message ”load file failed”
is generated.
*/
int load_file_cmd(Document *doc, char *command) {
  char arg1[MAX_STR_SIZE + 1], arg2[MAX_STR_SIZE + 1], arg3[MAX_STR_SIZE + 1];

  if (sscanf(command, "%s%s%s", arg1, arg2, arg3) != 2) {
    return FAILURE;
  }

  if (load_file(doc, arg2) == FAILURE) {
    printf("load_file failed");
  }
  return SUCCESS;
}

/*Checks if the line has enought " to be copied*/
int check_quotes(char *command, int amount) {
  int i, checker = 0;
  for (i = 0; command[i] != '\0'; i++) {
    if (command[i] == '\"') {
      checker++;
    }
  }

  if (checker == amount) {
    return 1;
  }
  return 0;
}

/*
This command replaces the string ”TARGET” with ”REPLACEMENT”. The ”Invalid
Command” message is generated if:
a. Both ”TARGET” and ”REPLACEMENT” are missing
b. Only ”TARGET” is provided

For this command, assume that if ”TARGET” and ”REPLACEMENT” are present, then
there is no additional data after ”REPLACEMENT”.

If the command is not successfully executed, the message ”replace text failed”
is generated.
*/
int replace_text_cmd(Document *doc, char *command) {
  char arg1[MAX_STR_SIZE + 1], arg2[MAX_STR_SIZE + 1], arg3[MAX_STR_SIZE + 1];
  char target[MAX_STR_SIZE + 1], replacement[MAX_STR_SIZE + 1];
  char *loc1, *loc2, *loc3, *loc4;

  if (sscanf(command, "%s%s%s", arg1, arg2, arg3) != 3) {
    return FAILURE;
  }

  if (!check_quotes(command, 4)) {
    return FAILURE;
  }

  loc1 = strstr(command, "\"");
  loc2 = strstr(loc1 + 1, "\"");
  loc3 = strstr(loc2 + 1, "\"");
  loc4 = strstr(loc3 + 1, "\"");

  strncpy(target, loc1 + 1, loc2 - loc1);
  target[loc2 - (loc1 + 1)] = '\0';

  strncpy(replacement, loc3 + 1, loc4 - loc3);
  replacement[loc4 - (loc3 + 1)] = '\0';

  if (replace_text(doc, target, replacement) == FAILURE) {
    printf("remove_line failed\n");
  }

  return SUCCESS;
}

/*
This command highlights the string ”TARGET”. The ”Invalid Command” message is
generated if ”TARGET” is missing.
For this command, assume that if ”TARGET” is present, there is no additional
data after it. No fail message is associated with this command; either text is
highlighted or not.
*/
int highlight_text_cmd(Document *doc, char *command) {
  char arg1[MAX_STR_SIZE + 1], arg2[MAX_STR_SIZE + 1], arg3[MAX_STR_SIZE + 1];
  char target[MAX_STR_SIZE + 1];
  char *loc1, *loc2;

  if (sscanf(command, "%s%s", arg1, arg2) != 2) {
    return FAILURE;
  }

  loc1 = strstr(command, "\"");
  loc2 = strstr(loc1 + 1, "\"");

  strncpy(target, loc1 + 1, loc2 - loc1);
  target[loc2 - (loc1 + 1)] = '\0';

  highlight_text(doc, target);

  return SUCCESS;
}

/*
This command removes the string ”TARGET”. The ”Invalid Command” message is
generated if ”TARGET” is missing.

For this command, assume that if ”TARGET” is present, there is no additional
data after it. No fail message is associated with this command; either a
deletion takes place or not.
*/
int remove_text_cmd(Document *doc, char *command) {
  char arg1[MAX_STR_SIZE + 1], arg2[MAX_STR_SIZE + 1], arg3[MAX_STR_SIZE + 1];
  char target[MAX_STR_SIZE + 1];
  char *loc1, *loc2;

  if (sscanf(command, "%s%s", arg1, arg2) != 2) {
    return FAILURE;
  }

  loc1 = strstr(command, "\"");
  loc2 = strstr(loc1 + 1, "\"");

  strncpy(target, loc1 + 1, loc2 - loc1);
  target[loc2 - (loc1 + 1)] = '\0';

  remove_text(doc, target);
  return SUCCESS;
}

/*
This command saves the curent document to the specified file. The ”Invalid
Command” message is generated if:
a. FILENAME is missing.
b. Any data appears after the filename.
Assume that if FILENAME is present, a file of that name can be opened. If the
command is not successfully executed, the message ”save document failed”
is generated.
*/
int save_document_cmd(Document *doc, char *command) {
  char arg1[MAX_STR_SIZE + 1], arg2[MAX_STR_SIZE + 1], arg3[MAX_STR_SIZE + 1];

  if (sscanf(command, "%s%s%s", arg1, arg2, arg3) != 2) {
    return FAILURE;
  }

  if (save_document(doc, arg2) == FAILURE) {
    printf("save_document failed\n");
  }

  return SUCCESS;
}

/*
This command resets the curent document. The ”Invalid Command” message is
generated if any data appears after reset document. No fail message is
associated with reset document.
*/
int reset_document_cmd(Document *doc, char *command) {
  char arg1[MAX_STR_SIZE + 1], arg2[MAX_STR_SIZE + 1];

  if (sscanf(command, "%s%s", arg1, arg2) != 1) {
    return FAILURE;
  }

  if (reset_document(doc) == FAILURE) {
    return FAILURE;
  }

  return SUCCESS;
}

/*
Main function that controls the command arguments and functions.
*/
int main(int argc, char *argv[]) {
  Document doc;
  FILE *file;
  char user_line[MAX_STR_SIZE + 1], function_called, line2[MAX_STR_SIZE + 1];

  /*Inicialize document with main*/
  init_document(&doc, "main_document");

  /*If there is only one arg file is stdin*/
  if (argc == 1) {
    /*Get users lines*/
    printf("> ");
    file = stdin;
    fgets(user_line, MAX_STR_SIZE + 1, stdin);

    /*Quit if the user returns quit or exit without extra characters*/
    while (strcmp(user_line, "quit\n") && strcmp(user_line, "exit\n")) {
      /*Scan the user line*/
      sscanf(user_line, "%c%s", &function_called, line2);
      user_line[strlen(user_line) - 1] = '\0';

      /*Check for the string \n or for a comment*/
      if (strcmp(user_line, "\n") != 0 && function_called != '#') {
        /*Compares with each command avalilable and calls the function*/
        if (strstr(user_line, "add_paragraph_after") != NULL) {
          if (add_paragraph_after_cmd(&doc, user_line)) {
            { printf("Invalid Command\n"); }
          }
        }

        if (strstr(user_line, "add_line_after") != NULL) {
          if (add_line_after_cmd(&doc, user_line)) {
            { printf("Invalid Command\n"); }
          }
        }

        if (strstr(user_line, "print_document") != NULL) {
          if (print_document_cmd(&doc, user_line)) {
            { printf("Invalid Command\n"); }
          }
        }

        if (strstr(user_line, "append_line") != NULL) {
          if (append_line_cmd(&doc, user_line)) {
            { printf("Invalid Command\n"); }
          }
        }

        if (strstr(user_line, "remove_line") != NULL) {
          if (remove_line_cmd(&doc, user_line)) {
            { printf("Invalid Command\n"); }
          }
        }

        if (strstr(user_line, "load_file") != NULL) {
          if (load_file_cmd(&doc, user_line)) {
            printf("Invalid Command\n");
          }
        }

        if (strstr(user_line, "replace_text") != NULL) {
          if (replace_text_cmd(&doc, user_line)) {
            { printf("Invalid Command\n"); }
          }
        }

        if (strstr(user_line, "highlight_text") != NULL) {
          if (highlight_text_cmd(&doc, user_line)) {
            { printf("Invalid Command\n"); }
          }
        }

        if (strstr(user_line, "remove_target") != NULL) {
          if (remove_text_cmd(&doc, user_line)) {
            { printf("Invalid Command\n"); }
          }
        }

        if (strstr(user_line, "save_document") != NULL) {
          if (save_document_cmd(&doc, user_line)) {
            { printf("Invalid Command\n"); }
          }
        }

        if (strstr(user_line, "reset_document") != NULL) {
          if (reset_document_cmd(&doc, user_line)) {
            { printf("Invalid Command\n"); }
          }
        }
      }
      /*Continue asking for input*/
      printf("> ");
      fgets(user_line, MAX_STR_SIZE + 1, stdin);
    }
  }
  /*If two arguments, read from file given*/
  else if (argc == 2) {
    /*Open file, and error if it can't be opened*/
    file = fopen(argv[1], "r");
    if (file == NULL) {
      printf("%s cannot be opened.\n", argv[1]);
      exit(EX_OSERR);
    }

    /*Read until you cant get line*/
    while (fgets(user_line, MAX_STR_SIZE + 1, file)) {
      /*Quit if the user returns quit or exit without extra characters*/
      if ((strcmp(user_line, "quit\n") && strcmp(user_line, "exit\n"))) {
        /*Scan the user input for comments*/
        sscanf(user_line, " %c%s", &function_called, line2);
        user_line[strlen(user_line) - 1] = '\0';

        /*Look for string \n or comment*/
        if (strcmp(user_line, "\n") != 0 && function_called != '#') {
          /*Compares with each command avalilable and calls the function*/
          if (strstr(user_line, "add_paragraph_after") != NULL) {
            if (add_paragraph_after_cmd(&doc, user_line)) {
              { printf("Invalid Command\n"); }
            }
          }

          else if (strstr(user_line, "add_line_after") != NULL) {
            if (add_line_after_cmd(&doc, user_line)) {
              { printf("Invalid Command\n"); }
            }
          }

          else if (strstr(user_line, "print_document") != NULL) {
            if (print_document_cmd(&doc, user_line)) {
              { printf("Invalid Command\n"); }
            }
          }

          else if (strstr(user_line, "append_line") != NULL) {
            if (append_line_cmd(&doc, user_line)) {
              { printf("Invalid Command\n"); }
            }
          }

          else if (strstr(user_line, "remove_line") != NULL) {
            if (remove_line_cmd(&doc, user_line)) {
              { printf("Invalid Command\n"); }
            }
          }

          else if (strstr(user_line, "load_file") != NULL) {
            if (load_file_cmd(&doc, user_line)) {
              printf("Invalid Command\n");
            }
          }

          else if (strstr(user_line, "replace_text") != NULL) {
            if (replace_text_cmd(&doc, user_line)) {
              { printf("Invalid Command\n"); }
            }
          }

          else if (strstr(user_line, "highlight_text") != NULL) {
            if (highlight_text_cmd(&doc, user_line)) {
              { printf("Invalid Command\n"); }
            }
          }

          else if (strstr(user_line, "remove_target") != NULL) {
            if (remove_text_cmd(&doc, user_line)) {
              { printf("Invalid Command\n"); }
            }
          }

          else if (strstr(user_line, "save_document") != NULL) {
            if (save_document_cmd(&doc, user_line)) {
              { printf("Invalid Command\n"); }
            }
          }

          else if (strstr(user_line, "reset_document") != NULL) {
            if (reset_document_cmd(&doc, user_line)) {
              { printf("Invalid Command\n"); }
            }
          } else if (strlen(user_line) == 0) {
            /*Do nothing, valid line*/
          } else if (not_only_space_checker(user_line) == SUCCESS) {
            /*Do nothing, valid line*/
          } else {
            printf("Invalid Command\n");
          }
        }
      }
    }
  }
  /*Show user how to properly input information*/
  else {
    printf("Usage: user_interface\n");
    printf("Usage: user_interface <filename>\n");
    exit(EX_USAGE);
  }
  /*Close document*/
  fclose(file);
}
