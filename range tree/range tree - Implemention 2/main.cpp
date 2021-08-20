#include <iostream>
#include <vector>
using namespace std;
class Node{
public:
    float xValue;
    float yValue;
    Node *right;
    Node *left;
    Node *yRoot;
    Node(float x, float y){
        xValue = x;
        yValue = y;
        right = NULL;
        left = NULL;
        yRoot = NULL;
    }
};

vector<float> javabX;
vector<float> javabY;
void merge(float xArr[], float yArr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    float xL[n1], xR[n2];
    float yL[n1], yR[n2];
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        xL[i] = xArr[l + i];
        yL[i] = yArr[l + i];
    }
    for (j = 0; j < n2; j++){
        xR[j] = xArr[m + 1+ j];
        yR[j] = yArr[m + 1+ j];
    }

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (xL[i] <= xR[j])
        {
            xArr[k] = xL[i];
            yArr[k] = yL[i];
            i++;
        }
        else
        {
            xArr[k] = xR[j];
            yArr[k] = yR[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
     are any */
    while (i < n1)
    {
        xArr[k] = xL[i];
        yArr[k] = yL[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
     are any */
    while (j < n2)
    {
        xArr[k] = xR[j];
        yArr[k] = yR[j];
        j++;
        k++;
    }
}

void mergeSort(float xArr[], float yArr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(xArr, yArr, l, m);
        mergeSort(xArr, yArr, m+1, r);

        merge(xArr, yArr, l, m, r);
    }
}


Node* rangeTreeX(float xValues[], float yValues[], Node *root, int a, int b){
    if(b==a){
        root = new Node(xValues[a], yValues[a]);
        return root;
    }
    int x = (b-a)/2 + a;

    root = new Node(xValues[x], yValues[x]);
    root->right = rangeTreeX(xValues, yValues, root->right, x+1, b);
    root->left = rangeTreeX(xValues, yValues, root->left, a, x);
    return root;
}
void inOrder(Node *root){
    if(root == NULL)
        return;
    cout<<root->xValue;
    inOrder(root->left);
    inOrder(root->right);
}
int tedadBarg(Node *node){
    if(node == NULL)
        return 0;
    if(node->right == NULL && node->left == NULL){
        //cout<<node->xValue;
        return 1;
    }else if(node->right == NULL){
        return tedadBarg(node->left);
    }
    else if(node->left == NULL){
        return tedadBarg(node->right);
    }
    return tedadBarg(node->left) + tedadBarg(node->right);
}
void berizTosh(Node *node, float xv[], float yv[], int tedadBarg){
    if(node->right == NULL && node->left == NULL){
        for(int i = 0;i<tedadBarg;i++){
            if(xv[i]==NULL){
                xv[i] = node->xValue;
                yv[i] = node->yValue;
                break;
            }
        }
        return;
    }else if(node->right == NULL){
        berizTosh(node->left, xv, yv, tedadBarg);
    }
    else if(node->left == NULL){
        berizTosh(node->right, xv, yv, tedadBarg);
    }
    berizTosh(node->left, xv, yv, tedadBarg);
    berizTosh(node->right, xv, yv, tedadBarg);
}
Node* makeSecTree(Node *node){
    if(node == NULL)
        return NULL;
    int tedad_barg = tedadBarg(node);
    float xv[tedad_barg], yv[tedad_barg];
    for(int i = 0;i<tedad_barg ; i++){
        xv[i] = NULL;
        yv[i] = NULL;
    }
    berizTosh(node, xv, yv, tedad_barg);
    mergeSort(yv, xv, 0, tedad_barg-1);
    node->yRoot = rangeTreeX(xv, yv, node, 0, tedad_barg-1);
    return node;
}

Node* makeSecTree2(Node *node){
    if(node ==NULL)
        return NULL;
    makeSecTree(node);
    //cout<<"Q";
    node->left = makeSecTree2(node->left);
    node->right = makeSecTree2(node->right);

    return node;
}

Node* searchY(Node *root, float minY, float maxY){
    if(root == NULL)
        return NULL;
    if(root->yValue>=minY && root->yValue<=maxY){
        //cout<<root->yValue<<"##"<<endl;
        return root;
    }
    else if(root->yValue>maxY){
        return searchY(root->left, minY, maxY);
    }
    else{
        return searchY(root->right, minY, maxY);
    }
}
void javabBede(Node *root){
    if(root == NULL)
        return;
    if(root->right == NULL && root->left == NULL){
        javabX.push_back(root->xValue);
        javabY.push_back(root->yValue);
        return;
    }else if(root->right == NULL){
        javabBede(root->left);
    }
    else if(root->left == NULL){
        javabBede(root->right);
    }
    else{
        javabBede(root->right);
        javabBede(root->left);
    }
}

void raftimToChapY(Node *root,float minY){
    if(root == NULL)
        return;
    if(root->left ==NULL && root->yValue >=minY){
        //inm javab e
        javabBede(root);
        return;
    }
    if(root->yValue>=minY){
        //kole rastesh javab e
        //cout<<tedadBarg(root->right)<<endl;
        javabBede(root->right);
        raftimToChapY(root->left, minY);
    }else
        raftimToChapY(root->right, minY);
}

void raftimToRastY(Node *root, float maxY){
    if(root == NULL)
        return;
    if(maxY>=root->yValue){
        //kole chapesh javabe
        //cout<<tedadBarg(root->left)<<endl;
        if(root->left == NULL){
            javabBede(root);
            return;
        }
        javabBede(root->left);
        raftimToRastY(root->right, maxY);
    }else
        raftimToRastY(root->left, maxY);
}
void answersY(Node *root,float minY, float maxY){
    //cout<<root->xValue<<" ## "<<root->yValue<<endl<<minY<<"$$"<<maxY<<endl;
    root = searchY(root, minY, maxY);
    //cout<<root->xValue<<"%%"<<endl;
    //cout<<"@@ "<<root->xValue<<endl;
    if(root == NULL)
        return;
    if(root->left==NULL){
        //in javab e
        javabBede(root);

        //  cout<<tedadBarg(root)<<endl;
    }
    raftimToChapY(root->left, minY);
    raftimToRastY(root->right, maxY);
}


Node* searchX(Node *root, float minX, float maxX){
    if(root == NULL)
        return NULL;
    if(root->xValue>=minX && root->xValue<=maxX){
        return root;
    }
    else if(root->xValue>maxX){
        return searchX(root->left, minX, maxX);
    }
    else{
        return searchX(root->right, minX, maxX);
    }
}



void raftimToChap(Node *root, float minX, float minY, float maxY){
    if(root == NULL)
        return;
    if(root->left ==NULL && root->xValue >=minX){
        //inm bayad y hash check she
        //cout<<root->yRoot->xValue<<" ## "<<root->yRoot->yValue<<endl;
        answersY(root->yRoot, minY, maxY);
    }
    if(root->xValue>=minX){
        //kole rastesh byd y hash check she
        //cout<<tedadBarg(root->right)<<endl;
        if(root->right != NULL){
            //cout<<root->right->yRoot->yValue<<"###"<<endl;
            answersY(root->right->yRoot, minY, maxY);
        }
        raftimToChap(root->left, minX, minY, maxY);
    }else
        raftimToChap(root->right, minX, minY, maxY);
}
void raftimToRast(Node *root, float maxX, float minY, float maxY){
    if(root == NULL)
        return;
    if(maxX>=root->xValue){
        //kole chapesh byd y hash check she
        //cout<<tedadBarg(root->left)<<endl;
        if(root->left != NULL)
            answersY(root->left->yRoot, minY, maxY);
        else
            answersY(root->yRoot, minY, maxY);
        raftimToRast(root->right, maxX, minY, maxY);
    }else
        raftimToRast(root->left, maxX, minY, maxY);
}
void answers(Node *root, float minX, float maxX, float minY, float maxY){
    //cout<<"***&&&&"<<minY<<" "<<maxY<<endl;
    root = searchX(root, minX, maxX);
    //cout<<"@@ "<<root->xValue<<endl;
    if(root == NULL)
        return;
    if(root->left==NULL){
        //byd in khone y hash check she
        answersY(root->yRoot, minY, maxY);
        //  cout<<tedadBarg(root)<<endl;
    }
    raftimToChap(root->left, minX, minY, maxY);
    raftimToRast(root->right, maxX, minY, maxY);
}

int main(){
    int n;
    cin>>n;
    float x[n];
    float y[n];
    for(int i = 0;i<n;i++)
        cin>>x[i];
    for(int i = 0;i<n;i++)
        cin>>y[i];
    mergeSort(x, y, 0, n-1);
    //cout<<x[0];
    int tedad;
    cin>>tedad;
    Node *root = NULL;
    root = rangeTreeX(x, y, root, 0, n-1);
    //inOrder(root);
    root = makeSecTree2(root);
    //cout<<root->left->right->yRoot->yValue;
    //answers(root, 2, 9);
    for(int k = 0;k<tedad;k++){
        float minX, maxX, minY, maxY;
        cin>>minX>>minY>>maxX>>maxY;
        //cout<<minX<<"!!!!"<<maxX<<endl;
        answers(root, minX, maxX, minY, maxY);
        if(javabX.size()>0){
            float xAns[javabX.size()], yAns[javabX.size()];
            for(int i = 0;i<javabX.size();i++){
                xAns[i] = javabX[i];
                yAns[i] = javabY[i];
            }
            int tol = (int)javabY.size()-1;
            mergeSort(yAns, xAns, 0, tol);
            for(int i = 0;i<javabX.size();i++){
                cout<<xAns[i]<<" ";
            }
            cout<<endl;
            for(int i = 0;i<javabX.size();i++){
                cout<<yAns[i]<<" ";
            }
            cout<<endl;
            for(int i= 0;i<javabX.size()+1;i++){
                javabX.pop_back();
                javabY.pop_back();
            }
        }
        else
            cout<<"None"<<endl;
    }
}
}
