/*********************************
 * Reviewer: Yohai Azoulai
 * Author: Irit Ofir
 * File: hash_table_test.c
 * ******************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <string.h>
#include "hash_table.h" 

int HashFunc(void *hash_data);
int IsMatchString(const void *a_data, const void *b_data);
int StringLength(void *data, void *param);

void TestCreate();
void TestInsert();
size_t NumberOfWordsInDictionary(FILE *dict);
void AddDictionary(char *str);

int main(int argc, char *argv[])
{
	TestCreate();
	TestInsert();

	if (argc > 1)
	{
		AddDictionary(argv[1]);
	}

	return 0;
}

int HashFunc(void *hash_data)
{
    char *word = (char *) hash_data;
	int hash = 5381;
    int c = '\0';

    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int IsMatchString(const void *a_data, const void *b_data)
{
	return !(strcmp(a_data, b_data));
}

int StringLength(void *data, void *param)
{
    *(int *)param += 1;
	if (8 < strlen(data))
	{
		return -17;
	}
	
	(void)param;
	return 0;
}

void TestCreate()
{
	hash_t *hash = NULL;

	hash = HashCreate(IsMatchString, HashFunc, 10);

	if (HashSize(hash))
	{
		printf("TestCreate failed (sized) on line %d\n", __LINE__);
	}

	if (!HashIsEmpty(hash))
	{
		printf("TestCreate failed (is empty) on line %d\n", __LINE__);
	}

	HashDestroy(hash);
}

void TestInsert()
{
	hash_t *hash = NULL;
	int for_each_result = 0, count = 0;
	char *test = NULL;
	
	char names[6][50] = 
	{
		"tal",
		"tamir",
		"eitan",
		"max",
		"lewis",
		"zrubavela"
	};

	hash = HashCreate(IsMatchString, HashFunc, 5);

	HashInsert(hash, names + 0);
	HashInsert(hash, names + 1);
	HashInsert(hash, names + 2);
	HashInsert(hash, names + 3);
	HashInsert(hash, names + 4);
	HashInsert(hash, names + 5);

	if (HashIsEmpty(hash))
	{
		printf("TestInsert failed (is empty) on line %d\n", __LINE__);
	}

	if (6 != HashSize(hash))
	{
		printf("TestInsert failed (size) on line %d\n", __LINE__);
	}

	HashRemove(hash, "eitan");

	if (5 != HashSize(hash))
	{
		printf("TestInsert failed (remove) on line %d\n", __LINE__);
	}


	test = HashFind(hash, "tal");

	if (!test)
	{
		printf("TestInsert failed (find) on line %d\n", __LINE__);
	}

	test = HashFind(hash, "irit");

	if (test)
	{
		printf("TestInsert failed (find) on line %d\n", __LINE__);
	}

	test = HashFind(hash, "zrubavela");

	if (!test)
	{
		printf("TestInsert failed (find) on line %d\n", __LINE__);
	}

	for_each_result = HashForEach(hash, StringLength, &count);

	if (-17 != for_each_result)
	{
		printf("TestInsert failed (for each) on line %d\n", __LINE__);
	}

	if (3 != count)
	{
		printf("TestInsert failed (for each) on line %d\n", __LINE__);
	}


	HashDestroy(hash);
}

size_t NumberOfWordsInDictionary(FILE *dict)
{
    size_t words = 0;

	while (!feof(dict))
	{
		if ('\n' == fgetc(dict))
		{
			++words;
		}
	}
	fseek(dict, 0, SEEK_SET);
	return words;
}


void AddDictionary(char *str)
{
	FILE *dict = NULL;
	size_t words = 0, read_word = 0, i = 0;
	char buffer[100] = {'\0'}, *test = NULL;
	char **dict_array = NULL;
	hash_t *hash = NULL;

	hash = HashCreate(IsMatchString, HashFunc, 1000);

	dict = fopen("/usr/share/dict/words", "r");
	words = NumberOfWordsInDictionary(dict);

	dict_array = (char **) malloc(sizeof(char *) * words);

	for(i = 0; i < words; ++i)
	{
		fscanf(dict, "%s", buffer);
		read_word = strlen(buffer);
		*(dict_array + i) = malloc(read_word * sizeof(char) + 1);
   	}

	fseek(dict, 0, SEEK_SET);

	for(i = 0; i < words; ++i)
	{
        fscanf(dict, "%s", *(dict_array + i));
	}

	for (i = 0; i < words; ++i)
	{
		HashInsert(hash, *(dict_array + i));
	}

	if (words != HashSize(hash))
	{
		printf("AddDictionary failed (size) on line %d\n", __LINE__);
	}

	test = HashFind(hash, str);

	if (test)
	{
		printf("The word %s is in the dictionary\n", str);
	}
	else
	{
		printf("The word %s is NOT in the dictionary\n", str);
	}


	/* **********BURN IT TO THE GROUND****************************** */
	HashDestroy(hash);

	for (i = 0; i < words; ++i)
	{
		free(dict_array[i]);
		dict_array[i] = NULL;
	}

	free(dict_array);
	dict_array = NULL;
	fclose(dict);
}
