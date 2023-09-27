/*********************************
 * Reviewer: Daniel.B				
 * Author: Yohai Azoulai			
 * File: sllEx.c					
 * ******************************/

#include "sllEx.h"

typedef struct node
{
	void *data;
	struct node *next;
}node_t;
/*
	This flips the order of the links
	1->2->3->4->5 ==> slist, Head -> 1
	Flip(slist) ==>
	5->4->3->2->1 ==> slist, Head -> 5
*/
node_t *Flip(node_t *head)
{
	node_t *next_ref->next = head->next;
	node_t *current = head->next->next;

	assert(head);

	head->next=NULL;

	while(NULL != new_next)
	{
		next_ref->next = head;
		head = next_ref;
		next_ref = current;
		current = current->next;
	}

	next_node->next = head;

	return next_ref;
}


/*
	This flips the order of the links
	1->2->3->4->5->3 ==> slist, Head -> 1
	this function returns if it has a back
	linking problem
*/
int Hasloop(const node_t *head)
{
	node_t *cur_node = (node_t *)head, *next_node = (node_t *)head;

	while(cur_node && next_node && next_node->next)
	{
		cur_node = cur_node->next;
		next_node = next_node->next->next;
		if(cur_node == next_node)
		{
			return 1;
		}
	}
	return 0;
}


/*
	This finds the point of intersection
	1->2->3->4->5 ==> slist, Head1 -> 1
	Flip(slist) ==>
	6->7->8->2->1 ==> slist, Head2 -> 6
	will return 2;
*/
node_t *FindIntersection(node_t *head1,node_t *head2)
{
    node_t *list1=head_1, *list2=head_2;

    while(list1!=list2)
    {
        list1=list1->next;
        list2=list2->next;

        if(list1==list2)
        {
            return list1;
        }

        if(NULL==list1)
        {
            list1=head_2;
        }

        if(NULL==list2)
        {
            list2=head_1;
        }
    }

    return list1;
}