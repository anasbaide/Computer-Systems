#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {
   Document doc;
   const char *doc_name = "Exercise Description";
   int paragraph_number, line_number;

   init_document(&doc, doc_name);

   /* Adding first paragraph */
   paragraph_number = 0;
   add_paragraph_after(&doc, paragraph_number);

   line_number = 0;
   paragraph_number = 1;
   add_line_after(&doc, paragraph_number, line_number, "1c");
   add_paragraph_after(&doc, 0);

   add_line_after(&doc, paragraph_number, line_number, "1b");
   add_line_after(&doc, paragraph_number, line_number, "1a");
   add_line_after(&doc, paragraph_number, line_number, "1d");

   print_document(&doc);

   return 0;
}
