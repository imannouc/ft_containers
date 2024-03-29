#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include "../iterators/iterator.hpp"
# include "avl.hpp"
# include "../headers/pair.hpp"
# include <stdlib.h>

namespace ft {

template< class Key,class T,class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
	public:
		typedef Key                     key_type;
		typedef T                       mapped_type;
		typedef pair<const Key, T>      value_type;
		typedef Compare                 key_compare;

		// value_compare	Nested function class to compare elements	see value_comp
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			public:
				// typedef bool result_type;
				// typedef value_type first_argument_type;
				// typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
		};

		typedef Allocator   allocator_type;// allocator_type	The fourth template parameter (Alloc)	defaults to: allocator<value_type>
		typedef typename allocator_type::reference reference;// reference	allocator_type::reference	for the default allocator: value_type&
		typedef typename allocator_type::const_reference const_reference;// const_reference	allocator_type::const_reference	for the default allocator: const value_type&
		typedef typename allocator_type::pointer pointer;// pointer	allocator_type::pointer	for the default allocator: value_type*
		typedef typename allocator_type::const_pointer const_pointer;// const_pointer	allocator_type::const_pointer	for the default allocator: const value_type*
		typedef avl_tree<value_type, key_compare, allocator_type>		tree;
		typedef typename tree::node_pointer								node_pointer;
		typedef	ft::mapiterator<pointer, node_pointer>					iterator;
		typedef	ft::mapiterator<const_pointer, node_pointer>				const_iterator;
		typedef	ft::reverse_iterator<iterator>						reverse_iterator;
		typedef	ft::reverse_iterator<iterator>						const_reverse_iterator;
		typedef	typename allocator_type::difference_type 			difference_type;
		typedef	typename allocator_type::size_type 					size_type;
	
	private:
		tree			_tree;
		key_compare		_cmp;
		allocator_type	_alloc;
	
	public:
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(), _cmp(comp), _alloc(alloc) {}
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _tree(), _cmp(comp), _alloc(alloc)
		{
			while (first != last)
			{
				_tree.insert(*first);
				first++;
			}
		}
		map (const map& x) : _cmp(x._cmp), _alloc(x._alloc)
		{
			*this = x;
		}
		map& operator= (const map& x)
		{
			if (this == &x)
				return *this;
			_tree.clear();
			if (x.size())
				insert(x.begin(), x.end());
			_alloc = x._alloc;
			_cmp = x._cmp;
			return *this;
		}
		~map() {}

		iterator begin()
		{
			return (iterator(_tree.getMin()));
		}
		const_iterator begin() const
		{
			return (const_iterator(_tree.getMin()));
		}
		iterator end()
		{
			return (iterator(_tree.getEnd()));
		}
		const_iterator end() const
		{
			return (const_iterator(_tree.getEnd()));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->end()));
		}
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->end()));
		}
		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin()));
		}
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->begin()));
		}

		allocator_type get_allocator() const {return (this->_alloc);}
		size_type	size() const {return (_tree.size());}
		bool empty() const {return (size() == 0);}
		size_type	max_size() const {return (_tree.max_size());}
		void clear() {_tree.clear();}
		
		mapped_type& operator[] (const key_type& k)
		{
			value_type data = ft::make_pair(k, mapped_type());
			node_pointer	node = _tree.find(data);
			if (!node || node == _tree.getEnd())
			{
				_tree.insert(data);
				node = _tree.find(data);
			}
			return (node->_data.second);
		}
		pair<iterator,bool> insert (const value_type& val)
		{
			node_pointer	node = _tree.find(val);
			bool	notInserted = false;
			if (!node || node == _tree.getEnd())
			{
				_tree.insert(val);
				node = _tree.find(val);
				notInserted = true;
			}
			return (ft::make_pair(iterator(node), notInserted));
		}
		iterator insert (iterator position, const value_type& val)
		{
			static_cast<void>(position);
			node_pointer	node = _tree.find(val);
			if (!node || node == _tree.getEnd())
			{
				_tree.insert(val);
				node = _tree.find(val);
			}
			return (iterator(node));
		}
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_tree.insert(*first);
				first++;
			}
		}
		void erase (iterator position)
		{
			node_pointer node = position.base();
			if (node)
				_tree.erase(*position);
		}
		size_type erase (const key_type& k)
		{
			node_pointer node = _tree.find(ft::make_pair(k, mapped_type()));
			if (!node || node == _tree.getEnd())
				return (0);
			_tree.erase(node->_data);
			return (1);
		}
		void erase (iterator first, iterator last)
		{
			iterator tmp;
			while (first != last)
			{
				tmp = first++;
				erase(tmp);
				if (first == iterator(_tree.getEnd()))
					return ;
			}
		}
		void swap (map& x)
		{
			allocator_type	alloc = x.get_allocator();
			key_compare		cmp = x._cmp;
			x._alloc = this->get_allocator();
			x._cmp = this->_cmp;
			this->_alloc = alloc;
			this->_cmp = cmp;
			_tree.swap(x._tree);
		}
		iterator find (const key_type& k)
		{
			node_pointer	node = _tree.find(ft::make_pair(k, mapped_type()));
			return (iterator(node));
		}
		const_iterator find (const key_type& k) const
		{
			node_pointer	node = _tree.find(ft::make_pair(k, mapped_type()));
			return (const_iterator(node));
		}
		size_type count (const key_type& k) const
		{
			node_pointer	node = _tree.find(ft::make_pair(k, mapped_type()));
			
			if (!node || node == _tree.getEnd())
				return (0);
			return (1);
		}
		key_compare key_comp() const
		{
			return (this->_cmp);
		}
		value_compare value_comp() const
		{
			return (value_compare(_cmp));
		}
		iterator lower_bound (const key_type& k)
		{
			iterator it = find(k);
			if (it.base() == _tree.getEnd())
				it = iterator(_tree.lowerBound(ft::make_pair(k, mapped_type())));
			return (it);
		}
		const_iterator lower_bound (const key_type& k) const
		{
			const_iterator cit = find(k);
			if (cit.base() == _tree.getEnd())
				cit = const_iterator(_tree.lowerBound(ft::make_pair(k, mapped_type())));
			return (cit);
		}
		iterator upper_bound (const key_type& k)
		{
			iterator it = find(k);
			if (it.base() != _tree.getEnd())
				++it;
			else
				it = iterator(_tree.upperBound(ft::make_pair(k, mapped_type())));
			return (it);
		}
		const_iterator upper_bound (const key_type& k) const
		{
			const_iterator cit = find(k);
			if (cit.base() != _tree.getEnd())
				++cit;
			else
				cit = const_iterator(_tree.upperBound(ft::make_pair(k, mapped_type())));
			return (cit);
		}
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			return (ft::make_pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k)));
		}
		pair<iterator,iterator>             equal_range (const key_type& k)
		{
			return (ft::make_pair<iterator,iterator>(lower_bound(k), upper_bound(k)));
		}
    };
};

#endif