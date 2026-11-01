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

bool find(Node* tree, int v) {
    if (tree==NULL) return false;
    bool ans=false;
    if (tree->val==v) ans=true;
    else if (tree->val<v) ans = find(tree->right, v);
    else if(tree->val>v) ans = find(tree->left, v);
    return ans;
}

Node* Delete(Node* tree, int v) {
    // Node* root=tree;
    if (tree==NULL) return NULL;
    if (tree->val<v) {
        tree->right=Delete(tree->right, v);
    }
    else if (tree->val>v) {
        tree->left=Delete(tree->left, v);
    }
    else {
        if(tree->left==NULL && tree->right==NULL) {
            delete tree;
            return NULL;
        }
        else if (tree->left!=NULL && tree->right==NULL) {
            Node* temp=tree->left;
            delete tree;
            return temp;
        }
        else if (tree->left==NULL && tree->right!=NULL) {
            Node* temp=tree->right;
            delete tree;
            return temp;
        }
        else {
            Node* curr=tree;
            tree=tree->right;
            while(tree->left!=NULL) tree=tree->left;
            curr->val=tree->val;
            curr->right=Delete(curr->right, tree->val);
            return curr;
        }
    }
    return tree;
}

void inorder(Node* tree) {
    if (tree==NULL) {
        //cout << -1 << " ";
        return;
    }

    inorder(tree->left);
    cout << tree->val << " ";
    inorder(tree->right);
    return;
}


int main () {
    vector<int>pre = {3,2,1,5,6,4};
    //int i=0;
    Node* tree=NULL;
    tree = buildTree(pre, pre.size(), tree);
    inorder(tree);

    cout << endl;
    cout << find(tree, 5);
    cout << " " << find(tree, 89);
    cout << endl;
    tree=Delete(tree, 5);
    inorder(tree);

    cout << endl;
    cout << find(tree, 5);

}