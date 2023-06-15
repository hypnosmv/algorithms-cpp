/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
	struct Node {
		int data;
		Node* left;
		Node* right;
	}
*/

bool checkHelper(Node* root, const int& toLow, const int& toHigh)
{
    if (root == nullptr) return true;
    
    if (root->data <= toLow || root->data >= toHigh)
        return false;
    
    return checkHelper(root->left, toLow, root->data) && checkHelper(root->right, root->data, toHigh);
}

bool checkBST(Node* root) 
{
    return checkHelper(root, -1, 100000);
}