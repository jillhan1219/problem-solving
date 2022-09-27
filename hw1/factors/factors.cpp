#include<iostream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

ostringstream convert;
void enumeration(int n,vector<int>& ans1,ostringstream& convert){
    for(int i=1;i<=n;++i){
        if(n%i==0){
            ans1.push_back(i);
        }
    }
    convert<<ans1.size();
    for(auto it=ans1.begin();it!=ans1.end();++it){
        convert<<" "<<*it;
    }
    convert<<"\n";
}

int getPrimeFactors(int n,vector<vector<int>>& helper){
    int i=1,s=1,t;
        vector<int> tmpV;
    while(n>1){
        i++;
        t=0;
        int tmp=i;
        tmpV.clear();
        while(n%i==0){
            n/=i;
            t++;
            if(t!=1)
                tmp*=i;
            tmpV.push_back(tmp);
        }
        s*=(t+1);
        if(t!=0)
            helper.push_back(tmpV);
    }
    return s;
}

void multiple(vector<int>& ans2,vector<int>& v2);
void getAns2(vector<vector<int>>& helper,vector<int>& ans2){
    ans2.push_back(1);
    for(auto it=helper.begin();it!=helper.end();++it){
        multiple(ans2,*it);
    }
}

void multiple(vector<int>& ans2,vector<int>& v2){
    vector<int> tmp;
    for(auto it1=ans2.begin();it1!=ans2.end();++it1){
        for(auto it2=v2.begin();it2!=v2.end();++it2){
            tmp.push_back((*it1)*(*it2));
        }
    }
    for(auto it3=tmp.begin();it3!=tmp.end();++it3){
        ans2.push_back(*it3);
    }
}

int divided(vector<int>&v,int low,int high)
{
	int p = v[low];
	while (low < high)
	{
		while (low < high && p <= v[high])
			high--;
		v[low] = v[high];
		while (low < high && p >= v[low])
			low++;
		v[high] = v[low];
	}
	v[low] = p;
	return low;
}
//快排第二部，递归
void repeact(vector<int>&v,int low,int high)
{
	if (low > high)	return;
	int flag = divided(v, low, high);
	repeact(v,low,flag-1);
	repeact(v,flag+1,high);

}

int main() 
{		
   bool exercise1=true;
    if(exercise1)    {
    //第一关执行代码
    string str;          
    getline(cin,str);    
    istringstream ss(str);
    int n;
    ss>>n;
    vector<int> ans1;
    enumeration(n,ans1,convert);

    vector<int> ans2;
    vector<vector<int>> helper;
    int s=getPrimeFactors(n,helper);
    getAns2(helper,ans2);
    repeact(ans2, 0, ans2.size() - 1);

    convert<<s;
    for(auto it=ans2.begin();it!=ans2.end();++it){
        convert<<" "<<*it;
    }
    string ans=convert.str();
    cout<<str.length()<<":"<<ans.length()<<"\n";
    cout<<ans;
    }   else     {
    //第二关执行代码


    }
    
    
	/********** End **********/
    system("pause");
  	return 0;
}