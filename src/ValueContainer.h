#pragma once

#include<sstream>
#include<string>
#include<tuple>
#include<map>

namespace ibl {
	class CValueContainer {
		struct SNode {
			std::map<std::string, SNode> children;
			std::map<std::string, std::string> values;
		};
		SNode m_Root;
	public:
		void SetValue( std::string path, std::string value );
		std::tuple<bool, std::string> Query( std::string query ) const;
		void Insert( std::string path, const CValueContainer& container );

		static void RecursivePrint( std::ostream& out, const SNode& node, unsigned int indent );

		friend std::ostream& operator << ( std::ostream& out, const CValueContainer& container );
	};

	inline std::ostream& operator << ( std::ostream& out, const CValueContainer& container ) {
		out << "root\n";
		CValueContainer::RecursivePrint( out, container.m_Root, 1 );
		return out;
	}

	template<typename T>
	T get_value( const CValueContainer& container, std::string query ) {
		T result{};
		const auto&[is_valid, value] = container.Query( query );
		if ( !is_valid ) {
			return result;
		}
		else {
			std::stringstream stream{ value };
			stream >> result;
			return result;
		}
	}

	template<typename T>
	void set_value( CValueContainer& container, std::string path, const T& value ) {
		container.SetValue( path, ( std::stringstream{ "" } << value ).str() );
	}
}
