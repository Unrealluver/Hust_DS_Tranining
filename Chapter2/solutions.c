typedef int ElemType;

# include "../Headers/CommonHeader.h"

// 2.10 Delete k elems form the elem i in the list.
Status DeleteK(SqList &a, int i, int k) {
  if (i < 1 || k < 0 || i + k > a.length)
    return INFEASIBLE;
  else {
    for (int count = 0; count < k; count++) {
      for (int j = a.length; j > j - 1; j--)
	a.elem[j - 1] = a.elem[j];
      a.length--;
    }
  }
}

int main () {
  printf("hello");
}

