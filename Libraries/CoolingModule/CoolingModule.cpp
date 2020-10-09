#include "CoolingModule.hpp"

CoolingModule::CoolingModule() : _current_state(false)
{

}

CoolingModule::~CoolingModule()
{

}

void	CoolingModule::switch_state(bool new_state)
{
	_current_state = new_state;
}
