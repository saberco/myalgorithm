#include"sort_all.h"
using namespace std;



int main(){
    sort_bucket sort_me;
    vector<int> input = {2,3,5,1,4,7,9,8,6};
    for(int i=0;i<input.size();++i){
        cout<<input[i]<<" ";
    }
    cout<<endl;
    sort_me.arr = input;
    sort_me.sort_arr();

    return 0;
}