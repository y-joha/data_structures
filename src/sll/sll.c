/*********************************
 * Reviewer: Avigail				
 * Author: Yohai Azoulai			
 * File: sll.c					
 * ******************************/

#include <stdlib.h> /*size_t, malloc & free |Corrected| CR: ALSO MALLOC AND FREE*/
#include <stdio.h>  /*printf*/
#include <assert.h> /* Assert */
#include "sll.h"
/*CR: add stddef for size_t || found in .h because it has size_t in the definitions*/


struct node
{
    void *data;
    struct node *next;
};

struct sll
{
    node_t *head;
    node_t *tail;
};

/*Service Functions*/
int ActionInt(sll_iterator_t curr, void *param);
int SetStr(sll_iterator_t curr, void *param);
int ActionCount(sll_iterator_t curr, void *param);




/*Main event*/


sll_t *SLLCreate()
{
    sll_t *slist = (sll_t *)malloc(sizeof(sll_t));
    if(NULL == slist)
    {
        printf("Couldnt allocated memory for SLLCreate (no head/tail)\n");
        return NULL;
    }
    slist->tail = (node_t *)malloc(sizeof(node_t));
    if(NULL == slist->tail)
    {
        printf("Couldnt allocated memory for tail SLLCreate no mem for tail\n");
        free(slist);
        return NULL;
    }
    	
    slist->head = slist->tail;
    slist->tail->data = slist;
    slist->tail->next = NULL;
    
    return slist;
}

sll_iterator_t SLLBegin(sll_t *slist)
{
    assert(slist);
    
    return slist->head;
}

sll_iterator_t SLLEnd(sll_t *slist)
{
    assert(slist);
    
    return slist->tail;
}

sll_iterator_t SLLNext(sll_iterator_t curr)
{
    assert(curr);
    return curr->next;
}

void *SLLGet(sll_iterator_t curr)
{
    assert(curr);
    
    return curr->data;
}

void SLLSetData(sll_iterator_t curr, void *data)
{
    assert(curr);
    assert(data);
    
    curr->data = data;
}

int SLLIteratorsIsEqual(sll_iterator_t iter1, sll_iterator_t iter2)
{
    assert(iter1);
    assert(iter2);
    
    return(iter1 == iter2);
    /*Corrected*/
    /*CR: drop the condition, return the expression as is. also karam said to check the pointers not the data*/
}

sll_iterator_t SLLInsert(sll_iterator_t curr, void *new_data)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    assert(curr);
    assert(new_data);
    
    if(NULL == new_node)
    {
        puts("Malloc allocation failed");/*CR: return the tail when fail |Corrected|*/
        return SLLEnd((sll_t*)curr->data);
    }
    
    if(NULL == curr->next)
/*CR: same logic as remove |Disccussed|-> after reviewing both together the
    code i explaing how in the insert i stem from dummy as opposed to 
    remove which i condence into the dummy which is why i can i change the code 
    for the remove but not the write*/
    {
        ((sll_t*)curr->data)->tail = new_node;
        new_node->data = curr->data;
        curr->data = new_data;
        curr->next = new_node;
        new_node->next = NULL;

        return curr;
    }

    new_node->next = curr->next;
    new_node->data = new_data;
    curr->next = new_node;


    return curr;    
}

sll_iterator_t SLLRemove(sll_iterator_t curr)
{
    node_t *next_curr;

    assert(curr);
    
    next_curr = curr->next;

    /*did i get the dummy?*/
    if(NULL == next_curr)
    {
        return curr;
    }
    /*am i not at dummy?*/

    curr->data = next_curr->data;
    curr->next = next_curr->next;

    free(next_curr);/*CR: add next_curr=NULL; |Corrected|*/
    next_curr=NULL;
    
    if(NULL == next_curr->next)
    {/*CR: this lines repeats themselfs later you can spare them. the only difference is the tail asignment*/
        ((sll_t*)curr->data)->tail = curr;
        return curr;
    }
    
    return curr;
}


