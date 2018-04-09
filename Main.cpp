#include"Expression.h"

int main()
{
	char *function = "5*((12 - 5/8)/(110 - 55*10/10)*((55 + 6)/4 - 5*2)+(11/2 + 5))";

	QUEUE<ELEMENT> qFunc;
	STACK<ELEMENT> sFunc;

	QUEUE<ELEMENT> qBalanFuncPost;
	QUEUE<ELEMENT> qBalanFuncPre;

	// chuyển chuỗi sang queue
	convertStringToQueue((const char *&)function, qFunc);
	// chuyển chuỗi sang stack
	convertStringToStack((const char *&)function, sFunc);
	// chuyển trung tố -> hậu tố
	convertInfixToPostfix(qFunc, qBalanFuncPost);
	// chuyển trung tố -> tiền tố
	convertInfixToPrefix(sFunc, qBalanFuncPre);
	
	// in trung tố
	std::cout << "TRUNG TO: " << function << std::endl;
	// in hậu tố
	std::cout << "HAU TO: ";
	for (QUEUENODE<ELEMENT> *curQ = qBalanFuncPost.pHead; curQ; curQ = curQ->pNext)
	{
		if (curQ->data.type == OPERAND)
			std::cout << curQ->data.value;
		else // OPERATOR
			std::cout << (char)curQ->data.value;
	}
	std::cout << std::endl;

	// in tiền tố
	std::cout << "TIEN TO: ";
	for (QUEUENODE<ELEMENT> *curS = qBalanFuncPre.pHead; curS; curS = curS->pNext)
	{
		if (curS->data.type == OPERAND)
			std::cout << curS->data.value;
		else // OPERATOR
			std::cout << (char)curS->data.value;
	}
	std::cout << std::endl << std::endl;

	// in kết quả hậu tố
	std::cout << "ResultPost = " << resultExpressionPost(qBalanFuncPost) << std::endl;
	//in kết quả tiền tố
	std::cout << "ResultPre = " << resultExpressionPre(qBalanFuncPre) << std::endl;

	// hủy
	destroyQueue(qBalanFuncPost);
	destroyQueue(qBalanFuncPre);
	destroyQueue(qFunc);
	destroyStack(sFunc);

	_getch();
	return 0;
}