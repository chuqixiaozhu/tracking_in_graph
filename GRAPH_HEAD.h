#ifndef GRAPH_HEAD
#define GRAPH_HEAD
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <random>

using namespace std;

// Vertex class
class Vertex {
public:
    Vertex(double x, double y) : x_(x), y_(y) { }
    Vertex() : x_(0), y_(0) { }
    double get_x_();
    double get_y_();
    void set_x_(double x);
    void set_y_(double y);
    void print() const;
    virtual ~Vertex() { }
private:
    double x_; //x coordinate
    double y_; //y coordinate
};
double Vertex::get_x_()
{
    return this->x_;
}
double Vertex::get_y_()
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
public:
    Node() { }
    Node(double x, double y) : Vertex(x, y) { }
    static double get_speed();
    static void set_speed(double s);
    static double get_fov();
    static void set_fov(double d);
private:
    static double speed; //Moving speed
    static double fov; //Field of view
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

double Node::speed = 2;
double Node::fov = 10;

//Graph Scenario
const int MAX_VERTEX_NUM = 50;
class Graph {
public:
    Graph() { }
    Vertex get_vertex(int index);
    void set_vertex(int index, int x, int y);
    int get_arcs(int i, int j);
    void set_arcs(int x, int i, int j);
    double get_arcs_length(int i, int j);
    void set_arcs_length(double l, int i, int j);
    double get_arcs_probs(int i, int j);
    void set_arcs_probs(double p, int i, int j);
    int get_vertex_num();
    void set_vertex_num(int n);
    int get_arc_num();
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
Vertex Graph::get_vertex(int index)
{
    return this->vertexes[index];
}
void Graph::set_vertex(int index, int x, int y)
{
    vertexes[index].set_x_(x);
    vertexes[index].set_y_(y);
}
int Graph::get_arcs(int i, int j)
{
    return arcs[i][j];
}
void Graph::set_arcs(int x, int i, int j)
{
    arcs[i][j] = x;
}
double Graph::get_arcs_length(int i, int j)
{
    return arcs_length[i][j];
}
void Graph::set_arcs_length(double l, int i, int j)
{
    arcs_length[i][j] = l;
}
double Graph::get_arcs_probs(int i, int j)
{
    return arcs_probs[i][j];
}
void Graph::set_arcs_probs(double p, int i, int j)
{
    arcs_probs[i][j] = p;
}
int Graph::get_vertex_num()
{
    return vertex_num;
}
void Graph::set_vertex_num(int n)
{
    vertex_num = n;
}
int Graph::get_arc_num()
{
    return arc_num;
}
void Graph::set_arc_num(int i)
{
    arc_num = i;
}
void Graph::init_graph(int v_num, int a_num)
{
    vertex_num = v_num;
    arc_num = a_num;

    /* test */
    //printf("vertex = %d, arc = %d\n", vertex_num, arc_num);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(8, 12);
    for (int i = 0; i < 10; ++i) {
        printf("random = %f\n", dist(gen));
    }
    /* /test */

    /* Initial vertexes with their coordinates */
    int row_num = 4; //Number of vertex rows
    int row_start = 18; //Coordinate start of vertex rows
    int row_end = 22; //Coordinate end of vertex rows
    int column_num = 5; // Number of vertex columns
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
        }
    }
}
#endif