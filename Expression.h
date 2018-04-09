#include"STACK.h"
#include"QUEUE.h"
#include<math.h>

#define OPERAND 0
#define OPERATOR 1
#define OPEN_BRACKET 2
#define CLOSE_BRACKET 3

struct element
{
	int value;
	int type;
}; typedef struct element ELEMENT;
//--------------------------------------------------------------------------------------
int readNumber(const char *&function, int &startPos);
int priorityOperator(const char &oper);

void convertStringToQueue(const char *&function, QUEUE<ELEMENT> &qFunc);
void convertStringToStack(const char *&function, STACK<ELEMENT> &sFunc);

void convertInfixToPostfix(QUEUE<ELEMENT> &qFunc, QUEUE<ELEMENT> &qBalanFunc);
void convertInfixToPrefix(STACK<ELEMENT> &sFunc, QUEUE<ELEMENT> &qBalanFunc);

int resultExpressionPost(QUEUE<ELEMENT> &qBalanFunc);
int resultExpressionPre(QUEUE<ELEMENT> &qBalanFunc);
