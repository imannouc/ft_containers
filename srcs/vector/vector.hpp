#ifndef VECTOR_H
# define VECTOR_H

#include "iterator.hpp"
#include <memory>
#include <iostream>

namespace ft {

    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            typedef T value_type; //The first template parameter (T)	
            typedef Alloc allocator_type; //The second template parameter (Alloc)	defaults to: allocator<value_type>
            typedef T& reference; //allocator_type::reference	for the default allocator: value_type&
            typedef const T&  const_reference; //allocator_type::const_reference	for the default allocator: const value_type&
            typedef T* pointer; //allocator_type::pointer	for the default allocator: value_type*
            typedef const T*  const_pointer; //allocator_type::const_pointer	for the default allocator: const value_type*
            typedef size_t size_type; //an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t
            typedef MyIterator<pointer> iterator; //a random access iterator to value_type	convertible to const_iterator
            typedef MyIterator<const_pointer> const_iterator; //	a random access iterator to const value_type	
            // typedef typename std::vector<value_type>::reverse_iterator reverse_iterator; //	reverse_iterator<iterator>	
            // typedef typename std::vector<value_type>::const_reverse_iterator const_reverse_iterator; //	reverse_iterator<const_iterator>	
            typedef ptrdiff_t difference_type; //a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t

        private:
            pointer _value;// pointer type instead.
            size_type _size;
            size_type _capacity;
            allocator_type _alloc;

        public:
            //default constructor
            explicit vector(const allocator_type& alloc = allocator_type())
            {
                std::cout << " DEFAULT constructor CALLED " << std::endl;
                _value = 0;
                _size = 0;
                _capacity = 0;
                this->_alloc = alloc;
            };
            //fill constructor¸¸¸
            explicit vector(int n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            {
                std::cout << " FILL constructor CALLED " << std::endl;
                this->_alloc = alloc;
                try
                {
                    if (_size <= this->max_size())
                        this->_value = _alloc.allocate(n);// 0 2 4 8 16 32...
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                for (int i = 0; i < n ; i++)
                {
                    _alloc.construct(_value + i,val);
                }
                this->_size = n;
                this->_capacity = n;
            };
            //range constructor
            template <class InputIterator>
            vector (InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type())
            {
                std::cout << " RANGE constructor CALLED " << std::endl;
                this->_alloc = alloc;
                try
                {
                    this->_value = _alloc.allocate(last - first);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                for (size_type i = 0 ; i < (last - first) ; i++)
                {
                    _alloc.construct(_value + i ,*first);
                }
                this->_size = last - first;
                this->_capacity = last - first;
            };
            //copy constructor
            vector(const vector& x)
            {
                std::cout << " COPY constructor CALLED " << std::endl;
                *this = x;
            }
            vector& operator= (vector const & x)
            {
                std::cout << " operator = CALLED " << std::endl;
                if (this != &x)
                    return *this;
                // if vector we wish to copy to is full , empty it first, then copy.
                if (this->_size)
                {
                    for (int i = 0; i < this->_capacity ; i++)// destroy && deallocate
                    {
                        _alloc.destroy(_value + i);
                    }
                    _alloc.deallocate(this->_value,_capacity);
                }
                try
                {
                    this->_value = _alloc.allocate(x.capacity());
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                this->_size = x.size();
                this->_capacity = x.capacity();
                for (int i = 0; i < this->_size ; i++)
                {
                    _alloc.construct(_value + i,*(x._value + i));
                }
                return *this;
            }
            ~vector(){};

                            /* ITERATORS */
            iterator begin() { return (iterator(_value)); };
            const_iterator begin() const { return (const_iterator(_value)); };
            iterator end() { return (iterator(_value + _size)); };
            const_iterator end() const { return (const_iterator(_value + _size)); };
            // reverse_iterator rbegin();
            // const_reverse_iterator rbegin() const;
            // reverse_iterator rend();
            // const_reverse_iterator rend() const;
            
                            /* CAPACITY */
            size_type size() const { return _size; };
            size_type max_size() const { return this->_alloc.max_size(); };
            void resize (size_type n, value_type val = value_type())
            {
                if (n < _size)
                {//If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
                    for (int i = n ; i < _size ; i++)
                        _alloc.destroy(_value + i);
                }

            };
            size_type capacity() const { return _capacity; };
            bool empty() const { return (_size == 0); };
            // void reserve (size_type n);


                            /* ELEMENT ACCESS */
            reference operator[] (size_type n) { return (_value[n]); };
            reference at (size_type n)
            {
                if (n < 0 || n >= _size)
                    throw(std::out_of_range("at : index out of range."));
                return (_value[n]);
            };
            const_reference at (size_type n) const
            {
                if (n < 0 || n >= _size)
                    throw(std::out_of_range("at : index out of range."));
                return (_value[n]);
            };
            reference front() { return (_value[0]); };
            const_reference front() const { return (_value[0]); };
            reference back() { return (_value[_size - 1]); };
            const_reference back() const { return (_value[_size - 1]); };


                            /* MODIFIERS */

                            /* ALLOCATOR */
            allocator_type get_allocator() const { return _alloc; };
    };

}


#endif