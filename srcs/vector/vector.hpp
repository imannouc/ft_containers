#ifndef VECTOR_H
# define VECTOR_H

#include <unistd.h>
#include "../iterators/iterator.hpp"
#include <memory>
#include <iostream>
#include "../headers/enable_if.hpp"
#include "../headers/is_integral.hpp"
#include "../headers/equal.hpp"

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
            typedef ft::reverse_iterator<iterator> reverse_iterator; //	reverse_iterator<iterator>	
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator; //	reverse_iterator<const_iterator>	
            typedef ptrdiff_t difference_type; //a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t

        private:
            pointer _value;// pointer type instead.
            size_type _size;
            size_type _capacity;
            allocator_type _alloc;

        public:
            //default constructor
            explicit vector(const allocator_type& alloc = allocator_type())// : _value(0), _size(0),_capacity(0),_alloc(alloc) {std::cout << " DEFAULT constructor CALLED " << std::endl;};
            {
                // std::cout << " DEFAULT constructor CALLED " << std::endl;
                _value = NULL;
                _size = 0;
                _capacity = 0;
                this->_alloc = alloc;
            };
            //fill constructor¸¸¸
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            {
                // std::cout << " FILL constructor CALLED " << std::endl;
                this->_value = NULL;
                this->_alloc = alloc;
                try
                {
                    // std::cout << "NAX SIIZE :" << max_size();
                    if (n <= this->max_size())
                        this->_value = _alloc.allocate(n);
                    // std::cout << "allocated " << n << " elements \n";
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    return;
                }
                for (size_type i = 0; i < n ; i++){
                    _alloc.construct(&_value[i],val);
                }
                this->_size = n;
                this->_capacity = n;
            };
            // range constructor
            template <class InputIterator>
            vector (InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type() , typename enable_if<!is_integral<InputIterator>::value,InputIterator>::type* = NULL)
            {
                // std::cout << " RANGE constructor CALLED " << std::endl;
                difference_type diff = last - first;
                this->_alloc = alloc;
                try
                {
                    this->_value = _alloc.allocate(diff);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                for (size_type i = 0 ;last != first ; first++,i++)
                    _alloc.construct(_value + i ,*first);
                this->_size = diff;
                this->_capacity = diff;
            };
            //copy constructor
            vector(const vector& x) : _value(0), _size(0),_capacity(0)
            {
                // std::cout << " COPY constructor CALLED " << std::endl;
                *this = x;
            }
            vector& operator= (vector const & x)
            {
                // std::cout << " operator = CALLED " << std::endl;
                if (this == &x)
                    return *this;
                // if vector we wish to copy to is full , empty it first, then copy.
                if (this->_size)
                {
                    for (size_type i = 0; i < this->_capacity ; i++)
                        _alloc.destroy(_value + i);
                    if (_value)
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
                for (size_type i = 0; i < this->_size ; i++)
                    _alloc.construct(_value + i,*(x._value + i));
                return *this;
            }
            ~vector()
            {
                if (_size > 0)
                    for (size_type i = 0; i < _size; i++)
                        _alloc.destroy(_value + i);
                if (_capacity > 0 && _value){
                    // usleep(5000);
                    _alloc.deallocate(_value, _capacity);
                }
            };

                            /* ITERATORS */
            iterator begin() { return (iterator(_value)); };
            const_iterator begin() const { return (const_iterator(_value)); };
            iterator end() { return (iterator(_value + _size)); };
            const_iterator end() const { return (const_iterator(_value + _size)); };
            reverse_iterator rbegin() { return reverse_iterator(iterator(_value + _size - 1)); };
            const_reverse_iterator rbegin() const { return const_reverse_iterator(iterator(_value + _size - 1)); };
            reverse_iterator rend() { return reverse_iterator(iterator(_value - 1));};
            const_reverse_iterator rend() const { return reverse_iterator(iterator(_value - 1)); };
            
                            /* CAPACITY */
            size_type size() const { return _size; };
            size_type max_size() const { return this->_alloc.max_size(); };
            void resize (size_type n, value_type val = value_type())
            {
                if (n < _size)
                {
                    for (size_type i = n ; i < _size ; i++)
                        _alloc.destroy(_value + i);
                    _size = n;
                }
                else if (n > _size)
                {
                    reserve(n);
                    for (size_type i = _size ; i < n ; i++)
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
                    for (size_type i = 0; i < this->_size; i++)
                        _alloc.construct(newValue + i, this->_value[i]);
                    for (size_type i = 0; i < this->_size ; i++)
                        _alloc.destroy(_value + i);
                    if (_size != 0 || _capacity != 0 || _value != NULL) {
                        _alloc.deallocate(this->_value,_capacity);
                    }
                    this->_value = newValue;
                    this->_capacity = n;
                }
            };


                            /* ELEMENT ACCESS */
            reference operator[] (size_type n) { return (_value[n]); };
            reference at (size_type n)
            {
                if ( n >= _size)
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
            // &_value[0];

                            /* MODIFIERS */
            template <class InputIterator>
            void assign (InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value,InputIterator>::type* = NULL)
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
                while (!empty())
                    pop_back();
            };

            iterator insert (iterator position, const value_type& val)
            {
                size_type index = position - begin();

                if (index < 0)
                    throw(std::out_of_range("insert : Out of range."));
                reserve(_size + 1);
                for (size_type i = _size + 1; i  >= 0 ; i--)
                {
                    if (i == index)
                    {
                        _alloc.construct(_value + i , val);
                        break;
                    }
                    // std::cout << i << '|' << std::endl;
                    _alloc.construct(_value + i , _value[i - 1]);
                }
                _size++;
                return (iterator(_value + index));
            };
            
            void insert (iterator position, size_type n, const value_type& val)
            {
                difference_type index = position - begin();

                if (index < 0)
                    throw(std::out_of_range("insert : Out of range."));
                reserve(_size + n);
                for (size_t i = _size + n ; i >= 0; i--)
                {
                    if (i == index + n - 1)
                    {
                        for (size_t j = index; j <= index + n - 1; j++)
                            _alloc.construct(_value + j , val);
                        break;
                    }
                    _alloc.construct(_value + i , _value[i - n]);
                }
                _size += n;
            };
            
            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value,InputIterator>::type* = NULL)
            {
                size_type index = position - begin();
                size_type n = last - first;

                if (index < 0 || index > _size)
                    throw(std::out_of_range("insert : Out of range."));
                reserve(_size + n);
                for (size_t i = _size + n ; i >= 0; i--)
                {
                    if (i == index + n - 1)
                    {
                        for (size_t j = index; first != last && j <= index + n - 1; j++, first++)
                            _alloc.construct(_value + j , *first);
                        break;
                    }
                    _alloc.construct(_value + i , _value[i - n]);
                }
                _size += n;
            };

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
                std::swap(this->_value, v._value);
                std::swap(this->_size, v._size);
                std::swap(this->_capacity, v._capacity);
                std::swap(this->_alloc, v._alloc);
            }


                            /* ALLOCATOR */
            allocator_type get_allocator() const { return _alloc; };

        template <class Type, class Alc>
        friend bool operator== (const vector<Type,Alc>& lhs, const vector<Type,Alc>& rhs);
        template <class Type, class Alc>
        friend bool operator!= (const vector<Type,Alc>& lhs, const vector<Type,Alc>& rhs);
        template <class Type, class Alc>
        friend bool operator<  (const vector<Type,Alc>& lhs, const vector<Type,Alc>& rhs);
        template <class Type, class Alc>
        friend bool operator<= (const vector<Type,Alc>& lhs, const vector<Type,Alc>& rhs);
        template <class Type, class Alc>
        friend bool operator>  (const vector<Type,Alc>& lhs, const vector<Type,Alc>& rhs);
        template <class Type, class Alc>
        friend bool operator>= (const vector<Type,Alc>& lhs, const vector<Type,Alc>& rhs);
    };


    template <class T, class Alloc> 
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
    {
        x.swap(y);
    };
// std::relational operators (vector)
    template <class T, class Alloc>  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return ((lhs.size() == rhs.size()) && equal(lhs.begin(),lhs.end(),rhs.begin()));
    };
    template <class T, class Alloc>  bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (!(lhs == rhs));
    };
    template <class T, class Alloc>  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end()));
    };
    template <class T, class Alloc>  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (!(rhs < lhs));
    };
    template <class T, class Alloc>  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (rhs < lhs);
    };
    template <class T, class Alloc>  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (!(lhs < rhs));
    };
}


#endif