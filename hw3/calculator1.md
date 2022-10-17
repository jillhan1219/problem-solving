## calculator完善
### 原始程序bug的修改
* 关于几个bug这里就不再赘述了，代码中已经注释过了，除了掉了一个构造函数，剩下几个bug还是比较难de的，第一关即使代码不是很理解debug以后也可以过
### 关于阶乘的实现
* 第二关才是在代码的理解上修改代码，第一次觉得上课讲的东西有用因为表达式的**文法结构**帮助你理解运算的先后顺序。下文中第几层为**从下到上**的排序。
  1. '+' '-' 
  * 第四层`expression()`
  * 运算顺序最低，因此其他计算完成以后再运算加减，在第四层`expression()`中处理，涉及值计算调用的均为第三层`term()`
  2. '*' '/' 
  * 第三层`term()`
  * 处理完阶乘以后处理，因此在第三层`term()`中处理，涉及值调用的均来自第二层`primary1()`
  3. !
  * 第二层`primary1()`
  * `get()`里添加`!`的处理
  * 处理完括号以后处理，涉及值调用的均来自第一层`primary()`
  * 这里要注意关于阶乘的非法情况的判断，即若`left`为负数或者小数的情况则报错，因此添加判断是否为整数的函数，原理为**截断以后作差判断是否为0**
```
bool isInt(double a)
{
	if(a-(int)a==0)
		return true;
	return false;
}

double primary1()
{
	double left=primary();
	Token t=ts.get();
	while(true)
	{
		if(t.kind=='!')
		{
			if(left<0||(!isInt(left)))
				error("i!: invalid factorial");
			if(left==0)
				left=1;
			for(int i=left-1;i>0;i--)
				left*=i;
			t=ts.get();
		}
		else
		{
			ts.unget(t);
			return left;
		}
	}
}
```
  4. ()和首个-号
  * 第一层`expression()`
  * 括号的处理没有变化，递归调用`expression()`即可
  * 第一个**负号**的处理要特别注意，因为他的运算级是在阶乘以后的，也就是处理`-3！`这种情况，因为这种情况是不报错的，如果不修改源代码这种情况会报错，因为直接调用的`primary()`。其实想明白了很好改，但是还是很难注意。一开始想了好久这个位置是不是阶乘的顺序放错了，后来才意识到只需要把这里的`primary()`改成`primary1`()`就好了，如此小的改动程序的逻辑就对了，代码有时候确实很有意思~
```
	case '-':
		return -primary1();
```
### 总结
* 这文法顺序画明白还挺有用的哈哈哈
* 大屏写代码就是好爽~
* 而且发现直接用git及时暂存提交对于修改代码的作业特别有帮助
* 这次作业写的比较顺利，附上看到的一个[更完整的calculator](https://www.cnblogs.com/yueba/p/4088264.html)