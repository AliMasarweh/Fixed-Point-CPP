//
// Created by ali-masa on 1/27/20.
//

#ifndef FIXEDPOINTPRICE_PRICE_H
#define FIXEDPOINTPRICE_PRICE_H

template <class D, class C>
class Price;

template <class D, class C>
Price<D,C>& operator+(const Price<D,C>& p1, const Price<D,C>& p2)
{
    return Price<D,C>(p1.getDollars()+ p2.getDollars(),
            p1.getCents() + p2.getCents());
}

template <class D, class C>
Price<D,C>& operator-(const Price<D,C>& p1, const Price<D,C>& p2)
{
    return Price<D,C>(p1.getDollars()- p2.getDollars(),
                      p1.getCents() - p2.getCents());
}

template <class D, class C>
Price<D,C>& operator*(const Price<D,C>& p1, const Price<D,C>& p2)
{
    D d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    C c_p1 = p1.getCents(), c_p2 = p2.getCents();

    return Price<D,C>(p1.getDollars() * p2.getDollars(),
                      p1.getCents() * p2.getCents());
}

template <class D, class C>
Price<D,C>& operator/(const Price<D,C>& p1, const Price<D,C>& p2)
{
    D d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    C c_p1 = p1.getCents(), c_p2 = p2.getCents();

    return Price<D,C>(p1.getDollars() / p2.getDollars(),
                      p1.getCents() / p2.getCents());
}

template <class D, class C>
Price<D,C>& operator%(const Price<D,C>& p1, const Price<D,C>& p2)
{
    D d_p1 = p1.getDollars(), d_p2 = p2.getDollars();
    C c_p1 = p1.getCents(), c_p2 = p2.getCents();

    return Price<D,C>(p1.getDollars() % p2.getDollars(),
                      p1.getCents() % p2.getCents());
}

template <class D, class C>
bool operator<(const Price<D,C>& p1, const Price<D,C>& p2)
{
    return p1.getDollars() < p2.getDollars() ||
           p1.getDollars() < p2.getDollars();
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


template <class D, class C>
class Price{
public:
    explicit Price(D dollars = 0, C cents = 0);
    D getDollars() const { return m_dollars; }
    C getCents() const { return m_cents; }
    static C max_cents = 100;

    Price<D, C>& operator+=(const Price<D, C>& other);
    Price<D, C>& operator-=(const Price<D, C>& other);
    Price<D, C>& operator*=(const Price<D, C>& other);
    Price<D, C>& operator/=(const Price<D, C>& other);
    Price<D, C>& operator%=(const Price<D, C>& other);

private:
    D m_dollars;
    C m_cents;
};

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

#endif //FIXEDPOINTPRICE_PRICE_H
