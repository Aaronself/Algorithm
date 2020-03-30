#include <stdio.h>
#include <malloc.h>

typedef struct PolyList* Polynomial;
struct PolyList {
	int Addr;
	int num;
	int NextAddr;
	struct PolyList* next;
};

int N, Addr_F, K;

Polynomial Attach(int addr, int num, int next, Polynomial* pREAR);
Polynomial ChangeList(int addr, int N, Polynomial P1);
Polynomial ReverseList(Polynomial P, int N, int K);

int main()
{
	Polynomial P, P1, P2, rear, tmp;
	int i, Addr, num, NextAddr;

	//读取生成链表
	P = (Polynomial)malloc(sizeof(struct PolyList));
	if (!P)return 0;
	P->next = NULL;rear = P;
	scanf("%d %d %d", &Addr_F, &N, &K);
	for(i = 0; i < N; i++)
	{
		scanf("%d %d %d", &Addr, &num, &NextAddr);
		Attach(Addr, num, NextAddr, &rear);
	}
	//
	tmp = P;
	P = P->next;
	free(tmp);

	P1 = ChangeList(Addr_F, N, P);
	P2 = ReverseList(P1, N, K);

	while (P2)
	{
		if(P2->NextAddr >= 0)
			printf("%05d %d %05d", P2->Addr, P2->num, P2->NextAddr);
		else
			printf("%05d %d %d", P2->Addr, P2->num, P2->NextAddr);
		P2 = P2->next;
		if (P2)
			printf("\n");
	}

	return 0;
}

Polynomial Attach(int addr, int num, int nextaddr, Polynomial* pRear)
{
	Polynomial tmp;

	tmp = (Polynomial)malloc(sizeof(struct PolyList));
	if (tmp == NULL)return 0;
	tmp->Addr = addr;
	tmp->num = num;
	tmp->NextAddr = nextaddr;
	tmp->next = NULL;
	(*pRear)->next = tmp;
	(*pRear) = tmp;
}

Polynomial ChangeList(int addr, int N, Polynomial P1)
{
	int addr_index;
	Polynomial t, P, rear, tmp;

	if (!P1)return 0;
	t = P1;
	P = (Polynomial)malloc(sizeof(struct PolyList));
	if (P == NULL) return 0;
	P->next = NULL;
	rear = P;

	//找到链表头
	while (t)
	{
		if (addr != t->Addr)
			t = t->next;
		else
		{
			Attach(t->Addr, t->num, t->NextAddr, &rear);
			break;
		}
	}
    addr_index = rear->NextAddr;;
    while (addr_index != -1)
	{
		addr_index = rear->NextAddr;//要找寻的下一个地址
		t = P1;
		while (t)//遍历P1
		{
			if (addr_index != t->Addr)
				t = t->next;
			else
			{
				Attach(addr_index, t->num, t->NextAddr, &rear);
                break;
			}
		}
    }

	tmp = P;
	P = P->next;
	free(tmp);

	return P;
}

Polynomial ReverseList(Polynomial P, int N, int K)
{
	int res, res_index, j, j_index, k_num;
	Polynomial t;
	Polynomial P2, rear, tmp;

	if (!P)return 0;
	//代表翻转次数
	res = N / K; res_index = res;

	P2 = (Polynomial)malloc(sizeof(struct PolyList));
	if (!P2) return 0;
	P2->next = NULL;
	rear = P2;

	
	//完成翻转操作
	while (res_index)
	{
		//j j_index是去排列后的链表中寻找待插入的数
		j = K - 1 + (res - res_index) * K;//当前翻转次序中要插入的第一项
		k_num = K;
		j_index = j;
		while (k_num)
		{
			t = P;
			j_index = j + k_num - K;
			while (j_index)
			{
				t = t->next;
				j_index--;
			}
			Attach(t->Addr, t->num, t->NextAddr, &rear);
			k_num--;
		}
		res_index--;
	}
	//复制后续
	t = P;
	j_index = res * K;
	while (j_index)
	{
		t = t->next;
		j_index--;
	}
	while (t)
	{
		Attach(t->Addr, t->num, t->NextAddr, &rear);
		t = t->next;
	}

	tmp = P2;
	P2 = P2->next;
	free(tmp);
	
	//修改翻转和复制中间的nextaddr
	t = P2;
	if (!t) return 0;

	rear = P2;
	while (t->next)
	{
		rear->NextAddr = t->next->Addr;
		rear = t->next;
		t = t->next;
	}
	rear->NextAddr = -1;

	return P2;
}