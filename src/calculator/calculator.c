/*********************************
 * Reviewer: Irit Ofir
 * Author: Yohai Azoulai
 * File: calculator.c
 * ******************************/

/**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/
#include <ctype.h> /*isspace*/


#include "stack.h"
#include "calculator.h"
/*******Defines******/

typedef char *(*func_ptr_t)();
typedef double (*func_double_ptr_t)();

static func_ptr_t Handlers[128];
static func_double_ptr_t Operators[128];
static int OperPrecTable[128];

/*******Structs******/

static stack_t *operators;
static stack_t *output;

/*******Service Funcs******/

static void InitStructs(int length);

static char *HandleOperand(const char *string);
static char *HandleOperator(const char *string);

static void HandleCalc();
double AddNums(double a, double b);
double SubsNums(double a, double b);
double MultNums(double a, double b);
double DivNums(double numerator, double denominator);

static char *HandleSpace(const char *string);
static char *HandleOpenBrace(const char *string);
static char *HandleCloseBrace(const char *string);

static int CheckPrecedence(stack_t *operator_stack,
                           const char *string);
static int CheckBracPrecedence(stack_t *operator_stack,
                           const char *string);


/*******Funcs Funcs******/

	/*the bee's knees
	or cat's pyjamas if you wish*/
double Calculate(const char *string)
{
    double result = 0;
    int leng_of_string = 0;

    assert(string);

    leng_of_string = strlen(string);

    InitStructs(leng_of_string);


    while (*string)
    {
        string = Handlers[(int)*string](string);
    }

    while (!StackIsEmpty(operators))
    {
        HandleCalc();
    }

    StackPeek(output, &result);

    StackDestroy(operators);
    StackDestroy(output);

    return result;
}

/*******************************************************/

	/*deals with open braces in string*/
static char *HandleOpenBrace(const char *string)
{
    StackPush(operators, (char *)string);

    return (char *)++string;
}
/*******************************************************/

	/*initiates the tratment of the currently
		reached paranthsis*/
static char *HandleCloseBrace(const char *string)
{
    while (!StackIsEmpty(operators) && 
                                !CheckBracPrecedence(operators,string))
    {
        HandleCalc();
    }
    
    StackPop(operators);
    
    return (char *)++string;
}
/*******************************************************/

	/*allows for inner brakets operations correctly
		(calculate t and push to output)*/
static int CheckBracPrecedence(stack_t *operator_stack,
                           const char *string)
{
    char active_operator = 0;
    StackPeek(operator_stack, &active_operator);
    return (3 == (OperPrecTable[(int)*string] -
             OperPrecTable[(int)active_operator]));
}
/*******************************************************/

	/*Calculate which operator has higher precedence
		newly inserted / current in stack*/
static int CheckPrecedence(stack_t *operator_stack,
                           const char *string)
{
    char active_operator = 0;
    StackPeek(operator_stack, &active_operator);
    /*
        when this return 1 active *.
        new to add is lower + -
    */
    return ((OperPrecTable[(int)active_operator] -
             OperPrecTable[(int)*string]) >= 0);
}
/*******************************************************/

	/*Handles Operands's in the string*/
static char *HandleOperand(const char *string)
{
    double num = 0;
    char *active_operand = NULL;

    num = strtod(string, &active_operand);
    
    StackPush(output, &num);

    return active_operand;
}
/*******************************************************/

	/*performs the calculation & correct insertion 
		to the stack				*/
static void HandleCalc()
{
    int active_operator = 0;
    double a = 0;
    double b = 0;
    double result = 0;

    StackPeek(operators, &active_operator);
    StackPop(operators);
    
    StackPeek(output,&a);
    StackPop(output);
    
    StackPeek(output,&b);
    StackPop(output);

    result = Operators[active_operator](b, a);

    StackPush(output, &result);
}
/*******************************************************/

	/*Handles Operator's in the string*/
static char *HandleOperator(const char *string)
{
    while (!StackIsEmpty(operators) && CheckPrecedence(operators, string))
    {
        HandleCalc();
    }
    
    StackPush(operators, (char *)string);
    
    return (char *)++string;
}
/*******************************************************/

	/*Iterativly deals with spaces 
	(only when more than one is present)*/
static char *HandleSpace(const char *string)
{
    while (isspace(*string))
    {
        (char *)++string;
    }
    return (char *)string;
}
/*******************************************************/
double AddNums(double a, double b)
{
    return (a + b);
}
/*******************************************************/
double SubsNums(double a, double b)
{
    return (a - b);
}
/*******************************************************/
double MultNums(double a, double b)
{
    return (a * b);
}
/*******************************************************/
double DivNums(double numerator, double denominator)
{
    return (numerator / denominator);
}
/*******************************************************/

	/*Initiates LUT's & Creates the Stacks*/
void InitStructs(int length)
{
    Handlers['0'] = HandleOperand;
    Handlers['1'] = HandleOperand;
    Handlers['2'] = HandleOperand;
    Handlers['3'] = HandleOperand;
    Handlers['4'] = HandleOperand;
    Handlers['5'] = HandleOperand;
    Handlers['6'] = HandleOperand;
    Handlers['7'] = HandleOperand;
    Handlers['8'] = HandleOperand;
    Handlers['9'] = HandleOperand;
    Handlers[' '] = HandleSpace;
    Handlers['+'] = HandleOperator;
    Handlers['-'] = HandleOperator;
    Handlers['*'] = HandleOperator;
    Handlers['/'] = HandleOperator;
    Handlers['('] = HandleOpenBrace;
    Handlers[')'] = HandleCloseBrace;

    Operators['+'] = AddNums;
    Operators['-'] = SubsNums;
    Operators['*'] = MultNums;
    Operators['/'] = DivNums;
    
    OperPrecTable['+'] = 1;
    OperPrecTable['-'] = 1;
    OperPrecTable['*'] = 2;
    OperPrecTable['/'] = 2;
    OperPrecTable['('] = 0;
    OperPrecTable[')'] = 3;

    output = StackCreate(length,sizeof(double));
    operators = StackCreate(length,sizeof(char));
    
}
/************************************************/

/**************Psedu***********************/
/*
*   1.)while(there is another char to pull)
        1.read next token (strok)
        2.)if token is operator (x)
            left accosi & pressedence =< y
            right accosi & pressedence < y
            1.)pop y and calculate ter of 2 operands (stackpop x 2 calculate
                                                        push to output)
            3.) push x.
        3.)if token is
         left parant push to operand
        4.)if token is right parant
            1.) until top token is left maching left paran calculate
                the terms like (2.1)
            2.) pop left paranthesis and push after result t
*       5.) add token to output
*   2.) pop any remaining operator tokens from operator stack to output
        (remainder right) paranthsis

    while -> for calculation of output  (& operand stack isnt empty)
*
*/

