/*********************************
 * Reviewer: Daniel_B
 * Author: Yohai Azoulai
 * File: BST.c
 * ******************************/

/**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/

#include "BST.h"
/*******Defines******/

/*******Structs******/

struct node_t
{
    void *data;
    struct node_t *parent;
    struct node_t *child[2];
};
typedef struct node_t bst_node_t;



struct bst
{
    bst_node_t *root;
    void *user_param;
    bst_compare_func_t func_ptr;
};



/*******Service Funcs******/

int PlusParam(void *list_data, void *param);
int CompareIntDown(const void *data1, const void *data2, void *user_param);
int CompareInt(const void *data1, const void *data2, void *user_param);
static int WhichChildAmI(bst_node_t *node_within_iter);
static int IsBarren(bst_node_t *node_within_iter);
static int HaveFatman(bst_node_t *node_within_iter);
static int HaveLittleBoy(bst_node_t *node_within_iter);
static int CountAction(void *list_data, void *param);
static int IfRoot(bst_node_t *node);


/*******Funcs Funcs******/



bst_t *BSTCreate(bst_compare_func_t compare_func, void *user_param)
{
    bst_t *admin_ptr = NULL;
    bst_node_t *dummy = NULL;
    
    admin_ptr = (bst_t *)malloc(sizeof(bst_t));
    if (!admin_ptr)
    {
        return NULL;
    }

    dummy = (bst_node_t *)malloc(sizeof(bst_node_t));
    if (!dummy)
    {
        return NULL;
    }


    dummy->data = NULL;
    dummy->parent = NULL;
    dummy->child[1] = NULL; /*right*/
    dummy->child[0] = NULL; /*left */

    admin_ptr->root = dummy;
    admin_ptr->func_ptr = compare_func;
    (void)user_param;
    return admin_ptr;
}

size_t BSTSize(bst_t *bst)
{
    size_t count = 0;

    count = BSTForEach(bst,CountAction,&count);

    return count;
} 

int BSTIsEmpty(bst_t *bst)
{
    return (bst->root->data == NULL);
}

bst_iterator_t BSTInsert(bst_t *bst, const void *data) 
{
    bst_iterator_t result_iter = {0};
    size_t child_index = 0;
    size_t cmpr_res = 0;
    bst_node_t *new_node = NULL;
    bst_node_t *work_node = NULL;

    work_node = bst->root;
    cmpr_res = bst->func_ptr(work_node,data, bst->user_param);
    child_index = cmpr_res > 0;

    
    new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
    if(!new_node)
    {
        return BSTEnd(bst);
    }
    
    if(BSTIsEmpty(bst))
    {
        new_node->data = NULL;  
        new_node->parent = bst->root;
        new_node->child[0] = NULL;
        new_node->child[1] = NULL;

        work_node->data = (void *)data;
        work_node->child[1] = new_node;
        result_iter.bst_node = new_node;
                    
        return result_iter;
    }

    /*chekcing if trying to insert same number*/
    if(0 == cmpr_res)
    {
        return BSTEnd(bst);
    }

    while ((work_node->child[child_index]) && 
                        (work_node->child[child_index])->data != NULL)
    {
        work_node = work_node->child[child_index];
        cmpr_res = bst->func_ptr(work_node,data, bst->user_param);

        if (0 == cmpr_res)
        {
            return BSTEnd(bst);
        }

        child_index = cmpr_res > 0;
    }

    new_node->data = (void *)data;
	new_node->parent = work_node;
	new_node->child[0] = NULL;
   	
	if(!(work_node->child[child_index])) /*child is null*/
	{
		new_node->child[1] = NULL;
		work_node->child[child_index] = new_node;
	}
	else
	{	
        /*child is dummy, conect the dummy and the new node*/			
		work_node->child[child_index]->parent = new_node;
		new_node->child[1] = work_node->child[child_index];
		work_node->child[child_index] = new_node;
	}

	result_iter.bst_node = new_node;
	return result_iter;

}

/*
void BSTDestroy(bst_t *bst)
{

}
*/

/*
    count children 

    0 children 
    1 child
    2 children -> 2 ways to implement 


void BSTRemove(bst_iterator_t iter)
{
    
}

*/


bst_iterator_t BSTBegin(bst_t *bst)
{
    bst_iterator_t cur = {0};
    cur.bst_node = bst->root;

    while(HaveLittleBoy(cur.bst_node))
    {
        cur.bst_node = cur.bst_node->child[0];
    }
    return cur;
}

bst_iterator_t BSTEnd(bst_t *bst)
{
    bst_iterator_t cur = {0};
    cur.bst_node = bst->root;

    while(HaveFatman(cur.bst_node))
    {
        cur.bst_node = cur.bst_node->child[1];
    }
    return cur;
}

bst_iterator_t BSTPrev(bst_iterator_t iter)
{
    if(IsBarren(iter.bst_node))
    {
        while(!WhichChildAmI(iter.bst_node))
        {
            iter.bst_node = iter.bst_node->parent;
        }
        iter.bst_node = iter.bst_node->parent;
        return iter;
    }
    
    iter.bst_node = iter.bst_node->child[0];
    while(HaveFatman(iter.bst_node))
    {
        iter.bst_node = iter.bst_node->child[1];
    }
    return iter;
}

