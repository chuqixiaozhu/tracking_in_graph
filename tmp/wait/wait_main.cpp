#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "WAIT_GRAPH_HEAD.h"

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
    while (total_target_dist < Target_Moving_Dist_Threshold) {
        int target_to = get_target_next_step(target, g);
        //printf("(%d -> %d)\n", target_from, target_to); //test
        //vector<int> shortest_paths[MAX_VERTEX_NUM];
        //vector<int> vertexes_selected;
        //double shortest_dists[MAX_VERTEX_NUM];
        //shortest_path_dijkstra(g, target_from, target_to,\
        //    shortest_paths, vertexes_selected,\
        //    shortest_dists, Search_Threshold);
        //int is_enclosed = 0;
        //if (is_target_enclosed(nodes, \
        //    shortest_paths, vertexes_selected)) {
        //    is_enclosed = 1;                
        //}
        vector<Expect_Saving> expects_set;
        //if (!is_enclosed) {
        //get_all_expects(expects_set, nodes, g, shortest_paths,\
        //    vertexes_selected, shortest_dists, tracking_id);
        get_all_expects(expects_set, nodes, g, target_from, target_to,\
            tracking_id);
        //}
        //printf("get_all_expects passed.\n"); //test
        mobile_node_schedule(expects_set, nodes, target_from, target_to,\
            g, tracking_id);
        //printf("mobile_node_schedule passed.\n"); //test
        target.set_start(target_to);
        target.set_end(target_to);
        target.set_x_(g.get_vertex(target_to).get_x_());
        target.set_y_(g.get_vertex(target_to).get_y_());
        double target_moved_dist = g.get_arcs_length(target_from, target_to);
        total_target_dist += target_moved_dist;
        target_from = target_to;
    }
    //double total_node_moving_dist = total_target_dist - Total_Distance_Saved;
    //printf("Total_Moving_Distance = %f (/%f)\n", \
    //    total_node_moving_dist, total_target_dist);
    printf("Total_Node_Moving_Dist = %f (/%f)\n", \
        Total_Node_Moving_Dist, total_target_dist);
    FILE *result_file = fopen(Result_File, "a");
    //printf("Result_File = %s\n", Result_File);
    if (result_file) {
        fprintf(result_file, "%d %f\n", \
            Mobile_Node_Num, Total_Node_Moving_Dist/total_target_dist);
        fclose(result_file);
    } else {
        printf("Error: cannot create file \"%s\"\n", Result_File);
    }
}

void init_parameters(int argc, char *argv[])
/* Set parameters */
{
    switch (argc) {
    case 4:
        Target_Moving_Dist_Threshold = atoi(argv[3]);
    case 3:
        sprintf(Result_File, "%s", argv[2]);
    //case 3:
    //    Search_Threshold = atoi(argv[2]);
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
    init_parameters(argc, argv);

    return 0;
}