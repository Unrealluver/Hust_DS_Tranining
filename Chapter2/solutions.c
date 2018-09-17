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

// 2.11 Insert the element x to the ordered(from small to big) list.
Status InsertToOrderedList(SqList &a, int x) {
    if (a.length + 1 > a.listsize) {
        ElemType *newBase = (ElemType *)realloc(a.elem,
                                      (a.listsize + LISTINCREMENT) * sizeof (ElemType));
        if (!newBase) return OVERFLOW;
        a.elem = newBase;
        a.listsize += LISTINCREMENT;
    }
    for (int i = 0; i < a.length - 1; i++) {
        if ((a.elem[i] < x && a.elem[i+1] > x) || (i == 0 && a.elem[i] > x) || (i == a.length - 1 && a.elem[i] < x)) {
            for (int j = a.length; j > i + 1; j--)
                a.elem[j] = a.elem[j-1];
            a.elem[i+1] = x;
            a.length++;
            return OK;
        }
    }
}

int main () {
  printf("hello");
}

