#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/hashset.h"

set set_test;

int int_hash(void *num1) {
	return *(int *)num1;
}

int int_equal(void *num1, void *num2) {
	return *(int *)num1 == *(int *)num2;
}

void setup (void) {
	set_test = hashset_methods.create(NULL, &int_hash, &int_equal);
}

void teardown(void) {
  hashset_methods.free(set_test);
}

START_TEST (test_set_create) {
	fail_if(!set_test, "hashset_methods.create failed.");
  fail_unless(hashset_methods.size(set_test) == 0, 
							"Size not set correctly on creation");
	fail_unless(hashset_methods.is_empty(set_test), "Error: set is not empty");
}
END_TEST

START_TEST (test_set_add1) {
	int error;
	int *nums[8];
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	set se = NULL;
	
	error = hashset_methods.add(se, nums[0]);
	fail_unless(error == ERROR_SET_IS_NULL, "Error adding to NULL set");
	fail_unless(hashset_methods.size(se) == ERROR_SET_IS_NULL, 
							"Size incorrect after adding to NULL set");
	
	se = hashset_methods.create(NULL, &int_hash, &int_equal);
	fail_if(!se, "hashset_methods.create failed.");
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.add(se, nums[i]);
		fail_unless(error == SUCCESS_SET, "Error adding to set");
		fail_unless(hashset_methods.size(se) == (i+1), "Size incorrect after add");	
		fail_unless(hashset_methods.contains(se, nums[i]), "Error in hashset_methods.contains");
	}
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.add(se, nums[i]);
		fail_unless(error == SUCCESS_SET, "Error adding to set");
		fail_unless(hashset_methods.size(se) == 8, "Size incorrect after add");	
		fail_unless(hashset_methods.contains(se, nums[i]), "Error in hashset_methods.contains");
	}
	
	int **items = (int **) hashset_methods.to_array(se);
	for (int i = 0; i < 8; i++) {
		fail_unless(*items[i] == *nums[i], "Error in to_array");
	}

	for (int i = 0; i < 8; i++)
		free(nums[i]);
	free(items);	
	hashset_methods.free(se);
}
END_TEST

START_TEST (test_set_add2) {
	int error;
	int temp_nums[8] = {5,7,6,2,0,3,4,1};
	int *nums[8];
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = temp_nums[i];
	}
	
	set se = NULL;
	
	error = hashset_methods.add(se, nums[0]);
	fail_unless(error == ERROR_SET_IS_NULL, "Error adding to NULL set");
	fail_unless(hashset_methods.size(se) == ERROR_SET_IS_NULL, 
							"Size incorrect after adding to NULL set");
	
	se = hashset_methods.create(NULL, &int_hash, &int_equal);
	fail_if(!se, "hashset_methods.create failed.");
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.add(se, nums[i]);
		fail_unless(error == SUCCESS_SET, "Error adding to set");
		fail_unless(hashset_methods.size(se) == (i+1), "Size incorrect after add");	
		fail_unless(hashset_methods.contains(se, nums[i]), "Error in hashset_methods.contains");
	}
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.add(se, nums[i]);
		fail_unless(error == SUCCESS_SET, "Error adding to set");
		fail_unless(hashset_methods.size(se) == 8, "Size incorrect after add");	
		fail_unless(hashset_methods.contains(se, nums[i]), "Error in hashset_methods.contains");
	}
	
	int **items = (int **) hashset_methods.to_array(se);
	for (int i = 0; i < 8; i++) {
		fail_unless(*items[i] == i, "Error in to_array");
	}

	for (int i = 0; i < 8; i++)
		free(nums[i]);
	free(items);	
	hashset_methods.free(se);
}
END_TEST

START_TEST (test_set_remove1) {
	int error;
	int *nums[8];
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	set se = NULL;
	
	error = hashset_methods.add(se, nums[0]);
	fail_unless(error == ERROR_SET_IS_NULL, "Error adding to NULL set");
	fail_unless(hashset_methods.size(se) == ERROR_SET_IS_NULL, 
							"Size incorrect after adding to NULL set");
	
	error = hashset_methods.remove(se, nums[0]);
	fail_unless(error == ERROR_SET_IS_NULL, "Error removing from NULL set");
	fail_unless(hashset_methods.size(se) == ERROR_SET_IS_NULL, 
							"Size incorrect after adding to NULL set");
	
	se = hashset_methods.create(NULL, &int_hash, &int_equal);
	fail_if(!se, "hashset_methods.create failed.");
	
	error = hashset_methods.remove(se, nums[0]);
	fail_unless(error == ERROR_SET_IS_EMPTY, "Error removing from EMPTY set");
	fail_unless(hashset_methods.size(se) == 0, 
							"Size incorrect after adding to NULL set");
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.add(se, nums[i]);
		fail_unless(error == SUCCESS_SET, "Error adding to set");
		fail_unless(hashset_methods.size(se) == (i+1), "Size incorrect after add");	
		fail_unless(hashset_methods.contains(se, nums[i]), "Error in hashset_methods.contains");
	}
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.add(se, nums[i]);
		fail_unless(error == SUCCESS_SET, "Error adding to set");
		fail_unless(hashset_methods.size(se) == 8, "Size incorrect after add");	
		fail_unless(hashset_methods.contains(se, nums[i]), "Error in hashset_methods.contains");
	}
	
	int *temp = malloc(sizeof(int));
	*temp = 8;
	error = hashset_methods.remove(se, temp);
	fail_unless(error == ERROR_SET_ITEM_NOT_FOUND, "Error removing an item not in set");
	fail_unless(hashset_methods.size(se) == 8, 
							"Size incorrect after removing an item not in set");	
	free(temp);
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.remove(se, nums[i]);
		fail_unless(error == SUCCESS_SET, "Error removing from set");
		fail_unless(hashset_methods.size(se) == (7 - i), "Size incorrect after remove");
		fail_if(hashset_methods.contains(se, nums[i]), "Error in hashset_methods.contains");
	}
	
	int **items = (int **) hashset_methods.to_array(se);
	fail_unless(items == NULL, "Error to_array after remove");

	for (int i = 0; i < 8; i++)
		free(nums[i]);
	free(items);	
	hashset_methods.free(se);
}
END_TEST

