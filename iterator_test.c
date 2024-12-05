#include <CUnit/Basic.h>

#include "linked_list.h"
#include "iterator.h"
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

void test_create_destroy()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  
  CU_ASSERT_PTR_NOT_NULL(iterator);

  ioopm_linked_list_destroy(list);
  ioopm_iterator_destroy(iterator);
}

void test_has_next()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_append(list, (elem_t) { .int_num = 1 });
  
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  
  CU_ASSERT_TRUE(ioopm_iterator_has_next(iterator));
  
  ioopm_linked_list_destroy(list);
  ioopm_iterator_destroy(iterator);
}

void test_current()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_append(list, (elem_t) { .int_num = 1});
  ioopm_linked_list_append(list, (elem_t) { .int_num = 2});

  ioopm_list_iterator_t *list_iter = ioopm_list_iterator(list);
  elem_t current_element = ioopm_iterator_current(list_iter);

  CU_ASSERT(list->eq_func(current_element, (elem_t) { .int_num = 1}));

  ioopm_iterator_next(list_iter);
  current_element = ioopm_iterator_current(list_iter);

  CU_ASSERT(list->eq_func(current_element, (elem_t) { .int_num = 2}));
}

void test_reset()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_append(list, (elem_t) { .int_num = 1 });
  ioopm_linked_list_append(list, (elem_t) { .int_num = 2 });
  
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  ioopm_iterator_next(iterator);
  ioopm_iterator_reset(iterator);
  
  CU_ASSERT_EQUAL(iterator->current, list->first);

  ioopm_linked_list_destroy(list);
  ioopm_iterator_destroy(iterator);
}

void test_next()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_append(list, (elem_t) { .int_num = 1 });
  ioopm_linked_list_append(list, (elem_t) { .int_num = 2 });
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  
  CU_ASSERT_EQUAL(ioopm_iterator_next(iterator).int_num, 1);
  CU_ASSERT_EQUAL(ioopm_iterator_next(iterator).int_num, 2);
  
  ioopm_linked_list_destroy(list);
  ioopm_iterator_destroy(iterator);
}

void test_remove_first()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_append(list, (elem_t) { .int_num = 1 });
  ioopm_linked_list_append(list, (elem_t) { .int_num = 2 });
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);

  CU_ASSERT_EQUAL(ioopm_iterator_remove(iterator).int_num, 1);
  CU_ASSERT_EQUAL(iterator->list->first->next, iterator->current->next);
  
  ioopm_linked_list_destroy(list);
  ioopm_iterator_destroy(iterator);
}

void test_remove_middle()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_append(list, (elem_t) { .int_num = 1 });
  ioopm_linked_list_append(list, (elem_t) { .int_num = 2 });
  ioopm_linked_list_append(list, (elem_t) { .int_num = 3 });
  
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  ioopm_iterator_next(iterator);
  ioopm_iterator_remove(iterator);
  
  CU_ASSERT_EQUAL(iterator->list->first->next, iterator->current);
  
  ioopm_linked_list_destroy(list);
  ioopm_iterator_destroy(iterator);
}

void test_remove_last()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_append(list, (elem_t) { .int_num = 1 });
  ioopm_linked_list_append(list, (elem_t) { .int_num = 2 });
  
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  ioopm_iterator_next(iterator);
  
  CU_ASSERT_EQUAL(ioopm_iterator_remove(iterator).int_num, 2);
  
  ioopm_linked_list_destroy(list);
  ioopm_iterator_destroy(iterator); 
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
  CU_pSuite my_test_suite = CU_add_suite("Iterator tests", init_suite, clean_suite);
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
    (CU_add_test(my_test_suite, "Test create destroy", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "Test has next", test_has_next) == NULL) ||
    (CU_add_test(my_test_suite, "Test next", test_next) == NULL) ||
    (CU_add_test(my_test_suite, "Test current", test_current) == NULL) ||
    (CU_add_test(my_test_suite, "Test remove first", test_remove_first) == NULL) ||
    (CU_add_test(my_test_suite, "Test remove middle", test_remove_middle) == NULL) ||
    (CU_add_test(my_test_suite, "Test remove last", test_remove_last) == NULL) ||
    (CU_add_test(my_test_suite, "Test reset", test_reset) == NULL) ||
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

