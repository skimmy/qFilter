#ifndef _FASTA_READER_H_
#define _FASTA_READER_H_

#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util/debug.h"

#define DEFAULT_STRING_SIZE  1024

#define NO_ERR 0             /* Code for no error occured  */
#define ERR_TRAILING_AT 1    /* Can't find '@' at the begin */
#define ERR_NO_ID_DIVIDER 2  /* Can't find the ':' divider */

#define REGEX_NO_MATCH 100   /* Regex test not passed */


/*
 * This data structure defines the custom header line of fasta file. This custom
 * line is not standard in any way and it was created specifically for the
 * qFilter software, feel free to use it if you need it, but keep in mind that
 * many available software may corrupt the header.
 */
typedef struct {
  char*  id;
  size_t sequencing_position;
  double error_probability;

  /*
   * These are optional and if not used should be set to NULL to indicate that
   * corresponsing memory zone needs not to be freed.
   */
  char* name;
  char* original;
  
} read_header;


/*
 *  Followinf functions are used to transform a raw string containing a valid
 *  header into a proper read_header structure. The difference between the two
 *  functions is on the way used to parse, in one case simple string scnning is
 *  used, in the other posix regular expression library is used.
 *
 *  str    the string containing the raw read header
 *  head   an valid pointer to a read_header structure
 */
int string_to_read_header(char* str, read_header * head); // NOT DONE YET!!!!
int string_to_header_regex(char* str, read_header* head);

#endif