START_TEST (test_set_remove2) {
	int error;
	int temp_nums[8] = {5,7,6,2,0,3,4,1};
	int *nums[8];
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = temp_nums[i];
	}
	
	set se = NULL;
	
	error = hashset_methods.add(se, nums[0]);
	fail_unless(error == ERROR_SET_IS_NULL, "Error adding to NULL set");
	fail_unless(hashset_methods.size(se) == ERROR_SET_IS_NULL, 
							"Size incorrect after adding to NULL set");
	
	error = hashset_methods.remove(se, nums[0]);
	fail_unless(error == ERROR_SET_IS_NULL, "Error removing from NULL set");
	fail_unless(hashset_methods.size(se) == ERROR_SET_IS_NULL, 
							"Size incorrect after adding to NULL set");
	
	se = hashset_methods.create(NULL, &int_hash, &int_equal);
	fail_if(!se, "hashset_methods.create failed.");
	
	error = hashset_methods.remove(se, nums[0]);
	fail_unless(error == ERROR_SET_IS_EMPTY, "Error removing from EMPTY set");
	fail_unless(hashset_methods.size(se) == 0, 
							"Size incorrect after adding to NULL set");
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.add(se, nums[i]);
		fail_unless(error == SUCCESS_SET, "Error adding to set");
		fail_unless(hashset_methods.size(se) == (i+1), "Size incorrect after add");	
		fail_unless(hashset_methods.contains(se, nums[i]), "Error in hashset_methods.contains");
	}
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.add(se, nums[i]);
		fail_unless(error == SUCCESS_SET, "Error adding to set");
		fail_unless(hashset_methods.size(se) == 8, "Size incorrect after add");	
		fail_unless(hashset_methods.contains(se, nums[i]), "Error in hashset_methods.contains");
	}
	
	int *temp = malloc(sizeof(int));
	*temp = 8;
	error = hashset_methods.remove(se, temp);
	fail_unless(error == ERROR_SET_ITEM_NOT_FOUND, "Error removing an item not in set");
	fail_unless(hashset_methods.size(se) == 8, 
							"Size incorrect after removing an item not in set");	
	free(temp);
	
	int *ordered_nums[8];
	for (int i = 0; i < 8; i++) {
		ordered_nums[i] = malloc(sizeof(int));
		*ordered_nums[i] = i;
	}
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.remove(se, ordered_nums[i]);
		fail_unless(error == SUCCESS_SET, "Error removing from set");
		fail_unless(hashset_methods.size(se) == (7 - i), "Size incorrect after remove");
		fail_if(hashset_methods.contains(se, ordered_nums[i]), "Error in hashset_methods.contains");
	}
	
	int **items = (int **) hashset_methods.to_array(se);
	fail_unless(items == NULL, "Error to_array after remove");

	for (int i = 0; i < 8; i++) {
		free(nums[i]);
		free(ordered_nums[i]);
	}
	free(items);	
	hashset_methods.free(se);
}
END_TEST

