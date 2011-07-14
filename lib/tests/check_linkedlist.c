#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/list.h"

list list_test;

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

START_TEST (test_get_first) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	list li = NULL;
	fail_unless(list_get_first(li) == NULL, 
							"Error getting from a NULL list");
	li = list_create();
	fail_if(!li, "list_create failed.");
	fail_unless(list_get_first(li) == NULL,
							"Error getting from an empty list");

	for (int i = 0; i < 3; i++) {
		error = list_add_last(li, nums[i]);
		fail_unless(error == SUCCESS_LIST, "Error adding with add_first");
	}
	
	item = list_get_first(li);
	fail_unless(*item == 0, "Error getting first item");
	
	for (int i = 0; i < 3; i++)
		free(nums[i]);
	list_free(li);
}
END_TEST

START_TEST (test_get_last) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	list li = NULL;
	fail_unless(list_get_last(li) == NULL, 
							"Error getting from a NULL list");
	li = list_create();
	fail_if(!li, "list_create failed.");
	fail_unless(list_get_last(li) == NULL,
							"Error getting from an empty list");

	for (int i = 0; i < 3; i++) {
		error = list_add_last(li, nums[i]);
		fail_unless(error == SUCCESS_LIST, "Error adding with add_last");
	}
	
	item = list_get_last(li);
	fail_unless(*item == 2, "Error getting first item");
	
	for (int i = 0; i < 3; i++)
		free(nums[i]);
	list_free(li);
}
END_TEST

START_TEST (test_get) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	list li = NULL;
	fail_unless(list_get(li, 0) == NULL, 
							"Error getting from a NULL list");
	li = list_create();
	fail_if(!li, "list_create failed.");
	fail_unless(list_get(li, 0) == NULL,
							"Error getting from an empty list");

	for (int i = 0; i < 3; i++) {
		error = list_add_last(li, nums[i]);
		fail_unless(error == SUCCESS_LIST, "Error adding with add_last");
	}
	
	for (int i = 0; i < 3; i++) {
		item = list_get(li, i);
		fail_unless(*item == i, "Error getting i-th item");
 	}

	fail_unless(list_get(li, -1) == NULL, "Error getting with index = -1");	
	fail_unless(list_get(li, 4) == NULL, "Error getting with index = 4");
	
	for (int i = 0; i < 3; i++)
		free(nums[i]);
	list_free(li);
}
END_TEST

