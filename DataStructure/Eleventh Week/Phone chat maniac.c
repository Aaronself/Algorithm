#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#define MAXTABLESIZE 1000000

typedef char ElementType[12];
typedef struct CeilNode *Ceil;
struct CeilNode{
    ElementType PhoneNumber;
    Ceil Next;
    int count;
};

typedef struct HashTableNode *HashTable;
struct HashTableNode{
    int HashSize;
    Ceil Head;
};

int NextPrime(int N);
HashTable CreatHashTable(int TableSize);
void Insert(HashTable H, ElementType Key);
Ceil Find(HashTable H, ElementType Key);
void ScanAndOutput(HashTable H);
// void DeleteTable(HashTableNode H);

int main(){
    int N, i;
    ElementType Key;
    HashTable H;

    scanf("%d", &N);
    H = CreatHashTable(N * 2);
    for (i = 0; i < N; i++){
        scanf("%s", Key);
        Insert(H, Key);
        scanf("%s", Key);
        Insert(H, Key);
    }
    ScanAndOutput(H);

    return 0;
}

HashTable CreatHashTable(int TableSize){
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct HashTableNode));
    H->HashSize = NextPrime(TableSize);
    H->Head = (Ceil)malloc(sizeof(struct CeilNode) * H->HashSize);
    for (i = 0; i < H->HashSize; i++){
        H->Head[i].PhoneNumber[0] = '\0';
        H->Head[i].Next = NULL;
        H->Head[i].count = 0;
    }
    
    return H;
}

int NextPrime(int N){
    int i, p = (N % 2) ? N + 2 : N + 1;
    while(p <= MAXTABLESIZE){
        for (i = 2; i < (int)sqrt(p); i++)
            if(p % i == 0) break;

        if(i != (int)sqrt(p)) break;
        else p += 2;
    }
    return p;
}

void Insert(HashTable H, ElementType Key){
    int pos, num = Key[10] + Key[9] * 10 + Key[8] * 100 + Key[7] * 1000 + Key[6] * 10000;
    Ceil Node, p;

    p = Find(H, Key);
    if(!p){
        pos = num % H->HashSize;
        Node = (Ceil)malloc(sizeof(struct CeilNode));
        Node->count = 1;
        strcpy(Node->PhoneNumber, Key);
        Node->Next = H->Head[pos].Next;
        H->Head[pos].Next = Node;
    }
    else
        p->count++;
}

Ceil Find(HashTable H, ElementType Key){
    Ceil p;
    int pos, num = Key[10] + Key[9] * 10 + Key[8] * 100 + Key[7] * 1000 + Key[6] * 10000;;

    pos = num % H->HashSize;
    p = H->Head[pos].Next;
    while(p && strcmp(p->PhoneNumber, Key))
        p = p->Next;
    return p;
}

void ScanAndOutput(HashTable H){
    int i;
    int MaxCnt = 0, PCnt = 0;
    Ceil ptr;
    ElementType MinPhone;

    for (i = 0; i < H->HashSize; i++){
        ptr = H->Head[i].Next;
        while(ptr){
            if(ptr->count > MaxCnt){
                MaxCnt = ptr->count;
                strcpy(MinPhone, ptr->PhoneNumber);
                PCnt = 1;
            }
            else if(ptr->count == MaxCnt)
            {
                if(strcmp(MinPhone, ptr->PhoneNumber) > 0)
                    strcpy(MinPhone, ptr->PhoneNumber);
                PCnt++;
            }
            
            ptr = ptr->Next;
        }
    }

    if(PCnt == 1)
        printf("%s %d", MinPhone, MaxCnt);
    else if(PCnt > 1)  
        printf("%s %d %d", MinPhone, MaxCnt, PCnt);
}