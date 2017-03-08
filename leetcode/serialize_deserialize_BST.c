//https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
//used for store or transfer data

//Make use of pre order traversal 
class Codec {
public:
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        if(root == NULL)
            return s;
        s+=to_string(root->val);
        s+=",";
        
        serialize_helper(root->left,s);
        serialize_helper(root->right,s);
        
        return s.substr(0,s.size()-1);
    }
    
    void serialize_helper(TreeNode* root, string &s){
        if(root==NULL){
            s+='#';
            s+=",";
            return ;
        }else{
            s+=to_string(root->val);
            s+=",";
        }
        serialize_helper(root->left,s);
        serialize_helper(root->right,s);    
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {         
        if(data.empty()) 
            return NULL;
        int index = 0;
        return deserialize_helper(data, index);
    }

     TreeNode* deserialize_helper(string& data, int & index) {
        if(data[index]=='#'){
            index++;
            if (index < data.size()) //pass ','
                index++;
            return NULL;
        }
        
        TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
        string cur = "";
        int start = index;
        while(data[index]!=','){
            index++;
        }
        cur = data.substr(start,index-start);
        node->val = stoi(cur);
        index++; //pass ','
        
        node->left = deserialize_helper(data,index);
        node->right = deserialize_helper(data,index);
        
        return node;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
