#ifndef BIGN_HPP
#define BIGN_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <algorithm>

namespace cyg {

    template<int maxn = 1000>
    class bign {
    private:
        int d[maxn], len;

        void clean() { while (len > 1 && !d[len - 1]) len--; }

    public:
        bign() {
            std::memset(d, 0, sizeof(d));
            len = 1;
        }

        bign(const int num) { *this = num; }

        bign(const char *num) { *this = num; }

        bign<maxn>& operator=(const char *num) {
            std::memset(d, 0, sizeof(d));
            len = int(std::strlen(num));
            for (int i = 0; i < len; i++) d[i] = num[len - 1 - i] - '0';
            clean();
            return *this;
        }

        bign<maxn>& operator=(const std::string num) {
            std::memset(d, 0, sizeof(d));
            len = int(num.length());
            for (int i = 0; i < len; i++) d[i] = num[len - 1 - i] - '0';
            clean();
            return *this;
        }

        bign<maxn>& operator=(const int num) {
            char s[20];
            std::sprintf(s, "%d", num);
            *this = s;
            return *this;
        }

        bign<maxn> operator+(const bign<maxn> b) {
            bign<maxn> c = *this;
            int i;
            for (i = 0; i < b.len; i++) {
                c.d[i] += b.d[i];
                if (c.d[i] > 9) c.d[i] %= 10, c.d[i + 1]++;
            }
            while (c.d[i] > 9) c.d[i++] %= 10, c.d[i]++;
            c.len = std::max(len, b.len);
            if (c.d[i] && c.len <= i) c.len = i + 1;
            return c;
        }

        bign<maxn> operator-(const bign<maxn> b) {
            bign<maxn> c = *this;
            int i;
            for (i = 0; i < b.len; i++) {
                c.d[i] -= b.d[i];
                if (c.d[i] < 0) c.d[i] += 10, c.d[i + 1]--;
            }
            while (c.d[i] < 0) c.d[i++] += 10, c.d[i]--;
            c.clean();
            return c;
        }

        bign<maxn> operator*(const bign<maxn> b) const {
            int i, j;
            bign<maxn> c;
            c.len = len + b.len;
            for (j = 0; j < b.len; j++)
                for (i = 0; i < len; i++)
                    c.d[i + j] += d[i] * b.d[j];
            for (i = 0; i < c.len - 1; i++)
                c.d[i + 1] += c.d[i] / 10, c.d[i] %= 10;
            c.clean();
            return c;
        }

        bign<maxn> operator/(const bign<maxn> b) {
            int i, j;
            bign <maxn>c = *this, a = 0;
            for (i = len - 1; i >= 0; i--) {
                a = a * 10 + d[i];
                for (j = 0; j < 10; j++) if (a < b * (j + 1)) break;
                c.d[i] = j;
                a = a - b * j;
            }
            c.clean();
            return c;
        }

        bign<maxn> operator%(const bign<maxn> b) {
            int i, j;
            bign<maxn> a = 0;
            for (i = len - 1; i >= 0; i--) {
                a = a * 10 + d[i];
                for (j = 0; j < 10; j++) if (a < b * (j + 1)) break;
                a = a - b * j;
            }
            return a;
        }

        bign<maxn> operator+=(const bign<maxn> b) {
            *this = *this + b;
            return *this;
        }

        bool operator<(const bign<maxn> b) const {
            if (len != b.len) return len < b.len;
            for (int i = len - 1; i >= 0; i--)
                if (d[i] != b.d[i]) return d[i] < b.d[i];
            return false;
        }

        bool operator>(const bign<maxn> b) const { return b < *this; }

        bool operator<=(const bign<maxn> b) const { return not(b > *this); }

        bool operator>=(const bign<maxn> b) const { return not(*this < b); }

        bool operator!=(const bign<maxn> b) const { return b < *this || *this < b; }

        bool operator==(const bign<maxn> b) const { return b >= *this && b <= *this; }

        std::string str() const {
            char s[maxn] = {};
            for (int i = 0; i < len; i++) s[len - 1 - i] = d[i] + '0';
            return s;
        }
    };

}

template<int maxn>
std::istream& operator >> (std::istream& in, cyg::bign<maxn>& x){
    std::string s;
    in >> s;
    x = s.c_str();
    return in;
}

template<int maxn>
std::ostream& operator << (std::ostream& out, const cyg::bign<maxn>& x){
    out << x.str();
    return out;
}

#endif