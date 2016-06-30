#ifndef GRAPH_HEAD
#define GRAPH_HEAD
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cfloat>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

/***************************************
 * Definition of Vertex, Node and Graph
 ***************************************/
// Vertex class
class Vertex {
public:
    Vertex(double x, double y) : x_(x), y_(y) { }
    Vertex() : x_(0), y_(0) { }
    double get_x_() const;
    double get_y_() const;
    void set_x_(double x);
    void set_y_(double y);
    void print() const;
    virtual ~Vertex() { }
private:
    double x_; //x coordinate
    double y_; //y coordinate
};
double Vertex::get_x_() const
{
    return this->x_;
}
double Vertex::get_y_() const
{
    return this->y_;
}
void Vertex::set_x_(double x)
{
    this->x_ = x;
}
void Vertex::set_y_(double y)
{
    this->y_ = y;
}
void Vertex::print() const
{
    printf("x_ = %f, y_ = %f\n", x_, y_);
}

// Node class
class Node : public Vertex {
    //friend void init_nodes(const Graph &g, int row_num, int column_num);
public:
    Node() { }
    Node(double x, double y) : Vertex(x, y) { }
    static double get_speed();
    static void set_speed(double s);
    static double get_fov();
    static void set_fov(double d);
    int get_start() const;
    void set_start(int s);
    int get_end() const;
    void set_end(int d);
    double get_dist2start() const;
    void set_dist2start(double d);

private:
    static double speed; //Moving speed
    static double fov; //Field of view
    int start; //Vertex ID moving from
    int end; //Vertex ID moving to
    double dist2start; // Distance from the start vertex
};
double Node::get_speed()
{
    return speed;
}
void Node::set_speed(double s)
{
    speed = s;
}
double Node::get_fov()
{
    return fov;
}
void Node::set_fov(double d)
{
    fov = d;
}
int Node::get_start() const
{
    return start;
}
void Node::set_start(int s)
{
    start = s;
}
int Node::get_end() const
{
    return end;
}
void Node::set_end(int d)
{
    end = d;
}
double Node::get_dist2start() const
{
    return dist2start;
}
void Node::set_dist2start(double d)
{
    dist2start = d;
}

