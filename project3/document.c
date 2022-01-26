/*
Ana Baide
UID: 118441368
Grace: abaide
*/

#include "document.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*Function prototypes*/
int space_checker(char *s);

/*
Initializes *doc to have 0 paragraphs and sets the document’s name based on
the provided parametervalue. The function returns FAILURE if doc is NULL, name
is NULL, or if the length of the name is notbetween 1 and MAX_STR_SIZE;
otherwise the function returns SUCCESS.
*/
int init_document(Document *doc, const char *name) {
  /*Checks if the strings are null*/
  if (doc == NULL || name == NULL) {
    return FAILURE;
  }

  /*Checks if the string is within the valid parameters*/
  if (1 > strlen(name) || strlen(name) > MAX_STR_SIZE) {
    return FAILURE;
  }

  /*Initialize the document*/
  doc->number_of_paragraphs = 0;
  strcpy(doc->name, name);

  return SUCCESS;
}

/*
Sets the number of paragraphs to 0. The function returns FAILURE if doc is NULL;
otherwise the function returns SUCCESS.
*/
int reset_document(Document *doc) {
  /*Checks if the strings are null*/
  if (doc == NULL) {
    return FAILURE;
  }

  /*Reset document*/
  doc->number_of_paragraphs = 0;
  return SUCCESS;
}

/*
Prints the document’s name, number of paragraphs, followed by the paragraphs.
Exactly one empty line (with zero characters before the newline) is inserted
between every two successive paragraphs. The function returns FAILURE if doc is
NULL; otherwise the function returns SUCCESS.
*/
int print_document(Document *doc) {
  int i, j;
  /*Checks if the strings are null*/
  if (doc == NULL) {
    return FAILURE;
  }

  /*Print name and number of paragraphs*/
  printf("Document name: \"%s\"\n", doc->name);
  printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);

  /*Print content of the paragraphs*/
  for (i = 0; i < doc->number_of_paragraphs; i++) {
    for (j = 0; j < doc->paragraphs[i].number_of_lines; j++) {
      printf("%s\n", doc->paragraphs[i].lines[j]);
    }

    if (doc->number_of_paragraphs > 1 && (i != doc->number_of_paragraphs - 1)) {
      printf("\n");
    }
  }
  return SUCCESS;
}

/*
Adds a paragraph after the specified paragraph number. Paragraph numbers in the
document start at 1. If paragraph number is 0 the paragraph is added at the
beginning of the document. The function returns FAILURE if doc is NULL, the
document already has the maximum number of paragraphs (MAX PARAGRAPHS), or if
paragraph number is negative or higher than the number of paragraphs in
the document; otherwise, the function returns SUCCESS.
*/
int add_paragraph_after(Document *doc, int paragraph_number) {
  int i;

  /*Check if the doc is null or negative paragraph number*/
  if (doc == NULL || paragraph_number < 0) {
    return FAILURE;
  }

  /*Check if the the paragraph number is greater than pargraphs*/
  if (paragraph_number > doc->number_of_paragraphs ||
      doc->number_of_paragraphs == MAX_PARAGRAPHS) {
    return FAILURE;
  }

  /*Adds the paragraph*/
  for (i = doc->number_of_paragraphs; i > paragraph_number; i--) {
    doc->paragraphs[i] = doc->paragraphs[i - 1];
  }

  doc->paragraphs[paragraph_number].number_of_lines = 0;
  doc->number_of_paragraphs++;

  return SUCCESS;
}

