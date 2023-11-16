#include <iostream>
#include <cassert>
using namespace std;

template <typename T, size_t N>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;
private:
    Grid<T, N - 1>* data;
    size_type x_n_size;
public:
    template <typename first, typename ...args>
    Grid(T const& t, first size1, args... size) : data(new Grid<T, N-1>[size1]), x_n_size(size1) {
        for (size_type i = 0; i != size1; ++i) {
            data[i] = Grid<T, N-1>(t, size...);
        }
    }

    Grid() : data(new Grid<T, N - 1>[1]), x_n_size(1) {}

    Grid(Grid<T, N> const& other) : data(other.data), x_n_size(other.x_n_size) {}

   ~Grid(){
       delete[] data;
   }

   Grid<T, N>& operator=(Grid<T, N>& other) {
        delete[] data;
        data = new Grid<T, N-1>[other.x_n_size];
        x_n_size = other.x_n_size;
        for (int i = 0; i != x_n_size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
   }

    Grid<T, N>& operator=(Grid<T, N>&& other) {
        swap(data, other.data);
        swap(x_n_size, other.x_n_size);
        return *this;
    }

    Grid<T, N-1> operator[](size_type idx) {
        return data[idx];
    }

    Grid<T, N - 1> operator[](size_type idx) const{
        return data[idx];
    }

    template <typename first, typename... other>
    T& operator()(first f_idx, other... idx) {
        return data[f_idx](idx...);
    }

    template <typename first, typename... other>
    T operator()(first f_idx, other... idx) const {
        return data[f_idx](idx...);
    }

};

template <typename T>
class Grid<T, 2> final {
public:
    using value_type = T;
    using size_type = unsigned;
private:
    T* data;
    size_type y_size, x_size;

public:

    Grid(): data(new T[1]), y_size(1), x_size(1) {}

    Grid(T* data, size_type y_size, size_type x_size) : data(data), y_size(y_size), x_size(x_size) {}

    Grid(Grid<T, 2> const& other) : data(other.data), y_size(other.y_size), x_size(other.x_size) {}

    Grid(T const& t, size_type y_size, size_type x_size) : data(new T[x_size * y_size]), y_size(y_size), x_size(x_size) {
        for (size_type i = 0; i != x_size * y_size; ++i) {
            data[i] = t;
        }
    }

   Grid(Grid<T, 2>&& other) {
        std::swap(other.data, data);
        std::swap(other.y_size, y_size);
        std::swap(other.x_size, x_size);
    }

    Grid(T const& t) : data(new T[1]), y_size(1), x_size(1) {
        data[0] = t;
    }

    Grid(size_type y_size, size_type x_size) : data(new T[x_size * y_size]), y_size(y_size), x_size(x_size) {
        for (size_type i = 0; i != x_size * y_size; ++i) {
            data[i] = T();
        }
    }

   ~Grid() {
        delete[] data;
    }

    Grid<T, 2>& operator=(Grid<T, 2>& other) {
        y_size = other.y_size;
        x_size = other.x_size;
        delete[] data;
        T* data = new T[x_size * y_size];
        memcpy(data, other.data, x_size * y_size * sizeof(T));
        return *this;
    }

    Grid<T, 2>& operator=(Grid<T, 2>&& other) {
        std::swap(other.data, data);
        std::swap(other.y_size, y_size);
        std::swap(other.x_size, x_size);
        return *this;
    }

    T operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    T& operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T, 2>& operator=(T const& t) {
        for (auto it = data, end = data + x_size * y_size; it != end; ++it) {
            *it = t;
        }
        return *this;
    }

    T* operator[](size_type y_idx) {
        return data + y_idx * x_size;
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};


int main() {
    return 0;
}