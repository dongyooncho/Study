#include<iostream>
int arr[10000], len;

int find_rc(int l, int r)
{
	int c = l+1;
	for (; c < r && arr[c] < arr[l]; c++);
	return c;
}

void getSome(int l, int r)
{
	if (l >= r) return;

	int ret = find_rc(l, r);

	getSome(l + 1, ret);
	getSome(ret, r);

	printf("%d\n", arr[l]);
}

int main()
{
	for (len = 0; scanf("%d", &arr[len]) > 0; len++);

	getSome(0, len);

	return 0;
}