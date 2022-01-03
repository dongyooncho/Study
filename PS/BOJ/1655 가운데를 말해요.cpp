#if 0
/** Case 1
 *  합병 정렬
 */
#include <iostream>
#include <algorithm>
#define MIN(a, b) a < b ? a : b
int N, arr[100001], buf[100001];

void merge(int left, int mid, int right)
{
	int l_cursor = left, r_cursor = mid + 1, dest_cursor = left;

	// 왼쪽과 오른쪽 덩어리에서 작은 순서대로 정렬하며 복사
	while (l_cursor <= mid && r_cursor <= right)
	{
		if (arr[l_cursor] < arr[r_cursor])
			buf[dest_cursor++] = arr[l_cursor++];
		else
			buf[dest_cursor++] = arr[r_cursor++];
	}

	// 남은 값 복사
	for (int j = l_cursor; j <= mid; ++j)
		buf[dest_cursor++] = arr[j];

	for (int j = r_cursor; j <= right; ++j)
		buf[dest_cursor++] = arr[j];

	// 원래 배열로 복사
	for (int j = left; j <= right; ++j)
		arr[j] = buf[j];
}

void merge_sort(int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;

		// 분할
		merge_sort(left, mid);
		merge_sort(mid + 1, right);
		// 합병정렬
		merge(left, mid, right);
	}
}

void print_middle(int time)
{
	if (time % 2 == 1)
		printf("%d\n", arr[(time + 1) / 2]);
	else
		printf("%d\n", MIN(arr[time / 2], arr[time / 2 + 1]));
}

int main()
{
	scanf("%d", &N);

	for (int time = 1; time <= N; ++time)
	{
		// 1. 값 입력
		scanf("%d", &arr[time]);

		// 2. 정렬
		merge_sort(1, time);

		// 3. 중간값 출력
		print_middle(time);
	}

	return 0;
}
#endif

#if 0
/** Case 2
 *  힙 정렬
 */
#include <iostream>
#include <algorithm>
#define MIN(a, b) a < b ? a : b
#define SWAP(a, b) if (a != b) a^=b^=a^=b
int N, sorted[100001], heap[100001], arr[100001];

void push_heap(int num, int count)
{
	int cursor = count;
	heap[cursor] = num;

	while (cursor != 1)
	{
		if (heap[cursor / 2] > heap[cursor])
		{
			SWAP(heap[cursor / 2], heap[cursor]);
			cursor /= 2;
		}
		else
			break;
	}
}

int pop_heap(int count)
{
	int num = arr[1], cursor = 1;
	arr[1] = 987654321;
	SWAP(arr[1], arr[count]);

	for (;;)
	{
		if (cursor * 2 + 1 < count)
		{
			if (arr[cursor] < arr[cursor * 2] && arr[cursor] < arr[cursor * 2 + 1])
				break;

			if (arr[cursor * 2] < arr[cursor * 2 + 1])
			{
				SWAP(arr[cursor * 2], arr[cursor]);
				cursor *= 2;
			}
			else
			{
					SWAP(arr[cursor * 2 + 1], arr[cursor]);
					cursor = cursor * 2 + 1;
			}
		}
		else if (cursor * 2 < count)
		{
			if (arr[cursor * 2] < arr[cursor])
			{
				SWAP(arr[cursor * 2], arr[cursor]);
				cursor *= 2;
			}
			else
				break;
		}
		else
			break;
	}

	return num;
}

void heap_sort(int count)
{
	int i = 1;
	for (int i = 1; i <= count; ++i)
		arr[i] = heap[i];

	for (int c = count; c > 0; --c)
	{
		sorted[i++] = pop_heap(c);
	}
}

void print_middle(int count)
{
	if (count % 2 == 1)
		printf("%d\n", sorted[(count + 1) / 2]);
	else
		printf("%d\n", MIN(sorted[count / 2], sorted[count / 2 + 1]));
}

int main()
{
	scanf("%d", &N);

	for (int count = 1; count <= N; ++count)
	{
		// 1. 값 입력
		int num;
		scanf("%d", &num);
		push_heap(num, count);

		// 2. 정렬
		heap_sort(count);

		// 3. 중간값 출력
		print_middle(count);
	}

	return 0;
}
#endif

#if 1
/** Case 3
 *  최소 힙, 최대 힙 이용
 */
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct comp
{
	bool operator()(int a, int b)
	{
		return a > b;
	}
};

int N;
priority_queue<int> max_heap;
priority_queue<int, vector<int>, comp> min_heap;

int main()
{
	scanf("%d", &N);

	for (int count = 1; count <= N; ++count)
	{
		// 1. 값 입력
		int num;
		scanf("%d", &num);

		if (max_heap.size() == min_heap.size())
			max_heap.push(num);
		else
			min_heap.push(num);

		// 2. 데이터 비교
		int max = max_heap.top();
		int min = min_heap.size() ? min_heap.top() : 987654321;

		if (max > min)
		{
			max_heap.pop();
			min_heap.pop();
			
			max_heap.push(min);
			min_heap.push(max);
		}

		// 3. 중간값 출력
		printf("%d\n", max_heap.top());
	}

	return 0;
}
#endif