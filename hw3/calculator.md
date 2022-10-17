## 计算器总结
### error/try/catch
* 这一节需要好好总结一下报错机制了。
  1. error
    * 这里的`error`函数是std_lib_facilities库中所带，本质上为`throw`两种类型错误，其中`runtime_error()`为标准库[stdexcept](https://blog.csdn.net/qingdujun/article/details/75195061?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166567571516782427457796%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166567571516782427457796&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-75195061-null-null.142^v56^pc_search_v3,201^v3^add_ask&utm_term=stdexcept&spm=1018.2226.3001.4187)中定义的两种错误，因此因为main里所有的步骤都在`try`中，所以遇到异常以后马上跳出进入`catch`中，因此统计输入不能通过`get()`中的`cin`中来统计，具体处理方法见后。
    ```
      inline void error(const string& s)
      {
          throw runtime_error(s);
      }
    ```
    * 执行throw语句类似于执行返回语句，因为它也将终止函数的执行；但throw**不是**将控制权返回给**调用程序**，而是导致程序沿函数调用序列后退，直到找到**包含try块**的函数。程序将在该函数中寻找与引发的异常类型匹配的异常处理程序（位于try块的后面）
    * `catch`中的`e.what()`为`virtual const char *std::exception::what() const noexcept`
  2. try
    * try块标识其中特定的异常可能被激活的代码块，它后面跟一个或多个catch块。try块是由关键字try指示的，关键字try的后面是一个由花括号括起的代码块，表明需要注意这些代码引发的异常。
  3. catch
    * 执行完try块中的语句后，如果没有引发任何异常，则程序**跳过**try块后面的catch块，直接执行处理程序后面的第一条语句
    * catch块点类似于函数定义，但并不是函数定义。另外，当异常与该处理程序匹配时，程序将执行括号中的代码。
    * 这个程序中有一点棘手的是`q`的处理，如果按照原程序执行的话遇到第一个`;`后会直接计算下一个计算式`val=expression()`，因此盲猜正确的处理方式是`;`情况中加上一个`continue`，然后正常的输入输出放在`try`里的`while`后面就好了，感觉也没什么毛病。不过参考了cxx同学的处理感觉也挺简单的，可以把`q`的情况看作异常，然后在`get`中不和其他的字符一起处理，直接抛出一个空的`class quit{}`，然后再`catch`中捕获一下就好了~
    ```
    class quit{};

    Token Token_stream::get()
    {
        if (full) {       // do we already have a Token ready?
            // remove token from buffer
            full = false;
            return buffer;
        }

        char ch;
        is >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)
        switch (ch) {
        case ';':    // for "print"
        //case 'q':    // for "quit"
        case '(': case ')': case '+': case '-': case '*': case '/':
            return Token(ch);        // let each character represent itself
        case 'q': throw quit{};
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            is.putback(ch);         // put digit back into the input stream
            double val;
            is >> val;              // read a floating-point number
            return Token('8', val);   // let '8' represent "a number"
        }
        default:
            error("Bad token");
        }
    }

    catch(quit& q)
    {
        string res=os.str();
        cout<<cinlen<<":"<<res.size()<<endl;
        cout<<res;
        system("pause");
        return 0;
    }
    ```
### 统计输入字符串
* 如上文所说，因为输入过程中抛出错误后不会再输入，因此如果直接用int计数的话是很麻烦的，抛开单独输入的字符串，输入`double`类型的val的时候需要转化成字符串给一个string，再转化给istringstream，再输入，并且在catch中还需要继续统计没输入的字符串，还是挺麻烦的。不过也是可以过的，还是贴一下代码
```
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '9': case '8':
  {
      cin.putback(ch);         // put digit back into the input stream
      char tmp=cin.peek();
      string str;
      while((tmp>='0'&&tmp<='9')||tmp=='.')
      {
          tmp=cin.get();
          str+=tmp;
          tmp=cin.peek();
      }
      double val;
      istringstream ss(str);
      ss>>val;
      cnt+=str.length()-1;
      return Token('8', val);   // let '8' represent "a number"
  }
```
```
catch (exception& e) {
    //cout << "error: " << e.what() << '\n';
    while(cin.get()!=EOF) cnt++;
    output2 << "error: " << e.what() ;
    string tmp=output2.str();
    cout<<cnt-1<<":"<<tmp.length()<<"\n";
    cout<<tmp;
    return 1;
}
```
* 不过这个实在是太繁琐了哈哈，最好的方法肯定是不管啥情况先把输入统计出来，但是统计的输入还要接着用，于是考虑放到`istringstream ss`中，因为这个是由`istream`为基类派生过来的，所以直接把`cin`全部**替换**为`ss`就好了，具体做法是先放到字符串里然后再放到ss里，其实和上面输入val的步骤完全一样嘛，写的时候没想到还费好大劲QAQ
```
    string input;
    char ch;
    while((ch=cin.get())!='q') input+=ch;
    input.push_back('q');
    cinlen=input.size();
    is.clear();
    is.str(input);
```
### 总结
* 修改程序其实还是蛮费劲的，尤其是他这个程序的错误太过阴险，比如掉了`case 8:`和一堆`break`害我debug了好久......不过这个题收获比较多的就是异常处理和输入的问题，也算是有提升吧~