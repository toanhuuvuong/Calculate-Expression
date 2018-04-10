#include"Expression.h"
// hàm đọc chuỗi function từ vị trí startPos (dừng lại khi gặp kí tự khác number) và chuyển số vừa đọc từ dạng chuỗi sang dạng số nguyên 
int readNumber(const char *&function, int &startPos)
{
	int result = 0;
	char *stringNumber = NULL;
	int length = 0;

	while (true)
	{
		if (*(function + startPos) >= '0' && *(function + startPos) <= '9')
		{
			stringNumber = (char*)realloc(stringNumber, (length + 1)*sizeof(char));
			*(stringNumber + length) = *(function + startPos);
			length++;
			startPos++; // khi gặp kí tự không phải số thì startPos đã ++ lên
		}
		else
		{
			stringNumber = (char*)realloc(stringNumber, (length + 1)*sizeof(char));
			*(stringNumber + length) = '\0';
			startPos--; // để trả về vị trí chưa đọc lố các kí tự khác số
			break;
		}
	}
	// Chuyển chuỗi vừa đọc sang dạng số
	for (int i = 0; i < length; i++)
	{
		result += (*(stringNumber + i) - '0')*pow(10.0, length - i - 1);
	}
	delete[] stringNumber;
	return result;
}//---------------------------------------------------------------------------------------------------------------------------------------
// hàm chuyển từ chuỗi function sang hàng đợi qFunc để dễ tính toán trong việc chuyển (trung tố -> hậu tố)
void convertStringToQueue(const char *&function, QUEUE<ELEMENT> &qFunc)
{
	int startPos = 0;
	int length = strlen(function);
	ELEMENT element;

	initQueue(qFunc);

	while (startPos < length)
	{
		if (*(function + startPos) == '(')
		{
			element.value = '(';
			element.type = OPEN_BRACKET;
			addTailQueue(qFunc, element);
		}
		else if (*(function + startPos) == ')')
		{
			element.value = ')';
			element.type = CLOSE_BRACKET;
			addTailQueue(qFunc, element);
		}
		else if (*(function + startPos) >= '0' && *(function + startPos) <= '9')
		{
			element.value = readNumber(function, startPos);
			element.type = OPERAND;
			addTailQueue(qFunc, element);
		}
		else if (*(function + startPos) == '+' || *(function + startPos) == '-' || *(function + startPos) == '*' || *(function + startPos) == '/')
		{
			element.value = *(function + startPos);
			element.type = OPERATOR;
			addTailQueue(qFunc, element);
		}

		startPos++;
	}
}//---------------------------------------------------------------------------------------------------------------------------------------------------
// hàm chuyển từ chuỗi function sang ngăn xếp sFunc để dễ tính toán trong việc chuyển (trung tố -> tiền tố)
void convertStringToStack(const char *&function, STACK<ELEMENT> &sFunc)
{
	int startPos = 0;
	int length = strlen(function);
	ELEMENT element;

	initStack(sFunc);

	while (startPos < length)
	{
		if (*(function + startPos) == '(')
		{
			element.value = '(';
			element.type = OPEN_BRACKET;
			addTopStack(sFunc, element);
		}
		else if (*(function + startPos) == ')')
		{
			element.value = ')';
			element.type = CLOSE_BRACKET;
			addTopStack(sFunc, element);
		}
		else if (*(function + startPos) >= '0' && *(function + startPos) <= '9')
		{
			element.value = readNumber(function, startPos);
			element.type = OPERAND;
			addTopStack(sFunc, element);
		}
		else if (*(function + startPos) == '+' || *(function + startPos) == '-' || *(function + startPos) == '*' || *(function + startPos) == '/')
		{
			element.value = *(function + startPos);
			element.type = OPERATOR;
			addTopStack(sFunc, element);
		}

		startPos++;
	}

}
// hàm kiểm tra độ ưu tiên của toán tử
int priorityOperator(const char &oper)
{
	if (oper == '+' || oper == '-')
		return 1;
	if (oper == '*' || oper == '/')
		return 2;
	return 0;
}//--------------------------------------------------------------------------------------------------------------------------------------------------
// hàm chuyển (trung tố -> hậu tố)
void convertInfixToPostfix(QUEUE<ELEMENT> &qFunc, QUEUE<ELEMENT> &qBalanFunc)
{
	initQueue(qBalanFunc);
	STACK<ELEMENT> tempStack;
	initStack(tempStack);
	ELEMENT element;

	int length = lengthQueue(qFunc);

	for (int i = 0; i < length; i++)
	{
		element = getFirstQueue(qFunc);

		switch (element.type)
		{
		case OPERAND:
			addTailQueue(qBalanFunc, element);
			break;
		case OPERATOR:
			if (!isEmpty(tempStack))
				if(priorityOperator(topStack(tempStack).value) >= priorityOperator(element.value))// dấu * hoặc dấu /
					addTailQueue(qBalanFunc, getTopStack(tempStack));

			addTopStack(tempStack, element);

			break;
		case OPEN_BRACKET:
			addTopStack(tempStack, element);
			break;
		case CLOSE_BRACKET:
			while (topStack(tempStack).type != OPEN_BRACKET)
			{
				addTailQueue(qBalanFunc, getTopStack(tempStack));
			}

			getTopStack(tempStack);

			break;
		default:
			std::cout << "Error" << std::endl;
			exit(0);
		}
	}
	// khi trong stack còn phần tử
	while (heightStack(tempStack))
	{
		addTailQueue(qBalanFunc, getTopStack(tempStack));
	}

	destroyStack(tempStack);
}//----------------------------------------------------------------------------------------------------------------------------
// hàm chuyển (trung tố -> tiên tố)
void convertInfixToPrefix(STACK<ELEMENT> &sFunc, QUEUE<ELEMENT> &qBalanFunc)
{
	initQueue(qBalanFunc);
	STACK<ELEMENT> tempStack;
	initStack(tempStack);
	ELEMENT element;

	int height = heightStack(sFunc);

	for (int i = 0; i < height; i++)
	{
		element = getTopStack(sFunc);

		switch (element.type)
		{
		case OPERAND:
			addTailQueue(qBalanFunc, element);
			break;
		case OPERATOR:
			if (!isEmpty(tempStack))
				if(priorityOperator(topStack(tempStack).value) > priorityOperator(element.value)) // khi đầu của tempStack là dấu (* hoặc /)
					addTailQueue(qBalanFunc, getTopStack(tempStack));

			addTopStack(tempStack, element);

			break;
		case OPEN_BRACKET:
			while (topStack(tempStack).type != CLOSE_BRACKET)
			{
				addTailQueue(qBalanFunc, getTopStack(tempStack));
			}
			// xóa luôn dấu đóng ngoặc của tempStack
			getTopStack(tempStack);
			break;
		case CLOSE_BRACKET:
			addTopStack(tempStack, element);
			break;
		default:
			std::cout << "Error" << std::endl;
			exit(0);
		}
	}
	// khi trong tempStack còn phần tử thì lấy ra bỏ vào qBalanFunc cho đến hết
	while (heightStack(tempStack))
	{
		addTailQueue(qBalanFunc, getTopStack(tempStack));
	}
	// Hủy stack trung gian 
	destroyStack(tempStack);
 }
