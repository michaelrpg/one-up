#include "one_up.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

OneUp::OneUp() {
  srand(time(nullptr));  // use current time as seed for random generator
};

bool OneUp::loadTiles(const std::string &tileFilename) {
  std::ifstream tileFile(tileFilename);

  if (!tileFile.good()) {
    return false;
  }

  while (!tileFile.eof()) {
    std::string t;
    tileFile >> t;

    if (t.empty()) {
      break;
    }

    tiles.push_back(t);
  }

  return true;
}

bool OneUp::loadDictionary(const std::string &dictionaryFileName) {
  std::ifstream wordListFile(dictionaryFileName);

  if (!wordListFile.good()) {
    return false;
  }

  while (!wordListFile.eof()) {
    std::string s;
    wordListFile >> s;
    if (s.length() >= 3) {
      std::string originalWord = s;
      std::sort(s.begin(), s.end());

      memo[""].insert(s);
      wordMap[s].insert(originalWord);
    }
  }

  return true;
}

int OneUp::dictionarySize() { return wordMap.size(); }

std::vector<char> OneUp::getTiles() {
  std::vector<char> tiles;

  for (const std::string &w : currentWords) {
    if (w.size() == 1) {
      tiles.push_back(w[0]);
    }
  }

  return tiles;
}

std::vector<std::string> OneUp::getWords() {
  std::vector<std::string> words;

  for (const std::string &w : currentWords) {
    if (w.size() > 1) {
      words.push_back(w);
    }
  }

  return words;
}

char OneUp::flipTile() {
  if (tiles.empty()) {
    return '\0';
  }

  int pos = rand() % tiles.size();
  char tile = tiles[pos][0];

  currentWords.push_back(tiles[pos]);
  tiles.erase(tiles.begin() + pos);

  sort(currentWords.begin(), currentWords.end());

  return tile;
}

int OneUp::tilesRemaining() { return tiles.size(); }

void OneUp::addWord(const std::string &word) {
  currentWords.push_back(word);

  sort(currentWords.begin(), currentWords.end());
}

void OneUp::removeWord(const std::string &word) {
  auto p = find(currentWords.begin(), currentWords.end(), word);

  if (p != currentWords.end()) {
    currentWords.erase(p);
  }
}

std::set<std::pair<std::string, std::vector<std::string>>>
OneUp::getCheatWords() {
  std::string soFar;
  std::vector<std::string> build;
  std::set<std::pair<std::string, std::vector<std::string>>> results;

  cheatWords(0, false, soFar, build, results);

  return results;
}

void OneUp::cheatWords(
    size_t pos, bool valid, std::string soFar, std::vector<std::string> build,
    std::set<std::pair<std::string, std::vector<std::string>>> &results) {
  if (pos >= currentWords.size()) {
    return;
  }

  cheatWords(pos + 1, valid, soFar, build, results);

  if (currentWords[pos].size() == 1) {
    valid = true;
  }

  std::string oldSoFar = soFar;

  size_t uppityPos = currentWords[pos].find('?');
  if (uppityPos == std::string::npos) {
    soFar += currentWords[pos];
    build.push_back(currentWords[pos]);
    std::sort(soFar.begin(), soFar.end());
    if (valid) {
      for (auto w : wordMap[soFar]) {
        results.insert(make_pair(w, build));
      }
    }

    if (memo.count(soFar) == 0) {
      for (const std::string &w : memo[oldSoFar]) {
        bool valid = true;
        size_t wPos = 0;
        size_t soFarPos = 0;

        while (true) {
          if (soFarPos >= soFar.size()) {
            break;
          }

          if (wPos >= w.size()) {
            valid = false;
            break;
          }

          if (soFar[soFarPos] == w[wPos]) {
            wPos++;
            soFarPos++;
          } else if (w[wPos] < soFar[soFarPos]) {
            wPos++;
          } else {
            valid = false;
            break;
          }
        }

        if (valid) {
          memo[soFar].insert(w);
        }
      }
    }

    if (!memo[soFar].empty()) {
      cheatWords(pos + 1, valid, soFar, build, results);
    }
  } else {
    std::string soFarOriginal = soFar;
    std::vector<std::string> buildOriginal = build;

    for (char letter = 'a'; letter <= 'z'; letter++) {
      soFar = soFarOriginal;
      build = buildOriginal;

      std::string newWord = currentWords[pos];
      newWord[uppityPos] = letter;

      soFar += newWord;
      build.push_back(currentWords[pos]);
      sort(soFar.begin(), soFar.end());
      if (valid) {
        for (auto w : wordMap[soFar]) {
          results.insert(make_pair(w, build));
        }
      }

      if (memo.count(soFar) == 0) {
        for (const std::string &w : memo[oldSoFar]) {
          bool valid = true;
          size_t wPos = 0;
          size_t soFarPos = 0;

          while (true) {
            if (soFarPos >= soFar.size()) {
              break;
            }

            if (wPos >= w.size()) {
              valid = false;
              break;
            }

            if (soFar[soFarPos] == w[wPos]) {
              wPos++;
              soFarPos++;
            } else if (w[wPos] < soFar[soFarPos]) {
              wPos++;
            } else {
              valid = false;
              break;
            }
          }

          if (valid) {
            memo[soFar].insert(w);
          }
        }
      }

      if (!memo[soFar].empty()) {
        cheatWords(pos + 1, valid, soFar, build, results);
      }
    }
  }
}
