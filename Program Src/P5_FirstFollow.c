#include <stdio.h>
#include <string.h>

#define MAX_TRANSISTION 100
#define MAX_VARIABLES 100
#define MAX_FINAL_STATES MAX_VARIABLES

int isInArr(char arr[], int len, char val)
{
	for (int i = 0; i < len; ++i)
		if (arr[i] == val)
			return i;
	return -1;
}

int Read(char *str)
{
	int i = 0;
	while (1)
	{
		str[i] = getchar();
		if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			return i;
		}
		i++;
	}
}

void swap(char *x, char *y)
{
	char temp = *x;
	*x = *y;
	*y = temp;
}

void sortArray(char arr[], int len)
{
	int flag = 0;
	for (int i = 0; i < len; ++i)
	{
		flag = 0;
		for (int j = 0; j < len - i - 1; ++j)
			if (arr[j] > arr[j + 1])
			{
				swap(&arr[j], &arr[j + 1]);
				flag = 1;
			}
		if (flag == 0)
			break;
	}
}

// removes duplicates from sorted array
void removeDuplicates(char arr[])
{
	int len = strlen(arr);
	sortArray(arr, len);
	for (int i = 0; i < len - 1; ++i)
	{
		if (arr[i] == arr[i + 1])
		{
			for (int j = i + 1; j < len - 1; ++j)
				arr[j] = arr[j + 1];
			len--;
			i--;
			arr[len] = '\0';
		}
	}
}

void removeChar(char arr[], char ch)
{
	int len = strlen(arr);
	for (int i = 0; i < len; ++i)
	{
		if (arr[i] == ch)
		{
			for (int j = i; j < len - 1; ++j)
				arr[j] = arr[j + 1];
			len--;
			i--;
			arr[len] = '\0';
		}
	}
}

