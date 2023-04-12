#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// data structure like a map that keeps track of used floating letters 
// multi set?
// for all floating letters you start out with, every time you insert one then insert into used floating set multi set


// Add prototypes of helper functions here
// checks if word is valid given set of dictionary words

void getCombinations(const std::string& pattern, const string& floating, std::set<std::string>& results, int index, const std::set<std::string>& dict);
bool isValid(const std::string& word, const std::set<std::string>& dict);
int countChars(const std::string& str);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
	std::set<std::string> results;

	//std::string word(in.size(), ' ');

	getCombinations(in, floating, results, 0, dict);

	return results;

}
//map<char, int> floating;
// map of character to integer where integer is count of that character in the floating string

void getCombinations(const std::string& pattern, const string& floating, std::set<std::string>& results, int index, const std::set<std::string>& dict){

	// in base case, don't need to loop through floating to see if matches character
	// just check if floating map is empty
	// if floating map is empty, then word is valid
	string f = floating;
	string word = pattern;
	
	if (f.size() == 0 && index == static_cast<int>(word.size())){
		if (isValid(word, dict)){
			results.insert(pattern);
		}
		return;
	}
	unsigned int spaces = countChars(word);
	
	if (word[index] == '-'){
		if (f.size() == spaces){
			for (unsigned int i = 0; i < f.size(); i++){
				word[index] = f[i];
				f.erase(i,1);
				getCombinations(word, f, results, index + 1, dict);
				f = floating;
			}
		}
		else if (spaces > f.size()){
			for (char c = 'a'; c <= 'z'; c++){
				word[index] = c;
				if (f.find(c) != string::npos){
					f.erase(f.find(c),1);
					getCombinations(word, f, results, index+1, dict);
					f = floating;
				}
				else{
					getCombinations(word, f, results, index+1, dict);
				}
			}
		}
		else{
			return;
		}
	}
	else{
		getCombinations(word, f, results, index+1, dict);
	}
	return;
}



bool isValid(const std::string& word, const std::set<std::string>& dict){
	if (dict.find(word) != dict.end()){
		return true;
	}
	return false;
}



int countChars(const std::string& str){
	int count = 0;
	for (char ch: str){
		if (ch == '-'){
			count++;
		}
	}
	return count;
}



