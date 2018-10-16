typedef int ElemType;

# include "../Headers/CommonHeader.h"

// 2.10 Delete k elems form the elem i in the list.
Status DeleteK (SqList &a, int i, int k) {
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
Status InsertToOrderedList (SqList &a, int x) {
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

// 2.12
enum judgement {
    BIGGER, SMALLER, EQUAL
};

judgement JudgeTheLists (SqList &a, SqList &b) {
    int limitation = a.length > b.length ? b.length : a.length;
    for (int i = 0; i < limitation; i++) {
        if (a.elem[i] == b.elem[i]) continue;
        else {
            if (a.elem[i] > b.elem[i]) return BIGGER;
            else return SMALLER;
        }
    }
    return EQUAL;
}

// 2.13
LinkList LOCATE (LNode &L, int X) {
    if (X == 0) return &L;
    else return LOCATE(*L.next, X - 1);
}

// 2.14
LinkList LENGTH (LNode &L) {
    if (L.next == NULL) return 0;
    else return 1 + LENGTH(*L.next);
}

// 2.15
Status LinkListCat (LinkList &a, LinkList &b, int alength, int blength, LinkList &c) {
    LinkList firstP;
    LinkList lastP;
    if (alength > blength) {
        firstP = b;
        lastP = a;
    } else {
        firstP = a;
        lastP = b;
    }
    c = firstP;
    while (firstP -> next != NULL) firstP = firstP -> next;
    firstP -> next = lastP -> next -> next;
    return OK;
}

// 2.16
Status DeleteAndInsertSub (LinkList la, LinkList lb, int i, int j, int len) {
    if (i < 0 || j < 0 || len < 0) return INFEASIBLE;
    LinkList p = la;
    int k = 1;
    while (k <= i) {
        p = p -> next;
        k++;
    }
    LinkList q = p;
    k = 1;
    while (k <= len) {
        q = q -> next;
        k++;
    }
    LinkList s = lb;
    k = 1;
    while (k < j - 1) {
        s = s -> next;
        k++;
    }
    q -> next = s -> next;
    s -> next = p;
    return OK;
}

// 2.17 含头结点
void INSERT (LinkList L, int i, LNode b) {
    if (i == 0) {
        b.next = L -> next;
        L -> next = &b;
    } 
    else {
        INSERT (L -> next, i-1, b);
    }
}

// 2.18 含头结点
void DELETE (LinkList L, int i) {
    // 因为链表单向传递，所以删除首元素时得提前一位
    if (i == 1) {
        L = L -> next;
    }
    else {
        DELETE (L -> next, i-1);
    }
}

// 2.19 
Status DeleteElement(LinkList L, ElemType mink, ElemType maxk) {
    if (L == NULL)
        return OK;
    LinkList* tmp;
    while (L -> data < mink) {
        L = L -> next;
        if (L == NULL) {
            break;
        }
    }
    tmp = &L;
    LinkList token;
    while (L -> data > mink && L -> data < maxk) {
        token = L;
        L = L -> next;
        free(token);
        if (L == NULL) {
            break;
        }
    }
    *tmp = L; 
}

int main () {
  printf("It seems all right!\n");
}

