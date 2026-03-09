#include <iostream>
#include <print>
#include <cstdint>
#include <vector>
#include <string>

template <typename T>
void analyze_mem(std::string name){

	const int N = 100000;
	std::vector<uintptr_t> addrs;

	for(int i=0; i<N; i++){
		T* p = new T();
		addrs.push_back(reinterpret_cast<uintptr_t>(p));
	}

	std::sort(addrs.begin(), addrs.end());

	size_t gap = addrs.back()-addrs[0];

	double physical_size = (double)gap/N;
	size_t logical_size = sizeof(T);
	size_t overhead = (size_t)physical_size - logical_size;
	double efficiency = (double)logical_size/physical_size;

	std::println("DATA TYPE: {}", name);
	std::println(" Logical Size: {}", logical_size);
	std::println(" Physical Size: {}", physical_size);
	std::println(" Overhead: {}", overhead);
	std::println(" Efficiency: {:.2f}%", efficiency*100.0);

	for(auto it: addrs) delete reinterpret_cast<T*>(it);

	std::println("---------------------------------------------------\n");

}


int main(){

	std::println("---------------------New/Delete-------------------------\n");
	analyze_mem<int>("Integer");
	analyze_mem<long long>("Long Integer");
	analyze_mem<double>("Double");
	analyze_mem<long double>("Long Double");
	analyze_mem<char>("Character");
	analyze_mem<std::string>("String");

	return 0;
}
