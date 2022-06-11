#ifndef VECTOR_H
# define VECTOR_H

#include <vector>
#include <memory>
namespace ft {

    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
        private:
            T *ptr;
            size_t size;
            size_t capacity;
            size_t max_size;


        public:
            typedef typename T value_type; //The first template parameter (T)	
            typedef typename Alloc allocator_type; //The second template parameter (Alloc)	defaults to: allocator<value_type>
            typedef typename T& reference; //allocator_type::reference	for the default allocator: value_type&
            typedef typename T& const const_reference; //allocator_type::const_reference	for the default allocator: const value_type&
            typedef typename T* pointer; //allocator_type::pointer	for the default allocator: value_type*
            typedef typename T* const const_pointer; //allocator_type::const_pointer	for the default allocator: const value_type*
            // typedef iterator; //a random access iterator to value_type	convertible to const_iterator
            // typedef const_iterator; //	a random access iterator to const value_type	
            // typedef reverse_iterator; //	reverse_iterator<iterator>	
            // typedef const_reverse_iterator; //	reverse_iterator<const_iterator>	
            // typedef difference_type; //a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
            typedef size_t size_type; //an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t

            explicit vector(const allocator_type& alloc = allocator_type())
            {
                ptr = 0;
                size = 0;
                capacity = 0;
                // max_size = ;
            };

            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            {
                

            };

            vector(T const & rhs);
            vector<T>& operator= (vector<T> const & x);
            ~vector();
    };

}


#endif