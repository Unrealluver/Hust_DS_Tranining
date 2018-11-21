#include <stdio.h>

void addColor(int *colorP, int map[][7], int nowP) {
	// 终止条件检测
	if (colorP[6] == 0) {
		// 颜色遍历
		for (int color = 1; color <= 4; color++) {
			// 设置颜色循环continue的flag
			int flag = 0;
			// 检查邻接矩阵中的邻居是否撞色
			for (int i = 0; i < 7; i++) {
				if (map[nowP][i] == 1 && color == colorP[i]) {
					flag = 1;
					break;
				}
			}
			// 撞色后continue
			if (flag) 
				continue;
			// 无撞色后确定着色
			colorP[nowP] = color;
			// 递归
			addColor(colorP, map, nowP+1);
			// 复位已填充的颜色
			colorP[nowP] = 0;
		}
	}
	else {
		// 遍历色彩数组并打印
		for (int i = 0; i < 7; i++) {
			printf("%d ", colorP[i]);
		}
		printf("\n");
	}
}

int* initStack() {
	static int s[100] = {0};
	return s;
}

int push(int *stack, int top, int x) {
	stack[top] = x;
	return ++top;
}

int pop(int *stack, int top) {
	stack[--top] = 0;
	return top;
}

void addColorStack(int *stack, int map[][7], int top) {
	// 终止条件检测
	if (top < 7) {
		// 颜色遍历
		for (int color = 1; color <= 4; color++) {
			// 压栈
			top = push(stack, top, color);
			// 设置颜色循环continue的flag
			int flag = 0;
			// 检查邻接矩阵中的邻居是否撞色
			for (int i = 0; i < 7; i++) {
				if (map[top - 1][i] == 1 && color == stack[i]) {
					flag = 1;
					break;
				}
			}
			// 撞色后弹栈continue
			if (flag) {
				top = pop(stack, top);
				continue;
			}
			// 递归
			addColorStack(stack, map, top);
			// 复位
			top = pop(stack, top);
		}
	}
	else {
		// 遍历色彩数组并打印
		for (int i = 0; i < 7; i++) {
			printf("%d ", stack[i]);
		}
		printf("\n");
	}
}


int main() {
	// 在这里做栈和递归填色数组的初始化工作
	int *stack = initStack();
	int color2[7] = {0};
	// 在这里初始化7 x 7的地图数组
	int map[7][7] = {0,1,0,1,1,0,0,1,0,1,0,1,1,1,0,1,0,1,0,0,1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,0,1,0,1,0,0,1,0,1,1,1,0,1,0,};
	// 输出地图样例
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	// 输出栈调用结果
	printf("\n\n");
	printf("This is the result of stack method:\n");
	addColorStack(stack, map, 0);
	// 输出递归调用结果
	printf("\n\n");
	printf("This is the result of recursive method:\n");
	addColor(color2, map, 0);

	getchar();
	return 0;
}