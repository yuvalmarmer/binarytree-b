
#pragma once
#include <queue>
#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;
namespace ariel
{
    template <typename T>
    class BinaryTree
    {

        // Node class
        struct Node
        {
            T value;
            Node *left_child = nullptr;
            Node *right_child = nullptr;
            Node() {} ;
            Node(T v) : value(v){};
            Node(Node& other){
                this->left_child = other.left_child;
                this>right_child = other.right_child;
                this->value = other.value;
            }
            Node& operator=(Node&& other) noexcept{
                this->left_child = other.left_child;
                this>right_child = other.right_child;
                this->value = other.value;
                return *this;
            }
            Node& operator=(Node other) noexcept{
                this->left_child = other.left_child;
                this>right_child = other.right_child;
                this->value = other.value;
                return *this;
            }
            Node(Node&& other) noexcept{
                this->left_child = other.left_child;
                this>right_child = other.right_child;
                this->value = other.value;
            }
            ~Node()
            {
                if (left_child != nullptr)
                {
                    delete left_child;
                }
                if (right_child != nullptr)
                {
                    delete right_child;
                }
            }
        };

    public:
        // fields
        Node *root = nullptr;
        vector<Node*> inorderVector;
        vector<Node*> preorderVector;
        vector<Node*> postorderVector;

        void init_vectors(Node *root){
            inorderVector.clear();
            preorderVector.clear();
            postorderVector.clear();

            init_inorder_vector(inorderVector,root);
            init_postorder_vector(preorderVector,root);
            init_preorder_vector(postorderVector,root);
        }

        void init_inorder_vector(std::vector<Node *> &vector, Node *root)
        {
            if (root == NULL)
            {
                return;
            }
            if (root->left_child != nullptr)
            {

                init_inorder_vector(vector, root->left_child);
            }
            vector.push_back(root);

            if (root->right_child != nullptr)
            {

                init_inorder_vector(vector, root->right_child);
            }
        };
        
        void init_postorder_vector(std::vector<Node *> &vector, Node *root)
        {
            if (root == nullptr)
            {
                return;
            }

            if (root->left_child != nullptr)
            {
                init_postorder_vector(vector, root->left_child);
            }

            if (root->right_child != nullptr)
            {
                init_postorder_vector(vector, root->right_child);
            }
            vector.push_back(root);
        };
        
        void init_preorder_vector(std::vector<Node *> &vector, Node *root)
        {
            if (root == nullptr)
            {
                return;
            }
            vector.push_back(root);
            if (root->left_child != nullptr)
            {
                init_preorder_vector(vector, root->left_child);
            }

            if (root->right_child != nullptr)
            {
                init_preorder_vector(vector, root->right_child);
            }
        };
        
        BinaryTree()
        {
            // root = new Node();
        }
        ~BinaryTree(){
            delete root;
        }
        BinaryTree &add_root(T value)
        {
            if(root == nullptr){
                
                root = new Node(value);
          
            }
            else{
                this->root->value = value;
            }
            init_vectors(this->root);
            return *this;
        };
        BinaryTree &add_left(T prev, T child)
        {
            auto it = begin_inorder();
            int root_found = 0;
            while (it != end_inorder())
            {
                if (*it == prev)
                {
                    root_found = 1;
                    break;
                }
                it++;
            }

            if (root_found != 0)
            {
                
                if (it.current_node->left_child != NULL)
                {
                    it.current_node->left_child->value = child;
                }
                else
                {
                    it.current_node->left_child = new Node(child);
                }
                init_vectors(this->root);
            }
            else{
                throw invalid_argument("No root like this");
            }
            return *this;
        };
        BinaryTree &add_right(T prev, T child)
        {
            auto it = begin_inorder();
            int root_found = 0;

            while (it != end_inorder())
            {
                if (*it == prev)
                {
                    root_found = 1; 
                    break;
                }
                it++;
            }

            if (root_found != 0)
            {

                if (it.current_node->right_child != NULL)
                {
                    it.current_node->right_child->value = child;
                }
                else
                {
                    it.current_node->right_child = new Node(child);
                }
                init_vectors(this->root);
            }
            else{
                throw invalid_argument("No root like this");
            }
            return *this;
        };
        BinaryTree(BinaryTree<T> const & t){
            this->root = copyTree(t.root);
        }

