#include"std_lib_facilities.h"
#include"Graph.h"
#include"star.h"
#include<vector>
#include<iostream>
#include<cmath>
#include"std_lib_facilities.h"

using namespace Graph_lib;
using namespace std;

#define PI acos(-1)
#define R 50
#define r 20

star::star(int n,Point cc):n(n),center(cc)
{
    if(n<=2)
        error("n should >=3.");
    double gap=2*PI/n;
    double R_angle=0;
    double r_angle=gap/2;
    for(int i=0;i<n;++i)
    {
        Closed_polyline::add(Point(center.x+R*cos(R_angle),center.y+R*sin(R_angle)));
        Closed_polyline::add(Point(center.x+r*cos(r_angle),center.y+r*sin(r_angle)));
        R_angle+=gap;
        r_angle+=gap;
    }
}

void star::draw_lines() const
{
    Closed_polyline::draw_lines();
}
