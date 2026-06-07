#include<bits/stdc++.h>
using namespace std;

int next2power(int n){
    int p=1;
    while(p<n) p*=2;
    return p;
}

//Function to fill the array with 0's until the size becomes a power of 2
vector<int> fillarray(const vector<int> &arr){
    vector<int> fillarr= arr;
    int target= next2power(arr.size());
    while(fillarr.size() < target) fillarr.push_back(0);
    return fillarr;
}

void upsweepworker(vector<int> &arr, int step, int st, int end){
    int n= arr.size();
    for(int idx= st; idx<end; idx++){
        int i= (idx+1)*step -1;
        arr[i]+= arr[i- step/2];
    }
}
void downsweepworker(vector<int> &arr, int step, int st, int end){
    int n=arr.size();
    for(int idx=st; idx<end; idx++){
        int i= (idx+1)*step -1;
        int temp = arr[i- step/2];
        arr[i- step/2] = arr[i];
        arr[i] += temp;
    }
}
void parupsweep(vector<int> &fillarr){
    int n= fillarr.size();
    for(int step=2; step<=n; step*=2){
        //We shall use 4 threads.
        int totupdates= n/step;
        int chunk= (totupdates+3)/4;
        thread t1(upsweepworker, ref(fillarr), step, 0, min(chunk, totupdates));
        thread t2(upsweepworker, ref(fillarr), step, min(chunk, totupdates), min(2*chunk, totupdates));
        thread t3(upsweepworker, ref(fillarr), step, min(2*chunk, totupdates), min(3*chunk, totupdates));
        thread t4(upsweepworker, ref(fillarr), step, min(3*chunk, totupdates), totupdates);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }
}
void pardownsweep(vector<int> &fillarr){
    int n= fillarr.size();
    fillarr[n-1]=0;
    for(int step=n; step>=2; step/=2){
        int totupdates= n/step;
        int chunk= (totupdates+3)/4;
        thread t1(downsweepworker, ref(fillarr), step, 0, min(chunk, totupdates));
        thread t2(downsweepworker, ref(fillarr), step, min(chunk, totupdates), min(2*chunk, totupdates));
        thread t3(downsweepworker, ref(fillarr), step, min(2*chunk, totupdates), min(3*chunk, totupdates));
        thread t4(downsweepworker, ref(fillarr), step, min(3*chunk, totupdates), totupdates);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }
}
int main(){
    vector<int> arr= {1,2,3,4,5};
    //parallel prefix sum execution
    vector<int> fillarr= fillarray(arr);

    //upsweep at each level
    parupsweep(fillarr);
    //downsweep at each level
    pardownsweep(fillarr);
    vector<int> parsum(arr.size());
    for(int i=0; i<arr.size(); i++){
        parsum[i]= fillarr[i]+ arr[i];
    }
    
    for(auto x: parsum) cout<< x<<" ";
    return 0;
}