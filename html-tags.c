#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include <stdio.h>

#define MAX_TAGS 100
#define MAX_TAG_LENGTH 50

int ft_strlen(char *html)
{
	int i = 0;
	while (html[i])
		i++;
	return (i);
}

/**
 * Opening tag increments top
*/
void process_opening_tag(char *opening_tag, char tags[][MAX_TAG_LENGTH], int *top)
{
	// fprintf(stderr, "%d\n", *top);

	/* Copy opening tag to tags in the corresponding tag level */
	strncpy(tags[++(*top)], opening_tag, MAX_TAG_LENGTH);

	// fprintf(stderr, "%d\n", *top);
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
	// fprintf(stderr, "closing_tag: %s\n", closing_tag);
	// fprintf(stderr, "tag: %s\n", tag);

	/* Compare current closing tag with the corresponding tag*/
	return (strncmp(tag, closing_tag, MAX_TAG_LENGTH) == 0);
}

/**
 * Closing tag decrements top
*/
bool process_closing_tag(char *closing_tag, char tag[][MAX_TAG_LENGTH], int *top)
{
	// fprintf(stderr, "%d\n", *top);

	/* Check if missing opening/closing tag error */
	if ((*top) < 0 || !is_closed(closing_tag, tag[*top]))
	{
		fprintf(stderr, "here\n");
		return false;
	}

	/* Decrement top */
	(*top)--;

	// fprintf(stderr, "%d\n", *top);
	
	return (true);
}

bool check_html(char *html)
{
	char tags[MAX_TAGS][MAX_TAG_LENGTH];
	int top = -1;
	int len = ft_strlen(html);

	/* Check for NULL error */
	if (html == NULL)
	{
		return (false);
	}

	/* Loop over length of str */
	for (int i = 0; i < len; i++)
	{
		/* Check if html tag */
		if (html[i] == '<')
		{
			/* Check if ending tag */
			if (html[i + 1] == '/')
			{
				i += 2; // skip tags
				int j = 0;
				char closing_tag[MAX_TAG_LENGTH];

				/* Loop over html until reaching ending tag > */
				while (html[i] != '>')
				{
					/* Copy current html char to closing_tag */
					closing_tag[j++] = html[i++];
				}

				/* NULL term closing_tag */
				closing_tag[j] = '\0';

				/* Check if closed properly */
				if (!process_closing_tag(closing_tag, tags, &top))
				{
					return (false);
				}
			}

			/* Is starting tag */
			else
			{
				i++;
				int j = 0;
				char opening_tag[MAX_TAG_LENGTH];

				/* Loop over html until reaching ending tag > */
				while (html[i] != '>')
				{
					/* Copy current html char to closing_tag */
					opening_tag[j++] = html[i++];
				}

				/* NULL term closing_tag */
				opening_tag[j] = '\0';

				/* Check if self closing tag (i.e. img) */
				if (is_self_closing_tag(opening_tag))
				{
					/* Loop over html */
					while (html[i])
					{
						i++;
						continue;
					}
				}

				/* Not a self closing tag */
				else
				{
					/* Check if we reached max tags */
					if (top == MAX_TAGS - 1)
					{
						write(1, "too many args\n", 14);
					}
				}

				/* Process opening tag */
				process_opening_tag(opening_tag, tags, &top);
			}
		}
	}
	return top < 0;
}

int main(int argc, char *argv[])
{
	/* Check argc error (min 2) */
	if (argc != 2)
	{
		write(1, "KO\n", 3);
		return (1);
	}

	/* Check html */
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
