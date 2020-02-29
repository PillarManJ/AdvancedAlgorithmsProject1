#include <iostream>
#include <algorithm>
#include <queue>
#include <deque> 

using namespace std;
//Note : This is the recursive set 



class Node
{
    int data;
    Node *parent, *left, *right; 

    public:
    Node insertRec(Node *root, Node* data); //DONE
    Node deleteRec(Node *root, Node* data);
    Node findNextRec(Node *node); //DONE
    Node findPrevRec(Node *node); //DONE
    Node findMinRec(Node *node); //DONE 
    Node findMaxRec(Node *node); // DONE

    void insertIter(Node*root, Node*z); //DONE
    void deleteIter(Node*root, Node*z); //DONE
    Node findNextIter(Node* node); //DONE
    Node findPrevIter(Node* node);//DONE
    Node findMinIter(Node *node); //DONE
    Node findMaxIter(Node *node);//DONE
};

//Question 3a
vector<int>getRandomArray(int n){
    vector<int> vec; 
    srand(time(NULL));
    iSecret = rand() % 1000000 + 1; 
    for(int i = 0; i < n; i++){
        vec.push_back(iSecret); 
       
    }
    return vec; 
}
//Question 3b
vector<int> getSortedArray(int n){
    int temp = n; 
    vector<int> vec; 
    for(int i = 0; i < n; i++){
       vec.push_back(temp);
       temp = temp - 1;
    }
    return vec; 
}

//Question 2b
vector<int>BSTtoArray(Node*node){
    vector<int>data;
    if(node!= NULL)
        BSTtoArray(node->left);
        data.push_back(node->data); 
        BSTtoArray(node->right);
    sort(data.begin(), data.begin()+sizeof(data));
    return data; 
}


//Iterative functions
Node*Node::findMinIter(Node* node){
    while(node>left != NULL)
        node = node->left;
    return node;
}

Node*Node::findMaxIter(Node*node){
    while(node->right != NULL)
        node = node->right;
    return node; 
}

Node*Node::findNextIter(Node*node){
    if(node->right != NULL)
        return findMinIter(node->right);
    y = node->parent; 
    while(y != NULL && node == y->right)
    {
        node = y; 
        y = y->parent; 
    }
    return y; 
}

Node*Node::findPrevIter(Node*node){
    if(node->left != NULL)
        return findMaxIter(node->left); 
    y = node->parent; 
    while(y != NULL && node == y->left)
    {
        node = y; 
        y = y->parent; 
    }
    return y; 
}

void Transplant(Node*T, Node*u, Node*v){
    if(u->parent == NULL){
        T = v;
        else if(u == u->parent->left)
            u->parent->left = v; 
        else
            u->parent->right = v; 
        if(v == NULL)
            v->parent = u->parent; 
    }
}

void Node::deleteIter(Node*root, Node*z){
    if(z->left == NULL)
        Transplant(root, z, z->right);
    else if(z->right == NULL)
        Transplant(root, z, z->left); 
    else 
        y = findMinIter(z->right); 
        if(y->parent != z){
            Transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y; 
        }Transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y; 
}


void Node::insertIter(Node*root, Node *z){
    Node*y = NULL;
    Node*x = root  
    while(x!= NULL){
        y = x; 
        if(z->data < x->data)
            x = x->left;
        else 
            x = x->right; 
    }
    z->parent = y; 
    if(y==NULL)
        root = z;
    else if (z->data  < y->data)
    {
         y->left =  z;
    }else 
    y->right = z;  
}


Node*Node::findMinRec(Node*node){
    while(node->left != NULL)
        findMinRec(node->left); 
    return node; 
}

Node*Node::findMaxRec(Node*node){
    while(node->right != NULL)
        findMaxRec(node->right);
    return node; 
}

Node*Node::findNextRec(Node *node){
    if(node->right != NULL)
        return(findMinRec(node->right)); 
    Node*y = node->parent; 
    while(y!= NULL && node == y->right){
        findMinRec(y->right);
        findMinRec(y->parent);
    }
    return node; 
}

Node*Node::findPrevRec(Node *node){
    //The predacessor is symmetric to successor.
    if(node->left != NULL)
        return(findMaxRec(node->left));
    Node*y = node->parent; 
    while(y!= NULL && node == y->left){
        findMaxRec(y->left);
        findMaxRec(y->parent);
    }

}

Node*Node::InsertRec(Node*root, Node*k){
    Node*y = NULL; 
    Node*x = root;
    while(x!= NULL){
        y = x; 
        if(root->data < k->data){
            InsertRec(x->left, k);
            k->parent = y;  
        }else{
            InsertRec(x->right, k);
            k->parent = y; 
        }if(y == NULL)
            root = k;
    }

}

Node*Node::DeleteRec(Node*T , Node*z){
    if(z->left == NULL)
        Transplant(T, z, z->right); 
    else if(z->right == NULL)
        Transplant(T, z, z->left); 
    else y = findMinRec(z->right); 
        if(y->parent != z){
            Transplant(T, y, y-right); 
            DeleteRec(T, z->right);
            DeleteRec(T, y->parent);
        }Transplant(T, z, y); 
        DeleteRec(T, z->left);
        DeleteRec(T, y->left); 
}
