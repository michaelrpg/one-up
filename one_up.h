#ifndef ONE_UP_H_
#define ONE_UP_H_

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

struct CheatResult {
  std::string word;
  std::vector<std::string> buildList;
  std::string wordToAdd;
  bool operator<(const CheatResult &rhs) const {
    if (this->word != rhs.word) {
      return this->word < rhs.word;
    }

    if (this->buildList != rhs.buildList) {
      return this->buildList < rhs.buildList;
    }

    return this->wordToAdd < rhs.wordToAdd;
  }
};

class OneUp {
 public:
  OneUp();
  bool loadTiles(const std::string &tileFilename);
  bool loadDictionary(const std::string &dictionaryFileName);
  int dictionarySize();
  std::vector<char> getTiles();
  std::vector<std::string> getWords();
  char flipTile();
  int tilesRemaining();
  void addWord(const std::string &word);
  void removeWord(const std::string &word);
  std::set<CheatResult> getCheatWords();

 private:
  void cheatWords(size_t pos, bool valid, std::string soFar,
                  std::vector<std::string> build,
                  std::set<CheatResult> &results);
  void pruneDictionary(std::string soFar, const std::string &oldSoFar);
  void buildResults(std::string &soFar, const std::string &currentWord,
                    const std::string &buildWord,
                    std::vector<std::string> &build,
                    std::set<CheatResult> &results, bool valid);
  std::string wordToAdd(std::string word, std::vector<std::string> buildPath);
  std::unordered_map<std::string, std::set<std::string>> memo;
  std::unordered_map<std::string, std::set<std::string>> wordMap;
  std::vector<std::string> currentWords;
  std::vector<char> tiles;
};

#endif
