//
// Created by ali-masa on 1/27/20.
//

#ifndef FIXEDPOINTPRICE_PRICE_H
#define FIXEDPOINTPRICE_PRICE_H

template <class D, class C>
class Price{
public:
    explicit Price(D dollars = 0, C cents = 0);
    D getDollars() const { return m_dollars; }
    C getCents() const { return m_cents; }

private:
    D m_dollars;
    C m_cents;
};

template <class D, class C>
Price<D,C> whaterver()
{
    return Price<D,C>;
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

#endif //FIXEDPOINTPRICE_PRICE_H
