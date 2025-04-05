#include <iostream>
#include <vector>
using namespace std;

const int MAXSEMESTER = 100;
int N, K, M, L;
int indegree[13]; // 들어오는 간선 개수
vector<vector<int>> outnodes; // 나가는 간선 도착노드들
vector<vector<int>> semesters;
int answer = MAXSEMESTER;

vector<int> getSet(int set) {
    vector<int> s;
    int idx = 0;
    int bitmask = 1;
    while (set > 0) {
        if (set & bitmask) {
            s.push_back(idx);
        }
        set >>= 1;
        ++idx;
    }
    return s;
}


bool inTarget(vector<int>& semester_set) {
    return semester_set.size() == 3 && semester_set[0] == 0 && semester_set[1] == 1 && semester_set[2] == 3;
}

bool hasIntersection(vector<int>& lectures, int acc) {
    for (int& lec : lectures) {
        if (acc & (1<<lec)) return true;
    }
    return false;
}

bool canLearn(vector<int>& lectures, vector<int>& sems) {
    for (int& lec : lectures) {
        // if (inTarget(sems)) {
        //     cout << indegree[lec] << " ";
        // }
        if (indegree[lec] > 0) return false;
    }
    // if (inTarget(sems)) {
    //     cout << endl;
    // }
    return true;
}

void cutOutdegrees(int lec, int tp) {
    for (int& node : outnodes[lec]) {
        if (tp == 1) {
            indegree[node] += 1;
        } else {
            indegree[node] -= 1;
        }
    }
}


void calMinSemester(vector<int>& semester_set, int cur_sem_idx, int acc_lecture_set, int sem_cnt, int lec_cnt) {
    // if (semester_set.size() == 3 && semester_set[0] == 0 && semester_set[1] == 1 && semester_set[2] == 3) {
    //     cout << "cursemidx=" << cur_sem_idx << ", " << "acc=" << acc_lecture_set << ", " << "semcnt=" << sem_cnt << ", " << "leccnt=" << lec_cnt << endl;
    // }

    // 다 들었으면 정답 갱신
    if (lec_cnt >= K) {
        answer = min(answer, sem_cnt);
        return;
    }

    // 이미 정답보다 더 많은 학기 들었으면 패스
    if (answer <= sem_cnt)
        return;

    if (semester_set.size() <= cur_sem_idx)
        return;

    // 1. 그냥 넘어가는 경우
    calMinSemester(semester_set, cur_sem_idx + 1, acc_lecture_set, sem_cnt, lec_cnt);

    // 2. 수강 확인하는 경우
    // 수강 후보 집합 구하기 -> 0, 2, 4 과목이 있다면 3개 있는거니까 001 <= x <= 111 사이값이 부분집합임.
    for (int i = 1; i < (1 << semesters[semester_set[cur_sem_idx]].size()); ++i) {
        vector<int> indexes = getSet(i);
        // 개수가 L 이하인지 체크
        if (indexes.size() > L) continue;

        vector<int> lectures;
        for (auto& idx : indexes) {
            lectures.push_back(semesters[semester_set[cur_sem_idx]][idx]);
        }

        // if (semester_set.size() == 3 && semester_set[0] == 0 && semester_set[1] == 1 && semester_set[2] == 3) {
        //     cout << "i:" << i << endl;
        //     cout << "idxes: ";
        //     for (auto& v : indexes) {
        //         cout << v << " ";
        //     }
        //     cout << endl;
        //     cout << "lectures: ";
        //     for (auto& v : lectures) {
        //         cout << v << " ";
        //     }
        //     cout << endl;
        // }

        // if (inTarget(semester_set)) {
        //     cout << "here1?" << endl;
        // }
        // 구해서 누적수강이랑 겹치는거 있으면 패스.
        if (hasIntersection(lectures, acc_lecture_set)) continue;

        // if (inTarget(semester_set)) {
        //     cout << "here2?" << endl;
        // }
        // 선수과목 들어야 하는거 남았으면 패스
        if (!canLearn(lectures, semester_set)) continue;

        // if (inTarget(semester_set)) {
        //     cout << "here3?" << endl;
        // }
        // outdegree 닦아주기
        for (int& lec : lectures) {
            cutOutdegrees(lec, -1);
        }

        // 수강하기
        int new_acc_lecture_set = acc_lecture_set;
        for (int& lec : lectures) {
            new_acc_lecture_set |= (1<<lec);
        }

        // if (semester_set.size() == 3 && semester_set[0] == 0 && semester_set[1] == 1 && semester_set[2] == 3) {
        //     cout << acc_lecture_set << " " << new_acc_lecture_set << endl;
        // }
        // cout << "HER4?" << endl;
        // 다음 학기 확인
        calMinSemester(semester_set, cur_sem_idx + 1, new_acc_lecture_set, sem_cnt + 1, lec_cnt + lectures.size());
        
        // outdegree 붙여주기
        for (int& lec : lectures) {
            cutOutdegrees(lec, 1);
        }
    }
}

void init() {
    outnodes = vector<vector<int>>(N); // 나가는 간선 도착노드들
    semesters = vector<vector<int>>(M);
    for (int i = 0; i < N; ++i) {
        indegree[i] = 0;
    }
    answer = MAXSEMESTER;
}

int main() {
    int C;
    cin >> C;
    while (C--) {
        cin >> N >> K >> M >> L;       
        init(); 
        if (K == 0) {
            cout << 0 << endl;
            continue;
        }
        int R_cnt;
        int R;
        for (int i = 0; i < N; ++i) {
            cin >> R_cnt;
            indegree[i] = R_cnt;
            if (R_cnt == 0) continue; // 선수 과목이 없다.
            for (int j = 0; j < R_cnt; ++j) {
                cin >> R;
                outnodes[R].push_back(i); // 선후수 과목 연결  
            }
        }
        int C_cnt;
        int C;
        for (int i = 0; i < M; ++i) {
            cin >> C_cnt;
            for (int j = 0; j < C_cnt; ++j) {
                cin >> C;
                semesters[i].push_back(C);
            }
        }

        // 비트마스크로 학기 집합 생성
        int bitmask = (1 << M);
        // TODO 집합 개수 작은 순서대로 순회하도록 개선 가능
        for (int i = 1; i < bitmask; ++i) {
            vector<int> sem_set = getSet(i);
            calMinSemester(sem_set, 0, 0, 0, 0); // (후보 학기 집합, 확인할 학기, 누적 수강 강의, 수강학기 개수, 누적 수강과목 개수)           
        }

        if (answer == MAXSEMESTER)
            cout << "IMPOSSIBLE" << endl;
        else
            cout << answer << endl;
    }
}