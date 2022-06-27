#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include <iterator>

template <class Category,              // iterator::iterator_category
          class T,                     // iterator::value_type
          class Distance = ptrdiff_t,  // iterator::difference_type
          class Pointer = T*,          // iterator::pointer
          class Reference = T&         // iterator::reference
          >
class iterator
{
	public:
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
};

template<typename Iterator>
class iterator_traits{
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T*>
{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*>
{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag iterator_category;
};
// template <class Iterator> class reverse_iterator;



template <class T>// ft::vector<T>::iterator
class MyIterator : std::iterator<std::random_access_iterator_tag,T>
{
	typedef T												iterator_type;//Iterator's type
	typedef typename iterator_traits<T>::iterator_category	iterator_category;
	typedef typename iterator_traits<T>::value_type 		value_type;
	typedef typename iterator_traits<T>::difference_type	difference_type;
	typedef typename iterator_traits<T>::pointer			pointer;
	typedef typename iterator_traits<T>::reference			reference;

private:
	iterator_type _p;

public:
	
	/* Member functions */
	MyIterator() : _p(0) {};
	MyIterator(iterator_type it)
	{
		this->_p = it.base();
	};

	template <class Iter>
	MyIterator( const MyIterator<Iter> & it)
	{
		*this = it;
	};

	template <class Iter>
	MyIterator& operator= (const MyIterator<Iter>& it)
	{
		this->_p = it.base();
		return *this;
	};

	iterator_type base() const
	{
		return _p;
	};
	~MyIterator();


	reference operator*() const
	{
		return *this->_p;
	};
	MyIterator operator+ (difference_type n) const;
	MyIterator& operator++();
	MyIterator  operator++(int);
	MyIterator& operator+= (difference_type n);
	MyIterator operator- (difference_type n) const;
	MyIterator& operator--();
	MyIterator  operator--(int);
	MyIterator& operator-= (difference_type n);
	pointer operator->() const;
	reference operator[] (difference_type n) const;





};

	/* Non-member function overloads */
	// relational ops , + , -	
	template <class Iterator>
	bool operator== (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return lhs == rhs;
	}	
	template <class Iterator>
	bool operator!= (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return !(lhs == rhs)
	}	
	template <class Iterator>
	bool operator<  (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return (lhs < rhs)
	}	
	template <class Iterator>
	bool operator<= (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return !(lhs > rhs)
	}	
	template <class Iterator>
	bool operator>  (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return (lhs > rhs)
	}	
	template <class Iterator>
	bool operator>= (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return !(lhs < ths)
	}


#endif