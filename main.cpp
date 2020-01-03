#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

map<string, set<string>> wordMap;
vector<string> pile;
vector<string> currentWords;

void cheatPile(int pos, string soFar, vector<string> &results) {
  // cout << pos << " " << soFar << endl;
  if (pos >= pile.size()) {
    return;
  }

  cheatPile(pos + 1, soFar, results);
  soFar += pile[pos];
  sort(soFar.begin(), soFar.end());
  if (wordMap[soFar].size() > 0) {
    results.insert(results.end(), wordMap[soFar].begin(), wordMap[soFar].end());
  }
  cheatPile(pos + 1, soFar, results);
}

vector<string> cheat() {
  string soFar = "";
  vector<string> results;
  
  cheatPile(0, soFar, results);

  return results;
}


int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Usage: ./program dictionary.txt" << endl;
    return 1;
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

  while (true) {
    cout << "Enter command (q=quit p=print 'a word'=add 'r word'=remove c=cheat): ";
    cin >> userInput;

    if (userInput == "q") {
      break;
    }
    else if (userInput == "p") {
      cout << "Letters in pile: ";

      for (auto l : pile) {
        cout << l << " ";
      }
      cout << endl;

      cout << "Current words: ";

      for (auto w : currentWords) {
        cout << w << " ";
      }
      cout << endl;
    }
    else if (userInput[0] == 'a' ) {
      string word;
      cin >> word;

      if (word.length() == 1) {
        pile.push_back(word);
      }
      else {
        currentWords.push_back(word);  
      }
    }
    else if (userInput[0] == 'r' ) {
      string word;
      cin >> word;

      if (word.length() == 1) {
        auto p = find(pile.begin(), pile.end(), word);
        pile.erase(p);
      }
      else {
        auto p = find(currentWords.begin(), currentWords.end(), word);
        currentWords.erase(p);
      }
    }
    else if (userInput[0] == 'c') {
      vector<string> cheatWords = cheat();

      for (auto w : cheatWords) {
        cout << w << " ";
      }

      cout << endl;
    }

    cout << endl;
  }

  return 0;
}
