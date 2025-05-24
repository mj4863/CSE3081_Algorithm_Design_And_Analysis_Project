#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	ifstream in("LPS_command.txt");

	if (!in.is_open()) {
		cerr << "cannot open the file: LPS_command.txt" << '\n';
		return 1;
	}

	int file_Num;
	in >> file_Num;

	string input_file, output_file;
	while (file_Num--) {
		in >> input_file >> output_file;
		ifstream fin(input_file);
		if (!fin.is_open()) {
			cerr << "cannot open the file: " << input_file << '\n';
			return 1;
		}

		int T;
		fin >> T;

		ofstream fout(output_file);
		fout << T;

		while (T--) {
			int n;
			string str;
			fin >> n >> str;

			vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
			for (int i = 1; i <= n; i++) {
				dp[i][i] = 1;
			}

			for (int k = 2; k <= n; k++) {
				for (int i = 1, j = k; j <= n; i++, j++) {
					if (str[i - 1] != str[j - 1]) {
						dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
					}
					else {
						dp[i][j] = dp[i + 1][j - 1] + 2;
					}
				}
			}

			string ans, copy;
			
			int row = 1, col = n;
			while (row < col) {
				if (str[row - 1] == str[col - 1]) {
					ans += str[row - 1];
					row++;
					col--;
				}
				else if (dp[row + 1][col] > dp[row][col - 1]) {
					row++;
				}
				else {
					col--;
				}
			}

			copy = ans;
			reverse(copy.begin(), copy.end());

			if (dp[row][col]) ans += str[row - 1];
			ans += copy;
			
			fout << '\n' << ans.length() << '\n' << ans;
		}

		fin.close();
		fout.close();
	}

	in.close();
	return 0;
}