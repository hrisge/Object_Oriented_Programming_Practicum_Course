#include "BigInt.hpp"
#pragma warning (disable : 4996)

void BigInt::copy(const BigInt& other)
{
    this->number = new char[strlen(other.number) + 1];
    strcpy(this->number, other.number);
    this->isNegative = other.isNegative;
}

void BigInt::free()
{
    delete[] this->number;
}

//nullptr или празен низ считаме за невалидни
bool BigInt::validNumber(const char* num)
{
    if (!num || strlen(num) < 1) return false;
    if (num[0] == '-') num++;
    for (size_t i = 0; i < strlen(num); i++) {
        if (num[i] < '0' || num[i] > '9') return false;
    }
    return true;
}
// премахваме нулите преди първата цифра на числото
void BigInt::trim(char*& str)
{
    size_t len = strlen(str);
    size_t count = 0;
    while (str[count] == '0' && count < len-1) {
        count++;
    }
    char* result = new char[len - count + 1];
    strcpy(result, str+count);
    delete[] str;
    str = result;
}

void BigInt::resize(size_t capacity)
{
    char* newNum = new char[capacity] {0};
    strcpy(newNum, number);
    delete[] number;
    number = newNum;
}

void BigInt::determineCarry(bool& carry, int& carrySign, char& sum) const
{
    if (sum > '9') {
        carry = true;
        carrySign = 1;
        sum -= 10;
    }
    else if (sum < '0') {
        carry = true;
        carrySign = -1;
        sum += 10;
    }
}

BigInt::BigInt() : number(new char[2] {'0',0}), isNegative(false) {}

BigInt::BigInt(const char* str) : number(new char[2] {'0',0}), isNegative(false)
{
    if (str[0] == '-') {
        isNegative = true;
        str++;
    }
    if (validNumber(str)) {
        this->number = new char[strlen(str) + 1];
        strcpy(this->number, str);
        trim(this->number);
        if (strcmp(this->number, "0")==0) isNegative = false;
    }
}

BigInt::BigInt(const BigInt& other)
{
    copy(other);
}

BigInt& BigInt::operator=(const BigInt& other)
{
    if (this == &other) return *this;
    free();
    copy(other);
    return *this;
}

BigInt::~BigInt()
{
    free();
}

BigInt BigInt::abs() const
{
    if (*this >= "0") return *this;
    else return -(*this);
}

BigInt BigInt::operator+(const BigInt& other) const
{
    // свеждаме всички случаи до тези, които са ни удобни:
    // да събираме две положителни числа вместо две отрицателни и 
    // да изваждаме по-малко от по-голямо(по абсолютна стойност)
    if (isNegative < other.isNegative && *this < -other || isNegative && other.isNegative) {
        return -(-(*this) + (-other));
    }

    size_t biggerLength;
    size_t smallerLength;
    int biggerSign;
    int smallerSign;
    const char* biggerNum;
    const char* smallerNum;

    if (strlen(number) >= strlen(other.number)) {
        biggerLength = strlen(number);
        smallerLength = strlen(other.number);
        biggerSign = isNegative ? -1 : 1;
        smallerSign = other.isNegative ? -1 : 1;
        biggerNum = number;
        smallerNum = other.number;
    }
    else {
        biggerLength = strlen(other.number);
        smallerLength = strlen(number);
        biggerSign = other.isNegative ? -1 : 1;
        smallerSign = isNegative ? -1 : 1;
        biggerNum = other.number;
        smallerNum = number;
    }
    
    BigInt result;
    // заделяме още едно място, защото при събиране дължината на числото може да се увеличи
    // с най-много 1
    result.resize(biggerLength + 2);

    bool carry = false;
    int carrySign = 0;
    for (size_t i = 1; i <= smallerLength; i++) {
        char sum =
            biggerSign*(biggerNum[biggerLength - i]-'0') +
            smallerSign*(smallerNum[smallerLength - i] - '0') +
            carrySign*carry + '0';

        carry = false;
        determineCarry(carry, carrySign, sum);

        result.number[biggerLength + 1 - i] = sum;
    }

    for (size_t i = smallerLength + 1; i <= biggerLength; i++) {
        char sum = biggerSign*(biggerNum[biggerLength - i] - '0') + carrySign * carry + '0';
        carry = false;
        determineCarry(carry, carrySign, sum);
        result.number[biggerLength + 1 - i] = sum;
    }
    //определяме дали дължината на числото ни се е увеличила
    result.number[0] = '0';
    if (carry && carrySign == 1) {
        result.number[0] = '1';
    }
    //премахваме нулите преди първата цифра
    trim(result.number);
    //ако сме получили нула, искаме да е положително число
    if (strcmp(result.number, "0") == 0) result.isNegative = false;
    return result;
}