START_TEST (test_to_array) {
	int error;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	list li = list_create();
	fail_if(!li, "list_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = list_add_first(li, nums[i]);
		fail_unless(error == SUCCESS_LIST, "Error adding with add_first");
	}
	
	int **items = (int **) list_to_array(li);
	for (int i = 0; i < 3; i++) {
		fail_unless(*items[i] != *nums[i], "Error in to_array");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	free(items);	
	list_free(li);
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
	
	list li = NULL;
	
	error = list_add_first(li, nums[0]);
	fail_unless(error == ERROR_LIST_IS_NULL, "Error adding to NULL list");
	fail_unless(list_size(li) == ERROR_LIST_IS_NULL, 
							"Size incorrect after adding to NULL list");
	
	li = list_create();
	fail_if(!li, "list_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = list_add_first(li, nums[i]);
		fail_unless(error == SUCCESS_LIST, "Error adding with add_first");
		fail_unless(list_size(li) == (i+1), "Size incorrect after add_first");	
		item = (int *) list_get_last(li);
		fail_unless(*item == 0, "Wrong item in last position");
		item = (int *) list_get_first(li);
		fail_unless(*item == i, "Wrong item in first position");
		fail_unless(list_contains(li, nums[i]), "Error in list_contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	list_free(li);
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
	
	list li = NULL;
	
	error = list_add_last(li, nums[0]);
	fail_unless(error == ERROR_LIST_IS_NULL, "Error adding to NULL list");
	fail_unless(list_size(li) == ERROR_LIST_IS_NULL, 
							"Size incorrect after adding to NULL list");
	
	li = list_create();
	fail_if(!li, "list_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = list_add_last(li, nums[i]);
		fail_unless(error == SUCCESS_LIST, "Error adding with add_last");
		fail_unless(list_size(li) == (i+1), "Size incorrect after add_last");
		item = (int *) list_get_first(li);
		fail_unless(*item == 0, "Wrong item in first position");	
		item = (int *) list_get_last(li);
		fail_unless(*item == i, "Wrong item in last position");
		fail_unless(list_contains(li, nums[i]), "Error in list_contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	list_free(li);
}
END_TEST

START_TEST (test_set) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	list li = NULL;

	error = list_set(li, 0, nums[0]);
	fail_unless(error == ERROR_LIST_IS_NULL, "Error adding to NULL list");
	fail_unless(list_size(li) == ERROR_LIST_IS_NULL, 
							"Size incorrect after adding to NULL list");

	li = list_create();
	fail_if(!li, "list_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = list_add_last(li, nums[i]);
		fail_unless(error == SUCCESS_LIST, "Error adding with add_last");
		fail_unless(list_size(li) == (i+1), "Size incorrect after add_last");
		item = (int *) list_get_first(li);
		fail_unless(*item == 0, "Wrong item in first position");	
		item = (int *) list_get_last(li);
		fail_unless(*item == i, "Wrong item in last position");
		fail_unless(list_contains(li, nums[i]), "Error in list_contains");
	}
	
	error = list_set(li, 3, nums[0]);
	fail_unless(error == ERROR_LIST_OUT_OF_BOUNDS);
	error = list_set(li, -1, nums[0]);
	fail_unless(error == ERROR_LIST_OUT_OF_BOUNDS);
	
	for (int i = 0; i < 3; i++) {
		error = list_set(li, i, nums[0]);
		fail_unless(error == SUCCESS_LIST, "Error setting ith position");
		item = (int *) list_get(li, i);
		fail_unless(*item == 0, "Wrong item after setting");
	}
	
	for (int i = 0; i < 3; i++)
		free(nums[i]);
	list_free(li);	
}
END_TEST

START_TEST (test_remove_first) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	list li = NULL;
	fail_unless(list_remove_first(li) == NULL, 
							"Error removing from a NULL list");
	li = list_create();
	fail_if(!li, "list_create failed.");
	fail_unless(list_remove_first(li) == NULL, 
							"Error removing from an empty list");			
	
	for (int i = 0; i < 3; i++) {
		error = list_add_first(li, nums[i]);
		fail_unless(error == SUCCESS_LIST, "Error adding with add_first");
	}
	
	for (int i = 2; i >= 0; i--) {
		item = list_remove_first(li);
		fail_unless(*item == i, "Error removing first item");
		fail_unless(list_size(li) == i, "Error in size after removing item");
	}
	
	for (int i = 0; i < 3; i++)
		free(nums[i]);
	list_free(li);
}
END_TEST

START_TEST (test_remove_last) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	list li = NULL;
	fail_unless(list_remove_last(li) == NULL, 
							"Error removing from a NULL list");
	li = list_create();
	fail_if(!li, "list_create failed.");
	fail_unless(list_remove_last(li) == NULL, 
							"Error removing from an empty list");			
	
	for (int i = 0; i < 3; i++) {
		error = list_add_first(li, nums[i]);
		fail_unless(error == SUCCESS_LIST, "Error adding with add_first");
	}
	
	for (int i = 0; i < 3; i++) {
		item = list_remove_last(li);
		fail_unless(*item == i, "Error removing first item");
		fail_unless(list_size(li) == (2 - i), 
								"Error in size after removing item");
	}
	
	for (int i = 0; i < 3; i++)
		free(nums[i]);
	list_free(li);	
}
END_TEST

START_TEST (test_remove) {
	int error;
	int *nums[4];
	for (int i = 0; i < 4; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	list li = NULL;
	fail_unless(list_remove(li, nums[0]) == ERROR_LIST_IS_NULL, 
							"Error removing from a NULL list");
	li = list_create();
	fail_if(!li, "list_create failed.");
	fail_unless(list_remove(li, nums[0]) == ERROR_LIST_IS_EMPTY, 
							"Error removing from an empty list");
	fail_unless(list_remove(li, NULL) == ERROR_LIST_ITEM_IS_NULL, 
							"Error removing a NULL item");

	for (int i = 0; i < 4; i++) {
		error = list_add_last(li, nums[i]);
		fail_unless(error == SUCCESS_LIST, "Error adding with add_first");
	}

	error = list_remove(li, nums[1]);
	fail_unless(error == SUCCESS_LIST, "Error removing middle item");
	fail_unless(list_size(li) == 3, "Error in size after removing item");
	error = list_remove(li, nums[0]);
	fail_unless(error == SUCCESS_LIST, "Error removing first item");
	fail_unless(list_size(li) == 2, "Error in size after removing item");
	error = list_remove(li, nums[3]);
	fail_unless(error == SUCCESS_LIST, "Error removing last item");
	fail_unless(list_size(li) == 1, "Error in size after removing item");

	for (int i = 0; i < 4; i++)
		free(nums[i]);
	list_free(li);
}
END_TEST

Suite *list_suite(void) {
  Suite *s = suite_create("LinkedList");

  /* test constructors and destructors */
  TCase *tc_init = tcase_create("Intialize");
  tcase_add_checked_fixture(tc_init, setup, teardown);
  tcase_add_test(tc_init, test_list_create);
  suite_add_tcase(s, tc_init);

	/* test getters */
  TCase *tc_setters = tcase_create("Getters");
  tcase_add_test(tc_setters, test_get_first);
  tcase_add_test(tc_setters, test_get_last);
	tcase_add_test(tc_setters, test_get);
	tcase_add_test(tc_setters, test_to_array);
  suite_add_tcase(s, tc_setters);

	/* test adders */
  TCase *tc_adders = tcase_create("Adders");
  tcase_add_test(tc_adders, test_add_first);
  tcase_add_test(tc_adders, test_add_last);
	tcase_add_test(tc_adders, test_set);
  suite_add_tcase(s, tc_adders);	

	/* test removers */
  TCase *tc_removers = tcase_create("Removers");
  tcase_add_test(tc_removers, test_remove_first);
  tcase_add_test(tc_removers, test_remove_last);
	tcase_add_test(tc_removers, test_remove);
  suite_add_tcase(s, tc_removers);

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