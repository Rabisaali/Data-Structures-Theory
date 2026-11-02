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
Node* insert(Node* root, int v) {
    if (root==NULL) {
        root = new Node(v);
    }
    //Node* root=NULL;
    else if (root->val>v) {
        root->left = insert(root->left, v);

    }
    else if (root->val<v) {
        root->right = insert(root->right, v);
    }
    return root;
}
Node* buildTree(vector<int>& pre, int n, Node* tree) {
    for(int i=0; i<n; i++) {
        tree=insert(tree, pre[i]);
    }
    return tree;
    
}

bool validate(Node* tree, int m, int M) {
    if (tree==NULL) return true;
    if (tree->val > M || tree->val < m) return false;
    
    return validate(tree->right, tree->val, M) && validate(tree->left, m, tree->val); 
}

int count(Node* tree) {
    if (tree==NULL) return 0;
    int l=count(tree->left);
    int r=count(tree->right);
    return l+r+1;
}

int sum(Node* tree) {
    if (tree==NULL)  return 0;
    int l=sum(tree->left);
    int r=sum(tree->right);
    return l+r+tree->val;

}


int main () {
    vector<int>pre = {3,2,1,5,6,4};
    //int i=0;
    Node* tree=NULL;
    tree = buildTree(pre, pre.size(), tree);

    cout << validate (tree, 0, 100);
    cout << " " << count (tree) << " " << sum(tree);
}