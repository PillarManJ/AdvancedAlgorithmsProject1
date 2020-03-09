#include <iostream>
#include <algorithm>
#include <vector> 
#include <stack>
#include <queue>
#include <new>
#include <deque>

using namespace std;


typedef struct Node Node; 
struct Node{
    int data ;
    int height; 
    Node *left, *right, *parent; 
};

class AVLTree{


public :
//Node root = new Node(); 


Node*insertRec(Node*root, int key); //Done
Node*deleteRec(Node*root, int key); //Done
Node*findNextRec(Node*root, int key); //Done
Node*findPrevRec(Node*root); //Done
Node*treeMinRec(Node*root); //Done
Node*treeMaxRec(Node*root); //Done


Node*insertIter(Node*root, int key); //Done
Node*deleteIter(Node*root, int key); //Done
Node*findNextIter(Node*root); //Done
Node*findPrevIter(Node*root);//Done
Node* treeMin(Node*root);//Done
Node* treeMax(Node*root); //Done
Node* removeTwoChild(Node*root);//Done
};

Node*newNode(int key){
    Node*temp = new Node(); 

    if(temp == nullptr){
        cout <<"error, memory could not be allocated for NewNode";
        exit; 
    }
    temp->data = key; 
    temp->height = 0;
    temp->parent = NULL;
    temp->left = NULL; 
    temp->right = NULL; 

}

int maxDepthRec(Node*node){
    if(node == NULL)
        return 0;
    else
    {
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right); 

        if(lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1); 
    }
    
}

vector<int> getSortedArray(int n){
    int temp = n; 
    vector<int> vec; 
    for(int i = 0; i < n; i++){
       vec.push_back(temp);
       temp = temp - 1;
    }
    return vec; 
}

vector<int>getRandomArray(int n){
    vector<int> vec;
    srand(time(NULL));
    iSecret = rand() % 100000000 + 1; 
    for(int i = 0; i < n; i++){
        vec.push_back(iSecret); 
    }
}

Node*AVLTree::treeMin(Node* key){
    while(key->left != NULL)
        key = key->left;
    return key;
    
}

Node*AVLTree::treeMinRec(Node* key){
    while(key->left != NULL)
        treeMinRec(key->left);
    return key; 
}

Node*AVLTree::treeMax(Node* key){
    while(key->right != NULL)
        key = key->right;
    return key;
}

Node*AVLTree::treeMaxRec(Node*key){
    while(key->right!= NULL)
        treeMaxRec(key->right);
    return key; 
}

Node* rotateLeft(Node*node){
Node*a = node; 
Node*pivot = node->left; 
Node*c = node->left->left;
Node*d = node->left->right;
node = pivot; 
node->left = c; 
delete(node->left->left->left);
delete(node->left->left->right);
node->right = a;
node->right->left = d; 
}

Node* rotateRight(Node*node){
Node*a = node; 
Node*pivot = node->right; 
Node*c = node->right->right; 
Node*d = node->right->left; 
node = pivot; 
node->right = c; 
delete(node->right->right->right);
delete(node->right->right->left);
node->left = a; 
node->right->left = d; 
}

Node*AVLTree::findNextIter(Node*root){
    Node*curr = root;
    if(curr->right != NULL)
        return
            treeMin(curr->right);
    Node* temp = curr->parent;
    while(temp!= NULL && curr == temp->right){
        curr = temp; 
        temp = curr->parent;
    }
    return temp;
}

Node*AVLTree::findNextRec(Node*root){
    Node*curr = root; 
    if(curr->right != NULL)
        return 
            treeMin(curr->right);
    Node*temp = curr->parent;
    while(temp!= NULL && curr == temp->right){
        findNextRec(temp);
    }
}

Node*AVLTree::findPrevIter(Node*root){
    Node*curr = root;
    if(curr->left!= NULL)
        return
            treeMax(curr->left);
    Node*temp = curr->parent;
    while(temp!= NULL && curr == temp->left){
        curr = temp; 
        temp = curr->parent; 
    }
}

