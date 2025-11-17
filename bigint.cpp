#include "bigint.hpp"

// =============================
// Constructors
// =============================
bigint::bigint() : str("0") {}

bigint::bigint(unsigned int num) {
    std::stringstream ss;
    ss << num;
    str = ss.str();
}

bigint::bigint(const bigint& source) {
    *this = source;
}

bigint& bigint::operator=(const bigint& source) {
    if (this != &source)
        str = source.str;
    return *this;
}

std::string bigint::getStr() const {
    return str;
}

// =============================
// Addition helper (safe & clean)
// =============================
std::string addition(const std::string& a, const std::string& b)
{
    std::string A = a;
    std::string B = b;

    // reverse for easy addition
    std::reverse(A.begin(), A.end());
    std::reverse(B.begin(), B.end());

    // pad to same length
    if (A.size() < B.size())
        A.append(B.size() - A.size(), '0');
    else if (B.size() < A.size())
        B.append(A.size() - B.size(), '0');

    std::string result;
    result.reserve(A.size() + 1);

    int carry = 0;

    for (size_t i = 0; i < A.size(); ++i) {
        int digit1 = A[i] - '0';
        int digit2 = B[i] - '0';

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;

        char out = static_cast<char>('0' + (sum % 10));
        result.push_back(out);
    }

    if (carry != 0)
        result.push_back(static_cast<char>('0' + carry));

    std::reverse(result.begin(), result.end());
    return result;
}

// =============================
// Addition operators
// =============================
bigint bigint::operator+(const bigint& other) const {
    bigint tmp;
    tmp.str = addition(this->str, other.str);
    return tmp;
}

bigint& bigint::operator+=(const bigint& other) {
    this->str = addition(this->str, other.str);
    return *this;
}

// =============================
// Increment operators
// =============================
bigint& bigint::operator++() {
    *this += bigint(1);
    return *this;
}

bigint bigint::operator++(int) {
    bigint tmp = *this;
    *this += bigint(1);
    return tmp;
}

// =============================
// Shifts with uint
// =============================
bigint bigint::operator<<(unsigned int n) const {
    bigint tmp = *this;
    if (!(tmp.str == "0"))
        tmp.str.append(n, '0');
    return tmp;
}

bigint bigint::operator>>(unsigned int n) const {
    bigint tmp = *this;

    if (n >= tmp.str.size()) {
        tmp.str = "0";
        return tmp;
    }

    tmp.str.erase(tmp.str.end() - n, tmp.str.end());
    return tmp;
}

bigint& bigint::operator<<=(unsigned int n) {
    *this = *this << n;
    return *this;
}

bigint& bigint::operator>>=(unsigned int n) {
    *this = *this >> n;
    return *this;
}

// =============================
// Shifts with BigInt
// =============================
static unsigned int toUInt(const std::string& s) {
    unsigned long val = std::stoul(s);
    return static_cast<unsigned int>(val);
}

bigint bigint::operator<<(const bigint& other) const {
    return *this << toUInt(other.getStr());
}

bigint bigint::operator>>(const bigint& other) const {
    return *this >> toUInt(other.getStr());
}

bigint& bigint::operator<<=(const bigint& other) {
    *this = *this << other;
    return *this;
}

bigint& bigint::operator>>=(const bigint& other) {
    *this = *this >> other;
    return *this;
}

// =============================
// Comparisons
// =============================
bool bigint::operator==(const bigint& other) const {
    return str == other.str;
}

bool bigint::operator!=(const bigint& other) const {
    return !(*this == other);
}

bool bigint::operator<(const bigint& other) const {
    if (str.size() != other.str.size())
        return str.size() < other.str.size();
    return str < other.str;
}

bool bigint::operator>(const bigint& other) const {
    return other < *this;
}

bool bigint::operator<=(const bigint& other) const {
    return !(*this > other);
}

bool bigint::operator>=(const bigint& other) const {
    return !(*this < other);
}

// =============================
// Stream output
// =============================
std::ostream& operator<<(std::ostream& os, const bigint& obj) {
    os << obj.getStr();
    return os;
}

