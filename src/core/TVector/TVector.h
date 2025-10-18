// "Copyright 2025 Artem Denisov 3824B1PR2"
#include <iostream>
#include <utility>
#include <random>
#include <chrono>
#include <initializer_list>
#pragma once
#define CAPACITY 15
#define DELETED_LIMIT 0.15

enum class TVectorElemState { empty, busy, deleted };

template<class T> class TVector {
    T* _data = nullptr;
    int _size = 0;
    int _capacity = CAPACITY;
    size_t _deleted = 0;
    TVectorElemState* _states = nullptr;

public:
    // Constructors
    TVector();
    explicit TVector(int);
    TVector(int, const T*);
    explicit TVector(std::initializer_list<T>);
    TVector(int, std::initializer_list<T>);
    explicit TVector(const TVector<T>&);
    TVector(TVector&&) noexcept;

    // Destructor
    ~TVector();

    // Getters
    T* data() const noexcept;
    int size() const noexcept;
    int capacity() const noexcept;
    size_t deleted_count() const noexcept;
    T& front() const;
    T& back() const;
    T* begin() const;
    T* end() const;

    // Functions
    bool is_empty() const noexcept;
    bool is_full() const noexcept;
    bool is_available(int) const;
    T& at(int) const;
    void emplace(int, const T&);
    void assign(const TVector<T>&);

    // Insertion functions
    void push_front(const T&);
    void push_back(const T&);
    void insert(int, const T&);

    // Deletion functions
    void pop_front();
    void pop_back();
    void erase(int);

    // Memory management functions
    void clear() noexcept;
    void shrink_to_fit();
    void reserve(int);
    void resize(int);

    // Operators overload
    void operator=(const TVector<T>&);
    TVector& operator=(TVector&&) noexcept;
    bool operator==(const TVector<T>&) const;
    bool operator!=(const TVector<T>&) const;
    T& operator[](int) const;

private:
    void effective_deletion();
    T& reverse_at(int) const;
    TVectorElemState get_state(int) const;
    int index_recalculation(int) const;
    void shifting_elements(int, int);
};

// Realization

// Constructors
template<class T> TVector<T>::TVector() {
    _data = new T[_capacity];
    _states = new TVectorElemState[_capacity];
    for (int i = 0; i < _capacity; i++) _states[i] = TVectorElemState::empty;
}

template<class T> TVector<T>::TVector(int size) {
    if (size < 0) throw std::invalid_argument("TVector.size_constructor: Invalid argument 'size' - must be >= 0");
    _size = size;
    if (_size == 0) {
        _data = new T[_capacity];
        _states = new TVectorElemState[_capacity];
        for (int i = 0; i < _capacity; i++) _states[i] = TVectorElemState::empty;
    }
    else {
        _capacity = size + CAPACITY;
        _data = new T[_capacity];
        _states = new TVectorElemState[_capacity];
        for (int i = 0; i < _size; i++) _states[i] = TVectorElemState::busy;
        for (int i = _size; i < _capacity; i++) _states[i] = TVectorElemState::empty;
    }
}

template<class T> TVector<T>::TVector(int size, const T* data) {
    if (size < 0) {
        throw std::invalid_argument("TVector.sizedata_constructor: Invalid argument 'size' - must be >= 0");
    }
    if (data == nullptr && size > 0) {
        throw std::invalid_argument("TVector.size_constructor: Invalid argument 'data' - is nullptr");
    }
    _size = size;
    _capacity = _size + CAPACITY;
    _data = new T[_capacity];
    _states = new TVectorElemState[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = data[i];
        _states[i] = TVectorElemState::busy;
    }
    for (int i = _size; i < _capacity; i++) {
        _states[i] = TVectorElemState::empty;
    }
}

template<class T> TVector<T>::TVector(std::initializer_list<T> init) {
    if (init.size() > 0) {
        _size = init.size();
        _capacity = _size + CAPACITY;
        _data = new T[_capacity];
        _states = new TVectorElemState[_capacity];
        const T* src = init.begin();
        for (int i = 0; i < _size; i++) {
            _data[i] = src[i];
            _states[i] = TVectorElemState::busy;
        }
        for (int i = _size; i < _capacity; i++) {
            _states[i] = TVectorElemState::empty;
        }
    }
}