/*
Adds a new line after the line with the specified line number. Line numbers
start at 1. If line number is 0, the new line is added at the beginning of the
paragraph. The function returns FAILURE if doc is NULL, paragraph number does
not refer to an existing paragraph, the paragraph already has the maximum number
of lines allowed, line number is negative or higher than the available number
of lines,or new line is NULL; otherwise, the function returns SUCCESS. Assume
that a non-NULL new line is a nul-terminated string of length between 1 and
MAX_STR_SIZE.
*/
int add_line_after(Document *doc, int paragraph_number, int line_number,
                   const char *new_line) {
  int i;

  /*Check if document is null or string is null*/
  if (doc == NULL || new_line == NULL) {
    return FAILURE;
  }

  /*Checks if paragraph exists*/
  if (doc->number_of_paragraphs < paragraph_number || paragraph_number < 0) {
    return FAILURE;
  }

  /*If paragraph is a maximum capacity*/
  if (doc->paragraphs[paragraph_number - 1].number_of_lines ==
      MAX_PARAGRAPH_LINES) {
    return FAILURE;
  }

  /*Check if line number is valid*/
  if (line_number < 0 ||
      line_number > doc->paragraphs[paragraph_number - 1].number_of_lines) {
    return FAILURE;
  }

  for (i = doc->paragraphs[paragraph_number - 1].number_of_lines;
       i > line_number; i--) {
    strcpy(doc->paragraphs[paragraph_number - 1].lines[i],
           doc->paragraphs[paragraph_number - 1].lines[i - 1]);
  }

  strcpy(doc->paragraphs[paragraph_number - 1].lines[line_number], new_line);
  doc->paragraphs[paragraph_number - 1].number_of_lines++;
  return SUCCESS;
}

/*
Returns the number of lines in a paragraph using the number of lines out
parameter. The function returns FAILURE if doc or number of lines is NULL or
if paragraph number does not refer to an existing paragraph; otherwise, the
function returns SUCCESS.
*/
int get_number_lines_paragraph(Document *doc, int paragraph_number,
                               int *number_of_lines) {
  /*Checks if document is null*/
  if (doc == NULL || number_of_lines == NULL) {
    return FAILURE;
  }

  /*Checks if paragraph exists*/
  if (doc->number_of_paragraphs < paragraph_number || paragraph_number < 0) {
    return FAILURE;
  }

  /*Assign value*/
  *number_of_lines = doc->paragraphs[paragraph_number - 1].number_of_lines;

  return SUCCESS;
}

/*
Appends a new line to the specified paragraph. The conditions that make add
line after fail apply to this function as well. The function returns SUCCESS if
the line is appended. Assume that a non-NULL new line is a nul-terminated string
of length between 1 and MAX_STR_SIZE.
*/
int append_line(Document *doc, int paragraph_number, const char *new_line) {
  int line_num;

  /*Check if document is null or string is null*/
  if (doc == NULL || new_line == NULL) {
    return FAILURE;
  }

  /*Checks if paragraph exists*/
  if (doc->number_of_paragraphs < paragraph_number || paragraph_number < 0) {
    return FAILURE;
  }

  /*If paragraph is a maximum capacity*/
  if (doc->paragraphs[paragraph_number - 1].number_of_lines ==
      MAX_PARAGRAPH_LINES) {
    return FAILURE;
  }

  /*Assign line at the end*/
  line_num = doc->paragraphs[paragraph_number - 1].number_of_lines;
  strcpy(doc->paragraphs[paragraph_number - 1].lines[line_num], new_line);
  doc->paragraphs[paragraph_number - 1].number_of_lines++;
  return SUCCESS;
}

/*
Removes the specified line from the paragraph. The function returns FAILURE
if doc is NULL, paragraph number does not refer to an existing paragraph, or
line number does not refer to an existing line; otherwise the function returns
SUCCESS.
*/
int remove_line(Document *doc, int paragraph_number, int line_number) {
  int i;

  /*Check is the doc is null*/
  if (doc == NULL) {
    return FAILURE;
  }

  /*Checks if paragraph exists*/
  if (doc->number_of_paragraphs < paragraph_number || paragraph_number < 0) {
    return FAILURE;
  }

  /*Check if line number is valid*/
  if (line_number < 0 ||
      line_number > doc->paragraphs[paragraph_number - 1].number_of_lines) {
    return FAILURE;
  }

  /*Remove the item*/
  for (i = line_number - 1;
       i < doc->paragraphs[paragraph_number - 1].number_of_lines - 1; i++) {
    strcpy(doc->paragraphs[paragraph_number - 1].lines[i],
           doc->paragraphs[paragraph_number - 1].lines[i + 1]);
  }

  doc->paragraphs[paragraph_number - 1].number_of_lines--;
  return SUCCESS;
}

