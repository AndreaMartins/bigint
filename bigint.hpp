#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

class bigint {
private:
    std::string str; // número en formato normal, no invertido

public:
    bigint();
    bigint(unsigned int num);
    bigint(const bigint& source);

    bigint& operator=(const bigint& source);

    std::string getStr() const;

    // ---- arithmetic ----
    bigint operator+(const bigint& other) const;
    bigint& operator+=(const bigint& other);

    // ---- increment ----
    bigint& operator++();   // ++x
    bigint operator++(int); // x++

    // ---- shifts with uint ----
    bigint operator<<(unsigned int n) const;
    bigint operator>>(unsigned int n) const;
    bigint& operator<<=(unsigned int n);
    bigint& operator>>=(unsigned int n);

    // ---- shifts with bigint ----
    bigint operator<<(const bigint& other) const;
    bigint operator>>(const bigint& other) const;
    bigint& operator<<=(const bigint& other);
    bigint& operator>>=(const bigint& other);

    // ---- comparisons ----
    bool operator==(const bigint& other) const;
    bool operator!=(const bigint& other) const;
    bool operator<(const bigint& other) const;
    bool operator>(const bigint& other) const;
    bool operator<=(const bigint& other) const;
    bool operator>=(const bigint& other) const;
};

// stream output
std::ostream& operator<<(std::ostream& os, const bigint& obj);

// helpers
std::string addition(const std::string& a, const std::string& b);

#endif

