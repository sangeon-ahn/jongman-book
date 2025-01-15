#include <iostream>
#include <vector>
using namespace std;

int N;
int D;
int P;
int matrix[51][51];
double approxies[101][51];
int way_cnts[51];
vector<vector<double>> answers;
vector<vector<int>> neighbors;

// P_An
void runAway()
{
    for (int i = 0; i < D; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int neighbor : neighbors[j]) {
                approxies[i + 1][j] += approxies[i][neighbor] / way_cnts[neighbor]; 
            }
        }
    }
}

void initApproxies()
{
    for (int i = 0; i < 101; ++i) {
        for (int j = 0; j < 51; ++j) {
            approxies[i][j] = 0;
        }
    }
    approxies[0][P] = 1;
}

void countWays()
{
    for (int i = 0; i < N; ++i) {
        int cnt = 0;
        for (int j = 0; j < N; ++j) {
            if (matrix[i][j] == 1) ++cnt;
        }
        way_cnts[i] = cnt;
    }
}

void setNeighbors()
{
    neighbors = vector<vector<int>>(N);

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (matrix[i][j] == 1) {
                neighbors[i].push_back(j);
                neighbors[j].push_back(i);
            }
        }
    }
}

void init()
{
    initApproxies();
    countWays();
    setNeighbors();
}


int main()
{
    int C;
    cin >> C;
    answers = vector<vector<double>>();

    while (C--)
    {
        cin >> N >> D >> P;
        
        int temp;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> temp; 
                matrix[i][j] = temp;
            }
        }

        init();

        runAway(); // (남은일수, 현재위치)

        int T;
        cin >> T;
        vector<double> temp_vec;
        for (int i = 0; i < T; ++i) {
            cin >> temp;
            temp_vec.push_back(approxies[D][temp]);
        }
        answers.push_back(temp_vec);
    }

    for (auto& vec : answers) {
        for (auto val : vec) {
            cout << val << " ";
        }
        cout << endl;
    }
}