// tính kết quả hậu tố
int resultExpressionPost(QUEUE<ELEMENT> &qBalanFunc)
{
	int result;
	STACK<ELEMENT> tempStack;
	initStack(tempStack);
	ELEMENT element;
	int firstValueStack, secondValueStack;

	while (lengthQueue(qBalanFunc))
	{
		element = getFirstQueue(qBalanFunc);

		if (element.type == OPERAND)
			addTopStack(tempStack, element);
		else // element.type == OPERATOR
		{
			firstValueStack = getTopStack(tempStack).value;
			secondValueStack = getTopStack(tempStack).value;

			switch (element.value)
			{
			case '+':
				result = secondValueStack + firstValueStack; // đẩy 2 giá trị đầu của ngăn xếp ra(thực hiện phép tính)
				break;
			case '-':
				result = secondValueStack - firstValueStack; // đẩy 2 giá trị đầu của ngăn xếp ra(thực hiện phép tính)
				break;
			case '*':
				result = secondValueStack * firstValueStack; // đẩy 2 giá trị đầu của ngăn xếp ra(thực hiện phép tính)
				break;
			case '/':
				result = secondValueStack / firstValueStack; // đẩy 2 giá trị đầu của ngăn xếp ra(thực hiện phép tính)
				break;
			default:
				break;
			}
			element.value = result;
			element.type = OPERAND;

			addTopStack(tempStack, element);
		}
	}

	return getTopStack(tempStack).value;
}//-------------------------------------------------------------------------------------------------------------------------------------
// tính kết quả tiền tố
int resultExpressionPre(QUEUE<ELEMENT> &qBalanFunc)
{
	int result;
	STACK<ELEMENT> tempStack;
	initStack(tempStack);
	ELEMENT element;
	int firstValueStack, secondValueStack;

	while (lengthQueue(qBalanFunc))
	{
		element = getFirstQueue(qBalanFunc);

		if (element.type == OPERAND)
			addTopStack(tempStack, element);
		else // element.type == OPERATOR
		{
			firstValueStack = getTopStack(tempStack).value;
			secondValueStack = getTopStack(tempStack).value;

			switch (element.value)
			{
			case '+':
				result = firstValueStack + secondValueStack;  // đẩy 2 giá trị đầu của ngăn xếp ra(thực hiện phép tính)
				break;
			case '-':
				result = firstValueStack - secondValueStack; // đẩy 2 giá trị đầu của ngăn xếp ra(thực hiện phép tính)
				break;
			case '*':
				result = firstValueStack * secondValueStack;  // đẩy 2 giá trị đầu của ngăn xếp ra(thực hiện phép tính)
				break;
			case '/':
				result = firstValueStack / secondValueStack; // đẩy 2 giá trị đầu của ngăn xếp ra(thực hiện phép tính)
				break;
			default:
				break;
			}
			element.value = result;
			element.type = OPERAND;

			addTopStack(tempStack, element);
		}
	}

	return getTopStack(tempStack).value;
}



