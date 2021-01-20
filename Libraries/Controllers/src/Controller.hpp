#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Controller {
	public:
		Controller();
		virtual ~Controller();
		virtual bool Init();
		virtual bool Update();
	private:
};

#endif
