#ifndef STL_EXPAND_HPP
#define STL_EXPAND_HPP

#include<boost/any.hpp>
#include<iostream>
#include<cstdlib>

namespace cyg{
    template<typename T>
    inline T get_any(const boost::any &Any){
        try{
            return boost::any_cast<T>(Any);
        }
        catch(boost::bad_any_cast& badAnyCast){
            std::cerr<<badAnyCast.what();
            std::exit(-1);
        }
    }
}

#endif