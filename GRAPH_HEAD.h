#ifndef GRAPH_HEAD
#define GRAPH_HEAD
#include <iostream>
#include <cstdio>
#include <cstdlib>

// Vetex class
class Vetex {
public:
    Vetex(double x, double y) : x_(x), y_(y) { }
    Vetex() : x_(0), y_(0) { }
    double get_x_();
    double get_y_();
    void set_x_(double x);
    void set_y_(double y);
    void print() const;
    virtual ~Vetex() { }
private:
    double x_; //x coordinate
    double y_; //y coordinate
};
double Vetex::get_x_()
{
    return this->x_;
}
double Vetex::get_y_()
{
    return this->y_;
}
void Vetex::set_x_(double x)
{
    this->x_ = x;
}
void Vetex::set_y_(double y)
{
    this->y_ = y;
}
void Vetex::print() const
{
    printf("x_ = %f, y_ = %f\n", x_, y_);
}

// Node class
class Node : public Vetex {
public:
    Node() { }
    Node(double x, double y) : Vetex(x, y) { }
    double get_speed();
    static void set_speed(double s);
private:
    static double speed; //Moving speed
};
double Node::get_speed()
{
    return this->speed;
}
void Node::set_speed(double s)
{
    speed = s;
}
double Node::speed = 2;

//Graph Scenario
const int MAX_VERTEX_NUM = 50;
Class Graph {
public:
private:
    Vetex vetexes[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //顶点之边的弧长
    double arcs_probs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //弧的概率
    int vetex_num; //Number of vetexes
    int arc_num; //Number of arc
};
#endif