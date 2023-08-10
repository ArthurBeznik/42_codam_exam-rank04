#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TAGS 100
#define MAX_TAG_LENGTH 50

int ft_strlen(char *html)
{
	int i = 0;
	while (html[i])
		i++;
	return (i);
}

void process_opening_tag(char *opening_tag, char tags[][MAX_TAG_LENGTH], int *top)
{
	strncpy(tags[++(*top)], opening_tag, MAX_TAG_LENGTH);
}

bool is_self_closing_tag(char *tag)
{
	if (tag[0] == 'i' && tag[1] == 'm' && tag[2] == 'g' && tag[3] == '\0')
	{
		return (true);
	}
	return (false);
}

bool is_closed(char *closing_tag, char *tag)
{
	return (strncmp(tag, closing_tag, MAX_TAG_LENGTH) == 0);
}

bool process_closing_tag(char *closing_tag, char tag[][MAX_TAG_LENGTH], int *top)
{
	if ((*top) < 0 || !is_closed(closing_tag, tag[*top]))
	{
		return false;
	}
	(*top)--;
	return (true);
}

bool check_html(char *html)
{
	char tags[MAX_TAGS][MAX_TAG_LENGTH];
	int top = -1;
	int len = ft_strlen(html);

	if (html == NULL)
	{
		return (false);
	}
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
					while (html[i])
					{
						i++;
						continue;
					}
				}
				else
				{
					if (top == MAX_TAGS - 1)
					{
						write(1, "too many args\n", 14);
					}
				}
				process_opening_tag(opening_tag, tags, &top);
			}
		}
	}
	return top < 0;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(1, "KO\n", 3);
		return (1);
	}
	if (check_html(argv[1]))
	{
		write(1, "OK\n", 3);
		return (0);
	}
	else
	{
		write(1, "KO\n", 3);
		return (1);
	}
}
