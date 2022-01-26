#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {
   Document doc;
   const char *doc_name = "Exercise Description";
   int paragraph_number, line_number;

   init_document(&doc, doc_name);

   /* Adding paragraph */
   paragraph_number = 0;
   add_paragraph_after(&doc, paragraph_number);

   /* Adding lines to paragraph */
   paragraph_number = 1;

   /* First line */
   line_number = 0;
   add_line_after(&doc, paragraph_number, line_number, "is apple. This course will be");
   printf("add: %s\n", doc.paragraphs[0].lines[0]); 

   /* Additional lines */
   add_line_after(&doc, paragraph_number, line_number + 1, "First Paragraph, Second line");
   add_line_after(&doc, paragraph_number, line_number + 2, "First Paragraph, Third line");

  replace_text(&doc, "apple", "apples");
  remove_text(&doc, "line");
  highlight_text(&doc, "Third");
  print_document(&doc);

   return 0;
}
