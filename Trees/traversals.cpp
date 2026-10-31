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

void inorder(Node* tree) {
    if (tree==NULL) {
        cout << -1 << " ";
        return;
    }

    inorder(tree->left);
    cout << tree->val << " ";
    inorder(tree->right);
    return;
}


void postorder(Node* tree) {
    if (tree==NULL) {
        cout << -1 << " ";
        return;
    }

    postorder(tree->left);
    postorder(tree->right);
    cout << tree->val << " ";
    return;
}

void preorder(Node* tree) {
    if (tree==NULL) {
        cout << -1 << " ";
        return;
    }
    cout << tree->val << " ";
    preorder(tree->left);
    preorder(tree->right);
}

int main () {
    vector<int>pre = {1,2,-1,-1,3,4,-1,-1,5,-1,-1};
    int n=pre.size();
    int i=0;
    Node* tree=buildTree(pre, i, n);
    cout << endl;
    inorder(tree);
    cout << endl;
    postorder(tree);
    cout << endl;
    preorder(tree);
    cout << endl;
}