#Level Order Traversal
````
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == NULL)
            return ans;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            vector<int> level;
            for (int i = 0; i < size; i++) {
                TreeNode* newNode = q.front();
                q.pop();
                if (newNode->left != NULL)
                    q.push(newNode->left);
                if (newNode->right != NULL)
                    q.push(newNode->right);
                level.push_back(newNode->val);
            }
            ans.push_back(level);
        }
        return ans;
    }
};
````