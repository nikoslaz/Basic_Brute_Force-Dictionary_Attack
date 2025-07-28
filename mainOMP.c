#include"md5.h"
#include <omp.h>

#define TARGET_1 "d077f244def8a70e5ea758bd8352fcd8"
#define TARGET_2 "df53ca268240ca76670c8566ee54568a"
#define TARGET_3 "6b718641741f992e68ec3712718561b8"

#define ROCKYOU_FILE "rockyou.txt"

static int found;
static char found_password[9];


int call_brute_force() {
    // Brute force all combinations
    // Define the character: a-z and 0-9
    const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    const int charset_size = sizeof(charset) - 1; // Exclude null terminator

    // Global variables initialization
    found = 0;
    found_password[0] = '\0';

    // Brute force all 8-character combinations
    #pragma omp parallel for collapse(8) schedule(dynamic) shared(found, found_password, charset, charset_size)
    for (int i0 = 0; i0 < charset_size; i0++) {
        for (int i1 = 0; i1 < charset_size; i1++) {
            for (int i2 = 0; i2 < charset_size; i2++) {
                for (int i3 = 0; i3 < charset_size; i3++) {
                    for (int i4 = 0; i4 < charset_size; i4++) {
                        for (int i5 = 0; i5 < charset_size; i5++) {
                            for (int i6 = 0; i6 < charset_size; i6++) {
                                for (int i7 = 0; i7 < charset_size; i7++) {
                                    if (found) {
                                        #pragma omp cancel for
                                    }
                                    
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

                                    // Hash the guess
                                    char* hash = md5(guess, strlen(guess));
                                    if (hash == NULL) {
                                        #pragma omp critical
                                        fprintf(stderr, "Error hashing string: %s\n", guess);                                        
                                        continue;
                                    }

                                    // Compare the hash with the target hash
                                    if (strcmp(hash, TARGET_3) == 0) {
                                        #pragma omp critical
                                        {
                                            if (!found) {
                                                found = 1;
                                                strcpy(found_password, guess);
                                                printf("Found match for TARGET_3: %s\n", guess);
                                            }
                                        }
                                        free(hash);
                                        #pragma omp cancel for
                                    }

                                    // Free allocated memory for the hash
                                    free(hash);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (found) {
        printf("Password found: %s\n", found_password);
        return 0;
    } else {
        printf("No match found for TARGET_3.\n");
        return 1;
    }

    return 0;
}

int main() {
    //Call the brute force function
    int result = call_brute_force();
    if (result != 0) {
        fprintf(stderr, "Error in brute force function\n");
        return result;
    }
    printf("Brute force completed\n");

    return 0;
} 