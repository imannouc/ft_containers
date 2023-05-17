#ifndef AVL_HPP
# define AVL_HPP
#include "../iterators/iterator.hpp"
#include <memory>

namespace ft
{
	template <class T>
	struct node {
		typedef T value_type;

		value_type	_data;
		node		*_right;
		node		*_left;
		node		*_parent;
		int		    height;
		int		    balanceFactor;

		node() : _data(), _right(NULL), _left(NULL), _parent(NULL) {}
		node(value_type data) : _data(data) {}
		node(const value_type& data, const int height) : _data(data), _right(NULL), _left(NULL),_parent(NULL), height(height), balanceFactor(0) {}
	};

	template <class T, class Compare, class Alloc> 
    class avl_tree
    {
        public:
            typedef T															value_type;
			typedef Compare														key_compare;
			typedef node<T>*													node_pointer;
			typedef typename Alloc::template rebind<node<T> >::other			allocator_type;
			typedef	typename allocator_type::size_type 							size_type;
    
        private:
            node_pointer _root;
            node_pointer _end;
            allocator_type	_alloc;
			key_compare		_cmp;
			size_type		_size;

        public:
			avl_tree(const allocator_type& alloc = allocator_type(), const key_compare& cmp = key_compare()) : _root(NULL), _end(NULL), _alloc(alloc), _cmp(cmp), _size(0)
			{
				_end = _alloc.allocate(1);
				_alloc.construct(_end);//test
			}
			~avl_tree()
			{
				clear();
				_alloc.deallocate(_end, 1);
				_end = NULL;
			}
            size_type size() const
            {
                return _size;
            }
			size_type max_size() const
            {
                return _alloc.max_size();
            }
			allocator_type get_allocator() const
            {
                return (this->_alloc);
            }
			node_pointer	getEnd() const
            {
                return (this->_end);
            }
            node_pointer	getMin(node_pointer node = NULL) const
			{
				if (!node)
					node = _root;
				while (node && node->_left)
					node = node->_left;
				return node;
			}
			node_pointer	getMax(node_pointer node = NULL)
			{
				if (!node)
					node = _root;
				while (node && node->_right)
					node = node->_right;
				return node;
			}
            node_pointer	lowerBound(const value_type& data)
			{
				node_pointer node = getMin();
                while (node != _end)
                {
                    if (!_cmp(node->_data.first, data.first))
                        return (node);
                    node = successor(node);
                }
                return (_end);
			}
			node_pointer	upperBound(const value_type& data)
			{
				node_pointer node = getMin();
                while (node != _end)
                {
                    if (_cmp(data.first, node->_data.first))
                        return (node);
                    node = successor(node);
                }
                return (_end);
			}
            void	swap(avl_tree& tree)
			{
				node_pointer			root = _root;
				node_pointer			end = _end;
				allocator_type	alloc = _alloc;
				key_compare		cmp = _cmp;
				size_type		size = _size;

				_root = tree._root;
				_end = tree._end;
				_alloc = tree._alloc;
				_cmp = tree._cmp;
				_size = tree._size;
				
				tree._root = root;
				tree._end = end;
				tree._alloc = alloc;
				tree._cmp = cmp;
				tree._size = size;
			}
            void	clear()
			{
				clear(_root);
				_size = 0;
			}
			node_pointer	find(const value_type& data)
			{
				return find(data, _root);
			}
			void	insert(const value_type data)
			{
				insert(data, _root, _end);
				_end->_left = _root;
				_root->_parent = _end;
			}
			void	erase(const value_type& data)
			{
				erase(_root, data);
				_end->_left = _root;
				if (_root)
					_root->_parent = _end;
			}
        private:
            void	eraseHelper(node_pointer &node, node_pointer& parent)
			{
				node_pointer tmp;
				if (node->_right)
					tmp = node->_right;
				else
					tmp = node->_left;
				if (tmp)
					tmp->_parent = parent;
				_alloc.deallocate(node, 1);
				node = tmp;
				_size--;
			}
			void	erase (node_pointer &node, const value_type& data)
			{
				if (!node)
					return ;
				if (node->_data.first == data.first)
				{
					if (!node->_left || !node->_right)
					{
						eraseHelper(node, node->_parent);
						return ;
					}
					else
					{
						if (node->_left->height > node->_right->height)
						{
							value_type value(getMax(node->_left)->_data);
							_alloc.construct(node, value);
							erase(node->_left, value);
						}
						else
						{
							value_type value(getMin(node->_right)->_data);
							_alloc.construct(node, value);
							erase(node->_right, value);
						}
					}
				}
				else if (_cmp(data.first, node->_data.first))
					erase(node->_left, data);
				else
					erase(node->_right, data);
				update(node);
				balance(node);
			}
			void	insert(const value_type& data, node_pointer &node, node_pointer& parent)
			{
				if (!node)
				{
					node = _alloc.allocate(1);
					_alloc.construct(node, data,0);//
					node->_parent = parent;
					_size++;
					return ;
				}
				if (_cmp(data.first, node->_data.first))
					insert(data, node->_left, node);
				else
					insert(data, node->_right, node);
				update(node);
				balance(node);
			}
			node_pointer	find(const value_type& data, node_pointer& node)
			{
				if (!node || node == _end)
					return (_end);
				if (data.first == node->_data.first)
					return (node);
				if (_cmp(data.first, node->_data.first))
					return (find(data, node->_left));
				return (find(data, node->_right));
			}
			node_pointer	successor(node_pointer node)
			{
				node_pointer	parent = node->_parent;
				node_pointer	tmp = node;
				if (tmp->_right)
				{
					tmp = tmp->_right;
					while (tmp->_left)
						tmp = tmp->_left;
					return tmp;
				}
				else
				{
					while (parent && tmp == parent->_right)
					{
						tmp = parent;
						parent = tmp->_parent;
					}
					return (parent);
				}
			}
			void	clear(node_pointer &node)
			{
				if (node)
				{
					clear(node->_left);
					clear(node->_right);
					_alloc.deallocate(node, 1);
					node = NULL;
				}
			}
			void	update(node_pointer node)
			{
				int	leftNodeHeight = -1;
				int	rightNodeHeight = -1;
				
				if (node->_left)
					leftNodeHeight = node->_left->height;
				if (node->_right)
					rightNodeHeight = node->_right->height;

				int diff = ((leftNodeHeight > rightNodeHeight) ? leftNodeHeight : rightNodeHeight);
				node->height = 1 + diff;
				node->balanceFactor = rightNodeHeight - leftNodeHeight;
			}
			void	balance(node_pointer &node)
			{
				if (node->balanceFactor < -1)
				{
					if (node->_left->balanceFactor <= 0)
						leftLeftCase(node);
					else
						leftRightCase(node);
				}
				else if (node->balanceFactor > 1)
				{
					if (node->_right->balanceFactor >= 0)
						rightRightCase(node);
					else
						rightLeftCase(node);
				}
			}
			void	leftRotation(node_pointer &node)
			{
				node_pointer	parent = node->_parent;
				node_pointer	root = node->_right;
				node->_right = root->_left;
				if (node->_right)
					node->_right->_parent = node;
				node->_parent = root;
				root->_left = node;
				root->_parent = parent;
				node = root;
				update(node->_left);
				update(node);
			}		
			void	rightRotation(node_pointer &node)
			{
				node_pointer	parent = node->_parent;
				node_pointer	root = node->_left;
				node->_left = root->_right;
				if (node->_left)
					node->_left->_parent = node;
				node->_parent = root;
				root->_right = node;
				root->_parent = parent;
				node = root;
				update(node->_right);
				update(node);
			}		
			void	leftLeftCase(node_pointer &node)
			{
				rightRotation(node);
			}
			void	leftRightCase(node_pointer &node)
			{
				leftRotation(node->_left);
				rightRotation(node);
			}
			void	rightRightCase(node_pointer &node)
			{
				leftRotation(node);
				
			}
			void	rightLeftCase(node_pointer &node)
			{
				rightRotation(node->_right);
				leftRotation(node);
			}
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