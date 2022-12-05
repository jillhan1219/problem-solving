#include"std_lib_facilities.h"
#include"Graph.h"
#include<vector>
#include<iostream>

using namespace Graph_lib;
using namespace std;

struct binary_tree:Shape{
    binary_tree(int n);
    virtual void draw_lines() const;

    protected:
    vector<Point> position;
    //vector<Circle> node;
    void getChildren(int& floor,int& y);
    int level;
    //int width;
    int height;
    int number;
};

struct binary_tree_tri:binary_tree{
    binary_tree_tri(int n):binary_tree(n){};
    void draw_lines() const;
    private:
    void draw_tri(Point center) const;
};
