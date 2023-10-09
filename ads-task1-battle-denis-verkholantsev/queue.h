namespace my {
template <typename T>
class queue {
 private:
  class node {
   public:
    T _elem;
    node* _next;
    node(T elem) : _elem(elem), _next(nullptr){};
  };
  node* _first;
  node* _last;

 public:
  queue() : _first(nullptr), _last(nullptr){};
  ~queue() {
    while (!this->empty()) {
      this->pop();
    }
  };
  bool empty() { return _first == nullptr; };
  void push(T elem) {
    if (!this->empty()) {
      this->_last->_next = new node(elem);
      this->_last = this->_last->_next;
    } else {
      this->_first = this->_last = new node(elem);
    }
  };
  T pop() {
    T first_elem;
    if (!this->empty()) {
      node* is_new = _first;
      first_elem = _first->_elem;
      this->_first = this->_first->_next;
      delete is_new;
      return first_elem;
    }
    return first_elem;
  };
  void make_empty() {
    while (!this->empty()) {
      this->pop();
    }
  };
};
}  // namespace my
