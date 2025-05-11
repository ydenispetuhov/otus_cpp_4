#include <string>
#include <type_traits>

struct SomeStruct {

	template <typename TT,
			  typename Fake =
				  typename std::enable_if<
					  !std::is_same<typename std::remove_reference<TT>::type,
									SomeStruct>::value,
					  void>::type>
	SomeStruct(TT &&value) : m_value{std::forward<TT>(value)} {
	}

	SomeStruct(const SomeStruct &other) : m_value{other.m_value} {
	}

	const std::string &getValue() const {
		return m_value;
	}

private:
	std::string m_value;
	std::string m_value2;
};

int main() {

	SomeStruct first("Hello, World!");
	SomeStruct second = first;

	return 0;
}