int main()
{
	int i = 0, j = 0, k = 0;
	int tempInt1, tempInt2;
	char ch1, ch2;

	FILE *filePointer = NULL;
	filePointer = fopen("FirstFollow2.txt", "r");

	char CFG2D[MAX_VARIABLES][MAX_VARIABLES];
	char firstOf[MAX_VARIABLES][MAX_VARIABLES];
	char followOf[MAX_VARIABLES][MAX_VARIABLES];

	for (i = 0; i < MAX_VARIABLES; ++i)
		for (j = 0; j < MAX_VARIABLES; ++j)
		{
			CFG2D[i][j] = 0;
			firstOf[i][j] = 0;
			followOf[i][j] = 0;
		}

	if (filePointer == NULL)
	{
		printf("Unable to open FirstFollow.txt\n");
		return 1;
	}

	char startSymbol;
	fscanf(filePointer, "%c%c", &startSymbol, &ch1);
	printf("Start symbol : %c\n", startSymbol);

	i = j = 0;
	while (fscanf(filePointer, "%c", &ch1) != EOF)
	{
		if (ch1 == '\n')
		{
			i++, j = 0;
			continue;
		}
		CFG2D[i][j] = ch1;
		j++;
	}
	fclose(filePointer);

	char variables[MAX_VARIABLES] = {0};
	char terminals[MAX_VARIABLES] = {0};
	int numberOfVariables = 0;
	int numberOfTerminals = 0;
	int numberOfProductions = 0;

	for (i = 0; i < MAX_VARIABLES; i++)
	{
		if (CFG2D[i][0] == 0)
			break;
		printf("%c -> ", CFG2D[i][0]);
		variables[numberOfVariables++] = CFG2D[i][0];
		for (j = 1; j < MAX_VARIABLES; j++)
		{
			if (CFG2D[i][j] == 0)
				break;
			printf("%c", CFG2D[i][j]);
			// if (CFG2D[i][j] >= 'a' && CFG2D[i][j] <= 'z')
			// 	terminals[numberOfTerminals++] = CFG2D[i][j];
			if (CFG2D[i][j] >= 'A' && CFG2D[i][j] <= 'Z')
				variables[numberOfVariables++] = CFG2D[i][j];
			else if (CFG2D[i][j] == '#')
				continue;
			else
				terminals[numberOfTerminals++] = CFG2D[i][j];
		}
		printf("\n");
	}
	numberOfProductions = i;

	printf("Number of variables : %d\n", numberOfVariables);
	printf("Number of terminals : %d\n", numberOfTerminals);
	printf("Variables : ");
	for (i = 0; i < numberOfVariables - 1; ++i)
		printf("%c, ", variables[i]);
	printf("%c\n", variables[i]);

	printf("Terminals : ");
	for (i = 0; i < numberOfTerminals - 1; ++i)
		printf("%c, ", terminals[i]);
	printf("%c\n\n\n", terminals[i]);

	removeDuplicates(variables);
	numberOfVariables = strlen(variables);
	removeDuplicates(terminals);
	numberOfTerminals = strlen(terminals);

	printf("Number of variables : %d\n", numberOfVariables);
	printf("Number of terminals : %d\n", numberOfTerminals);
	printf("Variables : ");
	for (i = 0; i < numberOfVariables - 1; ++i)
		printf("%c, ", variables[i]);
	printf("%c\n", variables[i]);

	printf("Terminals : ");
	for (i = 0; i < numberOfTerminals - 1; ++i)
		printf("%c, ", terminals[i]);
	printf("%c\n\n\n", terminals[i]);

	for (i = 0; i < numberOfVariables; i++)
	{
		char currentVariable = variables[i];
		for (j = 0; j < numberOfProductions; ++j)
		{
			char tempStr[] = {0, 0, 0, 0, 0};
			if (CFG2D[j][0] != currentVariable)
				continue;
			if (CFG2D[j][1] == '#')
			{
				tempStr[0] = '#';
				strcat(firstOf[i], tempStr);
			}
			else
			{
				tempStr[0] = CFG2D[j][1];
				strcat(firstOf[i], tempStr);
			}
			// else if (isInArr(terminals, numberOfTerminals, CFG2D[j][1]) != -1)
			// {
			// 	tempStr[0] = CFG2D[j][1];
			// 	strcat(firstOf[i], tempStr);
			// }
		}
	}

	printf("First Of :\n");
	for (i = 0; i < numberOfVariables; ++i)
	{
		printf("%c : ", variables[i]);
		for (j = 0; firstOf[i][j] != '\0'; j++)
			printf("%c ", firstOf[i][j]);
		printf("\n");
	}

	
	// for (i = 0; i < numberOfProductions; i++)
	// {
	// 	if (CFG2D[i][1] == '#')
	// 		continue;

	// 	int variableIndex = isInArr(variables, numberOfVariables, CFG2D[i][0]);
	// 	int j = 1;
	// 	int flag = 0;
	// 	char tempStr[] = {0, 0, 0, 0, 0};

	// 		while (j < strlen(CFG2D[i]))
	// 		{
	// 			int indexOfProductionVariable = isInArr(variables, numberOfVariables, CFG2D[i][j]);
	// 			if (indexOfProductionVariable == -1)
	// 				break;
	// 			// tempStr[0] = CFG2D[i][j];
	// 			// strcat(firstOf[variableIndex], tempStr);

	// 			int tempIndexOfProductionVariable = -1;
	// 			do
	// 			{
	// 				tempIndexOfProductionVariable = isInArr(variables, numberOfVariables, CFG2D[indexOfProductionVariable][1]);
	// 				if (tempIndexOfProductionVariable != -1)
	// 					indexOfProductionVariable = tempIndexOfProductionVariable;
	// 			} while (tempIndexOfProductionVariable == -1);

	// 			if (isInArr(firstOf[indexOfProductionVariable], strlen(firstOf[indexOfProductionVariable]), '#') == -1)
	// 				break;
	// 			tempStr[0] = CFG2D[i][j];
	// 			strcat(firstOf[variableIndex], tempStr);
	// 			j++;
	// 		}
	// 		if (j == strlen(CFG2D[i]))
	// 		{
	// 			tempStr[0] = '#';
	// 			strcat(firstOf[variableIndex], tempStr);
	// 		}
	// }

	printf("First Of :\n");
	for (i = 0; i < numberOfVariables; ++i)
	{
		printf("%c : ", variables[i]);
		for (j = 0; firstOf[i][j] != '\0'; j++)
			printf("%c ", firstOf[i][j]);
		printf("\n");
	}

	int flag = 0;
	int flag2 = 0;
	do
	{
		flag = 0;
		for (i = 0; i < numberOfVariables; i++)
		{
			// char tempFirst[MAX_VARIABLES] = {0};
			flag2 = 0;
			if (isInArr(firstOf[i], numberOfVariables, '#') != -1)
				flag2 = 1;
			for (j = 0; j < strlen(firstOf[i]); j++)
			{
				int index = isInArr(variables, numberOfVariables, firstOf[i][j]);
				if (index == -1)
					continue;

				// Removes variable if referencing itself
				if (index == i)
				{
					int k = 0;
					for (k = j; k < strlen(firstOf[i]) - 1; ++k)
						firstOf[i][k] = firstOf[i][k + 1];
					firstOf[i][k] = '\0';
				}

				// Removes variable and replaces it with first of that variable
				else
				{
					int k = 0;
					for (k = j; k < strlen(firstOf[i]) - 1; ++k)
						firstOf[i][k] = firstOf[i][k + 1];
					firstOf[i][k] = '\0';
					strcat(firstOf[i], firstOf[index]);
					if (isInArr(variables, numberOfVariables, firstOf[index][0]))
						flag = 1;
				}

				// remove # from fistOf
				removeChar(firstOf[i], '#');

				// if firstOf contained # at begining and #
				if (flag2)
				{
					char tempStr[] = "#";
					strcat(firstOf[i], tempStr);
				}
			}
		}
	} while (flag);

	printf("First Of :\n");
	for (i = 0; i < numberOfVariables; ++i)
	{
		printf("%c : ", variables[i]);
		for (j = 0; firstOf[i][j] != '\0'; j++)
			printf("%c ", firstOf[i][j]);
		printf("\n");
	}

	return 0;
	// calculating follow
	for (i = 0; i < numberOfVariables; i++)
	{
		char currentVariable = variables[i];
		if (currentVariable == startSymbol)
			strcat(followOf[i], "$");

		for (j = 0; j < numberOfProductions; ++j)
		{
			char tempStr[] = {0, 0, 0, 0, 0};

			// pass from next pointer of CFG[j] thus not reading first value
			int index = isInArr(CFG2D[j] + 1, strlen(CFG2D[j]) - 1, currentVariable);
			if (index == -1)
				continue;

			// increment index as pointer was deceremented earlier
			index++;

			printf("Found variable %c in productions %s at index %d\n", currentVariable, CFG2D[j], index);
			if (CFG2D[j][index + 1] == '\0')
			{
				tempStr[0] = CFG2D[j][0];
				if (tempStr[0] != currentVariable)
					strcat(followOf[i], tempStr);
			}
			else if (isInArr(terminals, numberOfTerminals, CFG2D[j][index + 1]) != -1)
			{
				tempStr[0] = CFG2D[j][index + 1];
				strcat(followOf[i], tempStr);
			}
			else if (isInArr(variables, numberOfVariables, CFG2D[j][index + 1]) != -1)
			{
				int indexVariable = isInArr(variables, numberOfVariables, CFG2D[j][index + 1]);
				printf("current variable : %c, first of variable : %c, producer : %c\n", currentVariable, variables[indexVariable], CFG2D[j][0]);
				if (isInArr(firstOf[indexVariable], strlen(firstOf[indexVariable]), '#') != -1)
				{
					printf("-----true\n");
					tempStr[0] = CFG2D[j][0];
					strcat(followOf[i], tempStr);
				}
				strcat(followOf[i], firstOf[indexVariable]);
			}
		}
		removeDuplicates(followOf[i]);
		// removes epsilon '#'
		int index = isInArr(followOf[i], strlen(followOf[i]), '#');
		if (index != -1)
		{
			int k = 0;
			for (k = index; k < strlen(followOf[i]) - 1; ++k)
				followOf[i][k] = followOf[i][k + 1];
			followOf[i][k] = '\0';
		}
	}

	printf("Follow Of :\n");
	for (i = 0; i < numberOfVariables; ++i)
	{
		printf("%c : ", variables[i]);
		for (j = 0; followOf[i][j] != '\0'; j++)
			printf("%c ", followOf[i][j]);
		printf("\n");
	}

	for (i = 0; i < numberOfVariables; i++)
	{
		int len = strlen(followOf[i]);
		for (j = 0; j < len; j++)
		{
			int index = isInArr(variables, numberOfVariables, followOf[i][j]);
			if (index == -1)
				continue;

			// removes the variable
			int k = 0;
			for (k = j; k < len - 1; ++k)
				followOf[i][k] = followOf[i][k + 1];
			followOf[i][k] = '\0';

			strcat(followOf[i], followOf[index]);
			len = strlen(followOf[i]);
			// decrement j to check if followOf[index] first element is variable or not
			j--;
		}

		removeDuplicates(followOf[i]);
	}
	printf("Follow Of :\n");
	for (i = 0; i < numberOfVariables; ++i)
	{
		printf("%c : ", variables[i]);
		for (j = 0; followOf[i][j] != '\0'; j++)
			printf("%c ", followOf[i][j]);
		printf("\n");
	}
	printf("\nExiting...\n");
	return 0;
}
