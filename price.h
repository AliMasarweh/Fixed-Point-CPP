//
// Created by ali-masa on 1/27/20.
//

#ifndef FIXEDPOINTPRICE_PRICE_H
#define FIXEDPOINTPRICE_PRICE_H

template <class D, class C>
class Price{
    friend std::ostream &operator<<(std::ostream &os, const Price<D, C> &p) {
        std::string padding = "";
        if(p.m_cents < 10)
            padding = "0";
        os << p.m_dollars << '.' << padding << (int) p.m_cents << '$';
        return os;
    }

public:
    explicit Price(D dollars = 0, C cents = 0, C maxCents = 100);
    D getDollars() const { return m_dollars; }
    C getCents() const { return m_cents; }
    C m_maxCents;

    Price<D, C>& operator=(int);

    Price<D, C>& operator+=(const Price<D, C>& other);
    Price<D, C>& operator-=(const Price<D, C>& other);
    Price<D, C>& operator*=(const Price<D, C>& other);
    Price<D, C>& operator/=(const Price<D, C>& other);
    Price<D, C>& operator%=(const Price<D, C>& other);

    Price<D, C>& operator-();
    Price<D, C>& operator++();
    const Price<D, C>  operator++(int);
    Price<D, C>& operator--();
    const Price<D, C>  operator--(int);

    explicit operator double() const;

private:
    D m_dollars;
    C m_cents;
};


template <class D, class C>
Price<D,C> operator+(const Price<D,C>& p1, const Price<D,C>& p2)
{
    return Price<D,C>(p1.getDollars()+ p2.getDollars(),
                      p1.getCents() + p2.getCents());
}

template <class D, class C>
Price<D,C> operator-(const Price<D,C>& p1, const Price<D,C>& p2)
{
    return Price<D,C>(p1.getDollars()- p2.getDollars(),
                      p1.getCents() - p2.getCents());
}

template <class D, class C>
Price<D,C> operator*(const Price<D,C>& p1, const Price<D,C>& p2)
{
    D d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    C c_p1 = p1.getCents(), c_p2 = p2.getCents();

    long long total = ((d_p1 * p1.m_maxCents+c_p1) * (d_p2 *p2.m_maxCents+c_p2))
            / p1.m_maxCents;
    return Price<D,C>(total / p1.m_maxCents,
                      total % p1.m_maxCents);
}

template <class D, class C>
Price<D,C> operator/(const Price<D,C>& p1, const Price<D,C>& p2)
{
    D d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    C c_p1 = p1.getCents(), c_p2 = p2.getCents();

    long long total = ((d_p1 * p1.m_maxCents+c_p1) * p1.m_maxCents)
            / (d_p2 *p2.m_maxCents+c_p2);
    return Price<D,C>(total / p1.m_maxCents,
                      total % p1.m_maxCents);
}

template <class D, class C>
Price<D,C> operator%(const Price<D,C>& p1, const Price<D,C>& p2)
{
    D d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    C c_p1 = p1.getCents(), c_p2 = p2.getCents();

    long long total = (d_p1 * p1.m_maxCents+c_p1)
                      % (d_p2 *p2.m_maxCents+c_p2);
    return Price<D,C>(total / p1.m_maxCents,
                      total % p1.m_maxCents);
}

template <class D, class C>
bool operator<(const Price<D,C>& p1, const Price<D,C>& p2)
{
    if (p1.getDollars() < p2.getDollars())
        return true;
    if (p1.getDollars() == p2.getDollars() &&
        p1.getCents() < p2.getCents())
        return true;
    return false;
}

template <class D, class C>
bool operator>(const Price<D,C>& p1, const Price<D,C>& p2)
{
    return p2 < p1;
}

template <class D, class C>
bool operator!=(const Price<D,C>& p1, const Price<D,C>& p2)
{
    return p1 < p2 || p2 < p1;
}

template <class D, class C>
bool operator==(const Price<D,C>& p1, const Price<D,C>& p2)
{
    return !(p1 != p2);
}

template <class D, class C>
bool operator<=(const Price<D,C>& p1, const Price<D,C>& p2)
{
    return !(p1 > p2);
}

template <class D, class C>
bool operator>=(const Price<D,C>& p1, const Price<D,C>& p2)
{
    return !(p1 < p2);
}


template<class D, class C>
Price<D, C>::Price(D dollars, C cents, C maxCents)
{
    this->m_maxCents = maxCents;
    this->m_dollars = dollars + cents/m_maxCents;
    this->m_cents = cents%m_maxCents;
}

template <class D, class C>
Price<D, C>& Price<D, C>::operator+=(const Price<D, C>& other){
    *this = *this + other;
    return *this;
}

template <class D, class C>
Price<D, C>& Price<D, C>::operator-=(const Price<D, C>& other){
    *this = *this - other;
    return *this;
}

template <class D, class C>
Price<D, C>& Price<D, C>::operator*=(const Price<D, C>& other){
    *this = *this * other;
    return *this;
}

template <class D, class C>
Price<D, C>& Price<D, C>::operator/=(const Price<D, C>& other){
    *this = *this / other;
    return *this;
}

template <class D, class C>
Price<D, C>& Price<D, C>::operator%=(const Price<D, C>& other){
    *this = *this % other;
    return *this;
}

template<class D, class C>
Price<D, C> &Price<D, C>::operator-() {
    return *Price<D, C>(this->m_dollars*-1, this->m_cents*-1,
            this->m_maxCents);
}

template<class D, class C>
Price<D, C> &Price<D, C>::operator++() {
    ++this->m_dollars;
    return *this;
}

template<class D, class C>
const Price<D, C> Price<D, C>::operator++(int) {
    Price<D, C> tmp = *this;
    ++this->m_dollars;
    return tmp;
}


template<class D, class C>
Price<D, C> &Price<D, C>::operator--() {
    --this->m_dollars;
    return *this;
}

template<class D, class C>
const Price<D, C> Price<D, C>::operator--(int) {
    Price<D, C> tmp = *this;
    --this->m_dollars;
    return tmp;
}

template<class D, class C>
Price<D, C>::operator double() const {
    return m_dollars + static_cast<double>(m_cents)/m_maxCents;
}

template<class D, class C>
Price<D, C> &Price<D, C>::operator=(int dollars) {
    this->m_dollars = dollars;
    this->m_cents = 0;
    return *this;
}

#endif //FIXEDPOINTPRICE_PRICE_H
