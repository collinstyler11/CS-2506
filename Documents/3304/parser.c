#include <stdio.h>
#define MAX_LENGTH 40

int main (int argc, char *argv[])
{
	char input[MAX_LENGTH];
	printf("Enter an input:   ");
	scanf("%s", input);
	
	char curr = input[0];
	int num = -1;
	int i = 0;
	while (curr != '\n')
	{		
		if (curr == '+')
		{
			i = i + 1;
						
		}
		else if (curr == '-')
		{
			
		}
		else if (curr == '*')
		{
			
		}
		else if (curr == '/')
		{
		
		}
		else
		{
			num = curr - '0';
			i = i + 1;
			printf("%d\n", num);
		}
		
		curr = input[i];
	}
	return 0;
}


