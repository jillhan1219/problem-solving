 
//
// This is example code from Chapter 7.7 "Recovering from errors" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "std_lib_facilities.h"

/*
    Simple calculator

    Revision history:

        Revised by Bjarne Stroustrup May 2007
        Revised by Bjarne Stroustrup August 2006
        Revised by Bjarne Stroustrup August 2004
        Originally written by Bjarne Stroustrup
            (bs@cs.tamu.edu) Spring 2004.

    This program implements a basic expression calculator.
    Input from iss; output to cout.

    The grammar for input is:

    Statement:
        Expression
        Print
        Quit

    Print:
        ;

    Quit:
        q

    Expression:
        Term
        Expression + Term
        Expression - Term
    Term:
        Primary
        Term * Primary
        Term / Primary
        Term % Primary
    Primary:
        Number
        ( Expression )
        - Primary
        + Primary
    Number:
        floating-point-literal


        Input comes from iss through the Token_stream called ts.
*/

istringstream iss;          // use iss instead of cin to get expression
//------------------------------------------------------------------------------

const char number = '8';    // t.kind==number means that t is a number Token
const char quit   = 'q';    // t.kind==quit means that t is a quit Token
const char print  = ';';    // t.kind==print means that t is a print Token
const string prompt = "> ";
const string result = "= "; // used to indicate that what follows is a result

//------------------------------------------------------------------------------

class Token {
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
    Token_stream();   // make a Token_stream that reads from iss
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
    void ignore(char c);      // discard tokens up to an including a c
private:
    bool full;        // is there a Token in the buffer?
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

Token Token_stream::get() // read characters from iss and compose a Token
{
    if (full) {         // check if we already have a Token ready
        full=false;
        return buffer;
    }

    char ch;
    iss >> ch;          // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case quit:
    case print:
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '!':
        return Token(ch); // let each character represent itself
    case '.':             // a floating-point literal can start with a dot
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':    // numeric literal
    {
        iss.putback(ch);// put digit back into the input stream
        double val;
        iss >> val;     // read a floating-point number
        return Token(number,val);
    }
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
    // c represents the kind of a Token
{
    // first look in buffer:
    if (full && c==buffer.kind) {
        full = false;
        return;
    }
    full = false;

    // now seach input:
    char ch = 0;
    while (iss>>ch)
        if (ch==c) return;
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback()

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()
double factorial();    // declaration so that primary() can call factorial()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':           // handle '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
    case number:
        return t.value;    // return the number's value
    case '-':
        return - factorial();
    case '+':
        return primary();
    default:
        error("primary expected");
    }
}

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// deal with !
bool isInt(double a)
{
	if(a-(int)a==0)
		return true;
	return false;
}

double factorial()
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
			ts.putback(t);
			return left;
		}
	}
}
//------------------------------------------------------------------------------


