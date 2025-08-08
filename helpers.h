#define MIN 33
#define MAX 126
#define SALT_LENGTH 40

/**
 * Returns int value of char key_string at index osc_index.
 * Increments/rolls over tracker.
 */
int key_oscillator(char *key_string, int *osc_index);

/// Returns if 1 if inputs match, else 0
int str_match(char *str1, char *str2);

/// Prints out help text
void print_help(void);

// Returns a char* to a salt of SALT_LENGTH length
char *salt_generate(void);
