# Custom Grep Command Implementation

This project is a **C** implementation of the `grep` command, a powerful utility used to search for patterns in text files. The custom version focuses on simplicity and essential features, such as case-insensitive searching, word highlighting, and support for standard input when no file is provided.

## Features

- **Case-Insensitive Search**: Search for patterns regardless of letter case.
- **Word Highlighting**: Matched patterns are highlighted for better readability in the output.
- **File and Standard Input Support**:  
  - Search text in one or multiple files.  
  - If no file is specified, the program reads from `stdin`.
- **Line Number Display**: Displays the line numbers where the matched patterns occur.

## Installation

### Prerequisites

Make sure you have a **C compiler** (like **GCC**) installed on your machine.

### Clone the Repository

First, clone this repository to your local machine:

`git clone https://github.com/yourusername/custom-grep.git`

Then, navigate to the project directory:

`cd custom-grep`

### Compilation

To compile the project, run the following command in your terminal:

`gcc -o custom_grep custom_grep.c`

This will create an executable named `custom_grep`.

## Usage

Once the program is compiled, you can use it in the terminal for searching patterns in files or input streams.

### Basic Usage

- To search for a pattern in a file:

`./custom_grep "pattern" filename.txt`

- To search for a pattern in multiple files:

`./custom_grep "pattern" file1.txt file2.txt`

- To perform a case-insensitive search:

`./custom_grep -i "pattern" filename.txt`

- To read from standard input (`stdin`) if no files are provided:

`echo "This is a test string." | ./custom_grep "test"`

### Command-Line Options

- **`-i`**: Perform a **case-insensitive** search (e.g., "Pattern" will match "pattern").
- **No file input**: When no files are provided, input can be piped or typed directly in the terminal.

### Example Output

For a file named `sample.txt` containing:

