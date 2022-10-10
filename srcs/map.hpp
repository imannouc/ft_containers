#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>

namespace ft {

    template< class Key,class T,class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
    class map {
        public:
            typedef std::pair<const Key, T> value_type;
            typedef Key                     key_type;// key_type	The first template parameter (Key)	
            typedef T                       mapped_type;// mapped_type	The second template parameter (T)	
            typedef Compare                 key_compare;// key_compare	The third template parameter (Compare)	defaults to: less<key_type>
            // value_compare	Nested function class to compare elements	see value_comp
            template <class Key, class T, class Compare, class Alloc>
            class value_compare : public std::binary_function<value_type, value_type, bool>
            {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
                friend class map;
                protected:
                    Compare comp;
                    value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                    bool operator() (const value_type& x, const value_type& y) const
                    {
                        return comp(x.first, y.first);
                    }
            };

            typedef Allocator   allocator_type;// allocator_type	The fourth template parameter (Alloc)	defaults to: allocator<value_type>
            typedef allocator_type::reference reference;// reference	allocator_type::reference	for the default allocator: value_type&
            typedef allocator_type::const_reference const_reference;// const_reference	allocator_type::const_reference	for the default allocator: const value_type&
            typedef allocator_type::pointer pointer;// pointer	allocator_type::pointer	for the default allocator: value_type*
            typedef allocator_type::const_pointer const_pointer;// const_pointer	allocator_type::const_pointer	for the default allocator: const value_type*
            // typedef iterator;// iterator	a bidirectional itgerator to value_type	convertible to const_iterator
            // typedef const_iterator;// const_iterator	a bidirectional iterator to const value_type	
            typedef reverse_iterator<iterator> reverse_iterator;// reverse_iterator	reverse_iterator<iterator>	
            typedef reverse_iterator<const_iterator> const_reverse_iterator;// const_reverse_iterator	reverse_iterator<const_iterator>	
            typedef ptrdiff_t difference_type;// difference_type	a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
            typedef size_t size_type;// size_type	an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t

        private:
            value_type data;



    };






};

#endif