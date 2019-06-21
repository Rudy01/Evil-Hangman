#include <stdio.h>
#include "unit_test.h"
int main(int argc, char* argv[]){
  Status (*tests[])(char*, int) =
    {
      test_init_default_returns_nonNULL,
      test_get_size_on_init_default_returns_0,
      test_get_capacity_on_init_default_returns_7,
      test_get_capacity_on_my_string_init_c_string_returns_size_plus_one,
      test_get_size_on_init_c_string_returns_correctly,
      test_compare_left_string_shorter,
      test_compare_left_string_bigger,
      test_compare_strings_same,
      test_compare_strings_prefix,
      test_string_push_back_increments_size,
      test_pop_back_decrements_size,
      test_string_destroy_sets_handle_NULL,
      test_my_string_at_returns_e,
      test_my_string_at_returns_NULL_at_underflow,
      test_my_string_at_returns_NULL_at_overflow,
      test_my_string_c_string_returns_first_element,
      test_my_string_c_str_returns_null_terminated,
      test_string_pop_back_returns_FAILURE_on_empty_string,
      test_string_concat_size_incremented_correctly,
      test_string_concat_does_not_change_appended_string,
      test_string_extraction_matches_insertion,
      test_extraction_size_increments_correctly,
      test_my_string_extraction_ignores_all_leading_whitespace,
      test_string_extraction_replaces_data,
      test_extraction_stops_at_whitespace
    };
  
  int number_of_functions = sizeof(tests) / sizeof(tests[0]);
  int i;
  char buffer[500];
  int success_count = 0;
  int failure_count = 0;
  for(i = 0; i < number_of_functions; i++){
    if(tests[i](buffer, 500) == FAILURE){
      printf("FAILED: Test %d failed miserably\n", i);
      printf("\t%s\n", buffer);
      failure_count++;
    } else {
      printf("PASS: Test %d passed\n", i);
      printf("\t%s\n", buffer);
      success_count++;
    }
  }
  printf("Total number of tests: %d\n", number_of_functions);
  printf("%d/%d Pass, %d/%d Failure\n", success_count,
	 number_of_functions, failure_count, number_of_functions);
  return 0;
}
