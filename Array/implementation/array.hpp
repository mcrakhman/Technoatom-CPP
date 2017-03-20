#ifndef ARRAY_HPP_
#define ARRAY_HPP_

template <class T, std::size_t N>
Array<T, N>::Array() :
	ContainerInterface(static_data_, N){
}

template <class T, std::size_t N>
Array<T, N>::Array(const Array & that) :
	ContainerInterface(static_data_, that.size_) {
	for (std::size_t i = 0; i < size_; i++) {
		data_[i] = that[i];
	}
}


template <class T, std::size_t N>
Array<T, N>::~Array() { for (auto& i : static_data_) i = 0; }


template <class T, std::size_t N>
const Array<T, N> & Array<T, N>::operator=(const Array & that) {
	if (this == &that) {
		return *this;
	}
	Array<T, N> tmp_array(that);
	swap(tmp_array);
	return *this;
}

template <class T, std::size_t N>
void Array<T, N>::swap(Array & that) {
	std::swap(static_data_, that.static_data_);
}

;
#endif // ARRAY_HPP_