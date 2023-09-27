/*********************************
 * Reviewer: 				
 * Author: Yohai Azoulai			
 * File: heap.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/
#include <string.h> /*memcpy*/
#include <sys/types.h> /*ssize_t in remove*/

#include "heap.h"
#include "vector.h"
/*******Defines******/



/*******Structs******/

struct heap
{
    vector_t *vector;
    void *user_parm;
    heap_is_less_func_t comp_func_ptr;
};

/*******Service Funcs******/

static void SwappingFunc(
                    void *a_data, 
                    void *b_data, 
                    size_t elem_size);
static void HeapiffyUp(heap_t *heap,int index);

static void HeapiffyDown(heap_t *heap, int index_parent);

static int IndexParent(int index);

static int WhichChild(heap_t *heap,int parent_index);

static int WhereIsChildIter(
                    heap_t *heap,
                    int parent_index,
                    void *data, 
                    heap_is_match_func_t is_match, 
                    void *user_param);

/* static int InExistance(heap_t *heap, int parent_index);
 */
static int GiveLeftChild(int parent_index);

static int GiveRightChild(int parent_index);

/*******Funcs Funcs******/


heap_t *HeapCreate(heap_is_less_func_t comp_ptr,void *user_param)
{
    heap_t *heap_list = NULL;
    
    assert(comp_ptr);


    heap_list  = (heap_t *)malloc(sizeof(heap_t));

    heap_list->vector = VectorCreate(1,sizeof(void *));
    heap_list->user_parm = user_param;
    heap_list->comp_func_ptr = comp_ptr;
    return heap_list;

}

void HeapDestroy(heap_t *heap)
{
    assert(heap);
    VectorDestroy(heap->vector);
    heap->vector = NULL;
    free(heap);
    heap = NULL;
}

size_t HeapSize(heap_t *heap)
{
    assert(heap);
    return VectorSize(heap->vector);
}

int HeapIsEmpty(heap_t *heap)
{
    assert(heap);
    return VectorIsEmpty(heap->vector);
}

void *HeapPeek(heap_t *heap)
{
    assert(heap);
    return ((void *)*(size_t *)VectorGetAccess(heap->vector,0));
}

int HeapPush(heap_t *heap, const void *data)
{
    assert(heap);
    if(VectorPush(heap->vector,&data))
    {
        return 1;
    }
    if(1 < HeapSize(heap))
    {
        HeapiffyUp(heap , HeapSize(heap)-1);
    }

    return 0;
}


void HeapPop(heap_t *heap)
{
    void *vec =NULL, *last = NULL;
    size_t size = HeapSize(heap)-1;

    assert(heap);

    vec = VectorGetAccess(heap->vector , 0);
    last = VectorGetAccess(heap->vector, size);

    SwappingFunc(vec ,last, sizeof(void *));

    VectorPop(heap->vector);
    HeapiffyDown(heap,0);   
}


void *HeapRemove(heap_t *heap, const void *data, heap_is_match_func_t is_match, void *user_param)
{

    ssize_t index = 0;
    void* return_ptr = NULL;

    assert(heap);
    assert(data);
    assert(is_match);

    index = WhereIsChildIter(
                                heap,
                                0,
                                (void *)data,
                                is_match,
                                user_param);
  
    if(index != -1)
    {
        void **last = VectorGetAccess(heap->vector , VectorSize(heap->vector)-1),
            **to_remove = VectorGetAccess(heap->vector, index);
        return_ptr = *to_remove;
        SwappingFunc(last, to_remove,sizeof(void *));
        VectorPop(heap->vector);
        if(HeapSize(heap) > 1)
        {   
            HeapiffyDown(heap, index);
        }    
    }

    return return_ptr;

}



/* 
void *HeapRemove(heap_t *heap,
                const void *data,
                heap_is_match_func_t is_match,
                void *user_param)
{
    int child_index = 0;
    void *removed_data = NULL;
    
    assert(heap);

    child_index = WhereIsChildIter(
                                heap,
                                0,
                                (void *)data,
                                is_match,
                                user_param);
    removed_data = *VectorGetAccess(heap->vector,child_index);

    if (-1 != child_index)
    {
        VectorPop(heap->vector);
        HeapiffyDown(heap,child_index);
        return removed_data;
    }
    return NULL;    
} */

/*******Service Funcs******/


