#include "Graph.h"
#include "Simple_window.h"
#include <vector>
#include <FL/Fl_Window.H>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#define x_gap 90
using namespace Graph_lib;
using namespace std;

struct chart
{
private:
    Open_polyline line_max;
    Open_polyline line_min;
    Open_polyline aug_max;
    Open_polyline aug_min;
    Simple_window win;
    Axis day;
    Axis temperature;
    Text coordinates_max;
    Text coordinates_min;
public:
    chart(vector<double>& vec_max,vector<double>& vec_min,int& counter,vector<string>& date);
};
chart::chart(vector<double>& vec_max,vector<double>& vec_min,int& counter,vector<string>& date):
    win(Point(100,100),760,460,"line chart"),
    day(Axis::x,Point(20,380),720,8,"day"),
    temperature(Axis::y,Point(20,380),350,7,"temperature"),
    coordinates_max(Point(70,420),""),
    coordinates_min(Point(70,440),"")
{
    if(counter>=5)
    {
        for(int i=0;i<7;++i)
        {
            line_max.add(Point(20+90*(i+1),380-vec_max[i]*10));
            line_min.add(Point(20+90*(i+1),380-vec_min[i]*10));
        }
    }
    else
    {
        int i;
        for(i=0;i<=3;++i)
        {
            aug_max.add(Point(20+90*(i+1),380-vec_max[i]*10));
            aug_min.add(Point(20+90*(i+1),380-vec_min[i]*10));
        }
        aug_max.set_color(1);
        aug_min.set_color(2);
        for(i=3;i<7;++i)
        {
            line_max.add(Point(20+90*(i+1),380-vec_max[i]*10));
            line_min.add(Point(20+90*(i+1),380-vec_min[i]*10));
        }
    }
    line_max.set_color(1);
    line_min.set_color(2);

    ostringstream iss1;
    ostringstream iss2;
    if(counter<61&&counter>=5)
    {
        for(int i=0;i<7;++i){
            iss1<<"("<<date[i]<<","<<vec_max[i]<<")"<<"      ";
        }
         for(int i=0;i<7;++i){
            iss2<<"("<<date[i]<<","<<vec_min[i]<<")"<<"      ";
        }
    }
    else if(counter==61)
    {
        line_max.set_style(1);
        line_min.set_style(1);
        int i=0;
        iss1<<"(10-31,"<<vec_max[i]<<")"<<"   ";
        iss2<<"(10-31,"<<vec_min[i]<<")"<<"   ";
        for(i=1;i<7;++i)
        {
            iss1<<"(11-0"<<i<<","<<fixed<<setprecision(1)<<vec_max[i]<<")   ";
            iss2<<"(11-0"<<i<<","<<fixed<<setprecision(1)<<vec_min[i]<<")   ";
        }
    }

    else
    {
        aug_max.set_style(1);
        aug_min.set_style(1);
        for(int i=0;i<3;++i)
        {
            iss1<<"(08-"<<(i+29)<<","<<fixed<<setprecision(1)<<vec_max[i]<<")"<<"   ";
            iss2<<"(08-"<<(i+29)<<","<<fixed<<setprecision(1)<<vec_min[i]<<")"<<"   ";
        }
        for(int i=3;i<7;++i)
        {
            iss1<<"(09-0"<<(i-2)<<","<<vec_max[i]<<")"<<"   ";
            iss2<<"(09-0"<<(i-2)<<","<<vec_min[i]<<")"<<"   ";
        }
    }

    coordinates_max.set_label(iss1.str());
    coordinates_min.set_label(iss2.str());

    win.attach(day);
    win.attach(temperature);
    win.attach(line_max);
    win.attach(line_min);
    if(counter<5)
    {
        win.attach(aug_max);
        win.attach(aug_min);
    }
    win.attach(coordinates_max);
    win.attach(coordinates_min);
    win.wait_for_button();
}