/*
Adds the first data lines number of rows from the data array to the document,
starting a new paragraph at the beginning of the document. A row with an empty
string starts a new paragraph. So if there are n empty rows in the first data
lines, the function adds n + 1 new paragraphs to the document.

Assume that data lines is non-negative, and if it is positive then each of the
corresponding rows in the data array has a null-terminated string of length at
most MAX_STR_SIZE. The function returns FAILURE if doc is NULL, data is NULL or
data lines is 0. It also returns FAILURE if adding data lines number of rows
would violate the max number of allowed paragraphs or the max number of lines
in a paragraph; in this case, either leave the document unchanged or grow the
document to the maximum allowed. In all other cases, the function returns
SUCCESS.
*/
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1],
                  int data_lines) {
  int i = 0;

  /*Check if they are null*/
  if (doc == NULL || data_lines == 0 || data == NULL) {
    return FAILURE;
  }

  /*Add first paragraph*/
  add_paragraph_after(doc, 0);

  /*Copy the data from the array*/
  for (i = 0; i < data_lines; i++) {
    if (!strcmp(data[data_lines - i - 1], "")) {
      if (doc->number_of_paragraphs != MAX_PARAGRAPHS) {
        add_paragraph_after(doc, 0);
      } else {
        return FAILURE;
      }
    } else {
      if (doc->paragraphs[0].number_of_lines != MAX_PARAGRAPH_LINES) {
        add_line_after(doc, 1, 0, data[data_lines - i - 1]);
      } else {
        return FAILURE;
      }
    }
  }
  return SUCCESS;
}

/*
This function help the replace function by returning through the return
parameter the modified information.
*/
void text_changer(const char *line, const char *target, const char *replacement,
                  char *final, int tar_len, int len_rep) {
  int i, counter = 0;

  /*Iterates over the line and compares with target*/
  for (i = 0; line[i] != '\0'; i++) {
    if (strstr(&line[i], target) == &line[i]) {
      counter++;
      i += tar_len - 1;
    }
  }

  i = 0;

  /*Iterates over line and get the final result*/
  while (*line) {
    if (strstr(line, target) == line) {
      strcpy(&final[i], replacement);
      i += len_rep;
      line += tar_len;
    } else {
      final[i++] = *line++;
    }
  }
  final[i] = '\0';
}

/*
Replaces every appearance of the text target in the document with the text
replacement. Assume that the target is not the empty string. Assume that the
replacement does not generate a line that exceeds the maximum allowed line
length. The function returns FAILURE if doc, target or replacement is NULL;
otherwise the function returns SUCCESS.
*/
int replace_text(Document *doc, const char *target, const char *replacement) {
  int x, y;
  char temp[MAX_STR_SIZE + 1];
  int target_len = 0, replace_len = 0;

  /*Check for null pointers*/
  if (doc == NULL || target == NULL || replacement == NULL) {
    return FAILURE;
  }

  /*Get the string length of target and replacement*/
  target_len = strlen(target);
  replace_len = strlen(replacement);

  /*Loop through document*/
  for (x = 0; x < doc->number_of_paragraphs; x++) {
    for (y = 0; y < doc->paragraphs[x].number_of_lines; y++) {
      text_changer(doc->paragraphs[x].lines[y], target, replacement, temp,
                   target_len, replace_len);
      strcpy(doc->paragraphs[x].lines[y], temp);
      /*line = strstr(doc->paragraphs[x].lines[y], target);
      while (line) {
        strcpy(temp, line);
        strcpy(line, "");
        strcat(strcat(line, replacement) + replace_len, temp + target_len);
        line = strstr(line + target_len, target);
      }*/
    }
  }

  return SUCCESS;
}