template<class T> TVector<T>::TVector(int size, std::initializer_list<T> init) {
    if (size < 0) {
        throw std::invalid_argument("TVector.sizeinitlist_constructor: Invalid argument 'size' - must be >= 0");
    }
    if (size > 0) {
        _size = size;
        _capacity = _size + CAPACITY;
        _data = new T[_capacity];
        _states = new TVectorElemState[_capacity];
        const T* src = init.begin();
        for (int i = 0; i < _size; i++) {
            _data[i] = src[i];
            _states[i] = TVectorElemState::busy;
        }
        for (int i = _size; i < _capacity; i++) {
            _states[i] = TVectorElemState::empty;
        }
    }
}

template<class T> TVector<T>::TVector(const TVector<T>& other) {
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    _deleted = other._deleted;
    _states = new TVectorElemState[_capacity];
    for (int i = 0; i < _capacity; i++) {
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }
}

template<class T> TVector<T>::TVector(TVector&& other) noexcept :
    _data(std::exchange(other._data, nullptr)),
    _size(std::exchange(other._size, 0)),
    _capacity(std::exchange(other._capacity, CAPACITY)),
    _deleted(std::exchange(other._deleted, 0)),
    _states(std::exchange(other._states, nullptr))
{

}


// Destructor
template<class T> TVector<T>::~TVector() {
    if (_data != nullptr) {
        delete[] _data;
        delete[] _states;
    }
}

// Getters
template<class T> T* TVector<T>::data() const noexcept {
    return _data;
}

template<class T> int TVector<T>::size() const noexcept {
    return static_cast<int>(_size - _deleted);
}

template<class T> int TVector<T>::capacity() const noexcept {
    return _capacity;
}

template<class T> size_t TVector<T>::deleted_count() const noexcept {
    return _deleted;
}

template<class T> T& TVector<T>::front() const {
    return at(0);
}

template<class T> T& TVector<T>::back() const {
    return reverse_at(size() - 1);
}

// Functions
template<class T> bool TVector<T>::is_empty() const noexcept {
    if (size() == 0) return true;
    for (int i = 0; i < size(); i++) {
        if (_states[i] == TVectorElemState::busy) return false;
    }
    return true;
}

template<class T> bool TVector<T>::is_full() const noexcept {
    return size() >= _capacity;
}

template<class T> bool TVector<T>::is_available(int index) const {
    if (index >= size() || index < 0) {
        throw std::out_of_range("TVector.is_available: 'index' out of range or vector is empty");
    }
    if (get_state(index) == TVectorElemState::busy) return false;
    return true;
}

template<class T> T& TVector<T>::at(int index) const {
    if (index >= size() || index < 0) {
        throw std::out_of_range("TVector.at: 'index' out of range or vector is empty");
    }
    return _data[index_recalculation(index)];
}

template<class T> void TVector<T>::emplace(int index, const T& value) {
    if (index >= size() || index < 0) {
        throw std::out_of_range("TVector.emplace: 'index' out of range or vector is empty");
    }
    at(index) = value;
}

template<class T> void TVector<T>::assign(const TVector<T>& other) {
    delete[] _states;
    delete[] _data;
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    _states = new TVectorElemState[_capacity];
    _deleted = other._deleted;
    for (int i = 0; i < _capacity; i++) {
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }
}

// Insertion functions
template<class T> void TVector<T>::push_front(const T& value) {
    if (_size == 0) _size++;
    if (_states[0] == TVectorElemState::busy) {
        _size++;
        if (is_full()) reserve(_size + CAPACITY);
        shifting_elements(_size - 1, 0);
    }
    if (_states[0] == TVectorElemState::deleted) _deleted--;
    _data[0] = value;
    _states[0] = TVectorElemState::busy;
}

template<class T> void TVector<T>::push_back(const T& value) {
    if (_size == 0) _size++;
    if (_states[_size - 1] == TVectorElemState::busy) {
        _size++;
        if (is_full()) reserve(_size + CAPACITY);
    }
    if (_states[_size - 1] == TVectorElemState::deleted) _deleted--;
    _data[_size - 1] = value;
    _states[_size - 1] = TVectorElemState::busy;
}

