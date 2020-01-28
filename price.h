//
// Created by ali-masa on 1/27/20.
//

#ifndef FIXEDPOINTPRICE_PRICE_H
#define FIXEDPOINTPRICE_PRICE_H

#include <cmath>

template <class D, class C, unsigned char SIZE>
class Price{
    friend std::ostream &operator<<(std::ostream &os, const Price<D, C, SIZE> &p) {
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

    D m_maxCents;

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
    C maxCents = p1.m_maxCents;
    long long d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    long long c_p1 = p1.getCents(), c_p2 = p2.getCents();

    std::cout << c_p1 << " " << c_p2 << std::endl;

    long long dollars = (d_p1 * d_p2);

    long long cents = static_cast<long long>((c_p1 * c_p2)/maxCents + d_p1 * c_p2 + d_p2 * c_p1);
    std::cout << dollars << " " << cents << std::endl;
    return Price<D, C, SIZE>((D)dollars, (C)cents);
}

template <class D, class C, unsigned char SIZE>
Price<D, C, SIZE> operator/(const Price<D, C, SIZE>& p1, const Price<D, C, SIZE>& p2)
{
    long long d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    C c_p1 = p1.getCents(), c_p2 = p2.getCents();

    /*long long total = (((d_p1 * p1.m_maxCents+c_p1) * p1.m_maxCents)
            / (d_p2 *p2.m_maxCents+c_p2));
    return Price<D, C, SIZE>(total / p1.m_maxCents,
                             long(total) % p1.m_maxCents);*/

    long double total_p1 = d_p1 + static_cast<long double>(c_p1) / pow(p1.m_maxCents, 2);
    long double total_p2 = d_p2 + static_cast<long double>(c_p2) / pow(p2.m_maxCents, 2);
    long double total = total_p1 / total_p2;
    return Price<D, C, SIZE>(floor(total),
                             static_cast<long>(total*p1.m_maxCents)%p1.m_maxCents);
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
    this->m_cents = static_cast<C>(cent * pow(10, (SIZE - floor(log10(cent) + 1))))%m_maxCents;
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
