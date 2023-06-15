/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution 
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        if (root == nullptr) 
            return nullptr;
        
		if (root->val == p->val || root->val == q->val)
            return root;
        
        TreeNode* leftChild = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightChild = lowestCommonAncestor(root->right, p, q);
        
        if (leftChild != nullptr && rightChild != nullptr)
            return root;
        
        if (leftChild != nullptr)
            return leftChild;
        
        if (rightChild != nullptr)
            return rightChild;
        
        return nullptr;
    }
};