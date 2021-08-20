#include<bits/stdc++.h>
#include <list>
using namespace std;

// An AVL tree node for X
class Node
{
public:
    float key;
    Node *left;
    Node *right;
    int height;
};
int max(int a, int b);
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
int max(int a, int b)
{
    return (a > b)? a : b;
}
/* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */
Node* newNode(float key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially
    // added at leaf
    return(node);
}
/*
// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.*/
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    // Return new root
    return x;
}
/* A utility function to left
// rotate subtree rooted with x
// See the diagram given above.*/
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    // Return new root
    return y;
}
// Get Balance factor of node N
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
Node* insert(Node* node, float key)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}
Node* reverseTree(Node* n){
    Node *temp = NULL;
    if(n==NULL)
        return NULL;
    reverseTree(n->right);
    reverseTree(n->left);
    temp = n->left;
    n->left = n->right;
    n->right = temp;
}
void preOrder(Node *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}
void posOrder(Node *root)
{
    if(root != NULL)
    {
        posOrder(root->left);
        posOrder(root->right);
        cout << root->key << " ";

    }
}
//sort array points
void selectionSort(float* x, float* y, int n) {
    int i, j , min;
    float temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (x[j] < x[min])
                min = j;
        temp = x[i];
        x[i] = x[min];
        x[min] = temp;

        temp = y[i];
        y[i] = y[min];
        y[min] = temp;
    }
}

int flagEnter = 0;
//n is the count of points
void searchOn2DRangeTree(Node* rootX,float x1,float y1,float x2 , float y2, int n , float x[] , float y[])
{
    if(x1>x2)
    {
        int temp = x2;
            x2 = x1;
            x1 = temp;
    }
    if(y1>y2)
    {
        int temp = y2;
            y2 = y1;
            y1 = temp;
    }


    float a[n];
    int k = 0;
    list<Node*> list;

    list.push_back(rootX);
    while(!list.empty())
    {
        Node* t = NULL;
        t= list.back();
        list.pop_back();
        if(t->key==x2 && t->key > x1)
        {
            a[k] = t->key;
            if(t->left!=NULL)
                list.push_back(t->left);
            k++;
        }
        else if(t->key==x1 && t->key <x2)
        {
            a[k] = t->key;
            if(t->right!=NULL)
                list.push_back(t->right);
            k++;
        }
        else if(t->key>x1 && t->key<x2)
        {
            a[k] = t->key;
            if(t->right!=NULL)
                list.push_back(t->right);
            if(t->left!=NULL)
                list.push_back(t->left);
            k++;
        }
        else if(t->key>x1 && t->key>x2)
        {
            if(t->left!=NULL)
                list.push_back(t->left);
        }
        else if(t->key<x1 && t->key<x2)
        {
            if(t->right!=NULL)
                list.push_back(t->right);
        }
    }


    float xy[2][n];
    for(int i = 0 ; i < 2 ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            xy[i][j]=-1;
        }
    }
    int flag= 0 ;
    for(int i = 0 ; i < k ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            if(a[i]==x[j])
            {
                if(y[j]>=y1 && y[j]<=y2)
                {
                    flag++;
                    xy[0][j]=x[j];
                    xy[1][j]=y[j];
                    //cout << "(" << x[j] <<","<< y[j]<<")";
                }
            }
        }
    }
    if(flag==0)
    {
        cout << "None";
        if(flagEnter!=1 && flagEnter!=2)
        {
            cout<<"\n";
            flagEnter-=2;
        }
        return;
    }
    //selectionSort(xy[0],xy[1],n);
    selectionSort(xy[1],xy[0],n);
    for(int i = 0 ; i < 2 ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            if(xy[i][j]!=-1)
                cout<<xy[i][j]<<" ";
        }
        if(flagEnter!=1)
        {
            cout<<"\n";
            flagEnter--;
        }

    }

}

int main()
{
    int n;
    cin >> n ;
    float x[n], y[n];
    for(int i = 0 ; i < n ; i ++)
        cin>>x[i];
    for(int i = 0 ; i < n ; i ++)
        cin>>y[i];
    selectionSort(x,y,n);

    Node *root = NULL;
    for(int i = 0 ; i < n ; i ++)
        root = insert(root, x[i]);
    //preOrder(root);
    //cout<<"\n";

    /*selectionSort(y,x,n);
    Node *root2 = NULL;
    for(int i = 0 ; i < n ; i ++)
        root2 = insert(root2, y[i]);

    reverseTree(root2);
    preOrder(root2);
    */
    int n2;
    cin>>n2;
    float x1[n2],x2[n2],y1[n2],y2[n2];
    for(int i = 0 ; i < n2 ; i++)
    {
        cin>>x1[i];
        cin>>y1[i];
        cin>>x2[i];
        cin>>y2[i];
    }
    flagEnter = n2*2;
    for(int i = 0 ; i < n2 ; i++)
    {
        searchOn2DRangeTree(root,x1[i],y1[i],x2[i],y2[i],n,x,y);
    }


    return 0;
}