#include <CUnit/Basic.h>

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

void test_create_destroy()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  CU_ASSERT_PTR_NOT_NULL(list);

  ioopm_linked_list_destroy(list);
}

void test_insert()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_insert(list, 0, (elem_t) { .int_num = 5 });
  ioopm_linked_list_insert(list, 1, (elem_t) { .int_num = 6 });
  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0).int_num, 5);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1).int_num, 6);
  
  ioopm_linked_list_destroy(list);
}

void test_insert_first()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_insert(list, 0, (elem_t) { .int_num = 5 });
  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0).int_num, 5);
  
  ioopm_linked_list_insert(list, 0, (elem_t) { .int_num = 6 });
  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0).int_num, 6);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1).int_num, 5);
  
  ioopm_linked_list_destroy(list);
}

void test_insert_last()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_insert(list, 0, (elem_t) { .int_num = 5 });
  ioopm_linked_list_insert(list, 1, (elem_t) { .int_num = 6 });
  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0).int_num, 5);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1).int_num, 6);

  ioopm_linked_list_insert(list, 2, (elem_t) { .int_num = 7 });
  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1).int_num, 6);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 2).int_num, 7);
  
  ioopm_linked_list_destroy(list);
}

void test_size()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  
  CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 0);
  
  ioopm_linked_list_insert(list, 0, (elem_t) { .int_num = 5 });
  ioopm_linked_list_insert(list, 1, (elem_t) { .int_num = 10 });
  
  CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 2);
  
  ioopm_linked_list_remove(list, 1);
  
  CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 1);
  
  ioopm_linked_list_destroy(list);
}

void test_index()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);

  CU_ASSERT_EQUAL(ioopm_list_index_of(list, (elem_t) { .int_num = 1 }), -1);

  ioopm_linked_list_append(list, (elem_t) { .int_num = 1 });

  CU_ASSERT_EQUAL(ioopm_list_index_of(list, (elem_t) { .int_num = 1 }), 0);

  ioopm_linked_list_append(list, (elem_t) { .int_num = 2 });

  CU_ASSERT_EQUAL(ioopm_list_index_of(list, (elem_t) { .int_num = 2 }), 1);

  ioopm_linked_list_destroy(list);
}

void test_append()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_append(list, (elem_t) { .int_num = 10 });
  ioopm_linked_list_append(list, (elem_t) { .int_num = 5 });
  ioopm_linked_list_append(list, (elem_t) { .int_num = 15 });
  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0).int_num, 10);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1).int_num, 5);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 2).int_num, 15);
  
  ioopm_linked_list_destroy(list);
}

void test_prepend()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_prepend(list, (elem_t) { .int_num = 10 });
  ioopm_linked_list_prepend(list, (elem_t) { .int_num = 5 });
  ioopm_linked_list_prepend(list, (elem_t) { .int_num = 15 });
  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0).int_num, 15);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1).int_num, 5);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 2).int_num, 10);
  
  ioopm_linked_list_destroy(list);
}

void test_get()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_insert(list, 0, (elem_t) { .int_num = 5 });
  ioopm_linked_list_insert(list, 1, (elem_t) { .int_num = 10 });
  ioopm_linked_list_insert(list, 2, (elem_t) { .int_num = 15 });
  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0).int_num, 5);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1).int_num, 10);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 2).int_num, 15);
  
  ioopm_linked_list_destroy(list);
}

void test_contains()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  int value = 5;
  
  CU_ASSERT_FALSE(ioopm_linked_list_contains(list, (elem_t) { .int_num = value }));
  
  ioopm_linked_list_insert(list, 0, (elem_t) { .int_num = value });
  
  CU_ASSERT_TRUE(ioopm_linked_list_contains(list, (elem_t) { .int_num = value }));
  
  ioopm_linked_list_destroy(list);
}

void test_is_empty()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  
  CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));
  
  ioopm_linked_list_append(list, (elem_t) { .int_num = 5 });
  
  CU_ASSERT_FALSE(ioopm_linked_list_is_empty(list));
  
  ioopm_linked_list_destroy(list);
}

void test_remove()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_insert(list, 0, (elem_t) { .int_num = 5 });
  ioopm_linked_list_insert(list, 1, (elem_t) { .int_num = 7 });
  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0).int_num, 5);
  CU_ASSERT_FALSE(ioopm_linked_list_remove(list, -1));
  CU_ASSERT_FALSE(ioopm_linked_list_remove(list, 2));
  
  CU_ASSERT_TRUE(ioopm_linked_list_remove(list, 0));
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0).int_num, 7);
  
  ioopm_linked_list_destroy(list);
}

