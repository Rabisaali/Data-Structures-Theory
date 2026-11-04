#include<iostream>
using namespace std;

class Node {
    public:
        int data;
        Node* left;
        Node* right;

        Node(int v) {
            data=v;
            left=NULL;
            right=NULL;
        }
};

class BST {
    private:
        Node* tree;

        Node* insertHelper(Node* tree, int v) {
            if (tree==NULL) {
                return new Node(v);
            }
            else if (tree->data<v) {
                tree->right=insertHelper(tree->right, v);
            } 
            else if (v<tree->data) tree->left=insertHelper(tree->left, v);
            return tree;
        }

        bool searchHelper(Node* tree, int v) {
            if (tree==NULL) return false;
            if (tree->data==v) return true;
            else if (tree->data<v) return searchHelper(tree->right, v);
            else if (tree->data>v) return searchHelper(tree->left, v);
            return false;
        }

        Node* findMinNode(Node* root) {
            while(root && root->left!=NULL) {
                root=root->left;
            }
            return root;
        }

        Node* findMaxNode(Node* root) {
            while(root && root->right!=NULL) {
                root=root->right;
            }
            return root;
        }

        Node* DeleteHelper(Node* root, int key) {
            if (root==NULL) return NULL;
            if (key<root->data) {
                root->left=DeleteHelper(root->left, key);
            } 
            else if (key>root->data) {
                root->right=DeleteHelper(root->right, key);
            }
            else {
                if (root->left==NULL && root->right==NULL) {
                    delete root;
                    return NULL;
                }
                else if (root->left==NULL) {
                    Node* temp=root->right;
                    delete root;
                    return temp;
                }
                else if(root->right==NULL) {
                    Node* temp=root->left;
                    delete root;
                    return temp;
                }
                
                Node* temp=findMinNode(root->right);
                root->data=temp->data;
                root->right=DeleteHelper(root->right, temp->data);
            }
            return root;
        }

        int heightHelper(Node* root) {
            if (root==NULL) return -1;
            return 1+max(heightHelper(root->left), heightHelper(root->right));
        }

        void inorderHelper(Node* root) {
            if (root!=NULL) {
                inorderHelper(root->left);
                cout << root->data;
                cout << " ";
                inorderHelper(root->right);
            }
        }

    public:

        BST() {
            tree=NULL;
        }

        void insert(int key) {
            tree=insertHelper(tree, key);
        }

        bool search(int key) {
            return searchHelper(tree, key);
        }

        void Delete(int key) {
            tree=DeleteHelper(tree, key);
        }

        int findMin() {
            Node* minNode=findMinNode(tree);
            if (minNode==NULL) {
                cout << "Tree is empty\n";
                return -1;
            }
            return minNode->data;
        }

        int findMax() {
            Node* maxNode=findMaxNode(tree);
            if (maxNode==NULL) {
                cout << "Tree is empty\n";
                return -1;
            }
            return maxNode->data;
        }

        int height() {
            return heightHelper(tree);
        }

        int inorderSuccessor(int key) {
            Node* curr=tree;
            Node* temp=NULL;

            while(curr!=NULL && curr->data!=key) {
                if (key<curr->data) {
                    temp=curr;
                    curr=curr->left;
                }
                else curr=curr->right;
            }

            if (curr==NULL) {
                cout << "Key not found in BST\n";
                return -1;
            }

            if (curr->right!=NULL) {
                Node* minRight=findMinNode(curr->right);
                return minRight->data;
            }
            if (temp!=NULL) return temp->data;

            cout << "Inorder succesor doesn't exist (it's the maximum element)\n";
            return -1;
        }

        void printInorder() {
            inorderHelper(tree);
            cout << endl;
        }

};

int main() {
    BST Tree;

    int keys[] = {10, 20, 30, 40, 50, 25};
    std::cout << "--- Inserting keys: 10, 20, 30, 40, 50, 25 ---\n";
    for (int key : keys) {
        Tree.insert(key);
    }

    cout << "Inorder Traversal: ";
    Tree.printInorder(); 


    cout << "\n--- Tree Metadata ---\n";
    cout << "Minimum value: " << Tree.findMin() << "\n";
    cout << "Maximum value: " << Tree.findMax() << "\n";
    cout << "Tree Height (edges): " << Tree.height() << "\n";

    cout << "\n--- Search Operations ---\n";
    cout << "Search 25: " << (Tree.search(25) ? "Found" : "Not Found") << "\n";
    cout << "Search 99: " << (Tree.search(99) ? "Found" : "Not Found") << "\n";

    cout << "\n--- Inorder Successor Tests ---\n";
    cout << "Successor of 25: " << Tree.inorderSuccessor(25) << "\n"; 
    cout << "Successor of 30: " << Tree.inorderSuccessor(30) << "\n"; 
    

    cout << "\n--- Deletion Tests ---\n";
    cout << "Deleting leaf node (25)...\n";
    Tree.Delete(25);
    cout << "Inorder after deleting 25: ";
    Tree.printInorder();

    cout << "Deleting node with one child (40)...\n";
    Tree.Delete(40);
    cout << "Inorder after deleting 40: ";
    Tree.printInorder();
    
    cout << "Deleting node with two children (20)...\n";
    Tree.Delete(20);
    cout << "Inorder after deleting 20: ";
    Tree.printInorder();

    return 0;
}