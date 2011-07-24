#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/linkedstack.h"

stack st_test;

void setup (void) {
	st_test = linkedstack_methods.create();
}

void teardown(void) {
  linkedstack_methods.free(st_test);
}

START_TEST (test_stack_create) {
	fail_if(!st_test, "linkedstack_methods.create failed.");
  fail_unless(linkedstack_methods.size(st_test) == 0, 
							"Size not set correctly on creation");
	fail_unless(linkedstack_methods.is_empty(st_test), "Error: stack is not empty");
}
END_TEST

START_TEST (test_stack_push) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	stack st = NULL;
	
	error = linkedstack_methods.push(st, nums[0]);
	fail_unless(error == ERROR_STACK_IS_NULL, "Error adding to NULL stack");
	fail_unless(linkedstack_methods.size(st) == ERROR_STACK_IS_NULL, 
							"Size incorrect after adding to NULL stack");
	
	st = linkedstack_methods.create();
	fail_if(!st, "linkedstack_methods.create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = linkedstack_methods.push(st, nums[i]);
		fail_unless(error == SUCCESS_STACK, "Error adding with push");
		fail_unless(linkedstack_methods.size(st) == (i+1), "Size incorrect after push");	
		item = (int *) linkedstack_methods.peek(st);
		fail_unless(*item == 0, "Error in peek");
		fail_unless(linkedstack_methods.contains(st, nums[i]), "Error in linkedstack_methods.contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	linkedstack_methods.free(st);
}
END_TEST

START_TEST (test_stack_pop) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	stack st = NULL;
	
	error = linkedstack_methods.push(st, nums[0]);
	fail_unless(error == ERROR_STACK_IS_NULL, "Error adding to NULL stack");
	fail_unless(linkedstack_methods.size(st) == ERROR_STACK_IS_NULL, 
							"Size incorrect after adding to NULL stack");
	
	st = linkedstack_methods.create();
	fail_if(!st, "linkedstack_methods.create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = linkedstack_methods.push(st, nums[i]);
		fail_unless(error == SUCCESS_STACK, "Error adding with enstack");
		fail_unless(linkedstack_methods.size(st) == (i+1), "Size incorrect after push");	
		item = (int *) linkedstack_methods.peek(st);
		fail_unless(*item == 0, "Error in peek");
		fail_unless(linkedstack_methods.contains(st, nums[i]), "Error in linkedstack_methods.contains");
	}
	
	for (int i = 0; i < 3; i++) {
		item = (int *) linkedstack_methods.pop(st);
		fail_unless(*item == i, "Error in pop");
		fail_unless(linkedstack_methods.size(st) == (2-i), "Size incorrect after push");
		fail_if(linkedstack_methods.contains(st, nums[i]), "Error in linkedstack_methods.contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	linkedstack_methods.free(st);
}
END_TEST

Suite *stack_suite(void) {
  Suite *s = suite_create("LinkedList Stack");

  /* test constructors and destructors */
  TCase *tc_init = tcase_create("Intialize");
  tcase_add_checked_fixture(tc_init, setup, teardown);
  tcase_add_test(tc_init, test_stack_create);
  suite_add_tcase(s, tc_init);

  /* test push and pop */
  TCase *tc_stack = tcase_create("Stack Properties");
  tcase_add_test(tc_stack, test_stack_push);
  tcase_add_test(tc_stack, test_stack_pop);
  suite_add_tcase(s, tc_stack);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = stack_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}