        BinaryTree(BinaryTree<T>&& other) noexcept {
            this->root  = other.root;
            other.root = nullptr;
	    }

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree &n) { return os; };

        Node* copyTree(Node* root1){
            if(root1 == nullptr){
                return nullptr;
            }
            Node* newRoot = new Node(root1->value);
            newRoot->left_child = copyTree(root1->left_child);
            newRoot->right_child = copyTree(root1->right_child);
            return newRoot;
        }
        BinaryTree<T>& operator=(BinaryTree&& other) noexcept{
                if (root) {delete root;}
                root  = other.root;
                other.ptr = nullptr;
                return *this;
            }

        BinaryTree<T>& operator=(BinaryTree<T> tree){
            if(this->root){ delete root;}
            this->root = copyTree(tree.root);
            return *this;
        }
        // 0 - in , 1- post , 2- pre
        class iterator{
        public:

            Node *current_node = nullptr;
            vector<Node*>& current_vector;
            vector<Node*>::iterator it_vec;
            iterator(Node *ptr, int order)
            {
                switch (order)
                {
                case 0:
                    current_vector = inorderVector;
                    break;
                case 1:
                    current_vector = postorderVector;
                    break;

                case 2:
                    current_vector = preorderVector;
                    break;
                
                default:
                    break;
                }

                if(!this->current_vector.empty()){
                    current_node = this->current_vector.front();    
                    it_vec = current_vector.begin()
                }
            }

            T &operator*() const
            {
                //return *pointer_to_current_node;
                // return current_node->value;
                return *it_vec;
            }

            T *operator->() const
            {
                // return &(current_node->value);
                // T& temp;
                // return temp;
                return &(*it_vec);
            }

            // ++i;
            iterator &operator++()
            {
                // if (current_vector.empty())
                // {
                //     current_node = nullptr;
                // }
                // else{
                // queue.pop();
                // current_node = queue.front();
                
                // }
                it_vec++;
                return *this;
            }


            iterator operator++(int)
            {

                iterator tmp = *this;
                // if (queue.empty())
                // {
                //     current_node = nullptr;
                // }
                // else
                // {
                //     queue.pop();
                //     current_node = queue.front();
                    
                // }
                it_vec++;
                return tmp;
            }

            bool operator==(const iterator &rhs) const
            {
                // if((queue.empty() && !rhs.queue.empty()) || (queue.empty() && !rhs.queue.empty())){
                //     return false;
                // } 
                // if(queue.empty() && rhs.queue.empty()){
                //     return true;
                // }
                return it_vec == rhs.it_vec;
            }

            bool operator!=(const iterator &rhs) const
            {
                // if((queue.empty() && !rhs.queue.empty()) || (queue.empty() && !rhs.queue.empty())){
                //     return true;
                // }
                // if(queue.empty() && rhs.queue.empty()){
                //     return false;
                // }
                return it_vec != rhs.it_vec;
            }
        };

        
        iterator begin_preorder() { return iterator{root,2}; };
        iterator end_preorder() { return iterator{nullptr,2}; };

        iterator begin_inorder() { return iterator{root,0}; };
        iterator end_inorder() { return iterator{nullptr,0}; };

        iterator begin_postorder() { return iterator{root,1}; };
        iterator end_postorder() { return iterator{nullptr,1}; };

        iterator begin()
        {
            return iterator{root,0};
        }

        iterator end()
        {
            return iterator{nullptr,0};
        }

    private:
    };
} // namespace ariel