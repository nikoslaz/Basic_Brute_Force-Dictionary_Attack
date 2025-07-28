#include"md5.h"

#define TARGET_1 "d077f244def8a70e5ea758bd8352fcd8"
#define TARGET_2 "df53ca268240ca76670c8566ee54568a"
#define TARGET_3 "6b718641741f992e68ec3712718561b8"

#define ROCKYOU_FILE "rockyou.txt"

int call_brute_force() {
    // Brute force all combinations
    // Define the character: a-z and 0-9
    const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    const int charset_size = sizeof(charset) - 1; // Exclude null terminator

    // Brute force all 8-character combinations
    for (int i0 = 0; i0 < charset_size; i0++) {
        for (int i1 = 0; i1 < charset_size; i1++) {
            for (int i2 = 0; i2 < charset_size; i2++) {
                for (int i3 = 0; i3 < charset_size; i3++) {
                    for (int i4 = 0; i4 < charset_size; i4++) {
                        for (int i5 = 0; i5 < charset_size; i5++) {
                            for (int i6 = 0; i6 < charset_size; i6++) {
                                for (int i7 = 0; i7 < charset_size; i7++) {
                                    // Create the guess string
                                    char guess[9]; // 8 characters + null terminator
                                    guess[0] = charset[i0];
                                    guess[1] = charset[i1];
                                    guess[2] = charset[i2];
                                    guess[3] = charset[i3];
                                    guess[4] = charset[i4];
                                    guess[5] = charset[i5];
                                    guess[6] = charset[i6];
                                    guess[7] = charset[i7];
                                    guess[8] = '\0';

                                    printf("Trying: %s\n", guess); // Print the current guess

                                    // Hash the guess
                                    char* hash = md5(guess, strlen(guess));
                                    if (hash == NULL) {
                                        fprintf(stderr, "Error hashing string: %s\n", guess);                                        
                                        return 1;
                                    }

                                    // Keep track if any target is found for this guess
                                    int found = 0;
                                    // Compare the hash with the target hashes
                                    if (strcmp(hash, TARGET_3) == 0) {
                                        printf("Found match for TARGET_1: %s\n", guess);
                                        found = 1;
                                    }

                                    // Free allocated memory for the hash
                                    free(hash);

                                    // If any target is found, break out of the loop
                                    if (found) {
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printf("No match found for any TARGET\n");
    return 0;
}

int call_dictionary_attack() {
    FILE* file = fopen(ROCKYOU_FILE, "r");
    if (!file) {
        fprintf(stderr, "Can't open %s\n", ROCKYOU_FILE);
        perror("fopen");
        return 1;
    }

    char line[100];

    while (fgets(line, 100, file) != NULL) {
        // Trim newline character
        line[strcspn(line, "\n")] = 0;

        char* hash = md5(line, strlen(line));

        if (strcmp(hash, TARGET_2) == 0) {
            printf("Found match for TARGET: %s\n", line);
            exit(0);
        }
    }

    fclose(file); 
    printf("No match found in %s\n", ROCKYOU_FILE);

    return 1;
}

int main() {
    //Call the brute force function
    // int result = call_brute_force();
    // if (result != 0) {
    //     fprintf(stderr, "Error in brute force function\n");
    //     return result;
    // }
    // printf("Brute force completed\n");

    //Call the dictionary attack function
    int result2 = call_dictionary_attack();
    if (result2 != 0) {
        fprintf(stderr, "Error in dictionary attack function\n");
        return result2;
    }
    printf("Dictionary attack completed\n");

    return 0;
} 