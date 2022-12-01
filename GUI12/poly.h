#ifndef POLY_H
#define POLY_H

#include"Graph.h"
#include"Point.h"
#include"std_lib_facilities.h"
#include <assert.h>
#include<FL/fl_draw.H>
#include<vector>
using namespace std;
//using namespace Graph_lib;

struct poly:Graph_lib::Closed_polyline{
    private:
        bool flag=true;
    public:
        poly(vector<Point>& v);

        bool isPoly(){return flag;}
        void add(Point p);
        void draw_lines() const;
};
#endif
