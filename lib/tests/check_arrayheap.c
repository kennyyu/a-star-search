#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/heap.h"

heap heap_test;

int int_compare(void *num1, void *num2) {
	return *((int *) num1) - *((int *) num2);
}

void setup (void) {
	heap_test = heap_create(&int_compare);
}

void teardown(void) {
  heap_free(heap_test);
}

START_TEST (test_heap_create) {
	fail_if(!heap_test, "heap_create failed.");
  fail_unless(heap_size(heap_test) == 0, 
							"Size not set correctly on creation");
	fail_unless(heap_is_empty(heap_test), "Error: list is not empty");
}
END_TEST

START_TEST (test_heap_add1) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	heap hp = NULL;
	
	error = heap_add(hp, nums[0]);
	fail_unless(error == ERROR_HEAP_IS_NULL, "Error adding to NULL heap");
	fail_unless(heap_size(hp) == ERROR_HEAP_IS_NULL, 
							"Size incorrect after adding to NULL heap");
	
	hp = heap_create(&int_compare);
	fail_if(!hp, "heap_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = heap_add(hp, nums[i]);
		fail_unless(error == SUCCESS_HEAP, "Error adding to heap");
		fail_unless(heap_size(hp) == (i+1), "Size incorrect after add");	
		item = (int *) heap_peek(hp);
		fail_unless(*item == 0, "Error in peek");
		fail_unless(heap_contains(hp, nums[i]), "Error in heap_contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	heap_free(hp);
}
END_TEST

START_TEST (test_heap_add2) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = 2 - i;
	}
	
	heap hp = NULL;
	
	error = heap_add(hp, nums[0]);
	fail_unless(error == ERROR_HEAP_IS_NULL, "Error adding to NULL heap");
	fail_unless(heap_size(hp) == ERROR_HEAP_IS_NULL, 
							"Size incorrect after adding to NULL heap");
	
	hp = heap_create(&int_compare);
	fail_if(!hp, "heap_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = heap_add(hp, nums[i]);
		fail_unless(error == SUCCESS_HEAP, "Error adding to heap");
		fail_unless(heap_size(hp) == (i+1), "Size incorrect after add");	
		item = (int *) heap_peek(hp);
		fail_unless(*item == (2 - i), "Error in peek");
		fail_unless(heap_contains(hp, nums[i]), "Error in heap_contains");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	heap_free(hp);
}
END_TEST

START_TEST (test_heap_add3) {
	int error;
	int *item;
	int *nums[8];
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = 7 - i;
	}
	
	heap hp = NULL;
	
	error = heap_add(hp, nums[0]);
	fail_unless(error == ERROR_HEAP_IS_NULL, "Error adding to NULL heap");
	fail_unless(heap_size(hp) == ERROR_HEAP_IS_NULL, 
							"Size incorrect after adding to NULL heap");
	
	hp = heap_create(&int_compare);
	fail_if(!hp, "heap_create failed.");
	
	for (int i = 0; i < 8; i++) {
		error = heap_add(hp, nums[i]);
		fail_unless(error == SUCCESS_HEAP, "Error adding to heap");
		fail_unless(heap_size(hp) == (i+1), "Size incorrect after add");	
		item = (int *) heap_peek(hp);
		fail_unless(*item == (7 - i), "Error in peek");
		fail_unless(heap_contains(hp, nums[i]), "Error in heap_contains");
	}

	for (int i = 0; i < 8; i++)
		free(nums[i]);
	heap_free(hp);
}
END_TEST

START_TEST (test_heap_to_array) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	heap hp = NULL;
	
	error = heap_add(hp, nums[0]);
	fail_unless(error == ERROR_HEAP_IS_NULL, "Error adding to NULL heap");
	fail_unless(heap_size(hp) == ERROR_HEAP_IS_NULL, 
							"Size incorrect after adding to NULL heap");
	
	hp = heap_create(&int_compare);
	fail_if(!hp, "heap_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = heap_add(hp, nums[i]);
		fail_unless(error == SUCCESS_HEAP, "Error adding to heap");
		fail_unless(heap_size(hp) == (i+1), "Size incorrect after add");	
		item = (int *) heap_peek(hp);
		fail_unless(*item == 0, "Error in peek");
		fail_unless(heap_contains(hp, nums[i]), "Error in heap_contains");
	}
	
	int **items = (int **) heap_to_array(hp);
	for (int i = 0; i < 3; i++) {
		int found = 0;
		for (int j = 0; j < 3; j++) {
			if (i == *items[j])
				found = 1;
		}
		fail_unless(found == 1, "Error in to_array");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	heap_free(hp);
}
END_TEST

