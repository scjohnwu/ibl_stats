#include <iostream>

#include "IOCContainer.h"

namespace ibl {
	void MyUsefulImplementation::Do() {
		std::cout << "Ho-Ho" << std::endl;
	}

	void MyLogger::Log( std::string value ) {
		std::cout << value << std::endl;
	}

	CIOCContainer::impls CIOCContainer::Resolve() const {
		// In the real container localized singletons have to be provided, not some
		// randomly initialized classes
		impls result( new MyLogger(), new MyUsefulImplementation() );
		return result;
	}
	
}