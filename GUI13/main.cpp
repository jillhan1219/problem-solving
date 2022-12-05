//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "binary_tree.h"
#include <iostream>

using namespace std;
//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib



    cout<<"Please input n:"<<endl;
    int n;
    cin>>n;

    cout<<"Please input a number. 2 for circle, 3 for triangle:"<<endl;
    int flag;
    cin>>flag;
    if(flag==2){
        binary_tree test2(n);
        Point tl(100,100);           // to become top left  corner of window
        Simple_window win(tl,600,400,"Canvas");    // make a simple window
        win.attach(test2);
        win.wait_for_button();       // give control to the display engine
    }
    else{
        binary_tree_tri test3(n);
        Point tl(100,100);           // to become top left  corner of window
        Simple_window win(tl,600,400,"Canvas");    // make a simple window
        win.attach(test3);
        win.wait_for_button();       // give control to the display engine
    }
}

//------------------------------------------------------------------------------
