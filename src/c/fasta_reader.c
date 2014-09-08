#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_STRING_SIZE  1024

#define NO_ERR 0             /* Code for no error occured  */
#define ERR_TRAILING_AT 1    /* Can't find '@' at the begin */
#define ERR_NO_ID_DIVIDER 2  /* Can't find the ':' divider */

void header_parse_error_message(int error) {
  switch(error) {
  case 0:
    printf("No error");
    break;
  case 1:
    printf("Can't find trailing '@' (%d)", error);
    break;
  case 2:
    printf("Can't find ':' divider (%d)", error);
    break;
  default:
    printf("Unclasified error (%d)", error);
  }
}

typedef struct {
  int id;
  size_t seuencing_position;
  double  error_probability;
} read_header;

/*
 *  Transforms a raw string containing a valid header into a proper
 *  read_header structure. 
 *
 *  str    the string containing the raw read header
 *  head   an valid pointer to a read_header structure
 */
int string_to_read_header(char* str, read_header * head) {
  // support string and its index
  char* tmp = malloc(DEFAULT_STRING_SIZE);
  size_t j = 0;  

  // first character must be '@'
  if (*str != '@') {
    return ERR_TRAILING_AT;
  }
  str++;
  j = 0;
  tmp[j] = '\0';
  while(*str != ':') {
    if (*str == '\0') {     
      // end of string reached before finding ':'
      return ERR_NO_ID_DIVIDER;
    }
    tmp[j++] = *str;
    str++;
  }
  str++;
  tmp[j] = '\0';
  printf("%s\n",tmp);
  
  // all ok return the no error code
  return NO_ERR;

  free(tmp);
  tmp = NULL;     
}

char* example = "@ecoli_sample:0 pos=510030 NoErr=GACAATTGCCTGCCAGCGGA 0.115553";
char* error_example = "@#@@!#!@";

int main(int argc, char** argv)
{

  read_header header;  
  header_parse_error_message(string_to_read_header(example, &header));
  
  printf("\n");
  return 0;
}
