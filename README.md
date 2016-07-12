# nonogramSolver
[Nonogram][1] solver with a command line interface.

Algorithm:
Each *line* is independently processed, where a *line* corresponds to a row or a column. There are two steps for processing each line. In the first step, the input blocks are pushed (1) to the beginning and (2) to the end of the line, and their intersection is taken complying with to the block indices as in the following example:

legend: filled=@ , empty=_ , unknown=?

Input block sizes: 2 5

|cell # |0|1|2|3|4|5|6|7|8|9|10|11|12|
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|initial line state|?|_|?|?|?|?|?|@|?|?|?|?|?|
|left-aligned      |_|_|@|@|_|@|@|@|@|@|_|_|_|
|right-aligned     |_|_|_|_|@|@|_|@|@|@|@|@|_|
|intersection      |_|_| | | | | |@|@|@| | |_|
|step 1 result     |_|_|?|?|?|?|?|@|@|@|?|?|_|

The second step checks the unknown cells that have the same value in both left- and right-aligned lines but with different block indices. For each such cell, it checks whether there is a feasible solution if the cell value is different. Example:

Input block sizes: 2 2

|cell # |0|1|2|3|4|5|6|7|8|9|10|
|---|---|---|---|---|---|---|---|---|---|---|---|
|initial line state                  |?|?|?|?|?|_|@|?|?|?|?|
|left-aligned                        |@|@|_|_|_|_|@|@|_|_|_|
|right-aligned                       |_|_|_|_|_|_|@|@|_|@|@|
|step 1 result                       |?|?|?|?|?|_|@|?|?|?|?|
|cell value is feasible otherwise    | | |y|y|y| | |N|N| | |
|result                              |?|?|?|?|?|_|@|@|_|?|?|

Lines to process are selected using a simple priority queue. Initially, the lines with the largest block sizes are processed. Then, the lines with the highest number of recently modified cells are processed.

[1]: https://en.wikipedia.org/wiki/Nonogram
