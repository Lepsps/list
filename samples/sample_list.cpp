#include <iostream>
#include "list.h"
#include <stdexcept>

//---------------------------------------------------------------------------

template <typename T>
list<T> numToList(unsigned int num) {
    list<T> res;
    if (num == 0) {
        res.push_back(0);
        return res;
    }
    while (num > 0) {
        res.push_back(num % 10);
        num /= 10;
    }
    return res;
}

template <typename T>
void multiplyByDigit(list<T>& res,  list<T>& num, int digit, int pos) {
    int carry = 0;
    list<T> tmp;
        
    for (int i = 0; i < pos; i++)
        tmp.push_back(0);

    for (auto it = num.begin(); it != num.end(); ++it) {
        int product = num.at(it) * digit + carry;
        tmp.push_back(product % 10);
        carry = product / 10;
    }
    if (carry > 0)
        tmp.push_back(carry);

    if (res.empty())
        res = std::move(tmp);
    else {

        list<T> new_res;
        auto it1 = res.begin();
        auto it2 = tmp.begin();
        int carry = 0;

        while (it1 != res.end() || it2 != tmp.end()) {
            int sum = carry;
            if (it1 != res.end()) {
                sum += res.at(it1);
                ++it1;
            }
            if (it2 != tmp.end()) {
                sum += tmp.at(it2);
                ++it2;
            }
            new_res.push_back(sum % 10);
            carry = sum / 10;
        }

        if (carry > 0) {
            new_res.push_back(carry);
        }

        res = std::move(new_res);
    }
}

template <typename T>
list<T> multiplyList( list<T>& num, unsigned int mult) {
    list<T> res;

    if (mult == 0 || num.at(num.begin()) == 0) {
        res.push_back(0);
        return res;
    }

    int pos = 0;

    while (mult > 0) {
        int digit = mult % 10;
        multiplyByDigit(res, num, digit, pos);
        mult /= 10;
        pos++;
    }

    return res;
}


template <typename T>
void printList( list<T>& lst) {
    list<T> rev;
    for (auto it = lst.begin(); it != lst.end(); ++it) 
        rev.push_front(lst.at(it));

    for (auto it = rev.begin(); it != rev.end(); ++it) 
        std::cout << rev.at(it);
    std::cout << std::endl;
}


int main() {
    while (true) {
        unsigned int num, mult;

        std::cout << "Enter the first num: ";
        std::cin >> num;

        std::cout << "Enter the second num: ";
        std::cin >> mult;

        list<int> num_list = numToList<int>(num);
        list<int> res = multiplyList(num_list, mult);

        std::cout << "Result: ";
        printList(res);

    }
    return 0;
}
//---------------------------------------------------------------------------
