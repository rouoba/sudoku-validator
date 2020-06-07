# sudoku-validator

This program was created as a school project for Introduction to Operating Systems. It makes use of multi threads and is used to automatically check if a filled Sudoku puzzle is valid. The size of the puzzle is 9x9. The validation process is by checking all rows (or all columns) and all 9 sub-puzzles (size 3x3) for unique occurrence of numbers 1 to 9. The parent thread assigns a child thread to each section of the puzzle and only validates the puzzle once all children threads return a "true" (in other words valid) for each of their respective sections.

The data structure used was vectors as they are dynamic. A validation was basically comparing the "correct" vector containing numbers 1 to 9, to a row, columnn, or "box"(3x3 grid of numbers). 


Heap corruption 
Error occurring when running the program, seemingly due to a lack of memory. We initially thought about changing the heap size, but no such modification was feasibble with the lab computers (it might also not be a safe idea). The problem was solved by reducing the number of concurrent threads (initially set to a staggering 11: 1 for all rows, 1 for all columns, and one for each of the nine smaller "boxes" that make up the entire puzzle) to 3 at a time.
