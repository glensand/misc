#include <iostream>

class sample_class{
	void private_method(){
		std::cout << "Private method called" << std::endl;
	}
};

template<typename TClass>
using method_t = void (TClass::*)();

#define DECLARE_METHOD_ZERO_ARG(CLASS, METHOD)  \
template<typename TClass, method_t<TClass> func> \
struct t##CLASS##METHOD{ \
	friend void call_##CLASS##_##METHOD(TClass& obj){ \
		(obj.*func)(); \
	} \
	friend void call_##CLASS##_##METHOD(const TClass& obj){ \
		(obj.*func)(); \
	} \
}; \
void call_##CLASS##_##METHOD(const CLASS&); \
void call_##CLASS##_##METHOD(CLASS&); \
template struct t##CLASS##METHOD<CLASS, & CLASS::METHOD>; \

DECLARE_METHOD_ZERO_ARG(sample_class, private_method)

int main(){
	sample_class obj;
	call_sample_class_private_method(obj);
	return 0;
}
