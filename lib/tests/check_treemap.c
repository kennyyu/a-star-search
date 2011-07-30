#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/treemap.h"

map map_test;

int int_compare(void *num1, void *num2) {
	return *((int *) num1) - *((int *) num2);
}

void setup (void) {
	map_test = treemap_methods.create(&int_compare, NULL, NULL);
}

void teardown(void) {
  treemap_methods.free(map_test);
}

START_TEST (test_map_create) {
	fail_if(!map_test, "treemap_methods.create failed.");
	fail_unless(treemap_methods.size(map_test) == 0, 
							"Size not map correctly on creation");
	fail_unless(treemap_methods.is_empty(map_test), "Error: map is not empty");
}
END_TEST

START_TEST (test_map_add1) {
	int error;
	int *item;
	int *values[8];
	int *nums[8];
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = i;
		values[i] = malloc(sizeof(int));
		*values[i] = 7 - i;
	}
	
	map mp = NULL;
	
	error = treemap_methods.add(mp, nums[0], values[0]);
	fail_unless(error == ERROR_MAP_IS_NULL, "Error adding to NULL map");
	fail_unless(treemap_methods.size(mp) == ERROR_MAP_IS_NULL, 
							"Size incorrect after adding to NULL map");
	
	mp = treemap_methods.create(&int_compare, NULL, NULL);
	fail_if(!mp, "treemap_methods.create failed.");

	for (int i = 0; i < 8; i++) {
		error = treemap_methods.add(mp, nums[i], values[i]);
		fail_unless(error == SUCCESS_MAP, "Error adding to map");
		fail_unless(treemap_methods.size(mp) == (i+1), "Size incorrect after add");
		fail_unless(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
		item = (int *) treemap_methods.get(mp, nums[i]);
		fail_unless(*item == (7 - i), "Error in get"); 
	}
	
	for (int i = 0; i < 8; i++) {
		error = treemap_methods.add(mp, nums[i], values[i]);
		fail_unless(error == SUCCESS_MAP, "Error adding to map");
		fail_unless(treemap_methods.size(mp) == 8, "Size incorrect after add");	
		fail_unless(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
		item = (int *) treemap_methods.get(mp, nums[i]);
		fail_unless(*item == (7 - i), "Error in get");
	}
	
	int **items = (int **) treemap_methods.keys_to_array(mp);
	for (int i = 0; i < 8; i++) {
		fail_unless(*items[i] == *nums[i], "Error in to_array");
	}
	free(items);
	
	map_node *pairs = treemap_methods.to_array(mp);
	for (int i = 0; i < 8; i++) {
		fail_unless(*((int *) pairs[i]->key) == *nums[i], "Error in keys_to_array key");
		fail_unless(*((int *) pairs[i]->value) == *values[i], "Error in values_to_array key");
	}
	free(pairs);

	for (int i = 0; i < 8; i++) {
		free(nums[i]);
		free(values[i]);
	}
	treemap_methods.free(mp);
}
END_TEST

START_TEST (test_map_add2) {
	int error;
	int *item;
	int *values[8];
	int *nums[8];
	int temp[8] = {4, 5, 7, 0, 3, 2, 6, 1};
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = temp[i];
		values[i] = malloc(sizeof(int));
		*values[i] = 7 - temp[i];
	}
	
	map mp = NULL;
	
	error = treemap_methods.add(mp, nums[0], values[0]);
	fail_unless(error == ERROR_MAP_IS_NULL, "Error adding to NULL map");
	fail_unless(treemap_methods.size(mp) == ERROR_MAP_IS_NULL, 
							"Size incorrect after adding to NULL map");
	
	mp = treemap_methods.create(&int_compare, NULL, NULL);
	fail_if(!mp, "treemap_methods.create failed.");

	for (int i = 0; i < 8; i++) {
		error = treemap_methods.add(mp, nums[i], values[i]);
		fail_unless(error == SUCCESS_MAP, "Error adding to map");
		fail_unless(treemap_methods.size(mp) == (i+1), "Size incorrect after add");
		fail_unless(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
		item = (int *) treemap_methods.get(mp, nums[i]);
		fail_unless(*item == 7 - temp[i], "Error in get"); 
	}
	
	for (int i = 0; i < 8; i++) {
		error = treemap_methods.add(mp, nums[i], values[i]);
		fail_unless(error == SUCCESS_MAP, "Error adding to map");
		fail_unless(treemap_methods.size(mp) == 8, "Size incorrect after add");	
		fail_unless(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
		item = (int *) treemap_methods.get(mp, nums[i]);
		fail_unless(*item == 7 - temp[i], "Error in get");
	}
	
	int **items = (int **) treemap_methods.keys_to_array(mp);
	for (int i = 0; i < 8; i++) {
		fail_unless(*items[i] == i, "Error in to_array");
	}
	free(items);
	
	map_node *pairs = treemap_methods.to_array(mp);
	for (int i = 0; i < 8; i++) {
		fail_unless(*((int *) pairs[i]->key) == i, "Error in keys_to_array key");
		fail_unless(*((int *) pairs[i]->value) == 7 - i, "Error in values_to_array key");
	}
	free(pairs);

	for (int i = 0; i < 8; i++) {
		free(nums[i]);
		free(values[i]);
	}
	treemap_methods.free(mp);
}
END_TEST

START_TEST (test_map_remove1) {
	int error;
	int *item;
	int *values[8];
	int *nums[8];
	int temp[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = temp[i];
		values[i] = malloc(sizeof(int));
		*values[i] = 7 - temp[i];
	}
	
	map mp = NULL;
	
	error = treemap_methods.add(mp, nums[0], values[0]);
	fail_unless(error == ERROR_MAP_IS_NULL, "Error adding to NULL map");
	fail_unless(treemap_methods.size(mp) == ERROR_MAP_IS_NULL, 
							"Size incorrect after adding to NULL map");
	
	item = (int *) treemap_methods.remove(mp, nums[0]);
	fail_unless(item == NULL, "Error removing from NULL map");
	fail_unless(treemap_methods.size(mp) == ERROR_MAP_IS_NULL, 
							"Size incorrect after adding to NULL map");
	
	mp = treemap_methods.create(&int_compare, NULL, NULL);
	fail_if(!mp, "treemap_methods.create failed.");

	item = (int *) treemap_methods.remove(mp, nums[0]);
	fail_unless(item == NULL, "Error removing from NULL map");
	fail_unless(treemap_methods.size(mp) == 0, 
							"Size incorrect after adding to NULL map");
	
	for (int i = 0; i < 8; i++) {
		error = treemap_methods.add(mp, nums[i], values[i]);
		fail_unless(error == SUCCESS_MAP, "Error adding to map");
		fail_unless(treemap_methods.size(mp) == (i+1), "Size incorrect after add");
		fail_unless(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
		item = (int *) treemap_methods.get(mp, nums[i]);
		fail_unless(*item == 7 - temp[i], "Error in get"); 
	}

	for (int i = 0; i < 8; i++) {
		error = treemap_methods.add(mp, nums[i], values[i]);
		fail_unless(error == SUCCESS_MAP, "Error adding to map");
		fail_unless(treemap_methods.size(mp) == 8, "Size incorrect after add");	
		fail_unless(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
		item = (int *) treemap_methods.get(mp, nums[i]);
		fail_unless(*item == 7 - temp[i], "Error in get");
	}
	
	int *missing = malloc(sizeof(int));
	*missing = 8;
	item = treemap_methods.remove(mp, missing);
	fail_unless(item == NULL, "Error removing an item not in map");
	fail_unless(treemap_methods.size(mp) == 8, 
							"Size incorrect after removing an item not in map");	
	free(missing);
	
	for (int i = 0; i < 8; i++) {
		item = treemap_methods.remove(mp, nums[i]);
		fail_unless(*item == *values[i], "Error removing from map");
		fail_unless(treemap_methods.size(mp) == (7 - i), "Size incorrect after remove");
		fail_if(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
	}
	
	int **items = (int **) treemap_methods.keys_to_array(mp);
	fail_unless(items == NULL, "Error keys_to_array after remove");

	map_node *pairs = treemap_methods.to_array(mp);
	fail_unless(pairs == NULL, "Error to_array after remove");

	for (int i = 0; i < 8; i++) {
		free(nums[i]);
		free(values[i]);
	}
	treemap_methods.free(mp);
}
END_TEST

START_TEST (test_map_remove2) {
	int error;
	int *item;
	int *values[8];
	int *nums[8];
	int temp[8] = {5, 3, 7, 2, 0, 1, 4, 6};
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = temp[i];
		values[i] = malloc(sizeof(int));
		*values[i] = 7 - temp[i];
	}
	
	map mp = NULL;
	
	error = treemap_methods.add(mp, nums[0], values[0]);
	fail_unless(error == ERROR_MAP_IS_NULL, "Error adding to NULL map");
	fail_unless(treemap_methods.size(mp) == ERROR_MAP_IS_NULL, 
							"Size incorrect after adding to NULL map");
	
	item = (int *) treemap_methods.remove(mp, nums[0]);
	fail_unless(item == NULL, "Error removing from NULL map");
	fail_unless(treemap_methods.size(mp) == ERROR_MAP_IS_NULL, 
							"Size incorrect after adding to NULL map");
	
	mp = treemap_methods.create(&int_compare, NULL, NULL);
	fail_if(!mp, "treemap_methods.create failed.");

	item = (int *) treemap_methods.remove(mp, nums[0]);
	fail_unless(item == NULL, "Error removing from NULL map");
	fail_unless(treemap_methods.size(mp) == 0, 
							"Size incorrect after adding to NULL map");
	
	for (int i = 0; i < 8; i++) {
		error = treemap_methods.add(mp, nums[i], values[i]);
		fail_unless(error == SUCCESS_MAP, "Error adding to map");
		fail_unless(treemap_methods.size(mp) == (i+1), "Size incorrect after add");
		fail_unless(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
		item = (int *) treemap_methods.get(mp, nums[i]);
		fail_unless(*item == 7 - temp[i], "Error in get"); 
	}

	for (int i = 0; i < 8; i++) {
		error = treemap_methods.add(mp, nums[i], values[i]);
		fail_unless(error == SUCCESS_MAP, "Error adding to map");
		fail_unless(treemap_methods.size(mp) == 8, "Size incorrect after add");	
		fail_unless(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
		item = (int *) treemap_methods.get(mp, nums[i]);
		fail_unless(*item == 7 - temp[i], "Error in get");
	}
	
	int *missing = malloc(sizeof(int));
	*missing = 8;
	item = treemap_methods.remove(mp, missing);
	fail_unless(item == NULL, "Error removing an item not in map");
	fail_unless(treemap_methods.size(mp) == 8, 
							"Size incorrect after removing an item not in map");	
	free(missing);
	
	for (int i = 0; i < 8; i++) {
		item = treemap_methods.remove(mp, nums[i]);
		fail_unless(*item == *values[i], "Error removing from map");
		fail_unless(treemap_methods.size(mp) == (7 - i), "Size incorrect after remove");
		fail_if(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
	}
	
	int **items = (int **) treemap_methods.keys_to_array(mp);
	fail_unless(items == NULL, "Error keys_to_array after remove");

	map_node *pairs = treemap_methods.to_array(mp);
	fail_unless(pairs == NULL, "Error to_array after remove");

	for (int i = 0; i < 8; i++) {
		free(nums[i]);
		free(values[i]);
	}
	treemap_methods.free(mp);
}
END_TEST

START_TEST (test_map_remove_random1) {
	int error;
	int *item;
	map_node node;
	int *values[8];
	int *nums[8];
	int temp[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = temp[i];
		values[i] = malloc(sizeof(int));
		*values[i] = 7 - temp[i];
	}
	
	map mp = NULL;
	
	error = treemap_methods.add(mp, nums[0], values[0]);
	fail_unless(error == ERROR_MAP_IS_NULL, "Error adding to NULL map");
	fail_unless(treemap_methods.size(mp) == ERROR_MAP_IS_NULL, 
							"Size incorrect after adding to NULL map");
	
	node = treemap_methods.remove_random(mp);
	fail_unless(node == NULL, "Error removing random from NULL map");
	fail_unless(treemap_methods.size(mp) == ERROR_MAP_IS_NULL, 
							"Size incorrect after adding to NULL map");
	
	mp = treemap_methods.create(&int_compare, NULL, NULL);
	fail_if(!mp, "treemap_methods.create failed.");

	node = treemap_methods.remove_random(mp);
	fail_unless(node == NULL, "Error removing random from NULL map");
	fail_unless(treemap_methods.size(mp) == 0, 
							"Size incorrect after adding to NULL map");
	
	for (int i = 0; i < 8; i++) {
		error = treemap_methods.add(mp, nums[i], values[i]);
		fail_unless(error == SUCCESS_MAP, "Error adding to map");
		fail_unless(treemap_methods.size(mp) == (i+1), "Size incorrect after add");
		fail_unless(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
		item = (int *) treemap_methods.get(mp, nums[i]);
		fail_unless(*item == 7 - temp[i], "Error in get"); 
	}

	for (int i = 0; i < 8; i++) {
		error = treemap_methods.add(mp, nums[i], values[i]);
		fail_unless(error == SUCCESS_MAP, "Error adding to map");
		fail_unless(treemap_methods.size(mp) == 8, "Size incorrect after add");	
		fail_unless(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
		item = (int *) treemap_methods.get(mp, nums[i]);
		fail_unless(*item == 7 - temp[i], "Error in get");
	}
	
	for (int i = 0; i < 8; i++) {
		node = treemap_methods.remove_random(mp);
		fail_unless(*(int *)node->key == i, "Error removing from map");
		fail_unless(*(int *)node->value == 7 - i, "Error removing from map");
		fail_unless(treemap_methods.size(mp) == (7 - i), "Size incorrect after remove");
		fail_if(treemap_methods.contains(mp, node->key), "Error in treemap_methods.contains");
	}
	
	int **items = (int **) treemap_methods.keys_to_array(mp);
	fail_unless(items == NULL, "Error keys_to_array after remove");

	map_node *pairs = treemap_methods.to_array(mp);
	fail_unless(pairs == NULL, "Error to_array after remove");

	for (int i = 0; i < 8; i++) {
		free(nums[i]);
		free(values[i]);
	}
	treemap_methods.free(mp);
}
END_TEST

START_TEST (test_map_remove_random2) {
	int error;
	int *item;
	map_node node;
	int *values[8];
	int *nums[8];
	int temp[8] = {4, 2, 6, 1, 7, 0, 3, 5};
	for (int i = 0; i < 8; i++) {
		nums[i] = malloc(sizeof(int));
		*nums[i] = temp[i];
		values[i] = malloc(sizeof(int));
		*values[i] = 7 - temp[i];
	}
	
	map mp = NULL;
	
	error = treemap_methods.add(mp, nums[0], values[0]);
	fail_unless(error == ERROR_MAP_IS_NULL, "Error adding to NULL map");
	fail_unless(treemap_methods.size(mp) == ERROR_MAP_IS_NULL, 
							"Size incorrect after adding to NULL map");
	
	node = treemap_methods.remove_random(mp);
	fail_unless(node == NULL, "Error removing random from NULL map");
	fail_unless(treemap_methods.size(mp) == ERROR_MAP_IS_NULL, 
							"Size incorrect after adding to NULL map");
	
	mp = treemap_methods.create(&int_compare, NULL, NULL);
	fail_if(!mp, "treemap_methods.create failed.");

	node = treemap_methods.remove_random(mp);
	fail_unless(node == NULL, "Error removing random from NULL map");
	fail_unless(treemap_methods.size(mp) == 0, 
							"Size incorrect after adding to NULL map");
	
	for (int i = 0; i < 8; i++) {
		error = treemap_methods.add(mp, nums[i], values[i]);
		fail_unless(error == SUCCESS_MAP, "Error adding to map");
		fail_unless(treemap_methods.size(mp) == (i+1), "Size incorrect after add");
		fail_unless(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
		item = (int *) treemap_methods.get(mp, nums[i]);
		fail_unless(*item == 7 - temp[i], "Error in get"); 
	}

	for (int i = 0; i < 8; i++) {
		error = treemap_methods.add(mp, nums[i], values[i]);
		fail_unless(error == SUCCESS_MAP, "Error adding to map");
		fail_unless(treemap_methods.size(mp) == 8, "Size incorrect after add");	
		fail_unless(treemap_methods.contains(mp, nums[i]), "Error in treemap_methods.contains");
		item = (int *) treemap_methods.get(mp, nums[i]);
		fail_unless(*item == 7 - temp[i], "Error in get");
	}
	
	for (int i = 0; i < 8; i++) {
		node = treemap_methods.remove_random(mp);
		fail_unless(*(int *)node->key == i, "Error removing from map");
		fail_unless(*(int *)node->value == 7 - i, "Error removing from map");
		fail_unless(treemap_methods.size(mp) == (7 - i), "Size incorrect after remove");
		fail_if(treemap_methods.contains(mp, node->key), "Error in treemap_methods.contains");
	}
	
	int **items = (int **) treemap_methods.keys_to_array(mp);
	fail_unless(items == NULL, "Error keys_to_array after remove");

	map_node *pairs = treemap_methods.to_array(mp);
	fail_unless(pairs == NULL, "Error to_array after remove");

	for (int i = 0; i < 8; i++) {
		free(nums[i]);
		free(values[i]);
	}
	treemap_methods.free(mp);
}
END_TEST

Suite *map_suite(void) {
  Suite *s = suite_create("TreeMap");

  /* test constructors and destructors */
  TCase *tc_init = tcase_create("Intialize");
  tcase_add_checked_fixture(tc_init, setup, teardown);
  tcase_add_test(tc_init, test_map_create);
  suite_add_tcase(s, tc_init);

  /* test add */
  TCase *tc_add = tcase_create("Map Add");
  tcase_add_test(tc_add, test_map_add1);
	tcase_add_test(tc_add, test_map_add2);
  suite_add_tcase(s, tc_add);

  /* test remove */
  TCase *tc_remove = tcase_create("Map Remove");
  tcase_add_test(tc_remove, test_map_remove1);
	tcase_add_test(tc_remove, test_map_remove2);
  suite_add_tcase(s, tc_remove);

  /* test remove random */
  TCase *tc_remove_random = tcase_create("Map Remove Random");
  tcase_add_test(tc_remove_random, test_map_remove_random1);
	tcase_add_test(tc_remove_random, test_map_remove_random2);
  suite_add_tcase(s, tc_remove_random);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = map_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}