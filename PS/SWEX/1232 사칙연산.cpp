#include<iostream>
#define MAX_CNT 1001

struct TREE {
	TREE* l;
	TREE* r;
	double n;
	char op;
} Tree[MAX_CNT];

int N, memPoolCnt, ans;

void init()
{
	memPoolCnt = ans = 0;
}

bool isNum(int ch)
{
	if (ch == '+' || ch == '/' || ch == '*' || ch == '-') return false;
	return true;
}

int atoi(char ch[])
{
	int ret = 0;
	for (int i = 0; ch[i]; ++i)
	{
		ret *= 10;
		ret += ch[i] - '0';
	}
	return ret;
}

double calc(int x, int y, int op)
{
	switch (op)
	{
	case '+':
		return x + y;
	case '-':
		return x - y;
	case '*':
		return x * y;
	case '/':
		return x / y;
	}
}

double inOrder(TREE *root)
{
	if (root->l == nullptr) return root->n;
	int l = inOrder(root->l);
	int r = inOrder(root->r);
	root->l = root->r = nullptr;
	return calc(l, r, root->op);
}

int main()
{
	for (int tc = 1; tc <= 10; ++tc)
	{
		scanf("%d", &N);
		for (int i = 0; i < N; ++i)
		{
			int id, l, r;
			char ch[100];
			scanf("%d %s", &id, &ch);

			if (!isNum(ch[0])) // ¿¬»êÀÚ
			{
				scanf("%d %d", &l, &r);
				Tree[id].op = ch[0];
				Tree[id].l = &Tree[l];
				Tree[id].r = &Tree[r];
			}
			else
			{
				Tree[id].n = atoi(ch);
			}
		}
		ans = inOrder(&Tree[1]);
		printf("#%d %d\n", tc, ans);
	}
	return 0;
}