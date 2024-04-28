#ifndef MY_STOCK_LIST_H
# define MY_STOCK_LIST_H
#include "myList.h"
#include "myStock.h"
#include<iostream>
#include<algorithm>
using namespace myList;
using namespace myStock;
using std::unique_ptr;
using std::make_unique;
using std::sort;
using std::cout;
using std::endl;

namespace myStockList {
    class stockListType: public listType<stockType> {
        public:
        stockListType() = default;
        ~stockListType() = default;
        // Insert a stock into the stock list, return true if insertion is performed successfully
        // return false otherwise.
        bool insert_stock(stockType &s) {
            if (length == max_length) {
                return false;
            }
            unique_ptr<stockType> stock_ptr = make_unique<stockType>(s);
            list.push_back(stock_ptr);
            length += 1;
            return true;
        }

        // View the list of stocks sorted by stock ticker
        void view_by_ticker() {
            sort(list.begin(), list.end(), comp_by_ticker_ptr);
            const int fieldWidth = myList::listType<stockType>::fieldWidth;
            cout << setw(fieldWidth) << "Symbol"
        }

        // View the list of stocks sorted by one-day gain
        void view_by_gain();
    };
}
#endif