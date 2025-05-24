#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <climits>
#include <iomanip>
#include <algorithm>
#define DBL_MAX numeric_limits<double>::max()
using namespace std;

void vertex_Answer(vector<vector<double>>& c, vector<vector<double>>& d, vector<vector<int>>& k_val, vector<pair<int, int>>& ans, int k, int i, int s) {
	if (s < 4) return;

	if (d[i][i + k] != 0.0) ans.push_back({ i,i + k });
	if (d[i + k][i + s - 1] != 0.0) ans.push_back({ i + k, i + s - 1 });

	vertex_Answer(c, d, k_val, ans, k_val[i][k + 1], i, k + 1);
	vertex_Answer(c, d, k_val, ans, k_val[i + k][s - k], i + k, s - k);
}

double vertex_Distance(double x1, double x2, double y1, double y2) {
	return sqrt(pow(abs(x1 - y1), 2) + pow(abs(x2 - y2), 2));
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	ifstream in("MT_command.txt");
	if (!in.is_open()) {
		cerr << "cannot open the file: MT_command.txt" << '\n';
		return 1;
	}

	int T;
	in >> T;

	string input_file, output_file;
	while (T--) {
		in >> input_file >> output_file;
		ifstream fin(input_file);
		if (!fin.is_open()) {
			cerr << "cannot open the file: " << input_file << '\n';
			return 1;
		}
		ofstream fout(output_file);

		int n;
		fin >> n;

		if (n <= 3) {
			fout << fixed << setprecision(3) << 0.0;
			fin.close();
			fout.close();
			continue;
		}

		vector<vector<double>> c(n + 1, vector<double>(n + 1, 0));
		vector<vector<double>> d(n + 1, vector<double>(n + 1, 0));
		vector<vector<int>> k_val(n + 1, vector<int>(n + 1, 0));
		vector<pair<double, double>> v;
		vector<pair<int, int>> ans;

		for (int i = 0; i < n; i++) {
			double a, b;
			fin >> a >> b;
			v.push_back({ a,b });
		}

		for (int i = 0; i < v.size() - 2; i++) {
			for (int j = i + 2; j < v.size(); j++) {
				double dist = vertex_Distance(v[i].first, v[i].second, v[j].first, v[j].second);
				d[i][j] = dist;
				d[j][i] = dist;
			}
		}
		d[0][n - 1] = 0;
		d[n - 1][0] = 0;

		for (int s = 4; s <= n; s++) {
			for (int i = 0; i <= n - s; i++) {
				double mn = DBL_MAX;
				for (int k = 1; k <= s - 2; k++) {
					double tmp = c[i][k + 1] + c[i + k][s - k] + d[i][i + k] + d[i + k][i + s - 1];
					if (tmp < mn) {
						mn = tmp;
						k_val[i][s] = k;
					}
				}
				c[i][s] = mn;
			}
		}
		vertex_Answer(c, d, k_val, ans, k_val[0][n], 0, n);
		sort(ans.begin(), ans.end());

		fout << fixed << setprecision(3) << c[0][n] << '\n';

		int i;
		for (i = 0; i < ans.size() - 1; i++) {
			fout << ans[i].first << ' ' << ans[i].second << '\n';
		}
		fout << ans[i].first << ' ' << ans[i].second;

		fin.close();
		fout.close();
	}

	in.close();
	return 0;
}