template<class T> void TVector<T>::insert(int index, const T& value) {
    if (_size == 0) _size++;
    int real_index = index_recalculation(index);
    _size++;
    if (is_full()) reserve(_size + CAPACITY);
    shifting_elements(_size - 1, real_index);
    _data[real_index] = value;
    _states[real_index] = TVectorElemState::busy;
}

// Deletion functions
template<class T> void TVector<T>::pop_front() {
    if (is_empty()) {
        throw std::logic_error("TVector.pop_front: Impossible to delete - there are no elements in the vector");
    }
    _states[index_recalculation(0)] = TVectorElemState::deleted;
    _deleted++;
    if (_deleted >= static_cast<int>(_size * DELETED_LIMIT)) {
        effective_deletion();
    }
}

template<class T> void TVector<T>::pop_back() {
    if (is_empty()) {
        throw std::logic_error("TVector.pop_back: Impossible to delete - there are no elements in the vector");
    }
    int index = 0;
    for (int i = _size - 1; i >= 0; i--) {
        if (_states[i] == TVectorElemState::busy) {
            index = i;
            break;
        }
    }
    _states[index] = TVectorElemState::empty;
    _size--;
}

template<class T> void TVector<T>::erase(int index) {
    if (is_empty()) {
        throw std::logic_error("TVector.erase: Impossible to delete - there are no elements in the vector");
    }
    int real_index = index_recalculation(index);
    if (real_index == size() - 1) {
        pop_back();
        return;
    }
    _states[real_index] = TVectorElemState::deleted;
    _deleted++;
    if (_deleted >= static_cast<int>(_size * DELETED_LIMIT)) {
        effective_deletion();
    }
}

// Memory management functions
template<class T> void TVector<T>::clear() noexcept {
    _size = 0;
    _deleted = 0;
    for (int i = 0; i < _capacity; i++) _states[i] = TVectorElemState::empty;
}

template<class T> void TVector<T>::shrink_to_fit() {
    effective_deletion();
    if (_size < _capacity) {
        T* new_data = new T[_size];
        TVectorElemState* new_states = new TVectorElemState[_size];
        for (int i = 0; i < _size; i++) {
            new_data[i] = _data[i];
            new_states[i] = _states[i];
        }
        delete[] _data;
        delete[] _states;
        _data = new_data;
        _states = new_states;
        _capacity = _size;
    }
}

template<class T> void TVector<T>::reserve(int new_capacity) {
    effective_deletion();
    if (new_capacity > _capacity) {
        T* new_data = new T[new_capacity];
        TVectorElemState* new_states = new TVectorElemState[new_capacity];
        for (int i = 0; i < _capacity; i++) {
            new_data[i] = _data[i];
            new_states[i] = _states[i];
        }
        for (int i = _capacity; i < new_capacity; i++) new_states[i] = TVectorElemState::empty;
        delete[] _data;
        delete[] _states;
        _data = new_data;
        _states = new_states;
        _capacity = new_capacity;
    }
}

template<class T> void TVector<T>::resize(int new_size) {
    if (new_size < 0) {
        throw std::invalid_argument("TVector.resize: Invalid argument 'new_size' - must be >= 0");
    }
    effective_deletion();
    if (new_size == size()) return;
    if (new_size < size()) {
        int cnt = 0;
        for (int i = new_size; i < _size; i++) _states[i] = TVectorElemState::empty;
    }
    else {
        if (new_size >= _capacity) reserve(new_size + CAPACITY);
        for (int i = _size; i < new_size; i++) _states[i] = TVectorElemState::empty;
    }
    _size = new_size;
}


// Operators overload
template <class T> void TVector<T>::operator=(const TVector<T>& other) {
    assign(other);
}

template <class T> TVector<T>& TVector<T>::operator=(TVector&& other) noexcept {
    if (this != &other) {
        delete[] _data;
        delete[] _states;

        _data = std::exchange(other._data, nullptr);
        _size = std::exchange(other._size, 0);
        _capacity = std::exchange(other._capacity, CAPACITY);
        _deleted = std::exchange(other._deleted, 0);
        _states = std::exchange(other._states, nullptr);
    }
    return *this;
}

