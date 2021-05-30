
#include "BinaryTree.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
using namespace std;
using namespace ariel;


template<typename T>//t
BinaryTree<T> create_simple_tree(int adder = 0) {
    BinaryTree<T> tree;

    // create the following tree
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23
    tree.add_root(1 + adder);
    tree.add_left(1 + adder, 2 + adder);

    tree.add_right(1 + adder, 3 + adder);
    tree.add_left(2 + adder, 4 + adder);
    tree.add_right(2 + adder, 5 + adder);
    tree.add_left(5 + adder, 10 + adder);
    tree.add_right(5 + adder, 11 + adder);
    tree.add_left(10 + adder, 20 + adder);
    tree.add_right(11 + adder, 23 + adder);



    return tree;
}



int main(){

    cout << "[*]        Creating simple tree        [*]" << endl << endl;    
    BinaryTree<int> tree = create_simple_tree<int>();

    cout << "[-] Print test" << endl << endl; 
    cout << tree << endl;

    cout << "[-] Changing the root to 999" << endl << endl;
    tree.add_root(999);
    cout << tree << endl;

    cout << "[-] Changing the '5' to '55'" << endl << endl;
    tree.add_right(2,55);
    cout << tree << endl;

    cout << "[-] Adding left child '223' to '3' " << endl << endl;
    tree.add_left(3,223);
    cout << tree << endl;

    cout << "[-] Adding right child '222' to '3' " << endl << endl;
    tree.add_right(3,222);
    cout << tree << endl;

    cout << "[-] Preorder iterator check and print it" << endl << endl;
    for (auto it = tree.begin_preorder();it != tree.end_preorder(); it++){
        cout << *it << " " ;
    }
    cout << endl <<endl;
    cout << "[-] Inorder iterator check and print it" << endl << endl;
    for (auto it = tree.begin_inorder();it!= tree.end_inorder(); it++){
        cout << *it << " " ;
    }
    cout << endl << endl;
    cout << "[-] Postorder iterator check and print it " << endl << endl;
    for (auto it = tree.begin_postorder();it!= tree.end_postorder(); it++){
        cout << *it << " " ;
    }
    cout << endl;

    return 0;
}