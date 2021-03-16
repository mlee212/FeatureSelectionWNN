#ifndef __SEARCH__
#define __SEARCH__

#include <unordered_set>
#include <math.h>

using namespace std;

int LOOCrossVal(vector<vector<double>> df, unordered_set<int> curr_set, int k) {
	vector<double> object;
	int label = 0;
	int nndist = 0;
	int nnloc = 0;
	int nnlabel = 0;

	int correct = 0;

	for (int i = 0; i < df.size(); i++) {
		object = df.at(i);
		label = df.at(i).at(0);

		nndist = INT_MAX;
		nnloc = INT_MAX;
		for (int k = 0; k < df.size(); k++) {
			if (k != i) {
				int dist = 0;
				for (int j = 0; j < object.size(); j++) {
					dist += pow(object[j] - df[k][j], 2);
				}
				sqrt(dist);
				if (dist < nndist) {
					nndist = dist;
					nnloc = k;
					nnlabel = df[nnloc][0];
				}
			}
		}
		if (label == nnloc) {
			correct++;
		}
	}
	return correct / df.size();
}

void feature_search_demo(vector<vector<double>> df) {

	unordered_set<int> curr_set;
	int acc = 0;
	int best_acc_rn;
	int feat_add_ind;

	for (int i = 0; i < df[0].size(); i++) {
		cout << "On the " << i << "th level of the search tree" << endl;
		feat_add_ind = 0;
		best_acc_rn = 0;

		for (int k = 0; k < df[0].size(); k++) {
			if (curr_set.find(k) == curr_set.end()) {
				cout << "\t--Considering adding the " << k << " feature" << endl;
				acc = LOOCrossVal(df, curr_set, k);
			}

			if (acc > best_acc_rn) {
				best_acc_rn = acc;
				feat_add_ind = k;
			}
		}
		cout << "On level " << i << " i added feature " << feat_add_ind << " to current set\n" << endl;
	}
}

#endif