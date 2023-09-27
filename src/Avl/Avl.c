/*********************************
 * Reviewer: Roy Mantel				
 * Author: Yohai Azoulai			
 * File: Avl.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/

#include "Avl.h"

/*******Defines******/

typedef int (*avl_my_action_func_t)();

/*******Structs******/


struct node_t
{
    int *data;
    int height;
    struct node_t *child[2];
};
typedef struct node_t avl_node_t;


struct avl
{
    avl_node_t *root;
    void *user_param;
    avl_compare_func_t func_ptr;
};

/*******Service Funcs******/

static int AvlCountKids(avl_node_t *node);


static int HowNodeBalance(avl_node_t *node);
static int HeightOfNode(avl_node_t *node);
static int WhoIsTaller(int height_left, int height_right);
static int HeightOfNode(avl_node_t *node);




void HeightUpdater(avl_node_t *node_to_update);
void AdjustHeight(avl_t *admin, avl_node_t* root, const void *data);

static avl_node_t *AvlRecFind(avl_node_t *node,const void *data, 
                            avl_compare_func_t func_ptr);


/* static avl_node_t *GoLeftRecurs(avl_node_t *node);

static avl_node_t *GoRightRecurs(avl_node_t *node);

 */

/* static int AvlMyForEach(avl_t *avl, avl_my_action_func_t action_func, 
                                void *param); */
static void TraversTreeSizePreOrder(avl_node_t *work_node, 
                                avl_action_func_t func_ptr, 
                                void *user_param);
static void TraversTreeInOrder(avl_node_t *work_node, 
                                avl_action_func_t func_ptr, 
                                void *user_param);
static void TraversTreeDestroyPstOrder(avl_node_t *work_node);


avl_node_t *FindParent(avl_t *avl, avl_node_t *node, const void *data);
void BalanceMyTree(avl_t *admin, avl_node_t * root);
void AdjustHeight(avl_t *admin, avl_node_t* root, const void *data);

avl_node_t *FindTheParent(avl_t *admin,avl_node_t *work_node,void *data);





static avl_action_func_t CountStuff(void *data,void *param);
static int DestroyStuff(avl_node_t *work_node);
/* static avl_my_action_func_t CountStuff(int *param);
 */static int HeightOfNode(avl_node_t *node);





/*******Funcs Funcs******/

    /*    creates the avl and the admin struct */
avl_t *AvlCreate(avl_compare_func_t compare_func, 
                                    void *user_param)
{
    avl_t *admin_ptr = NULL;
    avl_node_t *root_node = NULL;
    
    admin_ptr = (avl_t *)malloc(sizeof(avl_t));
    if (!admin_ptr)
    {
        return NULL;
    }

    root_node = (avl_node_t *)malloc(sizeof(avl_node_t));
    if (!root_node)
    {
        return NULL;
    }

    root_node->data = NULL;
    root_node->height = 0;
    root_node->child[1] = NULL; /*right*/
    root_node->child[0] = NULL; /*left */

    admin_ptr->root = root_node;
    admin_ptr->func_ptr = compare_func;


    (void)user_param;
    return admin_ptr;
}
/************************************************/
        /* Inserts a node in the correct
        position based on user Func                 */
int AvlInsert(avl_t *avl, const void *data)
{
    avl_node_t *work_node = NULL;
    avl_node_t *new_node = NULL;
    size_t child_index = 0;
    int cmpr_res = 0;

    

    /* Locating the node using Recursive find function
                which returns the node*/
    work_node = avl->root;
    if (!work_node->data)
    {
        work_node->data = (void *)data;
        work_node->child[0] = NULL;
        work_node->child[1] = NULL;
        return 0;
    }

    work_node = AvlRecFind(work_node,(void *)data,avl->func_ptr);
    
    /* inserting the node after reciving correct
            spot*/
    cmpr_res = avl->func_ptr(work_node->data,data, avl->user_param);
    child_index = cmpr_res > 0;

    if (0 == cmpr_res)
    {
        return 1;
    }
    

    new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
    if(!new_node)
    {
        return 1;
    }
    work_node->child[child_index] = new_node;
    new_node->data = (void *)data;
    new_node->child[0] = NULL;
    new_node->child[1] = NULL;
 
    AdjustHeight(avl,avl->root,data);


    
    return 0;
}
    
/************************************************/
        /*  Avl find looksup Relevent Node
                and return its data           */
