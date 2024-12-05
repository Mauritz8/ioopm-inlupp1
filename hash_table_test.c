#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "iterator.h"
#include "linked_list.h"
#include "common.h"

int init_suite(void)
{
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void)
{
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

int ioopm_string_sum_hash(const elem_t key1)
{
  int result = 0;
  int i = 0;

  while (key1.str[i] != '\0')
  {
    result += key1.str[i];
    i++;
  }
  return result;
}

int ioopm_int_hash_function(elem_t key1)
{
  return key1.int_num;
}

void test_create_destroy()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  CU_ASSERT_PTR_NOT_NULL(ht);
  
  ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  elem_t key1 = {.int_num = 2};
  elem_t value = {.str = "5"};
  char **null_pointer = (char **) NULL;
  elem_t *my_value = ioopm_hash_table_lookup(ht, key1);
  
  CU_ASSERT_EQUAL(my_value, null_pointer);

  ioopm_hash_table_insert(ht, key1, value);
  my_value = ioopm_hash_table_lookup(ht, key1);

  CU_ASSERT_NOT_EQUAL(my_value, null_pointer);
  
  ioopm_hash_table_destroy(ht);
}

void test_insert_key_in_use()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  elem_t key1 = { .int_num = 4 };
  elem_t value = {.str = "5"};
  ioopm_hash_table_insert(ht, key1, value);
  elem_t *value1 = ioopm_hash_table_lookup(ht, key1);

  ioopm_hash_table_insert(ht, key1, value);
  elem_t *value2 = ioopm_hash_table_lookup(ht, key1);

  CU_ASSERT_EQUAL(value1, value2);
  
  ioopm_hash_table_destroy(ht);
}

void test_lookup_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  for (int i = 0; i < No_Buckets + 1; ++i)
    {
      CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, (elem_t) { .int_num = i }));
    }
  
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, (elem_t) { .int_num = -1 }));
  
  ioopm_hash_table_destroy(ht);
}

void test_lookup()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  elem_t key1 = { .int_num = 1};
  elem_t value1 = { .str = "hej" };
  ioopm_hash_table_insert(ht, key1, value1);
  elem_t key2 = { .int_num = 2};
  elem_t value2 = { .str = "hi" };
  ioopm_hash_table_insert(ht, key2, value2);

  elem_t *key1_value = ioopm_hash_table_lookup(ht, key1);
  CU_ASSERT(ioopm_hash_table_keys_equal(ht, *key1_value, value1));

  elem_t *key2_value = ioopm_hash_table_lookup(ht, key2);
  CU_ASSERT(ioopm_hash_table_keys_equal(ht, *key2_value, value2));
  
  ioopm_hash_table_destroy(ht);
}

void test_remove_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  elem_t key1 = { .int_num = 1 };
  elem_t value = {.str = "hej"};
  ioopm_hash_table_insert(ht, key1, value);
  elem_t *lookup_result1 = ioopm_hash_table_lookup(ht, key1);
  
  CU_ASSERT_STRING_EQUAL(lookup_result1->str, "hej");

  ioopm_hash_table_remove(ht, key1);
  elem_t *lookup_result2 = ioopm_hash_table_lookup(ht, key1);
  
  CU_ASSERT_EQUAL(lookup_result2, NULL);
  
  ioopm_hash_table_destroy(ht);
}

void test_get_size_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  
  ioopm_hash_table_destroy(ht);
}

void test_get_size_one_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  ioopm_hash_table_insert(ht, (elem_t) { .int_num = 1235 }, (elem_t) { .str = "test" });
  
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);
  
  ioopm_hash_table_destroy(ht);
}

void test_get_size_multiple_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  size_t size = 5;
  
  for (int i = 0; i < size; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t) { .int_num = i }, (elem_t) { .str = "test" });
  }
  
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), size);
  
  ioopm_hash_table_destroy(ht);
}

void test_is_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  CU_ASSERT_EQUAL(ioopm_hash_table_is_empty(ht), true);
  
  ioopm_hash_table_insert(ht, (elem_t) { .int_num = 1 }, (elem_t) { .str = "test" });
  CU_ASSERT_EQUAL(ioopm_hash_table_is_empty(ht), false);
  
  ioopm_hash_table_destroy(ht);
}

void test_clear()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  ioopm_hash_table_insert(ht, (elem_t) { .int_num = 1 }, (elem_t) { .str = "test" });
  CU_ASSERT_EQUAL(ioopm_hash_table_is_empty(ht), false);
  
  ioopm_hash_table_clear(ht);
  CU_ASSERT_EQUAL(ioopm_hash_table_is_empty(ht), true);
  
  ioopm_hash_table_destroy(ht);
}

