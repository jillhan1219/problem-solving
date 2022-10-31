# Huffman Code
## 总体思路
* 算法的原理这里就直接省略了，数据结构有讲过，但是实现的比较麻烦，记得是用数组然后通过编号来标记子节点和父节点，实在麻烦。
* 用`unordered_map`统计字符串中char对应的weight
* 利用`priority_queue`储存`Node*`，以实现以`weight`为先、`content`为后的小顶堆，因此建树的时候只需要每次取前两个元素，如果取完第一个元素队空那么直接将第一个元素赋值给`root`，但需要注意这里需要自定义排序函数。
* 最后生成哈夫曼编码。不用递归的树不是一棵好树。递归结束条件为既无左子也无右子，此时把他放入`map<string,string> code`中，即获得了字典序的编码
* 最后生成位长并输出即可。这里有个小小trick就是可以输出字符数目比之后不加新行，这样每次先给`convert`传一个新行，最后长度*-1*即可
```
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
```
## 具体实现
0. 准备工作
  * `Node`
```
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
```
  * `class cmp`
     * 这里注意是`>`号
     * 一开始的写法有些繁琐，自定义排序参考[这里](https://blog.csdn.net/Strengthennn/article/details/119078911?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166720659116782428693249%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166720659116782428693249&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-119078911-null-null.142^v62^pc_search_tree,201^v3^add_ask,213^v1^t3_esquery_v3&utm_term=priority_queue%E8%87%AA%E5%AE%9A%E4%B9%89%E6%8E%92%E5%BA%8F&spm=1018.2226.3001.4187) 
```
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
```
```
priority_queue<Node*,vector<Node*>,cmp> tree;
```
1. 建树
   * 这里注意将`char`转化为`string`，否则会报错
   * `priority_queue`中的`pop`只删除元素不取元素，其他用法看[这里](https://blog.csdn.net/weixin_36888577/article/details/79937886?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166720427816800180631294%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166720427816800180631294&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-79937886-null-null.142^v62^pc_search_tree,201^v3^add_ask,213^v1^t3_esquery_v3&utm_term=priority_queue&spm=1018.2226.3001.4187)
```
void huffmanCode::buildTree(){
    for(auto& itr:input){
        Node* character=new Node(string(1,itr.first),itr.second);//注意转化为string
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
```
2. 生成编码
```
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
```