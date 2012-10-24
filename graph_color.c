#include <stdio.h>

#define VERTEX_NUM 4
int color[VERTEX_NUM] = {0};

/* if no collision then return 1 or 0 */
int check_collision(int (*graph)[VERTEX_NUM], int current_vertex)
{
    int i;
    for (i = 0; i < current_vertex; ++i){
        /* if they are ajcent and the colors are same then discard*/
        if (graph[current_vertex][i] == 1
            && color[current_vertex] == color[i]){
            return 0;
        }
    }
    return 1;
}

void mini_color(int (*graph)[VERTEX_NUM], int current_vertex)
{
    if (current_vertex == VERTEX_NUM){
        return;
    }
    int i;
    for (i = 0; i < VERTEX_NUM; ++i){
        color[current_vertex] = i;
        if (check_collision(graph, current_vertex)){
            mini_color(graph, current_vertex + 1);
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    /* graph matrix */
    int graph[VERTEX_NUM][VERTEX_NUM] = {
        {0, 1, 1, 1}, {1, 0, 1, 0},
        {1, 1, 0, 1}, {1, 0, 1, 0}};

    mini_color(graph, 0);
    int i;
    for (i = 0; i < VERTEX_NUM; ++i){
        printf ("%d%c", color[i],
                i == VERTEX_NUM - 1? '\n':' ');
    }
    return 0;
}
