#include <algorithm>
#include <iostream>
#include <map>
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

  std::map<std::string, std::pair<std::string, std::vector<std::string>>>
      actionMap;

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

    std::cout << "Enter command (q=quit f=flip c=cheat #=combo 'a X X X'=add "
              << "'r X X X'=remove: ";

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
      actionMap.clear();
      std::set<CheatResult> cheatWords = oneUp.getCheatWords();

      for (auto cheatItem : cheatWords) {
        std::cout << actionMap.size() + 1 << ". " << cheatItem.word << " ";

        std::cout << "(" << cheatItem.wordToAdd << ") ";

        std::cout << "(";
        for (size_t pos = 0; pos < cheatItem.buildList.size(); pos++) {
          std::cout << cheatItem.buildList[pos];
          if (pos != cheatItem.buildList.size() - 1) {
            std::cout << " ";
          }
        }
        std::cout << ")" << std::endl;

        actionMap[std::to_string(actionMap.size() + 1)] =
            make_pair(cheatItem.wordToAdd, cheatItem.buildList);
      }
    } else if (actionMap.count(userInput) > 0) {
      oneUp.addWord(actionMap[userInput].first);

      for (const std::string &w : actionMap[userInput].second) {
        oneUp.removeWord(w);
      }

      actionMap.clear();
    }

    std::cout << std::endl;
  }

  return 0;
}
