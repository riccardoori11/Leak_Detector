#ifndef LEAK_DETECTOR_H
#define LEAK_DETECTOR_H

#include <cstdlib>
#include <iostream>
#include <atomic>
#include <new>

class Accountant{

		std::atomic<long long> curr;
		Accountant(): curr{0LL}{};

public:

		Accountant(const Accountant& other) = delete;

		Accountant& operator= (const Accountant& other) = delete;

		static auto& get(){
				static Accountant singleton;
				return singleton;

		};

		void take(std::size_t n){

				curr += n;
		}

		void give_back(std::size_t n){

				curr -= n;
		}

		std::size_t how_much() const{

				return curr.load();
		};
};

		void *operator new(std::size_t n);

		void *operator new[] (std::size_t n);



		void operator delete(void* q) noexcept;

		void operator delete[](void* q) noexcept; 


#endif


