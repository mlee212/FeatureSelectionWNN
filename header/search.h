#ifndef __SEARCH__
#define __SEARCH__

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <math.h>


using namespace std;

// accuracy function for forward
double LOOCrossValForward(vector<vector<double>> df, unordered_set<int> curr_set, int cFeat) {
	vector<vector<double>> dfcpy = df;
	unordered_set<int> new_set = curr_set;
	new_set.insert(cFeat);

	// clause to compute accuracy for empty set
	if(cFeat==-1){
		new_set.clear();
	}

	// clause to ignore columns 
	for (int a = 0; a < dfcpy.size(); a++) {
		dfcpy[a].erase(dfcpy[a].begin());
		for (int b = 0; b < dfcpy.at(a).size(); b++) {
			
			if (new_set.find(b) == new_set.end()) {
				dfcpy[a][b] = 0;
			}
		}
	}
	cout << fixed << setprecision(8);

	vector<double> object;
	int label = 0;
	double nndist = 0;
	int nnloc = 0;
	int nnlabel = 0;
	int correct = 0;

	// Dr. Eamonn Keogh's Pseudocode format
	for (int i = 0; i < dfcpy.size(); i++) {
		object.clear();
		for (int y = 0; y < dfcpy[i].size(); y++) {
			object.push_back(dfcpy[i][y]);
		}
		label = df.at(i).at(0);
		nndist = 999;
		nnloc = 999;
		for (int k = 0; k < dfcpy.size(); k++) {
			if (k != i) {
				double dist = 0;
				for (int j = 0; j < object.size(); j++) {
					dist += pow((object[j] - dfcpy[k][j]), 2);
				}
				dist = sqrt(dist);
				if (dist < nndist) {
					nndist = dist;
					nnloc = k;
					nnlabel = df[nnloc][0];
				}
			}
		}
		if (label == nnlabel) {
			correct = correct + 1;
		}
	}
	return static_cast<double> (correct) / df.size();
}

// accuracy function for backward
double LOOCrossValBackward(vector<vector<double>> df, unordered_set<int> curr_set, int cFeat) {
	vector<vector<double>> dfcpy = df;
	unordered_set<int> new_set = curr_set;
	
	// clause to compute accuracy for empty set
	if(cFeat !=-1){
		new_set.erase(new_set.find(cFeat));
	}

	// clause to ignore columns 
	for (int a = 0; a < dfcpy.size(); a++) {
		dfcpy[a].erase(dfcpy[a].begin());
		for (int b = 0; b < dfcpy.at(a).size(); b++) {
			if (new_set.find(b) == new_set.end()) {
				dfcpy[a][b] = 0;
			}
		}
	}
	
	cout << fixed << setprecision(8);
	vector<double> object;
	int label = 0;
	double nndist = 0;
	int nnloc = 0;
	int nnlabel = 0;
	int correct = 0;

	// Dr. Eamonn Keogh's Pseudocode format
	for (int i = 0; i < dfcpy.size(); i++) {
		object.clear();
		for (int y = 0; y < dfcpy[i].size(); y++) {
			object.push_back(dfcpy[i][y]);
		}
		label = df.at(i).at(0);
		nndist = 999;
		nnloc = 999;
		for (int k = 0; k < dfcpy.size(); k++) {
			if (k != i) {
				double dist = 0;
				for (int j = 0; j < object.size(); j++) {
					dist += pow((object[j] - dfcpy[k][j]), 2);
				}
				dist = sqrt(dist);
				if (dist < nndist) {
					nndist = dist;
					nnloc = k;
					nnlabel = df[nnloc][0];
				}
			}
		}
		if (label == nnlabel) {
			correct = correct + 1;
		}
	}
	return static_cast<double> (correct) / df.size();
}

