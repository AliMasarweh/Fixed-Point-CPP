//
// Created by ali-masa on 1/27/20.
//

#ifndef FIXEDPOINTPRICE_PRICE_H
#define FIXEDPOINTPRICE_PRICE_H

#include <cmath>

template <class D, class C, unsigned char SIZE>
class Price{
    friend std::ostream &operator<<(std::ostream &os, const Price<D, C, SIZE> &p) {
        std::string padding = "";
        if(p.m_cents < 10)
            padding = "0";
        os << p.m_dollars << '.' << padding << (int) p.m_cents << '$';
        return os;
    }

public:
    explicit Price(D dollars = 0, C cents = 0);
    D getDollars() const { return m_dollars; }
    C getCents() const { return m_cents; }

    Price<D, C, SIZE>& operator=(int);

    Price<D, C, SIZE>& operator+=(const Price<D, C, SIZE>& other);
    Price<D, C, SIZE>& operator-=(const Price<D, C, SIZE>& other);
    Price<D, C, SIZE>& operator*=(const Price<D, C, SIZE>& other);
    Price<D, C, SIZE>& operator/=(const Price<D, C, SIZE>& other);
    Price<D, C, SIZE>& operator%=(const Price<D, C, SIZE>& other);

    Price<D, C, SIZE>& operator-();
    Price<D, C, SIZE>& operator++();
    const Price<D, C, SIZE>  operator++(int);
    Price<D, C, SIZE>& operator--();
    const Price<D, C, SIZE>  operator--(int);

    explicit operator double() const;

    C m_maxCents;
    
private:
    D m_dollars;
    C m_cents;
};


template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE> operator+(const Price<D, C, SIZE>& p1, const Price<D, C, SIZE>& p2)
{
    return Price<D, C, SIZE>(p1.getDollars()+ p2.getDollars(),
                      p1.getCents() + p2.getCents());
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE> operator-(const Price<D, C, SIZE>& p1, const Price<D, C, SIZE>& p2)
{
    return Price<D, C, SIZE>(p1.getDollars()- p2.getDollars(),
                      p1.getCents() - p2.getCents());
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE> operator*(const Price<D, C, SIZE>& p1, const Price<D, C, SIZE>& p2)
{
    D d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    C c_p1 = p1.getCents(), c_p2 = p2.getCents();

    long long total = ((d_p1 * p1.m_maxCents+c_p1) * (d_p2 *p2.m_maxCents+c_p2))
            / p1.m_maxCents;
    return Price<D, C, SIZE>(total / p1.m_maxCents,
                      total % p1.m_maxCents);
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE> operator/(const Price<D, C, SIZE>& p1, const Price<D, C, SIZE>& p2)
{
    D d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    C c_p1 = p1.getCents(), c_p2 = p2.getCents();

    long long total = ((d_p1 * p1.m_maxCents+c_p1) * p1.m_maxCents)
            / (d_p2 *p2.m_maxCents+c_p2);
    return Price<D, C, SIZE>(total / p1.m_maxCents,
                      total % p1.m_maxCents);
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE> operator%(const Price<D, C, SIZE>& p1, const Price<D, C, SIZE>& p2)
{
    D d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    C c_p1 = p1.getCents(), c_p2 = p2.getCents();

    long long total = (d_p1 * p1.m_maxCents+c_p1)
                      % (d_p2 *p2.m_maxCents+c_p2);
    return Price<D, C, SIZE>(total / p1.m_maxCents,
                      total % p1.m_maxCents);
}

template <class D, class C, unsigned char SIZE>
bool operator<(const Price<D, C, SIZE>& p1, const Price<D, C, SIZE>& p2)
{
    if (p1.getDollars() < p2.getDollars())
        return true;
    if (p1.getDollars() == p2.getDollars() &&
        p1.getCents() < p2.getCents())
        return true;
    return false;
}

template <class D, class C, unsigned char SIZE>
bool operator>(const Price<D, C, SIZE>& p1, const Price<D, C, SIZE>& p2)
{
    return p2 < p1;
}

template <class D, class C, unsigned char SIZE>
bool operator!=(const Price<D, C, SIZE>& p1, const Price<D, C, SIZE>& p2)
{
    return p1 < p2 || p2 < p1;
}

template <class D, class C, unsigned char SIZE>
bool operator==(const Price<D, C, SIZE>& p1, const Price<D, C, SIZE>& p2)
{
    return !(p1 != p2);
}

template <class D, class C, unsigned char SIZE>
bool operator<=(const Price<D, C, SIZE>& p1, const Price<D, C, SIZE>& p2)
{
    return !(p1 > p2);
}

template <class D, class C, unsigned char SIZE>
bool operator>=(const Price<D, C, SIZE>& p1, const Price<D, C, SIZE>& p2)
{
    return !(p1 < p2);
}


template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE>::Price(D dollars, C cent)
{
    this->m_maxCents = pow(10, SIZE);
    this->m_dollars = (dollars + cent/m_maxCents);
    this->m_cents = cent%m_maxCents;
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE>& Price<D, C, SIZE>::operator+=(const Price<D, C, SIZE>& other){
    *this = *this + other;
    return *this;
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE>& Price<D, C, SIZE>::operator-=(const Price<D, C, SIZE>& other){
    *this = *this - other;
    return *this;
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE>& Price<D, C, SIZE>::operator*=(const Price<D, C, SIZE>& other){
    *this = *this * other;
    return *this;
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE>& Price<D, C, SIZE>::operator/=(const Price<D, C, SIZE>& other){
    *this = *this / other;
    return *this;
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE>& Price<D, C, SIZE>::operator%=(const Price<D, C, SIZE>& other){
    *this = *this % other;
    return *this;
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE> &Price<D, C, SIZE>::operator-() {
    return *Price<D, C, SIZE>(this->m_dollars*-1, this->m_cents*-1,
            this->m_maxCents);
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE> &Price<D, C, SIZE>::operator++() {
    ++this->m_dollars;
    return *this;
}

template <class D, class C, unsigned char SIZE>
const Price<D, C, SIZE> Price<D, C, SIZE>::operator++(int) {
    Price<D, C, SIZE> tmp = *this;
    ++this->m_dollars;
    return tmp;
}


template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE> &Price<D, C, SIZE>::operator--() {
    --this->m_dollars;
    return *this;
}

template <class D, class C, unsigned char SIZE>
const Price<D, C, SIZE> Price<D, C, SIZE>::operator--(int) {
    Price<D, C, SIZE> tmp = *this;
    --this->m_dollars;
    return tmp;
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE>::operator double() const {
    return m_dollars + static_cast<double>(m_cents)/m_maxCents;
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE> &Price<D, C, SIZE>::operator=(int dollars) {
    this->m_dollars = dollars;
    this->m_cents = 0;
    return *this;
}

#endif //FIXEDPOINTPRICE_PRICE_H
