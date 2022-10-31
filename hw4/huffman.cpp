//#include "stb_lib_facilities.h"
#include<string>
#include<iostream>
#include<map>
#include<queue>
#include<sstream>

using namespace std;

struct Node
{
    string content;
    int weight;
    Node* left,*right;
    string code="";
    Node(string str,int w,Node* l=nullptr,Node* r=nullptr){
        content=str;
        weight=w;
        left=l;
        right=r;
    }
};

class cmp{
public:
    bool operator()(const Node* a,const Node* b){
        //if(a->weight==b->weight)
        //{
            //if(a->content>b->content)
                //return true;
            //else
                //return false;
        //}
        //else if(a->weight>b->weight)
            //return true;
        //else
            //return false;
        return a->weight==b->weight?a->content>b->content:a->weight>b->weight;
    }

};

class huffmanCode{
private:
    string line;
    map<char,int> input;
    map<string,string> code;
    priority_queue<Node*,vector<Node*>,cmp> tree;
    Node* root;
    void getCode(Node* n);
public:
    int getWeight();
    void buildTree();
    void getCode();
    void display(ostringstream& convert);
};

int huffmanCode::getWeight(){
    getline(cin,line);
    int len=line.length();
    for(int i=0;i<len;++i){
        input[line[i]]++;
    }
    return len;
}

void huffmanCode::buildTree(){
    for(auto& itr:input){
        Node* character=new Node(string(1,itr.first),itr.second);
        tree.push(character);
    }
    while(true){
        Node* leftC=tree.top();
        tree.pop();
        if(tree.empty()){
            root=leftC;
            return;
        }
        Node* rightC=tree.top();
        tree.pop();
        Node* father=new Node((leftC->content+rightC->content),(leftC->weight+rightC->weight),leftC,rightC);
        tree.push(father);
    }
}

void huffmanCode::getCode(){
    getCode(root);
}
void huffmanCode::getCode(Node* n){
    if((!n->left)&&(!n->right)){
        code[n->content]=n->code;
        return;
    }
    if(n->left){
        n->left->code=n->code;
        n->left->code+="0";
        getCode(n->left);
    }
    if(n->right){
        n->right->code=n->code;
        n->right->code+="1";
        getCode(n->right);
    }
}

void huffmanCode::display(ostringstream& convert){
    int len=line.length();
    int cnt=0;
    for(int i=0;i<len;++i){
        cnt+=code[string(1,line[i])].length();
    }
    convert<<"\n"<<cnt;
    for(auto& itr:code){
        convert<<"\n"<<itr.first<<" "<<itr.second;
    }
}
int main(){
    huffmanCode hf;
    ostringstream convert;
    int len=hf.getWeight();
    hf.buildTree();
    hf.getCode();
    hf.display(convert);

    string result=convert.str();
    cout<<len<<":"<<result.length()-1;
    cout<<result;

    return 0;
}