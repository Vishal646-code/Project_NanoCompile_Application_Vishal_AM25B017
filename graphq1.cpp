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
    unordered_map<string, Operator*> operators;
    unordered_map<string, Tensor*> tensors;
};
int main(){
    return 0;
}