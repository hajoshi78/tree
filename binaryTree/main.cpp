/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: harsh
 *
 * Created on November 27, 2020, 8:18 PM
 */

#include <cstdlib>
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <vector>
#include <future>
#include <map>

using namespace std;

struct Node{
    struct Node* lChild;
    struct Node* rChild;
    int data;
};

struct Node* createNewNode(int data){
    struct Node*  temp = new struct Node();
    temp->lChild =NULL;
    temp->rChild = NULL;
    temp->data = data;
    return temp;
}


void preOrderTraversalRecursive(struct Node* root){
    if( root == NULL){
        return;
    }
    cout << root->data<<"\t";
    preOrderTraversalRecursive(root->lChild);
    preOrderTraversalRecursive(root->rChild);
    return;
}

void preOrderTraversalIterative(struct Node* root){
    if( root== NULL){
        return;
    }
    stack<struct Node*> nodeStack;
    nodeStack.push( root);
    
    while(!nodeStack.empty()){
        struct Node* temp = nodeStack.top();
        cout << temp->data<<"\t";
        nodeStack.pop();
        if( temp->rChild!= NULL){
            nodeStack.push(temp->rChild);
        }
        if( temp->lChild!=NULL){
            nodeStack.push( temp->lChild);
        }
    }
}

void inOrderTraversalRecursive(struct Node* root){
    if( root == NULL){
        return;
    }
    inOrderTraversalRecursive(root->lChild);
    cout << root->data<<"\t";
    inOrderTraversalRecursive(root->rChild);
    return;
}

void inOrderTraversalIterative(struct Node* root){
    if( root== NULL){
        return;
    }
    stack<struct Node*> nodeStack;
    
    struct Node* p = root;
    while(1){
        while(p!=NULL){
            nodeStack.push(p);
            p = p->lChild;
        }
        if(nodeStack.empty()){
            break;
        }
        p= nodeStack.top();
        cout <<p->data<<"\t";
        nodeStack.pop();
        p= p->rChild;
    }
}

bool search(struct Node* root , int elem){
    if(root == NULL){
        return false;
    }
    if( root->data == elem ){
        return true;
    }
    bool rightSearch = search(root->rChild, elem);
    bool leftSearch = search(root->lChild, elem);
    return rightSearch || leftSearch;  
}



void postOrderTraversalRecursive(struct Node* root){
    if( root == NULL){
        return;
    }
    postOrderTraversalRecursive(root->lChild);
    postOrderTraversalRecursive(root->rChild);
    cout << root->data<<"\t";
    return;
}

void postOrderTraversalIterative(struct Node* root){
    if( root== NULL){
        return;
    }
    stack<struct Node*> nodeStack;
    nodeStack.push( root);
    
    while(!nodeStack.empty()){
        struct Node* temp = nodeStack.top();
        
        if( temp->rChild!= NULL){
            nodeStack.push(temp->rChild);
        }
        if( temp->lChild!=NULL){
            nodeStack.push( temp->lChild);
        }
        cout << temp->data<<"\t";
        nodeStack.pop();
    }
}

void levelOrderTraversal(struct Node* root){
    queue<struct Node*> nodeQueue;
    
    if( root ==NULL){
        return;
    }
    struct Node* p = root;
    nodeQueue.push(p);
    while(!nodeQueue.empty()){
        struct Node* temp = nodeQueue.front();
        cout<<temp->data<<"\t";
        if(temp->lChild){
            nodeQueue.push(temp->lChild);
        }
        if(temp->rChild){
            nodeQueue.push(temp->rChild);
        }
        nodeQueue.pop();
    }
}

void levelOrderZigZag(struct Node* root){
    if( root == NULL){
        return;
    }
    stack<struct Node *> currentLevel;
    stack<struct Node *> nextLevel;
    currentLevel.push(root);
    bool leftToRight = true;
    while( !currentLevel.empty()){
        struct Node* temp = currentLevel.top();
        currentLevel.pop();
        if( temp){
            cout <<temp->data<<"\t";
            if(leftToRight){
                if(temp->lChild){
                    nextLevel.push(temp->lChild);
                }
                if( temp->rChild){
                    nextLevel.push(temp->rChild);
                }
            }
            else{
                if( temp->rChild){
                    nextLevel.push(temp->rChild);
                }
                if(temp->lChild){
                    nextLevel.push(temp->lChild);
                }
            }     
        }
        if(currentLevel.empty()){
            leftToRight= !leftToRight;
            swap(currentLevel, nextLevel);      
        }
    }
}

