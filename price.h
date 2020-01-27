//
// Created by ali-masa on 1/27/20.
//

#ifndef FIXEDPOINTPRICE_PRICE_H
#define FIXEDPOINTPRICE_PRICE_H
template <class D, class C>
class Price{
public:
    explicit Price(D dollars = 0, C cents = 0);
private:
    D m_dollars;
    C m_cents;
};

#endif //FIXEDPOINTPRICE_PRICE_H
