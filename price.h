//
// Created by ali-masa on 1/27/20.
//

#ifndef FIXEDPOINTPRICE_PRICE_H
#define FIXEDPOINTPRICE_PRICE_H

#include <cmath>


namespace numbersSpeller
{
    const char* smallNumbers[] = {
            "zero", "one", "two", "three", "four", "five",
            "six", "seven", "eight", "nine", "ten",
            "eleven", "twelve", "thirteen", "fourteen", "fifteen",
            "sixteen", "seventeen", "eighteen", "nineteen"
    };

    std::string spellHundreds(unsigned n) {
        std::string res;
        if (n > 99) {
            res = smallNumbers[n/100];
            res += " hundred";
            n %= 100;
            if (n) res += " and ";
        }
        if (n >= 20) {
            static const char* Decades[] = {
                    "", "", "twenty", "thirty", "forty",
                    "fifty", "sixty", "seventy", "eighty", "ninety"
            };
            res += Decades[n/10];
            n %= 10;
            if (n) res += "-";
        }
        if (n < 20 && n > 0)
            res += smallNumbers[n];
        return res;
    }


    const char* thousandPowers[] = {
            " billion", " million",  " thousand", "" };

    typedef unsigned long Spellable;

    std::string spell(Spellable n) {
        if (n < 20) return smallNumbers[n];
        std::string res;
        const char** pScaleName = thousandPowers;
        Spellable scaleFactor = 1000000000;	// 1 billion
        while (scaleFactor > 0) {
            if (n >= scaleFactor) {
                Spellable h = n / scaleFactor;
                res += spellHundreds(h) + *pScaleName;
                n %= scaleFactor;
                if (n) res += ", ";
            }
            scaleFactor /= 1000;
            ++pScaleName;
        }
        return res;
    }
}

template <unsigned char SIZE, class D = int, class C = int>
class FixedPoint{
    friend std::ostream &operator<<(std::ostream &os, const FixedPoint<SIZE, D, C> &p) {
        C tmpToPadZeros = p.m_cents != 0? p.m_cents : 1;

        os << p.m_dollars << '.';

        while(tmpToPadZeros < SIZE) {
            os << "0";
            tmpToPadZeros *= 10;
        }

        os << (D) p.m_cents << '$';
        return os;
    }

public:
    explicit FixedPoint(D dollars = 0, C cents = 0);
    D getDollars() const { return m_dollars; }
    C getCents() const { return m_cents; }

    FixedPoint<SIZE, D, C>& operator=(int);

    FixedPoint<SIZE, D, C>& operator+=(const FixedPoint<SIZE, D, C>& other);
    FixedPoint<SIZE, D, C>& operator-=(const FixedPoint<SIZE, D, C>& other);
    FixedPoint<SIZE, D, C>& operator*=(const FixedPoint<SIZE, D, C>& other);
    FixedPoint<SIZE, D, C>& operator/=(const FixedPoint<SIZE, D, C>& other);
    FixedPoint<SIZE, D, C>& operator%=(const FixedPoint<SIZE, D, C>& other);

    FixedPoint<SIZE, D, C>& operator-();
    FixedPoint<SIZE, D, C>& operator++();
    const FixedPoint<SIZE, D, C>  operator++(int);
    FixedPoint<SIZE, D, C>& operator--();
    const FixedPoint<SIZE, D, C>  operator--(int);

    explicit operator double() const;

    std::string asString() const;
    std::string digitsToWords(const std::string str,
                              std::size_t startIndex, std::size_t endIndex) const;
    std::string makeMoney() const;


    D m_maxCents;

private:
    D m_dollars;
    C m_cents;
};


template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C> operator+(const FixedPoint<SIZE, D, C>& p1, const FixedPoint<SIZE, D, C>& p2)
{
    return FixedPoint<SIZE, D, C>(p1.getDollars()+ p2.getDollars(),
                      p1.getCents() + p2.getCents());
}

template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C> operator-(const FixedPoint<SIZE, D, C>& p1, const FixedPoint<SIZE, D, C>& p2)
{
    return FixedPoint<SIZE, D, C>(p1.getDollars()- p2.getDollars(),
                      p1.getCents() - p2.getCents());
}

template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C> operator*(const FixedPoint<SIZE, D, C>& p1, const FixedPoint<SIZE, D, C>& p2)
{
    C maxCents = p1.m_maxCents;
    long long d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    long long c_p1 = p1.getCents(), c_p2 = p2.getCents();

    long long dollars = (d_p1 * d_p2);

    long long cents = static_cast<long long>((c_p1 * c_p2)/maxCents + d_p1 * c_p2 + d_p2 * c_p1);
    return FixedPoint<SIZE, D, C>((D)dollars, (C)cents);
}

template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C> operator/(const FixedPoint<SIZE, D, C>& p1, const FixedPoint<SIZE, D, C>& p2)
{
    long long d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    C c_p1 = p1.getCents(), c_p2 = p2.getCents();

    /*long long total = (((d_p1 * p1.m_maxCents+c_p1) * p1.m_maxCents)
            / (d_p2 *p2.m_maxCents+c_p2));
    return FixedPoint<SIZE, D, C>(total / p1.m_maxCents,
                             long(total) % p1.m_maxCents);*/

    long double total_p1 = d_p1 + static_cast<long double>(c_p1) / pow(p1.m_maxCents, 2);
    long double total_p2 = d_p2 + static_cast<long double>(c_p2) / pow(p2.m_maxCents, 2);
    long double total = total_p1 / total_p2;
    return FixedPoint<SIZE, D, C>(floor(total),
                             static_cast<long>(total*p1.m_maxCents)%p1.m_maxCents);
}

