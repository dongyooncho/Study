// 1, 2, 3, 4 : l의 크기로 1, 2, 3, 4 1회
// 5, 6, 7, 8 : N의 크기로 1, 2, 3, 4 1회, l의 크기로 1, 2, 4, 3 1회
#include <iostream>
#include<queue>
using namespace std;

int N, R, k, l; // k번 연산을 l단계로
int arr[128][128], square[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
queue<int> Q;

void tilt_ud(int sx, int ex, int sy, int ey, int lev)
{
	if (ex - sx == square[lev])
	{
		for (int x = sx; x < ex; x++)
		{
			for (int y = sy; y < ey; y++)
			{
				Q.push(arr[y][x]);
			}

			for (int y = ey - 1; y >= sy; y--)
			{
				arr[y][x] = Q.front();
				Q.pop();
			}
		}
	}
	else if (ex - sx > square[lev])
	{
		int mx = (ex + sx) / 2;
		int my = (ey + sy) / 2;

		// 4등분
		tilt_ud(sx, mx, sy, my, lev);
		tilt_ud(mx, ex, sy, my, lev);
		tilt_ud(sx, mx, my, ey, lev);
		tilt_ud(mx, ex, my, ey, lev);
	}
}

void tilt_lr(int sx, int ex, int sy, int ey, int lev)
{
	if (ex - sx == square[lev])
	{
		for (int y = sy; y < ey; y++)
		{
			for (int x = sx; x < ex; x++)
			{
				Q.push(arr[y][x]);
			}

			for (int x = ex - 1; x >= sx; x--)
			{
				arr[y][x] = Q.front();
				Q.pop();
			}
		}
	}
	else if (ex - sx > square[lev])
	{
		int mx = (ex + sx) / 2;
		int my = (ey + sy) / 2;

		// 4등분
		tilt_lr (sx, mx, sy, my, lev);
		tilt_lr(mx, ex, sy, my, lev);
		tilt_lr(sx, mx, my, ey, lev);
		tilt_lr(mx, ex, my, ey, lev);
	}
}

void turn_l(int sx, int ex, int sy, int ey, int lev)
{
	if (ex - sx == square[lev])
	{
		for (int y = sy; y < ey; y++)
		{
			for (int x = sx; x < ex; x++)
			{
				Q.push(arr[y][x]);
			}
		}
		for (int x = sx; x < ex; x++)
		{
			for (int y = ey - 1; y >= sy; y--)
			{
				arr[y][x] = Q.front();
				Q.pop();
			}
		}
	}
	else if (ex - sx > square[lev])
	{
		int mx = (ex + sx) / 2;
		int my = (ey + sy) / 2;

		// 4등분
		turn_l(sx, mx, sy, my, lev);
		turn_l(mx, ex, sy, my, lev);
		turn_l(sx, mx, my, ey, lev);
		turn_l(mx, ex, my, ey, lev);
	}
}

void turn_r(int sx, int ex, int sy, int ey, int lev)
{
	if (ex - sx == square[lev])
	{
		for (int y = sy; y < ey; y++)
		{
			for (int x = sx; x < ex; x++)
			{
				Q.push(arr[y][x]);
			}
		}
		for (int x = ex - 1; x >= sx; x--)
		{
			for (int y = sy; y < ey; y++)
			{
				arr[y][x] = Q.front();
				Q.pop();
			}
		}
	}
	else if (ex - sx > square[lev])
	{
		int mx = (ex + sx) / 2;
		int my = (ey + sy) / 2;

		// 4등분
		turn_r(sx, mx, sy, my, lev);
		turn_r(mx, ex, sy, my, lev);
		turn_r(sx, mx, my, ey, lev);
		turn_r(mx, ex, my, ey, lev);
	}
}

int main()
{
	scanf("%d %d", &N, &R);
	for (int y = 0; y < square[N]; y++)
		for (int x = 0; x<square[N]; x++)
			scanf("%d", &arr[y][x]);

	for (int tc = 0; tc < R; tc++)
	{
		scanf("%d %d", &k, &l);
		if (k < 5 && l == 0) continue; // 변화 없는 연산은 건너뛰기

		switch (k)
		{
		case 5:
			tilt_ud(0, square[N], 0, square[N], N);
		case 1:
			tilt_ud(0, square[N], 0, square[N], l);
			break;
		case 6:
			tilt_lr(0, square[N], 0, square[N], N);
		case 2:
			tilt_lr(0, square[N], 0, square[N], l);
			break;
		case 8:
			turn_l(0, square[N], 0, square[N], N);
		case 3:
			turn_r(0, square[N], 0, square[N], l);
			break;
		case 7:
			turn_r(0, square[N], 0, square[N], N);
		case 4:
			turn_l(0, square[N], 0, square[N], l);
			break;
		}
	}

	for (int y = 0; y < square[N]; y++)
	{
		for (int x = 0; x < square[N]; x++)
			printf("%d ", arr[y][x]);
		printf("\n");
	}

	return 0;
}