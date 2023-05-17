# ft_containers


## Description :
"Do you really understand something if you can't code it ?"

In this project, I implemented a few container types of the C++ standard template
library.

## Main Part :

The namespace is ```ft```. (instead of ```std::vector``` I use ```ft::vector``` and so on...)

#### STL Containers that I re-implemented :
Every container is implemented in ```<container>.hpp```
* Vector
    * without the ```vector<bool>``` specialization
* Stack
    * It uses my ft::vector class as default underlying container.
* Map

#### Other useful classes :
* std::iterator_traits
* std::reverse_iterator
* std::enable_if
* std::is_integral
* std::equal , std::lexicographical_compare
* std::pair
* std::make_pair

## References :

```https://www.cplusplus.com/```


```https://cppreference.com/```

## Tests :
The file ```main_abb.cpp``` contains all the tests. Can be verified as follows :

    make
    ./ft_containers > ft_output

If you want to see the std library outputs , make sure to change the namespace MACRO :

    #define NS ft

to :

    #define NS std

make sure to compile again :

    make 
    ./ft_containers std_output

    diff ft_output std_output
