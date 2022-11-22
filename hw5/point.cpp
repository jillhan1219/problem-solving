#include<iostream>
#include<vector>
#include<algorithm>
#include"std_lib_facilities.h"
#include<regex>
using namespace std;

struct point
{
    int x;int y;
    bool operator ==(const point& p)
    {
        if(p.x==x&&p.y==y)
            return true;
        return false;
    }
    bool operator ==(int d)
    {
        return x*x+y*y==d*d;
    }

    int distance(const point& p)
    {
        return (x-p.x)*(x-p.x)+(y-p.y)*(y-p.y);
    }
};

class points
{
private:
    vector<point> allPoints;
    void invalid(){cout<<"invalid input";}
public:
    void add(stringstream& iss);
    void myfind(stringstream& iss);
    void filter(stringstream& iss);
    void mysort(stringstream& iss);
};

void points::add(stringstream& iss)
{
    try
    {
        char ch;
        int n;
        iss>>n;
        int value;
        int cnt=1;
        vector<point> points_tmp;
        while(iss>>value)
        {
            point tmp;
            if(cnt%2==1)
            {
                tmp.x=value;
                cnt++;
                continue;
            }
            else
            {
                tmp.y=value;
                points_tmp.push_back(tmp);
                cnt++;
            }
        }
        if(cnt!=n*2+1)
            error("invalid input");
        for(auto& it:points_tmp)
            allPoints.push_back(it);
        sort(allPoints.begin(),allPoints.end(),[](point& a,point& b){
            return a.x==b.x?a.y<b.y:a.x<b.x; });
        auto end=allPoints.end();
        vector<point>::iterator new_end=unique(allPoints.begin(),end);
        allPoints.erase(new_end,end);
        cout<<allPoints.size()<<endl;
    }
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}
}

void points::myfind(stringstream& iss)
{
    try
    {
        string pattern="^(find)(\\x20[-]?[0-9]+){2}$";
        regex r(pattern);
        string input=iss.str();
        if(!regex_match(input,r))
            error("invalid input");
        point target;
        iss>>target.x>>target.y;
        vector<point>::iterator it=find(allPoints.begin(),allPoints.end(),target);
        if(it!=allPoints.end())
            //cout<<"\n"<<"find";
            cout<<"find"<<endl;
        else
            //cout<<"\n"<<"not find";
            cout<<"not find"<<endl;
    }
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}
}

void points::filter(stringstream& iss)
{
    try
    {
        string pattern="^(filter)(\\x20[-]?[0-9]+){3}$";
        regex r(pattern);
        string input=iss.str();
        if(!regex_match(input,r))
            error("invalid input");
        point target;
        iss>>target.x>>target.y;
        int d;
        iss>>d;
        auto new_end=partition(allPoints.begin(),allPoints.end(),
        [d,target](point tmp){return tmp.distance(target)<=d*d;});
        allPoints.erase(new_end,allPoints.end());
        //cout<<"\n"<<allPoints.size();
        cout<<allPoints.size()<<endl;
    }
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}
}

void points::mysort(stringstream& iss)
{
    try{
        if(allPoints.empty())
        {
            cout<<"\n";
            return;
        }
        string pattern="^(sort)(\\x20[-]?[0-9]){2}$";
        regex r(pattern);
        string input=iss.str();
        if(!regex_match(input,r))
            error("invalid input");
        point target;
        iss>>target.x>>target.y;
        sort(allPoints.begin(),allPoints.end(),
        [target](point a,point b){return a.distance(target)==b.distance(target)?
        (a.x==b.x?a.y<b.y:a.x<b.x):a.distance(target)<b.distance(target);});
        //cout<<"\n";
        auto itr=allPoints.begin();
        cout<<"("<<itr->x<<","<<" "<<itr->y<<")";
        itr++;
        for(;itr!=allPoints.end();++itr)
        {
            cout<<","<<" "<<"("<<itr->x<<","<<" "<<itr->y<<")";
        }
        cout<<endl;
    }
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}
}

int main()
{
    points test;
    string input;
    while(getline(cin,input))
    {
        stringstream iss(input);
        string order;
        iss>>order;
        if(order=="add")
            test.add(iss);
        else if(order=="find")
            test.myfind(iss);
        else if(order=="filter")
            test.filter(iss);
        else
            test.mysort(iss);
    }
    return 0;
}