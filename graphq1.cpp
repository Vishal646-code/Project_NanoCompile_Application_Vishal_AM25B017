#include<bits/stdc++.h>
using namespace std;
class Tensor; class Operator;
class Operator{
public:
    string name;
    string type;
    int runtime=0;
    vector<Tensor*> inputs;
    Tensor* output = nullptr;
    map<string, string> attributes;
};
class Tensor{
public:
    string name;
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

int earextime(Operator* node, unordered_map<Operator*, int> &memo){
    if(memo.find(node) != memo.end()){
        return memo[node];
    }
    int maxtime=0;
    for(Tensor* input: node->inputs){
        if(input->producer != nullptr){
            int time= earextime(input->producer, memo);
            maxtime= max(maxtime, time);
        }
    }
    memo[node]= maxtime + node->runtime;
    return memo[node];
}

void printgraph(Graph &graph){
    for(auto &[tname, ten]: graph.tensors){
        if(ten.producer == nullptr) continue;
        for(Operator* consumer : ten.consumers){
            cout<< ten.producer->name << " -> "<< consumer->name<<'\n';
        }
    }
}
int main(){
    Graph graph;
    //1st operator
    Operator &n1 = graph.operators["n1"];
    Tensor &a = graph.tensors["a"];
    Tensor &x = graph.tensors["x"];
    Tensor &w1 = graph.tensors["w1"];
    n1.name= "n1";
    n1.type = "Conv";
    n1.runtime = 8;
    n1.inputs = {&x, &w1};
    n1.output = &a;
    a.name= "a";
    x.name="x";
    w1.name= "w1";
    x.consumers.push_back(&n1);
    w1.consumers.push_back(&n1);
    a.producer = &n1;

    //2nd operator
    Operator &n2 = graph.operators["n2"];
    Tensor &b = graph.tensors["b"];
    n2.name= "n2";
    n2.type = "ReLU";
    n2.runtime = 1;
    n2.inputs = {&a};
    n2.output = &b;
    b.name = "b";
    a.consumers.push_back(&n2);
    b.producer = &n2;
    
    //3rd operator
    Operator &n3 = graph.operators["n3"];
    Tensor &c = graph.tensors["c"];
    Tensor &w2 = graph.tensors["w2"];
    n3.name= "n3";
    n3.type = "Conv";
    n3.runtime = 10;
    n3.inputs = {&b, &w2};
    n3.output = &c;
    c.name= "c";
    w2.name= "w2";
    b.consumers.push_back(&n3);
    w2.consumers.push_back(&n3);
    c.producer = &n3;

    //4th operator
    Operator &n4 = graph.operators["n4"];
    Tensor &s = graph.tensors["s"];
    Tensor &w_skip = graph.tensors["w_skip"];
    n4.name= "n4";
    n4.type = "Conv";
    n4.runtime = 5;
    n4.inputs = {&x, &w_skip};
    n4.output = &s;
    s.name= "s";
    w_skip.name= "w_skip";
    x.consumers.push_back(&n4);
    w_skip.consumers.push_back(&n4);
    s.producer = &n4;

    //5th operator
    Operator &n5 = graph.operators["n5"];
    Tensor &d = graph.tensors["d"];
    n5.name= "n5";
    n5.type = "Add";
    n5.runtime = 1;
    n5.inputs = {&c, &s};
    n5.output = &d;
    d.name= "d";
    c.consumers.push_back(&n5);
    s.consumers.push_back(&n5);
    d.producer = &n5;

    //6th operator
    Operator &n6 = graph.operators["n6"];
    Tensor &e = graph.tensors["e"];
    n6.name= "n6";
    n6.type = "ReLU";
    n6.runtime = 1;
    n6.inputs = {&d};
    n6.output = &e;
    e.name= "e";
    d.consumers.push_back(&n6);
    e.producer = &n6;

    //7th operator
    Operator &n7 = graph.operators["n7"];
    Tensor &f = graph.tensors["f"];
    Tensor &scale = graph.tensors["scale"];
    n7.name= "n7";
    n7.type = "Mul";
    n7.runtime = 1;
    n7.inputs = {&e, &scale};
    n7.output = &f;
    f.name= "f";
    scale.name= "scale";
    e.consumers.push_back(&n7);
    scale.consumers.push_back(&n7);
    f.producer = &n7;

    //8th operator
    Operator &n8 = graph.operators["n8"];
    Tensor &y = graph.tensors["y"];
    Tensor &bias = graph.tensors["bias"];
    n8.name= "n8";
    n8.type = "Add";
    n8.runtime = 1;
    n8.inputs = {&f, &bias};
    n8.output = &y;
    y.name= "y";
    bias.name= "bias";
    f.consumers.push_back(&n8);
    bias.consumers.push_back(&n8);
    y.producer = &n8;
    
    unordered_map<Operator*, int> memo;
    cout<<"Earliest execution time of n8 is: "<<earextime(&n8, memo)<<"ms\n";
    printgraph(graph);
    return 0;
}
