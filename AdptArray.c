
#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"

typedef struct AdptArray_ {
    int size_arr;
    COPY_FUNC copy;
    DEL_FUNC del;
    PRINT_FUNC pri;
    PElement *ptr;
}  PAdpt, * PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC c_f, DEL_FUNC d_f,PRINT_FUNC p_f){
    PAdptArray arrp = (PAdptArray )malloc(sizeof(PAdpt) + sizeof(PElement));
    arrp->copy = c_f;
    arrp-> del = d_f;
    arrp->pri = p_f;
    arrp->size_arr = 0;
    arrp->ptr = (PElement *)malloc(sizeof(PElement));
    return arrp;
}
void DeleteAdptArray(PAdptArray pa_arr){
    for(int i = 0; i < pa_arr->size_arr; i++){
        if(pa_arr->ptr[i] != NULL) pa_arr->del(pa_arr->ptr[i]);
    }
    free(pa_arr->ptr);
    free(pa_arr);
}
Result SetAdptArrayAt(PAdptArray pa_arr, int index, PElement elmo){
    if(index > pa_arr->size_arr) {
        int new_size = index+1;             //expanding size to index+1
        pa_arr->ptr = (PElement *)realloc(pa_arr->ptr ,sizeof(PElement)* new_size);
        for(int i =pa_arr->size_arr; i < new_size; i++){
            pa_arr->ptr[i] = NULL;                              // preventing garbage values
        }
        pa_arr->size_arr = new_size;
    }
    else if(pa_arr->ptr[index] != NULL){
        pa_arr->del(pa_arr->ptr[index]);
    }
    pa_arr->ptr[index] = pa_arr->copy(elmo);
    if(pa_arr->ptr[index] == NULL) return FAIL;
    else return SUCCESS;
}
PElement GetAdptArrayAt(PAdptArray pa_arr, int index){
    
    if(index >= pa_arr->size_arr) return NULL;
    if(pa_arr->ptr[index] == NULL) return NULL;
    else return pa_arr->copy(pa_arr->ptr[index]);
}
int GetAdptArraySize(PAdptArray pa_arr){
    //if ptr=null return -1
    if(pa_arr == NULL) return -1;
    if(pa_arr->ptr == NULL) return -1;
    else return pa_arr->size_arr;
}
void PrintDB(PAdptArray pa_arr){
    int i;
    PElement tmp;
    int size_arr = GetAdptArraySize(pa_arr);
    for(i =0; i < size_arr; i++){
        tmp = pa_arr->ptr[i];
        if(tmp != NULL) pa_arr->pri(tmp);

    }
}
