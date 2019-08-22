#pragma once

#include <tuple>
#include <string>
#include <memory>

namespace ibl {
	// Some interfaces to share
	class ISomeUsefulInterface {
	public:
		virtual ~ISomeUsefulInterface() = default;
		virtual void Do() = 0;
	};
	using ISomeUsefulInterfacePtr = std::shared_ptr<ISomeUsefulInterface>;

	class MyUsefulImplementation : public ISomeUsefulInterface{
	public:
		void Do() override;
	};

	// Le logger
	class ISuperLogger {
	public:
		virtual ~ISuperLogger() = default;
		virtual void Log( std::string ) = 0;
	};
	using ISuperLoggerPtr = std::shared_ptr<ISuperLogger>;

	class MyLogger : public ISuperLogger {
	public:
		void Log( std::string value ) override;
	};

	// Google what is IOC container if any questions appear
	class CIOCContainer {
	public:
		using impls = std::tuple<ISuperLoggerPtr, ISomeUsefulInterfacePtr>;
		impls Resolve() const;
	};
}
