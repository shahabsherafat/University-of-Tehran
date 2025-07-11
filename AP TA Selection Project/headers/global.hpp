#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <regex>
#include <set>

using namespace std;

const string ROOT_TYPE = "root";
const string MANDATORY_TYPE = "mandatory";
const string OPTIONAL_TYPE = "optional";
const string ALTERNATIVE_TYPE = "alternative";
const string OR_TYPE = "or";
const string NO_CHILD = "no child";

const string COMBINATION_TYPE = "combination";

const string INVALID_CONFIG = "Invalid";
const string VALID_CONFIG = "Valid";

const string END_OF_DESCRIPTIONS = "#";
const string END_OF_CONFIGS = "##";
const string END_OF_TESTS = "###";
const string END_OF_RESULTS = "+++";
const string OR_SIGN = "|";
const string XOR_SIGN = "^";
const string COMBINATION_SIGN = "+";
const string QUESTION_MARK = "?";
const string EMPTY_STRING = "";

#define debug(x) cout << x << endl, exit(0);