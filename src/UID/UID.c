/*********************************
 * Reviewer: 				
 * Author: Yohai Azoulai			
 * File: UID.c					
 * ******************************/
 
 /**/

#include <unistd.h> /*getpid()*/

#include "UID.h"

/*******Structs******/


/*******Service Funcs******/
ilrd_uid_t g_bad_uid = {-1,-1,-1};

/*******Funcs Funcs******/

ilrd_uid_t UIDGet(void)
{
    static size_t count;
    ilrd_uid_t UID;
    
    UID.count = count;
    UID.time = time(NULL);
    UID.pid = getpid();
    /*consider offloading to txt file on storage*/
    count++;
    return UID;
}

int UIDIsSame(const ilrd_uid_t uid1,const ilrd_uid_t uid2)
{
    return ((uid1.count == uid2.count)&&(uid1.time == uid2.time)&&(uid1.pid == uid2.pid));
}

ilrd_uid_t UIDGetNull(void)
{
    ilrd_uid_t UID = {0,0,0};
    return UID;
}

/*
C Program to get IP address with : 
https://www.sanfoundry.com/c-program-get-ip-address/


*/