Node*AVLTree::findPrevRec(Node*root){
    Node*curr = root; 
    if(curr->left != NULL)
        return  
            treeMax(curr->left);
            Node*temp = curr->parent; 
        while(temp!= NULL && curr == temp-> left){
            findPrevRec(temp); 
        } 
}
/*
int setHeight(Node*node){
    int height = 0; 
    stack <*Node> stacc;
    Node*temp = node;
    while(temp != NULL && stacc.isEmpty == false){
        while(temp != NULL){
            stacc.push(temp);
            temp = temp->left;
            height += height -1; 
        }
        temp = stacc.top();
        stacc.pop();
        temp = temp->right; 
        height += height + 1; 
    }
    return height; 
}*/

Node*deepcopy(Node* root){
    Node*copyNode = new Node(*root);
    copyNode->right = root->right; 
    copyNode->left = root->left;
    return copyNode; 
}

bool hasChild(Node*root){
    if(root->left != NULL || root->right != NULL)
        return true;
    else return false;
}

int getHeight(Node* root){
    int l = 0;
    int r = 0;
    int h = 0;
    Node*curr = root; 
    stack< Node*> stacc;  
    //int keyroot = curr->data;
    //Travel to the left subtree.
    while(curr!= NULL && stacc.empty() == false)
    {
        while(curr != NULL){
            stacc.push(curr);
            curr = curr->left;
            if(hasChild(curr)== true && curr->data < root->data)
                l = l + 1; 
        }
        curr = stacc.top();
        stacc.pop();
        curr = curr->right;
        if(hasChild(curr)==true && curr->data > root->data)
            r = r + 1; 
    }
    
    h = l - r;
    return h;
}




Node* AVLTree::insertIter(Node*root, int data){
    Node*curr = root;
    Node*temp = NULL; 
    Node*newN = newNode(data);  
    int height = 0; 

    if(newN == nullptr){
        cout << "error, memory could not be allocated.";
        exit;
    }
    
    //Traverse through the nodes by continuously comparing data to 
    //the nodes.
    while(curr != NULL){
        temp = curr; 
        if(data < curr->data)
            curr = curr->left;
        else 
            curr = curr->right;
        //Balance the trees. 
        temp->height = getHeight(temp);
        if(temp->height > 0)
            rotateRight(temp);
        else if(temp->height < 0)
            rotateLeft(temp);         
    }
    if(temp == NULL){
        temp->parent = temp;
        temp = newN; 
        //Balance the trees
        temp->height = getHeight(temp);
        if(temp->height > 0)
            rotateRight(temp);
        else if(temp->height < 0)
            rotateLeft(temp); 
    }
    else if(data < temp->data){
    temp->left->parent = temp;
    temp->left = newN;
     //Balance the trees
     temp->height = getHeight(temp); 
     if(temp->height > 0)
        rotateRight(temp); 
     else if(temp->height < 0)
        rotateLeft(temp); 
    }
    else{ 
    temp->right->parent = temp;
    temp->right = newN;
    //Balance the trees
    temp->height = getHeight(temp);
    if(temp->height > 0)
        rotateRight(temp); 
    else if(temp-> height < 0)
        rotateRight(temp);
    }
    return temp;
  
}

Node*AVLTree::InsertRec(Node*root, int key){
    Node*y = NULL; 
    Node*curr = root;
    int z = 0;
    while(curr!= NULL){
        y = curr;
        z = getHeight(y); 
        if(z > 0)
            rotateLeft(y);
        else if(z < 0)
            rotateRight(y); 
        if(root->data < key){
            InsertRec(x->left, key)
            key->parent = y; 
        }else if(root->data > key){
            InsertRec(root->right, key); 
            key->parent = y;
        }if(y == NULL)
            root newNode(key); 
    } 
}

Node*removeNoChild(Node*root){
    Node*curr = root; 
                 curr = NULL;
    return curr; 
}

