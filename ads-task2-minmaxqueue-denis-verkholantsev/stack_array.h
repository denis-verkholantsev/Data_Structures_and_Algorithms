#include <exception>

namespace my {
template <typename T>
class stack {
  T* data_;
  int size_;
  int capacity_;

 public:
  stack() : size_(0), capacity_(8) { data_ = new T[8]; };
  ~stack() { delete[] data_; }

  int size() const { return size_; };

  void capacity_x2() {
    capacity_ *= 2;
    T* tmp = new T[capacity_];
    for (int i = 0; i < size_; ++i) {
      tmp[i] = data_[i];
    }
    delete[] data_;
    data_ = nullptr;
    data_ = tmp;
  };

  void push(const T& X) {
    if (size_ == capacity_) {
      capacity_x2();
    }
    data_[size_++] = X;
  };

  T pop_back() {
    if (size_ < 1) {
      throw std::exception();
    }
    return data_[--size_];
  };

  T top() const { return data_[size_ - 1]; };

  bool empty() const { return size_ == 0; };
};
}  // namespace my