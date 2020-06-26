# About One Up!
One Up! is a fun tile-based word game in which you form words from tiles, including tiles owned by other players.

Official rules: <http://www.oneupmanship.com/movies/images/Master%20One%20Up!%20Instructions.pdf>  
Official tile count information: <http://www.oneupmanship.com/faq.html>

## Compile
    g++ -Wall -O2 main.cpp one_up.cpp

## Usage
    ./a.out dictionary_of_choice.txt

## Command explanations:
* (q) to quit
* (f) to simulate flipping over a tile. Useful way to play a practice game
* (c) to cheat. Show all possible combinations
* (#number) to use the previously shown combo
* (a word/letter word/letter ...) to manually add the list of tiles/words
* (r word/letter word/letter ...) to manually remove the list of tiles/words

## Dictionaries
* dict_70k.txt is from http://www-personal.umich.edu/~jlawler/wordlist.html
* dict_100k.txt is from https://norvig.com/ngrams/
* dict_370k.txt is from https://github.com/dwyl/english-words
