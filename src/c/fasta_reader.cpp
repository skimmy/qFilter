#include <fstream>

#include "fasta_reader.hpp"
#include "read_sorter.hpp"

#include "util/seq.hpp"

bool isBase(const char c) {
  return (c == 'A' || c == 'a' || c == 'C' || c == 'c' ||
	  c == 'G' || c == 'g' || c == 'T' || c == 't' ||
	  c == 'n' || c == 'N');
}

/* 
 * This is the POSIX regex for the (custom) reads header.
 * The header is in the form:
 *     @<name>:<id> pos=<seq_pos> NoErr=<orig_seq> Pe=<error_prob>
 **/
//char* header_re_string = 
string header_re_string = 
  "@([_A-Za-z0-9]+):([_A-Za-z0-9]+) pos=([0-9]+) NoErr=([ACGTN]+) Pe=([0-1].[0-9]+)$";

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


/*
 *  Transforms a raw string containing a valid header into a proper
 *  read_header structure. 
 *
 *  str    the string containing the raw read header
 *  head   an valid pointer to a read_header structure
 */
int string_to_read_header(const char* str, read_header * head) {
  if (*str != '@') {
    return ERR_TRAILING_AT;
  }
  str++;
  char tempBuffer[2048];
  size_t i = 0;
  //  size_t n = strlen(str);

  // NAME - search for the first ':' meaning the end of the name  
  while((*str != ':') && (*str != '\0')) {
    tempBuffer[i] = *str;
    i++;
    str++;
  }
  // end of the string without ':' char
  if (*str == '\0') {
    return ERR_NO_ID_DIVIDER;
  }
  tempBuffer[i] = '\0';
  head->name = (char*)malloc(strlen(tempBuffer));
  strcpy(head->name, tempBuffer);
  str++;

  // ID - first blank ' ' indicates the end of id
  i = 0;
  while((*str != ' ') && (*str != '\0')) {
    tempBuffer[i] = *str;
    i++;
    str++;
  }
  tempBuffer[i] = '\0';
  head->id = (char*) malloc(strlen(tempBuffer));
  strcpy(head->id, tempBuffer);
  // end of the string after id (it is not custom format)
  if (*str == '\0') {
    return ERR_NO_CUSTOM_FORMAT;
  }
  str++;

  // POS= - String is matched
  char posString[] = "pos=";
  if (strstr(str, posString) == NULL) {
    return ERR_NO_CUSTOM_FORMAT;
  }
  str += 4;
  // find the position  
  i = 0;
  while((isdigit(*str)) && (*str != '\0')) {
    tempBuffer[i] = *str;
    str++;
    i++;
  }
  tempBuffer[i] = '\0';
   head->sequencing_position = atoi(tempBuffer);
  if (*str == '\0') {
    return ERR_NO_CUSTOM_FORMAT;
  }

  // NOERR=
  char noErrStr[] = "NoErr=";
  if ((str = strstr(str, noErrStr)) == NULL) {
    return ERR_NO_CUSTOM_FORMAT;
  }
  str += 6;
  i = 0;
  while (isBase(*str) && (*str != '\0')) {
    tempBuffer[i] = *str;
    str++;
    i++;
  }
  tempBuffer[i] = '\0';
  head->original = (char*) malloc(strlen(tempBuffer));
  strcpy(head->original, tempBuffer);
  if (*str == '\0') {
    return ERR_NO_CUSTOM_FORMAT;
  }


  // PE=
  char peStr[] = "Pe=";
  if ((str = strstr(str, peStr)) == NULL) {
    return ERR_NO_CUSTOM_FORMAT;
  }
  str +=3;
  i = 0;
  // first digit
  tempBuffer[i++] = *str;
  str++;
  // dot
  tempBuffer[i++] = *str;
  str++;
  // decimal part
  while(isdigit(*str) && (*str != '\0')) {
    tempBuffer[i] = *str;
    i++;
    str++;
  }
  tempBuffer[i] = '\0';
  head->error_probability = atof(tempBuffer);

  return NO_ERR;
}

