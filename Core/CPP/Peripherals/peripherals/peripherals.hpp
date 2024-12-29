/*
 * peripherals.hpp
 *
 *  Created on: Oct 16, 2024
 *      Author: Ayoub
 */

#ifndef CPP_PERIPHERALS_PERIPHERALS_PERIPHERALS_HPP_
#define CPP_PERIPHERALS_PERIPHERALS_PERIPHERALS_HPP_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
class Peripheral {
public:
	virtual void Init() = 0;
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual ~Peripheral() {
	}
};
#endif /* __cplusplus */

#endif /* CPP_PERIPHERALS_PERIPHERALS_HPP_ */
