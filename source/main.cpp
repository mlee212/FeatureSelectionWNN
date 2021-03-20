/*
=====================================================
	Matthew Lee
	CS170
	Dr.Eamonn Keogh
	Proj 2
=====================================================
*/

#include <stdio.h>
#include <windows.h>
#include "D:\Coding\Projects\FeatureSelectionNew\header\test.h"
#include "D:\Coding\Projects\FeatureSelectionNew\header\parse.h"
#include "D:\Coding\Projects\FeatureSelectionNew\header\search.h"

using namespace std;

// ----- UNORIGINAL CODE USED TO TRACK CPUTIME FROM: https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9
double get_cpu_time() {
	FILETIME a, b, c, d;
	if (GetProcessTimes(GetCurrentProcess(), &a, &b, &c, &d) != 0) {
		//  Returns total user time.
		//  Can be tweaked to include kernel times as well.
		return
			(double)(d.dwLowDateTime |
				((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
	}
	else {
		//  Handle error
		return 0;
	}
}
// -----

int main() {
	string fileNum;
	int fsz;

	// menu
	cout << "Welcome to Matthew Lee\'s Feature Selection.\n" << endl;
	cout << "Which file size would you like? Large, small, or special small file size? (1, 2, or 3): ";
	cin >> fsz;
	cout << "Please enter the file number: ";
	cin >> fileNum;
	int opt;
	cout << "Enter your choice of algorithm\n\t1) Forward Selection\n\t2) Backward Elimination" << endl;
	cin >> opt;

	string fname;

	// file name string generator to read from
	if(fsz == 1) {
		fname = "CS170_largetestdata__" + fileNum + ".txt";
	}
	else if(fsz == 2){
		fname = "CS170_SMALLtestdata__" + fileNum + ".txt";
	}
	else if(fsz == 3){
		fname = "CS170_small_special_testdata__" + fileNum + ".txt";
	}
	else{
		exit(1);
	}

	vector<vector<double>> df = parse(fname);

	double begintimer;
	double endtimer;
	double elapsedtimer;
	
	// Forward selection or Backward elimination
	if(opt == 1){
		begintimer = get_cpu_time();
		feature_search_forward(df, fileNum, fsz);
		endtimer = get_cpu_time();
		elapsedtimer = (endtimer - begintimer);
	}
	else if(opt == 2){
		begintimer = get_cpu_time();
		feature_search_backward(df, fileNum, fsz);
		endtimer = get_cpu_time();
		elapsedtimer = (endtimer - begintimer);
	}
	else{
		exit(1);
	}
	

	cout << fixed << setprecision(8);

	// store best set
	unordered_set<int> curr_set;
	curr_set.insert(1);

	// display time elapsed
	printf("Time measured: %3f seconds.\n", elapsedtimer);
	
	string trace;
	string jData;

	// file name generator to write
	if (fsz == 1) {
		trace = "CS170_large_newtime" + fileNum + "_print.txt";
	}
	else if(fsz == 2){
		trace = "CS170_small_time" + fileNum + "_print.txt";
	}
	else if(fsz == 3){
		trace = "CS170_spec_small_time" + fileNum + "_print.txt";
	}
	else{
		exit(1);
	}

	ifstream ifs;
	ofstream ofs;

	// write the time to a new separate file
	ifs.open(trace);
	ofs.open(trace);
	if (ifs.is_open()) {
		ofs << "Time measured: " << elapsedtimer << " seconds." << endl;
	}
	
	ifs.close();
	ofs.close();

	cout << "program finished" << endl;
}

