//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "binary_tree.h"
#include "star.h"
#include <iostream>

using namespace std;
//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib


    cout<<"Please input a number. 1 for star, 2 for binary tree, 3 for binary tree(triangle):"<<endl;
    int flag;
    cin>>flag;

    Point tl(100,100);           // to become top left  corner of window
    Simple_window win(tl,600,400,"Canvas");    // make a simple window

    if(flag==1)
    {
        cout<<"Please input n:"<<endl;
        int n;
        cin>>n;
        cout<<"Please input center's coordinate:"<<endl;
        int x,y;
        cin>>x>>y;
        star test1(n,Point(x,y));
        int fill_color;
        int line_color;
        cout<<"Please input 2 numbers between 0 and 13 for different line color and fill color:"<<endl;
        cin>>line_color>>fill_color;
        test1.set_color(line_color);
        test1.set_fill_color(fill_color);
        win.attach(test1);
        win.wait_for_button();       // give control to the display engine
    }
    else
    {
        cout<<"Please input n:"<<endl;
        int n;
        cin>>n;
        if(flag==2){
            binary_tree test2(n);
            win.attach(test2);
            win.wait_for_button();       // give control to the display engine
        }
        else{
            binary_tree_tri test3(n);
            win.attach(test3);
            win.wait_for_button();       // give control to the display engine
        }
    }

}

//------------------------------------------------------------------------------
