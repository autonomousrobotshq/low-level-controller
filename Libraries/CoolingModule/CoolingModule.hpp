#ifndef COOLINGMODULE_HPP
# define COOLINGMODULE_HPP
#include <Arduino.h>

class CoolingModule {
	private:
		bool _current_state;

	public:
		CoolingModule();
		~CoolingModule();

		void	switch_state(bool new_state);
}

#endif