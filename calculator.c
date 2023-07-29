#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#define max 50

char *getCurrTime();
double add(double, double);
double multiply(double, double);
double divide(double, double);
double subtract(double, double);
double power(double, double);
void writeLog(int, char *);
void handleInput(char *);
int isValidOperator(char);
void showRes(double, int, char *);

char expression[max];
double outputResult;

int isValidOperator(char c)
{
	if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^')
		return 1;
	return 0;
}
char *getCurrTime()
{	// return arr of size 25 ie. loop <25
	time_t t;
	time(&t);
	return ctime(&t);
}
// status : success(1) or failure(0)
void showRes(double n, int status, char *msg)
{
	if (status) // if status == 1 ie. successful
	{
		(n == (int)n) ? printf("%d\n", (int)n) : printf("%lf\n", n);
		char str[100];
		sprintf(str, "%lf", n);
		writeLog(1, str);
	}
	else // failure in execution
	{
		printf("%s\n", msg);
		writeLog(0, msg);
	}
}
double add(double a, double b)
{
	return a + b;
}
double multiply(double a, double b)
{
	return a * b;
}
double divide(double a, double b)
{
	// if (b == 0)
	//{
	//	printf("Cannot divide by 0. Please try again.");
	//	return -1;
	// }
	return a / b;
}
double subtract(double a, double b)
{
	return a - b;
}
double power(double a, double b)
{
	double res = 1;

	for (int i = 1; i <= b; ++i)
		res *= a;

	return res;
}
void writeLog(int status, char *outputMsg) // writes time and log message
{
	FILE *fp;
	fp = fopen("calculator.log", "a+");

	if (fp == NULL)
	{
		printf("file not found or cannot create file");
		return;
	}
	// char resStatus[] = {(status == 1 ? "success" : "failure")};

	// fprintf(fp, "%sStatus => %s, input:%s\n", getCurrTime(), resStatus, s);
	// fprintf(fp, "%sinput:%s; output:%s; status => %s\n\n", getCurrTime(), expression, outputMsg, (status == 1 ? "success" : "failure"));
	fprintf(fp, "%sStatus => %s; input:\"%s\"; output:\"%s\"\n\n", getCurrTime(), (status == 1 ? "success" : "failure"), expression, outputMsg);

	fclose(fp);
}
void handleInput(char *arr)
{
	// printf("\nInput:%s\n", arr);
	printf(">> ");

	int countOperators = 0, operatorIndex = -1;
	double exp1 = 0, exp2 = 0;

	// handle multiple operators (*,/)
	// for (int i = 0; i < strlen(arr) - 1; i++)
	for (int i = 0; i < strlen(arr); i++)
	{
		if (isValidOperator(arr[i]))
		{
			if (countOperators == 1)
			{
				showRes(0, 0, "Currently single operation supported, please try again");
				// printf("Currently single operation supported, please try again\n");
				return;
			}
			operatorIndex = i;
			countOperators++;
		}
		// else if ((arr[i] < 48 || arr[i] > 56) && (arr[i] != ' ' && arr[i] != '.' && arr[i] != '\0'))
		else if ((arr[i] < 48 || arr[i] > 56) && (arr[i] != ' ' && arr[i] != '.'))
		{
			showRes(0, 0, "Invalid expression");
			// printf("Invalid expression:%c ", arr[i]);
			return;
		}
	}

	// differentiate the numbers
	for (int i = 0; i < strlen(arr); i++)
	{
		if (arr[i] == ' ' || i == operatorIndex)
		{
			continue;
		}

		if (i < operatorIndex)
		{
			exp1 = atof(&arr[i]);
			i = operatorIndex;
		}
		else if (i > operatorIndex)
		{
			exp2 = atof(&arr[i]);
			break;
		}
	}

	if (countOperators == 0)
	{
		// printf("Need operators");
		showRes(0, 0, "Need operators");
		return;
	}

	// printf("exp1:%lf\nexp2:%lf\n", exp1, exp2);

	switch (arr[operatorIndex])
	{
	case '*':
		showRes(multiply(exp1, exp2), 1, "");
		break;
	case '/':
		showRes(divide(exp1, exp2), exp2 != 0 ? 1 : 0, "Cannot divide by 0");
		break;
	case '+':
		showRes(add(exp1, exp2), 1, "");
		break;
	case '-':
		showRes(subtract(exp1, exp2), 1, "");
		break;
	case '^':
		showRes(power(exp1, exp2), 1, "");
		break;
	default:
		showRes(0, 0, "Please try again");
		// printf("Please try again");
	}
}

int main()
{

	printf("Calculator : \n -------\n");
	printf("Supported Operations:\n");
	printf("1) Add:      >> 35.5 + 45\n");
	printf("2) Multiply: >> 2 * 3\n");
	printf("3) Divide:   >> 12 / 4\n");
	printf("4) Subtract: >> 23 - 11\n");
	printf("5) Power:    >> 2 ^ 3\n");
	printf("6) Exit:     >> exit\n");
	printf("\nEnter any expression and press ENTER to see the result :\n\n");

	while (1)
	{
		printf(">> ");
		gets(expression);

		if (strcmp(expression, "exit") == 0)
			return 0;
		handleInput(expression);
	}
}
