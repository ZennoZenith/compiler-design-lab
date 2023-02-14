#include <stdio.h>
#include <string.h>

#define MAX_TRANSISTION 100
#define MAX_VARIABLES 100
#define MAX_FINAL_STATES MAX_VARIABLES

int isInFinalState(int arr[], int len, int state)
{
	for (int i = 0; i < len; ++i)
		if (arr[i] == state)
			return 1;
	return 0;
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

int main()
{

	int i = 0, j = 0;
	int tempInt1, tempInt2;
	char ch1, ch2;

	FILE *filePointer = NULL;
	filePointer = fopen("DFA.txt", "r");

	int finalStates[MAX_FINAL_STATES] = {0};
	unsigned int finalStatesLen = 0;
	int DFA_Table[MAX_TRANSISTION][MAX_VARIABLES];

	for (i = 0; i < MAX_TRANSISTION; ++i)
		for (j = 0; j < MAX_VARIABLES; ++j)
			DFA_Table[i][j] = -1;

	if (filePointer == NULL)
	{
		printf("Unable to open DFA.txt\n");
		return 1;
	}

	int initialState = -1;
	int currentState = -1;
	int numberOfTransisation = 0;
	int numberOfVariables = 0;

	fscanf(filePointer, "%d%c", &initialState, &ch1);
	printf("Initial state : %d\n", initialState);

	printf("Final states : ");

	do
	{
		fscanf(filePointer, "%d%c", &tempInt1, &ch1);
		finalStates[finalStatesLen] = tempInt1;
		finalStatesLen++;
		printf("%d, ", tempInt1);
	} while (ch1 != '\n');
	printf("\n");

	i = j = 0;
	while (fscanf(filePointer, "%d%c", &tempInt1, &ch1) != EOF)
	{
		DFA_Table[i][j] = tempInt1;
		j++;
		if (ch1 == '\n')
			numberOfVariables = j, j = 0, i++;
	}
	numberOfTransisation = i;

	printf("Transistion Table\n");
	for (i = 0; i < numberOfTransisation; ++i)
	{
		for (j = 0; j < numberOfVariables; ++j)
		{
			printf("%d ", DFA_Table[i][j]);
		}
		printf("\n");
	}
	fclose(filePointer);

	int flag = 0;
	char inputString[100] = {0};
	int inputStringLen = 0;

	while (1)
	{
		printf("\n------------------------\nEnter input string ('#' to exit) : ");
		// scanf("%s", inputString);
		inputStringLen = Read(inputString);

		if (inputString[0] == '#')
			break;

		printf("Input string : %s, Input string len : %d\n\n", inputString, inputStringLen);

		currentState = initialState;
		flag = 0;
		for (i = 0; i < inputStringLen; ++i)
		{
			tempInt1 = inputString[i] - '0';

			printf("string and state transition : %d , q%d -> ", tempInt1, currentState);
			currentState = DFA_Table[currentState][tempInt1];

			if (currentState == -1)
			{
				printf("NO TRANSISTION\n");
				flag = 1;
				break;
			}
			printf("q%d\n", currentState);
		}

		if (flag == 1 || !isInFinalState(finalStates, finalStatesLen, currentState))
			printf("\nString %s is NOT accepted by the DFA!\n", inputString);
		else
			printf("\nString %s is accepted by the DFA!\n", inputString);
	}

	printf("\nExiting...\n");

	return 0;
}