void printAllLeafNodes(struct Node* root){
    if( root == NULL){
        return;
    }
    if( root->lChild == NULL && root->rChild == NULL){
        cout <<root->data<<"\t";
    }
    printAllLeafNodes(root->lChild);
    printAllLeafNodes(root->rChild);
}

void printLeftMostNodes(struct Node* root){
    if(root==NULL){
        return;
    }
    if(root->lChild){
        cout<<root->data<<"\t";
        printLeftMostNodes(root->lChild);
    }
    else if( root->rChild){
        cout<<root->data<<"\t";
        printLeftMostNodes(root->rChild);
    }
    
}


void printRightMostNodes(struct Node* root){
    if(root==NULL){
        return;
    }
    if(root->rChild){
        printRightMostNodes(root->rChild);
        cout<<root->data<<"\t";
    }
    else if( root->lChild){
        printRightMostNodes(root->lChild);
        cout<<root->data<<"\t";
    }
    
}

void printPerimeter(struct Node* root){
    printLeftMostNodes(root);
    printAllLeafNodes(root);
    printRightMostNodes(root);
}

int heightOfBinaryTree(struct Node* root){
    if( root ==NULL){
        return 0;
    }
    int leftHeight = heightOfBinaryTree(root->lChild);
    int rightHeight = heightOfBinaryTree(root->rChild);
    return 1+ (leftHeight>rightHeight?leftHeight:rightHeight);
}

void deleteTree(struct Node* root){
    if( root == NULL){
        return;
    }
    else{
        deleteTree(root->lChild);
        deleteTree(root->rChild);
        delete root;
        root = NULL;
    }  
}

bool findNodeWithPath(struct Node* root, int elem, vector<struct Node*>& path){
    if(root == NULL){
        return false;
    }
    path.push_back(root);
    if(root->data == elem){
        return true;
    }
  
   if(findNodeWithPath(root->lChild, elem, path)||findNodeWithPath(root->rChild, elem, path)){
       return true;
   }
   else{
       path.pop_back();
       return false;
   }
}

struct Node* getCommonParent(struct Node* root, int elem1, int elem2){
    
    vector<struct Node*> pathToElem1;
    bool elem1Exists = findNodeWithPath(root, elem1, pathToElem1);
    
    
    vector<struct Node*> pathToElem2;
    bool elem2Exists = findNodeWithPath(root, elem2, pathToElem2);
    
    if( !elem2Exists || !elem1Exists){
        return NULL;
    }
    struct Node* parent = NULL;
    
    cout<<endl<<"Path to " <<elem1 << " is : ";
    for ( auto x: pathToElem1){
        cout <<x->data <<"\t";
    }
    
    cout<<endl<<"Path to " <<elem2 << " is : ";
    for ( auto x: pathToElem2){
        cout <<x->data <<"\t";
    }
    
    if( elem1Exists && elem2Exists){
        
        vector<struct Node*>::iterator it1 = pathToElem1.begin();
        vector<struct Node*>::iterator it2 = pathToElem2.begin();
        parent = *it1;
        while(it1!=pathToElem1.end() && it2!= pathToElem2.end()){    
            if(*it1 != *it2){
                break;
            }   
            else{
                parent = *it1;
            }
            it1++;
            it2++;
        }
    }
    return parent;
}

struct Node* cloneTree(struct Node* root){
    if( root == NULL){
        return NULL;
    }
    else{
        struct Node* newRoot = new struct Node();
        newRoot->data  = root->data;
        newRoot->lChild = cloneTree(root->lChild);
        newRoot->rChild = cloneTree(root->rChild);
        return newRoot;
        
    }
}

void rightDiagonalTraversalUtil(struct Node* root, map<int,vector<int>>& mapOfSlopes,int slope){
    if( root== NULL){
        return;
    }
    mapOfSlopes[slope].push_back(root->data);
    rightDiagonalTraversalUtil(root->lChild, mapOfSlopes, slope+1);
    rightDiagonalTraversalUtil(root->rChild, mapOfSlopes, slope);   
}