//Graph Scenario
const int MAX_VERTEX_NUM = 50;
class Graph {
    friend void init_vertexes(Graph &g, int row_num, int column_num);
    friend void init_arcs(Graph &g, int row_num, int column_num);
    friend void init_arcs_length(Graph &g);
    friend void init_arcs_probs(Graph &g);
    //friend void init_nodes(Graph &g, int row_num, int column_num);
    
public:
    Graph() { }
    Vertex get_vertex(int index) const;
    void set_vertex(int index, int x, int y);
    int get_arcs(int i, int j) const;
    void set_arcs(int x, int i, int j);
    double get_arcs_length(int i, int j) const;
    void set_arcs_length(double l, int i, int j);
    double get_arcs_probs(int i, int j) const;
    void set_arcs_probs(double p, int i, int j);
    int get_vertex_num() const;
    void set_vertex_num(int n);
    int get_arc_num() const;
    void set_arc_num(int i);
    void init_graph(int v_num = 20, int a_num = 31);
    
private:
    Vertex vertexes[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //顶点之间是否有边
    double arcs_length[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //边长
    double arcs_probs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //目标经过弧的概率
    int vertex_num; //Number of vertexes
    int arc_num; //Number of arc
};
Vertex Graph::get_vertex(int index) const
{
    return this->vertexes[index];
}
void Graph::set_vertex(int index, int x, int y)
{
    vertexes[index].set_x_(x);
    vertexes[index].set_y_(y);
}
int Graph::get_arcs(int i, int j) const
{
    return arcs[i][j];
}
void Graph::set_arcs(int x, int i, int j)
{
    arcs[i][j] = x;
}
double Graph::get_arcs_length(int i, int j) const
{
    return arcs_length[i][j];
}
void Graph::set_arcs_length(double l, int i, int j)
{
    arcs_length[i][j] = l;
}
double Graph::get_arcs_probs(int i, int j) const
{
    return arcs_probs[i][j];
}
void Graph::set_arcs_probs(double p, int i, int j)
{
    arcs_probs[i][j] = p;
}
int Graph::get_vertex_num() const
{
    return vertex_num;
}
void Graph::set_vertex_num(int n)
{
    vertex_num = n;
}
int Graph::get_arc_num() const
{
    return arc_num;
}
void Graph::set_arc_num(int i)
{
    arc_num = i;
}
void init_vertexes(Graph &g, int row_num, int column_num)
/* Initial vertexes with their coordinates.
 * 4 rows, 5 columns, an arc is between 16 to 24.
 */
{
    random_device rd;
    mt19937 gen(rd());
    //int row_start = 18; //Coordinate start of vertex rows
    //int row_end = 22; //Coordinate end of vertex rows
    //int column_start = 8; //Coordinate start of vertex columns
    //int column_end = 12; //Coordinate end of vertex columns
    int row_start = 14; //Coordinate start of vertex rows
    int row_end = 26; //Coordinate end of vertex rows
    int column_start = 4; //Coordinate start of vertex columns
    int column_end = 16; //Coordinate end of vertex columns
    double inc = 2 * Node::get_fov(); // Increase of coordinate 

    for (int i = 0; i < row_num; ++i) {
        double up = row_start + inc * i;
        double down = row_end + inc * i;
        uniform_real_distribution<> y_random(up, down);
        for (int j = 0; j < column_num; ++j) {
            double left = column_start + inc * j;
            double right = column_end + inc * j;
            uniform_real_distribution<> x_random(left, right);
            int index = i * column_num + j;
            //Set coordinate
            g.vertexes[index].set_x_(x_random(gen));
            g.vertexes[index].set_y_(y_random(gen));
        }
    }
    //test
    //for (int i = 0; i < g.vertex_num; ++i) {
    //    printf("%d: (%f, %f)\n", i, g.vertexes[i].get_x_(), g.vertexes[i].get_y_());
    //}
}
void init_arcs(Graph &g, int row_num, int column_num)
/* Initial the matrix arcs[][], set arc with 1, otherwise 0. */
{
    memset(g.arcs, 0, sizeof(g.arcs));
    //printf("sizeof(g.arcs) = %d\n", sizeof(g.arcs));
    for (int i = 1; i <= g.vertex_num - column_num; ++i) {
        g.arcs[i - 1][i - 1 + column_num] = 1;
        g.arcs[i - 1 + column_num][i - 1] = 1;
        if (i % column_num != 0) {
            g.arcs[i - 1][i] = 1;
            g.arcs[i][i - 1] = 1;
        }
    }
    for (int i = g.vertex_num - column_num + 1; i < g.vertex_num; ++i) {
        g.arcs[i - 1][i] = 1;
        g.arcs[i][i - 1] = 1;
    }
    //test
    //printf("  ");
    //for (int i = 0; i < g.vertex_num; ++i) {
    //    printf("%3d", i);
    //}
    //fputc('\n', stdout);
    //for (int i = 0; i < g.vertex_num; ++i) {
    //    printf("%-2d", i);
    //    for (int j = 0; j < g.vertex_num; ++j) {
    //        //printf("%3d", g.arcs[i][j]);
    //        printf("%3d", g.get_arcs(i,j));
    //    }
    //    fputc('\n', stdout);
    //}
}
int is_arc(const Graph &g, int i, int j)
/* If there is a edge between vertex i and j */
{
    return g.get_arcs(i, j);
}
double get_dist_vertexes(const Vertex &vi, const Vertex &vj)
{
    double xi = vi.get_x_();
    double yi = vi.get_y_();
    double xj = vj.get_x_();
    double yj = vj.get_y_();

    return sqrt(pow(xi - xj, 2) + pow(yi - yj, 2));
}
void init_arcs_length(Graph &g)
/* Calculate lengths of arcs.
 */
{
    memset(g.arcs_length, 0, sizeof(g.arcs_length));
    for (int i = 0; i < g.vertex_num; ++i) {
        for (int j = 0; j < g.vertex_num; ++j) {
            if (!is_arc(g, i, j)) {
                //g.arcs_length[i][j] = DBL_MAX;
                //g.arcs_length[j][i] = DBL_MAX;
                continue;
            }
            double dist = get_dist_vertexes(g.vertexes[i], g.vertexes[j]);
            g.arcs_length[i][j] = dist;
            g.arcs_length[j][i] = dist;
        }
    }
    //test
    //printf("  ");
    //for (int i = 0; i < g.vertex_num; ++i) {
    //    printf("%5d", i);
    //}
    //fputc('\n', stdout);
    //for (int i = 0; i < g.vertex_num; ++i) {
    //    printf("%-2d", i);
    //    for (int j = 0; j < g.vertex_num; ++j) {
    //        //printf("%3d", g.arcs[i][j]);
    //        printf("%5.1f", g.get_arcs_length(i,j));
    //    }
    //    fputc('\n', stdout);
    //}
}
void init_arcs_probs(Graph &g)
/* Calculate probabilities of moving in arcs */
{
    memset(g.arcs_probs, 0, sizeof(g.arcs_probs));
    random_device rd;
    mt19937 gen(rd());
    for (int v = 0; v < g.vertex_num; ++v) {
        /* Out Degree of vertex v */
        int degree = 0;
        for (int j = 0; j < g.vertex_num; ++j) {
            if (g.arcs[v][j]) {
                ++degree;
            }
        }
        double cumulative_prob = 0;
        for (int j = 0; j < g.vertex_num; ++j) {
            if (!g.arcs[v][j]) {
                continue;
            }
            --degree;
            if (degree == 0) {
                g.arcs_probs[v][j] = 1 - cumulative_prob;
            } else {
                uniform_real_distribution<> prob_random(0, 1 - cumulative_prob);
                double prob_vj = prob_random(gen);
                g.arcs_probs[v][j] = prob_vj;
                cumulative_prob += prob_vj;
            }
        }
    }
    //test
    //printf("  ");
    //for (int i = 0; i < g.vertex_num; ++i) {
    //    printf("%7d", i);
    //}
    //fputc('\n', stdout);
    //for (int i = 0; i < g.vertex_num; ++i) {
    //    printf("%-2d", i);
    //    for (int j = 0; j < g.vertex_num; ++j) {
    //        //printf("%3d", g.arcs[i][j]);
    //        printf("%7.4f", g.get_arcs_probs(i,j));
    //    }
    //    fputc('\n', stdout);
    //}
}
void Graph::init_graph(int v_num, int a_num)
{
    vertex_num = v_num;
    arc_num = a_num;
    int row_num = 4; //Number of vertex row
    int column_num = 5; //Number of vertex column

    /* Initial vertexes with their coordinates */
    init_vertexes(*this, row_num, column_num);

    /* Initial the matrix of arcs */
    init_arcs(*this, row_num, column_num);

    /* Calculate the matrix of lengths of arcs */
    init_arcs_length(*this);

    /* Calculate the probabilities of moving in arcs */
    init_arcs_probs(*this);


}

void shortest_path_dijkstra(const Graph &g, int target_from, int start,\
    vector<int> *shortest_paths, vector<int> &vertexes_selected,\
    double *distances, double threshold)
/* Calculate shortest paths from vertex start */
{
    //double distances[MAX_VERTEX_NUM]; //Temporary shortest distances set
    vector<int> paths[MAX_VERTEX_NUM]; //Temporary shortest paths set
    /* Initialization */
    for (int i = 0; i < g.get_vertex_num(); ++i) {
        if (0 == g.get_arcs(start, i)) {
            distances[i] = DBL_MAX;
        } else {
            distances[i] = g.get_arcs_length(start, i);
        }
        //from[i] = start;
        paths[i].push_back(target_from);
        paths[i].push_back(start);
    }
    int is_gotten[MAX_VERTEX_NUM]; //Flags: if vertex is finished
    memset(is_gotten, 0, sizeof(is_gotten));
    is_gotten[start] = 1;
    is_gotten[target_from] = 1;
    /* Solving */
    for (int i = 1; i < g.get_vertex_num(); ++i) {
        double dist_min = DBL_MAX;
        int index_min = -1;
        for (int j = 0; j < g.get_vertex_num(); ++j) {
            if (is_gotten[j]) {
                continue;
            }
            if (distances[j] < dist_min) {
                dist_min = distances[j];
                index_min = j;
            }
        }
        if (-1 == index_min || dist_min > threshold) {
            break;
        }
        is_gotten[index_min] = 1;
        vertexes_selected.push_back(index_min);
        paths[index_min].push_back(index_min);
        for (int j = 0; j < g.get_vertex_num(); ++j) {
            if (is_gotten[j] || !g.get_arcs(index_min, j)) {
                continue;
            }
            if (dist_min + g.get_arcs_length(index_min, j) < distances[j]) {
                distances[j] = dist_min + g.get_arcs_length(index_min, j);
                paths[j].assign(paths[index_min].begin(),\
                                paths[index_min].end());
            }
        }
    }
    for (vector<int>::iterator it = vertexes_selected.begin();\
         it != vertexes_selected.end(); ++it) {
        shortest_paths[*it].assign(paths[*it].begin(), paths[*it].end());
    }

    //test
    //printf("Dijkstra:\nStart: %d\n", start);
    //printf("Vertexes selected:");
    //sort(vertexes_selected.begin(), vertexes_selected.end());
    //for (vector<int>::iterator it = vertexes_selected.begin();\
    //     it != vertexes_selected.end();
    //     ++it) {
    //    printf(" %d", *it);
    //}
    //fputc('\n', stdout);
    //for (int i = 0; i < g.get_vertex_num(); ++i) {
    //    printf("distances[%i] = %f\n", i, distances[i]);
    //    printf("Shortest path:");
    //    for (vector<int>::iterator it = shortest_paths[i].begin();\
    //         it != shortest_paths[i].end(); ++it) {
    //        printf(" %d", *it);
    //    }
    //    fputc('\n', stdout);
    //}

}

/***************************************
 * Definition of Expectation of movement saving
 ***************************************/
//Expectation of moving distance saving
class Expect_Saving {
public:
    Expect_Saving() { }
    //Expect_Saving(double v, int n, int m) : \
    //    value(v), node(n), if_move(m), to(-1) { }
    //Expect_Saving(double v, int n, int m, int t, double d) : \
    //    value(v), node(n), if_move(m), to(t), dist_saved(d) { }
    //Expect_Saving(double v, int n, int m, int t) : \
    //    value(v), node(n), if_move(m), to(t) { }
    Expect_Saving(double v, int n, int m) : \
        value(v), node(n), if_move(m) { }
    double get_value() const;
    void set_value(double v);
    int get_node() const;
    void set_node(int n);
    int get_if_move() const;
    void set_if_move(int m);
    //int get_to() const;
    //void set_to(int t);
    //double get_dist_saved() const;
    //void set_dist_saved(double d);
private:
    double value; //Expectation value
    int node; //Which node
    int if_move; //Flag value: if the node move
    //int to; //If the node move, which vertex it move to
    //double dist_saved; //Distance saved
};
double Expect_Saving::get_value() const
{
    return value;
}
void Expect_Saving::set_value(double v)
{
    value = v;
}
int Expect_Saving::get_node() const
{
    return node;
}
void Expect_Saving::set_node(int n)
{
    node = n;
}
int Expect_Saving::get_if_move() const
{
    return if_move;
}
void Expect_Saving::set_if_move(int m)
{
    if_move = m;
}
//int Expect_Saving::get_to() const
//{
//    return to;
//}
//void Expect_Saving::set_to(int t)
//{
//    to = t;
//}
//double Expect_Saving::get_dist_saved() const
//{
//    return dist_saved;
//}
//void Expect_Saving::set_dist_saved(double d)
//{
//    dist_saved = d;
//}

/***************************************
 * Settings of Scenario
 ***************************************/
//int END = 100; //Experiment time
int Mobile_Node_Num = 5; //Number of nodes
//double Search_Threshold = 100; //Distance threshold of shortest paths
double Target_Moving_Dist_Threshold = 2000; //Distance of target moving
int Target_Num = 1; //Number of target
double Node::speed = 2; //Speed of target and nodes
double Node::fov = 10; //Node's distance of field of view
//double Total_Distance_Saved = 0; // Total saved moving distance of nodes
double Total_Node_Moving_Dist = 0; //Total moving distance of nodes
char Result_File[256]; //File address for saving results

/***************************************
 * Deployment of Target and Nodes
 ***************************************/
//Node Nodes[MAX_VERTEX_NUM]; //Set of Nodes;
void init_nodes(Node *Nodes, const Graph &g, int row_num, int column_num)
/* Deploy nodes */
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> row_random(0, row_num - 1);
    uniform_int_distribution<> column_random(0, column_num - 1);
    int is_set[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    memset(is_set, 0, sizeof(is_set));
    int row;
    int column = column_random(gen);
    for (int i = 0; i < Mobile_Node_Num; ++i) {
        do {
            row = row_random(gen);
            column = (column + 1) % column_num; //Columns in turn, to make even
        } while(is_set[row][column]);
        is_set[row][column] = 1;
        int index = row * column_num + column;
        Nodes[i].set_start(index);
        Nodes[i].set_end(index);
        Nodes[i].set_dist2start(0);
        Nodes[i].set_x_(g.get_vertex(index).get_x_());
        Nodes[i].set_y_(g.get_vertex(index).get_y_());
    }
    //test
    //for (int i = 0; i < row_num; ++i) {
    //    for (int j = 0; j < column_num; ++j) {
    //        if (is_set[i][j]) {
    //            printf(" 1");
    //        } else {
    //            printf(" 0");
    //        }
    //    }
    //    fputc('\n', stdout);
    //}
}
//Node Target; // The Target
int init_target(Node &Target, const Node *nodes)
/* Deploy the target: choose the same location with one of those nodes */
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> node_random(0, Mobile_Node_Num - 1);
    int node = node_random(gen);
    int index = nodes[node].get_start();
    Target.set_start(index);
    Target.set_end(index);
    Target.set_dist2start(0);
    //printf("target start = %d\n", Target.get_start()); //test
    return node;
}

/***************************************
 * Processing
 ***************************************/
int is_on_arc(int v0, int v1, const Node &node);
int is_path_captured(const Node *nodes, const vector<int> &path) 
/* If the path is enclosed by nodes */
{
    for (vector<int>::const_iterator p_i = path.begin() + 1;\
         p_i != path.end(); ++p_i) {
        for (int i = 0; i < Mobile_Node_Num; ++i) {
            //if (*p_i == nodes[i].get_start()) {
            //    return 1;
            //}
            if (is_on_arc(*p_i, *(p_i + 1), nodes[i])) {
                return 1;
            }
        }
    }
    return 0;
}
int is_target_enclosed(const Node *nodes, const vector<int> *shortest_paths,\
                const vector<int> &vertexes_selected)
/* If the target is enclosed by nodes */
{
    int enclosed_count = 0;
    for (vector<int>::const_iterator vs_i = vertexes_selected.begin();\
         vs_i != vertexes_selected.end(); ++vs_i) {
        enclosed_count += is_path_captured(nodes, shortest_paths[*vs_i]);
        //test
        //printf("Vertex path (%d): %d\n",\
        //    *vs_i, is_path_captured(nodes, shortest_paths[*vs_i]));
    }
    if (enclosed_count == vertexes_selected.size()) {
        //printf("YES! Enclosed!\n"); //test
        return 1;
    } else {
        //printf("NO! Not enclosed!\n"); //test
        return 0;
    }
}

int is_on_vertex(int v, const Node &node)
/* If the node is on the vertex */
{
    if (node.get_start() == v && node.get_end() == v) {
        return 1;
    } else {
        return 0;
    }
}

int is_on_arc(int v0, int v1, const Node &node)
    /* If the node is on the arc(v0, v1) */
{
    if (is_on_vertex(v0, node) || is_on_vertex(v1, node)) {
        return 1;
    }
    if ((node.get_start() == v0 && node.get_end() == v1)\
        || (node.get_start() == v1 && node.get_end() == v0)) {
            return 1;
    } else {
        return 0;
    }
}

//void get_path_expect(vector<Expect_Saving> &expects_set, const Node *nodes,\
//    const Graph &g, const vector<int> &path, const double *distances, int tracking_id)
///* Calculate expectations in the path */
//{
//    double prob_start_v1 = 1;
//    double prob_start_v2 = 1;
//    double double_fov = 2 * Node::get_fov();
//    for (vector<int>::const_iterator v_i = path.begin();\
//         v_i != path.end() - 1; ++v_i) {
//        int v1 = *v_i;
//        int v2 = *(v_i + 1);
//        int v0 = (v_i != path.begin() ? *(v_i - 1) : -1);
//        //printf("@643 (v0 - v1 - v2) = (%d - %d - %d)\n", v0, v1, v2); //test
//        prob_start_v2 = prob_start_v1 * g.get_arcs_probs(v1, v2);
//        //printf("@646 Mobile_Node_Num = %d\n", Mobile_Node_Num); //test
//        //printf("prob_start_v1 = %f, prob_start_v2 = %f\n", prob_start_v1,\
//        //    prob_start_v2); //test
//        for (int i = 0; i < Mobile_Node_Num; ++i) {
//            if (!is_on_arc(v1, v2, nodes[i]) || tracking_id == i) {
//                continue;
//            }
//            double dist_v0_v1 = \
//                get_dist_vertexes(g.get_vertex(v0), g.get_vertex(v1));
//            double dist_v1_m1 = \
//                get_dist_vertexes(g.get_vertex(v1), nodes[i]);
//            //if (dist_v1_m1 > distances[v1]) {
//            //    printf("Cannot arrive in time! dist_v1_m1 = %f distances[%d] = %f\n", dist_v1_m1, v1, distances[v1]); //test
//            //    continue;
//            //}
//            //printf("@651\n"); //test
//            if (-1 == v0) {
//                /*double dist_v1_m1 = \
//                    get_dist_vertexes(g.get_vertex(v1), nodes[i]);*/
//                double dist_sav = \
//                    (dist_v1_m1 < double_fov ? dist_v1_m1 : double_fov);
//                double exp = dist_sav * prob_start_v2;
//                //printf("@655 exp = %f\n", exp); //test
//                Expect_Saving expect_tmp(exp, i, 0);
//                expects_set.push_back(expect_tmp);
//                //printf("******* v0 == -1 *******\n"); //test
//                //printf("dist_v1_m1 = %f\n\
//                //       prob_start_v2 = %f\n\
//                //       dist_sav = %f\n\
//                //       exp = %f\n", \
//                //    dist_v1_m1, prob_start_v2, dist_sav, exp);
//                //nodes[i].set_start(v2);
//                //nodes[i].set_end(v1);
//                continue;
//            }
//            double dist_sav;
//            double exp;
// 
//            //printf("******* Rock n Roll *******\n");
//            //printf("dist_v0_v1 = %f, dist_v1_m1 = %f\n", dist_v0_v1, dist_v1_m1); //test
//            /* Not to move */
//            //printf("***** Not to move:\n");
//            if (dist_v0_v1 >= double_fov) {
//                dist_sav = \
//                ((is_on_vertex(v1, nodes[i]) || dist_v1_m1 >= double_fov) ? \
//                    double_fov : dist_v1_m1);
//            } else {
//                if (is_on_vertex(v1, nodes[i])) {
//                    dist_sav = dist_v0_v1;
//                } else if (dist_v1_m1 < double_fov) {
//                    dist_sav = dist_v1_m1;
//                } else {
//                    dist_sav = double_fov;
//                }
//            }
//            if (is_on_vertex(v1, nodes[i])) {
//                exp = dist_sav * prob_start_v1;
//                //printf("dist_sav = %f\n", dist_sav);
//                //printf("prob_start_v1111 = %f\n", prob_start_v1);
//                //printf("exp = %f\n", exp); //test
//            } else {
//                exp = dist_sav * prob_start_v2;
//                //printf("dist_sav = %f\n", dist_sav);
//                //printf("prob_start_v2222 = %f\n", prob_start_v2);
//                //printf("exp = %f\n", exp); //test
//            }
//            Expect_Saving expect_wait(exp, i, 0);
//            expects_set.push_back(expect_wait);
//
//            /* To move */
//            //printf("***** To move:\n");
//            if (dist_v1_m1 > distances[v1]) {
//                //printf("Cannot arrive in time! dist_v1_m1 = %f distances[%d] = %f\n", dist_v1_m1, v1, distances[v1]); //test
//                continue;
//            }
//            if (is_on_vertex(v1, nodes[i])) {
//                continue;
//            }
//            if (dist_v0_v1 >= double_fov) {
//                dist_sav = (
//                    dist_v0_v1 - Node::get_fov() >= dist_v1_m1 ?
//                    double_fov - dist_v1_m1 :
//                    dist_v0_v1 + Node::get_fov() - 2 * dist_v1_m1);
//            } else {
//                dist_sav = (
//                    Node::get_fov() >= dist_v1_m1 ? 
//                    dist_v0_v1 - dist_v1_m1 :
//                    dist_v0_v1 + Node::get_fov() - 2 * dist_v1_m1);
//            }
//            exp = dist_sav * prob_start_v1;
//            //Expect_Saving expect_move(exp, i, 1, v1, exp);
//            Expect_Saving expect_move(exp, i, 1, v1, dist_sav);
//            expects_set.push_back(expect_move);
//            //printf("dist_sav = %f\n", dist_sav);
//            //printf("prob_start_v1 = %f\n", prob_start_v1);
//            //printf("exp = %f\n", exp); //test
//        }
//        /* Update prob_start_v1 */
//        prob_start_v1 = prob_start_v2;
//    }
//    //printf("@706 expects_set.size = %d\n", expects_set.size());
//}

//void get_all_expects(vector<Expect_Saving> &expects_set, const Node *nodes,\
//    const Graph &g, const vector<int> *shortest_paths,\
//    const vector<int> &vertexes_selected, const double *distances,\
//    int tracking_id)
double get_expect_not_move(const Node &node, int v1, double dist_v0_v1, \
                           double dist_v1_m1, double prob_v0_v1, \
                           double prob_v1_v2)
/* Calculate its expectation if the node does NOT move */
{
    //int i = node_on_arc[v];
    //double prob_v1_v2 = g.get_arcs_probs(v1, v);
    //double dist_v1_m1 = get_dist_vertexes(g.get_vertex(v1), nodes[i]);
    double dist_sav;
    double double_fov = 2 * Node::get_fov();
    if (dist_v0_v1 >= double_fov) {
        if (is_on_vertex(v1, node) || dist_v1_m1 >= double_fov) {
            dist_sav = double_fov;
        } else {
            dist_sav = dist_v1_m1;
        }
    } else {
        if (is_on_vertex(v1, node)) {
            dist_sav = dist_v0_v1;
        } else if (dist_v1_m1 < double_fov) {
            dist_sav = dist_v1_m1;
        } else {
            dist_sav = double_fov;
        }
    }
    double exp;
    if (is_on_vertex(v1, node)) {
        exp = dist_sav * prob_v0_v1;
    } else {
        exp = dist_sav * prob_v1_v2;
    }
    //printf("get_expect_not_move: exp(%f) = dist_sav(%f) * prob\n",\
    //    exp, dist_sav);//test
    return exp;
}

double get_expect_move(double dist_v0_v1, double dist_v1_m1, \
                       double prob_v0_v1, double &d_m0)
/* Calculate its expectation if the node does move */
{
    double dist_sav;
    double double_fov = 2 * Node::get_fov();
    if (dist_v0_v1 >= double_fov) {
        if (dist_v0_v1 - Node::get_fov() >= dist_v1_m1) {
            dist_sav = double_fov - dist_v1_m1;
            d_m0 = dist_v0_v1 - double_fov;
        } else {
            dist_sav = dist_v0_v1 + Node::get_fov() - 2 * dist_v1_m1;
            d_m0 = dist_v1_m1 - Node::get_fov();
        }
    } else {
        if (Node::get_fov() >= dist_v1_m1) {
            dist_sav = dist_v0_v1 - dist_v1_m1;
            d_m0 = 0;
        } else {
            dist_sav = dist_v0_v1 + Node::get_fov() - 2 * dist_v1_m1;
            d_m0 = dist_v1_m1 - Node::get_fov();
        }
    }
    double exp = dist_sav * prob_v0_v1;
    //printf("get_expect_move: exp(%f) = dist_sav(%f) * prob_v0_v1(%f)\n",\
    //    exp, dist_sav, prob_v0_v1);//test
    return exp;
}
void get_all_expects(vector<Expect_Saving> &expects_set, const Node *nodes,\
                     const Graph &g, int target_from, int target_to,\
                     int tracking_id)
/* Calculate all Expectations */    
{
    //for (vector<int>::const_iterator v_i = vertexes_selected.begin();
    //     v_i != vertexes_selected.end(); ++v_i) {
    //    get_path_expect(expects_set, nodes, g, \
    //        shortest_paths[*v_i], distances, tracking_id);
    //}
    //test
    //int count = 0;
    //for (vector<Expect_Saving>::iterator e_i = expects_set.begin();
    //    e_i != expects_set.end(); ++e_i) {
    //    printf("%d: ", ++count);
    //    printf("(value = %f, node = %d, if_move = %d, to = %d)\n",
    //        e_i->get_value(), e_i->get_node(), e_i->get_if_move(), e_i->get_to());
    //}
    double double_fov = 2 * Node::get_fov();
    int v0 = target_from;
    int v1 = target_to;
    double dist_v0_v1 = g.get_arcs_length(v0, v1);
    double prob_v0_v1 = 1.0;

    //test 
    //printf("******* get_all_expects *******\n");
    //printf("tracking_id = %d at [%d-%d %f]\n", \
    //    tracking_id, nodes[tracking_id].get_start(), \
    //    nodes[tracking_id].get_end(), nodes[tracking_id].get_dist2start());
    /* Special situation: a node is on v0v1. If so it will just wait. */
    //int is_met = 0;
    for (int i = 0; i < Mobile_Node_Num; ++i) {
        if (!is_on_arc(v0, v1, nodes[i]) || i == tracking_id) {
            continue;
        }
        //is_met = 1;
        double dist_v0_m1 = \
            get_dist_vertexes(g.get_vertex(v0), nodes[i]);
        double dist_sav = \
            (dist_v0_m1 < double_fov ? dist_v0_m1 : double_fov);
        Expect_Saving expect_meet(dist_sav, i, 0);
        expects_set.push_back(expect_meet);
        //test
        //printf("In Special Situation, i = %d at [%d - %d], dist_v0_m1 = %f, dist_sav = %f\n", \
        //    i, nodes[i].get_start(), nodes[i].get_end(), dist_v0_m1, dist_sav);
        //if (nodes[i].get_start() != nodes[i].get_end() && dist_sav == 0) {
        //    printf("@898 zerozero\n");
        //}

    }
    //if (is_met) {
    //    return;
    //}

    ////double prob_v0_v1 = g.get_arcs_probs(target_from, target_to);
    //int node_on_arc[MAX_VERTEX_NUM]; //vertex_on_arc[v2] = m1 (node m1 is on arc v1v2)
    //for (int i = 0; i < MAX_VERTEX_NUM; ++i) {
    //    node_on_arc[i] = -1;
    //}
    ///* Find out all possible nodes */
    //for (int v = 0; v < g.get_vertex_num(); ++v) {
    //    if (!g.get_arcs(v1, v) || v == v1) {
    //        continue;
    //    }
    //    for (int i = 0; i < Mobile_Node_Num; ++i) {
    //         if (is_on_arc(v1, v, nodes[i]) && i != tracking_id) {
    //             node_on_arc[v] = i;
    //             //printf("node[%d] is on arc (%d %d)\n", i, v1, v);//test
    //         }
    //    }
    //}
    //vector<Expect_Saving> expects_not_move;
    ///* Not to move */
    //for (int v = 0; v < g.get_vertex_num(); ++v) {
    //    if (node_on_arc[v] == -1) {
    //        continue;
    //    }
    //    int i = node_on_arc[v];
    //    double prob_v1_v2 = g.get_arcs_probs(v1, v);
    //    double dist_v1_m1 = get_dist_vertexes(g.get_vertex(v1), nodes[i]);
    //    //double dist_sav;
    //    //if (dist_v0_v1 >= double_fov) {
    //    //    if (is_on_vertex(v1, nodes[i]) || dist_v1_m1 >= double_fov) {
    //    //        dist_sav = double_fov;
    //    //    } else {
    //    //        dist_sav = dist_v1_m1;
    //    //    }
    //    //} else {
    //    //    if (is_on_vertex(v1, nodes[i])) {
    //    //        dist_sav = dist_v0_v1;
    //    //    } else if (dist_v1_m1 < double_fov) {
    //    //        dist_sav = dist_v1_m1;
    //    //    } else {
    //    //        dist_sav = double_fov;
    //    //    }
    //    //}
    //    //double exp;
    //    //if (is_on_vertex(v1, nodes[i])) {
    //    //    exp = dist_sav * 1.0;
    //    //} else {
    //    //    exp = dist_sav * prob_v1_v2;
    //    //}
    //    double exp = get_expect_not_move(nodes[i], v1, dist_v0_v1, \
    //        dist_v1_m1, prob_v0_v1, prob_v1_v2);
    //    //test
    //    //if (exp < 0.000001) {
    //    //    printf("@950 What happened?\n");
    //    //    printf("exp = %f, node[%d] (%d -> %d /%f)\n",\
    //    //        exp, i, nodes[i].get_start(), nodes[i].get_end(),\
    //    //        nodes[i].get_dist2start());
    //    //    printf("dist_v0_v1 = %f\n", dist_v0_v1);
    //    //    printf("dist_v1_m1 = %f\n", dist_v1_m1);
    //    //    printf("prob_v0_v1 = %f\n", prob_v0_v1);
    //    //    printf("prob_v1_v2 = %f\n", prob_v1_v2);
    //    //}
    //    Expect_Saving expect_wait(exp, i, 0);
    //    expects_not_move.push_back(expect_wait);
    //    expects_set.push_back(expect_wait);
    //}
    ///* To move */
    //for (int v = 0; v < g.get_vertex_num(); ++v) {
    //    if (node_on_arc[v] == -1) {
    //        continue;
    //    }
    //    int i = node_on_arc[v];
    //    double dist_v1_m1 = get_dist_vertexes(g.get_vertex(v1), nodes[i]);
    //    /* Advantages of movement */
    //    if (dist_v1_m1 > dist_v0_v1) {
    //        continue; // Cannot arrive in time
    //    }
    //    if (is_on_vertex(v1, nodes[i])) {
    //        continue; // Not need move
    //    }
    //    double d_m0;
    //    //double dist_sav;
    //    //if (dist_v0_v1 >= double_fov) {
    //    //    if (dist_v0_v1 - Node::get_fov() >= dist_v1_m1) {
    //    //        dist_sav = double_fov - dist_v1_m1;
    //    //        d_m0 = dist_v0_v1 - double_fov;
    //    //    } else {
    //    //        dist_sav = dist_v0_v1 + Node::get_fov() - 2 * dist_v1_m1;
    //    //        d_m0 = dist_v1_m1 - Node::get_fov();
    //    //    }
    //    //} else {
    //    //    if (Node::get_fov() >= dist_v1_m1) {
    //    //        dist_sav = dist_v0_v1 - dist_v1_m1;
    //    //        d_m0 = 0;
    //    //    } else {
    //    //        dist_sav = dist_v0_v1 + Node::get_fov() - 2 * dist_v1_m1;
    //    //        d_m0 = dist_v1_m1 - Node::get_fov();
    //    //    }
    //    //}
    //    //double exp = dist_sav;
    //    double exp = get_expect_move(dist_v0_v1, dist_v1_m1,\
    //                                 prob_v0_v1, d_m0);
    //    //if (exp < 0.000001 && exp >= 0) {
    //    //    printf("@999 What happened?\n");
    //    //    printf("exp = %f, node[%d] (%d -> %d /%f)\n",\
    //    //        exp, i, nodes[i].get_start(), nodes[i].get_end(),\
    //    //        nodes[i].get_dist2start());
    //    //    printf("dist_v0_v1 = %f\n", dist_v0_v1);
    //    //    printf("dist_v1_m1 = %f\n", dist_v1_m1);
    //    //    printf("prob_v0_v1 = %f\n", prob_v0_v1);
    //    //    printf("d_m0 = %f\n", d_m0);
    //    //}
    //    /* As well as advantages of future meet */
    //    for (vector<Expect_Saving>::iterator e_i = expects_not_move.begin();
    //         e_i != expects_not_move.end(); ++e_i) {
    //        if (e_i->get_node() == i) {
    //            continue;
    //        }
    //        exp += e_i->get_value();
    //    }
    //    /* The expectation should also add the one wait on v0v1, i.e. m0 */
    //    double dist_v1_m0 = g.get_arcs_length(v0, v1) - d_m0;
    //    double dist_sav = \
    //        (dist_v1_m0 >= double_fov ? double_fov : dist_v1_m0);
    //    exp += (dist_sav * g.get_arcs_probs(v1, v0));
    //    //Expect_Saving expect_move(exp, i, 1, v1);
    //    Expect_Saving expect_move(exp, i, 1);
    //    expects_set.push_back(expect_move);
    //}
}

//For the target to choose path
class Prob_range {
public:
    Prob_range() { }
    Prob_range(double p, int t) : prob(p), to(t) { }
    Prob_range(double l, double p, double u, int t) : \
        lower(l), prob(p), upper(u), to(t) { }
    int get_to() const;
    void set_to(int t);
    double get_prob() const;
    void set_prob(double l);
    double get_lower() const;
    void set_lower(double l);
    double get_upper() const;
    void set_upper(double u);
private:
    int to; // To which vertex
    double prob; //Probability to the vertex
    double lower; //Probability lower range
    double upper; //Probability upper range

};
int Prob_range::get_to() const
{
    return to;
}
void Prob_range::set_to(int t)
{
    to = t;
}
double Prob_range::get_prob() const
{
    return prob;
}
void Prob_range::set_prob(double p)
{
    prob = p;
}
double Prob_range::get_lower() const
{
    return lower;
}
void Prob_range::set_lower(double l)
{
    lower = l;
}
double Prob_range::get_upper() const
{
    return upper;
}
void Prob_range::set_upper(double u)
{
    upper = u;
}

bool prob_comp(const Prob_range &a, const Prob_range &b)
/* For sort of Prob_range */
{
    return a.get_prob() < b.get_prob();
}

int get_target_next_step(const Node &target, const Graph &g)
/* Get the next destination of the target */
{
    int t_i = target.get_start();
    vector<Prob_range> prob_set;
    /* Get all "to" vertex */
    for (int i = 0; i < g.get_vertex_num(); ++i) {
        if (!g.get_arcs(t_i, i) || i == t_i) {
            continue;
        }
        Prob_range prob_tmp(g.get_arcs_probs(t_i, i), i);
        prob_set.push_back(prob_tmp);
    }
    sort(prob_set.begin(), prob_set.end(), prob_comp);
    /* Set lower and upper */
    double lower_range = 0;
    for (vector<Prob_range>::iterator p_i = prob_set.begin();
        p_i != prob_set.end(); ++p_i) {
        p_i->set_lower(lower_range);
        p_i->set_upper(lower_range + p_i->get_prob());
        lower_range += p_i->get_prob();
    }
    //test
    //printf("from target (%d):\n", target.get_start());
    //for (vector<Prob_range>::iterator p_i = prob_set.begin();
    //    p_i != prob_set.end(); ++p_i) {
    //    printf("To vertex %d (%f): (%f, %f)\n",\
    //        p_i->get_to(), p_i->get_prob(), p_i->get_lower(), p_i->get_upper());
    //}

    /* Choose a destination */
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> prob_random(0, 1);
    double roll = prob_random(gen);
    int vertex_to = -1;
    for (vector<Prob_range>::iterator p_i = prob_set.begin();
        p_i != prob_set.end(); ++p_i) {
        if (roll >= p_i->get_lower() && roll < p_i->get_upper()) {
            vertex_to = p_i->get_to();
        }
    }
    //printf("roll = %f, vertex_to = %d\n", roll, vertex_to); //test
    return vertex_to;
}

void set_coordinate_in_arc(double &x, double &y,\
                           int from, int to, double dist2from, \
                           const Graph &g)
/* Set a node's coordinate in an arc */
{
    double delta_x = \
        g.get_vertex(to).get_x_() - g.get_vertex(from).get_x_();
    double delta_y = \
        g.get_vertex(to).get_y_() - g.get_vertex(from).get_y_();
    x = delta_x / g.get_arcs_length(from, to) * dist2from + \
        g.get_vertex(from).get_x_();
    y = delta_y / g.get_arcs_length(from, to) * dist2from + \
        g.get_vertex(from).get_y_();
    //wait for testing
}

void mobile_node_schedule(const vector<Expect_Saving> &expects_set, \
                          Node *nodes, int target_from, int target_to,\
                          const Graph &g, int &tracking_index)
/* Schedule the mobile nodes according to expectations */
{
    double expect_max = 0;
    int node_index;
    int will_move = 0;
    //int dest;
    //double dist_saved;
    int v0 = target_from;
    int v1 = target_to;
    double dist_v0_v1 = g.get_arcs_length(v0, v1);
    //double dist_v1_m1;

    //printf("======= mobile_node_schedule =======\n"); //test
    //printf("tracking_index = %d\n", tracking_index); //test
    if (expects_set.size() == 0) {
        Total_Node_Moving_Dist += dist_v0_v1;
        nodes[tracking_index].set_end(v1);
        nodes[tracking_index].set_start(v1);
        nodes[tracking_index].set_dist2start(0);
        nodes[tracking_index].set_x_(g.get_vertex(v1).get_x_());
        nodes[tracking_index].set_y_(g.get_vertex(v1).get_y_());
        //printf("size == 0, no node\n");
        return;
    }
    /* Choose the maximum expectation */
    for (vector<Expect_Saving>::const_iterator e_i = expects_set.begin();
         e_i != expects_set.end(); ++e_i) {
        if (e_i->get_value() >= expect_max) {
            expect_max = e_i->get_value();
            node_index = e_i->get_node();
            will_move = e_i->get_if_move();
            //dest = e_i->get_to();
            //dist_saved = e_i->get_dist_saved();
        }
        //test
        //printf("value = %f, node = %d, if_move = %d\n",\
        //    e_i->get_value(), e_i->get_node(), e_i->get_if_move());
    }
    //printf("expect_max = %f, node_index = %d, will_move = %d\n", \
    //    expect_max, node_index, will_move); //test
    /* If the node is to move */
    if (will_move) {
        /* Calculate the moving distance */
        double dist_v1_m1 = \
            get_dist_vertexes(g.get_vertex(v1), nodes[node_index]);
        //printf("@942 dist_v1_m1 = %f\n", dist_v1_m1); //test
        double double_fov = 2 * Node::get_fov();
        double d_m0;
        if (dist_v0_v1 >= double_fov) {
            if (dist_v0_v1 - Node::get_fov() >= dist_v1_m1) {
                d_m0 = dist_v0_v1 - double_fov;
            } else {
                d_m0 = dist_v1_m1 - Node::get_fov();
            }
        } else {
            if (Node::get_fov() >= dist_v1_m1) {
                d_m0 = 0;
            } else {
                d_m0 = dist_v1_m1 - Node::get_fov();
            }
        }
        Total_Node_Moving_Dist += (dist_v1_m1 + d_m0);
        /* Update nodes' coordinate */
        nodes[node_index].set_start(v1);
        nodes[node_index].set_end(v1);
        nodes[node_index].set_dist2start(0);
        nodes[node_index].set_x_(g.get_vertex(v1).get_x_());
        nodes[node_index].set_y_(g.get_vertex(v1).get_y_());
        nodes[tracking_index].set_start(v0);
        d_m0 == 0 ? \
            nodes[tracking_index].set_end(v0) : \
            nodes[tracking_index].set_end(v1);
        //if (dist_v0_v1 < double_fov && Node::get_fov() >= dist_v1_m1) {
        //    nodes[tracking_index].set_end(v0);
        //} else {
        //    nodes[tracking_index].set_end(v1);
        //}
        nodes[tracking_index].set_dist2start(d_m0);
        //test
        int ne = nodes[tracking_index].get_end();
        int ns = nodes[tracking_index].get_start();
        //if (ns != ne && d_m0 == 0) {
        //    printf("@1209 nodes[%d] (%d -> %d) %f\n",\
        //        tracking_index, ns, ne, nodes[tracking_index].get_dist2start());
        //    //zerozero
        //}

        double x, y;
        set_coordinate_in_arc(x, y, v0, v1, d_m0, g);
        nodes[tracking_index].set_x_(x);
        nodes[tracking_index].set_y_(y);
        tracking_index = node_index;
        //printf("@1245 Move: tracking_index = %d\n", tracking_index); //test
        return;
    }
    /* If the node is NOT to move */
    if (is_on_arc(v0, v1, nodes[node_index])) {
        double dist_v0_m1 = \
            get_dist_vertexes(g.get_vertex(v0), nodes[node_index]);
        double double_fov = 2 * Node::get_fov();
        double d_m0 = \
            (dist_v0_m1 >= double_fov ? dist_v0_m1 - double_fov : 0);
        Total_Node_Moving_Dist += d_m0;
        nodes[tracking_index].set_start(v0);
        //d_m0 ? \
        //    nodes[tracking_index].set_end(v1) : \
        //    nodes[tracking_index].set_end(v0);
        //dist_v0_m1 >= double_fov ? \
        //    nodes[tracking_index].set_end(v1) : \
        //    nodes[tracking_index].set_end(v0);
        d_m0 == 0 ? \
            nodes[tracking_index].set_end(v0) : \
            nodes[tracking_index].set_end(v1);
        nodes[tracking_index].set_dist2start(d_m0);
        //test
        //int ne = nodes[tracking_index].get_end();
        //int ns = nodes[tracking_index].get_start();
        //if (ns != ne && d_m0 == 0) {
        //    printf("@1241 nodes[%d] (%d -> %d) %f\n",\
        //        tracking_index, ns, ne, nodes[tracking_index].get_dist2start());
        //    //zerozero
        //}

        double x, y;
        set_coordinate_in_arc(x, y, v0, v1, d_m0, g);
        nodes[tracking_index].set_x_(x);
        nodes[tracking_index].set_y_(y);
        tracking_index = node_index;
    } else {
        Total_Node_Moving_Dist += dist_v0_v1;
        nodes[tracking_index].set_end(v1);
        nodes[tracking_index].set_start(v1);
        nodes[tracking_index].set_dist2start(0);
        nodes[tracking_index].set_x_(g.get_vertex(v1).get_x_());
        nodes[tracking_index].set_y_(g.get_vertex(v1).get_y_());
    }

    /* Schedule the tracking node */
    ///* If move */
    //if (will_move && dest == target_to) {
    //    Total_Distance_Saved += dist_saved; //Update total distance
    //    double dist_v0_v1 = g.get_arcs_length(target_from, target_to);
    //    //double dist_v1_m1 = \
    //    //    get_dist_vertexes(g.get_vertex(dest), nodes[node_index]);
    //    double d0 = dist_v0_v1 - dist_saved - dist_v1_m1; //Dm0 = |v0v1| - D - Dm1
    //    //Total_Node_Moving_Dist += (d0 + dist_v1_m1);
    //    Total_Node_Moving_Dist += d0;
    //    //printf("@959 dist_v1_m1 = %f, Total_Node_Moving_Dist = %f\n",\
    //    //    dist_v1_m1, Total_Node_Moving_Dist); //test
    //    /* Update tracking node */
    //    nodes[tracking_index].set_end(dest);
    //    nodes[tracking_index].set_dist2start(d0);
    //    double x, y;
    //    set_coordinate_in_arc(x, y, target_from, target_to, d0, g);
    //    nodes[tracking_index].set_x_(x);
    //    nodes[tracking_index].set_y_(y);
    //    tracking_index = node_index;

    //    return;
    //} else if (will_move) {
    //    Total_Node_Moving_Dist += g.get_arcs_length(target_from, target_to);

    //    return;
    //}
    /* If no move */
    //int is_met = 0; //If the target met with other nodes
    //for (int i = 0; i < Mobile_Node_Num; ++i) {
    //    if (i == tracking_index) {
    //        continue;
    //    }
    //    if (!is_on_arc(target_from, target_to, nodes[i])) {
    //        continue;
    //    }
    //    is_met = 1;
    //    double dist_v0_m1 = \
    //        get_dist_vertexes(g.get_vertex(target_from), nodes[i]);
    //    double double_fov = 2 * Node::get_fov();
    //    //double d0 = \
    //    //    (dist_v0_m1 > double_fov ? dist_v0_m1 - double_fov : 0);
    //    double d0;
    //    if (dist_v0_m1 > double_fov) {
    //        d0 = dist_v0_m1 - double_fov;
    //        Total_Distance_Saved += double_fov;
    //    } else {
    //        d0 = 0;
    //        Total_Distance_Saved += dist_v0_m1;
    //    }
    //    if (is_on_vertex(target_to, nodes[i])) {
    //        Total_Node_Moving_Dist += d0;
    //    } else {
    //        Total_Node_Moving_Dist += \
    //            d0 + get_dist_vertexes(nodes[i], g.get_vertex(target_to));
    //    }
    //    //printf("@992 d0 = %f, Total_Node_Moving_Dist = %f\n",\
    //    //    d0, Total_Node_Moving_Dist); //test
    //    if (d0) {
    //        nodes[tracking_index].set_end(target_to);
    //        nodes[tracking_index].set_start(target_from);
    //        nodes[tracking_index].set_dist2start(d0);
    //        double x, y;
    //        set_coordinate_in_arc(x, y, target_from, target_to, d0, g);
    //        nodes[tracking_index].set_x_(x);
    //        nodes[tracking_index].set_y_(y);
    //    }
    //    tracking_index = i;
    //    break;
    //}
    //if (!is_met) {
    //    Total_Node_Moving_Dist += g.get_arcs_length(target_from, target_to);
    //    nodes[tracking_index].set_end(target_to);
    //    nodes[tracking_index].set_start(target_to);
    //    nodes[tracking_index].set_dist2start(0);
    //    nodes[tracking_index].set_x_(g.get_vertex(target_to).get_x_());
    //    nodes[tracking_index].set_y_(g.get_vertex(target_to).get_y_());
    //}
}
#endif