# nonogramSolver
[Nonogram][1] solver with a command line interface. It takes input numbers in a file, where each line holds inputs of a row or a column as space-separated numbers. For a *n*x*m* nonogram, first *n* lines should have *n* row inputs, followed by an empty line, followed by *m* lines of *m* column inputs. Examples are provided in the sample_inputs directory.

Usage:

./nonogramSolver \<input_file\> [-i]

    -i    Info flag. Print which line is being processed and 'before' & 'after' line state for every iteration.

Algorithm:
Each *line* is independently processed, where a *line* corresponds to a row or a column. A line is processed in two steps. In the first step, the input blocks are pushed (1) to the beginning and (2) to the end of the line, and their intersection is taken complying with to the block indices as in the following example:

legend: filled=@ , empty=_ , unknown=?

Input block sizes: 2 5

|cell # |0|1|2|3|4|5|6|7|8|9|10|11|12|
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|**initial line state**|?|_|?|?|?|?|?|@|?|?|?|?|?|
|**left-aligned**      |_|_|@|@|_|@|@|@|@|@|_|_|_|
|**right-aligned**     |_|_|_|_|@|@|_|@|@|@|@|@|_|
|**intersection**      |_|_| | | | | |@|@|@| | |_|
|**step 1 result**     |_|_|?|?|?|?|?|@|@|@|?|?|_|

The second step checks the unknown cells that have the same value in both left- and right-aligned lines but with different block indices. For each such cell, it checks whether there is a feasible solution if the cell value is different. Example:

Input block sizes: 2 2

|cell # |0|1|2|3|4|5|6|7|8|9|10|
|---|---|---|---|---|---|---|---|---|---|---|---|
|**initial line state**                  |?|?|?|?|?|_|@|?|?|?|?|
|**left-aligned**                        |@|@|_|_|_|_|@|@|_|_|_|
|**right-aligned**                       |_|_|_|_|_|_|@|@|_|@|@|
|**step 1 result**                       |?|?|?|?|?|_|@|?|?|?|?|
|**cell value is feasible otherwise**    | | |y|y|y| | |N|N| | |
|**step 2 result**                       |?|?|?|?|?|_|@|@|_|?|?|

Lines to process are selected using a simple priority queue. Initially, the lines with the largest block sizes are processed. Then, the lines with the highest number of recently modified cells are processed.

[1]: https://en.wikipedia.org/wiki/Nonogram