void rightDiagonalTraversal(struct Node* root){
    cout <<endl<<"Right Diagonal Traversal"<<endl;
    map<int,vector<int>> mapOfNodesAtAGivenSlope;
    rightDiagonalTraversalUtil(root, mapOfNodesAtAGivenSlope,0);
    for( auto x:mapOfNodesAtAGivenSlope){
        vector<int> nodesVector = x.second;
        for( auto y : nodesVector){
            cout <<y<<"\t";
        }
        cout<<endl;
    }
}


void leftDiagonalTraversalUtil(struct Node* root, map<int,vector<int>>& mapOfSlopes,int slope){
    if( root== NULL){
        return;
    }
    mapOfSlopes[slope].push_back(root->data);
    leftDiagonalTraversalUtil(root->lChild, mapOfSlopes, slope+1);
    leftDiagonalTraversalUtil(root->rChild, mapOfSlopes, slope);   
}

void leftDiagonalTraversal(struct Node* root){
    cout <<endl<<"Right Diagonal Traversal"<<endl;
    map<int,vector<int>> mapOfNodesAtAGivenSlope;
    leftDiagonalTraversalUtil(root, mapOfNodesAtAGivenSlope,0);
    for( auto x:mapOfNodesAtAGivenSlope){
        vector<int> nodesVector = x.second;
        for( auto y : nodesVector){
            cout <<y<<"\t";
        }
        cout<<endl;
    }
}

void verticalViewUtil(struct Node* root, map<int,vector<int>>& mapOfSlopes,int slope){
    if( root== NULL){
        return;
    }
    mapOfSlopes[slope].push_back(root->data);
    verticalViewUtil(root->lChild, mapOfSlopes, slope-1);
    verticalViewUtil(root->rChild, mapOfSlopes, slope+1);   
}

void verticalView(struct Node* root){
    cout <<endl<<"Vertical View of Tree"<<endl;
    map<int,vector<int>> mapOfNodesAtAGivenSlope;
    verticalViewUtil(root, mapOfNodesAtAGivenSlope,0);
    for( auto x:mapOfNodesAtAGivenSlope){
        vector<int> nodesVector = x.second;
        for( auto y : nodesVector){
            cout <<y<<"\t";
        }
        cout<<endl;
    }
}


struct Node* mirrorBinaryTree(struct Node* root){
   if( root == NULL){
        return NULL;
    }
    else{
        struct Node* newRoot = new struct Node();
        newRoot->data  = root->data;
        newRoot->lChild = mirrorBinaryTree(root->rChild);
        newRoot->rChild = mirrorBinaryTree(root->lChild);
        return newRoot;
        
    }
}    

int diameterOfTree(struct Node *root){
    //diameter = max( height of Binary Tree or (1+HieghtOfRight Subtree + HeightOfLeft Sub Tree))
    if(root==NULL){
        return 0;
    }
    
    int leftSubtreeDiameter = diameterOfTree(root->lChild);
    int rightSubtreeDiameter = diameterOfTree(root->rChild);
    int leftSubTreeHeight = heightOfBinaryTree(root->lChild);
    int rightSubTreeHeight = heightOfBinaryTree(root->rChild);
    return max( max(leftSubtreeDiameter, rightSubtreeDiameter), (1+ leftSubTreeHeight+rightSubTreeHeight));
    
    
}

bool  isIdentical( struct Node* root1, struct Node* root2){
    if( root1== NULL && root2 == NULL){
        return true;
    }
    if( (root1 && !root2)  || (!root1 && root2)){
        return false;
    }
    if( (root1->data == root2->data) && isIdentical(root1->lChild, root2->lChild) && isIdentical(root1->rChild, root2->rChild)){
        return true;
    }
    else{
        return false;
    }
}

bool isSubTree(struct Node* root1, struct Node* root2){
    if( root1== NULL){
        return false;
    }
    if(root2==NULL){
        return false;
    }
    if( isIdentical(root1, root2)){
        return true;
    }
    if( isSubTree(root1->lChild, root2)|| isSubTree(root1->rChild, root2)){
        return true;
    }
    return false;
}
/*
 * 
 */
