#include<stdio.h>

#define MAX_TRANSISTION 100
#define MAX_VARIABLES 100

int Read(char* str){
	int i = 0;
	while(1){
		str[i]=getchar();
		if(str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			return i;			
		}
		i++;
	}
}

int main(){

	int tempInt1, tempInt2;
	char ch1, ch2, ch;
	int i = 0, j = 0;

	FILE *filePointer = NULL;
	filePointer = fopen("MOORE.txt", "r");

	if(filePointer == NULL){
		printf("Unable to open MOORE.txt\n");
		return 1;
	}

	int Transistion_Table[MAX_TRANSISTION][MAX_VARIABLES*2];
	
	for (i = 0; i < MAX_TRANSISTION; ++i)
		for (j = 0; j < MAX_VARIABLES; ++j)
			Transistion_Table[i][j] = -1;

	int initialState = -1;
	int currentState = -1;
	int numberOfTransisation = 0;
	int numberOfVariables = 0;

	fscanf(filePointer ,"%d%c", &initialState,&ch1);
	printf("Initial state : %d\n", initialState);

 	i=j=0;

	while(1){
		if(fscanf(filePointer ,"%c%c", &ch, &ch2) == EOF) break;
		Transistion_Table[i][j] = int(ch);
		j++;
		while(ch2 != '\n')
		{
			fscanf(filePointer ,"%d%c", &tempInt1, &ch2);
			Transistion_Table[i][j] = tempInt1;			
			j++;
		}
		numberOfVariables=j-1,j=0,i++;
	}
	numberOfTransisation = i;

	printf("Transistion Table\n");
	for (i = 0; i < numberOfTransisation; ++i)
	{
		j = 0;
		printf("%c ", char(Transistion_Table[i][j]));
		for (j = 1; j < numberOfVariables + 1; j++)
		{
			printf("%2d ", Transistion_Table[i][j]);
		}
		printf("\n");
	}
	fclose(filePointer);

	int flag = 0;
	char inputString[100] = {0};
	char outputString[100] = {0};
	int inputStringLen = 0;
	int outputStringLen = 0;

	while(1)
	{
		printf("\n------------------------\nEnter input string ('#' to exit) : ");
		// scanf("%s", inputString);
		inputStringLen = Read(inputString);

		if(inputString[0] == '#')
			break;

		printf("Input string : %s, Input string len : %d\n\n", inputString, inputStringLen);

		currentState = initialState;
		flag = 0;
		for (i = 0; i < inputStringLen; ++i)
		{
			tempInt1 = inputString[i] - '0';

			printf("string and state transition : %d , q%d / %c -> ", tempInt1, currentState, char(Transistion_Table[currentState][0]));
			int oldState = currentState;
			currentState = Transistion_Table[currentState][tempInt1+1];
			outputString[i] = char(Transistion_Table[currentState][0]);
			
			if (currentState == -1)
			{
				printf("NO TRANSISTION\n");
				flag = 1;
				break;
			}
			printf("q%d / %c\n", currentState, outputString[i]);
		}	
		outputString[i] = '\0';

		printf("\nOutput of Moore Machine : %s\n", outputString);

	}

	printf("\nExiting...\n");
	
	return 0;
}