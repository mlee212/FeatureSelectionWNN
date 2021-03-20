#ifndef __PARSE__
#define __PARSE__

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<double>> parse(string fname) {
	string lineStr;
	string currStr;
	string path = "D:/Coding/CS170/FeatureSelectionNN/FeatureSelectionNN/resource/";

	ifstream rf(path + fname);

	vector<vector<double>> ret;
	vector<double> temp;

	if (!rf) {
		cout << "File not found";
		temp.push_back(-1);
		ret.push_back(temp);
		return ret;
	}

	// read files and create a 2d array of the data
	while (getline(rf, lineStr)) {
		stringstream reader(lineStr);
		temp.clear();

		while (reader >> currStr) {
			temp.push_back(stod(currStr));
		}
		ret.push_back(temp);
	}

	rf.close();

	return ret;
}

#endif