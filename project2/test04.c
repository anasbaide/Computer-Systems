#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {
   Document doc;
   const char *doc_name = "Loading Document ";
   int data_lines = 8;
   char data[20][MAX_STR_SIZE + 1] = {
        "the first course the need to take",
	"is cmsc131.  This the will be",
	"followed by cmsc132 (the is also based on Java).",
	"",
	"the next the you will take the cmsc216.",
	"This course relies the C.",
	"",
	"Ruby the Ocaml will the covered in cmsc330"
   };

   init_document(&doc, doc_name);
   load_document(&doc, data, data_lines);
   remove_text(&doc, "the");
   print_document(&doc);

   return 0;
}
