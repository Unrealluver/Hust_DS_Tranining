# include <stdio.h>

# define TRUE 1
# define FALSE 0
# define OK 1
# define ERROR 0
# define INFEASIBLE -1
# define OVERFLOW -2

# define LIST_INIT_SIZE 100;
# define LISTINCREMENT 10;

typedef int Status;

typedef struct {
  ElemType *elem;
  int length;
  int listsize;
} SqList;

typedef struct LNode {
  ElemType data;
  struct LNode *next;
} LNode, *LinkList;

