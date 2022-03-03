
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

/***********希尔排序实现*****************/
void sort_xier::sort_arr(){
    std::vector<int> tmp = this->arr;
    int n = tmp.size();
    int gap = 1;
    //找到合适的增量序列个数
    while(gap<n/3){
        gap = gap * 3 + 1;
    }
    while(gap>=1){
        for(int i=gap;i<n;++i){
            for(int j=i;j>=gap&&tmp[j]<tmp[j-gap];j-=gap){
                swapij(tmp[j],tmp[j-gap]);
            }
        }
        gap /= 3;
    }
    for(int i=0;i<tmp.size();++i){
        std::cout<<tmp[i]<<" ";
    }
    std::cout<<std::endl;
}

/***********归并排序实现*****************/
void sort_guibin::sort_arr(){
    std::vector<int> tmp = this->arr;
    int n = tmp.size();
    sort_guibin::merging(tmp,0,n-1);
    for(int i=0;i<tmp.size();++i){
        std::cout<<tmp[i]<<" ";
    }
    std::cout<<std::endl;
}

void sort_guibin::merging(std::vector<int>& array,int front, int end){
    if(front>=end)return;
    int mid = (front+end)>>1;
    sort_guibin::merging(array,front,mid);
    sort_guibin::merging(array,mid+1,end);
    sort_guibin::mergeAll(array,front,mid,end);
}

void sort_guibin::mergeAll(std::vector<int>& array,int front, int mid, int end){
    std::vector<int> LeftSub(array.begin()+front, array.begin()+mid+1);
    std::vector<int> RightSub(array.begin()+mid+1, array.begin()+end+1);
    int idxLeft = 0, idxRight = 0;
    LeftSub.insert(LeftSub.end(),std::numeric_limits<int>::max());
    RightSub.insert(RightSub.end(),std::numeric_limits<int>::max());
    for(int i=front;i<=end;++i){
        if(LeftSub[idxLeft] < RightSub[idxRight]){
            array[i] = LeftSub[idxLeft];
            idxLeft++;
        }else{
            array[i] = RightSub[idxRight];
            idxRight++;
        }
    }
}
/***********快速排序实现*****************/
void sort_quick::sort_arr(){
    std::vector<int> tmp = this->arr;
    int n = tmp.size();
    sort_quick::quick(0,n-1,tmp);
    for(int i=0;i<tmp.size();++i){
        std::cout<<tmp[i]<<" ";
    }
    std::cout<<std::endl;
}

void sort_quick::quick(int left,int right,std::vector<int>& array){
    if(left>=right)return;
    int i,j,base;
    i = left;
    j = right;
    base = array[left];//   取最左的为基数（挖坑）
    while(i<j){
        while(array[j]>=base && i<j){
            j--;
        }//从右往左找到一个比base小的数
        if(i<j){
            array[i++]=array[j];//把这个数填入给第一个元素，并且把i++
        }//交换这两个数
        while(array[i]<=base && i<j){
            i++;
        }//从左往右找到一个比base大的数
        if(i<j){
            array[j--]=array[i];//把这个数填入给第j个元素，并且把j--
        }
    }
    array[i] = base;//基准归位（填坑）
    quick(left, i-1, array);//左边
    quick(i+1, right, array);//右边
}

/***********堆排序实现*****************/
void sort_heap::sort_arr(){
    std::vector<int> tmp = this->arr;
    int n = tmp.size();
    sort_heap::heapSort(tmp, n);
    for(int i=0;i<tmp.size();++i){
        std::cout<<tmp[i]<<" ";
    }
    std::cout<<std::endl;
}

void sort_heap::adjust(std::vector<int>& array,int len,int index){
    int left = 2 * index + 1;//index左节点
    int right = 2 * index + 2; //index右子节点

    int maxIdx = index;
    if(left<len && array[left]>array[maxIdx])maxIdx = left;
    if(right<len && array[right]>array[maxIdx])maxIdx = right;//maxIdx是这三个数中最大的数的下标
    //如果有更新maxIdx，那么进行交换，把大数换到index上
    if(maxIdx!=index){
        swapij(array[maxIdx], array[index]);
        sort_heap::adjust(array,len,maxIdx);//继续调整
    }
}

void sort_heap::heapSort(std::vector<int>& array,int len){
    //构建大顶堆
    for(int i = len/2 -1 ;i>=0;--i){//从最后一个非叶子节点开始，固定为长度/2-1
        sort_heap::adjust(array, len, i);
    }

    for(int i=len-1;i>=1;--i){
        swapij(array[0],array[i]);//把最大的数放到末尾
        adjust(array,i,0);
    }
}

//计数排序类实现
void sort_calculator::sort_arr(){
    std::vector<int> tmp = this->arr;
    int n = tmp.size();
    //确定最大值
    int max = *max_element(tmp.begin(),tmp.end());
    std::vector<int> data(max+1,0);
    //统计各数出现次数
    for(auto &num : tmp){
        ++data[num];
    }
    //进行排序,统计次数是几就输出几次
    int index = 0;
    for(int i=0;i<=max;++i){
        for(int j=0;j<data[i];++j){
            tmp[index++] = i;
        }
    }
    for(int i=0;i<tmp.size();++i){
        std::cout<<tmp[i]<<" ";
    }
    std::cout<<std::endl;
}

//桶排序实现

sort_bucket::ListNode* sort_bucket::insert(ListNode* head,int val){
        ListNode dummyNode;
        ListNode *newNode = new ListNode(val);
        ListNode *pre,*curr;
        dummyNode.mNext = head;
        pre = &dummyNode;
        curr = head;
        while(NULL!=curr && curr->mData<=val){
                pre = curr;
                curr = curr->mNext;
        }
        newNode->mNext = curr;
        pre->mNext = newNode;
        return dummyNode.mNext;
}


sort_bucket::ListNode* sort_bucket::Merge(ListNode *head1,ListNode *head2){
        ListNode dummyNode;
        ListNode *dummy = &dummyNode;
        while(NULL!=head1 && NULL!=head2){
                if(head1->mData <= head2->mData){
                        dummy->mNext = head1;
                        head1 = head1->mNext;
                }else{
                        dummy->mNext = head2;
                        head2 = head2->mNext;
                }
                dummy = dummy->mNext;
        }
        if(NULL!=head1) dummy->mNext = head1;
        if(NULL!=head2) dummy->mNext = head2;
       
        return dummyNode.mNext;
}

void sort_bucket::sort_arr(){
    std::vector<int> tmp = this->arr;
    int n = tmp.size();
    std::vector<ListNode*> buckets(BUCKET_NUM,(ListNode*)(0));
    for(int i=0;i<n;++i){
                int index = tmp[i]/BUCKET_NUM;
                ListNode *head = buckets.at(index);
                buckets.at(index) = insert(head,tmp[i]);
    }
    ListNode *head = buckets.at(0);
    for(int i=1;i<BUCKET_NUM;++i){
            head = Merge(head,buckets.at(i));
    }
    for(int i=0;i<n;++i){
            tmp[i] = head->mData;
            head = head->mNext;
    }
    for(int i=0;i<tmp.size();++i){
        std::cout<<tmp[i]<<" ";
    }
    std::cout<<std::endl;
}


