#include<bits/stdc++.h>

using namespace std;

//实现二叉搜索树，二叉搜索树的中序遍历是有序的
//主要实现：查找、插入、删除

//节点类
template<class T>
class BSTnode{
    
public:
    //构造函数
    BSTnode(const T& val):_val(val),_left(nullptr),_right(nullptr)
    {}
    T _val;
    BSTnode<T>* _left;
    BSTnode<T>* _right;
};

//树类
template<class T>
class BSTree{
public:
    typedef BSTnode<T> Node;
    //默认构造
    BSTree():_root(nullptr){}
    //拷贝构造
    Node* copyTree(Node* root){
        if(root){
            Node* cur = new Node(root->_val);
            cur->_left=copyTree(root->_left);
            cur->_right=copyTree(root->_right);
            return cur;
        }
        return nullptr;
    }
    BSTree(const BSTree<T>& obst){
        _root = copyTree(obst._root);
    }
    //析构
    void distroy(Node* root){
        if(root){
            distroy(root->_left);
            distroy(root->_right);
            delete root;
        }
    }
    ~BSTree(){
        distroy(_root);
    }
    //重载赋值
    BSTree<T>& operator=(BSTree<T> obst){
        swap(_root,obst._root);
        return *this;
    }
    //实现查找
    //找到了返回节点，未找到返回空
    Node* find(const T& val){
        Node* cur = _root;
        while(cur){
            if(cur->_val==val){
                return cur;
            }
            else if(cur->_val<val){
                cur = cur->_right;
            }
            else{
                cur = cur->_left;
            }
        }
        return nullptr;
    }
    //插入
    //插入成功返回true，失败返回false
    bool insert(const T& val){
        //判断树本身是否为空
        if(!_root){
            _root = new Node(val);
        }
        Node*cur = _root;
        Node* parent=nullptr;
        //先查找是否存在值为val的节点
        while(cur){
            parent = cur;
            if(cur->_val==val){
                return false;
            }
            else if(cur->_val<val){
                cur = cur->_right;
            }
            else{
                cur = cur->_left;
            }
        }
        //存在则直接返回，不存在则查询完整棵树
        cur = new Node(val);
        if(parent->_val<val){
            parent->_right=cur;
        }
        else {
            parent->_left=cur;
        }
        return true;
    }
    //删除
    bool erase(const T& val){
        //有几种情况
        //1.没找到，直接返回false，2.要删除的节点为叶子节点，
        //3.要删除的节点左子节点为空，4.要删除的节点右子节点为空，5.要删除的节点是度为2的节点
        //先查找
        Node*cur = _root;
        Node* parent=nullptr;
        while(cur){
            if(cur->_val==val){
                break;
            }
            else if(cur->_val<val){
                parent = cur;
                cur = cur->_right;
            }
            else{
                parent = cur;
                cur = cur->_left;
            }
        }
        //没找到
        if(cur==nullptr)return false;
        //如果是叶子节点
        if(cur->_right==nullptr&&cur->_left==nullptr){
            //如果要删除的是根节点
            if(cur==_root){
                _root = nullptr;
            }
            else{
                if(parent->_left==cur){
                    parent->_left=nullptr;
                }
                else{
                    parent->_right=nullptr;
                }
            }
            delete cur;
        }
        //如果是左孩子节点为空的节点
        else if(cur->_left==nullptr&&cur->_right!=nullptr){
            //如果要删除的是根节点
            if(cur==_root){
                _root = cur->_right;
            }
            else{
                if(parent->_left==cur){
                    parent->_left = cur->_right;
                }
                else{
                    parent->_right = cur->_right;
                }
            }
            delete cur;
        }
        //如果是右孩子节点为空的节点
        else if(cur->_left!=nullptr&&cur->_right==nullptr){
            //如果要删除的是根节点
            if(cur==_root){
                _root = cur->_left;
            }
            else{
                if(parent->_left==cur){
                    parent->_left = cur->_left;
                }
                else{
                    parent->_right = cur->_left;
                }
            }
            delete cur;
        }
        //如果左右孩子都存在,需要找到cur节点的右子树的最小值，作为当前节点的新值，才能保持二叉搜索树的关系
        else{
            Node* leftMostInRight = cur->_right;
            Node* parent = cur;
            //找到右子树的最左节点
            while(leftMostInRight->_left){
                parent = leftMostInRight;
                leftMostInRight = leftMostInRight->_left;
            }
            //用这个值来替换cur值
            cur->_val = leftMostInRight->_val;
            //判断最左值是在父亲的右边还是左边
            if(parent->_left==leftMostInRight){
                parent->_left = leftMostInRight->_right;
            }
            else{
                parent->_right = leftMostInRight->_right;
            }
            delete leftMostInRight;
        }
        return true;
    }
    //中序遍历
    void inorder(){
        _inorder(_root);
        cout<<endl;
    }
    void _inorder(Node* root){
        if(root==nullptr)return;
        _inorder(root->_left);
        cout<<root->_val<<" ";
        _inorder(root->_right);
    }

//根节点私有
private:
    Node * _root = nullptr;
};


void test() {
	BSTree <int> bst;
	bst.insert(0);
	bst.insert(5);
	bst.insert(6);
	bst.insert(3);
	bst.insert(7);
	bst.insert(1);
	bst.inorder();
	// 拷贝
	BSTree<int> p(bst); 
	p.inorder();
	// 删除
	bst.erase(3);
	bst.inorder();
	bst.erase(6);
	bst.inorder();
}




int main(){
    test();
    return 0;
}