void *AvlFind(avl_t *avl, const void *data)
{
    avl_node_t *work_node = NULL;
    int cmpr_res = 0;
    int child_index = 0;

    work_node = avl->root;
    cmpr_res = avl->func_ptr(work_node->data,data, avl->user_param);
    child_index = cmpr_res > 0;

    if(0 == cmpr_res)
    {
        return work_node->data;
    }
    else
    {
        work_node = AvlRecFind(work_node->child[child_index],data,avl->func_ptr);
        return work_node->data;
    }

    return NULL;
}

/************************************************/
        /*                              */
int AvlIsEmpty(avl_t *avl)
{
    return (!avl->root->data);
}
/************************************************/
        /*     post            
         This functions will be called by Destroys For 
        each accordingly
        0 - Pre Order
        1 - PstOrder
        defult - In*/    
void AvlDestroy(avl_t *avl)
{
     avl_node_t *work_node = NULL;
    work_node = avl->root;
    
    if (AvlCountKids(work_node))
    {
        TraversTreeDestroyPstOrder(avl->root);
    }
    else
    {
        DestroyStuff(work_node);
    }

    free(avl);
    avl = NULL;

}

/************************************************/
        /*    Preoreder  - 0        
         This functions will be called by size For 
        each accordingly
        0 - Pre Order
        1 - PstOrder
        defult - In      */  
size_t AvlSize(avl_t *avl)
{
    size_t size = 0;
    TraversTreeSizePreOrder(avl->root,CountStuff(avl->root,NULL),&size);

    return size;

}
/************************************************/
        /* This functions will be called by Destroys For 
        each accordingly
        0 - Pre Order
        1 - PstOrder
        defult - In*/
void AvlRemove(avl_t *avl, void *data)
{
    avl_node_t *work_node = NULL;

    work_node = avl->root;
    work_node = AvlRecFind(work_node,data,avl->func_ptr);
    switch (AvlCountKids(work_node))
    {
    case 0:
        work_node->data = NULL;
        work_node->child[0] = NULL;
        work_node->child[1] = NULL;
        work_node->height = 0;
        free(work_node);
        break;
    
    case 1:
        /* code */
        break;

    case 2:
        /* code */
        break;
    default:
        break;
    }

    HeightUpdater(avl->root);
    
}
/************************************************/
        /*     in order     */
int AvlForEach(avl_t *avl, avl_action_func_t action_func, 
                                void *param)
{
    avl_node_t *work_node = NULL;
    work_node = avl->root;

    if(!work_node)
    {
        return 1;
    }

    TraversTreeInOrder(work_node,action_func,param);

    return *(int *)param;

}
/************************************************/       
        /* Returns the height of the root */
size_t AvlHeight(const avl_t *tree)
{
    return tree->root->height;
}


/**************Service Funcs********************/
static void TraversTreeSizePreOrder(avl_node_t *work_node, 
                                avl_action_func_t func_ptr, 
                                void *user_param) 
{
    /*Runs the task pre order*/
    ++*(int *)user_param;
    /*traverses left side of tree*/
    
    if (work_node->child[0])
    {
        TraversTreeSizePreOrder(work_node->child[0]
                                ,func_ptr,user_param);       
    }
    /*traverses right side of tree */
    if (work_node->child[1])
    {
        TraversTreeSizePreOrder(work_node->child[1]
                                ,func_ptr,user_param);       
    }
    (void)func_ptr;

}

/************************************************/
static void TraversTreeInOrder(avl_node_t *work_node, 
                                avl_action_func_t func_ptr, 
                                void *user_param)
{
    if (work_node->child[0])
    {
        TraversTreeInOrder(work_node->child[0]
                                ,func_ptr,user_param);
    }
    func_ptr(work_node->data,user_param);
    /*traverses right side of tree */
    if (work_node->child[1])
    {
        TraversTreeInOrder(work_node->child[1]
                                ,func_ptr,user_param);
    }
}

/************************************************/
static void TraversTreeDestroyPstOrder(avl_node_t *work_node)
{
    if (work_node->child[0])
    {
        TraversTreeDestroyPstOrder(work_node->child[0]);       
    }
    /*traverses right side of tree */
    if (work_node->child[1])
    {
        TraversTreeDestroyPstOrder(work_node->child[1]);       
    }
    DestroyStuff(work_node);
}



/************************************************/
    /****Counts Number Of Children****/
