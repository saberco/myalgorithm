
#ifndef __SORT_ALL_H__
#define __SORT_ALL_H__
#include<vector>
#include<iostream>

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

#endif