void test_remove_last()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  
  CU_ASSERT_FALSE(ioopm_linked_list_remove(list, 1));
  
  ioopm_linked_list_append(list, (elem_t) { .int_num = 5 });
  ioopm_linked_list_append(list, (elem_t) { .int_num = 6 });
  ioopm_linked_list_append(list, (elem_t) { .int_num = 7 });
  
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 2).int_num, 7);
  CU_ASSERT_TRUE(ioopm_linked_list_remove(list, 2));

  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1).int_num, 6);
  CU_ASSERT_TRUE(ioopm_linked_list_remove(list, 1));

  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0).int_num, 5);
  CU_ASSERT_TRUE(ioopm_linked_list_remove(list, 0));
  
  ioopm_linked_list_destroy(list);
}

static bool is_less_than(elem_t value, void *extra)
{
  return value.int_num < *(int *) extra;
}

static bool is_equal_to(elem_t value, void *extra)
{
  return value.int_num == *(int *) extra;
}

void test_all()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  for (int i = 0; i < 10; i++){
    ioopm_linked_list_append(list, (elem_t) { .int_num = i });
  }
  int x = 10;
  
  CU_ASSERT_TRUE(ioopm_linked_list_all(list, is_less_than, &x));
  
  ioopm_linked_list_append(list, (elem_t) { .int_num = 11 });
  
  CU_ASSERT_FALSE(ioopm_linked_list_all(list, is_less_than, &x));
  
  ioopm_linked_list_destroy(list);
}

void test_any()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  ioopm_linked_list_append(list, (elem_t) { .int_num = 0 });
  ioopm_linked_list_append(list, (elem_t) { .int_num = 2 });
  int x = 1;
  
  CU_ASSERT_FALSE(ioopm_linked_list_any(list, is_equal_to, &x));
  
  ioopm_linked_list_append(list, (elem_t) { .int_num = 1 });
  
  CU_ASSERT_TRUE(ioopm_linked_list_any(list, is_equal_to, &x));
  
  ioopm_linked_list_destroy(list);
}

static void multiply_by(elem_t *value, void *extra)
{
  value->int_num *= *(int *) extra;
}

static bool is_divisible_by(elem_t value, void *extra)
{
  return value.int_num % *(int *) extra == 0;
}

void test_apply_to_all()
{
  ioopm_list_t *list = ioopm_linked_list_create(ioopm_int_eq_function);
  int num = 7;
  
  for (int i = 1; i < num; i++)
  {
    ioopm_linked_list_prepend(list, (elem_t) { .int_num = i });
  }
  
  CU_ASSERT_FALSE(ioopm_linked_list_any(list, is_divisible_by, &num));
  
  ioopm_linked_list_apply_to_all(list, multiply_by, &num);
  
  CU_ASSERT_TRUE(ioopm_linked_list_all(list, is_divisible_by, &num));
  
  ioopm_linked_list_destroy(list);
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
  CU_pSuite my_test_suite = CU_add_suite("Linked list tests", init_suite, clean_suite);
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
    (CU_add_test(my_test_suite, "Test insert", test_insert) == NULL) ||
    (CU_add_test(my_test_suite, "Test insert first", test_insert_first) == NULL) ||
    (CU_add_test(my_test_suite, "Test insert last", test_insert_last) == NULL) ||
    (CU_add_test(my_test_suite, "Test size", test_size) == NULL) ||
    (CU_add_test(my_test_suite, "Test index", test_index) == NULL) ||
    (CU_add_test(my_test_suite, "Test append", test_append) == NULL) ||
    (CU_add_test(my_test_suite, "Test prepend", test_prepend) == NULL) ||
    (CU_add_test(my_test_suite, "Test get", test_get) == NULL) ||
    (CU_add_test(my_test_suite, "Test contains", test_contains) == NULL) ||
    (CU_add_test(my_test_suite, "Test is empty", test_is_empty) == NULL) ||
    (CU_add_test(my_test_suite, "Test remove", test_remove) == NULL) ||
    (CU_add_test(my_test_suite, "Test remove last", test_remove_last) == NULL) ||
    (CU_add_test(my_test_suite, "Test all", test_all) == NULL) ||
    (CU_add_test(my_test_suite, "Test any", test_any) == NULL) ||
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
