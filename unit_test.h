#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"
Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_get_capacity_on_init_default_returns_7(char* buffer, int length);
Status test_get_capacity_on_my_string_init_c_string_returns_size_plus_one(char* buffer, int length);
Status test_get_size_on_init_c_string_returns_correctly(char* buffer, int length);
Status test_compare_left_string_shorter(char* buffer, int length);
Status test_compare_left_string_bigger(char* buffer, int length);
Status test_compare_strings_same(char* buffer, int length);
Status test_compare_strings_prefix(char* buffer, int length);
Status test_string_push_back_increments_size(char* buffer, int length);
Status test_pop_back_decrements_size(char* buffer, int length);
Status test_string_destroy_sets_handle_NULL(char* buffer, int length);
Status test_my_string_at_returns_e(char* buffer, int length);
Status test_my_string_at_returns_NULL_at_underflow(char* buffer, int length);
Status test_my_string_at_returns_NULL_at_overflow(char* buffer, int length);
Status test_my_string_c_string_returns_first_element(char* buffer, int length);
Status test_my_string_c_str_returns_null_terminated(char* buffer, int length);
Status test_string_pop_back_returns_FAILURE_on_empty_string(char* buffer, int length);
Status test_string_concat_size_incremented_correctly(char* buffer, int length);
Status test_string_concat_does_not_change_appended_string(char* buffer, int length);
Status test_string_extraction_matches_insertion(char* buffer, int length);
Status test_extraction_size_increments_correctly(char* buffer, int length);
Status test_my_string_extraction_ignores_all_leading_whitespace(char* buffer, int length);
Status test_string_extraction_replaces_data(char* buffer, int length);
Status test_extraction_stops_at_whitespace(char* buffer, int length);

#endif
