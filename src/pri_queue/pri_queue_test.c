#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "pri_queue.h"

typedef struct 
{
	size_t id;
	char name[50];
}pepole_t;

int compare(const void *data1, const void *data2, void *user_param)
{
	pepole_t p1 = *(pepole_t*)data1;
	pepole_t p2 = *(pepole_t*)data2;
	(void)user_param;
	return (p2.id - p1.id);
}

void TestCreateEnDeSize();
void TestClear();
void TestPeekEnOrder();
void TeseErase();

int main()
{
	TestCreateEnDeSize();
	TestClear();
	TestPeekEnOrder();
	TeseErase();
	return 0;
}


void TestCreateEnDeSize()
{
	pri_queue_t *pq = PQueueCreate(compare, NULL);
	pepole_t p1 = {2299, "shani"};
	pepole_t p2 = {1123, "elyashiv"};
	pepole_t p3 = {3323, "tzur"};
	pepole_t p4 = {3324, "ofri"};

	assert (PQueueIsEmpty(pq));
	assert (0 == PQueueSize(pq));
	PQueueEnQueue(pq, &p1);
	assert (1 == PQueueSize(pq));
	PQueueEnQueue(pq, &p2);
	assert (2 == PQueueSize(pq));
	PQueueEnQueue(pq, &p3);
	assert (3 == PQueueSize(pq));
	PQueueEnQueue(pq, &p4);
	assert (4 == PQueueSize(pq));

	PQueueDeQueue(pq);
	assert (3 == PQueueSize(pq));
	PQueueDeQueue(pq);
	assert (2 == PQueueSize(pq));
	PQueueDeQueue(pq);
	assert (1 == PQueueSize(pq));

	assert (!PQueueIsEmpty(pq));

	PQueueDestroy(pq);
}


void TestClear()
{
	pri_queue_t *pq = PQueueCreate(compare, NULL);
	pepole_t p1 = {2299, "shani"};
	pepole_t p2 = {1123, "elyashiv"};
	pepole_t p3 = {3323, "tzur"};
	pepole_t p4 = {3324, "ofri"};

	assert (PQueueIsEmpty(pq));
	assert (0 == PQueueSize(pq));
	PQueueEnQueue(pq, &p1);
	assert (1 == PQueueSize(pq));
	PQueueEnQueue(pq, &p2);
	assert (2 == PQueueSize(pq));
	PQueueEnQueue(pq, &p3);
	assert (3 == PQueueSize(pq));
	PQueueEnQueue(pq, &p4);
	assert (4 == PQueueSize(pq));

	PQueueClear(pq);
	assert (0 == PQueueSize(pq));
	assert (PQueueIsEmpty(pq));

	PQueueDestroy(pq);

}


void TestPeekEnOrder()
{
	pri_queue_t *pq = PQueueCreate(compare, NULL);
	pepole_t p1 = {2299, "shani"};
	pepole_t p2 = {1123, "elyashiv"};
	pepole_t p3 = {3323, "tzur"};
	pepole_t p4 = {3324, "ofri"};

	PQueueEnQueue(pq, &p1);
	PQueueEnQueue(pq, &p2);
	PQueueEnQueue(pq, &p3);
	PQueueEnQueue(pq, &p4);

	printf ("%s\n",((pepole_t*)PQueuePeek(pq))->name );
	assert (((pepole_t*)PQueuePeek(pq))->id == 1123);

	PQueueDeQueue(pq);

	assert (((pepole_t*)PQueuePeek(pq))->id == 2299);
	PQueueDeQueue(pq);

	assert (((pepole_t*)PQueuePeek(pq))->id == 3323);
	PQueueDeQueue(pq);

	assert (((pepole_t*)PQueuePeek(pq))->id == 3324);
	PQueueDeQueue(pq);


	PQueueDestroy(pq);


}

void TeseErase()
{
	pri_queue_t *pq = PQueueCreate(compare, NULL);
	pepole_t p1 = {2299, "shani"};
	pepole_t p2 = {1123, "elyashiv"};
	pepole_t p3 = {3323, "tzur"};
	pepole_t p4 = {3324, "ofri"};
	ilrd_uid_t uid1 = UIDGetNull();

	uid1 = PQueueEnQueue(pq, &p1);
	PQueueEnQueue(pq, &p2);
	PQueueEnQueue(pq, &p3);
	PQueueEnQueue(pq, &p4);
	assert (4 == PQueueSize(pq));

	PQueueErase(pq, uid1);
	assert (3 == PQueueSize(pq));

	assert (((pepole_t*)PQueuePeek(pq))->id == 1123);
	PQueueDeQueue(pq);

	assert (((pepole_t*)PQueuePeek(pq))->id == 3323);
	PQueueDeQueue(pq);

	assert (((pepole_t*)PQueuePeek(pq))->id == 3324);
	PQueueDeQueue(pq);
	assert (0 == PQueueSize(pq));

	PQueueEnQueue(pq, &p1);
	PQueueEnQueue(pq, &p2);
	PQueueEnQueue(pq, &p3);
	PQueueEnQueue(pq, &p4);
	assert (4 == PQueueSize(pq));

	PQueueErase(pq, g_bad_uid);
	assert (4 == PQueueSize(pq));
	PQueueErase(pq, uid1);
	assert (4 == PQueueSize(pq));


	PQueueDestroy(pq);

}

