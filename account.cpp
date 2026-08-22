#include "account.hpp"

void *operator new(std::size_t n){

				void *p = std::malloc(n + sizeof(n));

				if (!p){

						throw std::bad_alloc();
				}

				auto q = static_cast<std::size_t*>(p);
				/*q points to hidden n*/
				*q = n;

				Accountant::get().take(n);

				return q+1;
		}

		void *operator new[] (std::size_t n){

				void *p = std::malloc(n + sizeof(n));
				if (!p){

						throw std::bad_alloc();
				}

				auto q = static_cast<std::size_t*>(p);
				/*q points to hidden n*/
				*q = n;

				Accountant::get().take(n);

				return q+1;
		}


		void operator delete(void* q) noexcept {

				if (!q){

						return;
				}

				auto p = static_cast<std::size_t*>(q)-1;

				Accountant::get().give_back(*p);

				std::free(p);

		}

		void operator delete[](void* q) noexcept {

				if (!q){

						return;
				}

				auto p = static_cast<std::size_t*>(q)-1;

				Accountant::get().give_back(*p);

				std::free(p);
		}

int main(){

		auto pre = Accountant::get().how_much();
		
		{
				int *p = new int{3};

				int *q = new int[10]{3};

				delete p;
		}

		auto post = Accountant::get().how_much();

		if (post != pre){

				std::cout << post - pre << std::endl;
		}

		return 0;
}
