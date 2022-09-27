## factors总结
1. 输入输出
* 输入
    * 以字符串形式输入，关键是转化为int类型，结合CS106L所学，利用istringstream转化。
        ```
            getline(cin,str);    
            istringstream ss(str);
            int n;
            ss>>n;
        ```
* 输出
    * 需要统计总输出的字符数，肯定需要转换为字符串，同样利用ostringstream转换
    * 其中第二行开始先输出个数，因此先把数据放在vector中最后再send到convert
    * 注意最后一个数字后没有 **空格**，因此应先输入一个数字，后面的循环再" "+数字，最后不要忘记"\n"
        ```
        convert<<ans1.size();
        convert<<ans1.size();
        for(auto it=ans1.begin();it!=ans1.end();++it){
            convert<<" "<<*it;
        }
        convert<<"\n";
        ```
2. 枚举法
* 简单循环的话就是O(n)的复杂度，其实可以到O($\sqrt n$)的，考虑到还要排序就懒了QAQ
    ```
        for(int i=1;i<=n;++i){
            if(n%i==0){
                ans1.push_back(i);
            }
        }
    ```
3. 因式分解法
* 本题思考最久QAQ，要求里其实有一点点提示，就是先分解为质因子，再找所有的因子，但是想了半天没想明白怎么把质因子乘起来才能不重不漏，后来参考[求因子个数](https://blog.csdn.net/iwtwiioi/article/details/14170521)才大概有了思路。
* 首先就是找到所有的质因子，但其实对我们有用的不是所有的质因子的vector，而是每个相同的质因子出现了多少次。一开始想先把primeFactors求出来，后来感觉没有必要还占内存，干脆找质因子的时候直接把helper求出来，也就是一个嵌套的vector，第一层是不同的质因子各有一个vec，第二层是相同的质因子形成的幂vec。这里也顺道把总的因数个数求出来了。
***这里注意tmpV不是每次都要往helper里放的，因此应该判断一下t是否不等于0，第一次99999827没过就是因为之前没注意每次都放然后啥都跑不出来***
    ```
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
    ```
* 然后就是求ans2数组了，发现只要把1放进去，然后遍历helper的每一个vec，每次新乘出来的数字再放到ans2里，循环就好了，因此写一个multiple函数来算完成，没想到代码出奇地少嘿嘿。其中multiple中先用临时数组tmp储存新算出来的数，要不直接往ans里放直接死循环了xs
    ```
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
    ```
4. 排序
* 最后就是排序了，然后是真的好懒不想写快排了，不知道看不到的样例大概是多少，其实可以优化一下排序的，小于15个元素用insertsort这样的，但是真的好懒QAQ甚至第一遍提交引用了<algorithm>里的sort函数，所以就只写了个[快排](https://blog.csdn.net/m0_58618795/article/details/126357919)，似乎是可以再优化的，不过AC了就没再写xs
    ```
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
    ```
5. 总结
* 感觉想明白了因式分解法怎么求是关键，输入输出排序等都是细节问题（也够让人抓狂了），第一次写一些做题笔记是希望一些错误不要再犯，一些用过的东西尽量记住，顺便记录一下心路历程。最后希望第二题讲了以后能顺利码出来QAQ。