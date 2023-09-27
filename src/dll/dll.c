/*********************************
 * Reviewer: Nofar				
 * Author: Yohai Azoulai			
 * File: dll.c					
 * ******************************/
 
 /**/


#include <stdlib.h> /* malloc & free*/ /**nof: why? || Corrected**/
#include <assert.h> /* assert*/
#include "dll.h"

/*******Macros******/


/*******Structs******/
struct dll
{
    dll_iterator_t head;
    dll_iterator_t tail;
};

struct dll_node
{
    void *data;
    dll_iterator_t next;
    dll_iterator_t prev;
};
/*******Service Funcs******/

static int CountAction(void *list_data, void *param)
{
    assert (list_data);
    assert (param);
    (void)list_data;
    ++*(int *)param;
    return 0;
}

/*******Funcs Funcs******/

/*  psedu -> creates pointr variable dll_t , and assign memory dll struct size
            assign memory for head & tail dummy dll_node size

            dummy head                                                                            dummy tail
     | NULL || NULL  || 2 |    | 1 || x  || 3 |   | 2 || y  || 4 |     | 3 || z  || 5 |      | 4 || dlist || NULL |
                 1                    2                  3                    4                       5
    dlist->head->data = NULL;
    dlist->head->next = dlist->tail;
    dlist->head->prev = NULL;
    dlist->tail->data = dlist;
    dlist->tail->next = NULL;
    dlist->tail->prev = dlist->head;
    
    and returns pointer variable to dll (head&tail) structs (check null)
*/
dll_t *DListCreate(void)
{
    dll_t *dlist = (dll_t *)malloc(sizeof(dll_t));
    if(NULL == dlist)
    {
        return NULL;
    }

    dlist->head = (dll_iterator_t)malloc(sizeof(struct dll_node));
    if(NULL == dlist->head)
    {
        free(dlist);
        dlist = NULL;
        return NULL;
    }
    dlist->tail = (dll_iterator_t)malloc(sizeof(struct dll_node));
    if(NULL == dlist->tail)
    {
        free(dlist->head);
        dlist->head = NULL;
        free(dlist);
        dlist = NULL;
        return NULL;
    }
    
    /*intialzation both recive refrences*/    
    dlist->head->data = dlist;
    dlist->head->next = dlist->tail;
    dlist->head->prev = NULL;
    
    dlist->tail->data = dlist;
    dlist->tail->next = NULL;
    dlist->tail->prev = dlist->head;
    
    return dlist;
}

/*  psedu -> recives pointer to dll removes all nodes 
    and destroys the list removes all mallocs (free pointers)
*/
void DListDestroy(dll_t *dlist)
{
    dll_iterator_t destroyer = dlist->head;
    assert(dlist);

    while (destroyer->next)
    {
        dlist->head = destroyer->next;
        free(destroyer);
        destroyer = NULL;
        destroyer = dlist->head;
    }

    free(dlist->tail);
    dlist->tail = NULL;

    free(dlist);
    dlist = NULL;
}



/*  psedu -> recives dll_t variable calls size func and returns it
    as boolian expression return(0 == sizefunc)
*/
int DListIsEmpty(const dll_t *dlist)
{
    return(0 == DListSize(dlist));
}

/*  psedu -> return dlist->head
*/
dll_iterator_t DListBegin(const dll_t *dlist)
{
    assert(dlist);

    return dlist->head->next;
}

/*  psedu -> return dlist->tail
*/
dll_iterator_t DListEnd(const dll_t *dlist)
{
    assert(dlist);

    return dlist->tail;
}

/*  psedu -> return curr->next
*/
dll_iterator_t DListNext(dll_iterator_t curr)
{
    assert(curr);

    return curr->next;
}
/*  psedu -> return curr->prev
*/
dll_iterator_t DListPrev(dll_iterator_t curr)
{
    assert(curr);
    
    return curr->prev;
}
/*  psedu -> call the count function with an equal statment check 
    iter1 == iter2 
*/
int DListIsSameIter(dll_iterator_t first, dll_iterator_t sec)
{
    assert(first);
    assert(sec);
    
    return(first == sec);
}

/*  psedu -> curr -> data will recive the node and fetch its data with 
    casting (check which)returns void * with the data
*/
void* DListGetData(dll_iterator_t curr )
{
    assert(curr);
    
    return curr->data;
}

/*  psedu -> calls insert function and inserting an 
    node before head -> copying head into new node,
    and reassigning the dlist head refrence
    curr->prev->data->head = new_node
    assign data into old head with new data
*/
dll_iterator_t DListPushFront(dll_t *dlist, void *data)
{
    assert(dlist);
    assert(data);
    return DListInsert(dlist,DListBegin(dlist),data);
}

