#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/linkedqueue.h"

queue qu_test;

void setup (void) {
	qu_test = linkedqueue_methods.create();
}

void teardown(void) {
  linkedqueue_methods.free(qu_test);
}

START_TEST (test_queue_create) {
	fail_if(!qu_test, "linkedqueue_methods.create failed.");
  fail_unless(linkedqueue_methods.size(qu_test) == 0, 
							"Size not set correctly on creation");
	fail_unless(linkedqueue_methods.is_empty(qu_test), "Error: queue is not empty");
}
END_TEST

START_TEST (test_queue_enqueue) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	queue qu = NULL;
	
	error = linkedqueue_methods.enqueue(qu, nums[0]);
	fail_unless(error == ERROR_QUEUE_IS_NULL, "Error adding to NULL queue");
	fail_unless(linkedqueue_methods.size(qu) == ERROR_QUEUE_IS_NULL, 
							"Size incorrect after adding to NULL queue");
	
	qu = linkedqueue_methods.create();
	fail_if(!qu, "linkedqueue_methods.create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = linkedqueue_methods.enqueue(qu, nums[i]);
		fail_unless(error == SUCCESS_QUEUE, "Error adding with enqueue");
		fail_unless(linkedqueue_methods.size(qu) == (i+1), "Size incorrect after enqueue");	
		item = (int *) linkedqueue_methods.peek(qu);
		fail_unless(*item == 0, "Error in peek");
		fail_unless(linkedqueue_methods.contains(qu, nums[i]), "Error in linkedqueue_methods.contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	linkedqueue_methods.free(qu);
}
END_TEST

START_TEST (test_queue_dequeue) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	queue qu = NULL;
	
	error = linkedqueue_methods.enqueue(qu, nums[0]);
	fail_unless(error == ERROR_QUEUE_IS_NULL, "Error adding to NULL queue");
	fail_unless(linkedqueue_methods.size(qu) == ERROR_QUEUE_IS_NULL, 
							"Size incorrect after adding to NULL queue");
	
	qu = linkedqueue_methods.create();
	fail_if(!qu, "linkedqueue_methods.create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = linkedqueue_methods.enqueue(qu, nums[i]);
		fail_unless(error == SUCCESS_QUEUE, "Error adding with enqueue");
		fail_unless(linkedqueue_methods.size(qu) == (i+1), "Size incorrect after enqueue");	
		item = (int *) linkedqueue_methods.peek(qu);
		fail_unless(*item == 0, "Error in peek");
		fail_unless(linkedqueue_methods.contains(qu, nums[i]), "Error in linkedqueue_methods.contains");
	}
	
	for (int i = 0; i < 3; i++) {
		item = (int *) linkedqueue_methods.dequeue(qu);
		fail_unless(linkedqueue_methods.size(qu) == (2-i), "Size incorrect after enqueue");
		fail_unless(*item == i, "Error in dequeue");
		fail_if(linkedqueue_methods.contains(qu, nums[i]), "Error in linkedqueue_methods.contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	linkedqueue_methods.free(qu);
}
END_TEST

Suite *queue_suite(void) {
  Suite *s = suite_create("LinkedList Queue");

  /* test constructors and destructors */
  TCase *tc_init = tcase_create("Intialize");
  tcase_add_checked_fixture(tc_init, setup, teardown);
  tcase_add_test(tc_init, test_queue_create);
  suite_add_tcase(s, tc_init);

  /* test enqueue and dequeue */
  TCase *tc_queue = tcase_create("Queue Properties");
  tcase_add_test(tc_queue, test_queue_enqueue);
  tcase_add_test(tc_queue, test_queue_dequeue);
  suite_add_tcase(s, tc_queue);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = queue_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}