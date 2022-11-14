#ifndef TREE_H
#define TREE_H
#include"std_lib_facilities.h"

struct Node
{
    string code;
    vector<Node*> children;
    bool flag=false;
};

class Tree{
private:
    Node* root;
    string ini_str;
    void buildTree(Node*& node,int& start);
    string getCode(Node*& node);
public:
    Tree(string input);
    void buildTree();
    string getCode();
    bool isValid();
};

Tree::Tree(string input)
{
    root=new Node();
    ini_str=input;
}

void Tree::buildTree()
{
    int start=1;
    buildTree(root,start);
}

void Tree::buildTree(Node*& node,int& start)
{
    while(start<ini_str.length()-1)
    {
        if(ini_str[start]=='1')
        {
            Node* tmp=new Node();
            node->children.push_back(tmp);
            start++;
            buildTree(node->children.back(),start);
        }
        else
        {
            start++;
            return;
        }
    }
}

string Tree::getCode()
{
    return getCode(root);
}

string Tree::getCode(Node*& node)
{
    if(!node)
        return "";
    vector<string> childrenCode;
    for(auto& it:node->children)
    {
        childrenCode.push_back(getCode(it));
    }
    sort(childrenCode.begin(),childrenCode.end());
    for(auto& it:childrenCode)
    {
        node->code+=it;
    }
    node->code='1'+node->code+'0';
    return node->code;
}

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

#endif