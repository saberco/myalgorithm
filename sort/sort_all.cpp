
#include"sort_all.h"

void swapij(int& i,int& j){
    int tmp = i;
    i = j;
    j = tmp;
}

//冒泡排序实现
void sort_maopao::sort_arr(){
    std::vector<int> tmp = this->arr;
    int n = tmp.size();
    for(int i=0;i<n;++i){
        for(int j = i;j<n;++j){
            if(tmp[j]<tmp[i]){
                swapij(tmp[i],tmp[j]);
            }
        }
    }
    for(int i=0;i<tmp.size();++i){
        std::cout<<tmp[i]<<" ";
    }
    std::cout<<std::endl;
}

//选择排序实现
void sort_xuanze::sort_arr(){
    std::vector<int> tmp = this->arr;
    int n = tmp.size();
    for(int i=0;i<n;++i){
        int min_num = i;
        for(int j=i;j<n;++j){
            min_num = tmp[j] < tmp[min_num] ? j : min_num;
        }
        swapij(tmp[i],tmp[min_num]);
    }
    for(int i=0;i<tmp.size();++i){
        std::cout<<tmp[i]<<" ";
    }
    std::cout<<std::endl;
}

//插入排序实现
void sort_charu::sort_arr(){
    std::vector<int> tmp = this->arr;
    int n = tmp.size();
    for(int i=1;i<n;++i){
        int key = tmp[i];   //待排序的第一个
        int j = i-1;    //已排好序的前j个
        while(j>=0&&key<tmp[j]){
            //从后向前比较，如果比待排序的大，就把后边的用前边的代替
            tmp[j+1] = tmp[j];
            j--;
        }
        //找到合适的位置插入，在第j个后插入
        tmp[j+1] = key;
    }
    for(int i=0;i<tmp.size();++i){
        std::cout<<tmp[i]<<" ";
    }
    std::cout<<std::endl;

}











