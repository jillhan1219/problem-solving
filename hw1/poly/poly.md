## polynomial总结
### 1. 输入
  * 这个输入实在是太搞我心态了，我甚至觉得这个输入用了我编写整个题一半的时间，真的是要多不规范有多不规范，给maple等software跪了。总体来说我把输入分成两部分来写，***第一部分*** 是读取第一位的coef和exp，而 ***第二部分*** 的规律是不管怎样是从符号位开始的。然后利用istringstream和string的index判断并且赋值给double，利用ch来吸收ss中不用的char。
    * 第一部分：又分为几种情况。如果是数字的话先`>>`给coef，然后判断有没有x，这里exp可以默认为0，有的话变成1，然后再往后读看有没有 **^**，有的话还需要再`>>`给exp。总之第一项是不在while里面插入的。
    * 第二部分：这里要规律很多，只会遇到 **+**、**-**、**^** 的情况，再正负号里再判断是可以直接>>给coef（此时x有系数），还是直接写±1，^的处理和第一部分相同。
  * ***其中要注意如果直接>>给coef的话，意味着这时是不确定这个数字在string里是多少位的，所以不能直接通过±index来定位，只能通过while循环，也就是说吸收完以后我们需要在x的位置或者（常数项的话）进入到下一项，这里一定要注意，第八个用例就是这么挂的。***
  * ps：多少是觉得这个输入写得很一般，代码量也不少，逻辑也很容易乱，不知道会不会讲更好的做法。
