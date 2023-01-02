# wordle
Wordle game written in C++. Process: The game takes in a word from the wordlist file and asks the player to enter a guess
If any of the letters in the word you entered also appear in the secret word, one of two possibilities occur:
1) If any of the letters are identical and in the exact same place for both words, the character 'G' (for 'Green', 'correct') will appear below the words
2) If any of the letters appear in both words, but are not in the exact same place, the character 'Y' (for 'Yellow', 'wrong spot') will appear below the words
After 5 attempts, if all letters of the words are identical and in the same spots (marked with a 'G'), the game is won. Otherwise, the game is lost.
The user is prompted if they would like to play again or exit the game; depending on the response, the wordle game will reset with a new word or exit
