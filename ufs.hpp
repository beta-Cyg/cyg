#ifndef UFS_HPP
#define UFS_HPP

#include<unordered_map>
#include<algorithm>
#include<vector>

namespace cyg{
    template<typename T,typename sT=std::unordered_map<T,T>>
    class unifind_set{
    private:
        sT father;
        std::unordered_map<T,unsigned long long>size;
    public:
        typedef typename sT::iterator iterator;

        T find(T _val){
            if(father.find(_val)==father.end())return father[_val]=_val;
            if(father[_val]==_val)return _val;
            return father[_val]=find(father[_val]);
        }

        void merge(T _u,T _v){
            _u=find(_u),_v=find(_v);
            if(_u==_v)return;
            if(size[_u]>size[_v])std::swap(_u,_v);
            father[_u]=_v;
            size[_v]+=size[_u];
        }

        bool in(T _u,T _v){
            return find(_u)==find(_v) or _u==_v;
        }

        iterator begin(){
            return father.begin();
        }

        iterator end(){
            return father.end();
        }
    };
}
#endif