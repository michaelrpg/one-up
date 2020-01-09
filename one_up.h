#ifndef ONE_UP_H_
#define ONE_UP_H_

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class OneUp {
 public:
  bool loadTiles(std::string tileFilename);
  bool loadDictionary(std::string dictionaryFileName);
};

extern std::unordered_map<std::string, std::set<std::string>> memo;
extern std::unordered_map<std::string, std::set<std::string>> wordMap;
extern std::vector<std::string> currentWords;

#endif
