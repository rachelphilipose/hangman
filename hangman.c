
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
//#include "words.h"
#include "hangman-extras.c"
#include <string.h>

const int max_words = 1000;

// This program plays the game hangman :)
void play_game(void);

// is_lowercase(c) returns true if c is lowercase and false otherwise
bool is_lowercase(char c) {
  return (c >= 'a') && (c <= 'z');
}

// to_uppercase(c) converts lower case letters to
//   uppercase letters, everything else is unchanged
char to_uppercase(char c) {
  if (is_lowercase(c)) {
    return c - 'a' + 'A';;
  } else {
    return c;
  }
}


//print_word(word) prints all the characters in a word, followed by a newline
// requires: word is a valid string
// effects: produces output
// time: O(n)
void print_word(const char *word) {
  assert(word);
    int len = strlen(word);

    for (int i = 0; i < len ; ++i) {
      printf("%c", word[i]);
    }
    printf("\n");
}

// game_setup(stars, strikes) prints the basic stock game board based on strikes
// requires: stars is a valid string
//           valid number of strikes
// effects: prints output
// time: O(1)
void game_setup( char *stars, int strikes) {
  assert(stars);
  assert(strikes >= 0);
  assert(strikes <= max_strikes);

  print_hangman(strikes);
  printf("%s",letter_prompt);
  print_word(stars);
}

// make_printable_stars (word, result) formats string result with 
// *'s wherever there are letters, leaving spaces untouched
// requires: word and stars are valid strings
// effects: mutates result
// time: O(n)
void make_printable_stars (const char *word, char *result) {
  assert(word);
  assert(result);

  int len = strlen(word);
    for (int i = 0; i < len ; ++i) {
        if (word[i] == ' ') {
            result[i] = ' ';
        }
        else {
            result[i] = '*';
        }
    }
}

// letter_in_word(word, letter) returns true if the letter is in the array word, false otherwise
// requires: word is a valid string
// time: O(n)
bool letter_in_word(const char *word, char letter ) {
  assert(word);
  //printf("%s", word);
  //printf("%c", letter);

    int len = strlen(word);
    for (int i = 0; i < len; ++i) {
        if (word[i] == letter) {
            return true;
        }
    }
    return false;
}

// finished (stars, word) returns true if stars has all letters/spaces
// false if there are still stars 
// requires: stars is a valid string
// time: O(n)
bool finished(const char *stars) {
  assert(stars);

  int len = strlen(stars);
  
  for (int i = 0; i < len; ++i) {
      if (stars[i] == '*') {
          return false;
      }
  }  

  return true;

}

// play_again_prompt() prints the prompt asking users to play again, 
// and processes their response
// effects: takes input
//          prints output
// time: O(n) where n is the amount of input
void play_again_prompt(void) {
  printf("%s", play_again);
  char response = 0;
  //int retval = 0;
  //retval = scanf("%c", &response);
  scanf(" %c", &response);
  response = to_uppercase(response);
  //trace_char(response);

  if ((response != 'Y' && response != 'N')){
    printf("%s", invalid_play_again_response);
    play_again_prompt();
  }
  else if (response == 'Y') {
    play_game();
  }
  else { 
    return;
  }
}


// play_game() plays the game hangman!
// effects: takes input
//        produces output
// time: O(n) where n is the amount of input
void play_game(void) {
    // get number 
  
  bool valid_num = false;
  int game_num = 0;

  while (!valid_num) {
    printf(enter_game_number, max_words);
    scanf(" %d", &game_num);

    if (game_num >= 1 && game_num <= max_words) {
        valid_num = true;
    }

    else {
        printf("%s", invalid_game_number);

    }
  }

  const char *word = "HELLO";
  char stars[50] = {0};
  strcpy( stars, word);
  //printf("%s\n", stars);
    //trace_int(strlen(stars));
  //trace_int(strlen(word));


  make_printable_stars(word, stars);




  const int len = strlen(word);

  char guess = 0;
  int count_guesses = 0;
  char guess_list[56] = {0}; //56 is max length of string + 6 strikes
  int strike = 0;
  game_setup(stars, strike);

  while (scanf(" %c", &guess) == 1) {
    
    guess = to_uppercase(guess);

    if (guess < 65 || guess > 90) {
      printf(not_a_letter, guess);
      break;
    }

    else if (letter_in_word(guess_list, guess)) { //letter is already guessed
      printf(already_guessed_letter, guess);
    }
    // now we know that guess is a valid, uppercase letter
    // we can check if it's in the word
    else if (letter_in_word(word, guess)) {
      // replacing the stars with the letter
      for (int i = 0; i < len ; ++i){
        if (word[i] == guess) {
          stars[i] = guess;
        }
      }
      //print_word(stars);

      if (finished(stars)) {
        printf(congratulations, stars);
        play_again_prompt();
        break;
      }
    }

    else { // letter is unguessed but NOT in word
      printf(not_in_word, guess);
      strike += 1;

      if (strike < max_strikes) {
        printf(not_last_guess, (max_strikes - strike));
      }

      else {
        print_hangman(6);
        printf(game_over, word);
        play_again_prompt();
        break;
      }

    }
    guess_list[count_guesses] = guess;
    //trace_int(letter_in_word(guess_list, guess));
    //trace_int(letter_in_word(guess_list, 'a'));

    ++count_guesses;

    game_setup(stars, strike);

  }
}

int main(void) {
  play_game();

}