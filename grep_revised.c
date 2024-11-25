#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 1024

void search_file(FILE *file, const char *pattern, int ignore_case, int invert_match, int show_line_numbers) {
    char line[MAX_LINE_LEN];
    int line_number = 0;

    while (fgets(line, MAX_LINE_LEN, file)) {
        line_number++;
        char *found = NULL;

        // Perform case-insensitive comparison if required
        if (ignore_case) {
            char line_lower[MAX_LINE_LEN], pattern_lower[MAX_LINE_LEN];
            strncpy(line_lower, line, MAX_LINE_LEN);
            strncpy(pattern_lower, pattern, MAX_LINE_LEN);

            // Convert line and pattern to lowercase
            for (int i = 0; line_lower[i]; i++) line_lower[i] = tolower(line_lower[i]);
            for (int i = 0; pattern_lower[i]; i++) pattern_lower[i] = tolower(pattern_lower[i]);

            found = strstr(line_lower, pattern_lower);
        } else {
            found = strstr(line, pattern);
        }

        int is_match = (found != NULL);
        if (invert_match) is_match = !is_match;

        if (is_match) {
            if (show_line_numbers) printf("%d:", line_number);
            printf("%s", line);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: mygrep [OPTIONS] PATTERN [FILE...]\n");
        return 1;
    }

    const char *pattern = NULL;
    int ignore_case = 0, invert_match = 0, show_line_numbers = 0;
    int file_start_index = 2;

    // Parse options
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            // Parse individual options
            if (strchr(argv[i], 'i')) ignore_case = 1;
            if (strchr(argv[i], 'v')) invert_match = 1;
            if (strchr(argv[i], 'n')) show_line_numbers = 1;
        } else {
            // If it's not an option, it's the pattern
            pattern = argv[i];
            file_start_index = i + 1;
            break;
        }
    }

    if (!pattern) {
        fprintf(stderr, "Error: No pattern provided.\n");
        return 1;
    }

    // If no files are provided, read from stdin
    if (file_start_index == argc) {
        search_file(stdin, pattern, ignore_case, invert_match, show_line_numbers);
    } else {
        // Process files
        for (int i = file_start_index; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (!file) {
                fprintf(stderr, "Error: Cannot open file %s\n", argv[i]);
                continue;
            }
            search_file(file, pattern, ignore_case, invert_match, show_line_numbers);
            fclose(file);
        }
    }

    return 0;
}
