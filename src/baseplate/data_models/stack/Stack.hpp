#pragma once

#include <vector>

namespace baseplate {

    template <typename T>
    struct Stack {
    private:

        std::vector<T> Content;

    public:

    Stack() {}

        void Push(T instance) {

            Content.push_back(instance);
        }

        void Pop() {
            if (!Content.empty())
                Content.pop_back();
        }

        bool IsEmpty() {

            return Content.empty();
        }

        size_t Size() {

            return Content.size();
        }

        T Get() {

            return Content.back();
        }
    };
}