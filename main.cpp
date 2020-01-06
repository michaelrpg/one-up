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
  if (pos >= currentWords.size() || soFar.size() > 35) {
    return;
  }

  cheatWords(pos + 1, valid, soFar, build, results);

  if (currentWords[pos].size() == 1) {
    valid = true;
  }

  int uppityPos = currentWords[pos].find('?');
  if (uppityPos == string::npos) {

    soFar += currentWords[pos];
    build.push_back(currentWords[pos]);
    sort(soFar.begin(), soFar.end());
    if (valid) {
      for (auto w : wordMap[soFar]) {
        results.insert(make_pair(w, build));
      }
    }

    cheatWords(pos + 1, valid, soFar, build, results);
  } else {
    string soFarOriginal = soFar;
    vector<string> buildOriginal = build;

    for (char letter = 'a'; letter <= 'z'; letter++) {
      soFar = soFarOriginal;
      build = buildOriginal;

      string newWord = currentWords[pos];
      newWord[uppityPos] = letter;

      soFar += newWord;
      build.push_back(currentWords[pos]);
      sort(soFar.begin(), soFar.end());
      if (valid) {
        for (auto w : wordMap[soFar]) {
          results.insert(make_pair(w, build));
        }
      }

      cheatWords(pos + 1, valid, soFar, build, results);

    }

  }
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
  
  if (!tileFile.good()) {
    cout << "Couldn't open tileCount.txt" << endl;
    return 1;
  }

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

  if (!wordListFile.good()) {
    cout << "Couldn't open dictionary" << endl;
    return 1;
  }

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
      if (tiles.size() == 0) {
      	cout << "OUT OF TILES" << endl;
      } else {
        int pos = rand() % tiles.size();
        cout << "Flipped " << tiles[pos] << " from pile" << endl;;

        currentWords.push_back(tiles[pos]);

        tiles.erase(tiles.begin() + pos);
      
        cout << tiles.size() << " tiles left";
      }
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
	if (p != currentWords.end()) {
          currentWords.erase(p);
	}
      }
    }
    else if (userInput[0] == 'c') {
      set<pair<string, vector<string>>> cheatWords = cheat();
      
      for (auto cheatItem : cheatWords) {
        cout << cheatItem.first << ": ";

        string buildWord;
        for (auto w : cheatItem.second) {
          cout << w << " ";      
          buildWord += w;
        }
        
        if (buildWord.find('?') != string::npos) {
          for (char letter : cheatItem.first) {
            if (count(cheatItem.first.begin(), cheatItem.first.end(), letter) > 
              count(buildWord.begin(), buildWord.end(), letter)) {
              cheatItem.first[cheatItem.first.find(letter)] = '?';
              cout << "(" << cheatItem.first << ")";

              break;
            }
          }
        }
        
        cout << endl;
      }

    }

    cout << endl;
  }

  return 0;
}
