#include"std_lib_facilities.h"
#include"Graph.h"
#include<vector>
#include<iostream>

using namespace Graph_lib;
using namespace std;

struct star:Closed_polyline{
    star(int n,Point cc);
    void draw_lines() const;
private:
    int n;
    //Polygon poly;
    Point center;
};