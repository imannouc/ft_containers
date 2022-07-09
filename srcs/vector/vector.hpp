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
                        this->_value = _alloc.allocate(n);
                        std::cout << "allocated " << n << " elements \n";
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                for (int i = 0; i < n ; i++)
                    _alloc.construct(_value + i,val);
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
                    _alloc.construct(_value + i ,*first);
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
                if (this == &x)
                    return *this;
                // if vector we wish to copy to is full , empty it first, then copy.
                if (this->_size)
                {
                    for (int i = 0; i < this->_capacity ; i++)
                        _alloc.destroy(_value + i);
                    _alloc.deallocate(this->_value,_capacity);
                    _size = 0;
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
                    _alloc.construct(_value + i,*(x._value + i));
                return *this;
            }
            ~vector()
            {
                if (_size > 0)
                    for (size_type i = 0; i < _size; i++)
                        _alloc.destroy(_value + i);
                if (_capacity > 0)
                    _alloc.deallocate(_value, _capacity);
            };

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
                {
                    for (int i = n ; i < _size ; i++)
                        _alloc.destroy(_value + i);
                    _size = n;
                }
                else if (n > _size)
                {
                    reserve(n);
                    for (int i = _size ; i < n ; i++)
                        _alloc.construct(_value + i,val);
                    _size = n;
                }
            };
            size_type capacity() const { return _capacity; };
            bool empty() const { return (_size == 0); };
            void reserve (size_type n)
            {
                if (n > _capacity) 
                {
                    if ( _capacity * 2 > n )
                        n = _capacity * 2;
                    if (n > max_size())
                        throw(std::length_error("reserve : length error."));
                    pointer newValue;
                    newValue = _alloc.allocate(n);
                    for (int i = 0; i < this->_size ; i++)
                        _alloc.construct(newValue + i, this->_value[i]);
                    for (int i = 0; i < this->_capacity ; i++)
                        _alloc.destroy(_value + i);
                    _alloc.deallocate(this->_value,_capacity);
                    this->_value = newValue;
                    this->_capacity = n;
                }
            };


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
            template <class InputIterator>
            void assign (InputIterator first, InputIterator last)
            {
                vector tmp(first,last);
                *this = tmp;
            };
            void assign (size_type n, const value_type& val)
            {
                vector tmp(n, val);
                *this = tmp;
            };
            void    push_back(const value_type& val)
            {
                reserve( _size + 1);
                _alloc.construct(_value + _size , val);
                _size++;
            };
            void    pop_back()
            {
                _alloc.destroy(_value + _size - 1);
                _size--;
            };
            void    clear()
            {
                for (size_type i = 0 ; i < _size ; i++)
                    pop_back();
            };

            iterator insert (iterator position, const value_type& val)
            {
                difference_type index = position - begin();

                if (index < 0)
                    throw(std::out_of_range("insert : Out of range."));
                reserve(_size + 1);
                for (size_type i = _size + 1; i >= 0 ; i--)
                {
                    if (i == index)
                    {
                        _alloc.construct(_value + i , val);
                        break;
                    }
                    _alloc.construct(_value + i , _value[i - 1]);
                }
                _size++;
                return (iterator(_value + index));
            };
            
            void insert (iterator position, size_type n, const value_type& val);
            
            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last);

            iterator erase (iterator position)
            {
                difference_type index = position - begin();
                if (index < 0)
                    throw(std::out_of_range("erase : Out of range."));
                if (position + 1 == end())
                {
                    pop_back();
                    return end();
                }
                else
                {
                    for (size_type i = 0, j = 0 ; i < _size ; i++)
                    {
                        if (position.base() != _value + i)
                            _alloc.construct(this->_value + j++, this->_value[i]);
                        else
                            _alloc.destroy(this->_value + i);
                    }
                    _size--;
                    return (iterator(_value + index));
                }
            };
            iterator erase (iterator first, iterator last)
            {
                difference_type index = first - begin();
                size_type len = 0;
                if (last - first <= 0 || index < 0)
                    throw std::out_of_range("out_of_range");
                for (size_type i = 0, j = 0 ; i < _size ; i++)
                {
                    if (first.base() == _value + i)
                    {
                        for ( ; first != last ; first++)
                        {
                            _alloc.destroy(this->_value + i++);
                            len++;
                        }
                    }
                    _alloc.construct(this->_value + j++, this->_value[i]);
                }
                _size -= len;
                return (iterator(_value + index));
            };
            void swap(vector &v) {
                std::swap(this->_data, v._data);
                std::swap(this->_size, v._size);
                std::swap(this->_capacity, v._capacity);
                std::swap(this->_alloc, v._alloc);
            }


                            /* ALLOCATOR */
            allocator_type get_allocator() const { return _alloc; };
    };

}


#endif