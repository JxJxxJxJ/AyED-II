#ifndef ARRAY_HELPERS
#define ARRAY_HELPERS

unsigned int data_from_file(const char *path, unsigned int indexes[],
                            char letters[], unsigned int max_size);

#endif

void array_rebuild(char sorted[], unsigned int indexes[], char letters[],
                   unsigned int length);
