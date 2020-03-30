/*
解题思路：
按题意首先读入两个链表，按要求实现多项式的加法和乘法
难点：创建一个链表，如何添加链表的元素，Attach
加法实现：类似插入排序，若遇到合并同类相消的项，跳过
乘法实现：先用P1的第一项和P2相乘获得一个多项式，随后遍历剩下的t1和t2，
将乘法结果插入到原本的多项式中。
熟悉链表操作
*/

#include <stdio.h>
#include <malloc.h>

//定义了一个结构体
struct PolyNode
{
	int coef;
	int expon;
	struct PolyNode *link;
};

//定义了一个结构体指针，指向这个结构体
typedef struct PolyNode *Polynomial;

Polynomial ReadPoly();
Polynomial Attach(int coef, int expon, Polynomial* pRear);
Polynomial AddTwoList(Polynomial P1, Polynomial P2);
Polynomial MulTwoList(Polynomial P1, Polynomial P2);
void PutPoly(Polynomial P);

int main()
{
	int i, N1, N2, c, e;
	Polynomial P1, P2, Add, Mul, tmp;

	
	P1 = ReadPoly();
	P2 = ReadPoly();
	Mul = MulTwoList(P1, P2);
	PutPoly(Mul);
	printf("\n");
	Add = AddTwoList(P1, P2);
	PutPoly(Add);
	
	return 0;
}

Polynomial ReadPoly()
{
	int i, c, e, N;
	Polynomial P, rear, t;
	
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	if (P == NULL) return 0;
	P->link = NULL;
	rear = P;

	scanf_s("%d", &N);
	for (i = 0; i < N; i++)
	{
		scanf_s("%d %d", &c, &e);
		Attach(c, e, &rear);
	}

	t = P;
	P = P->link;
	free(t);

	return P;
}

//pRear是指向指针的指针
Polynomial Attach(int coef, int expon, Polynomial *pRear)
{
	Polynomial tmp;

	tmp = (Polynomial)malloc(sizeof(struct PolyNode));
	if (tmp == NULL) return 0;
	tmp->coef = coef;
	tmp->expon = expon;
	tmp->link = NULL;
	(*pRear)->link = tmp;
	(*pRear) = tmp;
}

void PutPoly(Polynomial P)
{
	int flag = 0;
	
	if (!P)
	{
		printf("0 0");
		return 0;
	}

	while (P)
	{
		if (!flag)
			flag = 1;
		else if (flag == 1)
			printf(" ");
		printf("%d %d", P->coef, P->expon);
		P = P->link;
	}
}

Polynomial AddTwoList(Polynomial P1, Polynomial P2)
{
	Polynomial P1_index, P2_index, rear, front, tmp;

	P1_index = P1;
	P2_index = P2;
	front = (Polynomial)malloc(sizeof(struct PolyNode));
	rear = front;
	if (rear == NULL || front == NULL)return 0;
	
	while (P1_index && P2_index)
	{
		if (P1_index->expon > P2_index->expon)
		{
			Attach(P1_index->coef, P1_index->expon, &rear);
			P1_index = P1_index->link;
		}
		else if (P2_index->expon > P1_index->expon)
		{
			Attach(P2_index->coef, P2_index->expon, &rear);
			P2_index = P2_index->link;
		}
		else if (P2_index->expon == P1_index->expon)
		{
			if (P1_index->coef + P2_index->coef != 0)
			{
				Attach(P1_index->coef + P2_index->coef, P1_index->expon, &rear);
			}
			P1_index = P1_index->link;
			P2_index = P2_index->link;
		}
	}
	for (; P1_index; P1_index = P1_index->link)
		Attach(P1_index->coef, P1_index->expon, &rear);
	for (; P2_index; P2_index = P2_index->link)
		Attach(P2_index->coef, P2_index->expon, &rear);

	rear->link = NULL;
	tmp = front;
	front = front->link;
	free(tmp);

	return front;
}

Polynomial MulTwoList(Polynomial P1, Polynomial P2)
{
	Polynomial t1, t2, Mul, rear, tmp;
	int c, e;
	
	if (P1 == NULL || P2 == NULL)return NULL;

	t1 = P1; t2 = P2;
	Mul = (Polynomial)malloc(sizeof(struct PolyNode));
	if (Mul == NULL)return 0;
	Mul->link = NULL;
	rear = Mul;

	while (t2)
	{
		Attach(t1->coef*t2->coef, t1->expon+t2->expon, &rear);
		t2 = t2->link; 
	}
	t1 = t1->link;
	while (t1)
	{
		t2 = P2;
		rear = Mul;//回到最开始的位置
		while (t2)
		{
			c = t1->coef * t2->coef;
			e = t1->expon + t2->expon;

			while (rear->link && rear->link->expon > e)
				rear = rear->link;
			if (rear->link && rear->link->expon == e)
			{
				if (rear->link->coef + c != 0)
					rear->link->coef += c;
				else
				{
					tmp = rear->link;
					rear->link = tmp->link;
					free(tmp);
				}
			}
			else
			{
				tmp = (Polynomial)malloc(sizeof(struct PolyNode));
				if (tmp == NULL)return 0;
				tmp->coef = c; tmp->expon = e; 
				tmp->link = rear->link;
				rear->link = tmp; rear = rear->link;
			}
			t2 = t2->link;
		}
		t1 = t1->link;
	}

	tmp = Mul;
	Mul = Mul->link;
	free(tmp);

	return Mul;
}
