#ifndef MOTORCONTROLLER_HPP
#define MOTORCONTROLLER_HPP

# define MOTORCONTROLLER_MAX_PWM 180

// throttle should be a number between 0 and 100 indicating percentage of applied force
class MotorController {
	public:
		void	forward(const unsigned int throttle);
		void	reverse(const unsigned int throttle);
		void	halt();
		MotorController(const unsigned pinPWM,
						const unsigned pinA,
						const unsigned pinB);
		~MotorController();
	private:
		const unsigned _pinPWM;
		const unsigned _pinA;
		const unsigned _pinB;
};

#endif
