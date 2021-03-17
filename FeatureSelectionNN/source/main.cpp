/*
=====================================================
	Matthew Lee
	CS170
	Dr.Eamonn Keogh
	Proj 2
=====================================================
*/

#include "D:\Coding\CS170\FeatureSelectionNN\FeatureSelectionNN\header\test.h"
#include "D:\Coding\CS170\FeatureSelectionNN\FeatureSelectionNN\header\parse.h"
#include "D:\Coding\CS170\FeatureSelectionNN\FeatureSelectionNN\header\search.h"

using namespace std;


int main() {
	
	string fname = "CS170_largetestdata__41.txt";

	vector<vector<double>> df = parse(fname);

	feature_search_demo(df);
	
	cout << fixed << setprecision(8);

	unordered_set<int> curr_set;
	curr_set.insert(1);

	/*df.erase(df.begin());

	for (int i = 0; i < df.size(); i++) {
		for (int j = 0; j < df.at(i).size(); j++) {
			if (df[i][j] > 0)
				cout << " ";
			cout << df[i][j] << "    ";
		}
		cout << endl;
	}
	
	vector<vector<double>> asdf = { {1, 2, 3, 4, 5, 6, 7, 8, 9},{1, 2, 3, 4, 5, 6, 7, 8, 9} ,{1, 2, 3, 4, 5, 6, 7, 8, 9} };
	cout << "old ----------------" << endl;
	for (int i = 0; i < asdf.size(); i++) {
		for (int j = 0; j < asdf[0].size(); j++) {
			cout << asdf[i][j] << "   ";
		}
		cout << endl;
	}
	
	asdf.erase(asdf.begin());
	cout << "newwwww ------------" << endl;
	for (int i = 0; i < asdf.size(); i++) {
		for (int j = 0; j < asdf[0].size(); j++) {
			cout << asdf[i][j] << "   ";
		}
		cout << endl;
	}*/

	cout << "program finished" << endl;
}

