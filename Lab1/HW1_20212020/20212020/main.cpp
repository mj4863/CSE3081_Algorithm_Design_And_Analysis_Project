#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <climits>
#include <string>
#include "measure_cpu_time.h"
using namespace std;

// PGM 파일을 2D 배열로 읽어들이는 함수
vector<vector<int>> read_pgmFile(const string& filename, int& n) {
    ifstream file(filename);
    string line;
    int max_val;

    getline(file, line); 
    file >> n >> n;
    file >> max_val;

    vector<vector<int>> image(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            file >> image[i][j];
    }

    file.close();
    return image;
}

// 평균값 파일을 읽는 함수
int read_averageFile(const string& filename) {
    ifstream file(filename);
    int average;
    file >> average;

    file.close();
    return average;
}

// 결과 파일에 결과를 기록하는 함수
void write_resultFile(const string& filename, int sum, int k, int i, int l, int j) {
    ofstream file(filename);

    file << sum << ' ' << k << ' ' << i << ' ' << l << ' ' << j;
    file.close();
}

// Algorithm 3: O(n^4) Summed Area Table
int MaxSumSubrectangle3(vector<vector<int>>& mat, int& k, int& i, int& l, int& j) {
    int n = mat.size();
    int max_sum = INT_MIN;
    vector<vector<int>> sum(n + 1, vector<int>(n + 1, 0));

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            sum[r][c] = mat[r - 1][c - 1] + sum[r - 1][c] + sum[r][c - 1] - sum[r - 1][c - 1];
        }
    }

    for (int r1 = 0; r1 < n; r1++) {
        for (int c1 = 0; c1 < n; c1++) {
            for (int r2 = r1; r2 < n; r2++) {
                for (int c2 = c1; c2 < n; c2++) {
                    int current_sum = sum[r2 + 1][c2 + 1] - sum[r1][c2 + 1] - sum[r2 + 1][c1] + sum[r1][c1];
                    if (current_sum > max_sum) {
                        max_sum = current_sum;
                        k = r1;
                        i = c1;
                        l = r2;
                        j = c2;
                    }
                    else if (current_sum == max_sum) {
                        if (c1 < i || (c1 == i && c2 < j) || (c1 == i && c2 == j && r1 < k) || (c1 == i && c2 == j && r1 == k && r2 < l)) {
                            k = r1;
                            i = c1;
                            l = r2;
                            j = c2;
                        }
                    }
                }
            }
        }
    }

    return max_sum;
}

int max_crossSum(vector<int>& arr, int left, int mid, int right, int& start, int& end) {
    int sum = 0;
    int left_sum = INT_MIN;
    int tmp_start = mid;
    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > left_sum) {
            left_sum = sum;
            tmp_start = i;
        }
    }

    sum = 0;
    int right_sum = INT_MIN;
    int tmp_end = mid + 1;
    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > right_sum) {
            right_sum = sum;
            tmp_end = i;
        }
    }

    start = tmp_start;
    end = tmp_end;
    return left_sum + right_sum;
}

int max_subarraySum(vector<int>& arr, int left, int right, int& start, int& end) {
    if (left == right) {
        start = end = left;
        return arr[left];
    }

    int mid = (left + right) / 2;
    int left_start, left_end, right_start, right_end, cross_start, cross_end;

    int left_max = max_subarraySum(arr, left, mid, left_start, left_end);
    int right_max = max_subarraySum(arr, mid + 1, right, right_start, right_end);
    int cross_max = max_crossSum(arr, left, mid, right, cross_start, cross_end);

    if (left_max >= right_max && left_max >= cross_max) {
        start = left_start;
        end = left_end;
        return left_max;
    }
    else if (right_max >= left_max && right_max >= cross_max) {
        start = right_start;
        end = right_end;
        return right_max;
    }
    else {
        start = cross_start;
        end = cross_end;
        return cross_max;
    }
}

