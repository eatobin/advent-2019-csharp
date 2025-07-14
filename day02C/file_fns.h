#pragma once
char *file_to_string(const char *filename);
int return_memory_length(const char *string);
int *create_initialized_int_array(int memory_length);
int *make_memory(int *memory, char *string);
struct Memory return_memory(const char *file_path);
