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

Suite *list_suite(void) {
  Suite *s = suite_create("ArrayList");

  /* test constructors and destructors */
  TCase *tc_init = tcase_create("Intialize");
  tcase_add_checked_fixture(tc_init, setup, teardown);
  tcase_add_test(tc_init, test_list_create);
  suite_add_tcase(s, tc_init);

	/* test getters */
	/*
  TCase *tc_setters = tcase_create("Getters");
  tcase_add_test(tc_setters, test_get_first);
  tcase_add_test(tc_setters, test_get_last);
	tcase_add_test(tc_setters, test_get);
	tcase_add_test(tc_setters, test_to_array);
  suite_add_tcase(s, tc_setters);*/

	/* test adders */
	/*
  TCase *tc_adders = tcase_create("Adders");
  tcase_add_test(tc_adders, test_add_first);
  tcase_add_test(tc_adders, test_add_last);
	tcase_add_test(tc_adders, test_set);
  suite_add_tcase(s, tc_adders);	*/

	/* test removers */
	/*
  TCase *tc_removers = tcase_create("Removers");
  tcase_add_test(tc_removers, test_remove_first);
  tcase_add_test(tc_removers, test_remove_last);
	tcase_add_test(tc_removers, test_remove);
  suite_add_tcase(s, tc_removers); */

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