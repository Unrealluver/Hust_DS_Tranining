#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

// 霍夫曼树编码表
typedef char **HuffmanCode;

int *BucketSort(char *list) {
    // 静态数组默认初始为0
    static int bucket[128];
    int i;
    do {
        bucket[(int) *list]++;
    } while (*(++list) != '\0');
    return bucket;
}

int InitHT(int *bucket, HuffmanTree *HT, int *n) {
    int i, treeLen;
    int num = 0;
    for (i = 0; i < 128; i++)
        if (bucket[i] != 0)
            num++;
    *n = num;
    treeLen = 128 + num;

    /**
     * 多申请了一个位置 总结点数本应该为 2 * num - 1,
     * 此处num个结点已经包含在了128个节点之中,
     * 故我们倘若再加上num个结点就会多出来一个.
     */

    *HT = (HuffmanTree) malloc((treeLen) * sizeof(HTNode));
    return treeLen;
}

void Select(HuffmanTree HT, int limit, int *s1, int *s2) {
    int i;
    *s1 = *s2 = -1;
    for (i = 1; i <= limit; i++) {
        if (*s1 == -1 && HT[i].weight != 0 && HT[i].parent == 0)
            *s1 = i;
        if (HT[*s1].weight > HT[i].weight && HT[i].parent == 0 && HT[i].weight != 0)
            *s1 = i;
    }
    for (i = 1; i <= limit; i++) {
        if (i == *s1)
            continue;
        if (*s2 == -1 && HT[i].weight != 0 && HT[i].parent == 0)
            *s2 = i;
        if (HT[*s1].weight > HT[i].weight && HT[i].parent == 0 && HT[i].weight != 0)
            *s2 = i;
    }
}

// n取128
//void HuffmanCoding(HuffmanTree * HT, HuffmanCode * HC, int * bucket, int * n) {
void HuffmanCoding(char * inputList) {
    HuffmanTree HT;
    HuffmanCode HC;
    HuffmanTree tree;
    int *bucket;
    bucket = (int *) malloc(128 * sizeof(int));
    int n;

    int i, treeLen, s1, s2;
    char *cd;
    int start, c, f, hcCount;
    bucket = BucketSort(inputList);

    for (i = 0; i < 128; i++) {
        if (bucket[i] != 0)
            printf("%c is not empty, its weight is %d\n", i, bucket[i]);
    }

    printf("\n%s\n", "At this step bucket is ready");
    treeLen = InitHT(bucket, &HT, &n);

    /**
     * 因为第一位的结点是其它节点的默认结点
     * 所以此处我们也对其做初始化处理
     */
    tree = HT;
    tree->lchild = 0;
    tree->rchild = 0;
    tree->parent = 0;
    tree->weight = 0;
    tree++;

    // 0号单元未使用, 录入n个字符的出现频率进HT
    for (i = 0; i < 128; ++i, ++tree) {
        tree->lchild = 0;
        tree->rchild = 0;
        tree->parent = 0;
        tree->weight = bucket[i];
    }
    // 将空数据录入后面的合成节点
    for (; i < treeLen - 1; ++i) {
        tree->parent = 0;
        tree->rchild = 0;
        tree->lchild = 0;
        tree->weight = 0;
    }
    // 生成树
    /**
     * 此处因为之前闲置了第0个空间的缘故,
     * 此处我们实际填充了数据的单元为
     * 1-128, 故应该从128 + 1的位置填起
     * 直至treeLen - 1为止
     * 总单元数为n - 1,与我们预设相符.
     *
     * 最后一个结点需要我们手动设置,
     * 所以我们这里终止条件给的是 treeLen - 1;
     */
     printf("\nThe treenLen = %d\n", treeLen);
    for (i = 128 + 1; i < treeLen - 1; ++i) {
        Select(HT, i - 1, &s1, &s2);
        printf("\nThe answer of Select Function is %d and %d", s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }

    /**
     * 此处是尾端的结点的初始化,
     * 该工作由我们手动来完成.
     */

    HT[treeLen - 1].lchild = treeLen - 3;
    HT[treeLen - 1].rchild = treeLen - 2;
    HT[treeLen - 1].weight = HT[treeLen - 3].weight + HT[treeLen - 2].weight;
    HT[treeLen - 2].parent = HT[treeLen - 3].parent = treeLen - 1;

    printf("\n");
    for (i = 1; i < treeLen; ++i) {
        printf("Node %d is %c, weight: %d, parent: %d, lchild: %d, rchild: a%d\n",
                i, i-1, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
    }

    // 从叶子到根求每个字符的霍夫曼编码
    HC = (HuffmanCode) malloc((n + 1) * sizeof(char *));
//    cd = (char *) malloc(n * sizeof(char));
    /**
     * 因为malloc的空间使用时会出现sigment fault(原因不明)
     * 故此处替换为长度为n的token数组
     */
    char token[n];
    cd = token;
    cd[n - 1] = '\0';
    hcCount = 1;
    for (i = 1; i < treeLen; i++) {
        if (HT[i].weight == 0) {
            continue;
        }
        start = n - 1;
        for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
            cd[--start] = HT[f].lchild == c ? '0' : '1';
        HC[hcCount] = (char *) malloc((n - start) * sizeof(char));
        strcpy(HC[hcCount], cd + start);
        // 输出所有字符的编码
        if (i - 1 < 128)
            printf("%c's HuffmanCode is %s \n", i - 1, HC[hcCount]);
        // 霍夫曼编码的标识符自增
        ++hcCount;
    }
}

int main() {
    char inputList[100];
    printf("Please input your string that you want to encoding:\n");
    scanf("%s", inputList);
    HuffmanCoding(inputList);
}