#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

#define SIZE1 15  // 迷宫的长度
#define SIZE2 10  // 迷宫的宽度
#define stacksize 1008

typedef struct {
    int** trait;
    int** visit;
} Graph;

typedef struct position {
    int x;
    int y;
} position;

typedef struct Stack {
    int tail;
    position* s;
} Stack;

Stack* InitStack(void) {
    Stack* a = (Stack*)malloc(sizeof(Stack));
    a->tail = 0;
    a->s = (position*)malloc(sizeof(position) * stacksize);
    return a;
}  // 初始化栈

Graph* InitGraph(void) {
    Graph* a = (Graph*)malloc(sizeof(Graph));
    a->trait = (int**)malloc(sizeof(int*) * SIZE1);
    a->visit = (int**)malloc(sizeof(int*) * SIZE1);
    for (int i = 0; i < SIZE1; i++) {
        a->trait[i] = (int*)malloc(sizeof(int) * SIZE2);
        a->visit[i] = (int*)malloc(sizeof(int) * SIZE2);
    }
    for (int i = 0; i < SIZE1; i++) {
        for (int j = 0; j < SIZE2; j++) {
            a->trait[i][j] = 0;
            a->visit[i][j] = 0;
        }
    }
    return a;
}  // 初始化地图

void creatmap(Graph* a) {
    for (int i = 0; i < SIZE1; i++) {
        for (int j = 0; j < SIZE2; j++) {
            a->trait[i][j] = 1;
        }
    }
}  // 生成地图

void InStack(Stack* a, position x) {
    a->s[a->tail] = x;
    a->tail++;
}  // 入栈

position OutStack(Stack* a) {
    a->tail--;
    return a->s[a->tail];
}  // 出栈

position CreatPos(int x, int y) {
    position a;
    a.x = x;
    a.y = y;
    return a;
}

void DFS(Graph* m, position a, position b, Stack* result) {
    Stack* helpstack = InitStack();
    InStack(helpstack, a);  // 入栈
    m->visit[a.x][a.y] = 1;

    while (helpstack->tail != 0) {
        position c = OutStack(helpstack);
        InStack(result, c);

        if (c.x == b.x && c.y == b.y) {
            free(helpstack->s);
            free(helpstack);
            return;
        }

        int x0 = c.x;
        int y0 = c.y;
        int found = 0;

        // 南边可以走
        if (x0 + 1 < SIZE1 && m->trait[x0 + 1][y0] == 1 && m->visit[x0 + 1][y0] == 0) {
            m->visit[x0 + 1][y0] = 1;
            position d = CreatPos(x0 + 1, y0);
            InStack(helpstack, d);
            found = 1;
        }
        // 北边可以走
        if (x0 - 1 >= 0 && m->trait[x0 - 1][y0] == 1 && m->visit[x0 - 1][y0] == 0) {
            m->visit[x0 - 1][y0] = 1;
            position d = CreatPos(x0 - 1, y0);
            InStack(helpstack, d);
            found = 1;
        }
        // 西边可以走
        if (y0 - 1 >= 0 && m->trait[x0][y0 - 1] == 1 && m->visit[x0][y0 - 1] == 0) {
            m->visit[x0][y0 - 1] = 1;
            position d = CreatPos(x0, y0 - 1);
            InStack(helpstack, d);
            found = 1;
        }
        // 东边可以走
        if (y0 + 1 < SIZE2 && m->trait[x0][y0 + 1] == 1 && m->visit[x0][y0 + 1] == 0) {
            m->visit[x0][y0 + 1] = 1;
            position d = CreatPos(x0, y0 + 1);
            InStack(helpstack, d);
            found = 1;
        }

        if (!found) {
            OutStack(result);

        }
    }
    free(helpstack->s);
    free(helpstack);
}  // 深度优先

void PrintMap(Stack* result, Graph* map) {
    for (int i = 0; i < result->tail; i++) {
        map->trait[result->s[i].x][result->s[i].y] = 2;
    }
    for (int i = 0; i < SIZE1; i++) {
        for (int j = 0; j < SIZE2; j++) {
            if (map->trait[i][j] == 0)
                printf("q");
            else if (map->trait[i][j] == 1)
                printf("A");
            else if (map->trait[i][j] == 2)
                printf("l");
        }
        printf("\n");
    }
}

int main() {
    Graph* map = InitGraph();
    creatmap(map);
    Stack* result = InitStack();
    position A = CreatPos(1, 0);
    position B = CreatPos(9, 1);

    DFS(map, A, B, result);

    PrintMap(result, map);

    // 释放内存
    for (int i = 0; i < SIZE1; i++) {
        free(map->trait[i]);
        free(map->visit[i]);
    }
    free(map->trait);
    free(map->visit);
    free(map);
    free(result->s);
    free(result);

    return 0;
}