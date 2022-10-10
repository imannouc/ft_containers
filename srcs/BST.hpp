#ifndef BST_HPP
# define BST_HPP

namespace ft
{
	template <class T>
	struct node {
		typedef T value_type;

		value_type	_data;
		node		*_right;
		node		*_left;
		node		*_parent;
		int		    balanceFactor;
		int		    height;

		node() : _data(), _right(nullptr), _left(nullptr), _parent(nullptr) {}
		node(value_type data) : _data(data) {}
		node(const value_type& data, const int height) : _data(data), _parent(nullptr), _left(nullptr), _right(nullptr), balanceFactor(0), height(height) {}
	};

    class avl_tree
    {
    private:
        /* data */
    public:
        avl_tree(/* args */);
        ~avl_tree();
    };
}
/*

Avl tree remove node
1)Find the element.
2)Replace the noe we want to remove with its successor (if any) to maitain BST invariant

@ Find phase : one of the four things will happen when searching BST for an element with a particular value
1) We hit a null node --> the value does not exist in our BST
2) Comp value == 0 (Found it)
3) Comp value < 0 , find(left);
4) Comp value > 0 , find(right);

@ Remove phase
    Four Cases
    1) Node to remove has no subtree (Node is a leaf)
    2) Node to remove has a right subtree only.
    3) Node to remove has a left subtree only.
    4) Node to remove has both left and right subtree.

        case 1 :
            remove without any side effect
        case 2 & 3 :
            replace with The successor immediate node down. (link it back to removed node parent)
        case 4 :
            The successor can either be the largest value in the left subtree
            OR the smallest value in the right subtree
    !!
        Once the successor node has been identified(if it exists) 
        replace the value of node to remove with value of successor node.
    Note:
        remove duplicate successor node that still exists in the tree at this point.
        call remove revursively on successor.
@ After removal
# Update balance factor.
# Rebalance tree.



Height of a node = max(h(left),h(right)) + 1;


*/
#endif