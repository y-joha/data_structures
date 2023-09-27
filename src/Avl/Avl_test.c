/*********************************
 * Reviewer: Roy Mantel				
 * Author: Yohai Azoulai			
 * File: Avl_test.c				
 * ******************************/

#include "Avl.h" 
#include <assert.h>
#include <stdio.h>

int CompareChars(const void *char_a, const void *char_b, void *user_param);
int PrintThisNode(const void *char_a, const void *char_b, void *user_param);


static void InitStuff();
static void TestCreate();
static void TestInsertNodes(); 
static void GeneralTesting();



typedef struct wow_chars
{
    int level;
    int gearlvl;
    char *char_name;
}wow_char_t;


static wow_char_t charecters[10];



int main(int argc, char *argv[])
{
    
    InitStuff();
    
    TestCreate();


    GeneralTesting();


    (void)argc;
    (void)argv;

    return 0;
}


void InitStuff()
{
    charecters[0].level = 30;
    charecters[0].gearlvl = 300;
    charecters[0].char_name = "Kizes";

    charecters[1].level = 6;
    charecters[1].gearlvl = 100;
    charecters[1].char_name = "Mitwakwek";

    charecters[2].level = 99;
    charecters[2].gearlvl = 778;
    charecters[2].char_name = "Nahardov";

    charecters[3].level = 43;
    charecters[3].gearlvl = 445;
    charecters[3].char_name = "Ptziza";

    charecters[4].level = 55;
    charecters[4].gearlvl = 150;
    charecters[4].char_name = "Pkak";

    charecters[5].level = 80;
    charecters[5].gearlvl = 22;
    charecters[5].char_name = "Utmazgin";

    charecters[6].level = 89;
    charecters[6].gearlvl = 636;
    charecters[6].char_name = "Uther";

    charecters[7].level = 7;
    charecters[7].gearlvl = 741;
    charecters[7].char_name = "Sylvanis";

    charecters[8].level = 4;
    charecters[8].gearlvl = 354;
    charecters[8].char_name = "Apolonios";

    charecters[9].level = 162;
    charecters[9].gearlvl = 999;
    charecters[9].char_name = "HolyGuakamoly";
}

void TestCreate()
{
    avl_t *lvltree = NULL;
    avl_t *grtree = NULL;

    int gears = 1;

    lvltree = AvlCreate(CompareChars,0);
    grtree = AvlCreate(CompareChars,&gears);

    assert(lvltree);
    assert(grtree);


    AvlDestroy(lvltree);
    AvlDestroy(grtree);

}

int PrintThisNode(const void *char_a, const void *char_b, void *user_param)
{
    printf("this is the data of this node %s \n",((wow_char_t *)char_a)->char_name);
    printf("and is arranged by this = %d \n",((wow_char_t *)char_a)->level);

    (void)char_b;
    (void)user_param;
    return 0;
}

int CompareChars(const void *char_a, const void *char_b, void *user_param)
{
    size_t char_a_lvl = 0;
    size_t char_b_lvl = 0;
    

    char_a_lvl = ((wow_char_t *)char_a)->level;
    char_b_lvl = ((wow_char_t *)char_b)->level;
    (void)user_param;
    return (char_b_lvl - char_a_lvl);

}

/*

static void TestInsertNodes()
{
    avl_t *lvltree = NULL;
    avl_t *grtree = NULL;
    int i = 0;

    int gears = 1;

    lvltree = AvlCreate(CompareChars,NULL);
    grtree = AvlCreate(CompareChars,&gears);

    assert(lvltree);
    assert(grtree);

    for (i = 0; i < 10; i++)
    {
        AvlInsert(lvltree,(charecters + i));
        printf("size of the tree is = %ld\n", AvlSize(lvltree));
        printf("and its height is = %ld\n", AvlHeight(lvltree));
    }

    AvlFind(lvltree,(charecters + 5));
    printf("the data it was suppose to find %d\n",(charecters + 4)->level);
    printf("the data it found %d\n",*(int *)AvlFind(lvltree,(charecters + 4)));



    AvlDestroy(lvltree);
    AvlDestroy(grtree);
}


*/
static void GeneralTesting()
{
    avl_t *lvltree = NULL;
    int i = 0;


    lvltree = AvlCreate(CompareChars,NULL);

    assert(lvltree);

    for (i = 0; i < 10; i++)
    {
        AvlInsert(lvltree,(charecters + i));
/*         printf("size of the tree is = %ld\n", AvlSize(lvltree)); 
 */        printf("and its height is = %ld\n", AvlHeight(lvltree)); 
    }

    AvlFind(lvltree,(charecters + 5));
    printf("the data it was suppose to find %d\n",(charecters + 4)->level);
    printf("the data it found %d\n",*(int *)AvlFind(lvltree,(charecters + 4)));



    AvlDestroy(lvltree);
}
