#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "GRAPH_HEAD.h"

void test()
{
    /*Node n(2, 3);
    n.print();
    n.set_x_(10);
    n.set_y_(10);
    n.print();*/
    Graph museum;
    museum.init_graph();
    int a[2][3] = {
        {1, 3, 4},
        {2, 5, 9}
    };
    printf("a[1][2] = %d\n", a[1][2]);
    memset(a, 0, sizeof(a));
    printf("sizeof(a) = %d\n", sizeof(a));
    printf("a[1][2] = %d\n", a[1][2]);
    //printf("DBL_MAX = %f\n", DBL_MAX);
    int row_num = 4;
    int column_num = 5;
    Node nodes[MAX_VERTEX_NUM]; //Set of Nodes;
    init_nodes(nodes, museum, row_num, column_num);
    Node target; // The Target
    init_target(target, nodes);
    vector<int> shortest_paths[MAX_VERTEX_NUM];
    vector<int> vertexes_selected;
    double threshold = 100;
    int start  = 0;
    shortest_path_dijkstra(museum, start,\
        shortest_paths, vertexes_selected,\
        threshold);
    is_target_enclosed(nodes, shortest_paths, vertexes_selected);
}

int main(int argc, char *argv[])
{
    freopen("output.txt", "w", stdout);
    test();
    return 0;
}