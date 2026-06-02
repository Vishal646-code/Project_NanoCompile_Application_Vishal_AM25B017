#include<bits/stdc++.h>
using namespace std;
class Tensor; class Operator;
class Operator{
public:
    string type;
    int runtime=0;
    vector<Tensor*> inputs;
    Tensor* output = nullptr;
    map<string, string> attributes;
};
class Tensor{
public:
    string dtype;
    vector<int> shape;
    vector<Operator*> consumers;
    Operator* producer = nullptr;
};
//nodes represent operators, edges represent tensors
class Graph{
public:
    unordered_map<string, Operator> operators;
    unordered_map<string, Tensor> tensors;
};
int main(){
    Graph graph;
    //1st operator
    Operator &n1 = graph.operators["n1"];
    Tensor &a = graph.tensors["a"];
    Tensor &x = graph.tensors["x"];
    Tensor &w1= graph.tensors["w1"];
    n1.type = "Conv";
    n1.runtime = 8;
    n1.inputs = {&x, &w1};
    n1.output = &a;
    x.consumers.push_back(&n1);
    w1.consumers.push_back(&n1);
    a.producer = &n1;
    return 0;
}
