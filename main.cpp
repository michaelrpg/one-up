#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

map<string, set<string>> wordMap;
vector<string> currentWords;

void cheatWords(int pos, bool valid, string soFar, vector<string> build, pair<vector<string>, vector<vector<string>>> &results) {
  // cout << pos << " " << soFar << endl;
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
      results.first.push_back(w);
      results.second.push_back(build);
    }
  }

  cheatWords(pos + 1, valid, soFar, build, results);
}

pair<vector<string>, vector<vector<string>>> cheat() {
  string soFar = "";
  vector<string> build;
  pair<vector<string>, vector<vector<string>>> results;
  
  cheatWords(0, false, soFar, build, results);

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
    sort(currentWords.begin(), currentWords.end());

    cout << "Enter command (q=quit p=print 'a X'=add 'r X'=remove c=cheat): ";
    cin >> userInput;

    if (userInput == "q") {
      break;
    }
    else if (userInput == "p") {
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
      cout << endl;
    }
    else if (userInput[0] == 'a' ) {
      string word;
      cin >> word;

      currentWords.push_back(word);  
    }
    else if (userInput[0] == 'r' ) {
      string word;
      cin >> word;

      auto p = find(currentWords.begin(), currentWords.end(), word);
      currentWords.erase(p);
    }
    else if (userInput[0] == 'c') {
      pair<vector<string>, vector<vector<string>>> cheatWords = cheat();

      for (int i=0; i < cheatWords.first.size(); i++) {
        cout << cheatWords.first[i] << ": ";
        for (auto w : cheatWords.second[i]) {
          cout << w << " ";      
        }
        cout << endl;
      }

      cout << endl;
    }

    cout << endl;
  }

  return 0;
}