START_TEST (test_set_remove_random1) {
	int error;
	int *item;
	int *nums[8];
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
	}
	
	set se = NULL;
	
	item = (int *) hashset_methods.remove_random(se);
	fail_unless(item == NULL, "Error removing from NULL set");
	fail_unless(hashset_methods.size(se) == ERROR_SET_IS_NULL, 
							"Size incorrect after adding to NULL set");
	
	se = hashset_methods.create(NULL, &int_hash, &int_equal);
	fail_if(!se, "hashset_methods.create failed.");
	
	item = (int *) hashset_methods.remove_random(se);
	fail_unless(item == NULL, "Error removing from EMPTY set");
	fail_unless(hashset_methods.size(se) == 0, 
							"Size incorrect after adding to EMPTY set");
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.add(se, nums[i]);
		fail_unless(error == SUCCESS_SET, "Error adding to set");
		fail_unless(hashset_methods.size(se) == (i+1), "Size incorrect after add");	
		fail_unless(hashset_methods.contains(se, nums[i]), "Error in hashset_methods.contains");
	}
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.add(se, nums[i]);
		fail_unless(error == SUCCESS_SET, "Error adding to set");
		fail_unless(hashset_methods.size(se) == 8, "Size incorrect after add");	
		fail_unless(hashset_methods.contains(se, nums[i]), "Error in hashset_methods.contains");
	}
	
	for (int i = 0; i < 8; i++) {
		item = hashset_methods.remove_random(se);
                int is_contained = 0;
		for (int j = 0; j < 8; j++) {
			if (*item == j)
				is_contained = 1;
		}
		fail_unless(is_contained, "Error in remove_random");	
		fail_unless(hashset_methods.size(se) == (7 - i), "Size incorrect after remove");
		fail_if(hashset_methods.contains(se, item), "Error in hashset_methods.contains");
	}
	
	int **items = (int **) hashset_methods.to_array(se);
	fail_unless(items == NULL, "Error to_array after remove");

	for (int i = 0; i < 8; i++) {
		free(nums[i]);
	}
	free(items);	
	hashset_methods.free(se);
}
END_TEST

START_TEST (test_set_remove_random2) {
	int error;
	int *item;
	int temp_nums[8] = {5,7,6,2,0,3,4,1};
	int *nums[8];
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = temp_nums[i];
	}
	
	set se = NULL;
	
	item = (int *) hashset_methods.remove_random(se);
	fail_unless(item == NULL, "Error removing from NULL set");
	fail_unless(hashset_methods.size(se) == ERROR_SET_IS_NULL, 
							"Size incorrect after adding to NULL set");
	
	se = hashset_methods.create(NULL, &int_hash, &int_equal);
	fail_if(!se, "hashset_methods.create failed.");
	
	item = (int *) hashset_methods.remove_random(se);
	fail_unless(item == NULL, "Error removing from EMPTY set");
	fail_unless(hashset_methods.size(se) == 0, 
							"Size incorrect after adding to EMPTY set");
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.add(se, nums[i]);
		fail_unless(error == SUCCESS_SET, "Error adding to set");
		fail_unless(hashset_methods.size(se) == (i+1), "Size incorrect after add");	
		fail_unless(hashset_methods.contains(se, nums[i]), "Error in hashset_methods.contains");
	}
	
	for (int i = 0; i < 8; i++) {
		error = hashset_methods.add(se, nums[i]);
		fail_unless(error == SUCCESS_SET, "Error adding to set");
		fail_unless(hashset_methods.size(se) == 8, "Size incorrect after add");	
		fail_unless(hashset_methods.contains(se, nums[i]), "Error in hashset_methods.contains");
	}
	
	int *ordered_nums[8];
	for (int i = 0; i < 8; i++) {
		ordered_nums[i] = malloc(sizeof(int));
		*ordered_nums[i] = i;
	}
	
	for (int i = 0; i < 8; i++) {
		item = hashset_methods.remove_random(se);
                int is_contained = 0;
		for (int j = 0; j < 8; j++) {
			if (*item == j)
				is_contained = 1;
		}
		fail_unless(is_contained, "Error in remove_random");	
		fail_unless(hashset_methods.size(se) == (7 - i), "Size incorrect after remove");
		fail_if(hashset_methods.contains(se, item), "Error in hashset_methods.contains");
	}
	
	int **items = (int **) hashset_methods.to_array(se);
	fail_unless(items == NULL, "Error to_array after remove");

	for (int i = 0; i < 8; i++) {
		free(nums[i]);
		free(ordered_nums[i]);
	}
	free(items);	
	hashset_methods.free(se);
}
END_TEST

Suite *set_suite(void) {
  Suite *s = suite_create("HashMap Set");

  /* test constructors and destructors */
  TCase *tc_init = tcase_create("Intialize");
  tcase_add_checked_fixture(tc_init, setup, teardown);
  tcase_add_test(tc_init, test_set_create);
  suite_add_tcase(s, tc_init);

  /* test add */
  TCase *tc_add = tcase_create("Set Add");
  tcase_add_test(tc_add, test_set_add1);
	tcase_add_test(tc_add, test_set_add2);
  suite_add_tcase(s, tc_add);

  /* test remove */
  TCase *tc_remove = tcase_create("Set Remove");
  tcase_add_test(tc_remove, test_set_remove1);
	tcase_add_test(tc_remove, test_set_remove2);
  suite_add_tcase(s, tc_remove);

  /* test remove random */
  TCase *tc_remove_random = tcase_create("Set Remove Random");
  tcase_add_test(tc_remove_random, test_set_remove_random1);
	tcase_add_test(tc_remove_random, test_set_remove_random2);
  suite_add_tcase(s, tc_remove_random);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = set_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}