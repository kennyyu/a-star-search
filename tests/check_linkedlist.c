#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/linkedlist.h"

linkedlist list_test;

void setup (void) {
	list_test = list_create();
}

void teardown(void) {
  list_free(list_test);
}

START_TEST (test_list_create) {
	fail_if(!list_test, "list_create failed.");
  fail_unless(list_size(list_test) == 0, 
							"Size not set correctly on creation");
	fail_unless(list_is_empty(list_test), "Error: list is not empty");
}
END_TEST

START_TEST (test_add_first) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	linkedlist list = NULL;
	
	error = list_add_first(list, nums[0]);
	fail_unless(error == ERROR_LIST_IS_NULL, "Error adding to NULL list");
	fail_unless(list_size(list) == ERROR_LIST_IS_NULL, 
							"Size incorrect after adding to NULL list");
	
	list = list_create();
	fail_if(!list, "list_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = list_add_first(list, nums[i]);
		fail_unless(error == SUCCESS_LIST, "Error adding with add_first");
		fail_unless(list_size(list) == (i+1), "Size incorrect after add_first");	
		item = (int *) list_get_last(list);
		fail_unless(*item == 0, "Wrong item in last position");
		item = (int *) list_get_first(list);
		fail_unless(*item == i, "Wrong item in first position");
		fail_unless(list_contains(list, nums[i]), "Error in list_contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
}
END_TEST

START_TEST (test_add_last) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	linkedlist list = NULL;
	
	error = list_add_last(list, nums[0]);
	fail_unless(error == ERROR_LIST_IS_NULL, "Error adding to NULL list");
	fail_unless(list_size(list) == ERROR_LIST_IS_NULL, 
							"Size incorrect after adding to NULL list");
	
	list = list_create();
	fail_if(!list, "list_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = list_add_last(list, nums[i]);
		fail_unless(error == SUCCESS_LIST, "Error adding with add_last");
		fail_unless(list_size(list) == (i+1), "Size incorrect after add_last");
		item = (int *) list_get_first(list);
		fail_unless(*item == 0, "Wrong item in first position");	
		item = (int *) list_get_last(list);
		fail_unless(*item == i, "Wrong item in last position");
		fail_unless(list_contains(list, nums[i]), "Error in list_contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
}
END_TEST

START_TEST (test_add_next) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	linkedlist list = NULL;

	error = list_add_next(list, nums[0], nums[1]);
	fail_unless(error == ERROR_LIST_IS_NULL, "Error adding to NULL list");
	fail_unless(list_size(list) == ERROR_LIST_IS_NULL, 
							"Size incorrect after adding to NULL list");

	list = list_create();
	fail_if(!list, "list_create failed.");
	
	error = list_add_first(list, nums[0]);
	fail_unless(error == SUCCESS_LIST, "Error adding with add_first");
	fail_unless(list_size(list) == 1, "Size incorrect after add_first");
	item = (int *) list_get_first(list);
	fail_unless(*item == 0, "Wrong item in first position");	
	item = (int *) list_get_last(list);
	fail_unless(*item == 0, "Wrong item in last position");
	fail_unless(list_contains(list, nums[0]), "Error in list_contains");
	
	error = list_add_next(list, nums[1], nums[2]);
	fail_unless(error == ERROR_LIST_ITEM_NOT_FOUND, 
					"Error adding after an item not in list");
	
	/* test adding at the tail */
	error = list_add_next(list, nums[0], nums[1]);
	fail_unless(error == SUCCESS_LIST, "Error adding with add_next");
	fail_unless(list_size(list) == 2, "Size incorrect after add_first");
	item = (int *) list_get_first(list);
	fail_unless(*item == 0, "Wrong item in first position");	
	item = (int *) list_get_last(list);
	fail_unless(*item == 1, "Wrong item in last position");
	item = (int *) list_get_next(list, nums[0]);
	fail_unless(*item == 1, "Wrong item after 0 position");
	fail_unless(list_contains(list, nums[0]), "Error in list_contains");
	fail_unless(list_contains(list, nums[1]), "Error in list_contains");
	
	/* test adding in the middle */
	error = list_add_next(list, nums[0], nums[2]);	
	fail_unless(error == SUCCESS_LIST, "Error adding with add_next");
	fail_unless(list_size(list) == 3, "Size incorrect after add_first");
	item = (int *) list_get_first(list);
	fail_unless(*item == 0, "Wrong item in first position");	
	item = (int *) list_get_last(list);
	fail_unless(*item == 1, "Wrong item in last position");
	item = (int *) list_get_next(list, nums[0]);
	fail_unless(*item == 2, "Wrong item after 0 position");
	item = (int *) list_get_next(list, nums[2]);
	fail_unless(*item == 1, "Wrong item after 0 position");
	fail_unless(list_contains(list, nums[0]), "Error in list_contains");
	fail_unless(list_contains(list, nums[1]), "Error in list_contains");
	fail_unless(list_contains(list, nums[2]), "Error in list_contains");
	
	for (int i = 0; i < 3; i++)
		free(nums[i]);
}
END_TEST

START_TEST (test_to_array) {
	int error;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	linkedlist list = list_create();
	fail_if(!list, "list_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = list_add_first(list, nums[i]);
		fail_unless(error == SUCCESS_LIST, "Error adding with add_first");
	}
	
	int **items = (int **) list_to_array(list);
	for (int i = 0; i < 3; i++) {
		fail_unless(*items[i] != *nums[i], "Error in to_array");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	free(items);	
}
END_TEST

Suite *list_suite(void) {
  Suite *s = suite_create("LinkedList");

  /* Core test case */
  TCase *tc_init = tcase_create("Intialize");
  tcase_add_checked_fixture(tc_init, setup, teardown);
  tcase_add_test(tc_init, test_list_create);
  suite_add_tcase(s, tc_init);

	/* test setters */
  TCase *tc_setters = tcase_create("Adders");
  tcase_add_test(tc_setters, test_add_first);
  tcase_add_test(tc_setters, test_add_last);
	tcase_add_test(tc_setters, test_add_next);
	tcase_add_test(tc_setters, test_to_array);
  suite_add_tcase(s, tc_setters);	

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = list_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}