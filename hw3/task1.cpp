#include "std_lib_facilities.h"

//------------------------------------------------------------------------------

static int cnt=0;

class Token{
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from ss
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
private:
    bool full {false};        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
    :full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)
    cnt++;

    switch (ch) {
    case ';':    // for "print"
    case 'q':    // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/':
        return Token(ch);        // let each character represent itself
    case '.':
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
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback() 

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    double d;
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
        d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");
            return d;
    case '8':            // we use '8' to represent a number
        return t.value;  // return the number's value
    default:
        error("primary expected");
    }
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = primary();

    while (true) {
        Token t = ts.get();        // get the next token from token stream
        switch (t.kind) {
        case '*':
            left *= primary();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            break;
        }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term

    while (true) {
        Token t = ts.get();        // get the next token from token stream
        switch (t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------

ostringstream output1,output2,output3;
//stringstream ss;

int main()
//{
    //int cnt=0;
    //string line;
    //while(getline(cin,line)){
        //ss<<line<<"\n";
    //}
    //cnt=ss.str().length()-1;
try
{
    double val=0;
    bool flag=false;
    while (cin) {
        Token t = ts.get();

        if (t.kind == 'q') {break;} // 'q' for quit
        if (t.kind == ';')        // ';' for "print now"
        {
            //cout << "=" << val << '\n';
            cnt++;
            if(!flag){
                output1 << "=" << val;
                flag=true;
            }
            else
                output1 <<"\n"<< "=" << val;
            continue;
        }
        else
            ts.putback(t);
        val = expression();
    }
    string tmp=output1.str();
    cout<<cnt<<":"<<tmp.length()<<"\n";
    cout<<tmp;
    return 0;
}
catch (exception& e) {
    //cout << "error: " << e.what() << '\n';
    while(cin.get()!=EOF) cnt++;
    output2 << "error: " << e.what() ;
    string tmp=output2.str();
    cout<<cnt-1<<":"<<tmp.length()<<"\n";
    cout<<tmp;
    return 1;
}
catch (...) {
    //cout << "Oops: unknown exception!\n";
    while(cin.get()!=EOF) cnt++;
    output3 << "Oops: unknown exception!";
    string tmp=output3.str();
    cout<<cnt-1<<":"<<tmp.length()<<"\n";
    cout<<tmp;
    return 2;
}
//------------------------------------------------------------------------------