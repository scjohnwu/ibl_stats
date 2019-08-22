#include "Component.h"

#include <iostream>

int main()
{
	ibl::CStatsCollector collector;
	auto component = ibl::AStatsComponentPtr( new ibl::CMyComponent() );
	collector.AddComponent( component );

	ibl::CIOCContainer container;
	auto gathered_stats = collector.Gather( &container );

	std::cout << gathered_stats << std::endl;

	return 0;
}
