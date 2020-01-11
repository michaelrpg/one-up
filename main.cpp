#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "one_up.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./program dictionary.txt" << std::endl;
    return 1;
  }

  OneUp oneUp;

  if (!oneUp.loadTiles("tileCount.txt")) {
    std::cout << "Couldn't load tileCount.txt" << std::endl;
    return 1;
  }

  if (!oneUp.loadDictionary(argv[1])) {
    std::cout << "Couldn't load dictionary" << std::endl;
    return 1;
  }

  std::cout << oneUp.dictionarySize() << " combinations in dictionary"
            << std::endl;

  std::string userInput;
  std::string tempInput;

  while (true) {
    std::cout << std::endl << "Letters in pile: ";
    for (const char &l : oneUp.getTiles()) {
      std::cout << l << " ";
    }
    std::cout << std::endl;

    std::cout << "Current words: ";
    for (const std::string &w : oneUp.getWords()) {
      std::cout << w << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "Enter command (q=quit f=flip 'a X X X'=add 'r X X X'=remove "
              << "c=cheat): ";

    std::getline(std::cin, tempInput);
    std::stringstream ssInput(tempInput);
    ssInput >> userInput;

    if (userInput == "q") {
      break;
    }

    if (userInput[0] == 'f') {
      char tile = oneUp.flipTile();

      if (tile == '\0') {
        std::cout << "OUT OF TILES" << std::endl;
      } else {
        std::cout << "Flipped tile " << tile << " from pile" << std::endl;
        std::cout << oneUp.tilesRemaining() << " tiles left";
      }
    } else if (userInput[0] == 'a') {
      std::string word;

      while (ssInput >> word) {
        oneUp.addWord(word);
      }
    } else if (userInput[0] == 'r') {
      std::string word;

      while (ssInput >> word) {
        oneUp.removeWord(word);
      }
    } else if (userInput[0] == 'c') {
      std::set<std::pair<std::string, std::vector<std::string>>> cheatWords =
          oneUp.getCheatWords();

      for (auto cheatItem : cheatWords) {
        std::cout << cheatItem.first << ": ";

        std::string buildWord;
        for (const auto &w : cheatItem.second) {
          std::cout << w << " ";
          buildWord += w;
        }

        if (buildWord.find('?') != std::string::npos) {
          for (char letter : cheatItem.first) {
            if (count(cheatItem.first.begin(), cheatItem.first.end(), letter) >
                count(buildWord.begin(), buildWord.end(), letter)) {
              cheatItem.first[cheatItem.first.find(letter)] = '?';
              std::cout << "(" << cheatItem.first << ")";

              break;
            }
          }
        }

        std::cout << std::endl;
      }
    }

    std::cout << std::endl;
  }

  return 0;
}
