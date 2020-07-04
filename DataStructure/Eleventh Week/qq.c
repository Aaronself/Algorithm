#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#define MAXTABLESIZE 1000000
typedef char ElementType;

typedef struct QNode *QList;
struct QNode{
    int username;
    char *password;
    int count;
    QList Next;
};

typedef struct HashTableNode *Hashtable;
struct HashTableNode{
    int HashSize;
    QList Heads;
};

Hashtable CreatHashTable(int N);
int NextPrime(int N);
int Hash(Hashtable H, int str);
void InsertQQNode(Hashtable H, char cmd, int Account, char *Password);
int SearchQQ(Hashtable H, char cmd, int Account, char *Password);

int main(){
    int i, N, QQAcount = 0;
    char cmd;
    char *password;
    Hashtable H;

    scanf("%d", &N);
    password = (char *)malloc(sizeof(char));
    H = CreatHashTable(N);
    for (i = 0; i < N; i++){
        scanf(" %c %d %s", &cmd, &QQAcount, password);
        if(cmd == 'L'){
            SearchQQ(H, cmd, QQAcount, password);
        }
        else if(cmd == 'N'){
            InsertQQNode(H, cmd, QQAcount, password);
        }
        if(i != N - 1)
            printf("\n");
    }

    return 0;
}

Hashtable CreatHashTable(int N){
    int i;
    Hashtable H;

    H = (Hashtable)malloc(sizeof(struct HashTableNode));
    H->HashSize = NextPrime(N);
    H->Heads = (QList)malloc(sizeof(struct QNode) * H->HashSize);
    for (i = 0; i < H->HashSize; i++){
        H->Heads[i].password = (char *)malloc(sizeof(char));
        H->Heads[i].username = 0;
        H->Heads[i].count = 0;
        H->Heads[i].Next = NULL;
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


int Hash(Hashtable H, int str){
    int hash = 0;

    hash = str % H->HashSize;
    return hash;
}

void InsertQQNode(Hashtable H, char cmd, int Account, char* Password){
    int pos;
    QList node;

    if(SearchQQ(H, cmd, Account, Password) == 0){
        pos = Hash(H, Account);
        node = (QList)malloc(sizeof(struct QNode));
        node->username = Account;
        node->password = (char *)malloc(sizeof(char));
        strcpy(node->password, Password);
        node->count = 1;
        H->Heads[pos].count = 1;
        node->Next = H->Heads[pos].Next;
        H->Heads[pos].Next = node;
        printf("New:OK");
    }
    else
        printf("ERROR: Exist");
}

/* return 0 not found        return 1 found */
int SearchQQ(Hashtable H, char cmd, int Account, char* Password){
    int pos = Hash(H, Account);
    QList ptr;

    if(H->Heads[pos].count == 0 && cmd == 'L'){
        printf("ERROR: Not Exist");
        return 0;
    }
    else {
        ptr = H->Heads[pos].Next;
        while(ptr){
            if(ptr->username == Account){
                if (strcmp(Password, ptr->password) == 0)
                {
                    if(cmd == 'L')
                        printf("Login: OK");
                    return 1;
                }
                else{
                    if(cmd == 'L')
                        printf("ERROR: Wrong PW");
                    return 1;
                }
            }
            else
                ptr = ptr->Next;
        }
        if(ptr == NULL && cmd == 'L'){
            printf("ERROR: Not Exist");
            return 0;
        }
    }

    return 0;
}