#ifndef MY_LIST_H
# define MY_LIST_H
#include<vector>
#include<memory>
using std::vector;
using std::unique_ptr;

namespace myList {
    template<typename T> class listType {
        public:
        listType() = default;
        virtual ~listType() = 0;
        static int fieldWidth;

        protected: // Members access permission to sub classes
        vector<unique_ptr<T>> list;
        int length = 0;
        size_t max_length = 50; // Maximum number of objects the list can hold
    };
}
#endif