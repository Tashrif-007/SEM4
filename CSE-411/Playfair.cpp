#include <iostream>
#include <cctype>
#include <cstring>

const int SIZE = 5;

// Function to remove duplicate letters from the key
std::string removeDuplicates(const std::string& input) {
    std::string result = "";
    for (char ch : input) {
        if (std::isalpha(ch) && result.find(ch) == std::string::npos) {
            result += std::toupper(ch);
        }
    }
    return result;
}

// Function to initialize the key matrix based on the provided key
void initializeKeyMatrix(char keyMatrix[SIZE][SIZE], const std::string& key) {
    std::string keyWithoutDuplicates = removeDuplicates(key + "ABCDEFGHIKLMNOPQRSTUVWXYZ");
    int k = 0;

    // Fill the key matrix with the key and remaining alphabet
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            keyMatrix[i][j] = keyWithoutDuplicates[k++];
        }
    }
}

// Function to get the position of a letter in the key matrix
void getLetterPosition(const char keyMatrix[SIZE][SIZE], char letter, int& row, int& col) {
    if (letter == 'J') letter = 'I'; // Treat 'J' as 'I'
    for (row = 0; row < SIZE; ++row) {
        for (col = 0; col < SIZE; ++col) {
            if (keyMatrix[row][col] == letter) {
                return;
            }
        }
    }
}

// Function to encrypt a pair of letters
std::string encryptPair(const char keyMatrix[SIZE][SIZE], char first, char second) {
    int row1, col1, row2, col2;
    getLetterPosition(keyMatrix, first, row1, col1);
    getLetterPosition(keyMatrix, second, row2, col2);

    if (row1 == row2) {
        // Same row, shift columns
        return std::string(1, keyMatrix[row1][(col1 + 1) % SIZE]) + keyMatrix[row1][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        // Same column, shift rows
        return std::string(1, keyMatrix[(row1 + 1) % SIZE][col1]) + keyMatrix[(row2 + 1) % SIZE][col2];
    } else {
        // Form a rectangle, swap columns
        return std::string(1, keyMatrix[row1][col2]) + keyMatrix[row2][col1];
    }
}

// Function to decrypt a pair of letters
std::string decryptPair(const char keyMatrix[SIZE][SIZE], char first, char second) {
    int row1, col1, row2, col2;
    getLetterPosition(keyMatrix, first, row1, col1);
    getLetterPosition(keyMatrix, second, row2, col2);

    if (row1 == row2) {
        // Same row, shift columns back
        return std::string(1, keyMatrix[row1][(col1 - 1 + SIZE) % SIZE]) + keyMatrix[row1][(col2 - 1 + SIZE) % SIZE];
    } else if (col1 == col2) {
        // Same column, shift rows back
        return std::string(1, keyMatrix[(row1 - 1 + SIZE) % SIZE][col1]) + keyMatrix[(row2 - 1 + SIZE) % SIZE][col2];
    } else {
        // Form a rectangle, swap columns back
        return std::string(1, keyMatrix[row1][col2]) + keyMatrix[row2][col1];
    }
}

int main() {
    char keyMatrix[SIZE][SIZE];
    std::string key;

    // Input the key
    std::cout << "Enter the key (without spaces): ";
    std::cin >> key;

    // Initialize the key matrix
    initializeKeyMatrix(keyMatrix, key);

    std::string plaintext;
    std::cout << "Enter the plaintext (uppercase): ";
    std::cin >> plaintext;

    std::string ciphertext = "";

    // Encrypt the plaintext
    for (size_t i = 0; i < plaintext.length(); i += 2) {
        char first = plaintext[i];
        char second = (i + 1 < plaintext.length()) ? plaintext[i + 1] : 'X'; // Add 'X' if the last pair has only one letter
        ciphertext += encryptPair(keyMatrix, first, second);
    }

    std::cout << "Encrypted Text: " << ciphertext << std::endl;

    std::string decryptedText = "";

    // Decrypt the ciphertext
    for (size_t i = 0; i < ciphertext.length(); i += 2) {
        char first = ciphertext[i];
        char second = ciphertext[i + 1];
        decryptedText += decryptPair(keyMatrix, first, second);
    }

    
    std::cout << "Decrypted Text: " << decryptedText << std::endl;

    return 0;
}
