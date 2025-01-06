const int MOD = 1000000007;
int cache[102];

int tiling(int n);

int asymTiling(int n)
{
    if (n <= 2) return 0;
    int& res = cache[n];
    if (res != -1) return res;

    res = 0;
    res = (res + asymTiling(n - 2)) % MOD; // |    | -> 2칸, 내부는 무조건 비대칭이어야 함.
    res = (res + asymTiling(n - 4)) % MOD; // =    = -> 4칸, 내부는 무조건 비대칭이어야 함.
    res = (res + tiling(n - 3)) % MOD; // |    = -> 3칸, 애초에 비대칭.
    res = (res + tiling(n - 3)) % MOD; // =    | -> 3칸, 애초에 비대칭.

    return res;
}