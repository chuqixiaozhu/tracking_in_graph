#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "GRAPH_HEAD.h"

void test()
{
    Node n(2, 3);
    n.print();
    n.set_x_(10);
    n.set_y_(10);
    n.print();
    Graph museum;
    museum.init_graph();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}