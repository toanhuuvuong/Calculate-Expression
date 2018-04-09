#ifndef STACK_H
#define STACK_H

#include<iostream>
#include<conio.h>
//---------------------------------------------------------------
template<typename T>
struct STACKNODE
{
	T data;
	STACKNODE<T> *pNext;
};//---------------------------------------------------------------
template<typename T>
struct STACK
{
	STACKNODE<T> *pHead;
	STACKNODE<T> *pTail;
};//----------------------------------------------------------------
template<typename T>
void initStack(STACK<T> &S)
{
	S.pHead = NULL;
	S.pTail = NULL;
}//----------------------------------------------------------------
template<typename T>
void destroyStack(STACK<T> &S)
{
	STACKNODE<T> *cur;
	while (S.pHead != NULL)
	{
		cur = S.pHead;
		S.pHead = S.pHead->pNext;
		delete cur;
	}
}//------------------------------------------------------------------
template<typename T>
static STACKNODE<T>* getNodeStack(const T &newData)
{
	STACKNODE<T> *cur = new STACKNODE<T>;
	if (cur)
	{
		cur->data = newData;
		cur->pNext = NULL;
		return cur;
	}
	else
	{
		std::cout << "Error" << std::endl;
		exit(0);
	}
}//------------------------------------------------------------------
template<typename T>
bool isEmpty(const STACK<T> &S)
{
	return S.pHead == NULL;
}//-------------------------------------------------------------------
template<typename T>
void addTopStack(STACK<T> &S, const T &newData)
{
	STACKNODE<T> *cur = getNodeStack(newData);
	if (isEmpty(S))
		S.pHead = S.pTail = cur;
	else
	{
		cur->pNext = S.pHead;
		S.pHead = cur;
	}
}//------------------------------------------------------------------
template<typename T>
T getTopStack(STACK<T> &S)
{
	if (isEmpty(S))
	{
		std::cout << "Error" << std::endl;
		exit(0);
	}
	else
	{
		T value = S.pHead->data;

		STACKNODE<T> *cur = S.pHead;
		S.pHead = S.pHead->pNext;
		delete cur;

		return value;
	}
}//-------------------------------------------------------------
template<typename T>
T topStack(const STACK<T> &S)
{
	if (isEmpty(S))
	{
		std::cout << "Error" << std::endl;
		exit(0);
	}
	else
	{
		T value = S.pHead->data;
		return value;
	}
}//-------------------------------------------------------------------------
template<typename T>
int heightStack(const STACK<T> &S)
{
	int height = 0;
	for (STACKNODE<T> *cur = S.pHead; cur; cur = cur->pNext)
		height++;
	return height;
}
#endif