START_TEST (test_heap_remove1) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	heap hp = NULL;
	
	error = heap_add(hp, nums[0]);
	fail_unless(error == ERROR_HEAP_IS_NULL, "Error adding to NULL heap");
	fail_unless(heap_size(hp) == ERROR_HEAP_IS_NULL, 
							"Size incorrect after adding to NULL heap");
	
	hp = heap_create(&int_compare);
	fail_if(!hp, "heap_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = heap_add(hp, nums[i]);
		fail_unless(error == SUCCESS_HEAP, "Error adding to heap");
		fail_unless(heap_size(hp) == (i+1), "Size incorrect after add");	
		item = (int *) heap_peek(hp);
		fail_unless(*item == 0, "Error in peek");
		fail_unless(heap_contains(hp, nums[i]), "Error in heap_contains");
	}
	
	for (int i = 0; i < 3; i++) {
		item = (int *) heap_remove(hp);
		fail_unless(*item == i, "Error in remove");
		fail_unless(heap_size(hp) == 2 - i, "Size incorrect after remove");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	heap_free(hp);
}
END_TEST

START_TEST (test_heap_remove2) {
	int error;
	int *item;
	int *nums[3];
	for (int i = 0; i < 3; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = 2 - i;
	}
	
	heap hp = NULL;
	
	error = heap_add(hp, nums[0]);
	fail_unless(error == ERROR_HEAP_IS_NULL, "Error adding to NULL heap");
	fail_unless(heap_size(hp) == ERROR_HEAP_IS_NULL, 
							"Size incorrect after adding to NULL heap");
	
	hp = heap_create(&int_compare);
	fail_if(!hp, "heap_create failed.");
	
	for (int i = 0; i < 3; i++) {
		error = heap_add(hp, nums[i]);
		fail_unless(error == SUCCESS_HEAP, "Error adding to heap");
		fail_unless(heap_size(hp) == (i+1), "Size incorrect after add");	
		item = (int *) heap_peek(hp);
		fail_unless(*item == (2 - i), "Error in peek");
		fail_unless(heap_contains(hp, nums[i]), "Error in heap_contains");
	}
	
	for (int i = 0; i < 3; i++) {
		item = (int *) heap_remove(hp);
		fail_unless(*item == i, "Error in remove");
		fail_unless(heap_size(hp) == 2 - i, "Size incorrect after remove");
	}

	for (int i = 0; i < 3; i++)
		free(nums[i]);
	heap_free(hp);
}
END_TEST

START_TEST (test_heap_remove3) {
	int error;
	int *item;
	int *nums[8];
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = 7 - i;
	}
	
	heap hp = NULL;
	
	error = heap_add(hp, nums[0]);
	fail_unless(error == ERROR_HEAP_IS_NULL, "Error adding to NULL heap");
	fail_unless(heap_size(hp) == ERROR_HEAP_IS_NULL, 
							"Size incorrect after adding to NULL heap");
	
	hp = heap_create(&int_compare);
	fail_if(!hp, "heap_create failed.");
	
	for (int i = 0; i < 8; i++) {
		error = heap_add(hp, nums[i]);
		fail_unless(error == SUCCESS_HEAP, "Error adding to heap");
		fail_unless(heap_size(hp) == (i+1), "Size incorrect after add");	
		item = (int *) heap_peek(hp);
		fail_unless(*item == (7 - i), "Error in peek");
		fail_unless(heap_contains(hp, nums[i]), "Error in heap_contains");
	}
	
	for (int i = 0; i < 8; i++) {
		item = (int *) heap_remove(hp);
		fail_unless(*item == i, "Error in remove");
		fail_unless(heap_size(hp) == 7 - i, "Size incorrect after remove");
	}

	for (int i = 0; i < 8; i++)
		free(nums[i]);
	heap_free(hp);
}
END_TEST

