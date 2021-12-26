#include <bits/stdc++.h>

using namespace std;

int n;
bitset<1000> arr[500001];
bitset<1000> tree[2000004];

void build_tree(int v, int tl, int tr)
{
    if (tl == tr)
        tree[v] = arr[tl];
    else
    {
        int tm = (tl + tr) / 2;
        build_tree(v * 2, tl, tm);
        build_tree(v * 2 + 1, tm + 1, tr);
        tree[v] = tree[v * 2] ^ tree[v * 2 + 1];
    }
}

bitset<1000> get_sum(int l, int r, int v, int tl, int tr)
{
    if (l <= tl && tr <= r)
        return tree[v];

    if (tr < l || r < tl)
        return 0;

    int tm = (tl + tr) / 2;

    return get_sum(l, r, v * 2, tl, tm) ^ get_sum(l, r, v * 2 + 1, tm + 1, tr);;
}

void update(int idx, int val, int v, int tl, int tr)
{
    if (idx <= tl && tr <= idx)
    {
        arr[idx] = 0;
        tree[v] = 0;
        arr[idx][val] = 1;
        tree[v][val] = 1;
        return;
    }

    if (tr < idx || idx < tl)
        return;

    int tm = (tl + tr) / 2;
    update(idx, val, v * 2, tl, tm);
    update(idx, val, v * 2 + 1, tm + 1, tr);

    tree[v] = tree[v * 2] ^ tree[v * 2 + 1];
}

int main()
{
    ifstream fin("array.in");
    ofstream fout("array.out");
    int n, q;
    fin >> n >> q;
    int l;
    for(int i = 0; i < n; i++)
        arr[i] = 0;
    for(int i = 0; i < n; i++)
    {
        fin >> l;
        arr[i][l - 1] = 1;
    }
    build_tree(1, 0, n - 1);
    string oper;
    int first, second;
    for(int i = 0; i < q; i++)
    {
        fin >> oper;
        fin >> first;
        fin >> second;
        if(oper == "Q")
            fout << get_sum(first - 1, second - 1, 1, 0, n - 1).count() << "\n";
        else if (oper == "S")
            update(first - 1, second - 1, 1, 0, n - 1);
        else
            cout << "Error" << "\n";
    }
    return 0;
}
