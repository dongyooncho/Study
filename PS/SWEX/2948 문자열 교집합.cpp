#if 0
#include<iostream>
#define HASH_SIZE (1<<17) 
#define MAXN 100000
#define ll long long
#define DIV (HASH_SIZE - 1)
int N, M, lev;
char A[100000][51], B[51];

bool strCmp(char a[], char b[]) {
	int i = 0;

	for (; a[i]; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return a[i] == b[i];
}

void strCpy(char dst[], char src[]) {
	while (*src) {
		*dst++ = *src++;
	}

	*dst = 0;
}

struct Node {
	char key[11];
	int data;
	Node *next;

	Node *alloc(char _key[], int _data, Node *_next) {
		strCpy(key, _key);
		data = _data;
		next = _next;
		return this;
	}

	/* 찾는 node의 바로 이전 node를 반환한다. */
	Node *getPrevNode(char _key[]) {
		Node *ptr = this;

		while (ptr->next) {
			if (strCmp(_key, ptr->next->key)) {
				break;
			}
			ptr = ptr->next;
		}

		return ptr;
	}
};

struct Hash 
{
	int lev = 0;
	char buf[HASH_SIZE][51];
	int hashTable[HASH_SIZE];

	int getKey(const char* str)
	{
		ll key = 5381;

		int c;
		while (c = *str++)
			key = ((key << 5) + key) + c-'a'+1;

		return (int) (key & DIV);
	}

	int find(char key[])
	{
		int target = getKey(key);
		if (hashTable[target] != lev) return -1;
		while (!strCmp(key, buf[target])) target++;

		return hashTable[target];
	}

	void add(char key[], int data)
	{
		int target = getKey(key);
		while (hashTable[target] == lev) target++;
		hashTable[target] = data;
		strCpy(buf[target], key);
	}

	void remove()
	{
		lev++;
	}
} a;

void init()
{
	a.remove();

}

int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		lev = tc;
		init();
		int ans = 0;
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; ++i)
		{
			scanf("%s", A[i]);
			a.add(A[i], tc);
		}
		for (int i = 0; i < M; ++i)
		{
			scanf("%s", B);
			if (a.find(B) == tc) ++ans;
		}

		printf("#%d %d\n", tc, ans);
	}
	return 0;
}
#endif
#if 1
#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;
int N, M;
char A[51];
string a;
unordered_map <string, int> mM;

void init()
{
	mM = {};
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		init();
		int ans = 0;
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; ++i)
		{
			scanf("%s", A);
			a = string (A);
			mM.insert({ a, tc });
		}
		for (int i = 0; i < M; ++i)
		{
			scanf("%s", A);
			if (mM.find(A) != mM.end()) ++ans;
		}

		printf("#%d %d\n", tc, ans);
	}
	return 0;
}
#endif