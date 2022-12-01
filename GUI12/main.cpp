#include "superellipse.h"
#include "Simple_window.h"
#include "Graph.h"
#include "poly.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    using namespace Graph_lib;
    cout<<"Please input number 1 or 2 for different problems. 1 for superellipse, 2 for poly"<<endl;
    int problem;
    cin>>problem;
    if(problem==1)
    {
         double a,b,m,n;
         int N;
         cout<<"Please input a b m n:"<<endl;
         cin>>a>>b>>m>>n;
         cout<<"Please input N: "<<endl;
         cin>>N;

         superellipse test(a,b,m,n,N);

         test.getStar();

         Simple_window win(Point(200,200),600,400,"supperellipse");
         win.attach(test.star);
         win.wait_for_button();
    }

    else
    {
        vector<Point> polyPoints;

        cout<<"Please input the number of points"<<endl;
        int N;
        cin>>N;
        for(int i=0;i<N;++i)
        {
            cout<<"Please input x and y of Point"<<(i+1)<<" :"<<endl;
            int x,y;
            cin>>x>>y;
            polyPoints.push_back(Point(x,y));
        }

        Simple_window win(Point(200,200),600,400,"poly");
        Text t(Point(150,200),"Sorry, the given points cannot be polygnal");

        poly test2(polyPoints);

        if(test2.isPoly())
            win.attach(test2);
        else
            win.attach(t);

        win.wait_for_button();
    }

    return 0;
}
