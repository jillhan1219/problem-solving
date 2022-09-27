## 高斯消去法
### 总体思路
* 要利用高斯消去法需要先把给定的奇葩输入转换成增广矩阵。对于这个奇葩输入已经懒得吐槽了，今天了解到正则表达式或许可以写得简单一些，可以学一学。这里还是用的最常规的下头方法。
* 基于输入，要确定矩阵首先需要确定二维数组的大小，及有几个变量，这样写出来的矩阵可以判断解的情况。而变量是**string**类型，不同的方程有相同的变量，很自然想到了`map`，而且输出要求按照字典序输出，那么直接利用`map`而不是`unordered_map`并且让变量作**key**，那么**value**是什么呢？因为确定变量以后需要确定变量的具体位置以生成矩阵，同时要记录系数，而矩阵的变量顺序即**col**即为map中key的顺序，而**row**取决于这是**第几个**方程，因此value为一个**vector**，其中放入`pair<int,double>`，前者储存第几个方程，**cntV**计数即可（有效方程个数），后者为系数。
* 之后生成矩阵。统计key的数目、开数组并全部初始化为0，然后对应位置输入数字就好了。
* 化简矩阵，这里把解情况的判断也放在这里。
### 输入
* 还是老方法，ostringstream的ss输入数字，index来判断情况。不一样的是加了一个`validEquation()`函数来判断是否合法。不合法直接跳过这一行。因为要统计输入的总字符数，还需要一个**cnt**来计数，这里是总行数。
* 但是输入合法性的判断还是很复杂的，要考虑常数在等号左边、出现二次项等情况，因此需要区域判断。
    * 读到数字需要一直读到**乘号**，否则报错；读到以后紧接着读变量，否则报错；因为最多两位数字，所以利用**cnt**计数，如果小于0则说明有其他符号。读入变量后放入set，可以保证每一个等式中只有一个相同的变量，否则报错。
    * 读到字母同上操作，这里只是检测合法性因此不用考虑系数问题
    * 如果是`+ -`的话跳过即可
    * 读到等号接着往后读数字，出现其他任何符号报错
```
bool MyClass1::validEquation(string& line){
    int len=line.length();
    int i=0;
    unordered_set<string> seen;
    while(i<len){
        char ch=line[i];
        if(isdigit(ch)){
            int j=i+1;
            while (line[j]!='*')
            {
                if(isdigit(line[j])||line[j]=='.')
                    ++j;
                else return false;
            }
            string variable;
            if(islower(line[++j])) {variable+=line[j];}
            else return false;

            j++;
            int cnt=2;
            while(isdigit(line[j])){
                cnt--;
                variable+=line[j];
                ++j;
            }
            if(cnt<0) return false;
            if(seen.count(variable)) return false;
            seen.insert(variable);
            i=j;
        }
        else if(islower(ch)){
            string variable;
            variable+=ch;
            int j=i+1;
            int cnt=2;
            while(isdigit(line[j])){
                cnt--;
                variable+=line[j];
                ++j;
            }
            if(cnt<0) return false;
            if(seen.count(variable)) return false;
            seen.insert(variable);
            i=j;
        }
        else if(ch=='-'||ch=='+') i++;
        else if(ch=='=') {
            int j=i+1;
            if(line[j]=='-') j++;
            while(j<len){
                if(isdigit(line[j])||line[j]=='.') ++j;
                else return false;
            }
            i=j;
        }
        else return false;
    }
    return true;
}
```
### 输出
* 统计字符数目还是利用ostringstream。这里特别注意截断函数，因为`convert<<fixed<<setprecision(4)`是四舍五入而不是直接截断其中`floor`需要引用头文件`#include<cmath>`
```
double MyClass1::keep(double x)
{
    int flag=x>=0;
    if(flag) return floor(x * 10000.000f) / 10000.000f;
    else return -(floor(abs(x) * 10000.000f+0.1 ) / 10000.000f);
}
convert<<fixed<<setprecision(4)<<keep(tmp)<<"\n";
```
### 求解
* 参考[洛谷P2455](https://www.luogu.com.cn/problem/solution/P2455)，其中特别注意判断是否为0时因为误差因此将`matrix[maxi][k]==0`改为`matrix[maxi][k]<1e-9`
* 题目要求利用`try`和`catch`机制，因此将解输入convert一步放入try中，先判断解的情况。
```
void MyClass1::solve(ostringstream& convert){
    int nwline=0;
    for(int k=0;k<variableNum;++k){
        int maxi=nwline;
        for(int i=nwline+1;i<variableNum;++i){
            if(abs(matrix[i][k])>abs(matrix[maxi][k]))
                maxi=i;
        }
        if(abs(matrix[maxi][k])<1e-9)
            continue;
        for(int j=0;j<variableNum+1;++j)
            swap(matrix[nwline][j],matrix[maxi][j]);
        for(int i=0;i<variableNum;++i){
            if(i==nwline)
                continue;
            double mul=matrix[i][k]/matrix[nwline][k];
            for(int j=k+1;j<variableNum+1;++j)
            matrix[i][j]-=matrix[nwline][j]*mul;
        }
        ++nwline;
    }
    try{
        if(nwline<variableNum){
            while(nwline<variableNum){
                if(matrix[nwline++][variableNum]!=0)
                    throw 1;
            }
            throw '2';
        }
        int i=0;
        for(auto& equ:equations){
            convert<<equ.first<<":";
            double tmp=matrix[i][variableNum]/matrix[i][i];
            convert<<fixed<<setprecision(4)<<keep(tmp)<<"\n";
            i++;
        }
    }
    catch(int e1){
        convert<<"error1"<<"\n";
    }
    catch(char e2){
        convert<<"error2"<<"\n";
    }
}
```
### 总结
* 输入输出还是一如既往的耗时，其实一开始是没有思路的，上课讲的高斯消元约等于没讲，看到洛谷上大佬的代码才有了思路，于是就想办法把输入转换成矩阵就好，因此又考虑到了map里面放变量和vector，vector里面又放pair的骚操作，在此感叹`auto&:`用起来是真的方便。其实整体写下来感觉还比较顺利，除了最后卡了一个测试集。当时以为是没检查数字在左边的非法输入，结果后来才知道是考截断函数。换句话来说判断非法函数的时候只要检测有没有非法字符这个作业就过了，真卡了好大一bug。代码中很大概率还有bug，写markdown的时候发现漏了一步set的插入而没有将`x1+2*x1=2`判为非法。不知道其他bug会不会有机会被修正。叹气。只能说好歹作业分拿到了~