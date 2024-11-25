#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 1024

// ANSI escape codes for coloring text
#define RESET_COLOR "\033[0m"
#define HIGHLIGHT_COLOR "\033[1;31m" // Red color

// Function to perform case-insensitive comparison (returns pointer to the match)
char *case_insensitive_strstr(const char *haystack, const char *needle) {
    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;

        while (*n && (tolower(*h) == tolower(*n))) {
            h++;
            n++;
        }

        if (!*n) return (char *)haystack; // Match found

        haystack++;
    }
    return NULL; // No match found
}

void search_file(FILE *file, const char *pattern, int ignore_case, int invert_match, int show_line_numbers) {
    char line[MAX_LINE_LEN];
    int line_number = 0;

    while (fgets(line, MAX_LINE_LEN, file)) {
        line_number++;
        char *found = NULL;

        if (ignore_case) {
            // Case-insensitive search
            found = case_insensitive_strstr(line, pattern);
        } else {
            // Case-sensitive search
            found = strstr(line, pattern);
        }

        int is_match = (found != NULL);
        if (invert_match) is_match = !is_match;

        if (is_match) {
            if (show_line_numbers) printf("%d:", line_number);

            char *start = line;
            char *match = found;

            while (match != NULL) {
                // Print text before the match
                fwrite(start, 1, match - start, stdout);

                // Highlight the match
                printf(HIGHLIGHT_COLOR "%.*s" RESET_COLOR, (int)strlen(pattern), match);

                // Move past the match
                start = match + strlen(pattern);

                // Find next match in case of multiple occurrences
                match = ignore_case ? case_insensitive_strstr(start, pattern) : strstr(start, pattern);
            }

            // Print the remaining part of the line
            printf("%s", start);
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
