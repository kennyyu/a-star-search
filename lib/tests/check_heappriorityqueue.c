#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/priorityqueue.h"

pqueue pq_test;

int int_compare(void *num1, void *num2) {
	return *((int *) num1) - *((int *) num2);
}

void setup (void) {
	pq_test = pqueue_create(&int_compare);
}

void teardown(void) {
  pqueue_free(pq_test);
}

START_TEST (test_pqueue_create) {
	fail_if(!pq_test, "pqueue_create failed.");
  fail_unless(pqueue_size(pq_test) == 0, 
							"Size not set correctly on creation");
	fail_unless(pqueue_is_empty(pq_test), "Error: pqueue is not empty");
}
END_TEST

START_TEST (test_pqueue_enpqueue) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	pqueue pq = NULL;
	
	error = pqueue_enpqueue(pq, nums[0]);
	fail_unless(error == ERROR_PQUEUE_IS_NULL, "Error adding to NULL pqueue");
	fail_unless(pqueue_size(pq) == ERROR_PQUEUE_IS_NULL, 
							"Size incorrect after adding to NULL pqueue");
	
	pq = pqueue_create(&int_compare);
	fail_if(!pq, "pqueue_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = pqueue_enpqueue(pq, nums[i]);
		fail_unless(error == SUCCESS_PQUEUE, "Error adding with enpqueue");
		fail_unless(pqueue_size(pq) == (i+1), "Size incorrect after enpqueue");	
		item = (int *) pqueue_peek(pq);
		fail_unless(*item == 0, "Error in peek");
		fail_unless(pqueue_contains(pq, nums[i]), "Error in pqueue_contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	pqueue_free(pq);
}
END_TEST

START_TEST (test_pqueue_depqueue) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	pqueue pq = NULL;
	
	error = pqueue_enpqueue(pq, nums[0]);
	fail_unless(error == ERROR_PQUEUE_IS_NULL, "Error adding to NULL pqueue");
	fail_unless(pqueue_size(pq) == ERROR_PQUEUE_IS_NULL, 
							"Size incorrect after adding to NULL pqueue");
	
	pq = pqueue_create(&int_compare);
	fail_if(!pq, "pqueue_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = pqueue_enpqueue(pq, nums[i]);
		fail_unless(error == SUCCESS_PQUEUE, "Error adding with enpqueue");
		fail_unless(pqueue_size(pq) == (i+1), "Size incorrect after enpqueue");	
		item = (int *) pqueue_peek(pq);
		fail_unless(*item == 0, "Error in peek");
		fail_unless(pqueue_contains(pq, nums[i]), "Error in pqueue_contains");
	}
	
	for (int i = 0; i < 3; i++) {
		item = (int *) pqueue_depqueue(pq);
		fail_unless(pqueue_size(pq) == (2-i), "Size incorrect after enpqueue");
		fail_unless(*item == i, "Error in depqueue");
		fail_if(pqueue_contains(pq, nums[i]), "Error in pqueue_contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	pqueue_free(pq);
}
END_TEST

Suite *pqueue_suite(void) {
  Suite *s = suite_create("HeapArray PriorityQueue");

  /* test constructors and destructors */
  TCase *tc_init = tcase_create("Intialize");
  tcase_add_checked_fixture(tc_init, setup, teardown);
  tcase_add_test(tc_init, test_pqueue_create);
  suite_add_tcase(s, tc_init);

  /* test enpqueue and depqueue */
  TCase *tc_pqueue = tcase_create("Queue Properties");
  tcase_add_test(tc_pqueue, test_pqueue_enpqueue);
  tcase_add_test(tc_pqueue, test_pqueue_depqueue);
  suite_add_tcase(s, tc_pqueue);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = pqueue_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}