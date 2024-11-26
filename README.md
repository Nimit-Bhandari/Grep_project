# Custom Grep Command Implementation

A simplified yet powerful implementation of the Linux `grep` command written in **C**. This utility allows users to search for specific patterns in text files, featuring case-insensitive search, word highlighting, and support for standard input when no file is provided.

## Features

- **Case-Insensitive Search**: Find text patterns regardless of letter case.
- **Word Highlighting**: Matches are highlighted in color for better visibility.
- **Flexible Input**:  
  - Reads from files specified as command-line arguments.  
  - Accepts input from `stdin` if no files are provided.
- **Line Number Display**: Displays the line number for every match.

## Installation

### Compilation

To compile the code, use the following command:

```bash
gcc -o custom_grep custom_grep.c