BigInt BigInt::operator-(const BigInt& other) const
{
    //използваме унарния - и събирането
    return *this + (-other);   
}

BigInt BigInt::operator-() const
{
    BigInt result = *this;
    if(result != "0") result.isNegative = !isNegative;
    return result;
}

BigInt BigInt::operator*(const BigInt& other) const
{
    //проверка за умножение с 0
    if (*this == "0" || other == "0") return "0";

    BigInt result = "0";
    for (BigInt i = other.abs(); i > "0"; --i) {
        result += *this;
    }

    result.isNegative = !(this->isNegative == other.isNegative); //XOR на двете булеви променливи
    return result;
}

BigInt BigInt::operator%(const BigInt& other) const
{
    //делене с частно и остатък
    BigInt q = (*this) / other;
    return *this - q * other;
}

BigInt BigInt::operator/(const BigInt& other) const
{
    //проверка за дление на 0
    if (other == "0") return "0";

    BigInt result = "0";
    BigInt copy = this->abs();
    BigInt otherCopy = other.abs();

    while (copy > "0") {
        copy -= otherCopy;
        result++;
    }
    if (copy < "0") result--;

    result.isNegative = !(this->isNegative == other.isNegative);
    return result;
}

BigInt& BigInt::operator+=(const BigInt& other)
{
    *this = *this + other;
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& other)
{
    *this = *this - other;
    return *this;
}

BigInt& BigInt::operator++() {
    return *this += "1";
}

BigInt BigInt::operator++(int)
{
    BigInt result = *this;
    ++(*this);
    return result;
}

BigInt& BigInt::operator--()
{
    return *this -= "1";
}

BigInt BigInt::operator--(int)
{
    BigInt result = *this;
    --(*this);
    return result;
}



bool BigInt::operator==(const BigInt& other) const
{
    return isNegative == other.isNegative && strcmp(this->number, other.number) == 0;
}

bool BigInt::operator!=(const BigInt& other) const
{
    return isNegative != other.isNegative || strcmp(this->number, other.number) != 0;
}

bool BigInt::operator>(const BigInt& other) const
{
    size_t len = strlen(number);
    size_t lenOther = strlen(other.number);
    if (!isNegative && other.isNegative) return true;
    else if (isNegative && !other.isNegative) return false;
    else if (len < lenOther) return false;
    else if (len > lenOther) return true;
    else return strcmp(number, other.number) > 0;
}

bool BigInt::operator<(const BigInt& other) const
{
    size_t len = strlen(number);
    size_t lenOther = strlen(other.number);
    if (!isNegative && other.isNegative) return false;
    else if (isNegative && !other.isNegative) return true;
    else if (len < lenOther) return true;
    else if (len > lenOther) return false;
    else return strcmp(number, other.number) < 0;
}

bool BigInt::operator<=(const BigInt& other) const
{
    return *this < other || *this == other;
}

bool BigInt::operator>=(const BigInt& other) const
{
    return *this > other || *this == other;
}

std::ostream& operator<<(std::ostream& out, const BigInt& num)
{
    if (num.isNegative) out << '-';
    out << num.number;
    return out;
}

std::istream& operator>>(std::istream& in, BigInt& num)
{
    char input;
    size_t capacity = 2;
    size_t size = 0;
    num.free();
    num.number = new char[capacity] {0};

    in >> input;
    if (input == '-') {
        num.isNegative = true;
    }
    else if (input >= '0' && input <= '9')
    {
        num.number[size++] = input;
    }
    // четем докато на потока получаваме цифри и се грижим за динамичната памет
    while (in >> input && input >= '0' && input <= '9') {
        if (size + 1 >= capacity) {
            capacity *= 2;
            num.resize(capacity);
        }
        num.number[size++] = input;
    }
    // накрая заделяме толкова памет колкото ни е нужна за да пазим числото
    num.resize(size + 1);
    BigInt::trim(num.number);
    return in;
}
