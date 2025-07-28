Nikolaos Lazarids - csd4922

## Basic Brute-Force Attack

This section details a basic brute-force attack designed to crack short passwords (up to 8 characters) protected by MD5 hashing.

1.  **Character Space:** A character set comprising lowercase letters (`a` through `z`) and digits (`0` through `9`) is defined.
2.  **Combination Generation:** The program iterates through all possible string combinations using the defined character set, starting from length 1 up to a maximum length of 8 characters.
3.  **Hashing and Comparison:** In each iteration:
    *   The current string combination is generated.
    *   The MD5 hash of this string is calculated.
    *   The calculated hash is compared against a list of target MD5 hashes.
    *   If a match is found, the corresponding plaintext password has been successfully recovered.

## Dictionary Attack

This section details a dictionary attack using a common password list (`rockyou.txt`) to crack MD5 hashes.

1.  **Password List:** The program reads passwords line by line from the `rockyou.txt` file.
2.  **Hashing and Comparison:** For each password read from the file:
    *   The MD5 hash of the password string is calculated.
    *   The calculated hash is compared against a list of target MD5 hashes.
    *   If a match is found, the corresponding plaintext password has been successfully recovered.
