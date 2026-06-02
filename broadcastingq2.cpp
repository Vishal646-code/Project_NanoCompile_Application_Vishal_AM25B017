#include<bits/stdc++.h>
using namespace std;
std::optional<std::vector<int64_t>>
broadcastShape(const std::vector<int64_t>& a,
const std::vector<int64_t>& b){
    for(auto x: a) if(x<=0) return nullopt;
    for(auto x: b) if(x<=0) return nullopt;
    int m= a.size(), n= b.size();
    int maxdim= max(m,n);
    vector<int64_t> res(maxdim);
    int i=m-1, j=n-1, k=maxdim-1;
    while(i>=0 && j>=0){
        if(a[i]==b[j]) res[k]= a[i];
        else if(a[i]==1) res[k]= b[j];
        else if(b[j]==1) res[k]= a[i];
        else return nullopt;
        i--; j--; k--;
    }
    while(k>=0){
        res[k]= (i>=0) ? a[i--] : b[j--];
        k--;
    }
    return res;
}
void printShape(const optional<vector<int64_t>>& shape){
    if(!shape){
        cout << "nullopt";
        return;
    }

    for(auto x : *shape)
        cout<<x<<" ";
} 
int main(){
    auto shape1= broadcastShape({2, 3}, {2, 3});
    auto shape2= broadcastShape({2, 3, 4}, {3, 4});
    auto shape3= broadcastShape({6, 8}, {6});
    cout<<"Broadcast shapes :\n";
    printShape(shape1); cout << "\n";
    printShape(shape2); cout << "\n";
    printShape(shape3); cout << "\n";
}