template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C> operator%(const FixedPoint<SIZE, D, C>& p1, const FixedPoint<SIZE, D, C>& p2)
{
    D d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    C c_p1 = p1.getCents(), c_p2 = p2.getCents();

    long long total = (d_p1 * p1.m_maxCents+c_p1)
                      % (d_p2 *p2.m_maxCents+c_p2);
    return FixedPoint<SIZE, D, C>(total / p1.m_maxCents,
                      total % p1.m_maxCents);
}

template <unsigned char SIZE, class D, class C>
bool operator<(const FixedPoint<SIZE, D, C>& p1, const FixedPoint<SIZE, D, C>& p2)
{
    if (p1.getDollars() < p2.getDollars())
        return true;
    if (p1.getDollars() == p2.getDollars() &&
        p1.getCents() < p2.getCents())
        return true;
    return false;
}

template <unsigned char SIZE, class D, class C>
bool operator>(const FixedPoint<SIZE, D, C>& p1, const FixedPoint<SIZE, D, C>& p2)
{
    return p2 < p1;
}

template <unsigned char SIZE, class D, class C>
bool operator!=(const FixedPoint<SIZE, D, C>& p1, const FixedPoint<SIZE, D, C>& p2)
{
    return p1 < p2 || p2 < p1;
}

template <unsigned char SIZE, class D, class C>
bool operator==(const FixedPoint<SIZE, D, C>& p1, const FixedPoint<SIZE, D, C>& p2)
{
    return !(p1 != p2);
}

template <unsigned char SIZE, class D, class C>
bool operator<=(const FixedPoint<SIZE, D, C>& p1, const FixedPoint<SIZE, D, C>& p2)
{
    return !(p1 > p2);
}

template <unsigned char SIZE, class D, class C>
bool operator>=(const FixedPoint<SIZE, D, C>& p1, const FixedPoint<SIZE, D, C>& p2)
{
    return !(p1 < p2);
}


template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C>::FixedPoint(D dollars, C cent)
{
    this->m_maxCents = pow(10, SIZE);
    this->m_dollars = (dollars + cent/m_maxCents);
    this->m_cents = static_cast<C>(cent * pow(10, (SIZE - floor(log10(cent?cent:1) + 1))))%m_maxCents;
}

template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C>& FixedPoint<SIZE, D, C>::operator+=(const FixedPoint<SIZE, D, C>& other){
    *this = *this + other;
    return *this;
}

template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C>& FixedPoint<SIZE, D, C>::operator-=(const FixedPoint<SIZE, D, C>& other){
    *this = *this - other;
    return *this;
}

template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C>& FixedPoint<SIZE, D, C>::operator*=(const FixedPoint<SIZE, D, C>& other){
    *this = *this * other;
    return *this;
}

template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C>& FixedPoint<SIZE, D, C>::operator/=(const FixedPoint<SIZE, D, C>& other){
    *this = *this / other;
    return *this;
}

template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C>& FixedPoint<SIZE, D, C>::operator%=(const FixedPoint<SIZE, D, C>& other){
    *this = *this % other;
    return *this;
}

template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C> &FixedPoint<SIZE, D, C>::operator-() {
    return *FixedPoint<SIZE, D, C>(this->m_dollars*-1, this->m_cents*-1,
            this->m_maxCents);
}

template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C> &FixedPoint<SIZE, D, C>::operator++() {
    ++this->m_dollars;
    return *this;
}

template <unsigned char SIZE, class D, class C>
const FixedPoint<SIZE, D, C> FixedPoint<SIZE, D, C>::operator++(int) {
    FixedPoint<SIZE, D, C> tmp = *this;
    ++this->m_dollars;
    return tmp;
}


template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C> &FixedPoint<SIZE, D, C>::operator--() {
    --this->m_dollars;
    return *this;
}

template <unsigned char SIZE, class D, class C>
const FixedPoint<SIZE, D, C> FixedPoint<SIZE, D, C>::operator--(int) {
    FixedPoint<SIZE, D, C> tmp = *this;
    --this->m_dollars;
    return tmp;
}

template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C>::operator double() const {
    return m_dollars + static_cast<double>(m_cents)/m_maxCents;
}

template <unsigned char SIZE, class D, class C>
FixedPoint<SIZE, D, C> &FixedPoint<SIZE, D, C>::operator=(int dollars) {
    this->m_dollars = dollars;
    this->m_cents = 0;
    return *this;
}

template<unsigned char SIZE, class D, class C>
std::string FixedPoint<SIZE, D, C>::asString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

template<unsigned char SIZE, class D, class C>
std::string FixedPoint<SIZE, D, C>::digitsToWords(const std::string str, std::size_t startIndex, std::size_t endIndex) const {
    std::stringstream ss;
    D toNumber;
    ss >> toNumber;
    return numbersSpeller::spell(std::atoi(str.substr(startIndex, endIndex).c_str()));
}

template<unsigned char SIZE, class D, class C>
std::string FixedPoint<SIZE, D, C>::makeMoney() const {
    const static std::string dollarsAndCentsAppender = " dollars and ",
                postfixCents = " cents", zeroMoney = "No money";
    std::string numstr = this->asString();
    std::size_t len = numstr.length();
    std::size_t afterpoint = SIZE;
    std::string dollarstr = digitsToWords(numstr, 0, len-afterpoint-1);
    std::string centstr = digitsToWords(numstr, len - afterpoint - 1, len);

    if(dollarstr == "zero" && centstr == "zero")
        return zeroMoney;
    std::stringstream ans;
    if(dollarstr != "zero")
        ans << dollarstr + dollarsAndCentsAppender;
    if(centstr != "zero")
        ans << centstr << postfixCents;
    return ans.str();
}

#endif //FIXEDPOINTPRICE_PRICE_H
