/*
prac7.c
이름: 이세진
학번: 20161619

*/
#include <stdio.h>
#include <stdlib.h>
#define N 10

typedef struct node NODE;
struct node {
	int data;
	NODE *link;
};

void insert(NODE **s, int d);
void printList(NODE*);

int erase(NODE **s, int d, int);
int search(NODE* s, int d, int);
int main()
{
	int A[N] = { 10, 6, 2, 9, 12, 1, 7, 8 , 13, 5};
	NODE* start;
	int i, data, pos;
	start = NULL;
	for (i = 0; i < N; i++)
	{
		insert(&start, A[i]);
		printList(start);
	}

	printf("Enter data to search : ");
	scanf("%d", &data);
	pos = search(start, data, N);

	if (pos != -1)
	{
		printf("There is %d in the position %d \n", data, pos+1);
	}
	else
	{
		printf("There is no 3 in the list\n");
	}
	printf("\n \n");

	printf("Enter data to delete : ");
	scanf("%d", &data);
	if (pos = erase(&start, data, N) != -1)
	{
		printf("%d deleted !\n\n", data);
		printList(start);
	}
	else
	{
		printf("Cannot delete!! There is no %d in the list.\n\n", data);
	}
	return 0;
	// 변수 선언 및 초기화

	// 오름차순으로 연결리스트 생성하기
	// 노드가 추가될 때마다 연결리스트 출력하기

	// 검색할 데이터 입력받기
	// 검색할 데이터가 없는 경우와 있는 경우 나누어 출력하기

	// 삭제할 데이터 입력받기
	// 삭제할 데이터가 없으면 아무 일도 하지 않는다.
	// 삭제할 데이터가 있으면 연결리스트에서 삭제 후 변경된
	// 연결리스트를 출력한다 (printList 함수)

	return 0;
}

int erase(NODE **s, int d, int length)
{
	NODE *temp, *next, *prev;
	int i;
	int pos = search(*s, d, length);
	if (pos == -1)
		return -1;

	temp = *s;
	if (pos == 0)
	{
		*s = temp->link;
		free(temp);
		return 0;

	}
	for (i = 0; i <pos; i++)
	{
		prev = temp;
		temp = temp->link;
	}

	prev->link = temp->link;
	free(temp);

}
int search(NODE *s, int d, int length)
{
	NODE* temp;
	int count = 0;
	for (temp = s; temp; temp = temp->link)
	{
		if (temp->data == d)
		{
			return count;
		}

		count++;

	}
	if (count == length)
	{
		return -1;
	}
	return count;
}


// 연결 리스트 출력하기
void insert(NODE **s, int d)
{
	NODE * temp, *newNode, *prev;
	newNode = (NODE*)malloc(sizeof(NODE));
	newNode->data = d;
	newNode->link = NULL;
	int flag = 1;
	if (*s == NULL)
	{
		*s = newNode;
	}
	else if (((*s)->data > d))
	{
		newNode->link = (*s);
		(*s) = newNode;
	}
	else
	{
		temp = *s;
		while (temp->link != NULL)
		{
			prev = temp;
			temp = temp->link;
			if (temp->data > d)
			{
				prev->link = newNode;
				newNode->link = temp;
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			for (temp = *s; temp->link != NULL; temp = temp->link);

			temp->link = newNode;
		}
	}


}
void printList(NODE *s)
{
	for (; s; s = s->link)
		printf("%d ", s->data);
	printf("\n-----------------------\n");
}
