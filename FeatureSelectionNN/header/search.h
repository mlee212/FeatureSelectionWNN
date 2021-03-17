#ifndef __SEARCH__
#define __SEARCH__

#include <unordered_set>
#include <math.h>

using namespace std;

double LOOCrossVal(vector<vector<double>> df, unordered_set<int> curr_set, int k) {
	vector<vector<double>> dfcpy = df;
	unordered_set<int> new_set = curr_set;
	new_set.insert(k);


	for (int a = 0; a < dfcpy.size(); a++) {
		dfcpy[a].erase(dfcpy[a].begin());
		for (int b = 0; b < dfcpy.at(a).size(); b++) {
			
			if (new_set.find(b) == new_set.end()) {
				dfcpy[a][b] = 0;
			}

		}
	}
	cout << fixed << setprecision(8);
	//cout << "NEW LOO CALL: " << endl;
	/*for (int i = 0; i < dfcpy.size(); i++) {
		for (int j = 0; j < dfcpy.at(i).size(); j++) {
			if (dfcpy[i][j] > 0)
				cout << " ";
			cout << dfcpy[i][j] << "    ";
		}
		cout << endl;
	}*/

	vector<double> object;
	int label = 0;
	double nndist = 0;
	int nnloc = 0;
	int nnlabel = 0;

	int correct = 0;

	

	for (int i = 0; i < dfcpy.size(); i++) {
		object.clear();
		//cout << "object: ";
		for (int y = 0; y < dfcpy[i].size(); y++) {
			object.push_back(dfcpy[i][y]);
			//cout << "i: " << i << " y: " << y << endl;
			//cout << dfcpy[i][y] << " ";
		}
		//cout << endl;
		label = df.at(i).at(0);
		//cout << "we made it" << endl;
		nndist = 999;
		nnloc = 999;
		//cout << "======================================================================================================================" << endl;
		//cout << "unordered set: " << new_set.size() << endl;
		for (int k = 0; k < dfcpy.size(); k++) {
			if (k != i) {
				double dist = 0;
				//cout << endl << "dist calc: " << endl;
				for (int j = 0; j < object.size(); j++) {
					
					//cout << object[j] << " - " << df[k][j + 1] << endl;
					/*cout << "j: " << j << endl;
					cout << "k: " << k << endl;
					cout << "obj size: " << object.size() << endl;
					cout << "dfcpy[k]: " << dfcpy[k].size() << endl;*/
					

					/*cout << "j: " << j << endl;
					cout << "j-1: " << j - 1 << endl;
					cout << "k: " << k << endl;
					cout << "object[j-1]: " << object[j-1] << endl;
					cout << "dfcpy[k][j-1]: " << dfcpy[k][j-1] << endl;*/
					
					/*cout << "obj[j] - dfcpy[k][j]: " << object[j] << " - " << dfcpy[k][j] << " = " << object[j] - dfcpy[k][j] << endl;
					cout << "pow(object[j] = dfcpy[k][j]: " << pow((object[j] - dfcpy[k][j]), 2) << endl;
					cout << "dist + new dist: " << dist + pow((object[j] - dfcpy[k][j]), 2) << endl;*/
					dist += pow((object[j] - dfcpy[k][j]), 2);
					//cout << "j: " << j << endl;
				
				}
				//cout << "dist: " << dist << endl;
				dist = sqrt(dist);
				//cout << "sqrt dist: " << dist << endl << endl;
				/*cout << "-------------------" << endl;
				cout << "nndist: " << nndist << endl;
				cout << "dist: " << dist << endl;*/
				if (dist < nndist) {
					nndist = dist;
					nnloc = k;
					nnlabel = df[nnloc][0];
					
					
					/*cout << "i: " << i << endl;
					cout << "k: " << k << endl;

					cout << "nnloc: " << nnloc << endl;
					cout << "nnlabel: " << nnlabel << endl;*/

					
				}
			}
		}
		
		//cout << "label: " << label << endl;
		//cout << "nnlabel: " << nnlabel << endl;
		//cout << "correct: " << correct << endl << endl;
		if (label == nnlabel) {
			correct = correct + 1;
			
			//cout << "\n\nnndist: " << nndist << endl;
			//cout << "curr: " << i << endl;
			//cout << "nnloc: " << nnloc << endl;

		}
	}
	//cout << "---------------------" << endl;
	//cout << "correct: " << correct << endl;
	//cout << "data size: " << df.size() << endl;
	//cout << "acc: " << static_cast<double> (correct) / df.size() << endl;
	return static_cast<double> (correct) / df.size();
}

void feature_search_demo(vector<vector<double>> df) {

	unordered_set<int> curr_set;
	unordered_set<int> best_set;
	double acc = 0;
	double best_acc_rn = 0;
	double overall_acc = 0;
	int feat_add_ind;
	

	for (int i = 0; i < df[0].size()-1; i++) {
		cout << "On the " << i + 1 << "th level of the search tree" << endl;
		feat_add_ind = 0;
		best_acc_rn = 0;

		for (int k = 0; k < df[0].size()-1; k++) {
			if (curr_set.find(k) == curr_set.end()) {
				cout << "\t--Considering adding the " << k + 1 << " feature" << endl;
				acc = LOOCrossVal(df, curr_set, k);
				cout << "\t\tacc: " << acc << endl;
				cout << "\t\tbest_curr_acc: " << best_acc_rn << endl;
				cout << "\t\tCurr set: ";
				for (auto it = curr_set.cbegin(); it != curr_set.cend(); it++) {
					cout << *it + 1 << " ";
				}
				cout << endl;
				if (acc > best_acc_rn) {
					best_acc_rn = acc;
					feat_add_ind = k;
				}
				
			}
		}
		cout << "overall_acc: " << overall_acc << endl;
		curr_set.insert(feat_add_ind);
		if (best_acc_rn > overall_acc) {
			overall_acc = best_acc_rn;
			best_set = curr_set;
		}
		
		
		cout << "On level " << i + 1 << ", " << feat_add_ind + 1 << " was added to current set\n" << endl;
	}
	cout << "best set: ";
	for (auto it = best_set.cbegin(); it != best_set.cend(); it++) {
		cout << *it + 1 << " ";
	}
	cout << endl;
	cout << "BEST ACCURACY: " << overall_acc << endl;
}

#endif