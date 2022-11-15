# 判断树的同构
## 思路
* 根据数字串建树，然后再生成排序的数字串，判断二者是否完全相同
## 注意点
### 1. 树合法性的判断
    * 初步的思路是直接用一个栈，碰到1入栈，碰到0弹栈。但是测试集9不过，询问TA后发现没考虑全，也就是说一棵树只能有一个root，像**1010**这种也不是一个合法的树。因此需要保证在弹栈过程里（除最后）栈不能为空。

```
bool Tree::isValid()
{
    stack<char> test;
    int len=ini_str.length();
    for(int i=0;i<len;++i)
    {
        if(ini_str[i]=='1')
            test.push('1');
        else
        {
            if(test.empty())
                return false;
            test.pop();
            if(test.empty()&&i<len-1)
                return false;
        }
    }
    if(!test.empty())
        return false;
    return true;
}
```
### 2. 关于建树和解码
* 注意题目为树而不是二叉树，第七关是考察多叉树。一开始全是按照二叉树来完成的，导致出现了一些致命错误。但其实是很好修改的，甚至修改以后比原来的实现还要简单。因为多叉树不确定会有多少孩子，所以每一个`node`自带一个`vector<Node*>`即可，建树的过程像里面插入，解码时递归解码，然后将其中元素排序并合并最后前后加上1，0