static int AvlCountKids(avl_node_t *node)
{
    if (!node->child[0] && !node->child[1])
    {
        return 0;
    }
    
    
    if((node->child[0] && !node->child[1]) || 
                    (!node->child[0] && node->child[1]))
    {
        return 1;
    }
    else
    {
        return 2;
    }
    
}

/************************************************/
    /*Check the balance of 2 children nodes*/
static int HowNodeBalance(avl_node_t *node)
{
    if(!node)
    {
        return 0;
    }
    
    return HeightOfNode(node->child[0]) - HeightOfNode(node->child[1]);
}

/************************************************/
    /*Returns Hight of node*/
static int HeightOfNode(avl_node_t *node)
{
    if (!node) 
    {
        return -1;
    }
    
    return node->height;
}

/************************************************/
    /*Returns the value of node which is "taller"*/
static int WhoIsTaller(int height_left, int height_right)
{
    return (height_left > height_right) ? height_left : height_right;
}

/************************************************/

/****************************************************************/
/* Checking Balance of the tree - rotate 
            accordingly*/



/************************************************/
/* This functions will be called by Destroys For 
        each accordingly
        0 - Pre Order
        1 - PstOrder
        defult - In*/
static int DestroyStuff(avl_node_t *work_node)
{
    work_node->child[0] = NULL;
    work_node->child[1] = NULL;
    work_node->height = 0;
    work_node->data = NULL;
    free(work_node);
    work_node = NULL;
    return 1;
}

/***********************************************
static avl_my_action_func_t CountStuff(int *param)
{
    ++param;
    return 0;
}

***********************************************/
/* This is my func for running my foreach 
        with the relevent functions
        0 - Pre Order
        1 - PstOrder
        defult - In
        */
       /*
static int AvlMyForEach(avl_t *avl, avl_my_action_func_t action_func, 
                                void *param)
{
    avl_node_t *work_node = NULL;
    int for_counting = 0;
    
    work_node = avl->root;

    if(!work_node)
    {
        return 1;
    }

    switch (*(int *)param)
    {
    case 0:
        TraversTreeSizePreOrder(work_node,action_func,&for_counting);
        return for_counting;
        break;
    case 1:
        TraversTreeDestroyPstOrder(work_node,action_func,&for_counting);
        return for_counting;
        break;
    default:
        TraversTreeInOrder(work_node,action_func,&for_counting);
        return for_counting;
        break;
    }

}
*/
/************************************************/
/* 
avl_node_t *GoLeftRecurs(avl_node_t *node)
{
    if (!node->child[0])
    {
        return NULL;
    }
    
    return GoLeftRecurs(node->child[0]);
}
avl_node_t *GoRightRecurs(avl_node_t *node)
{
    if (!node->child[1])
    {
        return NULL;
    }
    
    return GoRightRecurs(node->child[1]);
}
 */
static avl_action_func_t CountStuff(void *data,void *param)
{
    ++(*(int *)data);
    (void)param;
    return 0;
}


avl_node_t *FindTheNode(avl_t *admin,avl_node_t *work_node,void *data)
{
    int compare_result = 0;
    
    if(!AvlCountKids(work_node))
    {
        return work_node;
    }

    compare_result=admin->func_ptr(work_node->data, data, admin->user_param);
    
    return FindTheParent(admin, work_node->child[compare_result > 0], data);
}

avl_node_t *FindTheParent(avl_t *admin,avl_node_t *work_node,void *data)
{
    int compare_result = 0;

    compare_result=admin->func_ptr(work_node->data, data, admin->user_param);

    /* if(work_node == admin->root)
    {
        return NULL;
    } */

    if (compare_result == 0)
    {
        return NULL;
    }
    
    
    if (!admin->func_ptr(
            work_node->child[compare_result > 0]->data, data, admin->user_param))
    {
        return work_node;
    }

    return FindTheParent(admin, work_node->child[compare_result > 0], data);
}


avl_node_t *Rotation(avl_node_t *root, int dir)
{ 
    avl_node_t* node = root->child[!dir]; 
    avl_node_t* node2 = node->child[dir]; 

    /* Perform rotation */
    node->child[dir] = root;
    root->child[!dir] = node2;

    /* Update heights */
    HeightUpdater(root);
    HeightUpdater(node);

    return node; 
}

avl_node_t *DblRotate(avl_node_t *root, int dir)
{
    root->child[dir] = Rotation(root->child[dir],dir);
    return Rotation(root,!dir);
}

