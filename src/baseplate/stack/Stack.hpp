#pragma once

#include <vector>

template <typename T>
struct BSPLT_Stack {
private:

    std::vector<T> Content;

public:

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