bst_iterator_t BSTNext(bst_iterator_t iter)
{
    if(IsBarren(iter.bst_node))
    {
        while(WhichChildAmI(iter.bst_node))
        {
            iter.bst_node = iter.bst_node->parent;
        }
        iter.bst_node = iter.bst_node->parent;
        return iter;
    }
    
    iter.bst_node = iter.bst_node->child[1];
    while(HaveLittleBoy(iter.bst_node))
    {
        iter.bst_node = iter.bst_node->child[0];
    }
    return iter;
}



int BSTIsSameIter(bst_iterator_t f_iter, bst_iterator_t s_iter)
{
    return (f_iter.bst_node == s_iter.bst_node);
}


void *BSTGetData(bst_iterator_t iter)
{
    return ((void *)iter.bst_node->data);
}

bst_iterator_t BSTFind(bst_t *bst, const void *data)
{
    bst_node_t *work_node = NULL;
    bst_iterator_t return_iter = {0};
    size_t child_index = 0;
    size_t cmpr_res = 0;

    work_node = bst->root;

    cmpr_res = bst->func_ptr(work_node,data, bst->user_param);
    child_index = cmpr_res > 0;
    
    /*if found on the root node*/
    if(0 == cmpr_res)
    {
        return_iter.bst_node = work_node;
        return return_iter;
    }

                /*while =>
                1.have child
                2.not what i'm looking for
                3.not dummy*/
    while (work_node->child[child_index] && 
          (cmpr_res != 0) && 
          (work_node->child[child_index]->data != NULL))
    {
        work_node = work_node->child[child_index];
        cmpr_res = bst->func_ptr(work_node,data, bst->user_param);
        child_index = cmpr_res > 0;
        if (cmpr_res == 0)
        {
            return_iter.bst_node = work_node;
            return return_iter;
        }
        
    }
    return BSTEnd(bst);
    
}

int BSTForEach(bst_t *bst, bst_action_func_t action_func, void *param)
{
    bst_node_t *work_node = NULL;
    size_t reach_edge = 1;
    int dir = 0;
    int chk_mov = 1;
    int dummy_flag = 1;
    int prnt_flag = 1;
    int orpend = 0;

    work_node = bst->root;
    if(work_node->child[0 == NULL])
    {
        dir = 1;
        chk_mov = 0;
    }

    while (2 > prnt_flag)
    {
        
        /*do i have where to advance? && i havnt seen dummy yet?*/

        while (work_node->child[dir] != NULL && reach_edge && dummy_flag)
        {
            work_node = work_node->child[dir];
            if(work_node->child[dir]->data == NULL)
            {
                dummy_flag = 0;
            }
        }
        dummy_flag = 1;
        /*do i slide in opposite and reset?*/
        if(work_node->child[chk_mov] != NULL && dummy_flag)
        {
            if(work_node->child[dir]->data == NULL)
            {
                dummy_flag = 0;
                continue;
            }
            work_node = work_node->child[chk_mov];
            continue;
        }
        
        /*do i act?*/
        if (work_node->child[chk_mov] == NULL && dummy_flag)
        {
            if(!action_func(work_node->data,param))
            {
                return *(int *)param;
            }
            
            orpend = IfRoot(work_node);

            if(orpend && (2 > prnt_flag))
            {
                prnt_flag += 1;
                continue;
            }

            if(orpend && (2 == prnt_flag))
            {
                return 0;
            }
            

            work_node = work_node->parent;
            reach_edge = 0;
            continue;
        }
    }
    return 0;
}
    




/*
    maybe do this with a greater than sign?

checks if

static int IsSameNode(bst_node_t *node_within_iter)
{
    return (node_within_iter->data-node_within_iter->parent->data > 0);
}


if i'm the right child returns 1
if i'm the left child returns 0


*/



/**********************************************/
int CompareIntDown(const void *data1, const void *data2, void *user_param)
{
    (void)user_param;
    return (*(int *)data1 - *(int *)data2);
}
/**********************************************/
int PlusParam(void *list_data, void *param)
{
    *(int *)list_data += *(int *)param;
    return 0;
}
/**********************************************/
static int CountAction(void *list_data, void *param)
{
    assert (list_data);
    assert (param);
    (void)list_data;
    ++*(int *)param;
    return 0;
}
/**********************************************/
static int WhichChildAmI(bst_node_t *node_within_iter)
{
    return (*(int *)node_within_iter->data - 
            *(int *)node_within_iter->parent->data > 0);
}
/**********************************************/
static int IsBarren(bst_node_t *node_within_iter)
{
    return (!(node_within_iter->child[0] == NULL) && 
            !(node_within_iter->child[1] == NULL));
}
/**********************************************/
static int HaveFatman(bst_node_t *node_within_iter)
{
    return (node_within_iter->child[1] != NULL);
}
/**********************************************/
static int HaveLittleBoy(bst_node_t *node_within_iter)
{
    return (node_within_iter->child[0] != NULL);
}

/**********************************************/

void EuthanizeTip(bst_node_t *work_node)
{
    bst_node_t *child = NULL;
    child = work_node->child[0];

    child->data = NULL;
    child->parent = NULL;
    child->child[0] = NULL;
    child->child[1] = NULL;

    free(child);
    child = NULL;

    work_node->data = NULL;
    work_node->child[0] = NULL;
   
}   
/**********************************************/
static int IfRoot(bst_node_t *node)
{
    return (node->parent == NULL);
}
/**********************************************/

