#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/stack.h"

stack st_test;

void setup (void) {
	st_test = stack_create();
}

void teardown(void) {
  stack_free(st_test);
}

START_TEST (test_stack_create) {
	fail_if(!st_test, "stack_create failed.");
  fail_unless(stack_size(st_test) == 0, 
							"Size not set correctly on creation");
	fail_unless(stack_is_empty(st_test), "Error: stack is not empty");
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
	
	error = stack_push(st, nums[0]);
	fail_unless(error == ERROR_STACK_IS_NULL, "Error adding to NULL stack");
	fail_unless(stack_size(st) == ERROR_STACK_IS_NULL, 
							"Size incorrect after adding to NULL stack");
	
	st = stack_create();
	fail_if(!st, "stack_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = stack_push(st, nums[i]);
		fail_unless(error == SUCCESS_STACK, "Error adding with push");
		fail_unless(stack_size(st) == (i+1), "Size incorrect after push");	
		item = (int *) stack_peek(st);
		fail_unless(*item == 0, "Error in peek");
		fail_unless(stack_contains(st, nums[i]), "Error in stack_contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	stack_free(st);
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
	
	error = stack_push(st, nums[0]);
	fail_unless(error == ERROR_STACK_IS_NULL, "Error adding to NULL stack");
	fail_unless(stack_size(st) == ERROR_STACK_IS_NULL, 
							"Size incorrect after adding to NULL stack");
	
	st = stack_create();
	fail_if(!st, "stack_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = stack_push(st, nums[i]);
		fail_unless(error == SUCCESS_STACK, "Error adding with enstack");
		fail_unless(stack_size(st) == (i+1), "Size incorrect after push");	
		item = (int *) stack_peek(st);
		fail_unless(*item == 0, "Error in peek");
		fail_unless(stack_contains(st, nums[i]), "Error in stack_contains");
	}
	
	for (int i = 0; i < 3; i++) {
		item = (int *) stack_pop(st);
		fail_unless(*item == i, "Error in pop");
		fail_unless(stack_size(st) == (2-i), "Size incorrect after push");
		fail_if(stack_contains(st, nums[i]), "Error in stack_contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	stack_free(st);
}
END_TEST

Suite *stack_suite(void) {
  Suite *s = suite_create("Stack");

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