// Algorithm 4: O(n^3 log n) - 열을 합친 후 분할 정복 기법을 적용
int MaxSumSubrectangle4(vector<vector<int>>& mat, int& k, int& i, int& l, int& j) {
    int n = mat.size();
    int max_sum = INT_MIN;

    for (int left = 0; left < n; left++) {
        vector<int> tmp(n, 0);
        for (int right = left; right < n; right++) {
            for (int row = 0; row < n; row++)
                tmp[row] += mat[row][right];

            int start, end;
            int sum = max_subarraySum(tmp, 0, n - 1, start, end);

            // 최대 합을 갱신하고, 직사각형 좌표 저장
            if (sum > max_sum) {
                max_sum = sum;
                k = start;  // 시작 행 (최대 합이 발생한 구간의 시작 행)
                i = left;   // 시작 열
                l = end;    // 끝 행 (최대 합이 발생한 구간의 끝 행)
                j = right;  // 끝 열
            }
        }
    }

    return max_sum;
}

int kadane(vector<int>& arr, int& start, int& end, int n) {
    int max_sum = INT_MIN, current_sum = 0;
    start = -1;
    int tmp_start = 0;
    for (int i = 0; i < n; i++) {
        current_sum += arr[i];
        if (current_sum > max_sum) {
            max_sum = current_sum;
            start = tmp_start;
            end = i;
        }

        if (current_sum < 0) {
            current_sum = 0;
            tmp_start = i + 1;
        }
    }

    return max_sum;
}

// Algorithm 5: O(n^3) using Kadane's Algorithm
int MaxSumSubrectangle5(vector<vector<int>>& mat, int& k, int& i, int& l, int& j) {
    int n = mat.size();
    int max_sum = INT_MIN;

    for (int left = 0; left < n; left++) {
        vector<int> tmp(n, 0);
        for (int right = left; right < n; right++) {
            for (int row = 0; row < n; row++) {
                tmp[row] += mat[row][right];
            }

            int start, end;
            int sum = kadane(tmp, start, end, n);

            if (sum > max_sum) {
                max_sum = sum;
                k = start;
                i = left;
                l = end;
                j = right;
            }
            else if (sum == max_sum) {
                if (left < i || (left == i && right < j) || (left == i && right == j && start < k) || (left == i && right == j && start == k && end < l)) {
                    k = start;
                    i = left;
                    l = end;
                    j = right;
                }
            }
        }
    }

    return max_sum;
}

// Config 파일을 읽고 해당하는 알고리즘을 적용하여 결과를 출력하는 함수
void configfile_process(const string& configFilename) {
    ifstream configFile(configFilename);
    
    if (!configFile.is_open()) {
        cerr << "cannot open the file: " << configFilename << '\n';
        return;
    }

    int testcaseCnt;
    configFile >> testcaseCnt;

    for (int t = 0; t < testcaseCnt; t++) {
        int algorithm_num;
        string pgmFile, averageFile, resultFile;
        configFile >> algorithm_num >> pgmFile >> averageFile >> resultFile;

        pgmFile = "Data/" + pgmFile;
        averageFile = "Data/" + averageFile;
        resultFile = "Data/" + resultFile;

        int n;
        vector<vector<int>> image = read_pgmFile(pgmFile, n);
        int average = read_averageFile(averageFile);

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++)
                image[r][c] -= average;
        }

        int k, i, l, j, sum;

        // 알고리즘 선택 및 시간 측정
        if (algorithm_num == 3) {
            CHECK_TIME_START(_start, _freq);  // 시간 측정 시작
            sum = MaxSumSubrectangle3(image, k, i, l, j);
            CHECK_TIME_END(_start, _end, _freq, _compute_time);  // 시간 측정 끝
            cout << "Algorithm 3 Run Time: " << _compute_time << " ms\n";
        }
        else if (algorithm_num == 4) {
            CHECK_TIME_START(_start, _freq);  // 시간 측정 시작
            sum = MaxSumSubrectangle4(image, k, i, l, j);
            CHECK_TIME_END(_start, _end, _freq, _compute_time);  // 시간 측정 끝
            cout << "Algorithm 4 Run Time: " << _compute_time << " ms\n";
        }
        else if (algorithm_num == 5) {
            CHECK_TIME_START(_start, _freq);  // 시간 측정 시작
            sum = MaxSumSubrectangle5(image, k, i, l, j);
            CHECK_TIME_END(_start, _end, _freq, _compute_time);  // 시간 측정 끝
            cout << "Algorithm 5 Run Time: " << _compute_time << " ms\n\n";
        }

        // 결과 파일에 출력
        write_resultFile(resultFile, sum, k, i, l, j);
    }

    configFile.close();
}

int main() {
    // 상대 경로로 config 파일 읽기
    configfile_process("Data/HW1_config.txt");
    return 0;
}