#ifndef ONE_UP_H_
#define ONE_UP_H_

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

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
  std::set<std::pair<std::string, std::vector<std::string>>> getCheatWords();
  void cheatWords(
      size_t pos, bool valid, std::string soFar, std::vector<std::string> build,
      std::set<std::pair<std::string, std::vector<std::string>>> &results);

 private:
  std::unordered_map<std::string, std::set<std::string>> memo;
  std::unordered_map<std::string, std::set<std::string>> wordMap;
  std::vector<std::string> currentWords;
  std::vector<char> tiles;
};

#endif
