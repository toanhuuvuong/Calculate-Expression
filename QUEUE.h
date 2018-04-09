#ifndef QUEUE_H
#define QUEUE_H

#include<iostream>
#include<conio.h>
//---------------------------------------------------------------
template<typename T>
struct QUEUENODE
{
	T data;
	QUEUENODE<T> *pNext;
};//---------------------------------------------------------------
template<typename T>
struct QUEUE
{
	QUEUENODE<T> *pHead;
	QUEUENODE<T> *pTail;
};//----------------------------------------------------------------
template<typename T>
void initQueue(QUEUE<T> &Q)
{
	Q.pHead = NULL;
	Q.pTail = NULL;
}//----------------------------------------------------------------
template<typename T>
void destroyQueue(QUEUE<T> &Q)
{
	QUEUENODE<T> *cur;
	while (Q.pHead != NULL)
	{
		cur = Q.pHead;
		Q.pHead = Q.pHead->pNext;
		delete cur;
	}
}//------------------------------------------------------------------
template<typename T>
static QUEUENODE<T>* getNodeQueue(const T &newData)
{
	QUEUENODE<T> *cur = new QUEUENODE<T>;
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
bool isEmpty(const QUEUE<T> &Q)
{
	return Q.pHead == NULL;
}//-------------------------------------------------------------------
template<typename T>
void addTailQueue(QUEUE<T> &Q, const T &newData)
{
	QUEUENODE<T> *cur = getNodeQueue(newData);
	if (isEmpty(Q))
		Q.pHead = Q.pTail = cur;
	else
	{
		Q.pTail->pNext = cur;
		Q.pTail = cur;
	}
}//------------------------------------------------------------------
template<typename T>
T getFirstQueue(QUEUE<T> &Q)
{
	if (isEmpty(Q))
	{
		std::cout << "Error" << std::endl;
		exit(0);
	}
	else
	{
		T value = Q.pHead->data;

		QUEUENODE<T> *cur = Q.pHead;
		Q.pHead = Q.pHead->pNext;
		delete cur;

		return value;
	}
}
template<typename T>
T firstQueue(const QUEUE<T> &Q)
{
	if (isEmpty(Q))
	{
		std::cout << "Error" << std::endl;
		exit(0);
	}
	else
	{
		T value = Q.pHead->data;
		return value;
	}
}
template<typename T>
int lengthQueue(const QUEUE<T> &Q)
{
	int length = 0;
	for (QUEUENODE<T> *cur = Q.pHead; cur; cur = cur->pNext)
		length++;
	return length;
}
#endif