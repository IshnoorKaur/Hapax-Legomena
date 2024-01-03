# Hapax Legomena Counter

## Introduction
This program is designed to process text files and identify hapax legomena, which are words that occur only once in an entire document. It utilizes linked lists to keep track of word occurrences and provides various options for displaying the results.

## Usage

./hapax [<options>] <datafile> [ <datafile> ...]

## Options
-d: Print out all data loaded before printing hapax legomena.
-h: Display help information.
-l <N>: Only print hapax legomena of length <N>. If no -l option is given, all hapax legomena are printed.

## Examples
``
./hapax smalldata.txt
./hapax -l 3 smalldata.txt
./hapax -l 4 smalldata.txt
``

## Program Output
The program provides information about the total word count, the tally of loaded words, and the hapax legomena from the specified data files.

## Example Output
``
$ ./hapax smalldata.txt
Total word count 10
Tally loaded
Hapax legomena from file 'smalldata.txt':
    a
    is
    line
    test
    this
    three
    there
    where
``

## Code Structure
The program consists of several components:

1. Word Parser
A parser is provided to extract words from text files. This functionality is implemented and doesn't require modification.

2. Linked List Tool
A linked list tool is included to hold words. This tool is also complete and does not need modification.

3. Tally Framework
A partially completed framework to tally up the count of words is provided. Your task is to complete this section.

4. Main Program
A partially completed mainline is available to initiate the processing for each data file. Your responsibility is to add data allocation and cleanup, as well as command line parsing.

## Data Structure Approach
The program utilizes an array of pointers to linked lists, with one linked list for each potential word length. This structure enables efficient storage and retrieval of word information based on their lengths.

## Implementation
To complete the implementation, follow the comments in the code that guide you to the specific sections requiring modification. Make sure to test the program with different options and data files to ensure its correctness.

## Building the Program
Compile the program using your preferred C compiler. For example:
``
gcc hapax.c -o hapax
``

## Running the Program
Execute the program with the desired options and data files:
``
./hapax [-d] [-h] [-l <N>] <datafile> [ <datafile> ...]
``
