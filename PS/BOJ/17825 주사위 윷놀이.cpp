#include<iostream>
#define MAX(a, b) a>b?a:b
#define END 0
int cmd[10], ans;
struct NODE {
	int id;
	int score;
	NODE* next;
	NODE* blue;
} node[33], *S, *E;
int maxPoolCnt;

struct PLAYER {
	NODE* pos;
}player[4];

NODE* newNode(int score)
{
	node[maxPoolCnt].score = score;
	node[maxPoolCnt].id = maxPoolCnt;
	return &node[maxPoolCnt++];
}

void createMap()
{
	S = newNode(0), E = &node[32];
	S->score = E->score = END;
	E->id = 32;
	player[0].pos = player[1].pos = player[2].pos = player[3].pos = S;

	node[0].next = newNode(2);
	for (int i = 1; i < 20; ++i)
		node[i].next = newNode((i + 1) * 2);

	node[20].next = E;
	// blue line of node 10
	{
		node[5].blue = newNode(13);
		node[21].next = newNode(16);
		node[22].next = newNode(19);
		node[23].next = newNode(25);
		node[24].next = newNode(30);
		node[25].next = newNode(35);
		node[26].next = &node[20];
	}
	// blue line of node 20
	{
		node[10].blue = newNode(22);
		node[27].next = newNode(24);
		node[28].next = &node[24];
	}
	// blue line of node 30
	{
		node[15].blue = newNode(28);
		node[29].next = newNode(27);
		node[30].next = newNode(26);
		node[31].next = &node[24];
	}
	maxPoolCnt++;
}

void copyPlayerA2B(PLAYER A[], PLAYER B[])
{
	for (int i = 0; i < 4; ++i)
		B[i] = A[i];
}

bool movePlayer(int cnt, int selected)
{
	if (player[selected].pos == E || player[selected].pos->score == 40) return false; // 이미 종료지점에 도착한 말
	if (player[selected].pos->blue) player[selected].pos = player[selected].pos->blue;
	else player[selected].pos = player[selected].pos->next;

	for (int i = 1; i < cnt; ++i)
	{
		if (player[selected].pos == E) return true; // 도착을 넘어가면 도착에서 끝
		player[selected].pos = player[selected].pos->next;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (selected == i) continue;
		if (player[i].pos->id == player[selected].pos->id) return false; // 도착지에 다른 말이 있다면 움직일 수 없음
	}

	// 모든 검증이 끝났다면 움직일 수 있음.
	return true;
}

void DFS(int T, int val)
{
	ans = MAX(ans, val);
	if (T == 10) return;

	bool visited[33] = { false, };
	PLAYER tmp[4];
	copyPlayerA2B(player, tmp);
	for (int now = 0; now < 4; ++now)
	{
		int id = player[now].pos->id;
		if (!visited[id])
		{
			visited[id] = true;

			if (movePlayer(cmd[T], now)) DFS(T + 1, player[now].pos->score + val);
			copyPlayerA2B(tmp, player);
		}
	}
}

void getSome()
{
	int T = 0;
	movePlayer(cmd[T], 0);
	int val = player[0].pos->score;
	T++;

	bool visited[33] = {false,};
	PLAYER tmp[4];
	copyPlayerA2B(player, tmp);
	for (int now = 0; now < 4; ++now)
	{
		int id = player[now].pos->id;
		if (!visited[id])
		{
			// 같은 위치에 있는 말을 여러번 실험할 필요가 없음.
			visited[id] = true;

			if (movePlayer(cmd[T], now)) DFS(T + 1, val + player[now].pos->score);
			copyPlayerA2B(tmp, player);
		}
	}
}

int main()
{
	createMap();
	for (register int i = 0; i < 10; ++i)
		scanf("%d", &cmd[i]);

	getSome();

	printf("%d\n", ans);
	return 0;
}