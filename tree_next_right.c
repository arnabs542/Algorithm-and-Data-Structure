https://leetcode.com/problems/populating-next-right-pointers-in-each-node/

//Solution 1: iterative:BFS, next pointer provides a best way for BFS as replace for queue 
void connect(TreeLinkNode *root) {
    //BFS, next pointer provides a best way for BFS as replace for queue 
    if(root==NULL)
        return;
    TreeLinkNode* node;    
    for(;root;root = root->left){  //for each level
        for(node = root;node->left;node=node->next){
            node->left->next = node->right;
            if(node->next && node->right)
                node->right->next = node->next->left;
            else
                break;   //end of far right of this level
        }
    }
}

//solution 2: recursive of solution 1
void connect(TreeLinkNode *root) {
    //BFS, next pointer provides a best way for BFS as replace for queue 
    if(root==NULL)
        return;
    if(root->left == NULL || root->right == NULL)
        return;
    
    TreeLinkNode* next_level = root->left; 
    TreeLinkNode* cur_level = root;
    while(cur_level){
        next_level->next = cur_level->right;
        next_level = next_level->next;
        cur_level = cur_level->next;
        if(cur_level){
            next_level->next = cur_level->left;
            next_level = next_level->next;
        }
    }
    connect(root->left);  //recursive: to next level
}

//solution 3, use queue to do BFS, can be used in moew genernal tree scenario such as none-fully established tree
//queue both nodes and level
//https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
void connect(TreeLinkNode *root) {
    //BFS
    if(root==NULL)
        return;
    
    std::list<TreeLinkNode*> node_list;
    std::list<int> level_list;
    node_list.push_back(root);
    int cur_level = 0;
    level_list.push_back(cur_level);
    while(!node_list.empty()){
        TreeLinkNode* cur = node_list.front();
        cur_level = level_list.front(); 
        node_list.pop_front();
        level_list.pop_front();
        if(level_list.empty()){
            //end of tree tracerse
            cur->next = NULL;
        }else{
            if(level_list.front()>cur_level){
                //traverse to end of current level
                cur->next = NULL;
            }else{
                cur->next = node_list.front();
            }
        }
        int next_level = cur_level+1;
        if(cur->left){
            node_list.push_back(cur->left);
            level_list.push_back(next_level);
        }
        if(cur->right){
            node_list.push_back(cur->right);
            level_list.push_back(next_level);
        }
    }
}
