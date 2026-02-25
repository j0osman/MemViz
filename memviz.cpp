#include <iostream>
#include <print>
#include <cstdint>
#include <string>

template <typename T>
void analyze_mem(std::string name){
	T* p1 = new T();
	T* p2 = new T();

	uintptr_t addr1 = reinterpret_cast<uintptr_t>(p1);
	uintptr_t addr2 = reinterpret_cast<uintptr_t>(p2);

	size_t physical_size = (addr1>addr2) ? (addr1-addr2) : (addr2-addr1);
	size_t logical_size = sizeof(T);
	size_t waste = physical_size - logical_size;
	double efficiency = (double)logical_size/physical_size;

	std::println("DATA TYPE: {}", name);
	std::println(" Address A: {:p}", (void*)p1);
	std::println(" Address B: {:p}", (void*)p2);
	std::println(" Logical Size: {}", logical_size);
	std::println(" Physical Size: {}", physical_size);
	std::println(" Waste: {}", waste);
	std::println(" Efficiency: {:.2f}%", efficiency*100.0);

	delete p1;
	delete p2;

	std::println("---------------------------------------------------\n");

}


int main(){

	analyze_mem<int>("Integer");
	analyze_mem<long long>("Long Integer");
	analyze_mem<double>("Double");
	analyze_mem<long double>("Long Double");
	analyze_mem<char>("Character");
	analyze_mem<std::string>("String");

	return 0;
}
