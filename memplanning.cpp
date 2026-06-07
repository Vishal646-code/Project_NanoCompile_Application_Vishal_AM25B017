#include<bits/stdc++.h>
using namespace std;
struct Tensor{
    string name;
    int size;
    int firstcreated;
    int lastused;
    int bufferid= -1;
    string reusedfrom= "-";
};

struct Buffer{
    int id;
    int capacity;
};
struct Planresult{
    int peakm= 0;
    int fragm= 0;
};
int main(){
    return 0;
}