Node*removeOneChild(Node*root){
    Node*curr = root;
            if((curr-> left)!= NULL){
                curr->parent->left->left = curr->left->left;
                curr = curr->left->left;
                if(curr->left->left != NULL){
                    delete(curr->left->left); // Free the memory space.
                }else{
                    curr = curr->left;
                    delete(curr->left);
                }
            }else{
                curr->parent->right->right = curr->right->right;
                curr = curr->right->right; 
                if(curr->right->right != NULL)
                    delete(curr->right->right); 
                else
                    curr = curr->right;
                    delete(curr->right); 
            } 
            return curr;
        
}

Node*AVLTree::removeTwoChild(Node*root){
     Node* currentNode = treeMin(root);
     Node* nextNode = treeMax(root);
     Node*replacementNode = NULL; 
            Node* predacessor = deepcopy(currentNode);
            Node* successor = deepcopy(nextNode); 
            delete(currentNode->parent->left);
            replacementNode = nextNode->parent;
            delete(nextNode->parent->right);
           /* while(currentNode->data != key){
                currentNode = currentNode->parent; 
            } */
            //currentNode->data = predacessor->data;
            

}

Node*AVLTree::deleteIter(Node*root, int key){
    Node*curr = root; 
    int z = 0; 
    while(key!= curr->data){
        if(key < curr->data)
            curr = curr->left;
        else
            curr = curr->right; 
    }
    if(curr-> data == key){
        //Removing procedure for the case of no children
        if(curr->left  == NULL && curr->right == NULL){
        removeNoChild(curr);
        z = getHeight(curr);
        if(z > 0)
            rotateLeft;
        else if(z < 0)
            rotateRight; 
        }
        //Removing procedure for the case of one child.
        else if(curr->left != NULL || curr->right != NULL){
        removeOneChild(curr);
        z = getHeight(curr);
        if(z > 0)
            rotateLeft;
        else if(z < 0)
            rotateRight; 
        }
        //Removing procedure for the case of two children.
        else if(curr->left != NULL && curr->right != NULL)
        {
        removeTwoChild(curr);
        z = getHeight(curr);
        if(z > 0)
            rotateLeft;
        else if(z < 0)
            rotateRight; 
        }
    return root; 
}
}

void Transplant(Node*T, Node*u, Node*v){
    if(u->parent == NULL){
        T = v; 
    }else if(u == u->parent->left){
        u = parent->left = v; 
    }else 
        u->parent->right = v; 
    if(v == NULL)
        v->parent = u->parent; 
}

Node*AVLTree::DeleteRec(Node*T, Node*z){
if(z->left == NULL)
    Transplant(T, z, z->right);
else if(z->right == NULL)
    Transplant(T, z, z->left); 
}else 
    y = treeMinRec(z->right); 
    if(y->parent != z){
        Transplant(T, y, y->right);
        DeleteRec(T, z->right);
        DeleteRec(T, y->parent);
    }Transplant(T, z, y);
    DeleteRec(T, z->left);
    DeleteRec(T,y->left);
}

Node*ConstructTreeIter(){
    int depth = 0;
    Node*curr = new Node(NULL);
    vector<int> vec = getRandomArray(10000);
    for(int i = 0; i < vec.size(); i++)
        insertIter(curr, vec[i]); 
    depth = maxDepthRec(curr);
}

Node*ConstructTreeRec(){
    int depth = 0;
    Node*curr = new Node(NULL);
    vector<int> vec = getRandomArray(10000);
    for(int i = 0; i < vec.size(); i++)
        InsertRec(curr, vec[i]);
    depth = maxDepthRec(curr);
    cout << "depth is :" << depth << endl;
}

Node*ConstructSortedAVLTreeIter(){
    int depth = 0;
    Node*curr = new Node(NULL);
    vector<int> vec = getSortedArray(10000);
    for(int i = 0; i < vec.size(); i++)
        insertIter(curr, vec[i]);
    depth = maxDepthRec(curr); 
    cout << "depth is :" << depth << endl;
}

int main(){

    return 0;
}





