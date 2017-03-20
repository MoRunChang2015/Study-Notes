#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

template <typename T>
class shared_ptr;

template <typename T>
class refer_to_object {
    friend class shared_ptr<T>;
    refer_to_object(T* p) : _ptr(p), refer_count(1){};
    refer_to_object(const refer_to_object&) = delete;
    refer_to_object& operator=(const refer_to_object&) = delete;
    refer_to_object(refer_to_object&&) = delete;
    refer_to_object& operator=(refer_to_object&&) = delete;
    ~refer_to_object() = default;

    void refer_inc() { ++refer_count; }

    void refer_dec() {
        --refer_count;
        if (refer_count == 0) {
            delete _ptr;
            _ptr = nullptr;
        }
    }

    T* _ptr;
    int refer_count;
};

template <typename T>
class shared_ptr {
   public:
    shared_ptr() : _p(nullptr){};
    shared_ptr(T* p) : _p(new refer_to_object<T>(p)){};
    shared_ptr(const shared_ptr<T>& sp) {
        _p = sp._p;
        _p->refer_inc();
    }
    shared_ptr(shared_ptr<T>&& sp) {
        _p = sp._p;
        _p->refer_inc();
        sp._p->refer_dec();
    }
    shared_ptr& operator=(const shared_ptr<T>& sp) {
        if (this == &sp)
            return *this;
        if (_p != nullptr) _p->refer_dec();
        _p = sp._p;
        _p->refer_inc();
        return *this;
    }
    shared_ptr& operator=(shared_ptr<T>&& sp) {
        if (this == &sp)
            return *this;
        if (_p != nullptr) _p->refer_dec();
        _p = sp._p;
        _p->refer_inc();
        sp._p->refer_dec();
        return *this;
    }

    ~shared_ptr() { _p->refer_dec(); }

    void reset(T* p = nullptr) {
        _p->refer_dec();
        if (p == nullptr) {
            _p = nullptr;
        } else {
            _p = new refer_to_object<T>(p);
        }
    }

    T& operator*() const noexcept { return *(_p->_ptr); }

    T* operator->() const noexcept { return _p->_ptr; }

   private:
    refer_to_object<T>* _p;
};

#endif