```
bool Polynomial::getPoly(){
   string str;
    getline(cin,str);
    istringstream ss(str);
    int ex=-1;
    double co=-1;
    int len=str.length(),i=0;
    char ch;
    if(str[i]>='0'&&str[i]<='9'){
        ss>>co;
        while(str[i]=='.'||(str[i]>='0'&&str[i]<='9'))
            i++;
        ex=0;
        if(str[i]=='x'){
            ss>>ch;
            ex=1;
            i++;
        }
    }
    else if(str[i]=='x'){
        co=1;
        ex=1;
        ss>>ch;
        i++;
    }
    if(str[i]=='^'){
        ss>>ch;
        ss>>ex;
        i+=2;
    }
    if(co!=-1&&ex!=-1){
        node tmp={co,ex};
        insertNode(tmp);
    }
    while(i<len){
        ex=1;
        switch (str[i])
        {
        case 'x':
            co=1.0;
            i++;
            ss>>ch;
            break;
        case '+':
            if(str[++i]=='x'){
                co=1.0;
                i++;
                ss>>ch;
                ss>>ch;
            }
            else{
                ss>>co;
                while(str[i]=='.'||(str[i]>='0'&&str[i]<='9'))
                    i++;
                if(str[i]=='x'){
                    i++;
                    ss>>ch;
                }
                else
                    ex=0;
            }
            break;
        case '-':
            if(str[++i]=='x'){
                co=-1.0;
                i++;
                ss>>ch;
                ss>>ch;
            }
            else{
                ss>>co;
                while(str[i]=='.'||(str[i]>='0'&&str[i]<='9'))
                    i++;
                if(str[i]=='x'){
                    i++;
                    ss>>ch;
                }
                else
                    ex=0;
            }
            break;
        case '^':
            break;
        default:
            return false;
        }
        if(str[i]=='^'){
            ss>>ch;
            ss>>ex;
            i+=2;
        }
        node tmp={co,ex};
        insertNode(tmp);
    }
    return true;
}
```
### 2. 化简
* 开始的思路是插入的同时直接化简，而且很自然就想到了用map，直接用exp做key然后降序排序，插入的时候检查是否含有这个key。其实感觉这个思路完全可以行。后来网上看到了用[vector<double,int>](https://blog.csdn.net/BAI20010904/article/details/123156879)来实现的除法，于是考虑到vector可以直接sort，决定用vector。然后问题就出现了。首先人家那个是直接化简完的，此题如果全部插入后再化简要remove，然后vector的remove效率太低，遂改用list。完成自己的cmp函数后，发现sort位置报错，查了大量的资料才明白list不能直接调用algorithm里的sort，需要调用list自带的sort。卒。![](2022-09-20-23-47-41.png)
* 排序后的化简参考了[这个](https://www.docin.com/p-634840147.html)的思路。第一遍写的时候每一遍都递增了it，结果发现如果正好合并的话还递增那么it和it2内容相同，但是如果直接`erase()`掉it2就不能定位到下一个了，又面向csdn，遂发现 [list自带的erase返回下一个iterator](https://blog.csdn.net/han_hhh/article/details/81153095?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166367639816800182770893%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166367639816800182770893&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-81153095-null-null.142^v48^pc_rank_34_queryrelevant25,201^v3^add_ask&utm_term=list%E7%9A%84erase&spm=1018.2226.3001.4187)，问题解决，但又卒。
```
bool cmp(node& a,node& b){
    return a.exp>b.exp;
}
void Polynomial::mySort(){
    poly.sort(cmp);
}

void Polynomial::simplify(){
    auto it2=++poly.begin();
    auto it=poly.begin();
    while(it2!=poly.end()){
        if((*it).exp==(*it2).exp){
            (*it).coef+=(*it2).coef;
            it2=poly.erase(it2);
        }
        else{
            it2++;
            it++;
        }
    }
}
```
### 3. 乘除法
   * 反而感觉这里不是很难，这里需要实现除法的话需要一个substract和multiply，但其实乘法不是严格意义上的乘法，因为只需要乘一项就好。但是需要注意减法若出现有一个iterator没有到end的话需要单独复制到ans里（被减的没完）或者取反放到ans里（减的没完）。
```
Polynomial sub(Polynomial& beSub,Polynomial& sub){
    Polynomial ans;
    node tmp;
    auto it1=beSub.poly.begin();
    auto it2=sub.poly.begin();
    while(it1!=beSub.poly.end()&&it2!=sub.poly.end()){
        if((*it2).exp==(*it1).exp){
            tmp.coef=(*it1).coef-(*it2).coef;
            tmp.exp=(*it1).exp;
            if(tmp.coef!=0){
                ans.insertNode(tmp);
            }
            it1++;
            it2++;
        }
        else if((*it2).exp>(*it1).exp){
            tmp.coef=-(*it2).coef;
            tmp.exp=(*it2).exp;
            ans.insertNode(tmp);
            it2++;
        }
    }
    if(it1!=beSub.end()){
        while(it1!=beSub.end()){
            node temp=*it1;
            ans.insertNode(temp);
            it1++;
        }
    }
    if(it2!=sub.end()){
        while(it2!=sub.end()){
            node temp;
            temp.coef=-(*it2).coef;
            temp.exp=-(*it2).exp;
            ans.insertNode(temp);
            it2++;
        }
    }
    return ans;
}
Polynomial mul(Polynomial &bemul,node &mul){
    Polynomial ans;
    for(auto it=bemul.poly.begin();it!=bemul.poly.end();++it){
        node tmp;
        tmp.coef=(*it).coef*mul.coef;
        tmp.exp=(*it).exp+mul.exp;
        ans.insertNode(tmp);
    }
    return ans;
}
```
   * 除法中结束的标志为被除数的第一项指数大于除数的第一项指数 ***或者*** 被除数的iterator迭代到最后。写的过程中发现其实除数的iterator一直都在第一个。 **这里注意mul中不要返回除数的引用**，第一遍写为了节约空间但是发现除数就被修改了。
```
pair<Polynomial,Polynomial> div(Polynomial& bedi,Polynomial& di){
    Polynomial ans;//商
    Polynomial rem;//余数
    node mu;//乘数
    Polynomial d;//除数
    rem=bedi;
    auto it1=rem.begin();
    auto it2=di.begin();
    while ((it1!=rem.end())&&((*it1).exp>=(*it2).exp))
    {
        /* code */
        mu.exp=(*it1).exp-(*it2).exp;
        mu.coef=(*it1).coef/((*it2).coef);
        ans.insertNode(mu);
        d=mul(di,mu);
        rem=sub(rem,d);
        it1=rem.begin();
    }
    return make_pair(ans,rem);
}
```
### 4. 输出
   * 顺道把error输出放到这里了。一开始用例没看全，发现自己完全漏写了除数为0的情况，后来又想到如果除数化简完也为0的话也是error情况，于是干脆把这一步判断放到除数化简完来写而不是`getpoly`中来写。这里要提到输入中的`switch`中的`^`判断就是为了避免当作其他符号直接返回false报错的。
   * 其中输出仍然用ostringstream，利用`convert<<fixed<<setprecision<<num` 可以固定位数。需要注意如果第一项输出为整数时没有+号，因此第一个元素单独处理。
   * 这里第10题似乎还有截断的问题，研究后再来写，先贴代码。
```
void Polynomial::printPoly(ostringstream& convert){
    auto it=poly.begin();
    if(it==poly.end()){
        convert<<fixed<<setprecision(4)<<0.0000;
        return;
    }
    for(;it!=poly.end();++it){
        if((*it).coef>0&&(it!=poly.begin())){
            convert<<'+';
        }
        convert<<fixed<<setprecision(4)<<keep((*it).coef);
        if((*it).exp>0){
            convert<<'x';
            if((*it).exp>1){
                convert<<'^'<<(*it).exp;
            }
        }
    }
}
``` 
### 5. class语法问题
* 这里暴毙。因为很久没写`.h .cpp`加上vscode奇葩的引用，语法上就浪费了好多时间。这里总结一下。
    * 首先`.h`的头文件
    ```
    #ifndef POLYNOMIAL_H
    #define POLYNOMIAL_H

    #endif
    ```
    * 然后是文件之间的引用关系，但是vscode就比较奇怪，要么写在`main`里写`#include"class.cpp"`，要么在`class.cpp`里写`#include main.cpp`，并且前者只能成功编译`main`，后者只能成功编译`class.cpp`。`.h`的引用与图一样。![](2022-09-20-23-49-55.png)
* 这里再记录一下报错，避免下次死得太惨。
    * 这样，就是没有编译`class.cpp`，需要`main.cpp`引用一下。![](2022-09-20-23-53-26.png)
    * 这样，找不到main函数，需要上述两种方法引用一下。![](2022-09-20-23-55-05.png)
    * 还有生成任务终止的时候记得去看一眼终端。
    * 还有oj的话如果**SMF**自己不写的话不要放个空的在上面，会显示重定义。
### 6. 心德
* 心德？人要裂开了。compile+link浪费了太多时间，有一些报错根本不知道咋解决。其实开始debug以后效率就高了，前期写代码的时候因为语法错误tab补全功能无了导致代码写的特难受，总之就是感觉写的过程很不顺利，最后终于想明白输入的问题才把8过了。大物直接没有听，明天还要补课补作业，现在0:01，希望不要每周一个400行的programming作业了，年纪大了真的顶不住了，哭哭。