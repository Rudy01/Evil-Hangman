#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>

struct my_string{
  int size;
  int capacity;
  char* data;
};

typedef struct my_string My_String;

MY_STRING my_string_init_default(void){
  My_String * pMy_string;
  pMy_string = (My_String*)malloc(sizeof(My_String));
  if(pMy_string != NULL){
    pMy_string->size=0;
    pMy_string->capacity=7;
    pMy_string->data=malloc(sizeof(char)*pMy_string->capacity);
    return pMy_string;
  } else {
    free(pMy_string);
    pMy_string=NULL;
    return NULL;
  }
}

void my_string_destroy(Item* pItem){
  My_String * pMy_string = *pItem;
  free(pMy_string->data);
  free(pMy_string);
  *pItem = NULL;
  return;
}

MY_STRING my_string_init_c_string(const char* c_string){
  My_String * pMy_string;
  pMy_string = (My_String*)malloc(sizeof(My_String));
  int i = 0;
  while(c_string[i] != '\0'){
    i++;
  }
  if(pMy_string !=NULL){
    pMy_string->size = i;
    pMy_string->capacity = i+1;
    pMy_string->data=malloc(sizeof(char)*pMy_string->capacity);
    i = 0;
    while(c_string[i] != '\0'){
      pMy_string->data[i] = c_string[i];
      i++;
    }
    return pMy_string;
  } else {
    free(pMy_string);
    pMy_string=NULL;
    return NULL;
  }
}

int my_string_get_capacity(MY_STRING hMy_string){
  My_String * pMy_string = hMy_string;
  int cap = pMy_string->capacity;
  return cap;
}

int my_string_get_size(MY_STRING hMy_string){
  My_String * pMy_string = hMy_string;
  int siz = pMy_string->size;
  return siz;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string){
  My_String *pL_string = hLeft_string;
  My_String *pR_string = hRight_string;
  int i;
  if(pL_string->size > pR_string->size){
    for(i=0;i<pR_string->size; i++){
      if(pL_string->data[i] < pR_string->data[i]){
	return -1;
      }
      else
	if(pL_string->data[i] > pR_string->data[i]){
	  return 1;
	}
    }
    return 1;
  }
  else
    if(pL_string->size < pR_string->size){
      for(i = 0; i < pL_string->size; i++){
	if(pL_string->data[i] < pR_string->data[i]){
	  return -1;
	}
	else
	  if(pL_string->data[i] > pR_string->data[i]){
	    return 1;
	  }
      }
      return -1;
    } else {
      for(i = 0; i < pL_string->size; i++){
	if(pL_string->data[i] < pR_string->data[i]){
	  return -1;
	}
	else
	  if(pL_string->data[i] > pR_string->data[i]){
	    return 1;
	  }
      }
      return 0;
    }
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp){
  My_String * pMy_string = hMy_string;
  fpos_t position;
  fgetpos(fp, &position);
  int k;
  int i = 0;
  int j;
  char ch = fgetc(fp);
  char* temp = NULL;
  for(k=0;k<pMy_string->capacity; k++){
    pMy_string->data[k]='\0';
    pMy_string->size=0;
  }
  while(ch== ' '||ch == '\n'){
    ch=fgetc(fp);
  }
  while(ch != ' '){
    if(ch == EOF){
      break;
    }
    if(ch == '\n'){
      break;
    }
    fgetpos(fp, &position);
    if(pMy_string->capacity <= pMy_string->size){
      pMy_string->capacity *= 2;
      temp = (char*)malloc(sizeof(char)*pMy_string->capacity);
      if(temp == NULL){
	return FAILURE;
      }
      for(j = 0; j < pMy_string->size; j++){
	temp[j] = pMy_string->data[j];
      }
      free(pMy_string->data);
      pMy_string->data=(char*)malloc(sizeof(char)*pMy_string->capacity);
      for(j = 0; j < pMy_string->size; j++){
	pMy_string->data[j] = temp[j];
      }
      free(temp);
      temp = NULL;
    }
    pMy_string->data[i] = ch;
    pMy_string->size++;
    i++;
    ch = fgetc(fp);
  }
  fsetpos(fp, &position);
  if(pMy_string->size == 0){
    return FAILURE;
  }
  return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp){
  My_String * pMy_string = hMy_string;
  int i;
  for(i = 0; i < pMy_string->size; i++){
    fputc(pMy_string->data[i],fp);
  }
  if(pMy_string->data[0]!='\0'){
    return SUCCESS;
  }
  return FAILURE; 
}