int string_to_header_regex(const char* str, read_header* head) {
  int nmatches = 6;
  regmatch_t * matches = (regmatch_t*) malloc(sizeof(regmatch_t) * nmatches);
  regex_t head_re;
  int re_comp_ret = regcomp(&head_re, header_re_string.c_str(), REG_EXTENDED);
  int re_exec_ret = regexec(&head_re, str, nmatches, matches, 0);
  if (re_exec_ret != 0) {
    return REGEX_NO_MATCH;
  }
  int begin = -1, end = -1, match_size = -1;
  char* tmp = (char*) malloc(DEFAULT_STRING_SIZE);
  // matches[0] contains the part of the string that matched
  // ...do something with the whole string if  you need
  // matches[1] contains the name of the read (i.e. dataset)
  begin = (size_t) matches[1].rm_so;
  end = (size_t) matches[1].rm_eo;
  match_size = end - begin;
  head->name = (char*) malloc(match_size + 1);
  strncpy(head->name, (str + begin), match_size);
  head->name[match_size] = '\0';
  if ((_debug >= 2) && __out_enabled) {
    printf("Name: %s\n", head->name);
  }
  // match[2] contains the id of the read within the dataset
  begin = (size_t) matches[2].rm_so;
  end = (size_t) matches[2].rm_eo;
  match_size = end - begin;
  head->id = (char*) malloc(match_size + 1);
  strncpy(head->id, (str + begin), match_size);
  head->id[match_size] = '\0';
  if ((_debug >= 2) && __out_enabled) {
    printf("ID:   %s\n", head->id);
  }

  // match[3] contains the position which the read was sequenced
  begin = (size_t) matches[3].rm_so;
  end = (size_t) matches[3].rm_eo;
  match_size = end - begin;
  strncpy(tmp, (str + begin), match_size);
  tmp[match_size] = '\0';
  head->sequencing_position = atoi(tmp);
  if ((_debug >= 2) && __out_enabled) {
    printf("Pos:  %d\n", (int)head->sequencing_position);
  }

  // match[4] contains the original veriosn of the read (i.e. without errors)
  begin = (size_t) matches[4].rm_so;
  end = (size_t) matches[4].rm_eo;
  match_size = end - begin;
  head->original = (char*) malloc(match_size);
  strncpy(head->original, (str + begin), match_size);
  head->original[match_size] = '\0';  
  if ((_debug >= 2) && __out_enabled) {
    printf("Orig: %s\n", head->original);
  }

  // match[5] contains the error probability of the read
  begin = (size_t) matches[5].rm_so;
  end = (size_t) matches[5].rm_eo;
  match_size = end - begin;
  strncpy(tmp, (str + begin), match_size);
  tmp[match_size] = '\0';
  head->error_probability = atof(tmp);
  if ((_debug >= 2) && __out_enabled) {
    printf("Pe:   %f\n", head->error_probability);
  }
 
    
  // this part is performed only if debug level is at least 2
  // (high verbosity) and also the output is enabled. 
  if ((_debug >= 2) && __out_enabled) {
    printf("------------------\n");
    printf("regcom return value: %d\n", re_comp_ret);
    printf("regexec return value: %d\n", re_exec_ret);
    int i = 0;
    for (i = 1; i < nmatches; ++i) {
      begin = (size_t) matches[i].rm_so;
      end = (size_t) matches[i].rm_eo;
      match_size = end - begin;
      strncpy(tmp, (str + begin), match_size);
      tmp[match_size] = 0;
      printf("Matches %d: (%d,%d) - %s\n", i, begin, end, tmp);
    }
  }
  free(tmp);
  free(matches);
  matches = NULL;

  return NO_ERR;
}

read_header* default_header_init() {
  read_header* tmp = (read_header*) malloc(sizeof(read_header));
  tmp->id = NULL;
  tmp->name = NULL;
  tmp->original = NULL;

  tmp->sequencing_position = -1;
  tmp->error_probability = -1.0;

  return tmp;
}

void header_free(read_header* head) {
  if (head->id != NULL) {
    free(head->id);  
  }
  if (head->name != NULL) {
    free(head->name);
  }
  if (head->original != NULL) {
    free(head->original);

  }
}
