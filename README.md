# sudoku-validator

This program was created as a school project for Introduction to Operating Systems. It makes use of multi threads and is used to automatically check if a filled Sudoku puzzle is valid. The size of the puzzle is 9x9. The validation process is by checking all rows (or all columns) and all 9 sub-puzzles (size 3x3) for unique occurrence of numbers 1 to 9. The parent thread assigns a child thread to each section of the puzzle and only validates the puzzle once all children threads return a "true" (in other words valid) for each of their respective sections.
