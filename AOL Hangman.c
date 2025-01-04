#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define SCOREBOARD_FILE "scoreboard.txt"

// Daftar kata untuk permainan
const char *wordList[] = {
    "programming", "skibidi", "computer", "developer", "binus","string","pointer","array","class",
    "sigma", "keyboard", "language", "antediluvian", "algorithm","mewing","tv","sync","fly","jazz","junk",
    "zap","fox", "apple", "chair", "bread", "table", "water","house", "world", "plant", "music", "beach", 
    "pencil", "orange", "flower", "school", "window","family", "friend","jungle", "winter", "summer", 
	"garden", "butter", "sugar", "coffee", "mirror","animal", "mother","father", "brother", "sister",
    "kitten", "puppy", "yellow", "purple", "camera","dollar", "circle","rocket", "guitar", "helmet",
    "monkey", "rabbit", "donkey", "banana", "cookie","bridge", "castle","desert", "forest", "honey",
    "airport", "islands", "parrots", "sandwich", "blanket","ceiling", "journey", "luggage", "mountain", "picture", 
    "pyramid", "science", "stadium", "sunrise", "tractor","volcano","weather", "ancient", "balloon", "captain", 
    "diamond", "feather", "holiday", "laughter", "measure","notebook","penguin", "esoteric", "rainbow", "squirrel", 
    "texture", "treasure", "vacuum", "whistle", "wriggle","airplane","bicycle", "coconut", "crystal", "elephant", 
    "fortune", "gorilla", "obfuscate", "justice", "mermaid","monster","palace", "pirates", "pulchritudinous", "village",
    "alligator", "blueprint", "chemistry", "dandelion", "engineer","futuristic", "happiness", "immediate", "kangaroo", "labyrinth", 
    "lightning", "margarine", "nightmare", "obstacle", "parachute","pharmacy", "quarantine", "rectangle", "shipwreck", "snowflake", 
    "spectacle", "triangle", "umbrella", "universe", "waterfall","whirlpool", "adventure", "avalanche", "blueberry", "chocolate", 
    "fireworks", "greenhouse", "harvested", "jellyfish", "landscape","narrative", "pineapple", "recycling", "telescope", "vibration", 
    "woodpecker", "archeology", "compromise", "convenient", "discipline","quixotic","syzygy","cacophony","chiaroscuro",
    "floccinaucinihilipilification","ephemeral","sesquipedalian","xenophobia","ziggurat","cryptozoology"
};
const int wordCount = sizeof(wordList) / sizeof(wordList[0]);

// Struktur untuk menyimpan data skor
typedef struct {
    char name[50];
    int score;
} PlayerScore;

// Membandingkan skor untuk pengurutan
int compareScores(const void *a, const void *b) {
    PlayerScore *playerA = (PlayerScore *)a;
    PlayerScore *playerB = (PlayerScore *)b;
    return playerB->score - playerA->score; // Urutkan dari yang terbesar ke terkecil
}

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

void rule(){
puts("How to play :");
puts("+ Jadi game merupakan tebak kata degan memasukan huruf 1 per 1 ");
puts("+ Setiap huruf yang ditebak benar maka akan mendapat 5 poin namun jika salah menebak maka akan berkurang 2 poin ");
puts("+ Setiap tebakan salah juga akan menambah gambar dari hangedman. Jika gambar hangedman sudah lengkap tubuhnya maka game dinyatakan game over");
puts("+ Jika menang maka anda dapat memilih untuk melanjutkan permain atau tidak. Tidak ada batasan dalam bermain dan skor akan berlanjut");
puts("+ Anda juga dapat mencantumkan skor anda yang nanti bisa diliat pada bagian ScoreBoard");
puts("+ Selamat menikmati permainan");
}
// Memilih kata secara acak
const char* getRandomWord() {
    return wordList[rand() % wordCount];
}

