#include<bits/stdc++.h>

using namespace std;

class Tree_Node{
    public:
    long long int size;
    long long int actual_size;
    char name;
    long long int id;
    bool is_free;
    bool is_divided;
    long long int counter;    
    Tree_Node *left;
    Tree_Node *right;
    Tree_Node *parent;
    Tree_Node(long long int size,long long int actual_size, char name, long long int id){
        this->size = size;
        this->actual_size = actual_size;
        this->name = name;
        this->id = id;
        this->is_free = true;
        this->is_divided = false;
        this->counter = 0;
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
    }
};

void find_best_fit(Tree_Node *root, long long int size, Tree_Node *best_fit_node)
{
    cout<< "Finding best fit for " << size << endl;
    if(root == NULL)
        return;
    find_best_fit(root->left, size, best_fit_node);
    if(root->is_free && root->size >= size){
        cout << "Found free node: " << root->size << endl;
        if(best_fit_node == NULL)
            best_fit_node = root;
        else if(root->size < best_fit_node->size)
            best_fit_node = root;
        else if(root->size == best_fit_node->size && root->counter < best_fit_node->counter)
            best_fit_node = root;
    }
    find_best_fit(root->right, size, best_fit_node);
}

void allocate_memory(Tree_Node *root, long long int size, char name, long long int& id,long long int lower_limit){
    cout<< "Allocating memory for " << name << " of size " << size << endl;
    Tree_Node* best_fit_node;
    find_best_fit(root, size, best_fit_node);

    cout << "Best fit node: " << best_fit_node->size << endl;

    while(true)
    {
        if(best_fit_node->size/2 >= size && best_fit_node->size/2 >= lower_limit){
            best_fit_node->is_divided = true;
            best_fit_node->is_free = false;
            best_fit_node->left = new Tree_Node(best_fit_node->size/2, best_fit_node->actual_size/2, '.', ++id);
            best_fit_node->right = new Tree_Node(best_fit_node->size/2, best_fit_node->actual_size/2, '.', ++id);
            best_fit_node->left->parent = best_fit_node;
            best_fit_node->right->parent = best_fit_node;
            best_fit_node = best_fit_node->left;
        }
        else{
            best_fit_node->is_free = false;
            best_fit_node->name = name;
            best_fit_node->id = ++id;
            best_fit_node->actual_size = size;
            break;
        }
    }

}

void free_memory(Tree_Node* root, char name)
{
    if(root == NULL)
        return;
    free_memory(root->left, name);
    if(root->name == name){
        root->is_free = true;
        root->name = '.';
        root->id = 0;
        root->actual_size = 0;
        if(root->parent != NULL && root->parent->left->is_free && root->parent->right->is_free){
            root->parent->is_divided = false;
            root->parent->is_free = true;
            root->parent->counter = 0;
            root->parent->name = '.';
            root->parent->actual_size = root->parent->size;
            delete root->parent->left;
            delete root->parent->right;
            root->parent->left = NULL;
            root->parent->right = NULL;
            return;
        }
    }
    free_memory(root->right, name);
}

void increase_counter_all(Tree_Node* root)
{
    if(root==NULL)
        return;
    increase_counter_all(root->left);
    if(root->is_free)
        root->counter++;
    increase_counter_all(root->right);
}

void print_leaf_nodes(Tree_Node* root)
{
    if(root == NULL)
        return;
    print_leaf_nodes(root->left);
    if(root->left == NULL && root->right == NULL)
    {
        if(root->is_free)
            cout << "Free Block: "<< root->size << endl;
        else
            cout << root->name << ": "<< root->actual_size << endl;
    }
    print_leaf_nodes(root->right);
}

int main()
{
    ifstream infile("input.txt");
    int no_of_test_cases;
    infile >> no_of_test_cases;
    string read_line;
    getline(infile, read_line); // to read the empty line

    while(no_of_test_cases--){
        long long int upper_limit,lower_limit;
        infile >> upper_limit >> lower_limit;

        upper_limit = pow(2, upper_limit);
        lower_limit = pow(2, lower_limit);
        

        getline(infile, read_line);// to read the empty line
        getline(infile, read_line); // to read the empty line

        vector<pair<char,int>> requests;
        while(getline(infile, read_line) && read_line != "")
        {
            cout<< read_line << endl;
            char name;
            long long int size;
            sscanf(read_line.c_str(), "%c %llu", &name, &size);
            requests.push_back(make_pair(name, size));
        }
        long long int id = 0;

        Tree_Node *root = new Tree_Node(upper_limit, upper_limit,'.', id);
        
        for(auto request: requests){
            char name = request.first;
            long long int size = request.second;
            if(size == 0){
                free_memory(root, name);
            }
            else
            {
                allocate_memory(root, size, name, id, lower_limit);
            }
            increase_counter_all(root);
        }

        print_leaf_nodes(root);
    }
    return 0;
}