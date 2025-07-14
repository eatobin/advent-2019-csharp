#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Memory {
    int *contents;
    int length;
} aMemory;

char *file_to_string(const char *filename) {
    char c;
    int i = 0;
    int length = 0;

    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *string = malloc(sizeof(char) * (length + 1));

    while ((c = fgetc(file)) != EOF) {
        string[i] = c;
        i++;
    }
    string[i] = '\0';
    fclose(file);
    return string;
}

int return_memory_length(const char *string) {
    int count = 0;

    if (string != NULL) {
        char c;
        int i = 0;
        while ((c = string[i]) != '\0') {
            if (c == ',') {
                count++;
            }
            i++;
        }
    }
    return count + 1;
}

int *create_initialized_int_array(const int memory_length) {
    int *ret = malloc(memory_length * sizeof(int));
    if (!ret) return NULL;

    for (int i = 0; i < memory_length; ++i)
        ret[i] = -1;

    return ret;
}

int *make_memory(int *memory, char *string) {
    if (memory == NULL) {
        exit(1);
    }
    int index = 0;
    const char *token_at_index = strtok(string, ",");
    while (token_at_index) {
        memory[index] = atoi(token_at_index);
        token_at_index = strtok(NULL, ",");
        index++;
    }
    return memory;
}

aMemory return_memory(const char *file_path) {
    aMemory memory;

    char *string = file_to_string(file_path);
    const int memory_length = return_memory_length(string);
    int *initialized_int_array = create_initialized_int_array(memory_length);
    memory.contents = make_memory(initialized_int_array, string);
    memory.length = memory_length;

    free(string);
    string = NULL;

    return memory;
}
