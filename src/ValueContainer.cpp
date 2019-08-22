#include <iterator>
#include <vector>

#include "ValueContainer.h"

namespace {
	std::vector<std::string> tokenize( std::string query ) {
		std::stringstream input_stream{ query };
		std::vector<std::string> result;
		for ( std::string buffer; std::getline( input_stream, buffer, '.' ); ) {
			result.push_back( buffer );
		}
		return result;
	}
}

namespace ibl {
	void CValueContainer::SetValue( std::string path, std::string value ) {
		auto tokens = tokenize( path );

		SNode* current = &m_Root;
		for ( auto& token : tokens ) {
			auto found = current->children.find( token );
			if ( found != std::end( current->children ) ) {
				current = &found->second;
			}
			else {
				if ( token == tokens.back() ) {
					current->values[token] = value;
				}
				else {
					current = &current->children[token];
				}
			}
		}
	}

	void CValueContainer::Insert( std::string path, const CValueContainer& container ) {
		auto tokens = tokenize( path );

		SNode* current = &m_Root;
		for ( auto& token : tokens ) {
			auto found = current->children.find( token );
			if ( found != std::end( current->children ) ) {
				current = &found->second;
			}
			else {
				if ( token == tokens.back() ) {
					current->children[token] = container.m_Root;
				}
			}
		}
	}

	std::tuple<bool, std::string> CValueContainer::Query( std::string query ) const {
		auto tokens = tokenize( query );

		const SNode* current = &m_Root;
		for ( auto& token : tokens ) {
			auto found = current->children.find( token );
			if ( found != std::end( current->children ) ) {
				current = &found->second;
			}
			else if ( token == tokens.back() 
					&& current->values.find( token ) != std::end( current->values ) ) {
				return std::make_tuple( true, current->values.at(token) );
			}
			else {
				return std::make_tuple( false, "" );
			}
		}

		return std::make_tuple( false, "" );
	}

	void CValueContainer::RecursivePrint( std::ostream& out, const SNode& node, unsigned int indent ) {
		for ( auto child : node.children ) {
			std::fill_n( std::ostream_iterator<std::string>( out ), indent, "    " );
			out << ">" << child.first << "\n";
			for ( auto value : child.second.values ) {
				std::fill_n( std::ostream_iterator<std::string>( out ), indent, "     " );
				out << value.first<< ": " << value.second << "\n";
			}
			RecursivePrint( out, child.second, indent + 1 );
		}
	}
}