/*********************************
 * Reviewer:  
 * Author: Roy Mantel
 * File Name: heap_pq_test.c
 * ******************************/

#include <stdio.h>	/*printf*/
#include <string.h>	/*strcmp*/
#include "pri_queue.h"


void TestPQueueEnQueueDestroy(void);
void TestPQueueBasics(void);
void TestPQueueAdvanced(void);

typedef struct student
{
	char first_name[15];
	char last_name[15];
	unsigned int id_number;
} student_t;

int main(void)
{
 	TestPQueueEnQueueDestroy();
 	TestPQueueBasics();
	TestPQueueAdvanced();
	return 0;
}

int ComparePriority(const void *data1, const void *data2, void *user_param)
{
	(void)user_param;
	return (0 > strcmp(((student_t*)data1)->last_name, ((student_t*)data2)->last_name));
}

void TestPQueueEnQueueDestroy(void)
{
	pri_queue_t *pq = NULL;
	student_t student1 = {"Avigail", "Millatiner", 1234};
	student_t student2 = {"Roy", "Mantel", 324975};
	pq = PQueueCreate(ComparePriority, "ROY");
	PQueueEnQueue(pq, &student1);
	PQueueEnQueue(pq, &student2);
	PQueueDestroy(pq);
}

void TestPQueueBasics(void)
{
	pri_queue_t *pq = NULL;
	student_t student1 = {"Roy", "Mantel", 1234};
	pq = PQueueCreate(ComparePriority, NULL);
	if(!PQueueIsEmpty(pq))
	{
		printf("Error 1: Created PQ isn't empty\n");
	}

	if(PQueueSize(pq))
	{
		printf("Error 2: Created PQ size isn't zero\n");
	}

	PQueueEnQueue(pq, &student1);
	if(PQueueIsEmpty(pq))
	{
		printf("Error 3: After EnQueue, PQ is still empty\n");
	}

	if(!PQueueSize(pq))
	{
		printf("Error 4: After EnQueue, PQ size is still zero\n");
	}

	PQueueDeQueue(pq);
	if(!PQueueIsEmpty(pq))
	{
		printf("Error 5: After DeQueue, PQ is not empty\n");
	}

	if(PQueueSize(pq))
	{
		printf("Error 6: After DeQueue, PQ size is not zero\n");
	}

	PQueueDestroy(pq);
}

void TestPQueueAdvanced(void)
{
	pri_queue_t *pq = NULL;
	student_t student1 = {"Avigail", "Millatiner", 1234};
	student_t student2 = {"Daniel", "Binyamin", 48982};
	student_t student3 = {"Daniel", "Natan", 2039};
	student_t student4 = {"Irit", "Ofir", 8954};
	student_t student5 = {"Nofar", "Melamed", 9234};
	student_t student6 = {"Roy", "Mantel", 324975};
	student_t student7 = {"Sarah", "Toledano", 21098};
	student_t student8 = {"Shani", "Horden", 23409877};
	student_t student9 = {"Sigal", "Tal", 76438};
	student_t student10 = {"Viktor", "Fainshtein", 234558};
	student_t student11 = {"Yaakov", "Touitou", 54319};
	student_t student12 = {"Yohai", "Azoulai", 12048};
	student_t student13 = {"Yisrael", "Fisch", 10686};
	student_t *student_check = NULL;
	ilrd_uid_t uid = UIDGetNull();
	ilrd_uid_t uid_check = UIDGetNull();
	pq = PQueueCreate(ComparePriority, NULL);
	
	PQueueEnQueue(pq, &student1);
	student_check = (student_t *)PQueuePeek(pq);
	PQueueEnQueue(pq, &student2);
	student_check = (student_t *)PQueuePeek(pq);
	PQueueEnQueue(pq, &student3);
	student_check = (student_t *)PQueuePeek(pq);
	PQueueEnQueue(pq, &student4);
	student_check = (student_t *)PQueuePeek(pq);
	PQueueEnQueue(pq, &student5);
	student_check = (student_t *)PQueuePeek(pq);
	uid = PQueueEnQueue(pq, &student6);
	if(UIDIsSame(uid, g_bad_uid))
	{
		printf("Error UID is BAD\n");
	}

	PQueueEnQueue(pq, &student7);
	student_check = (student_t *)PQueuePeek(pq);
	PQueueEnQueue(pq, &student8);
	student_check = (student_t *)PQueuePeek(pq);
	PQueueEnQueue(pq, &student9);
	student_check = (student_t *)PQueuePeek(pq);
	PQueueEnQueue(pq, &student10);
	student_check = (student_t *)PQueuePeek(pq);
	PQueueEnQueue(pq, &student11);
	student_check = (student_t *)PQueuePeek(pq);
	uid_check = PQueueEnQueue(pq, &student12);
	student_check = (student_t *)PQueuePeek(pq);
	PQueueEnQueue(pq, &student13);

	if(13 != PQueueSize(pq))
	{
		printf("Error 7: PQueue size isn't correct\n");
	}

	student_check = (student_t *)PQueuePeek(pq);
	if(strcmp(student_check->last_name,"Azoulai"))
	{
		printf("Error 8: PQueue not according Priority...\n");
	}

	student_check = PQueueErase(pq, uid);
	if(12 != PQueueSize(pq))
	{
		printf("Error 9: PQueueErase didn't erase the element\n");
	}

	if(strcmp(student_check->first_name, student6.first_name) || 
		strcmp(student_check->last_name, student6.last_name) || 
		student_check->id_number != student6.id_number)
	{
		printf("Error 10: PQueueErase didn't return correct data\n");
	}

	if(PQueueReEnQueue(pq, &student6, uid))
	{
		printf("Error 11: PQueueReEnQueue\n");
	}

	if(13 != PQueueSize(pq))
	{
		printf("Error 12: PQueue size isn't correct after PQueueReEnQueue\n");
	}

	student_check = PQueueErase(pq, g_bad_uid);
	if(student_check)
	{
		printf("Error 13: PQueueErase returned data from a member not in the queue\n");
	}

	if(!UIDIsSame(uid_check, PQueueDeQueue(pq)))
	{
		printf("Error 14: PQueueDeQueue didn't return correct uid\n");
	}

	student_check = (student_t *)PQueuePeek(pq);
	if(strcmp(student_check->last_name,"Binyamin"))
	{
		printf("Error 15: PQueue not according Priority...\n");
	}

	PQueueClear(pq);
	if(!PQueueIsEmpty(pq))
	{
		printf("Error 16: PQueueClear didn't clear the PQueue\n");
	}

	PQueueDestroy(pq);
}