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

Planresult planmemory(vector<Tensor> &tensors){
    vector<Buffer> freebuffers;
    vector<pair<int, Buffer>> busybuffers;
    Planresult res;
    int nextbufferid= 1;
    sort(tensors.begin(), tensors.end(), [](const Tensor &a, const Tensor &b){
        return a.firstcreated < b.firstcreated;
    });

    for (auto &ten : tensors){
        // releasing expired buffers
        auto it= busybuffers.begin();
        while(it!= busybuffers.end() && it->first < ten.firstcreated){ // all those buffers whose resident has been consumed before this tensor is produced
            freebuffers.push_back(it->second);
            it= busybuffers.erase(it);
        }
        int best= -1;
        //best fit search
        for(int i=0; i<freebuffers.size(); i++){
            if(freebuffers[i].capacity >= ten.size){
                if(best == -1 || freebuffers[i].capacity < freebuffers[best].capacity){
                    best = i;
                }
            }
        }
        if(best != -1){
            Buffer reusedbuffer = freebuffers[best];
            ten.bufferid = reusedbuffer.id;
            ten.reusedfrom=  "Buffer "+ to_string(reusedbuffer.id);
            res.fragm += (reusedbuffer.capacity - ten.size);
            busybuffers.emplace_back(ten.lastused, reusedbuffer);
            freebuffers.erase(freebuffers.begin() + best);
        }
        else{
            Buffer newbuffer;
            newbuffer.id = nextbufferid++;
            newbuffer.capacity = ten.size;
            ten.bufferid= newbuffer.id;
            res.peakm += newbuffer.capacity; 
            busybuffers.emplace_back(ten.lastused, newbuffer);
        }
        sort(busybuffers.begin(), busybuffers.end(), [](const auto &a, const auto &b){
            return a.first < b.first;
        });
    }
    return res;
}
int main(){
    vector<Tensor> tensors= {{"A",24,1,2}, {"B",24,2,8}, {"C",32,3,5}, {"S",32,4,5},
    {"D",32,5,6}, {"E",32,6,7}, {"F",24,7,8}, {"G",24,8,9}, {"Y",24,9,9}};
    Planresult result= planmemory(tensors);
    cout<< "Tensor\tSize\tCreated\tLastUsed\tBuffer\tReused From\n";
    for(auto &t : tensors){
        cout<< t.name<<'\t'<< t.size<<'\t'<<t.firstcreated<<'\t'
        <<t.lastused<<'\t'<<t.bufferid<<'\t'<<t.reusedfrom<<'\n';
    }
    cout<< "Peak Memory: "<<result.peakm<<"KB"<<'\n';
    cout<< "Internal fragmentation: "<<result.fragm<<"KB"<<'\n';
    return 0;
}