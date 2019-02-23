#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>
#include <cmath>
#include <numeric>
//#include <string_view>

typedef double Type;
typedef std::vector<Type> DType;
// typedef std::vector<double> F64Type;

template<class YI>
std::vector<YI> CombRadixF(YI V, const YI& Radix) {
	std::vector<YI> R;
	while (V) {

		R.push_back(std::fmod( V,Radix));
		V /= Radix;
		YI Temp = (std::fmod(V,Radix)/Radix);
		R.back() += Temp / Radix;
	}

	return R;
}
template<class YI>
std::vector<YI> CombRadix(YI V, const YI& Radix) {
	std::vector<YI> R;
	while (V) {

		R.push_back(V%Radix);
		V /= Radix;
		YI Temp = ((V%Radix)/Radix);
		R += Temp / Radix;
	}

	return R;
}
template<class YI>
YI RestorRadix(const std::vector<YI>& V, const YI& Radix) {
	YI R = 1;
	for (std::size_t i = 0; i < V.size(); i++) {
		if (std::numeric_limits<Type>::epsilon() >= V[i]) {
			R = 1;
			continue;
		}
		//R *= Radix;
		R *= 1* V[i] * Radix;
	}

	return R;
}


bool Test() {
	Type V = 1234567890;
	std::string ch = "0123456789abcdef";
	const Type Radix = 16;
	auto R = CombRadixF<Type>(V, Radix);
	std::reverse(R.begin(), R.end());
	auto k = RestorRadix<Type>(R, Radix);

	//std::reverse(R.begin(), R.end());

	for (std::size_t i = 0; i < R.size();i++) {
		if (std::numeric_limits<Type>::epsilon()>=R[i]) continue;
		std::cout << ch[static_cast<std::uint8_t>(R[i])];
	}
	std::cout << std::endl;

	std::cout << std::hex << V << std::endl;

	std::cout <<std::dec<< k << std::endl;

	return true;
}

int main() {
	Test();

	return 0;
}