static void SwappingFunc(
                    void *a_data, 
                    void *b_data, 
                    size_t elem_size)
{
    void *tmp_buffer = malloc(sizeof(void *));                 
    
    memcpy(tmp_buffer, a_data, elem_size);
	memcpy(a_data, b_data, elem_size);
	memcpy(b_data, tmp_buffer, elem_size);
    free(tmp_buffer);
}


static void HeapiffyUp(heap_t *heap,int index)
{
    void *child_ptr = NULL;
    void *parent_ptr = NULL;
    int index_child = 0 , index_parent = 0;
    
    assert(heap);

    index_child  = index;
    index_parent = IndexParent(index_child);
    
    child_ptr = VectorGetAccess(heap->vector,index_child);
    parent_ptr = VectorGetAccess(heap->vector,index_parent);

    while(0 != index_child
                    && 
                    heap->comp_func_ptr(
                        (void *)*(size_t *)child_ptr,
                        (void *)*(size_t *)parent_ptr,
                        heap->user_parm))
    {
        SwappingFunc(child_ptr,parent_ptr,sizeof(void *));
        index_child = index_parent;
        index_parent = IndexParent(index_child);
        child_ptr = VectorGetAccess(heap->vector,index_child);
        parent_ptr = VectorGetAccess(heap->vector,index_parent);
    }
}

static void HeapiffyDown(heap_t *heap, int index_parent)
{
    void *child_ptr = NULL;
    void *parent_ptr = NULL;
    int index_child = 0;
    
    assert(heap);

    index_child  = HeapSize(heap);
    
    child_ptr = VectorGetAccess(heap->vector,index_child);
    parent_ptr = VectorGetAccess(heap->vector,index_parent);

    /* SwappingFunc(child_ptr,parent_ptr,sizeof(void *)); */
    /* parent_ptr = VectorGetAccess(heap->vector,index_parent); */
    /***TRUE is Bigger in Heirarchy 
     *      1 before ***/
    

    while ((int)HeapSize(heap) > GiveRightChild(index_parent))
    {
        index_child = WhichChild(heap,index_parent);
        child_ptr = VectorGetAccess(heap->vector,index_child);
        SwappingFunc(child_ptr,parent_ptr,sizeof(void *));
        index_parent = index_child;
        parent_ptr = VectorGetAccess(heap->vector,index_parent);
    }
    
    if ((int)HeapSize(heap) > GiveLeftChild(index_parent))
    {
        
        index_child = GiveLeftChild(index_parent);
        child_ptr = VectorGetAccess(heap->vector,index_child);
        SwappingFunc(child_ptr,parent_ptr,sizeof(void *));
        index_parent = index_child;
    } 
    
    HeapiffyUp(heap,index_parent);
    
    

}

static int IndexParent(int index)
{
    return (index - 1)/2;
}

static int GiveLeftChild(int parent_index)
{
    return (2*parent_index + 1);
}

static int GiveRightChild(int parent_index)
{
    return (2*parent_index + 2);
}

 static int WhichChild(heap_t *heap,int parent_index)
{
    int left_index = 0;
    int right_index = 0;
    void *left_child = NULL;
    void *right_child = NULL;

    int result_index = 0;

    left_index = GiveLeftChild(parent_index);
    right_index = GiveRightChild(parent_index);

    left_child = VectorGetAccess(heap->vector,left_index);
    right_child = VectorGetAccess(heap->vector,right_index);
    
    if (right_index < (int)HeapSize(heap))
    {
        result_index = heap->comp_func_ptr(
                    (void *)*(size_t*)left_child,
                    (void *)*(size_t*)right_child,heap->user_parm);
        if (1 == result_index)
        {
            return left_index;
        }
        else
        {
            return right_index;
        }
    }
    
    if (left_index < (int)HeapSize(heap))
    {
        return left_index;
    }
    return parent_index;
    
}
  

static int WhereIsChildIter(
                    heap_t *heap, 
                    int parent_index,
                    void *data, 
                    heap_is_match_func_t is_match, 
                    void *user_param)
{
    
    void **parent = NULL;
    size_t i = 0;
    
    assert(heap);

  	parent = VectorGetAccess(heap->vector,parent_index);

    for (i = 0; i < VectorSize(heap->vector); ++i)
    {
        parent_index = i;
        parent = VectorGetAccess(heap->vector,parent_index);
        if (is_match(*parent,data,user_param))
        {
            return parent_index;
        }
    }
    return -1;

}
/*
static int InExistance(heap_t *heap, int parent_index)
{
    int res = 0;
    assert(heap);
    res = (int)VectorSize(heap->vector) - (parent_index);
    
    return(0 < res);
}
*/