/*  psedu -> calls insert function and inserting an 
    node with DLLEnd as location past tail
     -> copying tail into new node,
    and reassigning the dlist tail refrence
    curr->data->tail = new_node
    assign data into old tail with new data
*/
dll_iterator_t DListPushBack(dll_t *dlist, void *data)
{
    assert(dlist);
    assert(data);
    return DListInsert(dlist,DListEnd(dlist),data);
}

/*  psedu -> call remove with DLLBegin as curr location
    removes head->next while head->next != NULL
*/
void *DListPopFront(dll_t *dlist)
{
    void *fetch_data = DListGetData(DListBegin(dlist));
    assert(dlist);
    DListRemove(DListBegin(dlist));
    return fetch_data;
}

/*  psedu -> call remove with DLLEnd as curr location
    removes head->next while head->next != NULL
*/
void *DListPopBack(dll_t *dlist)
{
    void *fetch_data = DListGetData(DListPrev(DListEnd(dlist)));
    assert(dlist);
    DListRemove(DListPrev(DListEnd(dlist)));
    return fetch_data;
}

/*  psedu -> 
*/
dll_iterator_t  DListInsert(dll_t *dlist ,dll_iterator_t curr, void *data)
{
    dll_iterator_t new_node = (dll_iterator_t)malloc(sizeof(struct dll_node));
    assert(curr);
    assert(data);
    
    
    
    if(!new_node)
    {
        free(new_node);
        new_node = NULL;
        return DListEnd(dlist);
    }

    new_node->data = data;
    new_node->next = curr;
    new_node->prev = curr->prev;
    curr->prev->next = new_node;
    curr->prev = new_node;

    return new_node;   
}
/*  psedu -> this function recives a location and removes current node!
            returns iterator to next valid.if tail return EOL
*/
dll_iterator_t DListRemove(dll_iterator_t curr)
{
    dll_iterator_t next_node = curr->next;
    assert(curr);

    curr->next->prev = curr->prev;
    curr->prev->next = curr->next;
    
    free(curr);
    curr = NULL;

    return next_node;
}
/*  psedu -> 
*/
dll_iterator_t DListSplice(dll_iterator_t where, dll_iterator_t begin,
                                                 dll_iterator_t end)
{   

    dll_iterator_t where_prev = where->prev;
    assert(where);
    assert(begin);
    assert(end);

    where->prev->next = begin;
    begin->prev->next = end;
    end->prev->next = where;
    where->prev = end->prev;
    end->prev = begin->prev;
    begin->prev = where_prev;

    return where_prev;

}
/*  psedu -> 
*/
int DListForEach(dll_iterator_t from, dll_iterator_t to, 
    void *param, action_func_t action_func) /**nof: you can unite the
     conditions at if + while inside the while , maybe you will need kind of flag
            || tried using same logic as FIND didnt work, need to think 
                    further**/
{
    int count = 0;
    assert(from);
    assert(to);
    assert(param);
    assert(action_func);
    
    while(from != to && !action_func(from->data,param))
    {
        from = DListNext(from);
        ++count;
    }

    if (DListIsSameIter(from, to))
    {
        return count;
    }
    return 0;

}

/*  recives dll_t variable and runs on all nodes
    while not zero increment count (use extra func? for each?)
*/
size_t DListSize(const dll_t * dlist)
{
    size_t count = 0;
    assert (dlist);

    DListForEach(DListBegin((dll_t *)dlist),
     DListEnd((dll_t *)dlist), &count, CountAction);
        
    return count;
}

/*  psedu -> 
*/
dll_iterator_t DListFind(dll_iterator_t from, dll_iterator_t to,
                                     const void *data, is_match_t func) /**nof: same as for each **/
{
    assert(from);
    assert(to);
    assert(data);
    assert(func);
    /* Corrected if into while*/
    while(!DListIsSameIter(from,to) && !func(DListGetData(from),data))
    {
        from = DListNext(from);
    }

    if (!from)
    {
        return from;
    }
    
    
    return from;

}       
/*  psedu -> 
*/
int DListMultiFind(dll_iterator_t from, dll_iterator_t to, dll_t *dlist_dest,
    const void *param, is_match_t func)
{
    dll_iterator_t curr = from;
    dll_iterator_t found= DListFind(curr, to, param, func);
    assert(from);
    assert(to);
    assert(param);
    assert(func);
    
    while(!DListIsSameIter(to, found))
    {
        if(DListIsSameIter(DListInsert(dlist_dest,
                           DListEnd(dlist_dest),
                           DListGetData(found)),
                           DListEnd(dlist_dest)))
            {
                return 1;
            }
        
    curr = DListNext(found);
    found = DListFind(curr, to, param, func);
    }
    return 0;
}


