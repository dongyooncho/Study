#include<iostream>
struct TREE {
	TREE* parent;
	TREE* l;
	TREE* r;
	int id;
	int count;
	int depth;
} Tree[10001];
int V, E, N1, N2, lca;

void init()
{
	for (int i = 1; i <= V; ++i)
	{
		Tree[i].parent = Tree[i].l = Tree[i].r = nullptr;
		Tree[i].count = 0;
	}
}

int LCA(TREE *x, TREE *y)
{
	if (x->depth < y->depth)
	{
		TREE *buf = x;
		x = y;
		y = buf;
	}

	while (x->depth != y->depth)
		x = x->parent;

	while (x != y)
	{
		x = x->parent;
		y = y->parent;
	}

	return x->id;
}

void setDepth(TREE* root, int d)
{
	root->depth = d;
	if (root->l != nullptr)
		setDepth(root->l, d + 1);
	if (root->r != nullptr)
		setDepth(root->r, d + 1);
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 1; i < 10001; ++i)
		Tree[i].id = i;

	for (int tc = 1; tc <= T; ++tc)
	{
		scanf("%d %d %d %d", &V, &E, &N1, &N2);
		init();
		for (int i = 0; i < E; ++i)
		{
			int p, c;
			scanf("%d %d", &p, &c);
			int cnt = Tree[c].count + 1;

			Tree[c].parent = &Tree[p];
			if (Tree[p].l == nullptr)
				Tree[p].l = &Tree[c];
			else
				Tree[p].r = &Tree[c];

			TREE *prev = &Tree[c], *next = Tree[c].parent;
			while (prev->parent != nullptr)
			{
				next->count += cnt;
				next = next->parent;
				prev = prev->parent;
			}
		}
		setDepth(&Tree[1], 0);

		lca = LCA(&Tree[N1], &Tree[N2]);
		printf("#%d %d %d\n", tc, lca, Tree[lca].count + 1);
	}
	return 0;
}