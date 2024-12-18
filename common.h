/**
 * @file common.h
 * @author Mauritz Sjödin, Alvin Ljung Hallgren
 * @date 6 Oct 2024
 * @brief Contains object definitions and common functions.
 */

#pragma once

typedef union elem elem_t;
union elem
{
  int int_num;
  unsigned int unsigned_num;
  bool boolean;
  float float_num;
  void *any;
  char *str;
};

typedef bool ioopm_eq_function(elem_t a, elem_t b);

bool ioopm_int_eq_function(elem_t a, elem_t b);
bool ioopm_float_eq_function(elem_t a, elem_t b);
bool ioopm_bool_eq_function(elem_t a, elem_t b);
bool ioopm_str_eq_function(elem_t a, elem_t b);

// an entry in a linked list
typedef struct list_entry list_entry_t;
typedef struct list_entry
{
  elem_t value; // then entry's value
  list_entry_t *next; // a pointer to the next entry in the list
} list_entry_t;


// a linked list
typedef struct list
{
  list_entry_t *first; // pointer to the first element in the list
  list_entry_t *last; // pointer to the last element in the list
  int size; // the size of the list
  ioopm_eq_function *eq_func; // pointer to a function that compares two elements in the list
} ioopm_list_t;

typedef struct ioopm_list_iterator
{
  list_entry_t *current; // the current element
  ioopm_list_t *list; // The underlying list
} ioopm_list_iterator_t;