template <class T> bool TVector<T>::operator==(const TVector<T>& other) const {
    if (size() != other.size()) return false;
    if (is_empty()) return true;
    for (int i = 0; i < size(); i++) {
        if (at(i) != other.at(i)) return false;
    }
    return true;
}

template <class T> bool TVector<T>::operator!=(const TVector<T>& other) const {
    return !(*this == other);
}

template <class T> T& TVector<T>::operator[](int index) const {
    return at(index);
}

// Private functions
template<class T> void TVector<T>::effective_deletion() {
    if (deleted_count() == 0) return;
    int new_size = size();
    int index = 0;
    for (int i = 0; i < _size; i++) {
        if (_states[i] == TVectorElemState::busy) {
            _data[index] = _data[i];
            _states[index] = TVectorElemState::busy;
            index++;
        }
    }
    for (int i = new_size; i < _capacity; i++) _states[i] = TVectorElemState::empty;
    _size = new_size;
    _deleted = 0;
}

template<class T> T& TVector<T>::reverse_at(int index) const {
    if (is_empty()) {
        throw std::logic_error("TVector.reverse_at: Impossible to access an element - there are no elements in the vector");
    }
    return _data[index_recalculation(index)];
}

template<class T> TVectorElemState TVector<T>::get_state(int index) const {
    if (is_empty()) {
        throw std::logic_error("TVector.get_state: Impossible to get state - there are no elements in the vector");
    }
    return _states[index_recalculation(index)];
}

template<class T> int TVector<T>::index_recalculation(int index) const {
    if (index >= size() || index < 0) {
        throw std::out_of_range("TVector.index_recalculation: 'index' out of range");
    }
    int busy_index = -1, real_index = index;
    for (int i = 0; i < _size; i++) {
        if (_states[i] == TVectorElemState::busy) busy_index++;
        if (busy_index == index) {
            real_index = i;
            break;
        }
    }
    return real_index;
}

template<class T> void TVector<T>::shifting_elements(int begin, int end) {
    for (int i = begin; i > end; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
}

// Friend functions

// Search functions
template <class T> int find_first(const TVector<T>& vector, const T& value) {
    if (vector.is_empty()) {
        throw std::logic_error("find_first: Impossible to find an element - vector is empty");
    }
    for (int i = 0; i < vector.size(); i++) {
        if (vector.at(i) == value) return i;
    }
    return -1;
}

template <class T> int find_last(const TVector<T>& vector, const T& value) {
    if (vector.is_empty()) {
        throw std::logic_error("find_last: Impossible to find an element - vector is empty");
    }
    for (int i = vector.size() - 1; i >= 0; i--) {
        if (vector.at(i) == value) return i;
    }
    return -1;
}

template <class T> int* find_all(const TVector<T>& vector, const T& value) {
    if (vector.is_empty()) {
        throw std::logic_error("find_all: Impossible to find elements - vector is empty");
    }
    int* result = nullptr, size_res = 0;
    for (int i = 0; i < vector.size(); i++) {
        if (vector.at(i) == value) size_res++;
    }

    if (size_res == 0) {
        result = new int[1];
        result[0] = -1;
    }
    else {
        result = new int[size_res];
        for (int i = 0, j = 0; j < size_res; i++) {
            if (vector.at(i) == value) {
                result[j] = i;
                j++;
            }
        }
    }
    return result;
}

// Shuffling

template <class T> void vectorShuffle(TVector<T>& vec) {
    if (vec.size() <= 1) return;
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = vec.size() - 1; i > 0; i--) {
        std::uniform_int_distribution<> distr(0, i);
        int j = distr(gen);
        std::swap(vec[i], vec[j]);
    }
}

template <class T> void vectorShuffle(TVector<T>& vec, std::mt19937& gen) {
    if (vec.size() <= 1) return;
    for (int i = vec.size() - 1; i > 0; i--) {
        std::uniform_int_distribution<> distr(0, i);
        int j = distr(gen);
        std::swap(vec[i], vec[j]);
    }
}
