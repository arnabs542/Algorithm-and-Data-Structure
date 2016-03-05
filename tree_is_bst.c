https://leetcode.com/problems/validate-binary-search-tree/
//Two ways

//Method 1: recursive
bool isBSTHelper(BinaryTree *p, long low, long high) {
	if (!p) return true;
	if (low < p->data && p->data < high)
		return isBSTHelper(p->left, low, p->data) &&
		isBSTHelper(p->right, p->data, high);
	else
		return false;
}

bool isBST(BinaryTree *root) {
	// INT_MIN and INT_MAX are defined in C++'s <climits> library
	return isBSTHelper(root, LONG_MIN, LONG_MAX);
}

//method 2: iterative
bool isValidBST(TreeNode *root) {
	if (root == NULL)
		return true;
	//Iterative, Since in order traverse of BST should be an array in ascend order
	stack<TreeNode*> s;
	TreeNode *node = root;
	TreeNode *cur;
	long min = LONG_MIN;
	while (!s.empty() || node) {
		while (node) {
			s.push(node);
			node = node->left;
		}
		cur = s.top();
		s.pop();
		if (cur->val >min) {
			min = cur->val;
		}
		else {
			return false;
		}
		node = cur->right;
	}

	return true;
}
