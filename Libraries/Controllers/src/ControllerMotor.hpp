#ifndef CONTROLLER_MOTOR_HPP
#define CONTROLLER_MOTOR_HPP

#include <Arduino.h>
#include "Controller.hpp"
#include "ActuatorMotor.hpp"

class ControllerMotor : public Controller {
	public:
		enum e_drive_action {
		    FORWARD,
		    BACKWARD,
		    HALT,
		    SLOWHALT
		};
		enum e_side {
			LEFT,
			RIGHT,
			FRONT,
			BACK
		};
		enum e_corner {
			FRONT_LEFT,
			FRONT_RIGHT,
			BACK_LEFT,
			BACK_RIGHT
		};
		static const uint8_t ALL = 255;
		struct t_motor_pins {
			const uint8_t pin_pwm;
			const uint8_t pin_a;
			const uint8_t pin_b;
		};
	public:
	    ControllerMotor(const uint8_t motor_count, const t_motor_pins pins[], const uint8_t acceleration_coef);
	    ControllerMotor();
	    ~ControllerMotor();
		void SetParameters(const uint8_t motor_count, const t_motor_pins pins[], const uint8_t acceleration_coef);
		bool Init();
	    bool Update();
	
	    bool IsReady();
	    bool IsMoving();
	
	    bool IsAccelerating();
	    bool IsDecelerating();

		void SetAccelerationCoef(const uint8_t acceleration_coef);
		uint8_t GetAccelerationCoef();
	
	    uint8_t GetThrottle(const uint8_t motor_index);
	    void SetThrottle(const uint8_t motor_index, const uint8_t throttle);
	
	    void SetAction(const uint8_t motor_index, const e_drive_action action, const uint8_t throttle);
	    void SetAction(const uint8_t motor_index, const e_drive_action action);
	private:
	    enum e_motorstate {
	        ACCELERATING,
	        DECELERATING,
	        READY
	    };
		class Motor {
			public:
				ActuatorMotor _actuators_motor;
				e_motorstate _motorstate;
				e_drive_action _action;
				uint8_t _current_throttle;
				uint8_t _starting_throttle;
				uint8_t _desired_throttle;
				
				unsigned long _acceleration_start_time;
				uint8_t _acceleration_start_throttle;
				void Clear();
				void SetParameters(const t_motor_pins &pins);
		};
		uint8_t _motor_count;
		Motor *_motors = NULL;
	    uint8_t _acceleration_coef;
	private:
	    bool IsAtDesiredState(const uint8_t motor_index);
	
	    void UpdateAcceleration(const uint8_t motor_index, const int8_t acceleration);
	    void UpdateMotorActuator(const uint8_t motor_index);
	    void UpdateMotor(const uint8_t motor_index);
	
	    e_motorstate GetMotorstate(const uint8_t motor_index, const uint8_t throttle);
	
	    void SetActionParameters(const uint8_t motor_index, const e_drive_action action, const uint8_t throttle);
	    uint8_t NormalizeThrottle(int16_t throttle);
};

#endif
