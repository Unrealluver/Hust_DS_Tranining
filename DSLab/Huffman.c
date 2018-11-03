#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int weight;
	int parent, lchild, rchild;
	int isSelect;
}HTNode, * HuffmanTree;

// 霍夫曼树编码表
typedef char * * HuffmanCode;

int * BucketSort(char * list) {
	// 静态数组默认初始为0
	static int bucket[128];
	int i;
	do {
	    bucket[(int) * list]++;
	} while (* (++list) != '\0');

    printf("%s", "bucket is going to show");
	for (i = 0; i < 128; i++) {
        printf("%d", i);
	    if (bucket[i] != 0)
            printf("%c %d\n", i, bucket[i]);	
	}

    printf("%s", "bucket is ready");
	return bucket;
}

int InitHT(int * bucket, HuffmanTree * HT, int * n) {
	int i, treeLen;
	int num = 0;
	for (i = 0; i < 128; i++)
		if (bucket[i] != 0)
			num++;
    * n = num;
	treeLen = 128 + num;
	// 多申请了一个位置
	HT = (HuffmanTree)malloc((128 + num) * sizeof(HTNode));
	return treeLen;
}

void Select(HuffmanTree HT, int limit,int * s1,int * s2) {
	int i;
	* s1 = * s2 = -1;
	for (i = 1; i <= limit; i++) {
		if (* s1 == -1 && HT[i].weight != 0 && HT[i].isSelect == 0)
			* s1 = i;
		if (HT[* s1].weight > HT[i].weight)
			* s1 = i;
	}
	for (i = 1; i <= limit; i++) {
		if (i == * s1)
			continue;
		if (* s2 == -1 && HT[i].weight != 0 && HT[i].isSelect == 0)
			* s2 = i;
		if (HT[* s1].weight > HT[i].weight)
			* s2 = i;
	}
}
// n取128
void HuffmanCoding(HuffmanTree * HT, HuffmanCode * HC, int * bucket, int * n) {
	HuffmanTree treeP;
	int i, treeLen, s1, s2;
	char * cd;
	int start, c, f;
	char * inputList = "a\0";
	bucket = BucketSort(inputList);
    printf("%s", "bucket is ready");
	treeLen = InitHT(bucket, HT, n);
    
	// 0号单元未使用, 录入n个字符的出现评率进HT
	for (treeP = HT + 1, i = 1; i <= n; ++i, ++treeP, ++bucket)
		* treeP = (HTNode) {* bucket, 0, 0, 0, 0};
	// 将空数据录入后面的合成节点
	for (; i <= treeLen; ++i, ++bucket)
		* treeP = (HTNode) {0, 0, 0, 0, 0};
	// 生成树
	for (i = n + 1; i <= treeLen; ++i) {
		Select(HT, i - 1, &s1, &s2);
		HT[s1] -> parent = i;
		HT[s2] -> parent = i;
		HT[i] -> lchild = s1;
		HT[i] -> rchild = s2;
		HT[i] -> weight = HT[s1] -> weight + HT[s2] -> weight;
	}
    
    for (i = 1; i <= 128; ++i) {
        printf("%d, %c", HT[i] -> weight, (char) i);
    }

	// 从叶子到根求每个字符的霍夫曼编码
	HC = (HuffmanCode)malloc((* n + 1) * sizeof (char *));
	cd = (char *)malloc (* n * sizeof (char));
	cd[* n - 1] = "\0";
	for (i = 1; i <= * n; i++) {
		start = n - 1;
		for (c = i, f = HT[i] -> parent; f != 0; c = f, f = HT[f] -> parent) 
			cd[--start] = HT[f] -> lchild == c ? "0" : "1";
		HC[i] = (char *)malloc((* n - start) * sizeof (char));
		strcpy(HC[i], cd + start);
	}
	free(cd);
}	

int main() {
    HuffmanTree * HT;
    HuffmanCode * HC;
    int * bucket;
    int * n = (int) malloc (sizeof (int));
    HuffmanCoding(&HT, &HC, &bucket, &n);
    free(n);
}
