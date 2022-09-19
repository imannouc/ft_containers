#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include <iterator>
namespace ft {
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
	class MyIterator : iterator<std::random_access_iterator_tag,T>
	{
	public:
		typedef T												iterator_type;
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
		explicit MyIterator(iterator_type it)
		{
			this->_p = it;
		};

		template <class Iter>
		explicit MyIterator( const MyIterator<Iter> & it)
		{
			this->_p = it.base();
		};

		~MyIterator() {};

		iterator_type base() const
		{
			return _p;
		};

		reference operator*() const
		{
			return *(this->_p);
		};

		MyIterator operator+ (difference_type n) const
		{
			return MyIterator(this->_p + n);
		};
		MyIterator& operator++()
		{
			++_p;
			return (*this);
		};
		MyIterator  operator++(int)
		{
			MyIterator tmp = *this;
			++(*this);
			return tmp;
		};
		MyIterator& operator+= (difference_type n)
		{
			this->_p += n;
			return (*this);
		};
		MyIterator operator- (difference_type n) const
		{
			return MyIterator(this->_p - n);
		};
		MyIterator& operator--()
		{
			--_p;
			return (*this);
		};
		MyIterator  operator--(int)
		{
			MyIterator tmp = *this;
			--(*this);
			return tmp;
		};
		MyIterator& operator-= (difference_type n)
		{
			this->_p -= n;
			return (*this);
		};
		pointer operator->() const
		{
			return (&(operator*()));
		};
		reference operator[] (difference_type n) const
		{
			return (_p[n]);
		};
	};

	/* Non-member function overloads */
	// relational ops , + , -	
	template <class Iterator>
	bool operator== (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}	
	template <class Iterator>
	bool operator!= (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return !(lhs.base() == rhs.base());
	}
	template <class Iterator>
	bool operator<  (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}	
	template <class Iterator>
	bool operator<= (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return !(lhs.base() > rhs.base());
	}	
	template <class Iterator>
	bool operator>  (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}	
	template <class Iterator>
	bool operator>= (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return !(lhs.base() < rhs.base());
	}

	template <class Iterator>
  	MyIterator<Iterator> operator+ (typename MyIterator<Iterator>::difference_type n,
	  	const MyIterator<Iterator>& it)
	{
		return (it.operator+(n));
	};

	template <class Iterator>
	typename MyIterator<Iterator>::difference_type operator- (
		const MyIterator<Iterator>& lhs,
		const MyIterator<Iterator>& rhs)
	{
		return (lhs.base() - rhs.base());
	};

template <class T>
class reverse_iterator : public iterator<typename iterator_traits<T>::iterator_category,
						typename iterator_traits<T>::value_type,
						typename iterator_traits<T>::difference_type,
						typename iterator_traits<T>::pointer,
						typename iterator_traits<T>::reference>
{

	public:
		typedef T												iterator_type;
		typedef typename iterator_traits<T>::iterator_category 	iterator_category;
		typedef typename iterator_traits<T>::value_type 		value_type;
		typedef typename iterator_traits<T>::difference_type 	difference_type;
		typedef	typename iterator_traits<T>::pointer 			pointer;
		typedef	typename iterator_traits<T>::reference 			reference;

	protected:
		iterator_type _p;

	public:
		reverse_iterator() : _p(0) {};
		explicit reverse_iterator (iterator_type it) : _p(it) {};

		template <class Iter>
		reverse_iterator (const reverse_iterator<T>& rev_it): _p(rev_it.base()) {};

		iterator_type base() const
		{
			return (_p);
		};
		
		
		reference operator*() const
		{
			iterator_type tmp = _p;
			return *--tmp;
		};
		reverse_iterator operator+ (difference_type n) const
		{
			return (reverse_iterator(_p - n));
		};
		reverse_iterator& operator++(){
			--_p;
			return *this;
		};
		
		reverse_iterator operator++(int) {
			reverse_iterator tmp = *this;
			--_p;
			return tmp;
		}
		reverse_iterator& operator+= (difference_type n)
		{
			_p -= n;
			return (*this);
		};
		reverse_iterator& operator--()
		{
			++_p;
			return (*this);
		};
		reverse_iterator  operator--(int)
		{
			reverse_iterator tmp = *this;
			++_p;
			return tmp;
		};
		reverse_iterator& operator-= (difference_type n)
		{
			_p += n;
			return (*this);
		};
		pointer operator->() const
		{
			return &(operator*());
		}
		reference operator[](difference_type n) const
        {
			return *(*this + n);
		}

};

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() != rhs.base();
	}
	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() > rhs.base();
	}	
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() >= rhs.base();
	}
	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() < rhs.base();
	}	
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class Iterator>
  	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,
	  	const reverse_iterator<Iterator>& it)
	{
		return (it.operator-(n));
	};

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	};

}


#endif