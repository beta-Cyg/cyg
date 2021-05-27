#ifndef BIGN_HPP
#define BIGN_HPP

#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<algorithm>

namespace cyg{
    class bign{
    private:
        long long len;
        std::string d;

        void clean(){while(len>1 and not d[len-1])len--;}
    public:
        bign():len(1){d.resize(1);}

        bign(const int num):len(){*this=num;}

        bign(const std::string num):len(){*this=num;}

        bign& operator=(const std::string num){
            d.clear();
            d.resize(len=num.length());
            for(int i=0;i<len;i++)d[i]=num[len-1-i]-'0';
            clean();
            return *this;
        }

        bign& operator=(const long long num){
            char s[20];
            std::sprintf(s,"%lld",num);
            *this=s;
            return *this;
        }

        bign operator+(const bign b){
            bign c=*this;
            c.d.resize(c.len=std::max(len,b.len)+1);
            long long i;
            for(i=0;i<b.len;i++){
                c.d[i]+=b.d[i];
                if(c.d[i]>9)c.d[i]%=10,c.d[i+1]++;
            }
            while(c.d[i]>9)c.d[i++]%=10,c.d[i]++;
            if(c.d[i] and c.len<=i)c.len=i+1;
            c.clean();
            return c;
        }

        bign operator-(const bign b){
            bign c=*this;
            c.d.resize(c.len=std::max(len,b.len)+1);
            long long i;
            for(i=0;i<b.len;i++){
                c.d[i]-=b.d[i];
                if(c.d[i]<0)c.d[i]+=10,c.d[i+1]--;
            }
            while(c.d[i]<0)c.d[i++]+=10,c.d[i]--;
            c.clean();
            return c;
        }

        bign operator*(const bign b)const{
            long long i,j;
            bign c;
            c.d.resize(c.len=len+b.len);
            for(j=0;j<b.len;j++)
                for(i=0;i<len;i++)c.d[i+j]+=d[i]*b.d[j];
            for(i=0;i<c.len-1;i++)
                c.d[i+1]+=c.d[i]/10,c.d[i]%=10;
            c.clean();
            return c;
        }

        bign operator/(const bign b){
            long long i,j;
            bign c=*this;
            bign a=0;
            for(i=len-1;i>=0;i--){
                a=a*bign(10)+bign(d[i]);
                for(j=0;j<10;j++)if(a<b*bign(j+1))break;
                c.d[i]=j;
                a=a-b*bign(j);
            }
            c.clean();
            return c;
        }

        bign operator%(const bign b){
            long long i,j;
            bign a(0);
            for(i=len-1;i>=0;i--){
                a=a*10+d[i];
                for(j=0;j<10;j++)if(a<b*(j+1))break;
                a=a-b*j;
            }
            return a;
        }

        bign operator+=(const bign b){
            *this=*this+b;
            return *this;
        }

        bign operator-=(const bign b){
            *this=*this-b;
            return *this;
        }

        bign operator*=(const bign b){
            *this=*this*b;
            return *this;
        }

        bign operator/=(const bign b){
            *this=*this/b;
            return *this;
        }

        bign operator%=(const bign b){
            *this=*this%b;
            return *this;
        }

        bool operator<(const bign b)const{
            if (len!=b.len)return len<b.len;
            for(long long i=std::min(len,b.len)-1;i>=0;i--)if(d[i]!=b.d[i])return d[i]<b.d[i];
            return false;
        }

        bool operator>(const bign b)const{return b<*this;}

        bool operator<=(const bign b)const{return not(b>*this);}

        bool operator>=(const bign b)const{return not(*this<b);}

        bool operator!=(const bign b)const{return b<*this or *this<b;}

        bool operator==(const bign b)const{return b>=*this and b<=*this;}

        std::string str()const{
            std::string s(len,'\0');
            for(int i=0;i<len;i++)s[len-1-i]=d[i]+'0';
            return s;
        }
    };
}

std::istream& operator>>(std::istream& in,cyg::bign& x){
    std::string s;
    in>>s;
    x=s;
    return in;
}

std::ostream& operator<<(std::ostream& out,const cyg::bign& x){
    out<<x.str();
    return out;
}

#endif
