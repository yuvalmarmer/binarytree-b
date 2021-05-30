
#pragma once
#include <queue>
#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>

using namespace std;
namespace ariel
{
    template <typename T>
    class BinaryTree
    {

        // Node class
        struct Node
        {   
            T value; //Value
            Node *left_child = nullptr; //Left child
            Node *right_child = nullptr; //Right child
            Node() {} ; 
            Node(T v) : value(v){}; // Default constructor
            Node(Node& other){  //Copy constructor
                this->left_child = other.left_child;
                this>right_child = other.right_child;
                this->value = other.value;
            }
            Node& operator=(Node&& other) noexcept{ // Move operator 
                this->left_child = other.left_child;
                this>right_child = other.right_child;
                this->value = other.value;
                return *this;
            }
            Node& operator=(Node other) noexcept{ //Copy assignment operator
                this->left_child = other.left_child;
                this>right_child = other.right_child;
                this->value = other.value;
                return *this;
            }
            Node(Node&& other) noexcept{ // Move constructor
                this->left_child = other.left_child;
                this>right_child = other.right_child;
                this->value = other.value;
            }
            ~Node() //Destructor
            {
                //If left child isnt null so delete it
                if (left_child != nullptr) 
                {
                    delete left_child;
                }
                //If right child isnt null so delete it
                if (right_child != nullptr)
                {
                    delete right_child;
                }
            }
        };

    public:
        //Root node for the binary tree
        Node *root = nullptr;

        // Default constructor
        BinaryTree(){} 
        
        // Default destructor
        ~BinaryTree(){  
            delete root; // Delete the root from memory
        }

        //Add root - if exist so replace the value 
        BinaryTree &add_root(T value) 
        {
            //If dont root exits - create new 
            if(root == nullptr){
                
                root = new Node(value);
            
            }
            //If root exits - replace the value 
            else{
            
                this->root->value = value;
            
            }
            return *this;
        };
       
        //Add left to parent - if parent dont exist throws exception
        BinaryTree &add_left(T parent, T child)
        {
            auto it = begin_inorder(); // Search inorder 
            int root_found = 0; // bool for finding the root
            
            //Searching for the parent node
            while (it != end_inorder())
            {
                if (*it == parent)
                {
                    root_found = 1;
                    break;
                }
                it++;
            }
            //If parent was found
            if (root_found != 0)
            {
                //Adding to the left
                if (it.current_node->left_child != NULL)
                {
                    it.current_node->left_child->value = child;
                }
                else
                {
                    it.current_node->left_child = new Node(child);
                }
            }
            else{
                //Throwing an execption - donsnt find a root 
                throw invalid_argument("No root like this");
            }
            return *this;
        };
       
        //Add right to parent - if parent dont exist throws exception
        BinaryTree &add_right(T parent, T child)
        {
            auto it = begin_inorder(); // Search inorder 
            int root_found = 0; // bool for finding the root

            //Searching for the parent node
            while (it != end_inorder())
            {
                if (*it == parent)
                {
                    root_found = 1; 
                    break;
                }
                it++;
            }

            //If parent was found
            if (root_found != 0)
            {
                //Adding to the right child
                if (it.current_node->right_child != NULL)
                {
                    it.current_node->right_child->value = child;
                }
                else
                {
                    it.current_node->right_child = new Node(child);
                }
            }
            else{
                //Throwing an execption - donsnt find a root 
                throw invalid_argument("No root like this");
            }
            return *this;
        };
        
        //Copy construtor
        BinaryTree(BinaryTree<T> const & t){
            this->root = copyTree(t.root);
        }

        //Move construtor
        BinaryTree(BinaryTree<T>&& other) noexcept {
            this->root  = other.root;
            other.root = nullptr;
	    }

        //Operator << thats pring the tree
        friend std::ostream &operator<<(std::ostream &os, const BinaryTree &n) {
            n.printBT("", n.root, false, os);
            return os;
        }

        //Recursive function for printing the binary tree
        void printBT(const std::string& prefix, const Node* node, bool isLeft, std::ostream &os) const
        {
            if( node != nullptr )
            {
                os << prefix;
                if(isLeft){
                    os << "├──";
                }
                else{
                    os << "└──";
                }
                // print the value of the node
                os << node->value << std::endl;

                // enter the next tree level - left and right branch
                printBT( prefix + (isLeft ? "│   " : "    "), node->left_child, true, os);
                printBT( prefix + (isLeft ? "│   " : "    "), node->right_child, false, os);
            }
        }
        
        //Preforming a deep copy of the tree
        Node* copyTree(Node* root1){
            //If node is nullptr get out of the recursive
            if(root1 == nullptr){
                return nullptr;
            }
            //Create new node
            Node* newRoot = new Node(root1->value);
            newRoot->left_child = copyTree(root1->left_child); //Copy left child
            newRoot->right_child = copyTree(root1->right_child); // Copy right child
            return newRoot;
        }
        
