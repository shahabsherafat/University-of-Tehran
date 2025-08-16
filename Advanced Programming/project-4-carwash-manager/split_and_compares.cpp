#include <iostream>
#include <vector>
#include "split_and_compares.hpp"
using namespace std;

vector<string> split(string s, string delimiter){
    int start = 0, end = 0;
    vector <string> result;

    while (end != -1) {
        end = s.find(delimiter, start);
        string segment = s.substr(start, end - start);

        if(segment != EMPTY){
            result.push_back(segment);
        }

        start = end + delimiter.size();
    }

    return result;
}

bool compare_by_first(pair<string,string> p1, pair<string,string> p2){
    return stoi(p1.first) < stoi(p2.first);
}