// forward search fxn call
void feature_search_forward(vector<vector<double>> df, string fileNum, int fsz) {
	string trace;
	string jData;
	
	// file name string generator to write to
	if (fsz == 1) {
		trace = "CS170_large_fwd" + fileNum + "_print.txt";
		jData = "large_fwd" + fileNum + "data.json";
	}
	else if(fsz == 2){
		trace = "CS170_small_fwd" + fileNum + "_print.txt";
		jData = "small_fwd" + fileNum + "data.json";
	}
	else if(fsz == 3){
		trace = "CS170_spec_small_fwd" + fileNum + "_print.txt";
		jData = "spec_small_fwd" + fileNum + "data.json";
	}
	else{
		exit(1);
	}
	
	ofstream ofs(trace, ofstream::out);
	ofstream datofs(jData, ofstream::out);

	// menu output to file
	ofs << "Welcome to Matthew Lee\'s Feature Selection.\n" << endl;
	ofs << "Which file size would you like? Large, small, or special small file size? (1, 2, or 3): ";
	ofs << fsz << endl;
	ofs << "Please enter the file number: ";
	ofs << fileNum << endl;
	ofs << "Enter your choice of algorithm\n\t1) Forward Selection\n\t2) Backward Elimination" << endl;
	ofs << "1\n" << endl;

	ofs << setprecision(3);
	datofs << setprecision(3);

	unordered_set<int> curr_set;
	unordered_set<int> best_set;
	double acc = 0;
	double best_acc_rn = 0;
	double overall_acc = 0;
	int feat_add_ind;
	
	double empty_acc = LOOCrossValForward(df, curr_set, -1);

	ofs << "Accuracy of the empty set: " << empty_acc << endl;

	datofs << "[[0, " << empty_acc << "],";

	for (int i = 0; i < df[0].size()-1; i++) {
		ofs << "On the " << i + 1 << "th level of the search tree" << endl;
		cout << "level: " << i + 1 << endl;
		feat_add_ind = 0;
		best_acc_rn = 0;

		for (int k = 0; k < df[0].size()-1; k++) {
			if (curr_set.find(k) == curr_set.end()) {
				ofs << "\t--Considering adding feature " << k + 1 << endl;
				acc = LOOCrossValForward(df, curr_set, k);
				if (acc > best_acc_rn) {
					best_acc_rn = acc;
					feat_add_ind = k;
				}
				
			}
		}
		
		curr_set.insert(feat_add_ind);
		if (best_acc_rn > overall_acc) {
			overall_acc = best_acc_rn;
			best_set = curr_set;
		}
		ofs << "overall_acc: " << overall_acc << endl;
		ofs << "On level " << i + 1 << ", " << feat_add_ind + 1 << " was added to current set\n" << endl;
		
		// writing to JSON file
		if(i + 2 != df[0].size()){
			datofs << "[" << i + 1 << ", " << best_acc_rn << "],";
		}
		else{
			datofs << "[" << i + 1 << ", " << best_acc_rn << "]]";
		}
	}
	ofs << "best set: ";
	for (auto it = best_set.cbegin(); it != best_set.cend(); it++) {
		ofs << *it + 1 << " ";
	}
	ofs << endl;
	ofs << "BEST ACCURACY: " << overall_acc << endl;

	datofs.close();
	ofs.close();
}

// backward search fxn call
void feature_search_backward(vector<vector<double>> df, string fileNum, int fsz) {
	string trace;
	string jData;
	
	if (fsz == 1) {
		trace = "CS170_large_bkwd" + fileNum + "_print.txt";
		jData = "large_bkwd" + fileNum + "data.json";
	}
	else if(fsz == 2){
		trace = "CS170_small_bkwd" + fileNum + "_print.txt";
		jData = "small_bkwd" + fileNum + "data.json";
	}
	else if(fsz == 3){
		trace = "CS170_spec_small_bkwd" + fileNum + "_print.txt";
		jData = "spec_small_bkwd" + fileNum + "data.json";
	}
	else{
		exit(1);
	}

	ofstream ofs(trace, ofstream::out);
	ofstream datofs(jData, ofstream::out);

	// menu output to file
	ofs << "Welcome to Matthew Lee\'s Feature Selection.\n" << endl;
	ofs << "Which file size would you like? Large, small, or special small file size? (1, 2, or 3): ";
	ofs << fsz << endl;
	ofs << "Please enter the file number: ";
	ofs << fileNum << endl;
	ofs << "Enter your choice of algorithm\n\t1) Forward Selection\n\t2) Backward Elimination" << endl;
	ofs << "2\n" << endl;

	ofs << setprecision(3);
	datofs << setprecision(3);

	unordered_set<int> curr_set;
	unordered_set<int> best_set;
	double acc = 0;
	double best_acc_rn = 0;
	double overall_acc = 0;
	int feat_add_ind;

	for (int z = 0; z < df[0].size()-1; z++) {
		curr_set.insert(z);
	}

	double empty_acc = LOOCrossValBackward(df, curr_set, -1);

	ofs << "Accuracy of the empty set: " << empty_acc << endl;

	// writing to JSON file
	datofs << "[[0, " << empty_acc << "],";

	for (int i = 0; i < df[0].size() - 1; i++) {
		ofs << "On the " << i + 1 << "th level of the search tree" << endl;
		cout << "level: " << i + 1 << endl;
		feat_add_ind = 0;
		best_acc_rn = 0;

		for (int k = 0; k < df[0].size() - 1; k++) {
			if (curr_set.find(k) != curr_set.end()) {
				ofs << "\t--Considering removing the " << k + 1 << " feature" << endl;
				acc = LOOCrossValBackward(df, curr_set, k);
				if (acc > best_acc_rn) {
					best_acc_rn = acc;
					feat_add_ind = k;
				}

			}
		}
		
		curr_set.erase(curr_set.find(feat_add_ind));
		if (best_acc_rn > overall_acc) {
			overall_acc = best_acc_rn;
			best_set = curr_set;
		}
		ofs << "overall_acc: " << overall_acc << endl;
		ofs << "On level " << i + 1 << ", " << feat_add_ind + 1 << " was removed from the current set\n" << endl;
		
		// writing to JSON file
		if(i + 2 != df[0].size()){
			datofs << "[" << i + 1 << ", " << best_acc_rn << "],";
		}
		else{
			datofs << "[" << i + 1 << ", " << best_acc_rn << "]]";
		}
		
	}
	ofs << "best set: ";
	for (auto it = best_set.cbegin(); it != best_set.cend(); it++) {
		ofs << *it + 1 << " ";
	}
	ofs << endl;
	ofs << "BEST ACCURACY: " << overall_acc << endl;

	datofs.close();
	ofs.close();
}

#endif