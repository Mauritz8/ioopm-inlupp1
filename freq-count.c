#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include "iterator.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"

void free_key(elem_t key, elem_t *value, void *extra)
{
  free(key.str);
}

static int cmpstringp(const void *p1, const void *p2)
{
  return strcmp(*(char *const *)p1, *(char *const *)p2);
}

void sort_keys(char *keys[], size_t no_keys)
{
  qsort(keys, no_keys, sizeof(char *), cmpstringp);
}

void process_word(char *word, ioopm_hash_table_t *ht)
{
  bool has_key = ioopm_hash_table_has_key(ht, (elem_t) {.str = word});
  elem_t *elem = ioopm_hash_table_lookup(ht, (elem_t) {.str = word});
  int freq = has_key
    ? elem->int_num
    : 0;
  
  char *word_dup = strdup(word);
  ioopm_hash_table_insert(ht, (elem_t) {.str = word_dup}, (elem_t) {.int_num = freq + 1});
  
  if (freq != 0)
  {
    free(word_dup);
  }
}

void process_file(char *filename, ioopm_hash_table_t *ht)
{
  FILE *f = fopen(filename, "r");

  while (true)
  {
    char *buf = NULL;
    size_t len = 0;
    getline(&buf, &len, f);

    if (feof(f))
    {
      free(buf);
      break;
    }

    for (char *word = strtok(buf, Delimiters);
        word && *word;
        word = strtok(NULL, Delimiters))
    {
      process_word(word, ht);
    }

    free(buf);
  }

  fclose(f);
}

int string_sum_hash(elem_t e)
{
  char *str = e.str;
  int result = 0;
  do
    {
      result += *str;
    }
  while (*++str != '\0');
  return result;
}

bool string_eq(elem_t e1, elem_t e2)
{
  return (strcmp(e1.str, e2.str) == 0);
}

int main(int argc, char *argv[])
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_eq, NULL, string_sum_hash);

  if (argc > 1)
  {
    for (int i = 1; i < argc; ++i)
    {
      process_file(argv[i], ht);
    }

    ioopm_list_t *keys = ioopm_hash_table_keys(ht);
    ioopm_list_iterator_t *keys_iterator = ioopm_list_iterator(keys);
    int size = ioopm_hash_table_size(ht);
    char **keys_arr = malloc(size * sizeof(char *));
    int i = 0;
    
    while (ioopm_iterator_has_next(keys_iterator))
    {
      elem_t key = ioopm_iterator_next(keys_iterator); 
      keys_arr[i] = strdup(key.str);
      i++;
    }

    ioopm_iterator_destroy(keys_iterator);
    ioopm_linked_list_destroy(keys);
    sort_keys(keys_arr, size);

    for (int i = 0; i < size; ++i)
    {
      int freq = ioopm_hash_table_lookup(ht, (elem_t) {.str = keys_arr[i]})->int_num;
      printf("%s: %d\n", keys_arr[i], freq);
      free(keys_arr[i]);
    }
    free(keys_arr);
  }
  else
  {
    puts("Usage: freq-count file1 ... filen");
  }
  
  ioopm_hash_table_apply_to_all(ht, free_key, NULL);
  ioopm_hash_table_destroy(ht);
}

