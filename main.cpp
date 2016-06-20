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
}

int main(int argc, char *argv[])
{
    freopen("output.txt", "w", stdout);
    test();
    return 0;
}