Status my_string_push_back(MY_STRING hMy_string, char item){
  int i;
  char* temp;
  My_String * pMy_string = hMy_string;
  if(pMy_string->capacity <= pMy_string->size+2){
    pMy_string->capacity *= 2;
    temp = (char*)malloc(sizeof(char)*pMy_string->capacity);
    if(temp == NULL){
      return FAILURE;
    }
    for(i = 0; i < pMy_string->size; i++){
      temp[i] = pMy_string->data[i];
    }
    free(pMy_string->data);
    pMy_string->data=(char*)malloc(sizeof(char)*pMy_string->capacity);
    for(i = 0; i < pMy_string->size; i++){
      pMy_string->data[i] = temp[i];
    }
    free(temp);
    temp=NULL;
  }
  pMy_string->data[pMy_string->size] = item;
  pMy_string->size++;
  return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string){
  My_String * pMy_string = hMy_string;
  if (pMy_string->size <= 0){
    return FAILURE;
  }
  pMy_string->data[pMy_string->size - 1] = '\0';
  pMy_string->size--;
  return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index){
  My_String * pMy_string = hMy_string;
  if(index < 0||index >= pMy_string->size){
    return NULL;
  }
  return &pMy_string->data[index];
}

char* my_string_c_str(MY_STRING hMy_string){
  My_String * pMy_string = hMy_string;
  char* temp;
  int i;
  if(pMy_string->size >= pMy_string->capacity){
    pMy_string->capacity++;
    temp = (char*)malloc(sizeof(char)*pMy_string->capacity);
    if(temp == NULL){
      return NULL;
    }
    for(i = 0; i < pMy_string->size; i++){
      temp[i] = pMy_string->data[i];
    }
    free(pMy_string->data);
    pMy_string->data=(char*)malloc(sizeof(char)*pMy_string->capacity);
    for(i = 0; i < pMy_string->size; i++){
      pMy_string->data[i] = temp[i];
    }
    free(temp);
    temp=NULL;
  }
  pMy_string->data[pMy_string->size]='\0';
  return &pMy_string->data[0];
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend){
  My_String * pRstring = hResult;
  My_String * pAstring = hAppend;
  int i;
  for (i = 0; i < pAstring->size;i++){
    if(my_string_push_back(pRstring, my_string_at(pAstring, i)[0]) == FAILURE){
      return FAILURE;
    }
  }
  return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string){
  My_String * pMy_string = hMy_string;
  if(pMy_string->size == 0){
    return TRUE;
  }
  return FALSE;
}

Status my_string_assignment(Item* pLeft, Item Right){
  int i;
  My_String* p_Left = *pLeft;
  My_String* p_Right = Right;
  if(p_Left == NULL){
    p_Left = (My_String*)malloc(sizeof(My_String));
    if (p_Left == NULL){
      printf("FAILED\n");
      return FAILURE;
    }
    *pLeft = p_Left;
  }
  p_Left->size = p_Right->size;
  p_Left->capacity = p_Right->capacity;
  p_Left->data = malloc(sizeof(char)*(p_Left->capacity));
  for(i = 0; i < p_Right->capacity; i++){
    p_Left->data[i] = p_Right->data[i];
  }
  return SUCCESS;
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess){
  My_String * pNew_key = new_key;
  My_String * pWord = word;
  
  free(pNew_key->data);
  my_string_assignment(&new_key, current_word_family);
  
  int i = 0;

  while(pWord->data[i] != '\0'){
    if(pWord->data[i] == guess){
      pNew_key->data[i] = guess;
    }
    i++;
  }
  return SUCCESS;
}
