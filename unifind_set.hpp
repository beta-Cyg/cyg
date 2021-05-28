#ifndef _GLIBCXX_UNIFIND_SET_HPP
#define _GLIBCXX_UNIFIND_SET_HPP 1

#ifndef _GLIBCXX_VECTOR
#include<vector>
#endif
#ifndef _GLIBCXX_SET
#include<set>
#endif
#ifndef _GLIBCXX_UNORDERED_SET
#include<unordered_set>
#endif

namespace cyg{
    template<typename T,typename sT=std::unordered_set<T>,typename ssT=std::vector<sT>>
    class unifind_set{
    private:
        ssT ufs;

        typename sT::iterator uni(sT& s1,sT& s2){
            for(auto iter=s2.begin();iter!=s2.end();iter++)s1.insert(*iter);
            return s1.begin();
        }
    public:
        typedef typename ssT::iterator iterator;

        iterator merge(const T _x,const T _y){
            sT ufs_s;
            auto i_y=find(_y),i_x=find(_x);
            if(_x==_y){
                if(i_x==ufs.end()){
                    ufs_s.insert(_x);
                    ufs.push_back(ufs_s);
                    return ufs.end()-1;
                }
                return i_x;
            }
            if(i_y==i_x and i_y!=ufs.end())return i_y;
            if(i_x!=ufs.end()){
                if(i_y!=ufs.end() and i_y!=i_x){
                    uni(*i_x,*i_y);
                    ufs.erase(i_y);
                }
                else{
                    ufs_s.insert(_y);
                    uni(*i_x,ufs_s);
                }
                return i_x;
            }
            else if(i_y!=ufs.end()){
                if(i_x!=ufs.end() and i_x!=i_y){
                    uni(*i_y,*i_x);
                    ufs.erase(i_x);
                }
                else{
                    ufs_s.insert(_x);
                    uni(*i_y,ufs_s);
                }
                return i_y;
            }
            else{
                ufs_s.insert(_x);
                ufs_s.insert(_y);
                ufs.push_back(ufs_s);
                return ufs.end()-1;
            }
        }

		iterator merge(){
			iterator result;
			for(auto iter=ufs.begin();iter!=ufs.end();iter++)result=merge(*((iter+1)->begin()),*(iter->begin()));
			return result;
		}

        iterator find(const T nn){
            for(auto set=ufs.begin();set!=ufs.end();set++)if(set->find(nn)!=set->end())return set;
            return ufs.end();
        }

        bool in(const T _x,const T _y){
            return (find(_x)!=ufs.end() and find(_x)==find(_y)) or _x==_y;
        }

        bool empty(){
            if(ufs.empty())return true;
            else{
                for(auto iter=ufs.begin();iter!=ufs.end();iter++)if(not iter->empty())return false;
                return true;
            }
        }

        void clear(){
            ufs.clear();
        }

        iterator begin(){
            return ufs.begin();
        }

        iterator end(){
            return ufs.end();
        }
    };
}

#endif
