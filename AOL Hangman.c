#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Daftar kata untuk permainan
const char *wordList[] = {
    "programming", "skibidi", "computer", "developer", "binus", 
    "sigma", "keyboard", "language", "science", "algorithm","mewing"
};
const int wordCount = sizeof(wordList) / sizeof(wordList[0]);

// Menampilkan Hangman berdasarkan jumlah kesalahan
void displayHangman(int mistakes) {
    const char *hangmanStages[] = {
    	"  \n      \n      \n      \n     ===",
        "  \n      |\n      |\n      |\n     ===",
        "  +---+\n      |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n  |   |\n      |\n     ===",
        "  +---+\n  O   |\n /|   |\n      |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n      |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n /    |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n / \\  |\n     ==="
    };
    printf("%s\n", hangmanStages[mistakes]);
}

// Memilih kata secara acak
const char* getRandomWord() {
    srand(time(NULL)); // Seed untuk random
    return wordList[rand() % wordCount];
}

// Main function
int main() {
    const char *word = getRandomWord();
    int wordLength = strlen(word);
    char guessed[wordLength + 1];
    int mistakes = 0, maxMistakes = 8;
    char guessedLetters[26] = {0}; // Menyimpan huruf yang sudah ditebak
    int guessedCount = 0;

    return 0;
}

