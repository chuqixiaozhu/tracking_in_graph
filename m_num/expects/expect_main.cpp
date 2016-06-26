#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "EXPECTS_GRAPH_HEAD.h"

void test()
{
    /*Node n(2, 3);
    n.print();
    n.set_x_(10);
    n.set_y_(10);
    n.print();*/
    Graph museum;
    museum.init_graph();
    //int a[2][3] = {
    //    {1, 3, 4},
    //    {2, 5, 9}
    //};
    //printf("a[1][2] = %d\n", a[1][2]);
    //memset(a, 0, sizeof(a));
    //printf("sizeof(a) = %d\n", sizeof(a));
    //printf("a[1][2] = %d\n", a[1][2]);
    //printf("DBL_MAX = %f\n", DBL_MAX);
    int row_num = 4;
    int column_num = 5;
    Node nodes[MAX_VERTEX_NUM]; //Set of Nodes;
    init_nodes(nodes, museum, row_num, column_num);
    Node target; // The Target
    int tracking_id = init_target(target, nodes);
    vector<int> shortest_paths[MAX_VERTEX_NUM];
    vector<int> vertexes_selected;
    double threshold = 100;
    int start = nodes[tracking_id].get_start();
    double distances[MAX_VERTEX_NUM];
    shortest_path_dijkstra(museum, start,\
        shortest_paths, vertexes_selected,\
        distances, threshold);
    is_target_enclosed(nodes, shortest_paths, vertexes_selected);
    vector<Expect_Saving> expects_set;
    get_all_expects(expects_set, nodes, museum, shortest_paths,\
        vertexes_selected, distances, tracking_id);
    //void get_all_expects(vector<Expect_Saving> &expects_set, const Node *nodes,\
    //    const Graph &g, const vector<int> *shortest_paths,\
    //    const vector<int> &vertexes_selected, int tracking_id)
    cout << "expects_set.size = " << expects_set.size() << endl;
    int next_vertex = get_target_next_step(target, museum);
    printf("tracking_id = %d in arc (%d, %d)\n", \
        tracking_id, nodes[tracking_id].get_start(),\
        nodes[tracking_id].get_end()); //test
    int old_tracking = tracking_id; //test
    mobile_node_schedule(expects_set, nodes, start, next_vertex,\
        museum, tracking_id);
    printf("new tracking_id = %d in arc (%d, %d)\n",\
        tracking_id, nodes[tracking_id].get_start(),\
        nodes[tracking_id].get_end()); //test
    printf("Total_Distance_Saved = %f\n", Total_Distance_Saved);
    printf("now old_tracking is on arc (%d, %d, %f) at (%f, %f)\n", \
        nodes[old_tracking].get_start(), \
        nodes[old_tracking].get_end(), \
        nodes[old_tracking].get_dist2start(), \
        nodes[old_tracking].get_x_(), \
        nodes[old_tracking].get_y_());
}
void do_expmt()
{
    Graph g;
    g.init_graph();
    int row_num = 4;
    int column_num = 5;
    Node nodes[MAX_VERTEX_NUM]; //Set of Nodes;
    init_nodes(nodes, g, row_num, column_num);
    Node target; // The Target
    int tracking_id = init_target(target, nodes);
    int target_from = nodes[tracking_id].get_start();
    double total_target_dist = 0;
    //double target_moving_dist_threshold = 20000;
    //double search_threshold = 100;
    while (total_target_dist < Target_Moving_Dist_Threshold) {
        vector<int> shortest_paths[MAX_VERTEX_NUM];
        vector<int> vertexes_selected;
        double shortest_dists[MAX_VERTEX_NUM];
        shortest_path_dijkstra(g, target_from,\
            shortest_paths, vertexes_selected,\
            shortest_dists, Search_Threshold);
        vector<Expect_Saving> expects_set;
        get_all_expects(expects_set, nodes, g, shortest_paths,\
            vertexes_selected, shortest_dists, tracking_id);
        int target_to = get_target_next_step(target, g);
        mobile_node_schedule(expects_set, nodes, target_from, target_to,\
            g, tracking_id);
        target.set_start(target_to);
        target.set_end(target_to);
        target.set_x_(g.get_vertex(target_to).get_x_());
        target.set_y_(g.get_vertex(target_to).get_y_());
        double target_moved_dist = g.get_arcs_length(target_from, target_to);
        total_target_dist += target_moved_dist;
        target_from = target_to;
    }
    double total_node_moving_dist = total_target_dist - Total_Distance_Saved;
    printf("Total_Moving_Distance = %f (/%f)\n", \
        total_node_moving_dist, total_target_dist);
    FILE *result_file = fopen(Result_File, "a");
    //printf("Result_File = %s\n", Result_File);
    if (result_file) {
        fprintf(result_file, "%d %f\n", \
            Mobile_Node_Num, total_node_moving_dist/total_target_dist);
    }
    if (result_file) {
        fclose(result_file);
    }
}

void init_parameters(int argc, char *argv[])
/* Set parameters */
{
    //int count = 1;
    switch (argc) {
    case 5:
        Target_Moving_Dist_Threshold = atoi(argv[4]);
    case 4:
        sprintf(Result_File, "%s", argv[3]);
        //printf("argv[4] = %s, Result_File = %s\n", argv[4], Result_File);
    //case 4:
    //    count = atoi(argv[3]);
    case 3:
        Search_Threshold = atoi(argv[2]);
    case 2:
        Mobile_Node_Num = atoi(argv[1]);
    default:
    	break;
    }
    do_expmt();
}

int main(int argc, char *argv[])
{
    //freopen("output.txt", "w", stdout);
    //test();
    //do_expmt();
    //for (int i = 0; i < argc; ++i) {
    //    printf("%s ", argv[i]);
    //}
    //fputc('\n', stdout);
    init_parameters(argc, argv);
    return 0;
}