#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRANSISTION 100
#define MAX_VARIABLES 100

struct Transistion
{
	int stateToTransistion;
	char output[5];
};

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

	int tempInt1, tempInt2;
	char ch1, ch2, ch;
	int i = 0, j = 0, k = 0;

	FILE *filePointer = NULL;
	filePointer = fopen("MEALY2.txt", "r");

	if (filePointer == NULL)
	{
		printf("Unable to open MEALY.txt\n");
		return 1;
	}

	struct Transistion Transistion_Table[MAX_TRANSISTION][MAX_VARIABLES * 2];

	for (i = 0; i < MAX_TRANSISTION; ++i)
		for (j = 0; j < MAX_VARIABLES; ++j)
		{
			for (k = 0; k < 5; ++k)
				Transistion_Table[i][j].output[k] = '\0';
			Transistion_Table[i][j].stateToTransistion = -1;
		}

	int initialState = -1;
	int currentState = -1;
	int numberOfStates = 0;
	int numberOfInputs = 0;

	fscanf(filePointer, "%d%c", &initialState, &ch1);
	printf("Initial state : %d\n", initialState);
	fscanf(filePointer, "%d%c", &numberOfInputs, &ch1);
	printf("Number of inputs : %d\n", numberOfInputs);

	i = j = 0;

	// while(fscanf(filePointer ,"%d%c%c%c", &tempInt1, &ch1, &ch, &ch2) != EOF){
	// 	Transistion_Table[i][j] = tempInt1;
	// 	Transistion_Table[i][j+1] = int(ch);
	// 	j+=2;
	// 	if (ch2 == '\n')
	// 		numberOfInputs=j/2,j=0,i++;
	// }
	// numberOfStates = i;

	char str1[10] = {0};
	char str2[10] = {0};
	i = j = 0;
	while (1)
	{
		if (fscanf(filePointer, "%s%s", str1, str2) == EOF)
			break;
		// printf("State : %s\n", str2);
		tempInt1 = atoi(str1);
		if (tempInt1 > -1)
		{
			Transistion_Table[i][j].stateToTransistion = tempInt1;
			strcpy(Transistion_Table[i][j].output, str2);
		}
		else
		{
			Transistion_Table[i][j].stateToTransistion = -1;
			strcpy(Transistion_Table[i][j].output, "-1");
		}
		j++;
		if (j == numberOfInputs)
			j = 0, i++;
	}
	// while (1)
	// {
	// 	k = 0;
	// 	if (fscanf(filePointer, "%d%c%c%c", &tempInt1, &ch1, &ch, &ch2) == EOF)
	// 		break;

	// 	Transistion_Table[i][j].stateToTransistion = tempInt1;
	// 	printf("%d\n", Transistion_Table[i][j].stateToTransistion);
	// 	if (ch == '-')
	// 	{
	// 		Transistion_Table[i][j].output[k] = '\0';
	// 		printf("%s\n", Transistion_Table[i][j].output);
	// 		fscanf(filePointer, "%d", &tempInt1);
	// 	}
	// 	else
	// 	{
	// 		Transistion_Table[i][j].output[k] = ch;
	// 		while (ch2 != '\n' || ch2 != ' ')
	// 		{
	// 			k++;
	// 			Transistion_Table[i][j].output[k] = ch2;
	// 			// printf("%s\n", Transistion_Table[i][j].output);
	// 			// break;
	// 			fscanf(filePointer, "%c", &ch2);
	// 		}
	// 		j++;
	// 		// printf("%c\n", ch);
	// 		// 	break;
	// 		// printf("%s\n", Transistion_Table[i][j].output);
	// 		// break;
	// 		if (ch2 == '\n')
	// 			numberOfInputs = j, j = 0, i++;
	// 	}
	// 	if (i == 2)
	// 		break;
	// }
	numberOfStates = i;

	printf("Number of states : %d\n", numberOfStates);

	// exit(1);
	printf("Transistion Table\n");
	for (i = 0; i < numberOfStates; ++i)
	{
		printf("%2d | ", i);
		for (j = 0; j < numberOfInputs; j++)
		{
			printf("%2d %4s | ", Transistion_Table[i][j].stateToTransistion, Transistion_Table[i][j].output);
		}
		printf("\n");
	}

	fclose(filePointer);

	int flag = 0;
	char inputString[100] = {0};
	char outputString[100] = {0};
	int inputStringLen = 0;
	int outputStringLen = 0;

	while (1)
	{
		outputString[0] = '\0';

		printf("\n------------------------\nEnter input string ('#' to exit) : ");
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
			int oldState = currentState;
			currentState = Transistion_Table[currentState][tempInt1].stateToTransistion;

			if (currentState == -1)
			{
				printf("NO TRANSISTION\n");
				flag = 1;
				break;
			}
			strcat(outputString, Transistion_Table[oldState][tempInt1].output);
			printf("q%d / %s\n", currentState, Transistion_Table[oldState][tempInt1].output);
		}
		// outputString[i] = '\0';

		printf("\nOutput of Mealy Machine : %s\n", outputString);
	}

	printf("\nExiting...\n");

	return 0;
}