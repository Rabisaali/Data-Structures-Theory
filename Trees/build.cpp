#include<iostream>
#include<vector>
using namespace std;

class Node {
    public:
        int val;
        Node* left;
        Node* right;

        Node(int v) {
            left=NULL;
            right=NULL;
            val=v;
        }
};

Node* buildTree(vector<int>& pre, int& i, int n) {
    if (pre[i]==-1) {
        i++;
        //cout << root->val << " ";
        return NULL;
    }
    
    Node* root=new Node(pre[i]);
    i++;
    //cout << root->val << " ";
    root->left=buildTree(pre, i, n);
    root->right=buildTree(pre, i, n);
    return root;
}
//inorder
void print(Node* tree) {
    if (tree==NULL) {
        cout << -1 << " ";
        return;
    }

    print(tree->left);
    cout << tree->val << " ";
    print(tree->right);
    return;
}


int main () {
    vector<int>pre = {1,2,-1,-1,3,4,-1,-1,5,-1,-1};
    int n=pre.size();
    int i=0;
    Node* tree=buildTree(pre, i, n);
    cout << endl;
    print(tree);
}