#include <iostream>

class sample_class{
	void private_method(){
		std::cout << "Private method called" << std::endl;
	}
};

template<typename TClass>
using method_t = void (TClass::*)();

template<typename TClass, method_t<TClass> func>
struct caller{
	friend void call(){
		TClass obj;
		(obj.*func)();
	}
};

void call();
template struct caller<sample_class, &sample_class::private_method>;

int main(){
	call();
	return 0;
}
