/*********************************
 * Reviewer: Victor Fainshtein
 * Author: Yohai Azoulai			
 * File: dhcp.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/
#include <arpa/inet.h> /*inet func*/


#include "dhcp.h"
/*******Defines******/

#define INT_BYTES 32
 /*CR - ??? what why and how ??? || Corrected*/
enum {not_taken,taken};


/*******Structs******/

struct dhcp
{
    struct node_dhcp *root;
    ip_address_t net_mask;
    int address_range;

};

struct node_dhcp
{
    struct node_dhcp *children[2];
    int flag;
};

typedef struct node_dhcp dhcp_node_t;


/*******Service Funcs******/

static dhcp_node_t *CreateNewNode();

static int CreateInitialNodes(dhcp_node_t *dhcp_list, int how_deep);

static void RecursDestroy(dhcp_node_t *dhcp_node);

static int IsThereAChild(dhcp_node_t *dhcp_node, int side);

static int IsChildTaken(dhcp_node_t *dhcp_node, int side);  
/*CR - Taken could be changed to Ocupied for better naming*/

static int FlagUpdater(dhcp_node_t *dhcp_node);

static ip_address_t RecursiveAlloc(
                                dhcp_node_t *running_ptr, 
                                ip_address_t ip, 
                                int depth);

static size_t RecursCount(dhcp_node_t *dhcp_node,int depth);

static int RenewRecurs(dhcp_node_t *node, ip_address_t path, int depth);

static int FreeRecurs(dhcp_node_t *node, ip_address_t path, int depth);

static int NumberOfKids(dhcp_node_t *dhcp_node);


/*******Funcs Funcs******/
dhcp_t *DHCPCreate(const char *net_address, int net_mask)
{
    dhcp_t *dhcp_list = NULL;

    assert(net_address);

    dhcp_list = (dhcp_t *)malloc(sizeof(dhcp_t));
    
    dhcp_list->net_mask = inet_network(net_address);
    dhcp_list->address_range = INT_BYTES - net_mask;
    dhcp_list->root = CreateNewNode();

    if (!CreateInitialNodes(dhcp_list->root,dhcp_list->address_range))
    {
        DHCPDestroy(dhcp_list);
        free(dhcp_list);
        dhcp_list = NULL;
    }

    return dhcp_list;
}
/********************************************************/
void DHCPDestroy(dhcp_t *dhcp)
{
    assert(dhcp);

    RecursDestroy(dhcp->root);
    dhcp->root = NULL;
    dhcp->address_range = 0;
    dhcp->net_mask = 0;
    free(dhcp);
}
/********************************************************/
ip_address_t DHCPAllocateIp(dhcp_t *dhcp)
{
    ip_address_t ip = 0;
    dhcp_node_t *running_ptr = NULL;
    
    assert(dhcp);

    running_ptr = dhcp->root;

    ip = RecursiveAlloc(running_ptr,ip,dhcp->address_range);


    return (dhcp->net_mask | ip);

} 
/********************************************************/

int DHCPFreeIp(dhcp_t *dhcp, ip_address_t ip)
{
    assert(dhcp);
    return FreeRecurs(dhcp->root,ip,dhcp->address_range);
} 
/********************************************************/
size_t DHCPCountFree(dhcp_t *dhcp)
{
    size_t count = 0;
    assert(dhcp);
    count = RecursCount(dhcp->root,dhcp->address_range);

    return (1 << dhcp->address_range) - count;
}
/********************************************************/

 int DHCPRenewIP(dhcp_t *dhcp, ip_address_t ip)
{
    
    return RenewRecurs(dhcp->root,ip,dhcp->address_range);
} 
/***************Service Funcs*******************/


static dhcp_node_t *CreateNewNode()
{
    dhcp_node_t *new_node = NULL;

    new_node = (dhcp_node_t *)malloc(sizeof(dhcp_node_t));
    if (!new_node)
    {
        return NULL;
    }
    
    new_node->children[0] = NULL;
    new_node->children[1] = NULL;
    new_node->flag = not_taken;

    return new_node;

}

static int CreateInitialNodes(dhcp_node_t *root, int how_deep)
{
    int i = 0;
    dhcp_node_t *running_ptr = NULL;
    running_ptr = root;
    /*Left Initializer*/
    for (i = 0; i < how_deep; i++)       
    /*CR - could change to: how_deep (readability) || Corrected*/
    {
        running_ptr->children[0] = CreateNewNode();
        
        if (!running_ptr->children[0])
        {
            return 0;
        }
        running_ptr->flag = not_taken;        
        running_ptr = running_ptr->children[0];
    } 
    
    running_ptr->flag = taken;
    running_ptr = root;
    /*Right Initializer*/
    for (i = 0; i < how_deep - 1; i++)
    {
        running_ptr->children[1] = CreateNewNode();
        
        if (!running_ptr->children[1])
        {
            return 0;
        }
        running_ptr->flag = not_taken;
        running_ptr = running_ptr->children[1];
    }
    running_ptr->children[0] = CreateNewNode();
    if (!running_ptr->children[0])
        {
            return 0;
        }
    running_ptr->children[1] = CreateNewNode();
    if (!running_ptr->children[1])
        {
            return 0;
        }
    running_ptr->flag = taken;
    running_ptr->children[0]->flag = taken;
    running_ptr->children[1]->flag = taken;

    return 1;
}

