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
    int get_dist2start() const;
    void set_dist2start(int d);

private:
    static double speed; //Moving speed
    static double fov; //Field of view
    int start; //Vertex ID moving from
    int end; //Vertex ID moving to
    int dist2start; // Distance from the start vertex
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
int Node::get_dist2start() const
{
    return dist2start;
}
void Node::set_dist2start(int d)
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
    int row_start = 18; //Coordinate start of vertex rows
    int row_end = 22; //Coordinate end of vertex rows
    int column_start = 8; //Coordinate start of vertex columns
    int column_end = 12; //Coordinate end of vertex columns
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
    for (int i = 0; i < g.vertex_num; ++i) {
        printf("%d: (%f, %f)\n", i, g.vertexes[i].get_x_(), g.vertexes[i].get_y_());
    }
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
    printf("  ");
    for (int i = 0; i < g.vertex_num; ++i) {
        printf("%3d", i);
    }
    fputc('\n', stdout);
    for (int i = 0; i < g.vertex_num; ++i) {
        printf("%-2d", i);
        for (int j = 0; j < g.vertex_num; ++j) {
            //printf("%3d", g.arcs[i][j]);
            printf("%3d", g.get_arcs(i,j));
        }
        fputc('\n', stdout);
    }
}
int is_arc(const Graph &g, int i, int j)
/* If there is a edge between vertex i and j */
{
    return g.get_arcs(i, j);
}
double distance_vertexes(const Vertex &vi, const Vertex &vj)
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
            double dist = distance_vertexes(g.vertexes[i], g.vertexes[j]);
            g.arcs_length[i][j] = dist;
            g.arcs_length[j][i] = dist;
        }
    }
    //test
    printf("  ");
    for (int i = 0; i < g.vertex_num; ++i) {
        printf("%5d", i);
    }
    fputc('\n', stdout);
    for (int i = 0; i < g.vertex_num; ++i) {
        printf("%-2d", i);
        for (int j = 0; j < g.vertex_num; ++j) {
            //printf("%3d", g.arcs[i][j]);
            printf("%5.1f", g.get_arcs_length(i,j));
        }
        fputc('\n', stdout);
    }
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
    printf("  ");
    for (int i = 0; i < g.vertex_num; ++i) {
        printf("%7d", i);
    }
    fputc('\n', stdout);
    for (int i = 0; i < g.vertex_num; ++i) {
        printf("%-2d", i);
        for (int j = 0; j < g.vertex_num; ++j) {
            //printf("%3d", g.arcs[i][j]);
            printf("%7.4f", g.get_arcs_probs(i,j));
        }
        fputc('\n', stdout);
    }
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

void shortest_path_dijkstra(const Graph &g, int start,\
    vector<int> *shortest_paths, vector<int> &vertexes_selected,\
    double threshold)
/* Calculate shortest paths from vertex start */
{
    double distances[MAX_VERTEX_NUM]; //Temporary shortest distances set
    vector<int> paths[MAX_VERTEX_NUM]; //Temporary shortest paths set
    /* Initialization */
    for (int i = 0; i < g.get_vertex_num(); ++i) {
        if (0 == g.get_arcs(start, i)) {
            distances[i] = DBL_MAX;
        } else {
            distances[i] = g.get_arcs_length(start, i);
        }
        //from[i] = start;
        paths[i].push_back(start);
    }
    int is_gotten[MAX_VERTEX_NUM]; //Flags: if vertex is finished
    memset(is_gotten, 0, sizeof(is_gotten));
    is_gotten[start] = 1;
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
    printf("Dijkstra:\nStart: %d\n", start);
    printf("Vertexes selected:");
    sort(vertexes_selected.begin(), vertexes_selected.end());
    for (vector<int>::iterator it = vertexes_selected.begin();\
         it != vertexes_selected.end();
         ++it) {
        printf(" %d", *it);
    }
    fputc('\n', stdout);
    for (int i = 0; i < g.get_vertex_num(); ++i) {
        printf("distances[%i] = %f\n", i, distances[i]);
        printf("Shortest path:");
        for (vector<int>::iterator it = shortest_paths[i].begin();\
             it != shortest_paths[i].end(); ++it) {
            printf(" %d", *it);
        }
        fputc('\n', stdout);
    }

}

/***************************************
 * Definition of Expectation of movement saving
 ***************************************/
//Expectation of moving distance saving
class Saving_Expect {
public:
    Saving_Expect() { }
    Saving_Expect(double v, int m) : value(v), if_move(m) { }
    Saving_Expect(double v, int m, int t) : value(v), if_move(m), to(t) { }
    double get_value() const;
    void set_value(double v);
    int get_if_move() const;
    void set_if_move(int m);
    int get_to() const;
    void set_to(int t);
private:
    double value;
    int if_move;
    int to;
};
double Saving_Expect::get_value() const
{
    return value;
}
void Saving_Expect::set_value(double v)
{
    value = v;
}
int Saving_Expect::get_if_move() const
{
    return if_move;
}
void Saving_Expect::set_if_move(int m)
{
    if_move = m;
}
int Saving_Expect::get_to() const
{
    return to;
}
void Saving_Expect::set_to(int t)
{
    to = t;
}

/***************************************
 * Settings of Scenario
 ***************************************/
int END = 100; //Experiment time
int Mobile_Node_Num = 6; //Number of nodes
int Target_Num = 1; //Number of target
double Node::speed = 2; //Speed of target and nodes
double Node::fov = 10; //Node's distance of field of view

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
    }
    //test
    for (int i = 0; i < row_num; ++i) {
        for (int j = 0; j < column_num; ++j) {
            if (is_set[i][j]) {
                printf(" 1");
            } else {
                printf(" 0");
            }
        }
        fputc('\n', stdout);
    }
}
//Node Target; // The Target
void init_target(Node &Target, const Node *nodes)
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
    printf("target start = %d\n", Target.get_start());
}

/***************************************
 * Processing
 ***************************************/
int is_path_captured(const Node *nodes, const vector<int> &path) 
/* If the path is enclosed by nodes */
{
    for (vector<int>::const_iterator p_i = path.begin() + 1;\
         p_i != path.end(); ++p_i) {
        for (int i = 0; i < Mobile_Node_Num; ++i) {
            if (*p_i == nodes[i].get_start()) {
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
        printf("Vertex path (%d): %d\n",\
            *vs_i, is_path_captured(nodes, shortest_paths[*vs_i]));
    }
    if (enclosed_count == vertexes_selected.size()) {
        printf("YES! Enclosed!\n"); //test
        return 1;
    } else {
        printf("NO! Not enclosed!\n"); //test
        return 0;
    }
}

void get_path_expect(vector<double> &expects_set, const Node *nodes,\
    const Graph &g, const vector<int> &path)
{

}

void get_all_expects(vector<double> &expects_set, const Node *nodes,\
    const Graph &g, const vector<int> *shortest_paths,\
    const vector<int> &vertexes_selected)
/* Calculate all Expectations */    
{

}
#endif