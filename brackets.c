#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#define MAX_TAGS 100
#define MAX_TAG_LENGTH 50

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

	if (str == NULL)
	{
		write(1, "\n", 1);
		return;
	}
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
		{
			buff[buffCount++] = str[i];
		}
		else if (str[i] == ')' || str[i] == '}' || str[i] == ']')
		{
			if (buffCount > 0 && check_closing_correctly(buff[buffCount - 1], str[i]))
			{
				buffCount--;
			}
			else
			{
				buffCount = -1;
				break;
			}
		}
	}
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
	int i = 1;
	if (argc < 2)
	{
		write(1, "error\n", 6);
		return (1);
	}
	while (argv[i])
	{
		check_string(argv[i]);
		i++;
	}
	return (0);
}

bool check_tags(char *html)
{
	char tags[MAX_TAGS][MAX_TAG_LENGTH];
	int top = -1;
	int len = ft_strlen(html);
	for (int i = 0; i < len; i++)
	{
		if (html[i] == '<')
		{
			if (html[i + 1] == '/')
			{
				i += 2;
				int j = 0;
				char closing_tag[MAX_TAG_LENGTH];
				while (html[i] != '>')
				{
					closing_tag[j++] = html[i++];
				}
				closing_tag[j] = '\0';
				if (!process_closing_tag(closing_tag, tags, &top))
				{
					return (false);
				}
			}
			else
			{
				i++;
				int j = 0;
				char opening_tag[MAX_TAG_LENGTH];
				while (html[i] != '>')
				{
					opening_tag[j++] = html[i++];
				}
				opening_tag[j] = '\0';
				if (is_self_closing_tag(opening_tag))
				{
					while (html[i] != '>')
						i++;
				}
				else
				{
					if (top == MAX_TAGS - 1)
					{
						write(1, "too many tags\n", 14);
					}
				}
				process_opening_tag(opening_tag, tags, &top);
			}
		}
	}
	return top < 0;
}
