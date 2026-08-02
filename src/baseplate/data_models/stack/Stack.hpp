#pragma once

#include <vector>

namespace baseplate {

    template <typename T>
    struct Stack {
    private:

        std::vector<T> content;

    public:

    Stack() {}

        void Push(T instance) {

            content.push_back(instance);
        }

        void Pop() {
            if (!content.empty())
                content.pop_back();
        }

        bool IsEmpty() {

            return content.empty();
        }

        size_t Size() {

            return content.size();
        }

        T Get() {

            return content.back();
        }
    };
}