// deal with *, /, and %
double term()
{
    double left = factorial();
    Token t = ts.get(); // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':
            left *= factorial();
            t = ts.get();
            break;
        case '/':
            {
                double d = factorial();
                if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
        case '%':
            {
                int i1 = narrow_cast<int>(left);
                int i2 = narrow_cast<int>(term());
                if (i2 == 0) error("%: divide by zero");
                left = i1%i2;
                t = ts.get();
                break;
            }
        default:
            ts.putback(t);        // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch(t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------

void clean_up_mess()
{
    ts.ignore(print);
}

//------------------------------------------------------------------------------

map<string,vector<string>> expressions;

bool getIndex(string& input,int& start,string& index)
{
    index="";
    while(isspace(input[start]))
        start++;
    if(input[start]!='[')
        return false;
    else
    {
        while(true)
        {
            if(input[start]=='[')
            {
                start++;
                while(isspace(input[start]))
                    start++;
            }
            else if(isspace(input[start]))
            {
                int j=start;
                while(isspace(input[j]))
                    j++;
                if(input[j] == ']')
                    start=j;
                else
                {
                    while(start<=j)
                    {
                        index+=input[start];
                        start++;
                    }
                }
            }
            else if(input[start]==']')
            {
                start++;     
                return true;
            }
            else
                index+=input[start++];
        }
    }
}


bool getExprn(string& input, int& start, string& exprn)
{
    exprn="";
    while(isspace(input[start]))
        start++;
    while(input[start]!=';')
    {
        if(isalpha(input[start]))
        {
            while(input[start]!='['&&input[start]!='q')
                start++;
            exprn="";
            return false;
        }
        if(isspace(input[start]))
        {
            int j=start;
            while(isspace(input[j]))
                j++;
            if(input[j] == ';')
                start=j;
            else
            {
                while(start<=j)
                {
                    exprn+=input[start];
                    start++;
                }
            }
            continue;
        }
        exprn+=input[start];
        start++;
    }
    exprn+=input[start++];    //add ; to the end
    while (isspace(input[start]))
        start++;
    if(input[start]=='['||input[start]=='q')
        return true;
    else
    {
        while(input[start]!='['&&input[start]!='q')
        start++;
        exprn="";
        return false;
    }
}

void getExpressions()
{
    string input;
    getline(cin,input);
    int len=input.length();
    if(input.find('q')>=len)
        input+='q';
    string index,exprn;
    int start=0;
    while(input[start]!='q')
    {
        bool flag_id,flag_ex;
        flag_id=getIndex(input,start,index);
        flag_ex=getExprn(input,start,exprn);
        if(flag_id)
            expressions[index].push_back(exprn);
    }
}

void calculate()
{
    for(auto& it_index:expressions)
    {
        for(auto it_exprn=it_index.second.begin();it_exprn!=it_index.second.end();)
        // use iterator for erase, cannot ++it_index as we might erase if it is invalid
        {
            iss.clear();
            iss.str(*it_exprn);
            while (iss)
            try {
                //cout << prompt;
                Token t = ts.get();
                while (t.kind == print) t=ts.get();    // first discard all "prints"
                if (t.kind == quit) return;        // quit
                ts.putback(t);
                double ans=expression();
                (*it_exprn).pop_back();
                *it_exprn+='=';
                if(isInt(ans))
                    *it_exprn+=to_string((int)ans);
                else
                {
                    ostringstream convert;
                    convert<<setprecision(6)<<ans;
                    *it_exprn+=convert.str();
                }
                it_exprn++;
                clean_up_mess();
                break;
                //cout << result << expression() << endl;
            }
            catch (exception& e) {
                //cout << e.what() << endl;        // write error message
                it_index.second.erase(it_exprn);   // delete the illegal expression
                clean_up_mess();
                iss.clear();
                break;   //不加break iss判断仍为true
            }
        }
    }
}

void display()
{
    string inquire;
    string in;
    if(getline(cin,in))
    {
        in='['+in+']';
        int start=0;
        getIndex(in,start,inquire);
        cout<<"["<<inquire<<"]";
        if(expressions.find(inquire)!=expressions.end())
        {
            sort(expressions[inquire].begin(),expressions[inquire].end());
            for(auto& it_exprn:expressions[inquire])
            {
                cout<<"\n"<<it_exprn;
            }
        }
    }
    else
    {
        for(auto it_index=expressions.begin();it_index!=expressions.end();++it_index)
        // 判断是否为第一个
        {
            if(it_index!=expressions.begin())
                cout<<"\n";
            cout<<"["<<it_index->first<<"]";
            sort(expressions[it_index->first].begin(),expressions[it_index->first].end());
            for(auto& it_exprn:it_index->second)
                cout<<"\n"<<it_exprn;
        }
    }
}

//------------------------------------------------------------------------------

int main()
try {
    getExpressions();
    calculate();
    display();
    //keep_window_open();    // cope with Windows console mode
    return 0;
}
//catch (runtime_error& e) {
    //cout << e.what() << endl;
    //keep_window_open("~~");
    //return 1;
//}
catch (...) {
    cout << "exception \n";
    keep_window_open("~~");
    return 2;
}

//------------------------------------------------------------------------------
 