static void RecursDestroy(dhcp_node_t *dhcp_node)
{                                    
    /*CR - Remove remarks that are not needed || Corrected*/
    if (!dhcp_node)
    {
        return;
    }
    
    RecursDestroy(dhcp_node->children[0]);
    
    RecursDestroy(dhcp_node->children[1]);
    
    free(dhcp_node);
}

static int IsThereAChild(dhcp_node_t *dhcp_node, int side)
{
    return (NULL != dhcp_node->children[side]);
}

static int IsChildTaken(dhcp_node_t *dhcp_node, int side)
{
    return (taken == dhcp_node->children[side]->flag);
}

static ip_address_t RecursiveAlloc(
                                dhcp_node_t *running_ptr, 
                                ip_address_t ip, 
                                int depth)
{
    if (0 == depth)
    {
        running_ptr->flag = taken;
        return ip;
    } 
    
    /*left side treatment*/
    if(IsThereAChild(running_ptr,0) && !IsChildTaken(running_ptr, 0))
    {
        ip <<= 1;
        ip = RecursiveAlloc(running_ptr->children[0],ip,depth - 1);
        running_ptr->flag = FlagUpdater(running_ptr);
        return ip;
    }

    if (!IsThereAChild(running_ptr,0))
    {
        running_ptr->children[0] = CreateNewNode();
        ip <<= 1;
        ip = RecursiveAlloc(running_ptr->children[0],ip,depth - 1);
        running_ptr->flag = FlagUpdater(running_ptr);
        return ip;

    }
    
    
    /*Right side treatment*/
    if(IsThereAChild(running_ptr,1) && !IsChildTaken(running_ptr, 1))
    {
        ip <<= 1;
        ip |= 1;
        ip = RecursiveAlloc(running_ptr->children[1],ip,depth - 1);
        running_ptr->flag = FlagUpdater(running_ptr);
        return ip;
    }

    if (!IsThereAChild(running_ptr,1))
    {
        running_ptr->children[1] = CreateNewNode();
        ip <<= 1;
        ip |= 1;
        ip = RecursiveAlloc(running_ptr->children[1],ip,depth - 1);
        running_ptr->flag = FlagUpdater(running_ptr);
        return ip;

    }

    return -1;
}
 
static size_t RecursCount(dhcp_node_t *dhcp_node,int depth)
{                                    
    /*CR - Remove remarks that are not needed || Corrected*/
    
    if(!dhcp_node)
    {
        return 0;
    }
    
    if (0 == depth)
    {
        return 1;
    }

    return RecursCount(dhcp_node->children[0],depth - 1) + 
                    RecursCount(dhcp_node->children[1],depth - 1);
}

static int RenewRecurs(dhcp_node_t *node, ip_address_t path, int depth)
{
    
    int index = 0;
    index = ((path>>(depth - 1))&1);
    
    if (!node)
    {
        return 1;
    }
    
    if (0 == depth)
    {
        return 0;
    }
    
    return RenewRecurs(node->children[index],path,depth - 1);
}


static int FlagUpdater(dhcp_node_t *dhcp_node)
{
    int res = 0;

    if(IsThereAChild(dhcp_node,0) && IsThereAChild(dhcp_node,1))
    {
        res += IsChildTaken(dhcp_node,0);
        res += IsChildTaken(dhcp_node,1);
        res = ((res == 2)? 1:0);
    }

    return res;
}

static int NumberOfKids(dhcp_node_t *dhcp_node)
{
    return !!dhcp_node->children[0] + !!dhcp_node->children[1];
}



void NodeDestroyer(dhcp_node_t *dhcp_node)          
/*Node_Destroyer_4000 || Approved!*/
{
    dhcp_node->children[0] = NULL;
    dhcp_node->children[1] = NULL;
    dhcp_node->flag = 0;
    free(dhcp_node);
}




int FreeRecurs(dhcp_node_t *node, ip_address_t path, int depth)
{
    {
    int rec_result = 0, index = 0;;
    
    if (!node)
    {
        return 1;
    }
    
    if (0 == depth)
    {
        return 0;
    }
    
    index = ((path>>(depth - 1))&1);
    rec_result =  FreeRecurs(node->children[index],path,depth - 1);

    if(rec_result)
    {
        return 1;
    }

    if(!NumberOfKids(node->children[index]))
    {
        NodeDestroyer(node->children[index]);
        node->children[index] = NULL;
    }

    node->flag = 0;

    return 0;

    }
}
