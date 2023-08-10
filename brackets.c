#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

int check_closing_correctly(char opening, char closing)
{
	if ((opening == '(' && closing == ')') || (opening == '[' && closing == ']') || (opening == '{' && closing == '}'))
		return (1);
	return (0);
}

void check_string(char *str)
{
	int buffCount = 0;
	char buff[4000];

	/* Check for NULL error */
	if (str == NULL)
	{
		write(1, "\n", 1);
		return;
	}
	
	/* Loop over each char of the string */
	for (int i = 0; str[i]; i++)
	{
		/* Check if opening bracket */
		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
		{
			/* Copy bracket char to buff */
			buff[buffCount++] = str[i];
		}

		/* Check if closing bracket */
		else if (str[i] == ')' || str[i] == '}' || str[i] == ']')
		{
			/**
			 * Check if buffCount > 0 (not empty) and if bracket is closed correctly
			 * 	by sending the previous char in the buffer and the current char of the str
			*/
			if (buffCount > 0 && check_closing_correctly(buff[buffCount - 1], str[i]))
			{
				/* Decrement buffCount (one opening = +1 and one closing = -1 => 0) */
				buffCount--;
			}

			/* Error */
			else
			{
				buffCount = -1;
				break;
			}
		}
	}

	/* If closed properly, buffCount = 0 */
	if (buffCount != 0)
	{
		write(1, "error\n", 6);
	}
	else
	{
		write(1, "OK\n", 3);
	}
}

int main(int argc, char *argv[])
{
	/* Check argc error (min 2) */
	if (argc < 2)
	{
		write(1, "error\n", 6);
		return (1);
	}
	/* Loop until no args left */
	int i = 1;
	while (argv[i])
	{
		check_string(argv[i]);
		i++;
	}
	return (0);
}