// Fungsi untuk mengurutkan array huruf
void sortGuessedLetters(char *letters, int count) {
    qsort(letters, count, sizeof(char), (int (*)(const void *, const void *)) strcmp);
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
        system("cls");
        rule();
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
            getchar(); getchar();
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
            getchar(); getchar();
            continue;
        }

        // Tambahkan huruf ke daftar huruf yang sudah ditebak
        if (guessedCount < 26) { // Pastikan tidak melebihi kapasitas array
            guessedLetters[guessedCount++] = guess;
        }

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
            *score = (*score - 2 > 0) ? *score - 2 : 0; // Penalti untuk tebakan salah, skor tidak negatif
            printf("Wrong guess!\n");
        } else {
            *score += 5; // Bonus untuk tebakan benar
            printf("Correct guess!\n");
        }

        // Cek apakah pemain menang
        if (strcmp(word, guessed) == 0) {
            printf("\nCongratulations! You guessed the word: %s\n", word);
            return 1;
        }
    }

    // Catat waktu selesai
    time_t endTime = time(NULL);
    double timeTaken = difftime(endTime, startTime);

    // Hitung bonus waktu (maksimal 45 detik)
    int timeBonus = (timeTaken <= 45) ? 45 - (int)timeTaken : 0;
    *score += timeBonus;

    // Tampilkan hasil akhir
    displayHangman(mistakes);
    printf("\nGame over! The word was: %s\n", word);
    printf("Final Score: %d\n", *score);

    return 0;
}

// Menyimpan skor ke file
void saveScore(int score) {
    char name[50];
    printf("Enter your name(name can only contain 1 word): ");
    getchar(); // Membersihkan buffer input
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Menghapus karakter newline

    if (strlen(name) == 0) {
        printf("Name cannot be empty.\n");
        return;
    }

    FILE *file = fopen(SCOREBOARD_FILE, "a");
    if (file == NULL) {
        printf("Error opening scoreboard file.\n");
        return;
    }

    fprintf(file, "\"%s\" %d\n", name, score); // Tambahkan tanda kutip
    fclose(file);
    printf("Score saved successfully!\n");
}

// Menampilkan scoreboard
void displayScoreboard() {
    system("cls");
    FILE *file = fopen(SCOREBOARD_FILE, "r");
    if (file == NULL) {
        printf("No scoreboard data available.\n");
        while (getchar() != '\n');
        getchar();
        return;
    }

    PlayerScore scores[100];
    int count = 0;
    char name[50];
    int score;
    // Membaca data dari file dengan validasi tambahan
    char line[100];
    int i;
    while (fgets(line, sizeof(line), file) != NULL && count < 100) {
    if (sscanf(line, "\"%49[^\"]\" %d", name, &score) == 2) {
        strncpy(scores[count].name, name, sizeof(scores[count].name) - 1);
        scores[count].name[sizeof(scores[count].name) - 1] = '\0';
        scores[count].score = score;
        count++;
    	}
	}
    fclose(file);

    if (count == 0) {
        printf("No scoreboard data available.\n");
        printf("\nPress Enter to return to the main menu...");
        while (getchar() != '\n');
        getchar();
        return;
    }

    // Urutkan skor dari terbesar ke terkecil
    qsort(scores, count, sizeof(PlayerScore), compareScores);

    printf("\n--- Scoreboard ---\n");
    printf("%-20s %-10s\n", "Name", "Score");
    printf("-----------------------------\n");
    for (i = 0; i < count; i++) {
        printf("%-20s %-10d\n", scores[i].name, scores[i].score);
    }

    printf("\nPress Enter to return to the main menu...");
    while (getchar() != '\n');
    getchar();
    system("cls");
}

// Fungsi utama
int main() {
    srand(time(NULL)); // Seed untuk random
    int score = 0;

    while (1) {
        printf("\n--- Hangman Game ---\n");
        printf("1. Play Game\n");
        printf("2. View Scoreboard\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Bersihkan buffer input
            continue;
        }

        switch (choice) {
            case 1: {
                char continuePlaying = 'y';
                while (tolower(continuePlaying) == 'y') {
                    playGame(&score);
                    printf("Do you want to continue playing? (y/n): ");
                    scanf(" %c", &continuePlaying);
                }
                printf("Do you want to save your score? (y/n): ");
                char save;
                scanf(" %c", &save);
                if (tolower(save) == 'y') {
                    saveScore(score);
                }
                score = 0; // Reset score setelah selesai sesi permainan
                getchar();
                system("cls");
                break;
            }

            case 2:
                displayScoreboard();
                break;

            case 3:
                printf("Thank you for playing!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