int string_array_index_of(char **arr, int len, char *value)
{
  for (int i = 0; i < len; i++)
  {
    if (strcmp(value, arr[i]) == 0)
    {
      return i;
    }
  }

  return -1;
}

void test_get_keys()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  int expected_keys_len = 3;
  ioopm_list_t *expected_keys = ioopm_linked_list_create(ioopm_int_eq_function);
  bool found[] = {false, false, false};
  
  for (int i = 0; i < expected_keys_len; i++)
  {
    elem_t key1 = { .int_num = i + 1 };
    ioopm_hash_table_insert(ht, key1, (elem_t) { .str = "test" });
    ioopm_linked_list_prepend(expected_keys, key1);
  }

  
  ioopm_list_t *actual_keys = ioopm_hash_table_keys(ht);
  ioopm_list_iterator_t *actual_keys_iter = ioopm_list_iterator(actual_keys);

  while (ioopm_iterator_has_next(actual_keys_iter))
  {
    elem_t key1 = ioopm_iterator_next(actual_keys_iter);
    int key_expected_keys_index = ioopm_list_index_of(expected_keys, key1);
    
    if (key_expected_keys_index == -1)
    {
      CU_FAIL("Found a key1 that was never inserted!")
    }
    else
    {
      found[key_expected_keys_index] = true;
    }
  }

  for (int i = 0; i < expected_keys_len; i++)
  {
    CU_ASSERT_TRUE(found[i]);
  }

  ioopm_hash_table_destroy(ht);
  ioopm_linked_list_destroy(expected_keys);
  ioopm_linked_list_destroy(actual_keys);
  ioopm_iterator_destroy(actual_keys_iter);
}

void test_get_values()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  int expected_values_len = 3;
  ioopm_list_t *expected_values = ioopm_linked_list_create(ioopm_str_eq_function);
  char *expected_values_arr[] = {"one", "two", "three"};
  
  for (int i = 0; i < expected_values_len; i++)
  {
    elem_t key1 = { .int_num = i + 1 };
    elem_t value = { .str = expected_values_arr[i] };
    ioopm_hash_table_insert(ht, key1, value);
    ioopm_linked_list_prepend(expected_values, value);
  }

  ioopm_list_t *actual_values = ioopm_hash_table_values(ht);
  ioopm_list_iterator_t *actual_values_iter = ioopm_list_iterator(actual_values);
  bool found[] = {false, false, false};

  while (ioopm_iterator_has_next(actual_values_iter))
  {
    elem_t value = ioopm_iterator_next(actual_values_iter);
    int value_expected_values_index = ioopm_list_index_of(expected_values, value);
    
    if (value_expected_values_index == -1)
    {
      CU_FAIL("Found a value that was never inserted!")
    }
    else
    {
      found[value_expected_values_index] = true;
    }
  }

  for (int i = 0; i < expected_values_len; i++)
  {
    CU_ASSERT_TRUE(found[i]);
  }

  ioopm_linked_list_destroy(expected_values);
  ioopm_linked_list_destroy(actual_values);
  ioopm_iterator_destroy(actual_values_iter);
  ioopm_hash_table_destroy(ht);
}

void test_get_keys_and_values()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  int expected_len = 5;
  ioopm_list_t *expected_keys = ioopm_linked_list_create(ioopm_int_eq_function);
  int expected_keys_array[] = {3, 10, 42, 0, 99};
  char *expected_values[] = {"three", "ten", "fortytwo", "zero", "ninetynine"};

  for (int i = 0; i < expected_len; i++)
  {
    elem_t key1 = { .int_num = expected_keys_array[i] };
    elem_t value = { .str = expected_values[i] };
    ioopm_hash_table_insert(ht, key1, value);
    ioopm_linked_list_append(expected_keys, key1);
  }
  
  ioopm_list_t *actual_keys = ioopm_hash_table_keys(ht);
  ioopm_list_iterator_t *actual_keys_iter = ioopm_list_iterator(actual_keys);
  ioopm_list_t *actual_values = ioopm_hash_table_values(ht);
  
  int i = 0;
  
  while (ioopm_iterator_has_next(actual_keys_iter))
  {
    elem_t key1 = ioopm_iterator_next(actual_keys_iter);
    int actual_index_in_expected = ioopm_list_index_of(expected_keys, key1);
    if (actual_index_in_expected == -1)
    {
      CU_FAIL("Found a key1 that was never inserted!")
    }
    else
    {
      elem_t retrived_element = ioopm_linked_list_get(actual_values, i);
      elem_t expected_element = (elem_t) { .str = expected_values[actual_index_in_expected] };
      CU_ASSERT_TRUE(ioopm_hash_table_values_equal(ht, retrived_element, expected_element));
    }
    
    i++;
  }
  
  ioopm_iterator_destroy(actual_keys_iter);
  ioopm_linked_list_destroy(expected_keys);
  ioopm_linked_list_destroy(actual_keys);
  ioopm_linked_list_destroy(actual_values);
  ioopm_hash_table_destroy(ht);
}

