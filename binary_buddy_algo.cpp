// author: Pavan Kumar V Patil
// Roll No: 200030041
// date: 2023-04-06
// description: Implementation of binary buddy algorithm
// course: Operating Systems
// Institute: IIT Dharwad

#include <bits/stdc++.h>

using namespace std;

class Tree_Node
{
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
    Tree_Node(long long int size, long long int actual_size, char name, long long int id)
    {
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

void find_best_fit(Tree_Node *root, long long int size, Tree_Node **best_fit_node)
{
    if (root == NULL)
        return;
    find_best_fit(root->left, size, best_fit_node);
    if (root->is_free && root->size >= size)
    {
        if ((*best_fit_node) == NULL)
            *best_fit_node = root;
        else if (root->size < (*best_fit_node)->size)
            *best_fit_node = root;
        else if (root->size == (*best_fit_node)->size && root->counter < (*best_fit_node)->counter)
            *best_fit_node = root;
    }
    find_best_fit(root->right, size, best_fit_node);
}

void allocate_memory(Tree_Node *root, long long int size, char name, long long int &id, long long int lower_limit)
{
    Tree_Node *best_fit_node = NULL;
    find_best_fit(root, size, &best_fit_node);

    while (true)
    {
        if (best_fit_node->size / 2 >= size && best_fit_node->size / 2 >= lower_limit)
        {
            best_fit_node->is_divided = true;
            best_fit_node->is_free = false;
            best_fit_node->left = new Tree_Node(best_fit_node->size / 2, best_fit_node->actual_size / 2, '.', ++id);
            best_fit_node->right = new Tree_Node(best_fit_node->size / 2, best_fit_node->actual_size / 2, '.', ++id);
            best_fit_node->left->parent = best_fit_node;
            best_fit_node->right->parent = best_fit_node;
            best_fit_node = best_fit_node->left;
        }
        else
        {
            best_fit_node->is_free = false;
            best_fit_node->name = name;
            best_fit_node->id = ++id;
            best_fit_node->actual_size = size;
            break;
        }
    }
}

void find_free_memory(Tree_Node *root, char name, Tree_Node **find_free_node)
{
    if (root == NULL)
        return;
    find_free_memory(root->left, name, find_free_node);
    if (root->name == name)
    {
        (*find_free_node) = root;
        return;
    }
    find_free_memory(root->right, name, find_free_node);
}

void free_memory(Tree_Node *root, char name)
{
    Tree_Node *find_free_node = NULL;
    find_free_memory(root, name, &find_free_node);
    if (find_free_node == NULL)
        return;

    find_free_node->is_free = true;
    find_free_node->name = '.';
    find_free_node->actual_size = find_free_node->size;
    find_free_node->counter = 0;

    while(true)
    {
        if (find_free_node->parent == NULL)
        {
            break;
        }
        else if (find_free_node->parent->left->is_free && find_free_node->parent->right->is_free)
        {
            find_free_node->parent->is_divided = false;
            find_free_node->parent->is_free = true;
            find_free_node->parent->counter = 0;
            find_free_node->parent->name = '.';
            find_free_node->parent->actual_size = find_free_node->parent->size;
            delete find_free_node->parent->left;
            delete find_free_node->parent->right;
            find_free_node->parent->left = NULL;
            find_free_node->parent->right = NULL;
            find_free_node = find_free_node->parent;
        }
        else
        {
            break;
        }
    }
}

void increase_counter_all(Tree_Node *root)
{
    if (root == NULL)
        return;
    increase_counter_all(root->left);
    if (root->is_free)
        root->counter++;
    increase_counter_all(root->right);
}

void print_leaf_nodes(Tree_Node *root)
{
    if (root == NULL)
        return;
    print_leaf_nodes(root->left);
    if (root->left == NULL && root->right == NULL)
    {
        if (root->is_free)
            cout << "Free Block: " << root->size << endl;
        else
            cout << root->name << ": " << root->actual_size << endl;
    }
    print_leaf_nodes(root->right);
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./a.out <input_file>" << endl;
        return 0;
    }

    ifstream infile(argv[1]);
    if (!infile.is_open())
    {
        cout << "Error in opening file" << endl;
        return 0;
    }

    int no_of_test_cases;
    infile >> no_of_test_cases;
    string read_line;
    getline(infile, read_line); // to read the empty line
    while (no_of_test_cases--)
    {
        long long int upper_limit, lower_limit;
        infile >> upper_limit >> lower_limit;

        upper_limit = pow(2, upper_limit);
        lower_limit = pow(2, lower_limit);

        getline(infile, read_line); // to read the empty line
        getline(infile, read_line); // to read the empty line

        vector<pair<char, int>> requests;
        while (getline(infile, read_line) && read_line != "")
        {
            char name;
            long long int size;
            sscanf(read_line.c_str(), "%c %llu", &name, &size);
            requests.push_back(make_pair(name, size));
        }
        long long int id = 0;

        Tree_Node *root = new Tree_Node(upper_limit, upper_limit, '.', id);

        for (auto request : requests)
        {
            char name = request.first;
            long long int size = request.second;
            if (size == 0)
            {
                free_memory(root, name);
            }
            else
            {
                allocate_memory(root, size, name, id, lower_limit);
            }
            increase_counter_all(root);
        }

        print_leaf_nodes(root);
        cout << endl;
    }
    return 0;
}