START_TEST (test_heap_merge) {
	int error;
	int *item;
	int *nums[8];
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = 7 - i;
	}
	
	heap hp = NULL;
	
	error = heap_add(hp, nums[0]);
	fail_unless(error == ERROR_HEAP_IS_NULL, "Error adding to NULL heap");
	fail_unless(heap_size(hp) == ERROR_HEAP_IS_NULL, 
							"Size incorrect after adding to NULL heap");
	
	hp = heap_create(&int_compare);
	fail_if(!hp, "heap_create failed.");
	
	for (int i = 0; i < 8; i++) {
		error = heap_add(hp, nums[i]);
		fail_unless(error == SUCCESS_HEAP, "Error adding to heap");
		fail_unless(heap_size(hp) == (i+1), "Size incorrect after add");	
		item = (int *) heap_peek(hp);
		fail_unless(*item == (7 - i), "Error in peek");
		fail_unless(heap_contains(hp, nums[i]), "Error in heap_contains");
	}
	
	int *nums2[5];
	for (int i = 8; i < 13; i++) {
		nums2[i-8] = malloc(sizeof(int));
		*nums2[i-8] = i;
	}

	heap hp2 = NULL;
	
	error = heap_add(hp2, nums2[0]);
	fail_unless(error == ERROR_HEAP_IS_NULL, "Error adding to NULL heap");
	fail_unless(heap_size(hp2) == ERROR_HEAP_IS_NULL, 
							"Size incorrect after adding to NULL heap");
	
	hp2 = heap_create(&int_compare);
	fail_if(!hp2, "heap_create failed.");
	
	for (int i = 0; i < 5; i++) {
		error = heap_add(hp2, nums2[i]);
		fail_unless(error == SUCCESS_HEAP, "Error adding to heap");
		fail_unless(heap_size(hp2) == (i+1), "Size incorrect after add");	
		item = (int *) heap_peek(hp2);
		fail_unless(*item == 8, "Error in peek");
		fail_unless(heap_contains(hp2, nums2[i]), "Error in heap_contains");
	}
	
	heap hp3 = heap_merge(hp, hp2);
	fail_if(hp3 == NULL, "Error in merge");
	
	for (int i = 0; i < 12; i++) {
		item = (int *) heap_remove(hp3);
		fail_unless(*item == i, "Error in remove");
		fail_unless(heap_size(hp3) == (12 - i), "Size incorrect after remove");
	}

	for (int i = 0; i < 8; i++)
		free(nums[i]);
	heap_free(hp);
	for (int i = 0; i < 5; i++)
		free(nums2[i]);
	heap_free(hp2);
	heap_free(hp3);
}
END_TEST

Suite *heap_suite(void) {
  Suite *s = suite_create("ArrayList Heap");

  /* test constructors and destructors */
  TCase *tc_init = tcase_create("Intialize");
  tcase_add_checked_fixture(tc_init, setup, teardown);
  tcase_add_test(tc_init, test_heap_create);
  suite_add_tcase(s, tc_init);

	/* test add */
  TCase *tc_add = tcase_create("Heap Add");
  tcase_add_test(tc_add, test_heap_add1);
  tcase_add_test(tc_add, test_heap_add2);
  tcase_add_test(tc_add, test_heap_add3);
	suite_add_tcase(s, tc_add);
	
	/* test remove */
  TCase *tc_remove = tcase_create("Heap Remove");
  tcase_add_test(tc_remove, test_heap_remove1);
  tcase_add_test(tc_remove, test_heap_remove2);
  tcase_add_test(tc_remove, test_heap_remove3);
	suite_add_tcase(s, tc_remove);
	
	/* test to array and merge */
	TCase *tc_misc = tcase_create("Heap Array & Merge");
	tcase_add_test(tc_misc, test_heap_to_array);
	tcase_add_test(tc_misc, test_heap_merge);
	suite_add_tcase(s, tc_misc);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = heap_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}