#ifndef VECTOR_H
# define VECTOR_H

#include <memory>

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
            typedef typename std::vector<value_type>::iterator iterator; //a random access iterator to value_type	convertible to const_iterator
            typedef typename std::vector<value_type>::const_iterator const_iterator; //	a random access iterator to const value_type	
            typedef typename std::vector<value_type>::reverse_iterator reverse_iterator; //	reverse_iterator<iterator>	
            typedef typename std::vector<value_type>::const_reverse_iterator const_reverse_iterator; //	reverse_iterator<const_iterator>	
            typedef ptrdiff_t difference_type; //a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t

        private:
            value_type *_value;
            size_type _size;
            size_type _capacity;
            size_type _max_size;
            allocator_type _alloc;

        public:
            //default constructor
            explicit vector(const allocator_type& alloc = allocator_type())
            {
                _value = 0;
                _size = 0;
                _capacity = 0;
                _max_size = alloc.max_size();
                this->_alloc = alloc;
            };
            //fill constructor
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            {
                this->_alloc = alloc;
                try
                {
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
                this->_alloc = _alloc;
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
                *this = x;
            }
            vector<T>& operator= (vector<T> const & x)
            {
                if (this != &x)
                {
                    // if vector we wish to copy to is full , empty it first, then copy.
                    if (this->_size)
                    {
                        for (int i = 0; i < this->_capacity ; i++)// destroy && deallocate
                        {
                            _alloc.destroy(&this->_value[i]);
                        }
                        // void deallocate (pointer p, size_type n);
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
                        _alloc.construct(_value + i,x._value + i);
                    }
                }
            }
            ~vector(){};

            /*
            Iterators:
                begin
                    Return iterator to beginning (public member function )
                end
                    Return iterator to end (public member function )
                rbegin
                    Return reverse iterator to reverse beginning (public member function )
                rend
                    Return reverse iterator to reverse end (public member function )
            */

            //               CAPACITY               //
            size_type size() const
            {
                return _size;
            };
            size_type max_size() const
            {
                return _max_size;
            };
            void resize (size_type n, value_type val = value_type())
            {

            };
            size_type capacity() const
            {
                return _capacity;
            };
            bool empty() const
            {
                return (_size == 0);
            };
            void reserve (size_type n)
            {

            };

            //               ALLOCATOR               //
            allocator_type get_allocator() const
            {
                return _alloc;
            };
            reference operator[] (size_type n)
            {
                return (this->_value[n]);
            };
            //[]
    };

}


#endif