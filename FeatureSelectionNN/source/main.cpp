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
	
	string fname = "CS170_SMALLtestdata__56.txt";

	vector<vector<double>> df = parse(fname);

	feature_search_demo(df);
	
	/*cout << fixed << setprecision(8);

	for (int i = 0; i < df.size(); i++) {
		for (int j = 0; j < df.at(i).size(); j++) {
			if (df[i][j] > 0)
				cout << " ";
			cout << df[i][j] << "    ";
		}
		cout << endl;
	}*/


	cout << "program finished" << endl;
}

