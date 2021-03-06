typedef void* G_VECTOR;
G_VECTOR generic_vector_init_default(Status(*item_assign)(Item_ptr, Item),void(*item_destroy)(Item_ptr));
void generic_vector_destroy(G_VECTOR* phG_Vector);
Status generic_vector_push_back(G_VECTOR hVector, Item item);
int generic_vector_get_size(G_VECTOR hVector);
int generic_vector_get_capacity(G_VECTOR hVector);
Status generic_vector_pop_back(G_VECTOR hVector);
Item generic_vector_at(G_VECTOR hVector, int index);
Status generic_vector_assignment(Item_ptr, Item);
void vector_destroy(G_VECTOR* phG_Vector);