/*
Highlights every appearance of the text target in the document, by surrounding
the text with the strings HIGHLIGHT START STR and HIGHLIGHT END STR
(see document.h). Assume that the target is not the empty string. Assume the
highlighting does not cause any line to exceed the maximum allowed line length.
The function returns FAILURE if doc or target is NULL; otherwise the function
returns SUCCESS.
*/
int highlight_text(Document *doc, const char *target) {
  char replacement[MAX_PARAGRAPH_LINES + 1] = "";

  /*Check for null pointers*/
  if (doc == NULL || target == NULL) {
    return FAILURE;
  }

  /*Create the highlight string*/
  strcat(replacement, HIGHLIGHT_START_STR);
  strcat(replacement, target);
  strcat(replacement, HIGHLIGHT_END_STR);

  /*Go over the document*/
  replace_text(doc, target, replacement);
  return SUCCESS;
}

/*
Removes every appearance of the text target in the document. Assume the target
is not the empty string. The function returns FAILURE if doc or target is NULL;
otherwise the function returns SUCCESS.
*/
int remove_text(Document *doc, const char *target) {
  char replacement[MAX_PARAGRAPH_LINES + 1] = "";

  /*Check for null pointers*/
  if (doc == NULL || target == NULL) {
    return FAILURE;
  }

  replace_text(doc, target, replacement);
  return SUCCESS;
}

/*Checks for any spaces in the empty line*/
int space_checker(char *s)
{
	int i;
	for (i = 0; i < strlen(s); i++)
	{
		if (isspace(s[i]) == 0)
		{
			return FAILURE;
		}
	}
	return SUCCESS;
}


/*This function is similar to load document, except that data is loaded from a
file instead of from an array in memory. A new paragraph is started at the
beginning of the document. An empty line indicates the beginning of a new
paragraph. The function returns FAILURE if doc is NULL, filename is NULL, or
opening the file fails. Otherwise the function returns SUCCESS. No error message
is generated if the file cannot be opened.*/
int load_file(Document *doc, const char *filename) {
  FILE *document;
  char line[MAX_STR_SIZE + 1];
  int paragraph_number = 0;

  /*Check for null pointer*/
  if (document == NULL && filename == NULL) {
    return FAILURE;
  }

  /*Open document*/
  document = fopen(filename, "r");

  if (document == NULL) {
    return FAILURE;
  }

  /*Add first paragraph*/
  add_paragraph_after(doc, paragraph_number);
  paragraph_number++;

  /*Get the lines*/
  while (fgets(line, MAX_STR_SIZE + 1, document))
	{
		line[strlen(line) - 1] = '\0';

		if (*line == '\0' || *line == '\n' || space_checker(line) == SUCCESS)
		{
			add_paragraph_after(doc, paragraph_number);
			paragraph_number++;
		}
		else
		{
			append_line(doc, paragraph_number, line);
		}
	}
  fclose(document);
	return SUCCESS;
}

/*
This function prints the document (same format as in project 2) to the specified 
file (overwriting the file). The function returns FAILURE if doc is NULL, 
filename is NULL, or the file cannot be opened. Otherwise the function returns 
SUCCESS. No error message is generated if the file cannot be opened.
*/
int save_document(Document *doc, const char *filename) {
  FILE *file;
	int i, j, num_lines;

  /*Checks for null pointers*/
	if (doc == NULL && filename == NULL)
	{
		return FAILURE;
	}

  /*Open file*/
	file = fopen(filename, "w");
	if (file == NULL)
	{
		return FAILURE;
	}

  /*Iterate over the doc*/
	for (i = 0; i < doc->number_of_paragraphs; i++)
	{
		for (j = 0; j < doc->paragraphs[i].number_of_lines; j++)
		{
			fputs(doc->paragraphs[i].lines[j], file);
			fputs("\n", file);
		}
		if (i + 1 < doc->number_of_paragraphs && 
			doc->paragraphs[i + 1].number_of_lines != 0)
		{
			fputs("\n", file);
		}
	}
	fclose(file);
	return SUCCESS;
}
