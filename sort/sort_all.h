
#ifndef __SORT_ALL_H__
#define __SORT_ALL_H__
#include<vector>
#include<iostream>
#include<cstring>
#include <stdexcept>
#include <limits>
#include<algorithm>
#include<iterator>

//冒泡排序类
class sort_maopao{
public:
    std::vector<int> arr;
public:
    void sort_arr();
    sort_maopao(){};
};

//选择排序类
class sort_xuanze{
public:
    std::vector<int> arr;
public:
    void sort_arr();
    sort_xuanze(){};   
};

//插入排序类
class sort_charu{
public:
    std::vector<int> arr;
public:
    void sort_arr();
    sort_charu(){};   
};

//希尔排序类
class sort_xier{
public:
    std::vector<int> arr;
public:
    void sort_arr();
    sort_xier(){};   
};

//归并排序类
class sort_guibin{
public:
    std::vector<int> arr;
public:
    void sort_arr();
    void merging(std::vector<int>& array,int front, int end);
    void mergeAll(std::vector<int>& array,int front, int mid, int end);
    sort_guibin(){};   
};

//快速排序类
class sort_quick{
public:
    std::vector<int> arr;
public:
    void sort_arr();
    void quick(int left,int right,std::vector<int>& array);
    sort_quick(){};   
};

//堆排序类
class sort_heap{
public:
    std::vector<int> arr;
public:
    void sort_arr();
    void heapSort(std::vector<int>& array,int len);
    void adjust(std::vector<int>& array,int len,int index);
    sort_heap(){};   
};

//计数排序类（0-100数最好的排序算法）
class sort_calculator{
public:
    std::vector<int> arr;
public:
    void sort_arr();
    sort_calculator(){};   
};

//桶排序
class sort_bucket{
public:
    std::vector<int> arr;
    const int BUCKET_NUM = 10;
    struct ListNode{
        explicit ListNode(int i=0):mData(i),mNext(NULL){};
        int mData;
        ListNode* mNext;
    };
public:
    void sort_arr();
    ListNode* insert(ListNode* head,int val);
    ListNode* Merge(ListNode *head1,ListNode *head2);
    sort_bucket(){};   
};

#endif