#include<bits/stdc++.h>

using namespace std;

//AVL就是高度平衡的二叉搜索树，其任意节点的左右子树的深度差不超过1.
//首先是节点类
//平衡因子的作用是用来判断当前树是否平衡，其值为右子树高度减左子树，只要绝对值不大于1，则平衡，否则需要旋转
template<class T>
struct AVLnode{
    //构造函数
    AVLnode(const T& data = T())
    :_left(nullptr)
    ,_right(nullptr)
    ,_parent(nullptr)
    ,_data(data)
    ,_bf(0)
    {}
    //成员
    AVLnode<T>* _left;
    AVLnode<T>* _right;
    AVLnode<T>* _parent;//父亲节点
    T _data;
    int _bf;//平衡因子
};
//AVLTree=二叉搜索树+平衡因子限制
template<class T>
class AVLTree{
    typedef AVLnode<T> Node;
public:
    //构造
    AVLTree():_root(nullptr){}
    //在AVL树上插入val值节点
    bool Insert(const T& val){
        Node* cur = _root;
        Node* parent = nullptr;
        //查找位置
        while(cur){
            if(cur->_data==val){
                return false;
            }
            else if(cur->_data<val){
                parent = cur;
                cur = cur->_right;
            }
            else{
                parent = cur;
                cur = cur->_left;
            }
        }
        //找到插入位置
        cur = new Node(val);
        //若插入节点为根节点
        if(parent == nullptr){
            _root = cur;
        }
        else if(parent->_data>cur->_data){
            parent->_left = cur;
            cur->_parent = parent;
        }
        else{
            parent->_right = cur;
            cur->_parent = parent;
        }
        //处理平衡因子
        while(parent){
            //从下往上更新
            //平衡因子为右子树高度减左子树，所以是左子树则--，右子树则++
            if(cur == parent->_left){
                parent->_bf--;
            }
            else{
                parent->_bf++;
            }
            if(parent->_bf==0){
                //平衡因子为0的节点，其父节点的平衡因子一定也为0，所以不用继续更新
                break;
            }
            else if(parent->_bf == 1|| parent->_bf == -1){
                //为1和-1要继续向上查找，看是否存在绝对值大于1的节点
                cur = parent;
                parent = cur->_parent;
            }
            else{//说明平衡因子有为2或者-2的，需要进行旋转
                if(parent->_bf<0 && cur->_bf<0){
                    //右旋，左子树大于右子树
                    RotateR(parent);
                }
                else if(parent->_bf>0 && cur->_bf>0){
                    //左旋
                    RotateL(parent);
                }
                else if(parent->_bf>0 && cur->_bf<0){
                    //右左双旋
                    RotateRL(parent);
                }
                else {
                    //左右双旋
                    RotateLR(parent);
                }
                break;
            }
        }
        return true;
    }
    //析构
    void distroy(Node* root){
        if(root){
            distroy(root->_left);
            distroy(root->_right);
            delete root;
        }
    }
    ~AVLTree(){
        distroy(_root);
    }
    bool IsAVLTree(){
        return _IsAVLTree(_root);
    }
    void _Inorder(Node* root){
        if(root==nullptr)return;
        _Inorder(root->_left);
        cout<<root->_data<<":"<<root->_bf<<",";
        _Inorder(root->_right);
    }
    void Inorder(){
        _Inorder(_root);
        cout<<endl;
    }
private:
    //根据二叉搜索树+平衡因子验证是否为有效的AVL树
    bool _IsAVLTree(Node* root){
        //空树有效
        if(!root)return true;
        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
        if(rightHeight-leftHeight!=root->_bf){
            cout<<"平衡因子异常："<<root->_data<<endl;
        }

        return abs(rightHeight-leftHeight)<=1
        &&_IsAVLTree(root->_left)
        &&_IsAVLTree(root->_right);
    }
    //高度计算
    int _Height(Node* root){
        if(root==nullptr)return 0;
        return 1+max(_Height(root->_left), _Height(root->_right));
    }
    //左子树不平衡右单旋,参数node为平衡因子2或-2的节点
    void RotateR(Node* node){
        //   3
        //  2
        //1
        //此时node为值为3的节点，将节点2的右子树变为节点3的左子树，再将2的右子树变为节点3
        Node* cur = node->_left;
        //将节点2的右子树变为节点3的左子树
        node->_left = cur->_right;
        //如果2号节点的子树存在，则更新其父节点
        if(cur->_right){
            cur->_right->_parent = node;
        }
        //再将2的右子树变为节点3
        cur->_right = node;
        //更新2号节点的父节点
        cur->_parent = node->_parent;
        //如果3号节点为根节点,更新根节点
        if(cur->_parent==nullptr){
            _root = cur;
        }
        //如果不是,更新父节点的子节点
        else{
            if(node == cur->_parent->_left){
                cur->_parent->_left=cur;
            }
            else{
                cur->_parent->_right=cur;
            }
        }
        //更新3号节点的父节点
        node->_parent = cur;
        cur->_bf = 0;
        node->_bf=0;
    }

    //左单旋
    void RotateL(Node* node){
        //1
        // 2
        //  3
        //将1号节点的右子树更新为2号节点的左子树，再更新2号节点的左子树为1号节点
        Node *cur = node->_right;
        node->_right = cur->_left;
        if(cur->_left){
            cur->_left->_parent = node;
        }
        //将2号节点的父节点更新为3号节点的父节点
        cur->_left = node;
        cur->_parent = node->_parent;
        //如果是根
        if(!cur->_parent){
            _root=cur;
        }
        else{
            if(node->_parent->_left == node){
                node->_parent->_left = cur;
            }
            else{
                node->_parent->_right = cur;
            }
        }
        node->_parent = cur;
        cur->_bf = 0;
        node->_bf = 0;
    }

    void RotateRL(Node* node){
        //1
        //   3
        // 2
        //这里异常的为1号节点
        Node* child = node->_right;//3号节点
        //需要保存2号节点的平衡因子
        int tmpbf = child->_left->_bf;
        //先右再左
        RotateR(child);
        RotateL(node);
        if(tmpbf==1){
            node->_bf = -1;
        }
        else if(tmpbf==-1){
            child->_bf = 1;
        }
        //若_bf为0说明2号节点为新节点，不需要进行更新
    }
    
    void RotateLR(Node* node){
        //  3
        //1
        //  2
        //这里异常的为3号节点
        Node* child = node->_left;//1号节点
        //需要保存2号节点的平衡因子
        int tmpbf = child->_right->_bf;
        RotateL(child);
        RotateR(node);
        if(tmpbf==1){
            child->_bf = -1;
        }
        else if(tmpbf==-1){
            node->_bf = 1;
        }
    }
private:
    Node* _root;
};
void test(){
    AVLTree<int> avlt;
    avlt.Insert(1);
    avlt.Insert(2);
    avlt.Inorder();
    if(avlt.IsAVLTree())cout<<"IsAVLTree"<<endl;
    avlt.Insert(9);
    avlt.Insert(5);
    avlt.Insert(8);
    avlt.Inorder();
    if(avlt.IsAVLTree())cout<<"IsAVLTree"<<endl;
    avlt.Insert(6);
    avlt.Insert(7);
    avlt.Inorder();
    if(avlt.IsAVLTree())cout<<"IsAVLTree"<<endl;
}

int main(){
    test();
    return 0;
}