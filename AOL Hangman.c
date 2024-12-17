#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Daftar kata untuk permainan
const char *wordList[] = {
    "programming", "skibidi", "computer", "developer", "binus", 
    "sigma", "keyboard", "language", "science", "algorithm", "mewing"
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
    return wordList[rand() % wordCount];
}

// Fungsi untuk mengurutkan array huruf
void sortGuessedLetters(char *letters, int count) {
	int i,j;
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (letters[i] > letters[j]) {
                char temp = letters[i];
                letters[i] = letters[j];
                letters[j] = temp;
            }
        }
    }
}

// Fungsi utama untuk satu ronde permainan
int playGame(int *score) {
    const char *word = getRandomWord();
    int wordLength = strlen(word);
    char guessed[wordLength + 1];
    int mistakes = 0, maxMistakes = 8;
    char guessedLetters[26] = {0}; // Menyimpan huruf yang sudah ditebak
    int guessedCount = 0;

    // Inisialisasi guessed dengan underscore
    int i;
    for (i = 0; i < wordLength; i++) {
        guessed[i] = '_';
    }
    guessed[wordLength] = '\0';

    // Catat waktu mulai
    time_t startTime = time(NULL);

    // Game loop
    while (mistakes < maxMistakes) {
        printf("\nWord: %s\n", guessed);
        displayHangman(mistakes);

        // Tampilkan huruf yang sudah ditebak
        sortGuessedLetters(guessedLetters, guessedCount);
        printf("Guessed letters: ");
        for (i = 0; i < guessedCount; i++) {
            printf("%c ", guessedLetters[i]);
        }
        printf("\n");

        // Input huruf dari pemain
        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        // Validasi input
        if (!isalpha(guess)) {
            printf("Invalid input. Please enter a letter.\n");
            continue;
        }

        // Cek apakah huruf sudah ditebak sebelumnya
        int alreadyGuessed = 0;
        for (i = 0; i < guessedCount; i++) {
            if (guessedLetters[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }
        if (alreadyGuessed) {
            printf("You already guessed that letter.\n");
            continue;
        }

        // Tambahkan huruf ke daftar huruf yang sudah ditebak
        guessedLetters[guessedCount++] = guess;

        // Cek apakah huruf ada di kata
        int correctGuess = 0;
        for (i = 0; i < wordLength; i++) {
            if (word[i] == guess) {
                guessed[i] = guess;
                correctGuess = 1;
            }
        }

        if (!correctGuess) {
            mistakes++;
            if (*score > 0) {
                *score -= 2; // Penalti untuk tebakan salah
            }
            printf("Wrong guess! Score: %d\n", *score);
        } else {
            *score += 5; // Bonus untuk tebakan benar
            printf("Correct guess! Score: %d\n", *score);
        }

        // Cek apakah pemain menang
        if (strcmp(word, guessed) == 0) {
            printf("\nCongratulations! You guessed the word: %s\n", word);
            break;
        }
    }

    // Catat waktu selesai
    time_t endTime = time(NULL);
    double timeTaken = difftime(endTime, startTime);

    // Hitung bonus waktu (maksimal 15 detik)
    int timeBonus = (timeTaken <= 15) ? 15 - (int)timeTaken : 0;
    *score += timeBonus;

    // Tampilkan hasil akhir
    if (mistakes == maxMistakes) {
        displayHangman(mistakes);
        printf("\nGame over! The word was: %s\n", word);
    }
    printf("Time Taken: %.0f seconds\n", timeTaken);
    printf("Time Bonus: %d\n", timeBonus);
    printf("Final Score: %d\n", *score);

    // Return apakah pemain menang
    return strcmp(word, guessed) == 0;
}

// Main function
int main() {
    srand(time(NULL)); // Seed untuk random
    int score = 0;
    char playAgain;

    do {
        int result = playGame(&score);

        if (result) {
            printf("\nDo you want to play again? (y/n): ");
            scanf(" %c", &playAgain);
        } else {
            printf("\nGame over! Final Score: %d\n", score);
            break;
        }

    } while (tolower(playAgain) == 'y');

    printf("Thank you for playing! Your total score: %d\n", score);
    return 0;
}

