#include "my_string.h"

struct generic_vector{
  int size;
  int capacity;
  Item_ptr data;
  Status(*item_assign)(Item_ptr, Item);
  void(*item_destroy)(Item_ptr);
};

typedef struct  generic_vector G_Vector;
G_VECTOR generic_vector_init_default(
				     Status (*item_assign)(Item_ptr, Item),
				     void(*item_destroy)(Item_ptr))
{
  G_Vector* pVector;
  pVector = (G_Vector*)malloc(sizeof(G_Vector));
  int i;
  if (pVector != NULL){
    pVector->size = 0;
    pVector->capacity = 1;
    pVector->item_destroy = item_destroy;
    pVector->item_assign = item_assign;
    pVector->data = (void**)malloc(sizeof(void*)*pVector->capacity);
    if (pVector->data == NULL){
      free(pVector);
      pVector = NULL;
    } else {
      for (i = 0; i < pVector->capacity; i++){
	pVector->data[i] = NULL;
      }
    }
  }
  return pVector;
}

void generic_vector_destroy(G_VECTOR* phG_Vector){
  G_Vector* pVector = (G_Vector*)*phG_Vector;
  int i;
  for (i = 0; i < pVector->capacity; i++){
    if (pVector->data[i] != NULL){
      pVector->item_destroy(&pVector->data[i]);
    }
  }
  free(pVector->data);
  free(pVector);
  *phG_Vector = NULL;
}

Status generic_vector_push_back(G_VECTOR hVector, Item item){
  G_Vector* pVector = (G_Vector*)hVector;
  Item_ptr temp;
  int i;
  if (pVector->size >= pVector->capacity){
    temp = (Item_ptr)malloc(sizeof(Item) * 2 * pVector->capacity);
    if (temp == NULL){
      return FAILURE;
    }
    pVector->capacity *= 2;
    for (i = 0; i < pVector->size; i++){
      temp[i] = pVector->data[i];
    }
    for (i = pVector->size;i < pVector->capacity; i++){
      temp[i] = NULL;
    }
    free(pVector->data);
    pVector->data = temp;
  }
  pVector->item_assign(&pVector->data[pVector->size], item);
  pVector->size++;
  
  return SUCCESS;
}

Status generic_vector_pop_back(G_VECTOR hVector){
  G_Vector* pVector = (G_Vector*)hVector;
  if (pVector->size <= 0){
    return FAILURE;
  }
  pVector->size--;
  return SUCCESS;
}

Item generic_vector_at(G_VECTOR hVector, int index){
  G_Vector* pVector = (G_Vector*)hVector;
  if (index < 0 || index >= pVector->size){
    return NULL;
  }
  return pVector->data[index];
}

int generic_vector_get_size(G_VECTOR hVector){
  G_Vector* pVector = (G_Vector*)hVector;
  return pVector->size;
}

int generic_vector_get_capacity(G_VECTOR hVector){
  G_Vector* pVector = (G_Vector*)hVector;
  return pVector->capacity;
}

Status generic_vector_assignment(Item_ptr phVector, Item hVector){
  G_Vector* pLeft = *phVector;
  G_Vector* pRight = hVector;
  int i;
  if (pLeft == NULL){
    pLeft = (G_Vector*)malloc(sizeof(G_Vector));
    if (pLeft == NULL){
      printf("FAILED\n");
      return FAILURE;
    }
    *phVector = pLeft;
  }
  pLeft->size = pRight->size;
  pLeft->capacity = pRight->capacity;
  pLeft->data = (void**)malloc(sizeof(void*)*pLeft->capacity);
  for(i = 0; i < pRight->capacity; i++){
    pLeft->data[i] = pRight->data[i];
  }
  pLeft->item_assign = pRight->item_assign;
  pLeft->item_destroy = pRight->item_destroy;
  return SUCCESS;
}

void vector_destroy(Item_ptr phG_Vector){
  G_Vector* pVector = (G_Vector*)*phG_Vector;
  int i;
  for (i = 0; i < pVector->size; i++){
    pVector->item_destroy(&pVector->data[i]);
  }
  free(pVector->data);
  free(pVector);
  *phG_Vector = NULL;
}
