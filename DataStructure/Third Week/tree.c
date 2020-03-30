/*
解题思路：
首先要构造一个结构来存储输入的数据。
在输入数据的时候，注意输入的格式问题，特别是对于字符的输入，和普通的整形数字输入并不相同 scanf(" %c %c", &&);
输入的前面加一个空格来规避输入时的回车问题，或者用一个getchar()来读取回车字符
判断是否同构：(讨论情况)
1. 是否为空 (都空，只有一个空)
2. 若左子树都空，看右子树；右子树空同理
3. 若atree左子树空右子树不空，btree右子树空左子树不空，则看atree右子树 btree左子树
4. 若atree右子树空左子树不空，btree左子树空右子树不空，则看atree左子树 btree右子树
5. 剩下的情况则是两边子树都有：
    1. atree左子树与btree右子树元素相同，即没有交换，对比atree左子树和btree左子树，atree右子树和btree右子树
    2. atree左子树与btree右子树元素不同，即发生交换，对比atree左子树和btree右子树，atree右子树和btree左子树
*/
#include <malloc.h>
#include <stdio.h>

#define Null -1
struct tree
{
    char letter[10];
    int left_right_node[2][10];
};

typedef struct tree *TreeNode;

int BuildTree(TreeNode tree);
int Isomorphism(TreeNode atree, TreeNode btree, int n1, int n2);

int main()
{
    int N1, N2, res;
    TreeNode ATree, BTree;

    ATree = (TreeNode)malloc(sizeof(struct tree));
    N1 = BuildTree(ATree);

    BTree = (TreeNode)malloc(sizeof(struct tree));
    N2 = BuildTree(BTree);

    res = Isomorphism(ATree, BTree, N1, N2);

    printf("\n%d %d\n", N1, N2);

    if (res)
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}

int BuildTree(TreeNode tree)
{
    int N, i, check[11] = {0};
    char letter, left_node, right_node;

    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf(" %c %c %c", &letter, &left_node, &right_node);
        //getchar();
        tree->letter[i] = letter;
        if (left_node == '-')
            tree->left_right_node[0][i] = Null;
        else
        {
            tree->left_right_node[0][i] = left_node - '0';
            check[left_node - '0'] = 1;
        }

        if (right_node == '-')
            tree->left_right_node[1][i] = Null;
        else
        {
            tree->left_right_node[1][i] = right_node - '0';
            check[right_node - '0'] = 1;
        }
    }

    if (N == 0)
        return Null;

    for (i = 0; i < N; i++)
    {
        if (!check[i])
            break;
    }

    return i;
}

int Isomorphism(TreeNode atree, TreeNode btree, int n1, int n2)
{
    //皆为空树
    if (n1 == Null && n2 == Null)
        return 1;
    //有一颗树为非空
    if ((n1 == Null && n2 != Null) || (n1 != Null && n2 == Null))
        return 0;
    //树的结点不一致
    if (atree->letter[n1] != btree->letter[n2])
        return 0;
    //左子树空
    if (atree->left_right_node[0][n1] == Null && btree->left_right_node[0][n2] == Null)
        return Isomorphism(atree, btree, atree->left_right_node[1][n1], btree->left_right_node[1][n2]);
    //右子树空
    if (atree->left_right_node[1][n1] == Null && btree->left_right_node[1][n2] == Null)
        return Isomorphism(atree, btree, atree->left_right_node[0][n1], btree->left_right_node[0][n2]);
    //atree左子树空 btree右子树空
    if (atree->left_right_node[0][n1] == Null && btree->left_right_node[1][n2] == Null)
        return Isomorphism(atree, btree, atree->left_right_node[1][n1], btree->left_right_node[0][n2]);
    if (atree->left_right_node[1][n1] == Null && btree->left_right_node[0][n2] == Null)
        return Isomorphism(atree, btree, atree->left_right_node[0][n1], btree->left_right_node[1][n2]);
    //判断左右子树 只要左子树不相同，则一定发生了左右子树交换的情况
    if ((atree->left_right_node[1][n1] != Null && btree->left_right_node[1][n1] != Null) && (atree->letter[atree->left_right_node[0][n1]] == btree->letter[btree->left_right_node[0][n2]]))
    {
        return ((Isomorphism(atree, btree, atree->left_right_node[0][n1], btree->left_right_node[0][n2])) && (Isomorphism(atree, btree, atree->left_right_node[1][n1], btree->left_right_node[1][n2])));
    }
    //一边判断左子树一边判断右子树
    else
    {
        return ((Isomorphism(atree, btree, atree->left_right_node[0][n1], btree->left_right_node[1][n2])) && (Isomorphism(atree, btree, atree->left_right_node[1][n1], btree->left_right_node[0][n2])));
    }
}