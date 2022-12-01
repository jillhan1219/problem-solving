#ifndef SUPERELLIPSE_H
#define SUPERELLIPSE_H

#include"Graph.h"
#include"Point.h"
#include<assert.h>
#include<vector>
#include<FL/fl_draw.H>
#include"std_lib_facilities.h"
using namespace std;
using namespace Graph_lib;

struct superellipse:Shape {
    private:
        int a,b,m,n;
        int N;
        vector<Point> se_points;
        void draw_lines()const;
    public:
        superellipse(double a,double b,double m,double n, double N);
        Lines star;
        void getStar();
};

#endif