/*CR improvment*/
/*size_t SLLCount(const sll_t *slist)
{
    size_t count_node = 0;
    node_t *tmp_ptr;
    assert(slist);

    tmp_ptr = slist->head;
    tmp_ptr = tmp_ptr->next;
    
    while(NULL != tmp_ptr)
    {
        ++count_node;
        tmp_ptr = tmp_ptr->next;
    }
    
    tmp_ptr = NULL;

    return count_node;
}
*/
size_t SLLCount(const sll_t *slist)/*CR: very cool ^^ */
{
    size_t count = 0;
    assert (slist);

    SLLForEach (SLLBegin((sll_t*)slist), SLLEnd((sll_t*)slist),
     &count, ActionCount);
        
    return count;
}


int SLLForEach(sll_iterator_t from, sll_iterator_t to, void *param,
 int (*action)(sll_iterator_t curr,void *param))
{
    
    assert(from);
    assert(to);
    assert(param);
    assert(action);
    
    while(!SLLIteratorsIsEqual(from, to))
    {
        if(action(from,param))
        {
            return 1;
        }
        from = from->next;
    }
    return 0;

}

sll_iterator_t SLLFind(sll_iterator_t from, sll_iterator_t to,void *param,
 int (*match)(sll_iterator_t curr,void *param))
{
    node_t *tmp_ptr;
    tmp_ptr = from;
    
    assert(from);
    assert(to);
    assert(param);
    assert(match);
    
    while(tmp_ptr != to)
    {
        if(0 == match(tmp_ptr,param))
        {
            return tmp_ptr;
        }
        tmp_ptr = tmp_ptr->next;
    }
    return to;

}




void SLLDestroy(sll_t *slist)
{
    node_t* tmp_ptr = slist->head->next;
    
    assert(slist);
    
    while(NULL != tmp_ptr)
    {
        free(slist->head);/*CR: add slist->head=NULL;|Corrected|*/
        slist->head = NULL;
        slist->head = tmp_ptr;
        tmp_ptr = slist->head->next;
    }
    /*CR: why? it is already NULL by now|You are absolutly right Corrected|*/
    free(slist->tail);/*CR: add slist->tail=NULL;|Corrected|*/
    slist->tail = NULL;
    free(slist);/*CR: add slist=NULL;*/
    slist = NULL;
}


sll_t *SLLAppend(sll_t *slist1, sll_t *slist2)
{
    /* Added Empty checks */
    assert(slist1);
    assert(slist2);
    /*
     if (SLLBegin(slist1) == SLLEnd(slist1))
     CR: delete this condition. ur func will do it anyway
     {
         SLLDestroy (slist1);
         return slist2;
     }
    
    */
    if (SLLBegin(slist2) == SLLEnd(slist2))
    {
        SLLDestroy (slist2);
        return slist1;
    }
    
    
    /*copy head into dummy*/
    slist1->tail->data = slist2->head->data;
    slist1->tail->next = slist2->head->next;

    /*change slist1 tail refrence to tail 2
    and change the data reference as well*/
    slist2->tail->data = slist1;
    slist1->tail = slist2->tail;

    free(slist2->head);/*CR: add slist2->head=NULL;|Corrected|*/
    slist2->head = NULL;
    free(slist2);/*CR: same|Corrected|*/
    slist2 = NULL;
    return slist1;
}

int ActionCount(sll_iterator_t curr, void *param)
{
    assert (curr);
    assert (param);
    (void)curr;
    ++*(size_t*)param;
    return 0;
}

sll_iterator_t GetNthNext(sll_iterator_t curr, size_t n)
{
    assert(curr);
    while(n)
    {
        curr = curr -> next;
        --n;
    }
    return curr;
}

sll_iterator_t FindNthNumFromTail(sll_t *slist,size_t n)
{
    size_t size = SLLCount(slist);
    sll_iterator_t curr = GetNthNext(SLLBegin(slist),size - n);
    return curr;
}





