void test_has_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  elem_t key1 = { .int_num = 1 };
  elem_t value = { .str = "test" };
  ioopm_hash_table_insert(ht, key1, value);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key1));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, (elem_t) { .int_num = 2 }));
  
  ioopm_hash_table_destroy(ht);
}

void test_has_value()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, 
                                                   ioopm_str_eq_function, 
                                                   ioopm_int_hash_function);
  elem_t value = { .str = "test" };
  ioopm_hash_table_insert(ht, (elem_t) { .int_num = 4 }, value);
  char *string_dup = strdup(value.str);
  elem_t value_dup = { .str = string_dup };
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, value));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, value_dup));
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, (elem_t) { .str = "not in hash table" }));
  
  free(string_dup);
  ioopm_hash_table_destroy(ht);
}

bool is_key_less_than_x(elem_t key1, elem_t value, void *x)
{
  return key1.int_num < *(int*) x;
}

void test_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, ioopm_str_eq_function, ioopm_int_hash_function);
  elem_t value = { .str = "test" };
  
  for (int i = 0; i < 10; i++)
  {
    elem_t key1 = { .int_num = i };
    ioopm_hash_table_insert(ht, key1, value);
  }
  
  int x = 10;
  CU_ASSERT_TRUE(ioopm_hash_table_all(ht, is_key_less_than_x, &x));
  
  ioopm_hash_table_destroy(ht);
}

void replace_with_new_string(elem_t key1, elem_t *value, void *new_string)
{
  value->str = (char*) new_string;
}

bool value_is_equal_to_other(elem_t key1, elem_t value, void *other)
{
  return strcmp(value.str, (char *) other) == 0;
}

void test_apply_to_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_int_eq_function, ioopm_str_eq_function, ioopm_int_hash_function);
  char *new_string = "abc";
  ioopm_hash_table_insert(ht, (elem_t) { .int_num = 1 }, (elem_t) { .str = "one" });
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, value_is_equal_to_other, new_string));

  ioopm_hash_table_apply_to_all(ht, replace_with_new_string, new_string);
  CU_ASSERT_TRUE(ioopm_hash_table_all(ht, value_is_equal_to_other, new_string));
  ioopm_hash_table_destroy(ht);
}

int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
  {
    return CU_get_error();
  }

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("Hash table tests", init_suite, clean_suite);
  if (my_test_suite == NULL)
  {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(my_test_suite, "Test create_destroy", test_create_destroy) == NULL) || 
    (CU_add_test(my_test_suite, "Test insert once", test_insert_once) == NULL) ||
    (CU_add_test(my_test_suite, "Test insert key1 already in use", test_insert_key_in_use) == NULL) ||
    (CU_add_test(my_test_suite, "Test lookup empty", test_lookup_empty) == NULL) ||
    (CU_add_test(my_test_suite, "Test lookup", test_lookup) == NULL) ||
    (CU_add_test(my_test_suite, "Test remove entry", test_remove_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test get size empty", test_get_size_empty) == NULL) ||
    (CU_add_test(my_test_suite, "Test get size one entry", test_get_size_one_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test get size multiple entries", test_get_size_multiple_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test is empty", test_is_empty) == NULL) ||
    (CU_add_test(my_test_suite, "Test clear", test_clear) == NULL) ||
    (CU_add_test(my_test_suite, "Test get keys", test_get_keys) == NULL) ||
    (CU_add_test(my_test_suite, "Test get values", test_get_values) == NULL) ||
    (CU_add_test(my_test_suite, "Test get keys and values", test_get_keys_and_values) == NULL) ||
    (CU_add_test(my_test_suite, "Test has key1", test_has_key) == NULL) ||
    (CU_add_test(my_test_suite, "Test has value", test_has_value) == NULL) ||
    (CU_add_test(my_test_suite, "Test all", test_all) == NULL) ||
    (CU_add_test(my_test_suite, "Test apply to all", test_apply_to_all) == NULL) ||
    0
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}

