#include <iostream>
#include <sstream>
#include "Graph.h"         // get access to our graphics library facilities
#include "GUI.h"
#include "Window.h"
#include "Chart.h"
#include "PolynomialRegression.h"
#include <Fl/fl_File_Chooser.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Chart.H>
#include <FL/fl_ask.H>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>

#define Mon_1st_sep 5
#define Sun_last_oct 60
#define days_sep 30
#define week 7

using namespace Graph_lib;
using namespace std;

/*
* 线性拟合采用全部数据预测
* 经与实际数据比较，发现二阶拟合相对误差最小，因此使用二阶拟合
*/

const vector<string> week_name={"Mon","Tue","Wed","Thus","Fri","Sat","Sun"};
vector<double> max_temp;
vector<double> min_temp;
vector<double> oct_max(7);//predict last 6
vector<double> oct_min(7);//predict last 6
vector<double> aug_max(7);//predict first 3
vector<double> aug_min(7);//predict last 6
vector<double> date;
vector<string> date_name;
//------------------------------------------------------------------------------
string fileName;

void importData(vector<double>& max_temp,vector<double>& min_temp,string& name,vector<double>& date,vector<string>& date_name);

struct Lines_window : Graph_lib::Window {
    Lines_window(Point xy, int w, int h, const string& title );

private:
    Button draw_button;        // input date
    Button quit_button;
    In_box month_input;
    In_box day_input;

    Button select_button;

    static void cb_next(Address, Address); // callback for draw_button
    void next();
    static void cb_quit(Address, Address); // callback for quit_button
    void quit();
    static void cb_select(Address,Address);
    void select();

};

//------------------------------------------------------------------------------

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    :Window(xy,w,h,title),
    draw_button(Point(x_max()-400,270), 150, 30, "Draw", cb_next),
    quit_button(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
    month_input(Point(x_max()-400,140), 100, 30, "month:"),
    day_input(Point(x_max()-400,200), 100, 30, "day:"),
    select_button(Point(200,80),150,30,"Import data file",cb_select)
{
    attach(draw_button);
    attach(quit_button);
    attach(month_input);
    attach(day_input);
    attach(select_button);
}

//------------------------------------------------------------------------------

void Lines_window::cb_quit(Address, Address pw)    // "the usual"
{
       reference_to<Lines_window>(pw).quit();
}

//------------------------------------------------------------------------------

void Lines_window::quit()
{
    hide();        // curious FLTK idiom for delete window
}

//------------------------------------------------------------------------------

void Lines_window::cb_next(Address, Address pw)     // "the usual"
{
    reference_to<Lines_window>(pw).next();
}

//------------------------------------------------------------------------------
void OK_callback(Fl_Widget* w,void* data)
{
    w->hide();
}

void Lines_window::next()
{
    int month = month_input.get_int();
    int day = day_input.get_int();

    if(fileName.empty())
    {
        fl_message("Please select a file to import data first.");
        return;
    }
    if(max_temp.size()==0)
        importData(max_temp,min_temp,fileName,date,date_name);

    int count=0;
    if(month==9)
    {
        if(day>30||day<1){
            fl_message("Invalid date.");
            return;
        }
        else
            count+=day;
    }

    else if(month==10)
    {
        if(day>31||day<1){
            fl_message("Invalid date.");
            return;
        }
        else
            count=days_sep+day;
    }

    else{
        fl_message("Please select a date in September or October.");
        return;
    }

    if(count>=Mon_1st_sep&&count<=Sun_last_oct)
    {
        int mol=(count-Mon_1st_sep)%7;
        int monday=(count-mol-1);
        vector<double> chart_data_max(max_temp.begin()+monday,max_temp.begin()+monday+7);
        vector<double> chart_data_min(min_temp.begin()+monday,min_temp.begin()+monday+7);
        vector<string> date_week(date_name.begin()+monday,date_name.begin()+monday+7);

        chart line_chart(chart_data_max,chart_data_min,count,date_week);
    }
    else
    {
        vector<double> coffes_max;
        vector<double> coffes_min;
        PolynomialRegression<double> predict_max;
        PolynomialRegression<double> predict_min;
        predict_max.fitIt(date,max_temp,2,coffes_max);
        predict_min.fitIt(date,min_temp,2,coffes_min);
        vector<string> date_tmp;

        if(count>Sun_last_oct)
        {
            oct_max[0]=max_temp[60];
            oct_min[0]=min_temp[60];
            for(int i=1;i<7;++i)
            {
                oct_max[i]=coffes_max[2]*(60+i)*(60+i)+coffes_max[1]*(60+i)+coffes_max[0];
                oct_min[i]=coffes_min[2]*(60+i)*(60+i)+coffes_min[1]*(60+i)+coffes_min[0];
            }
            chart line_chart(oct_max,oct_min,count,date_tmp);
        }
        else
        {
            for(int i=3;i<7;++i)
            {
                aug_max[i]=max_temp[i-3];
                aug_min[i]=min_temp[i-3];
            }
            for(int i=0;i<3;++i)
            {
                aug_max[i]=coffes_max[2]*(-3+i)*(-3+i)+coffes_max[1]*(-3+i)+coffes_max[0];
                aug_min[i]=coffes_min[2]*(-3+i)*(-3+i)+coffes_min[1]*(-3+i)+coffes_min[0];
            }
            chart line_chart(aug_max,aug_min,count,date_tmp);
        }
    }
}
void Lines_window::cb_select(Address, Address pw)     // "the usual"
{
    reference_to<Lines_window>(pw).select();
}

void FileChooser_cb(Fl_File_Chooser* fc, void* data)
{
	/*
	for (int i = 1; i <= fc->count(); i++)
	{
		const char* currentFilename = fc->value(i);
		cout << currentFilename << endl;
	}
	*/
	//cout<<fc->value()<<endl;
	fileName=fc->value();
	//cout<<fileName<<endl;
}

void Lines_window::select()
{
    Fl_File_Chooser* fc=new Fl_File_Chooser(".", "TXT (*.txt)", Fl_File_Chooser::SINGLE,"File Chooser");
	fc->callback(FileChooser_cb);

	fc->show();

}

//------------------------------------------------------------------------------
void importData(vector<double>& max_temp,vector<double>& min_temp,string& name,vector<double>& date,vector<string>& date_name)
{
    ifstream ifs;
    ifs.open(fileName,ios::in);
    if(!ifs.is_open())
    {
        cout<<"fail"<<endl;
        return;
    }

    string input;
    int index=0;

    while(getline(ifs,input))
    {
        int pos=input.find(" ");
        date_name.push_back(input.substr(0,pos));
        istringstream iss(input.substr(pos+1));
        int maxT,minT;
        iss>>maxT>>minT;
        max_temp.push_back(maxT);
        min_temp.push_back(minT);
        date.push_back(index++);
    }
    //cout<<date_name.size()<<endl;
}

int main()
try {
    Lines_window win(Point(100,100),600,400,"project2");
    return gui_main();
}
catch(exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Some exception\n";
    return 2;
}


