#include<iostream>
#include<vector>
#include<queue>
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

void level (Node* tree) {
    queue<Node*> q;

    q.push(tree);
    q.push(NULL); //to print next line

    while(!q.empty()) {

        Node* node=q.front();
        q.pop();

        if (node==NULL && !q.empty()) {
            cout << "\n"; //for new line
            q.push(NULL);
            continue;
        }
        else if (q.empty()) break;

        cout << node->val << " ";

        if(node->left!=NULL) q.push(node->left);
        if(node->right!=NULL) q.push(node->right);
        //q.push(NULL);

        
    }
}


int main () {
    vector<int>pre = {1,2,-1,-1,3,4,-1,-1,5,-1,-1};
    int n=pre.size();
    int i=0;
    Node* tree=buildTree(pre, i, n);
    cout << endl;

    level(tree);
    cout << endl;
}