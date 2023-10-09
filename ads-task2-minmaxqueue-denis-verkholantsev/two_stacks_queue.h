
#include <cstddef>

#include "stack_array.h"

namespace my {
template <typename T>
class two_stacks_queue {
 private:
  T min_1 = (T)NULL;
  T max_1 = (T)NULL;
  struct element {
    T elem;
    T min;
    T max;
    element() : elem((T)NULL), min((T)NULL), max((T)NULL){};
    element(T el, T min_, T max_) : elem(el), min(min_), max(max_){};
  };
  my::stack<T> stack_1;
  my::stack<element> stack_2;

 public:
  two_stacks_queue() = default;
  void push(T X) {
    if (!stack_1.empty()) {
      min_1 = X < min_1 ? X : min_1;
      max_1 = X > max_1 ? X : max_1;
    } else {
      min_1 = max_1 = X;
    }
    stack_1.push(X);
  };

  T pop() {
    while (!stack_1.empty()) {
      T tmp = stack_1.pop_back();
      if (!stack_2.empty()) {
        stack_2.push(
            element(tmp, tmp < stack_2.top().min ? tmp : stack_2.top().min,
                    tmp > stack_2.top().max ? tmp : stack_2.top().max));
      } else {
        stack_2.push(element(tmp, tmp, tmp));
      }
    }
    min_1 = max_1 = (T)NULL;
    return stack_2.pop_back().elem;
  };

  T get_min() {
    if (stack_1.size() && stack_2.size()) {
      return min_1 < stack_2.top().min ? min_1 : stack_2.top().min;
    }
    if (stack_2.size()) {
      return stack_2.top().min;
    }
    return min_1;
  };

  T get_max() {
    if (stack_1.size() && stack_2.size()) {
      return max_1 > stack_2.top().max ? max_1 : stack_2.top().max;
    }
    if (stack_2.size()) {
      return stack_2.top().max;
    }
    return max_1;
  };
};
}  // namespace my
