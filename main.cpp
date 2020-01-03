#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

map<string, set<string>> wordMap;
vector<string> currentWords;

void cheatWords(size_t pos, bool valid, string soFar, vector<string> build, set<pair<string, vector<string>>> &results) {
  if (pos >= currentWords.size()) {
    return;
  }

  cheatWords(pos + 1, valid, soFar, build, results);

  if (currentWords[pos].size() == 1) {
    valid = true;
  }

  soFar += currentWords[pos];
  build.push_back(currentWords[pos]);
  sort(soFar.begin(), soFar.end());
  if (valid && wordMap[soFar].size() > 0) {
    for (auto w : wordMap[soFar]) {
      results.insert(make_pair(w, build));
    }
  }

  cheatWords(pos + 1, valid, soFar, build, results);
}

set<pair<string, vector<string>>> cheat() {
  string soFar = "";
  vector<string> build;
  set<pair<string, vector<string>>> results;
  
  cheatWords(0, false, soFar, build, results);

  return results;
}


int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Usage: ./program dictionary.txt" << endl;
    return 1;
  }

  srand(time(nullptr)); // use current time as seed for random generator

  vector<string> tiles;
  ifstream tileFile("tileCount.txt");
  while (!tileFile.eof()) {
    string t;
    tileFile >> t;

    if (t.size() == 0) {
      break;
    }

    tiles.push_back(t);
  }
  
  ifstream wordListFile;
  wordListFile.open(argv[1]);

  while (!wordListFile.eof()) {
    string s;
    wordListFile >> s;
    if (s.length() >= 3) {
      string originalWord = s;
      sort(s.begin(), s.end());

      wordMap[s].insert(originalWord);
    }
  } 
  
  // not correct. just number of valid "combos"
  cout << wordMap.size() << " valid words in dictionary" << endl;
  	
  string userInput;
  string tempInput;

  while (true) {
    sort(currentWords.begin(), currentWords.end());
    
    cout << "Letters in pile: ";

    for (auto l : currentWords) {
      if (l.size() == 1) {
        cout << l << " ";
      }
    }
    cout << endl;

    cout << "Current words: ";

    for (auto w : currentWords) {
      if (w.size() > 1) {
        cout << w << " ";
      }
    }
    cout << endl << endl;

    cout << "Enter command (q=quit f=flip 'a X X X'=add 'r X X X'=remove c=cheat): ";
    getline(cin, tempInput);
    stringstream ssInput(tempInput);
    ssInput >> userInput;


    if (userInput == "q") {
      break;
    }
    else if (userInput[0] == 'f') {
      int pos = rand() % tiles.size();
      cout << "Flipped " << tiles[pos] << " from pile" << endl;;

      currentWords.push_back(tiles[pos]);

      tiles.erase(tiles.begin() + pos);
      
      cout << tiles.size() << " tiles left";
    }
    else if (userInput[0] == 'a' ) {
      string word;
      
      while (ssInput >> word) {
        currentWords.push_back(word);  
      }
    }
    else if (userInput[0] == 'r' ) {
      string word;

      while (ssInput >> word) {
        auto p = find(currentWords.begin(), currentWords.end(), word);
        currentWords.erase(p);
      }
    }
    else if (userInput[0] == 'c') {
      set<pair<string, vector<string>>> cheatWords = cheat();
      
      for (auto setItem : cheatWords) {
        cout << setItem.first << ": ";
        for (auto w : setItem.second) {
          cout << w << " ";      
        }
        cout << endl;
      }

    }

    cout << endl;
  }

  return 0;
}