        //Operator = move 
        BinaryTree<T>& operator=(BinaryTree&& other) noexcept{
                if (root) {delete root;}
                root  = other.root;
                other.ptr = nullptr;
                return *this;
            }
        
        //Operator = move 
        BinaryTree<T>& operator=(BinaryTree<T> tree){
            if(this->root){ delete root;}
            this->root = copyTree(tree.root);
            return *this;
        }
        
        //-----------Iterator class------------
        class iterator{
        public:
            Node *current_node = nullptr;

            void init_inorder_queue(queue<Node *> &queue, Node *root)
            {

                if (root == NULL)
                {
                    return;
                }
                if (root->left_child != nullptr)
                {

                    init_inorder_queue(queue, root->left_child);
                }
                queue.push(root);

                if (root->right_child != nullptr)
                {

                    init_inorder_queue(queue, root->right_child);
                }
            };
            
            void init_postorder_queue(queue<Node *> &queue, Node *root)
            {
                if (root == nullptr)
                {
                    return;
                }

                if (root->left_child != nullptr)
                {
                    init_postorder_queue(queue, root->left_child);
                }

                if (root->right_child != nullptr)
                {
                    init_postorder_queue(queue, root->right_child);
                }
                queue.push(root);
            };
           
            void init_preorder_queue(queue<Node *> &queue, Node *root)
            {
                if (root == nullptr)
                {
                    return;
                }
                queue.push(root);
                if (root->left_child != nullptr)
                {
                    init_preorder_queue(queue, root->left_child);
                }

                if (root->right_child != nullptr)
                {
                    init_preorder_queue(queue, root->right_child);
                }
            };
           
            //Queue from preforming iteration over the tree
            queue<Node *> queue;
            
            //Constructor that get Node what order to preforme
            // 0 - inorder , 1- postorder , 2- preorder
            iterator(Node *ptr, int order)
            {
                switch (order)
                {
                //Init Inorder queue 
                case 0:
                    init_inorder_queue(queue, ptr);
                    break;

                //Init Postorder queue 
                case 1:
                    init_postorder_queue(queue, ptr);
                    break;

                //Init Preorder queue 
                case 2:
                    init_preorder_queue(queue, ptr);
                    break;
                
                default:
                    break;
                }
                //If queue isnt empty after initizition,
                //make the current node the front of queue
                if(!this->queue.empty()){
                    current_node = this->queue.front();    
                }
            }

            //Operator to get the value from current node
            T &operator*() const
            {
                return current_node->value;
            }

            //Operator to get the value by reference
            T *operator->() const
            {
                return &(current_node->value);                
            }

            //Get the next item in the iterator
            iterator &operator++()
            {
                if (queue.empty())
                {
                    current_node = nullptr;
                }
                else{
                queue.pop();
                current_node = queue.front();
                
                }
                return *this;
            }

            //Get the next item in the iterator
            iterator operator++(int)
            {

                iterator tmp = *this;
                if (queue.empty())
                {
                    current_node = nullptr;
                }
                else
                {
                    queue.pop(); //Pop from the queue 
                    current_node = queue.front(); //Repoint the curent node
                    
                }
                return tmp;
            }

            //Operator for == 
            bool operator==(const iterator &rhs) const
            {   
                //If the queue is empty and the other one isnt or the opossite -> return false
                if((queue.empty() && !rhs.queue.empty()) || (queue.empty() && !rhs.queue.empty())){
                    return false;
                } 
                if(queue.empty() && rhs.queue.empty()){
                    return true;
                }
                return current_node == rhs.current_node;
            }

            //Operator for !=
            bool operator!=(const iterator &rhs) const
            {
                //If the queue is empty and the other one isnt or the opossite -> return false
                if((queue.empty() && !rhs.queue.empty()) || (queue.empty() && !rhs.queue.empty())){
                    return true;
                }
                if(queue.empty() && rhs.queue.empty()){
                    return false;
                }
                return current_node != rhs.current_node;
            }
        };

        //Create preorder iterator
        iterator begin_preorder() { return iterator{root,2}; };
        
        //Create end preorder iterator
        iterator end_preorder() { return iterator{nullptr,2}; };

        //Create inorder iterator
        iterator begin_inorder() { return iterator{root,0}; };
        
        //Create end inorder iterator
        iterator end_inorder() { return iterator{nullptr,0}; };

        //Create postorder iterator
        iterator begin_postorder() { return iterator{root,1}; };
        
        //Create end postorder iterator
        iterator end_postorder() { return iterator{nullptr,1}; };

        //Create default begin iterator - inorder iterator 
        iterator begin()
        {
            return iterator{root,0};
        }

        //Creates default end iterator - inorder iterator
        iterator end()
        {
            return iterator{nullptr,0};
        }

    };
};