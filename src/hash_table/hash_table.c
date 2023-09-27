/*********************************
 * Reviewer: Sarah Toledano				
 * Author: Yohai Azoulai			
 * File: hash_table.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/
#include <stdio.h> /*hash print printf*/

#include "dll.h"
#include "hash_table.h"
/*******Defines******/



/*******Structs******/

struct hash_node
{
    dll_t *dll;
};

typedef struct hash_node hash_node_t;

struct hash
{
    /*provides the key for Hash[index]*/
    hash_func_t scramble_func_ptr;
    /*to find the correct node in dll*/
    hash_is_match_t match_funct_ptr;
    size_t table_size;
    hash_node_t hash_dll_list[1];
};

/*******Service Funcs******/

static int Size(void *hash_data, void *count);
int GetIndex(hash_t *hash, const void *data);


/*******Funcs Funcs******/



hash_t *HashCreate(hash_is_match_t is_match_func,
				   hash_func_t hash_func,
                   size_t table_size)
{
    hash_t *hash_table = NULL;
    size_t index = 0;
    int removal_counter = 0;
    

    assert(is_match_func);
    assert(hash_func);

    hash_table = (hash_t *)malloc(offsetof(hash_t,hash_dll_list) + table_size * sizeof(hash_node_t));
    if (!hash_table)
    {
        return NULL;
    }


    for(index = 0; index < table_size; ++index)
    {
        (hash_table->hash_dll_list +index)->dll = DListCreate();
        if(NULL == (hash_table->hash_dll_list +index)->dll)
        {
            for(removal_counter = index;0 < removal_counter; --removal_counter)
            {
                DListDestroy((hash_table->hash_dll_list +
                                            removal_counter)->dll);
            }
            
            hash_table->match_funct_ptr = NULL;
            hash_table->scramble_func_ptr = NULL;
            hash_table->table_size = 0;
            
            free(hash_table);
            hash_table = NULL;

            return NULL;
        }
    }

    hash_table->table_size = table_size;
    hash_table->match_funct_ptr = is_match_func;
    hash_table->scramble_func_ptr = hash_func;
    return hash_table;

}
/**************************************************************/                    
void HashDestroy(hash_t *hash)
{
    size_t index = 0;
    
    assert(hash);
    
    for (index = 0; index < hash->table_size ; ++index)
    {
        DListDestroy((hash->hash_dll_list + index)->dll);
    }
    
    free(hash);
    hash = NULL;
}
/**************************************************************/

size_t HashSize(hash_t *hash)
{
    size_t size = 0;

    assert (hash);
    
    HashForEach(hash,Size,&size);

    return size;
}
/**************************************************************/

int HashIsEmpty(hash_t *hash)
{
    size_t i = 0;
    
    assert(hash);
    

    for (i = 0; i < hash->table_size && DListIsEmpty(
                                            (hash->hash_dll_list + i)->dll)
                                            ; i++);
    
    
    return(i == hash->table_size);
}
/**************************************************************/

int HashInsert(hash_t *hash, const void *data)
{
    dll_iterator_t insert_result_iter = NULL;
    int scrambled_index = 0;

    assert(hash);

    scrambled_index = GetIndex(hash,data);
    insert_result_iter = DListPushFront((hash->hash_dll_list +
                                            scrambled_index)->dll,
                                            (void *)data);

    if(!insert_result_iter)
    {
        return 1;
    }

    return 0;
    
}
/**************************************************************/

void HashRemove(hash_t *hash, void *data)
{
    int scrambled_index = 0;

    assert(hash);

    scrambled_index = GetIndex(hash,data);

    DListRemove(
            DListFind(
                DListBegin((hash->hash_dll_list + scrambled_index)->dll),
                DListEnd((hash->hash_dll_list + scrambled_index)->dll),
                (void *)data,
                hash->match_funct_ptr)
                );


}
/**************************************************************/

void *HashFind(hash_t *hash, const void *data)
{
    int scrambled_index = 0;
    dll_iterator_t checker = NULL;

    assert(hash);

    scrambled_index = GetIndex(hash,data);

    checker = DListFind(
                        DListBegin((hash->hash_dll_list + scrambled_index)->dll),
                        DListEnd((hash->hash_dll_list + scrambled_index)->dll),
                        (void *)data,
                        hash->match_funct_ptr);

    if(DListIsSameIter(checker,DListEnd((hash->hash_dll_list + scrambled_index)->dll)))
    {
        return NULL;
    }
    

    return DListGetData(checker);
                ;
    


}
/**************************************************************/

int HashForEach(hash_t *hash, hash_action_func_t action_func, void *param)
{
    size_t i = 0;
    int result = 0;

    assert(hash);

    for (i = 0; i < hash->table_size ; i++)
    {
        result += DListForEach(DListBegin((hash->hash_dll_list + i)->dll),
                        DListEnd((hash->hash_dll_list + i)->dll),
                        param,
                        action_func);
    }


    return result;


}
/**************************************************************/


/**************************************************************/
static void PrintIntDLL(dll_t *dll,int size)
{
    dll_iterator_t itr=DListBegin(dll);
    int i=0;
    
    printf("dlist: ");
    for(i=0;i<size;++i)
    {
        printf("%lu,",*(size_t*)DListGetData(itr));
        itr=DListNext(itr);
    }
    printf("\n");
}
/**************************************************************/
void PrintTable(hash_t *hash_table)
{
    size_t  i=0;
    for(; i < hash_table->table_size; ++i)
    {
        printf("index %ld\n",i);
        PrintIntDLL((hash_table->hash_dll_list[i]).dll,
                        DListSize((hash_table->hash_dll_list[i]).dll));
    }
}
/**************************************************************/


static int Size(void *hash_data, void *count)
{
    *(size_t *)count += 1;
    (void)hash_data;

    return 0;
}

int GetIndex(hash_t *hash, const void *data)
{
    return hash->scramble_func_ptr((void *)data) % hash->table_size;
}