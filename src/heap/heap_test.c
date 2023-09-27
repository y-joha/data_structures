/*********************************
 * Reviewer: Avigail Millatiner
 * Author: Irit Ofir
 * File: heap_test.c
 * ******************************/

#include <string.h> /* memset */
#include <strings.h> /* strcasecmp */
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */

#include "heap.h" 

typedef struct class
{
    char *surname_of_teacher;
    char *dep_name;
    unsigned int num_of_students;
    unsigned int class_num; 
} class_t;

int IsLessClass(const void *data1, const void *data2, void *user_param);
int IsMatchClass(const void *a_data, const void *b_data, void *user_param);

class_t *ClassCreate(char *surname_of_teacher, char *dep_name, 
                     unsigned int num_of_students, unsigned int class_num);

int PriorityInt(const void *data1, const void *data2, void *user_param);
int IsMatchInt(const void *a_data, const void *b_data, void *user_param);


void ClassDestroy(class_t *class);

void TestCreate();
void TestPush();
void TestHeapify();

/* ************************************** */

int main()
{
	TestCreate();
	TestPush();
	TestHeapify();

	return 0;
}

/* ************************************** */


int IsLessClass(const void *data1, const void *data2, void *user_param)
{
	int result = 0;
	*(size_t *)user_param += 1;

	if (data1 == data2)
	{
		return 0;
	}

    if (0 == (result = strcasecmp(((class_t *)data1)->dep_name, ((class_t *)data2)->dep_name)))
    {
        return (((class_t *)data1)->class_num < ((class_t *)data2)->class_num);
    }

    return result < 0;
}

int IsMatchClass(const void *a_data, const void *b_data, void *user_param)
{
	(void)user_param;

	return a_data == b_data;
}

class_t *ClassCreate(char *surname_of_teacher, char *dep_name, 
                     unsigned int num_of_students, unsigned int class_num)
{
    class_t *new_class = NULL;
    new_class = (class_t *) calloc(1, sizeof(class_t));
    if (!new_class)
    {
        printf("Failed to allocate memory on ClassCreate on line %d\n", __LINE__);
        return NULL;
    }

    new_class->num_of_students = num_of_students;
    new_class->surname_of_teacher = surname_of_teacher;
    new_class->dep_name = dep_name;
    new_class->class_num = class_num;

    return new_class;
}

int PriorityInt(const void *data1, const void *data2, void *user_param)
{
    (void)user_param;
	return (*(int *)data1 < *(int *)data2);
}

int PriorityIntQsort(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}

int IsMatchInt(const void *a_data, const void *b_data, void *user_param)
{
    (void)user_param;
	return (*(int *)a_data == *(int *)b_data);
}

void ClassDestroy(class_t *class)
{
    class->surname_of_teacher = NULL;
    class->dep_name = NULL;
    class->num_of_students = 0;
    class->class_num = 0;

    free(class);
}

void TestCreate()
{
	heap_t *heap = NULL;
	size_t count = 0;

	heap = HeapCreate(IsLessClass, &count);

	if (HeapSize(heap))
	{
		printf("TestCreate failed (size) on line %d\n", __LINE__);
	}

	if (!HeapIsEmpty(heap))
	{
		printf("TestCreate failed (is empty) on line %d\n", __LINE__);
	}

	HeapDestroy(heap);
}

void TestPush()
{
	heap_t *heap = NULL;
	class_t *class[6] = {NULL}, *test;
	size_t count = 0, i = 0;

	class[0] = ClassCreate("Smith", "CivilEng", 15, 2); /* 4 */
	class[1] = ClassCreate("Hedge", "ChemEng", 7, 3); /* 1 */
	class[2] = ClassCreate("Christie", "MechEng", 10, 2); /* 5 */
	class[3] = ClassCreate("Rice", "ChemEng", 9, 4); /* 2 */
	class[4] = ClassCreate("Smith", "CivilEng", 20, 1);  /* 3 */

	heap = HeapCreate(IsLessClass, &count);

	HeapPush(heap, class[0]);

	if (HeapIsEmpty(heap))
	{
		printf("TestPush failed (is empty) on line %d\n", __LINE__);
	}

	HeapPush(heap, class[1]);
	HeapPush(heap, class[2]);
	HeapPush(heap, class[3]);
	HeapPush(heap, class[4]);
	
	if (5 != HeapSize(heap))
	{
		printf("TestPush failed (size) on line %d\n", __LINE__);
	}

	test = (class_t *)(HeapPeek(heap));

	if (3 != test->class_num)
	{
		printf("TestPush failed (peek) on line %d\n", __LINE__);
	}
	
	class[5] = ClassCreate("Santa-Maria", "Bio", 35, 1);  /* 1 */

	HeapPush(heap, class[5]);

	test = (class_t *)HeapPeek(heap);

	if (35 != test->num_of_students)
	{
		printf("TestPush failed (heapify) on line %d\n", __LINE__);
	}

	HeapRemove(heap, class[1], IsMatchClass, NULL);

	if (5 != HeapSize(heap))
	{
		printf("TestPush failed (remove) on line %d\n", __LINE__);
	}

	HeapRemove(heap, class[5], IsMatchClass, NULL);

	test = (class_t *)HeapPeek(heap);

	if (!IsMatchClass(class[3], test, NULL))
	{
		printf("TestPush failed (remove) on line %d\n", __LINE__);
	}

	HeapPop(heap);

	test = (class_t *)HeapPeek(heap);

	if (!IsMatchClass(class[4], test, NULL))
	{
		printf("TestPush failed (remove) on line %d\n", __LINE__);
	}

	HeapDestroy(heap);

	for (i = 0; i < sizeof(class)/sizeof(class_t *); ++i)
	{
		ClassDestroy(class[i]);
	}
}

void TestHeapify()
{
	int array[100] = {0}, array_sorted[100] = {100}, test = 0;

	size_t i = 0, count = 0;
	heap_t *heap = NULL;

	for (i = 0; i < 100; ++i)
	{
		array[i] = array_sorted[i] = rand()%100;
	}

	qsort(array_sorted, 100, sizeof(int), PriorityIntQsort);
	
	heap = HeapCreate(PriorityInt, &count);

	for (i = 0; i < 100; ++i)
	{
		HeapPush(heap, array + i);
	}

	for (i = 0; i < 100; ++i)
	{
		if ((test = *(int *)HeapPeek(heap)) != array_sorted[i])
		{
			printf("TestHeapify failed on line %d\n", __LINE__);
			printf("num should be %d but is %d instead\n\n", array_sorted[i], test);
		}
		HeapPop(heap);
	}

	HeapDestroy(heap);
}
