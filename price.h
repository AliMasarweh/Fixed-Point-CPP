//
// Created by ali-masa on 1/27/20.
//

#ifndef FIXEDPOINTPRICE_PRICE_H
#define FIXEDPOINTPRICE_PRICE_H

#include <cmath>

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

std::string digitName(int digit);
std::string teenName(int number);
std::string tensName(int number);
std::string intName(int number);

/*std::string digitName(int digit)
{
    unsigned char minimalValue = 1, maximalValue = 9;
    static std::string words[] = {
            "one", "two", "three", "four", "five"
            , "six", "seven", "eight", "nine"
    };
    if(digit > minimalValue || digit < maximalValue)
        return "";
    return words[digit - minimalValue];
}

std::string teenName(int number)
{
    unsigned char minimalValue = 10, maximalValue = 19;
    static std::string words[] = {
            "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen"
            , "sixteen", "seventeen", "eighteen", "nineteen"
    };
    if(number < minimalValue || number > maximalValue)
        return "";

    return words[number - minimalValue];
}

std::string tensName(int number)
{
    if(number % 10 != 0)
        return "";
    number /= 10;
    unsigned char minimalValue = 2, maximalValue = 9;
    static std::string words[] = {
            "twenty", "thirty", "fourty", "fifty"
            , "sixty", "seventy", "eighty", "ninety"
    };
    if(number < minimalValue || number > maximalValue)
        return "";

    return words[number - minimalValue];
}*/

std::string digitName(int digit)
{
    if (digit == 1) return "one";
    if (digit == 2) return "two";
    if (digit == 3) return "three";
    if (digit == 4) return "four";
    if (digit == 5) return "five";
    if (digit == 6) return "six";
    if (digit == 7) return "seven";
    if (digit == 8) return "eight";
    if (digit == 9) return "nine";

    return "";
}

std::string teenName(int number)
{
    if (number == 10) return "ten";
    if (number == 11) return "eleven";
    if (number == 12) return "twelve";
    if (number == 13) return "thirteen";
    if (number == 14) return "fourteen";
    if (number == 15) return "fifteen";
    if (number == 16) return "sixteen";
    if (number == 17) return "seventeen";
    if (number == 18) return "eighteen";
    if (number == 19) return "nineteen";

    return "";
}

std::string tensName(int number)
{
    if (number >= 90) return "ninety";
    if (number >= 80) return "eighty";
    if (number >= 70) return "seventy";
    if (number >= 60) return "sixty";
    if (number >= 50) return "fifty";
    if (number >= 40) return "fourty";
    if (number >= 30) return "thirty";
    if (number >= 20) return "twenty";

    return "";
}

void intNameHelperMillionsAndThousands(int& number,
        std::string& name, int factor, std::string& valName)
{
    bool hasAddedWords = false;
    if (number >= 100 * factor)
    {
        name += digitName(number / (100 * factor)) + " hundrend ";
        number = number % (100 * factor);
        hasAddedWords = true;
    }

    if (number >= 20 * factor)
    {
        if (number % 10 * factor == 0)
        {
            name += tensName(number / factor) + " ";
            number = number % factor;

        }else
        {
            name += tensName(number / factor) + ", ";
            number = number % 10 * factor;
        }
        hasAddedWords = true;
    }

    if (number >= 10 * factor)
    {
        name += teenName(number / factor) + " ";
        number = number % factor;
        hasAddedWords = true;
    }

    if (number >= factor)
    {
        name += digitName(number / factor) + " ";
        number = number % factor;
        hasAddedWords = true;
    }

    if(hasAddedWords == true)
        name +=  valName+" ";
}

std::string intName(int number)
{
    int part = number;
    std::string name;
    const int THOUSAND = pow(10, 3);
    const int MILLION = pow(10, 6);
    std::string millionName = "million", thousandName = "thousand";
    if(number/MILLION > 0)
        intNameHelperMillionsAndThousands(part, name, MILLION, millionName);
    if(number/THOUSAND > 0)
        intNameHelperMillionsAndThousands(part, name, THOUSAND, thousandName);
    if (part >= 100)
    {
        name = name + digitName(part / 100) + " hundred, ";
        part = part % 100;
    }


    if (part >= 20)
    {
        if(name == "")
            name = tensName(part)+ " ";
        else
            name += tensName(part) + " ";
        part = part % 10;

    }else if (part >= 10)
    {
        if(name == "")
            name = teenName(part)+ " ";
        else
            name += teenName(part) + " ";
        part = 0;
    }

    if (part > 0)
    {
        name += digitName(part) + " ";
    }

    return name;
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
    return intName(std::atoi(str.substr(startIndex, endIndex).c_str()));
}

template<unsigned char SIZE, class D, class C>
std::string FixedPoint<SIZE, D, C>::makeMoney() const {
    const static std::string dollarsAndCentsAppender = "dollars and ",
                postfixCents = "cents", zeroMoney = "No money";
    std::string numstr = this->asString();
    std::size_t len = numstr.length();
    std::size_t afterpoint = SIZE;
    std::string dollarstr = digitsToWords(numstr, 0, len-afterpoint-1);
    std::string centstr = digitsToWords(numstr, len - afterpoint - 1, len);

    if(dollarstr == "" && centstr == "")
        return zeroMoney;
    std::stringstream ans;
    if(dollarstr != "")
        ans << dollarstr + dollarsAndCentsAppender;
    if(centstr != "")
        ans << centstr << postfixCents;
    return ans.str();
}

#endif //FIXEDPOINTPRICE_PRICE_H