int main(int argc, char** argv) {
    struct Node* root=NULL;
    root= createNewNode(10);
    root->lChild= createNewNode(5);
    root->rChild= createNewNode(15);
    root->lChild->lChild = createNewNode(3);
    root->lChild->rChild =  createNewNode(6);
    root->rChild->lChild = createNewNode(12);    
    root->rChild->rChild  = createNewNode(20);
    root->rChild->rChild->lChild = createNewNode(18);
    root->rChild->rChild->rChild = createNewNode(25);
    
    cout<<endl<<"Pre Order Traversal Recursive : ";
    preOrderTraversalRecursive(root);
    
    cout<<endl<<"Pre Order Traversal Iterative : ";
    preOrderTraversalIterative(root);
    
    cout<<endl<<"In Order Traversal Recursive : ";
    inOrderTraversalRecursive(root);
    
    cout<<endl<<"In Order Traversal Iterative : ";
    inOrderTraversalIterative(root);
    
    cout<<endl<<"Post Order Traversal : ";
    postOrderTraversalRecursive(root);
    
    
    cout<<endl<<"Level Order Traversal : ";
    levelOrderTraversal(root);

    cout<<endl<<"Level Order Traversal ZigZag: ";
    levelOrderZigZag(root);

    cout<<endl<<"All Leaf  NOdes : ";
    printAllLeafNodes(root);    
    
    cout<<endl<<"Perimeter of the tree : ";
    printPerimeter(root);    
    
    
    vector<struct Node*> path;
    bool pathFound = findNodeWithPath(root, 18,path);
    if( pathFound){
        cout <<endl<<"Path to the Node 18 :: ";
        for( auto x:path){
            cout<< x->data<<"\t";
        }
    }
    else{
        cout <<endl<<"Path to the Node 18 doesnt exist";
    }
    
    
    vector<struct Node*> path1;
    bool pathFound1 = findNodeWithPath(root, 100,path1);
    if( pathFound1){
        cout <<endl<<"Path to the Node 100:: ";
        for( auto x:path){
            cout<< x->data<<"\t";
        }
    }
    else{
        cout <<endl<<"Path to the Node 100 doesnt exist";
    }
    
    
    cout << endl<<"Does Element 3  Exists ? : " <<search(root,3);
    cout << endl<<"Does Element 25  Exists ? : " <<search(root,25);
    cout << endl<<"Does Element 100  Exists ? : " <<search(root, 100);
    cout << endl<<"Does Element 10  Exists ? : " <<search(root, 10);
    cout << endl<<"Does Element 1  Exists ? : " <<search(root ,1);
    
    cout <<endl<<"height Of the Tree is " <<heightOfBinaryTree(root);
    
    
    struct Node* commonParent =NULL;
    commonParent = getCommonParent(root, 10,5);
    if( commonParent){
        cout << endl<<"Common parent is "<< commonParent->data;
    }
    else{
        cout <<endl<<"Common Parent doesn't exist..";
    }
    
    struct Node* clonedTree=NULL;
    clonedTree = cloneTree(root);
    cout <<endl<<"In Order Traversal of Cloned Tree is :: ";
    inOrderTraversalRecursive(clonedTree);
    
    
    cout <<endl<<"Comparing if Cloned Tree is identical to the Original Tree :: "<< isIdentical(root, clonedTree);
    
    deleteTree(clonedTree);
 
    
    struct Node* mirroredTree=NULL;
    mirroredTree = mirrorBinaryTree(root);
    cout <<endl<<"In Order Traversal of Mirrored Tree is :: ";
    inOrderTraversalRecursive(mirroredTree);
    
    cout <<endl<<"Comparing if Mirrored Tree is identical to the Original Tree :: "<< isIdentical(root, mirroredTree);
    
    root->rChild->rChild->rChild->lChild = mirroredTree;
    cout<<endl<<"Level Order Traversal after appending mirrored tree to the Root Tree: ";
    levelOrderTraversal(root);
    cout<<endl<<"Checking is MirroredTree is a subtree of Main Tree :  " << isSubTree(root, mirroredTree);
    cout<<endl<<"Diameter of the Tree is :: "<<diameterOfTree(root);
    
    root->rChild->rChild->rChild->lChild=NULL;
    deleteTree(mirroredTree);
 
    rightDiagonalTraversal(root);
    leftDiagonalTraversal(root);
    verticalView(root);
    cout<<endl<<"Diameter of the Tree is :: "<<diameterOfTree(root);
    deleteTree(root);
    return 0;
}

