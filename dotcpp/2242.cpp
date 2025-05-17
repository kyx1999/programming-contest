// https://www.dotcpp.com/oj/problem2242.html
#include <algorithm>
#include <vector>
#include <stdio.h>
using namespace std;

const int maxn = 2e5 + 5;

int n, m, cnt, a[maxn], root[maxn];
vector<int> v;
struct Node
{
	int l, r, sum;
}hjt[maxn * 40];

int getid(int x)
{
	return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}

void insert(int l, int r, int pre, int &now, int p)
{
	hjt[++cnt] = hjt[pre];
	now = cnt;
	hjt[now].sum++;
	if (l == r)
	{
		return;
	}
	int m = (l + r) >> 1;
	if (p <= m)
	{
		insert(l, m, hjt[pre].l, hjt[now].l, p);
	}
	else
	{
		insert(m + 1, r, hjt[pre].r, hjt[now].r, p);
	}
}

int query(int l, int r, int L, int R, int k)
{
	if (l == r)
	{
		return l;
	}
	int tmp = hjt[hjt[R].r].sum - hjt[hjt[L].r].sum;
	int m = (l + r) >> 1;
	if (k <= tmp)
	{
		return query(m + 1, r, hjt[L].r, hjt[R].r, k);
	}
	else
	{
		return query(l, m, hjt[L].l, hjt[R].l, k - tmp);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", a + i);
		v.push_back(a[i]);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for (int i = 1; i <= n; i++)
	{
		insert(1, n, root[i - 1], root[i], getid(a[i]));
	}
	scanf("%d", &m);
	while(m--)
	{
		int l, r, k;
		scanf("%d %d %d", &l, &r, &k);
		printf("%d\n", v[query(1, n, root[l - 1], root[r], k) - 1]);
	}
	
	return 0;
}
