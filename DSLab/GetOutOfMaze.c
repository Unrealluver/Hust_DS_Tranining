
#include<stdio.h>
#include<stdlib.h>
#define MaxStackSize 72
#define m 9
#define n 8


// 初始化
int maze[m][n] = {
        {1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 0},
        {1, 0, 0, 0, 0, 1, 1, 0},
        {0, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 1}
};
// 用于堆栈求通路
int mazee[m][n] = {
        {1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 0},
        {1, 0, 0, 0, 0, 1, 1, 0},
        {0, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 1}
};


/**
 * 初始化相邻路口的相对偏移量数组，
 * 表示当前路口相邻的四个方向，
 * 按顺时针由右侧开始
 */

int move[4][2] = {{0,  1},
                  {1,  0},
                  {0,  -1},
                  {-1, 0}};


// 两个参数为入口坐标
int MAZE(int x, int y) {
    // 跳出越界路口
    if (x < 0 || x > m || y < 0 || y > n) {
        return 0;
    }
    int a, b;
    int tag = 0;
    // 迷宫出口
    if (x == 8 && y == 7)
        return 1;
    // 尝试相邻的4个路口
    for (int i = 0; i < 4; i++) {
        a = x + move[i][0];
        b = y + move[i][1];

        //如果路口通顺且没搜索过则进入该路口，否则什么都不做
        if (maze[a][b] == 1) {
            //(a,b)上的值改成2表示走过的路
            maze[a][b] = 2;
            //进入路口
            tag = MAZE(a, b);
            //判断是否找到出口用于输出路径
            if (tag) {

                printf("(%d,%d)←", a, b);
                return 1;
            }
        }
    }
    return 0;
}


/*
使用堆栈求迷宫通路
*/

// 路口数据化
typedef struct {
    // x,y表示路口位置
    int x;
    int y;
    // 表示路口状态，1表示通顺路口，2表示搜索过的，0表示障碍路口
    int condition;
} Stack;

// 栈用来储存从入口到当前路口的路径
typedef struct {
    Stack stack[MaxStackSize];
    int top;
} SeqStack;


// 堆栈初始化
void StackInitiate(SeqStack *s) {
    s->top = 0;
}


// 判断堆栈是否为空
int StackNotEmpty(SeqStack s) {
    if (s.top <= 0)return 0;
    else return 1;
}


// 入栈，成功返回1，否则返回0
int StackPush(SeqStack *s, Stack x) {
    if (s->top >= MaxStackSize) {
        printf("stack over flow!\n");
        return 0;
    } else {
        s->stack[s->top] = x;
        s->top++;
        return 1;
    }
}


// 取得栈顶元素,成功返回1，否则返回0
int StackTop(SeqStack s, Stack *x) {
    if (s.top <= 0) {
        printf("stack is empty!\n");
        return 0;
    } else {
        *x = s.stack[s.top - 1];
        return 1;
    }
}


// 出栈，成功返回1，否则返回0
int StackPop(SeqStack *s, Stack *x) {


    if (s->top <= 0) {
        printf("stack is empty, no elem was popped!\n");
        return 0;
    } else {
        s->top--;
        *x = s->stack[s->top];
        return 1;
    }
}


void getPass() {

    SeqStack s;
    //堆栈初始化
    StackInitiate(&s);
    Stack ss;
    //a,b表示当前搜索的迷宫位置，当前是入口
    int a = 0, b = 0;

    ss.x = a;
    ss.y = b;
    ss.condition = mazee[a][b] = 2;
    StackPush(&s, ss);

    //将堆栈为空设置成停止循环的条件，也意味着没有通路；
    while (StackNotEmpty(s)) {
        //获取当前位置
        StackTop(s, &ss);

        //下个路口的探索
        for (int i = 0; i < 4; i++) {

            a = ss.x + move[i][0];
            b = ss.y + move[i][1];
            // 如果不越界，进入下一个方向
            if (a >= 0 && a < m && b >= 0 && b < n) {

                // 如果通顺,进入路口，入栈，否则什么都不做，搜索另一个方向
                if (mazee[a][b] == 1) {
                    mazee[a][b] = 2;
                    ss.condition = mazee[a][b];
                    ss.x = a;
                    ss.y = b;
                    StackPush(&s, ss);
                    break;

                }
            }
            if (i == 3) {
                // 但搜索到第四个方向且该方向的路口不通，出栈
                StackPop(&s, &ss);
            }
        }
        //迷宫出口
        //搜索到出口跳出
        if (a == 8 && b == 7)break;
    }


    if (!StackNotEmpty(s))printf("The maze has no way out\n");
    else {
        while (StackNotEmpty(s)) {
            StackPop(&s, &ss);
            printf("(%d,%d)←", ss.x, ss.y);
        }
    }
}


void main() {
    // 堆栈求迷宫通路
    printf("Get the way of stack method：\n");
    getPass();
    printf("\n\n\n\n");
    // 递归求所有通路，按一定方向顺序进行搜索能得到一条路径，反过来想的话，用不同方向顺序进行搜索能得到不同路径，除非只有一条通路
    // 调用MAZE,每调用依次必须对迷宫进行初始化
    printf("Get the way of recursive method：\n");
    MAZE(0, 0);
    // 迷宫入口
    printf("(0,0)←in\n");
}