// 행렬곱으로 푸는 방식인데 이해하기 어렵다. O((n * maxLen(Song))^3 * logk)
vector<double> getProb2() {
    SquareMatrix W(4*n);

    for (int i = 0; i < 3 * n; ++i) {
        W[i][i + n] = 1.0;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            W[3 * n + i][(4 - length[j]) * n + j] = T[j][i];
        }
    }
    SquareMatrix Wk = W.pow(k);
    vector<double> ret(n);

    for (int song = 0; song < n; ++song) {
        for (int start = 0; start < length[song]; ++start) {
            ret[song] += Wk[(3 - start) * n + song][3 * n];
        }
    }
    return ret;
}