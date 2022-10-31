#include<iostream>
#include<regex>
#include<string>
using namespace std;

int main(){
    try{
        string number="[0-9]+(\\.[0-9]+){0,1}";
        //string pattern="^(([+-]?([0-9]+\\.?[0-9]+\\*)?)?[a-z][0-9]{1,2})([+-](([0-9]*\\.?[0-9]+\\*)?)?[a-z][0-9]{1,2})*(=([0-9]*\\.?[0-9]+))$";
        string pattern="^(([+-]?("+number+"\\*)?)?[a-z][0-9]{1,2})([+-](("+number+"\\*)?)?[a-z][0-9]{1,2})*(="+number+")$";
        string item="([+-]?("+number+"\\*)?)?[a-z][0-9]{1,2}";
        regex r(pattern);
        regex it(item);
        //regex r(number);
        string poly;
        while(cin>>poly)
        {
            //cout<<regex_match(poly,r)<<endl;
            if(regex_match(poly,r))
            {
                //smatch s;
                //cout<<regex_search(poly,s,it)<<"\n";
                //cout<<"size"<<s.size()<<"\n";
                //cout<<s.str(1)<<endl;
                //cout<<endl;
                const sregex_iterator end;
                for(sregex_iterator iter(poly.begin(),poly.end(),it); iter!=end;++iter)
                {
                    cout<<iter->str()<<" ";
                }
                cout<<endl;
            }
        }
        return 0;
    }
    catch(regex_error& e){
        cout<<e.what()<<e.code()<<endl;
        return 1;
    }
}
