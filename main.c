#include "my_string.h"

void clear_keyboard_buffer(void);
int main(int argc, char* argv[]){
  int length, guesses, wrong, i, j, iterations;
  char guess, rt;
  G_VECTOR arr[30];
  G_VECTOR keys, tempStringVector, wordBank, maxKey;
  MY_STRING hLetters;
  MY_STRING hMy_string = NULL;
  MY_STRING hCurrent_key = NULL;
  MY_STRING hNew_key = NULL;
  FILE* fp=fopen("dictionary.txt", "r");
  Boolean playing = TRUE;
  Boolean winner, validLength, validGuesses, runningTotal, validTotal, validPlay, validGuess, foundKey;
  
  hMy_string = my_string_init_default();
  for (i = 0; i < 30; i++){
    arr[i] = generic_vector_init_default(my_string_assignment, my_string_destroy);
  }

  while(my_string_extraction(hMy_string, fp)){
    generic_vector_push_back(arr[my_string_get_size(hMy_string)],hMy_string);
  }
  my_string_destroy(&hMy_string);
  fclose(fp);
  
  while(playing == TRUE){
    iterations = 0;
    wrong = 0;
    validLength = FALSE;
    validGuesses = FALSE;
    validTotal = FALSE;
    winner = FALSE;
    hLetters = my_string_init_default();
    while(validLength != TRUE){
      printf("What length word would you like to play with? ");
      scanf("%d", &length);
      clear_keyboard_buffer();
      if(generic_vector_get_size(arr[length]) == 0){
        printf("\nInvalid word length, please select a different length.");
      } else {
        validLength = TRUE;
        hCurrent_key = my_string_init_default();
        wordBank = generic_vector_init_default(my_string_assignment, my_string_destroy);
        for(i = 0; i < generic_vector_get_size(arr[length]); i++){
          generic_vector_push_back(wordBank, generic_vector_at(arr[length],i));
        }
        for(i = 0; i < length; i++){
          my_string_push_back(hCurrent_key, '-');
        }
      }
    }
    while(validGuesses != TRUE){
      printf("\nHow many guesses would you like to have? ");
      scanf("%d", &guesses);
      clear_keyboard_buffer();
      if(guesses <= 0){
        printf("\nInvalid number of guesses, please select a different number of guesses.");
      } else {
        validGuesses = TRUE;
      }
    }
    while(validTotal == FALSE){
      printf("\nWould you like a running total? (Y/N) ");
      scanf("%c", &rt);
      clear_keyboard_buffer();
      rt = tolower(rt);
      if(rt == 'y'){
        runningTotal = TRUE;
        validTotal = TRUE;
      } else
	if(rt == 'n'){
	  runningTotal = FALSE;
	  validTotal = TRUE;
	} else {
	  printf("\nPlease input y for yes or n for no." );
	}
    }
    
    while(wrong < guesses){
      winner = TRUE;
      for(i = 0; i < my_string_get_size(hCurrent_key); i++){
        if(*my_string_at(hCurrent_key,i) == '-'){
          winner = FALSE;
        }
      }
      if(winner == TRUE){
        break;
      }
      keys = generic_vector_init_default(generic_vector_assignment, vector_destroy);
      iterations++;
      printf("\nYou have %d guesses left\n", (guesses - wrong));
      printf("Used letters: %s\n", my_string_c_str(hLetters));
      printf("Word: ");
      my_string_insertion(hCurrent_key, stdout);
      printf("\n");
      validGuess = FALSE;
      while(validGuess == FALSE){
        printf("Enter guess: ");
        scanf("%c", &guess);
        clear_keyboard_buffer();
        if(isalpha(guess) != 0){
          validGuess = TRUE;
          for(i = 0; i < my_string_get_size(hLetters); i++){
            if(guess == *my_string_at(hLetters,i)){
              printf("The letter %c has already been guessed\n", guess);
              validGuess = FALSE;
            }
          }
        }
      }
      my_string_push_back(hLetters, guess);
      
      for(i = 0; i < generic_vector_get_size(wordBank); i++){
        hNew_key = my_string_init_default();
        get_word_key_value(hCurrent_key, hNew_key, generic_vector_at(wordBank, i), guess);
        foundKey = FALSE;
        j = 0;

        while(j < generic_vector_get_size(keys) && foundKey == FALSE){
          if(my_string_compare(hNew_key,generic_vector_at(generic_vector_at(keys,j), 0)) == 0){
            generic_vector_push_back(generic_vector_at(keys, j),generic_vector_at(wordBank, i));
            foundKey = TRUE;
          } else {
            j++;
          }
        }
        if(foundKey == FALSE){
          tempStringVector = generic_vector_init_default(my_string_assignment, my_string_destroy);
          generic_vector_push_back(keys, tempStringVector);
          generic_vector_push_back(generic_vector_at(keys, generic_vector_get_size(keys)-1), hNew_key);
          generic_vector_push_back(generic_vector_at(keys, generic_vector_get_size(keys)-1), generic_vector_at(wordBank, i));
          generic_vector_destroy(&tempStringVector);
        }
        my_string_destroy(&hNew_key);
      }
      if(runningTotal == TRUE){
        for(i = 0; i < generic_vector_get_size(keys); i++){
          printf("%s: %d\n", my_string_c_str(generic_vector_at(generic_vector_at(keys,i), 0)), generic_vector_get_size(generic_vector_at(keys, i)) - 1);
        }
      }
      maxKey = generic_vector_at(keys,0);
      for(i = 1; i < generic_vector_get_size(keys); i++){
        if(generic_vector_get_size(maxKey) < generic_vector_get_size(generic_vector_at(keys, i))){
          maxKey = generic_vector_at(keys, i);
        }
      }
      if(my_string_compare(generic_vector_at(maxKey, 0), hCurrent_key) == 0){
        wrong++;
      }
      my_string_destroy(&hCurrent_key);
      my_string_assignment(&hCurrent_key,generic_vector_at(maxKey, 0));
      generic_vector_destroy(&wordBank);
      wordBank = generic_vector_init_default(my_string_assignment, my_string_destroy);
      for(i = 1; i < generic_vector_get_size(maxKey); i++){
        generic_vector_push_back(wordBank, generic_vector_at(maxKey, i));
      }
      generic_vector_destroy(&keys);
    }
    if(winner == FALSE){
      printf("you have lost\n");
      printf("the word was :%s\n", my_string_c_str(generic_vector_at(wordBank,0)));
    } else {
      printf("you have won\n");
      printf("the word was :%s\n", my_string_c_str(hCurrent_key));
    }
    generic_vector_destroy(&wordBank);
    my_string_destroy(&hCurrent_key);
    my_string_destroy(&hLetters);
    validPlay = FALSE;
    while(validPlay == FALSE){
      printf("would you like to play again? (Y/N)\n");
      scanf("%c", &rt);
      clear_keyboard_buffer();
      rt = tolower(rt);
      if(rt == 'y'){
        validPlay = TRUE;
      } else
	if(rt == 'n'){
	  playing = FALSE;
	  validPlay = TRUE;
	} else {
	  printf("\nPlease input y for yes or n for no. " );
	} 
    }
  }
  for (i = 0; i < 30; i++){
    generic_vector_destroy(&arr[i]);
  }
  return 0;
}

void clear_keyboard_buffer(void){
  char c;
  scanf("%c", &c);
  while (c != '\n'){
    scanf("%c", &c);
  }
}
