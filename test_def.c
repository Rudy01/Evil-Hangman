#include "unit_test.h"
Status test_init_default_returns_nonNULL(char* buffer, int length){
  MY_STRING hString = NULL;
  hString = my_string_init_default();
  if(hString == NULL){
    my_string_destroy(&hString);
    strncpy(buffer, "test_init_default_returns_nonNULL\n"
	    "my_string_init_default returns NULL", length);
    return FAILURE;
  } else {
    my_string_destroy(&hString);
    strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
    return SUCCESS;
  }
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length){
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_default();
  if(my_string_get_size(hString) != 0){
    status = FAILURE;
    printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
    strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
	    "Did not receive 0 from get_size after init_default\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
	    , length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_get_capacity_on_init_default_returns_7(char* buffer, int length){
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_default();
  if(my_string_get_capacity(hString) != 7){
    status = FAILURE;
    printf("Expected a size of 7 but got %d\n", my_string_get_capacity(hString));
    strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n"
	    "Did not receive 7 from get_capacity after init_default\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n"
	    , length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_get_capacity_on_my_string_init_c_string_returns_size_plus_one(char* buffer, int length){
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_c_string("test");
  if(my_string_get_capacity(hString) != 5){
    status = FAILURE;
    printf("Expected a size of 5 but got %d\n", my_string_get_capacity(hString));
    strncpy(buffer, "test_get_capacity_on_my_string_init_c_string_returns_size_plus_one\n"
	    "Did not receive 5 from get_capacity after init_c_string\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_get_capacity_on_my_string_init_c_string_returns_size_plus_one\n"
	    , length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_get_size_on_init_c_string_returns_correctly(char* buffer, int length){
  MY_STRING hString;
  Status status;
  hString = my_string_init_c_string("test");
  if(my_string_get_size(hString) != 4){
    status=FAILURE;
    printf("Expected a size of 4 but got %d\n", my_string_get_size(hString));
    strncpy(buffer, "test_get_size_on_init_c_string_returns_correctly\n" "Did not receive 4 from get_size after init_c_string\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_get_size_on_init_c_string_returns_correctly\n", length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_compare_left_string_shorter(char* buffer, int length){
  MY_STRING lString;
  MY_STRING rString;
  lString = my_string_init_c_string("aaaaa");
  rString = my_string_init_c_string("bbbbb");
  Status status;
  if(my_string_compare(lString, rString) < 0){
    status = SUCCESS;
    strncpy(buffer, "test_compare_left_string_shorter\n", length);
  } else {
    status = FAILURE;
    printf("Expected a negative inter but got %d\n", my_string_compare(lString, rString));
    strncpy(buffer, "test_compare_left_string_shorter\n" "Did not receive negative int from compare\n", length);
  }
  my_string_destroy(&rString);
  my_string_destroy(&lString);
  return status;
}

Status test_compare_left_string_bigger(char* buffer, int length){
  MY_STRING lString;
  MY_STRING rString;
  lString = my_string_init_c_string("ccccc");
  rString = my_string_init_c_string("bbbbb");
  Status status;
  if(my_string_compare(lString, rString) > 0){
    status = SUCCESS;
    strncpy(buffer, "test_compare_left_string_bigger\n", length);
  } else {
    status = FAILURE;
    printf("Expected a positive inter but got %d\n", my_string_compare(lString, rString));
    strncpy(buffer, "test_compare_left_string_bigger\n" "Did not receive positive int from compare\n", length);
  }
  my_string_destroy(&rString);
  my_string_destroy(&lString);
  return status;
}


Status test_compare_strings_same(char* buffer, int length){
  MY_STRING lString;
  MY_STRING rString;
  lString = my_string_init_c_string("bbbbb");
  rString = my_string_init_c_string("bbbbb");
  Status status;
  if(my_string_compare(lString, rString) == 0){
    status = SUCCESS;
    strncpy(buffer, "test_compare_strings_same\n", length);
  } else {
    status = FAILURE;
    printf("Expected a zero but got %d\n", my_string_compare(lString, rString));
    strncpy(buffer, "test_compare_strings_same\n" "Did not receive zero from compare\n", length);
  }
  my_string_destroy(&rString);
  my_string_destroy(&lString);
  return status;
}

Status test_compare_strings_prefix(char* buffer, int length){
  MY_STRING lString;
  MY_STRING rString;
  lString = my_string_init_c_string("bbbb");
  rString = my_string_init_c_string("bbbbb");
  Status status;
  if(my_string_compare(lString, rString) < 0){
    status = SUCCESS;
    strncpy(buffer, "test_compare_strings_prefix\n", length);
  } else{
    status = FAILURE;
    printf("Expected a negative int but got %d\n", my_string_compare(lString, rString));
    strncpy(buffer, "test_compare_strings_prefix\n" "Did not receive negative int from compare\n", length);
  }
  my_string_destroy(&rString);
  my_string_destroy(&lString);
  return status;
}

Status test_string_push_back_increments_size(char* buffer, int length){
  MY_STRING hString;
  Status status;
  hString = my_string_init_c_string("test");
  my_string_push_back(hString, 'x');
  if(my_string_get_size(hString)!=5){
    status=FAILURE;
    printf("Expected a size of 5 but got %d\n", my_string_get_size(hString));
    strncpy(buffer, "test_string_push_back_increments_size\n" "Did not receive 5 from get_size after push_back\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_string_push_back_increments_size\n", length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_pop_back_decrements_size(char* buffer, int length){
  MY_STRING hString;
  Status status;
  hString = my_string_init_c_string("test");
  my_string_pop_back(hString);
  if(my_string_get_size(hString) != 3){
    status = FAILURE;
    printf("Expected a size of 3 but got %d\n", my_string_get_size(hString));
    strncpy(buffer, "test_pop_back_decrements_size\n" "Did not receive 3 from get_size after pop_back\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_pop_back_decrements_size\n", length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_string_destroy_sets_handle_NULL(char* buffer, int length){
  MY_STRING hString;
  hString = my_string_init_default();
  my_string_destroy(&hString);
  if(hString != NULL){
    strncpy(buffer, "test_string_destroy_sets_handle_NULL\n"
	    "my_string_destroy does not set handle to NULL", length);
    return FAILURE;
  } else {
    strncpy(buffer, "\ttest_string_destroy_sets_handle_NULL\n", length);
    return SUCCESS;
  }
}

Status test_my_string_at_returns_e(char* buffer, int length){
  MY_STRING hString;
  Status status;
  hString = my_string_init_c_string("test");
  if(*my_string_at(hString, 1) != 'e'){
    printf("Expected 'e' but got %c\n", *my_string_at(hString, 1));
    strncpy(buffer, "test_my_string_at_returns_e\n"
	    "my_string_at does not return e", length);
    status = FAILURE;
  } else {
    strncpy(buffer, "\ttest_my_string_at_returns_e\n", length);
    status = SUCCESS;
  }
  my_string_destroy(&hString);
  return status;
}

Status test_my_string_at_returns_NULL_at_underflow(char* buffer, int length){
  MY_STRING hString;
  Status status;
  hString = my_string_init_c_string("test");
  if(my_string_at(hString, -1) != NULL){
    printf("Expected NULL but got non NULL\n");
    strncpy(buffer, "test_my_string_at_returns_NULL_at_underflow\n"
	    "my_string_at does not return NULL", length);
    status = FAILURE;
  } else {
    strncpy(buffer, "\ttest_my_string_at_returns_NULL_at_underflow\n", length);
    status = SUCCESS;
  }
  my_string_destroy(&hString);
  return status;
}

Status test_my_string_at_returns_NULL_at_overflow(char* buffer, int length){
  MY_STRING hString;
  Status status;
  hString = my_string_init_c_string("test");
  if(my_string_at(hString, 4) != NULL){
    printf("Expected NULL but got non NULL\n");
    strncpy(buffer, "test_my_string_at_returns_NULL_at_overflow\n"
	    "my_string_at does not return NULL", length);
    status = FAILURE;
  } else {
    strncpy(buffer, "\ttest_my_string_at_returns_NULL_at_overflow\n", length);
    status = SUCCESS;
  }
  my_string_destroy(&hString);
  return status;
}

Status test_my_string_c_string_returns_first_element(char* buffer, int length){
  MY_STRING hString;
  Status status;
  hString = my_string_init_c_string("test");
  if(*my_string_c_str(hString) != 't'){
    printf("Expected 't' but got %c\n", *my_string_c_str(hString));
    strncpy(buffer, "test_my_string_c_string_returns_first_element\n"
	    "my_string_c_str does not return t", length);
    status = FAILURE;
  } else {
    strncpy(buffer, "\ttest_my_string_c_string_returns_first_element\n", length);
    status = SUCCESS;
  }
  my_string_destroy(&hString);
  return status;
}

Status test_my_string_c_str_returns_null_terminated(char* buffer, int length){
  MY_STRING hString;
  Status status;
  hString = my_string_init_c_string("test");
  if(my_string_c_str(hString)[4] != '\0'){
    printf("Expected null character but got %c\n", *my_string_c_str(hString));
    strncpy(buffer, "test_my_string_c_str_returns_null_terminated\n"
	    "my_string_c_str does not return null terminated", length);
    status = FAILURE;
  } else {
    strncpy(buffer, "\ttest_my_string_c_str_returns_null_terminated\n", length);
    status = SUCCESS;
  }
  my_string_destroy(&hString);
  return status;
}

Status test_string_pop_back_returns_FAILURE_on_empty_string(char* buffer, int length){
  MY_STRING hString;
  Status status;
  hString = my_string_init_default();
  if(my_string_pop_back(hString) != FAILURE){
    status = FAILURE;
    printf("Pop on empty string did not return FAILURE\n");
    strncpy(buffer, "test_string_pop_back_returns_FAILURE_on_empty_string\n" "Did not receive FAILURE from pop_back\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_string_pop_back_returns_FAILURE_on_empty_string\n", length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_string_concat_size_incremented_correctly(char* buffer, int length){
  MY_STRING rString;
  MY_STRING aString;
  rString = my_string_init_c_string("result");
  aString = my_string_init_c_string("append");
  Status status;
  my_string_concat(rString, aString);
  if(my_string_get_size(rString) != 12){
    status = FAILURE;
    printf("Expected a size of 12 but got %d\n", my_string_get_size(rString));
    strncpy(buffer, "test_string_concat_size_incremented_correctly\n"
	    "Did not receive 12 from get_size on result after my_string_concat\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_string_concat_size_incremented_correctly\n", length);
  }
  my_string_destroy(&rString);
  my_string_destroy(&aString);
  return status;
}

Status test_string_concat_does_not_change_appended_string(char* buffer, int length){
  MY_STRING rString;
  MY_STRING aString;
  MY_STRING controlString;
  rString = my_string_init_c_string("result");
  aString = my_string_init_c_string("append");
  controlString = my_string_init_c_string("append");
  Status status;
  my_string_concat(rString, aString);
  if(my_string_compare(aString, controlString) != 0){
    status = FAILURE;
    printf("Expected strings to be identical, but they were not \n");
    strncpy(buffer, "test_string_concat_does_not_change_appended_string\n"
	    "Did not receive 0 from string_compare on appended string and control string after my_string_concat\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_string_concat_does_not_change_appended_string\n", length);
  }
  my_string_destroy(&controlString);
  my_string_destroy(&rString);
  my_string_destroy(&aString);
  return status;
}

Status test_string_extraction_matches_insertion(char* buffer, int length){
  MY_STRING iString;
  MY_STRING eString;
  Status status;
  FILE * fpw;
  FILE * fpr;
  iString = my_string_init_c_string("test");
  eString = my_string_init_default();
  
  fpw = fopen("testfile", "w");
  my_string_insertion(iString, fpw);
  fclose(fpw);
  
  fpr = fopen("testfile", "r");
  my_string_extraction(eString, fpr);
  fclose(fpr);
  
  remove("testfile");
  
  if(my_string_compare(eString, iString) != 0){
    status = FAILURE;
    printf("Expected strings to be identical, but they were not \n");
    strncpy(buffer, "test_string_extraction_matches_insertion\n"
	    "Did not receive 0 from string_compare on inserted string and extracted string after my_string_extract\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_string_extraction_matches_insertion\n", length);
  }
  my_string_destroy(&iString);
  my_string_destroy(&eString);
  return status;
}

Status test_extraction_size_increments_correctly(char* buffer, int length){
  MY_STRING iString;
  MY_STRING eString;
  Status status;
  FILE * fpw;
  FILE * fpr;
  iString = my_string_init_c_string("test");
  eString = my_string_init_default();
  
  fpw = fopen("testfile", "w");
  my_string_insertion(iString, fpw);
  fclose(fpw);
  
  fpr = fopen("testfile", "r");
  my_string_extraction(eString, fpr);
  fclose(fpr);
  
  remove("testfile");
  
  if(my_string_get_size(eString)!=4){
    status = FAILURE;
    printf("Expected a size of 4 but got %d\n", my_string_get_size(eString));
    strncpy(buffer, "test_extraction_size_increments_correctly\n"
	    "Did not receive 4 from get_size after my_string_extract\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_extraction_size_increments_correctly\n", length);
  }
  my_string_destroy(&iString);
  my_string_destroy(&eString);
  return status;
}


Status test_my_string_extraction_ignores_all_leading_whitespace(char* buffer, int length){
  MY_STRING iString;
  MY_STRING eString;
  MY_STRING controlString;
  Status status;
  FILE * fpw;
  FILE * fpr;
  iString = my_string_init_c_string("     test");
  controlString = my_string_init_c_string("test");
  eString = my_string_init_default();
  
  fpw = fopen("testfile", "w");
  my_string_insertion(iString, fpw);
  fclose(fpw);
  
  fpr = fopen("testfile", "r");
  my_string_extraction(eString, fpr);
  fclose(fpr);
  
  remove("testfile");
  
  if(my_string_compare(eString, controlString) != 0){
    status = FAILURE;
    printf("Expected string_extract to ignore leading white space but it did not \n");
    strncpy(buffer, "test_my_string_extraction_ignores_all_leading_whitespace\n"
	    "Did not receive 0 from string_compare on control string and extracted string after my_string_extract\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_my_string_extraction_ignores_all_leading_whitespace\n", length);
  }
  my_string_destroy(&iString);
  my_string_destroy(&controlString);
  my_string_destroy(&eString);
  return status;
}

Status test_string_extraction_replaces_data(char* buffer, int length){
  MY_STRING iString;
  MY_STRING eString;
  Status status;
  FILE * fpw;
  FILE * fpr;
  iString = my_string_init_c_string("test");
  eString = my_string_init_c_string("a longer test");
  
  fpw = fopen("testfile", "w");
  my_string_insertion(iString, fpw);
  fclose(fpw);

  fpr = fopen("testfile", "r");
  my_string_extraction(eString, fpr);
  fclose(fpr);

  remove("testfile");

  if(my_string_compare(eString, iString)!=0){
    status = FAILURE;
    printf("Expected string_extract to replace existing data, but it did not \n");
    strncpy(buffer, "test_string_extraction_replaces_data\n"
	    "Did not receive 0 from string_compare on inserted string and extracted string after my_string_extract\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_string_extraction_replaces_data\n", length);
  }
  my_string_destroy(&iString);
  my_string_destroy(&eString);
  return status;
}

Status test_extraction_stops_at_whitespace(char* buffer, int length){
  MY_STRING iString;
  MY_STRING eString;
  MY_STRING controlString;
  Status status;
  FILE * fpw;
  FILE * fpr;
  iString = my_string_init_c_string("test     ");
  controlString = my_string_init_c_string("test");
  eString = my_string_init_default();

  fpw = fopen("testfile", "w");
  my_string_insertion(iString, fpw);
  fclose(fpw);

  fpr = fopen("testfile", "r");
  my_string_extraction(eString, fpr);
  fclose(fpr);

  remove("testfile");

  if(my_string_compare(eString, controlString)!=0){
    status = FAILURE;
    printf("Expected string_extract to stop at white space but it did not \n");
    strncpy(buffer, "test_extraction_stops_at_whitespace\n"
	    "Did not receive 0 from string_compare on control string and extracted string after my_string_extract\n", length);
  } else {
    status = SUCCESS;
    strncpy(buffer, "test_extraction_stops_at_whitespace\n", length);
  }
  my_string_destroy(&iString);
  my_string_destroy(&controlString);
  my_string_destroy(&eString);
  return status;
}