int WhichChildIndex(avl_t *admin,
                    avl_node_t *work_node,
                    const void *data,
                    void * user_param)
{
    int cmpr_res = 0 ,child_index = 0;
    cmpr_res = admin->func_ptr(work_node->data,data, user_param);
    child_index = cmpr_res > 0;
    return child_index;
}


void HeightUpdater(avl_node_t *node_to_update)
{
    
    node_to_update->height = WhoIsTaller(HeightOfNode(node_to_update->child[0]), 
                HeightOfNode(node_to_update->child[1])) + 1;
}


void AdjustHeight(avl_t *admin, avl_node_t* root, const void *data)
{

    if (!AvlCountKids(root))
    {
        HeightUpdater(root);
        return;
    }

    AdjustHeight(admin,root->child[WhichChildIndex(admin,
                                                    root,
                                                    data,
                                                    admin->user_param)],
                                                    data);

    HeightUpdater(root);

    BalanceMyTree(admin,root);

}

void BalanceMyTree(avl_t *admin, avl_node_t * root)
{   
    int balance_factor = 0 , child_Index = 0;
    int heavy_child_balance = 0;
    avl_node_t *parent_node = NULL;
    avl_node_t *tmp_node_updater = NULL;

    parent_node = FindTheParent(admin,admin->root,root->data);
    

    balance_factor = HowNodeBalance(root);
    if (balance_factor > -2 && balance_factor < 2 )
    {
        return ;
    }

    heavy_child_balance = HowNodeBalance(root->child[!(balance_factor > 0)]);
    
    if (balance_factor > 0 && heavy_child_balance > 0)
    {
        tmp_node_updater = Rotation(root,1);
    }

    if (balance_factor > 0 && heavy_child_balance < 0)
    {
        tmp_node_updater = DblRotate(root,0);
    }
    
    if (balance_factor < 0 && heavy_child_balance > 0)
    {
        tmp_node_updater = DblRotate(root,1);
    }
    
    if (balance_factor < 0 && heavy_child_balance < 0)
    {
        tmp_node_updater = Rotation(root,0);
    }
    
    if (!parent_node)
    {
        admin->root = tmp_node_updater;
    }
    else
    {
        child_Index = WhichChildIndex(admin,root,
                                      parent_node->data,
                                      admin->user_param);
        parent_node->child[child_Index] = tmp_node_updater;
    }
    
    

}




















/*****DiscardList******/




/************************************************/
        /* node_t recursive function  */
static avl_node_t *AvlRecFind(avl_node_t *node,const void *data, 
                            avl_compare_func_t func_ptr)
{
    size_t child_index = 0;
    int cmpr_res = 0;
    void *user_param = NULL;

    cmpr_res = func_ptr(node->data,data, user_param);
    child_index = cmpr_res > 0;

    if(!node->child[child_index] || cmpr_res == 0)
    {
        return node;
    }
    else
    {
        return AvlRecFind(node->child[child_index],data, func_ptr);
    }
    
}


/* static avl_node_t *RightTreeRotation(avl_node_t *grandfather_node)
{
    avl_node_t *parent_node = grandfather_node->child[0];
    avl_node_t *grandson_node = parent_node->child[1];

    parent_node->child[1] = grandfather_node;
    grandfather_node->child[0] = grandson_node;

    grandfather_node->height = WhoIsTaller(
                                HeightOfNode(grandfather_node->child[0]), 
                                HeightOfNode(grandfather_node->child[1])) + 1;
    parent_node->height = WhoIsTaller(
                                HeightOfNode(parent_node->child[0]), 
                                HeightOfNode(parent_node->child[1])) + 1;
    return parent_node;
}

static avl_node_t *LeftTreeRotation(avl_node_t *grandfather_node)
{
    avl_node_t *parent_node = grandfather_node->child[1];
    avl_node_t *grandson_node = parent_node->child[0];

    parent_node->child[0] = grandfather_node;
    grandfather_node->child[1] = grandson_node;

    grandfather_node->height = WhoIsTaller(
                            HeightOfNode(grandfather_node->child[0]), 
                            HeightOfNode(grandfather_node->child[1])) + 1;
    parent_node->height = WhoIsTaller(
                            HeightOfNode(parent_node->child[0]), 
                            HeightOfNode(parent_node->child[1])) + 1;

    return parent_node;
    
} */

/* 
static void printTree(avl_node_t *node)
{
    if(!node) 
    {
      return;
    }
    printTree(node->child[0]);
    printf("  %d ",((wow_chars_t *)(node->data))->level);
    printTree(node->child[0]);
    
} */