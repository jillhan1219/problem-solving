#include"std_lib_facilities.h"
#include"Graph.h"
#include"binary_tree.h"
#include<vector>
#include<iostream>

using namespace Graph_lib;
using namespace std;

binary_tree::binary_tree(int n):level(n)
{
    height=(400-40)/(n-1);
    number=pow(2,n)-1;
    int floor=0;
    int y=20;
    getChildren(floor,y);
}

void binary_tree::getChildren(int& floor,int& y)
{
   while(floor<level)
   {
        int tmp=pow(2,floor);
        int gap=600/(tmp+1);
        for(int i=0;i<tmp;++i)
        {
            Point point(gap*(i+1),y);
            position.push_back(point);
        }
        floor++;
        y+=height;
   }
}

void binary_tree::draw_lines()const
{
    for(auto& it:position)
    {
        fl_arc(it.x-5,it.y-5,5+5,5+5,0,360);
    }
    int fathers=pow(2,level-1)-1;
    for(int i=0;i<fathers;++i)
    {
        fl_line(position[i].x,position[i].y,
        position[i*2+1].x,position[i*2+1].y);
        fl_line(position[i].x,position[i].y,
        position[i*2+2].x,position[i*2+2].y);
    }
}
