#include "Interface.hpp"

Interface::Interface(const unsigned long update_interval)
    : Timer(update_interval)
{
}

Interface::~Interface()
{
}

bool Interface::Init()
{
	return (true);
}

bool Interface::Update()
{
	return (true);
}
