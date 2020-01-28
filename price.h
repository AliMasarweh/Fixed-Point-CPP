//
// Created by ali-masa on 1/27/20.
//

#ifndef FIXEDPOINTPRICE_PRICE_H
#define FIXEDPOINTPRICE_PRICE_H

#include <cmath>

template <unsigned char SIZE, class D, class C>
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

    std::cout << c_p1 << " " << c_p2 << std::endl;

    long long dollars = (d_p1 * d_p2);

    long long cents = static_cast<long long>((c_p1 * c_p2)/maxCents + d_p1 * c_p2 + d_p2 * c_p1);
    std::cout << dollars << " " << cents << std::endl;
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
    this->m_cents = static_cast<C>(cent * pow(10, (SIZE - floor(log10(cent) + 1))))%m_maxCents;
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

#endif //FIXEDPOINTPRICE_PRICE_H
