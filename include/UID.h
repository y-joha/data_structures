/*********************************
 * Reviewer:                
 * Author: Yohai Azoulai            
 * File: UID.c                  
 * ******************************/

#ifndef __UID_H__
#define __UID_H__

#include <sys/types.h> /*pid_t & size_t*/
#include <time.h>
#include <unistd.h> /*time_t*/

struct UID                                                                                                                                    
{                                                
  size_t count;
  time_t time;
  pid_t pid;
};


typedef struct UID ilrd_uid_t;

extern ilrd_uid_t g_bad_uid;

ilrd_uid_t UIDGet(void);

int UIDIsSame(const ilrd_uid_t uid1,const ilrd_uid_t uid2);

ilrd_uid_t UIDGetNull(void);

#endif 
