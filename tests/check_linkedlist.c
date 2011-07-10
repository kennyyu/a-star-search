#include <stdlib.h>
#include <check.h>
#include "../src/linkedlist.h"

linkedlist *list;

void setup (void) {
  list = list_create();
}

void teardown(void) {
  list_free(list);
}

START_TEST (test_list_create) {
  fail_unless(list_size(list) == 0,
	       "Size not set correctly on creation");
}
END_TEST

START_TEST (test_add_first) {
	list = list_create();
	int nums[] = {0,1,2};
	for(int i = 0; i < 3; i++) {
		list_add_first(list, &nums[i]);
	}
  fail_unless(list_size(list) == 3,
	       "Size incorrect after add_first");
}
END_TEST

START_TEST (test_add_last) {
	list = list_create();
	int nums[] = {0,1,2};
	for(int i = 0; i < 3; i++) {
		list_add_last(list, &nums[i]);
	}
  fail_unless(list_size(list) == 3,
	       "Size incorrect after add_last");
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
  TCase *tc_setters = tcase_create("Setters");
  tcase_add_test(tc_setters, test_add_first);
  tcase_add_test(tc_setters, test_add_last);
  suite_add_tcase(s, tc_setters);	

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = list_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
