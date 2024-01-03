#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_tally.h"

/** function to be passed in to llFree to delete allocated keys */
void deleteKey(LLNode *node, void *userdata)
{
	if (node->key != NULL)
	{
		free(node->key);
	}
}

/** Delete the contents of all of the word lists
 *
 * This function assumes that both the nodes and
 * the keys within the nodes have been allocated
 * using malloc() and need to be freed.
 */
void deleteWordLists(LLNode **wordListHeads, int maxLen)
{
	int i;

	for (i = 0; i <= maxLen; i++)
	{
		if (wordListHeads[i] != NULL)
		{
			llFree(wordListHeads[i], deleteKey, NULL);
			wordListHeads[i] = NULL;
		}
	}
}

int printData(char *filename, LLNode *wordListHeads[], int maxLen)
{
	LLNode *node;
	int i;

	printf("All word count data from file '%s':\n", filename);

	/**
	 * For each length, if the list is not null, print out
	 * the values in the list
	 */
	for (i = 0; i <= maxLen; i++)
	{
		node = wordListHeads[i];
		if (node != NULL)
		{
			printf("Length %d:\n", i);
			while (node != NULL)
			{
				printf("    '%s' %d\n", node->key, node->value);
				node = node->next;
			}
		}
	}
	return 1;
}

/** TODO: print out only the hapax legomena in a word list */
int printHapax(char *filename, LLNode *wordListHeads[],
			   int maxLen, int hapaxLength)
{
	// Add your code here
	printf("Hapax legomena from file '%s':\n", filename);

	if (hapaxLength == -1)
	{
		int i;
		for (i = 1; i <= maxLen; i++)
		{
			LLNode *node = wordListHeads[i];
			while (node != NULL)
			{
				printf("    %s\n", node->key);
				node = node->next;
			}
		}
	}
	else
	{
		LLNode *node = wordListHeads[hapaxLength];
		while (node != NULL)
		{
			// Check if the word occurs only once (hapax legomenon)
			if (node->value == 1)
			{
				printf("    %s\n", node->key);
			}
			node = node->next;
		}
	}

	return 1;
}

/* print out the command line help */
void usage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "Find and print the hapax legomena in one or more files.\n");
	fprintf(stderr, "A \"hapax legomenon\" is a word that occurs only once in the file\n");

	fprintf(stderr, "\n");
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "    hapax [<options>] <datafile> [ <datafile> ...]\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "-d     : print out all data loaded before printing hapax legomena.\n");
	fprintf(stderr, "-h     : this help.  You are looking at it.\n");
	fprintf(stderr, "-l <N> : only print hapax legomena of length <N>.\n");
	fprintf(stderr, "       : If no -l option is given, all hapax legomena are printed.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Sample command line:\n");
	fprintf(stderr, "    hapax -l 5 smalldata.txt");
	fprintf(stderr, "\n");
	fprintf(stderr, "This example would print all words of length 5 that exist in the\n");
	fprintf(stderr, "file \"smalldata.txt\".\n");
	fprintf(stderr, "\n");

	// exit the program
	exit(1);
}

/**
 * Program mainline
 */

// define the maximum length of word we will look for, and by extension,
// the number of entries that must be in the array of word lists
#define MAX_WORD_LEN 24

int main(int argc, char **argv)
{
	int i, shouldPrintData = 0, didProcessing = 0, printHapaxLength = -1;

	/** TODO: allocate an array of list heads of the required size */

	LLNode *wordListHeads[MAX_WORD_LEN + 1];

	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			// TODO: Put your code to process the command line options here
			for (int j = 1; j < argc; j++)
			{
				if (strcmp(argv[i], "-d") == 0)
				{
					// print out all data loaded before printing hapax legomena
					// sets a flag to print data
					shouldPrintData = 1;
				}
				else if (strcmp(argv[i], "-h") == 0)
				{
					// Display help and exit. This help. You are looking at it
					usage();
					return 0;
				}
				// only print hapax legomena of length <N>
				else if (strcmp(argv[i], "-l") == 0)
				{

					// Check if there is another argument for hapax length
					if (i + 1 < argc)
					{
						// if usere enters a negative printHapaxLength or if it is greater than MAX_WORD_LEN

						// Parse and store the hapax legomena length
						// atoi helps us convert string to an interger
						printHapaxLength = atoi(argv[i + 1]);
						if (printHapaxLength < 0 || printHapaxLength > MAX_WORD_LEN)
						{
							printf("Invalid hapax length: %d. Please specify a valid length between 0 and %d.\n", printHapaxLength, MAX_WORD_LEN);
							return 0;
						}
						// Skip the next argument
						i++;
					}
					else
					{
						// Handles the case in which -l is missing an argument
						fprintf(stderr, "Error: -l option requires an argument\n");
						// Display help message
						usage();
						// Exit
						return 1;
					}
				}
			}
		}
		else
		{
			// Once you have set up your array of word lists, you
			// should be able to pass them into this function
			if (tallyWordsInFile(argv[i], wordListHeads, MAX_WORD_LEN) == 0)
			{
				fprintf(stderr, "Error: Processing '%s' failed -- exitting\n",
						argv[i]);
				return 1;
			}

			didProcessing = 1;

			printf("Tally loaded\n");

			/**
			 * conditionally print out all the words loaded, based
			 * on the command line option
			 */
			if (shouldPrintData == 1)
			{
				// this should also work once you have allocated the
				// array of lists properly
				printData(argv[i], wordListHeads, MAX_WORD_LEN);
			}

			/** print out all the hapax legomena that we have found */
			printHapax(argv[i], wordListHeads, MAX_WORD_LEN, printHapaxLength);

			// TODO: clean up any memory that we have allocated in this loop
			deleteWordLists(wordListHeads, MAX_WORD_LEN);
		}
	}

	if (!didProcessing)
	{
		fprintf(stderr, "No data processed -- provide the name of"
						" a file on the command line\n");
		usage();
		return 1;
	}

	// TODO: clean up any remaining memory that we have allocated
	deleteWordLists(wordListHeads, MAX_WORD_LEN);
	return 0;
}
