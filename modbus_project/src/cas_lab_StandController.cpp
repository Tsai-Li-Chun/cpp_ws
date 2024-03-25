/** ******************************************************
	* @file		cas_lab_StandController.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "cas_lab_StandController.hpp"
/* User Includes End */

/* namespace ------------------------------------------------*/
/* namespace Begin */
/* namespace End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Typedef --------------------------------------------------*/
/* Typedef Begin */
/* Typedef End */


/* Class --------------------------------------------------*/
/* Class Begin */
/* Class End */


/* Variables ------------------------------------------------*/
/* Variables Begin */
/* Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */



/* ---------------------------------------------------------*/
/* ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ Program ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ ---------------------------*/
/* ---------------------------------------------------------*/
/* Program Begin */

/** * @brief constructor
	* @param none
 	* @return none
**	**/
cas_lab_StandController::cas_lab_StandController():
	deltaDRV_ctl(DRV_modbus_IP, DRV_modbus_port, DRV_modbus_slave),
	adam5000_ctl(adam5000_modbus_IP, adam5000_modbus_port,adam5000_modbus_slave)
{
	std::cout << "[cas_lab_StandController] create Succress!" << TC_RESET << std::endl;
}
/** * @brief destructor
	* @param none
 	* @return none
**	**/
cas_lab_StandController::~cas_lab_StandController()
{
	std::cout << "[cas_lab_StandController] memory release!" << std::endl;
}


int cas_lab_StandController::read_deltaDRV_total(void)
{
	read_deltaDRV_cmd(robot_adr::regulate, &robot_info_regulate_kg);
	read_deltaDRV_cmd(robot_adr::kinetrol, &robot_info_kinetrol);
	read_deltaDRV_cmd(robot_adr::brake, &robot_info_brake);
	read_deltaDRV_cmd(robot_adr::gripper, &robot_info_gripper);
	read_deltaDRV_cmd(robot_adr::toolATC, &robot_info_toolATC);
	read_deltaDRV_cmd(robot_adr::fixture, &robot_info_fixture);
	return 0;
}
int cas_lab_StandController::read_deltaDRV_cmd(robot_adr adr, uint16_t* data)
{
	rc = deltaDRV_ctl.read_deltaDRV_DataBuffer(static_cast<int>(adr),1,data);
	return rc;
}
int cas_lab_StandController::set_deltaDRV_total(void)
{
	set_deltaDRV_cmd(robot_adr::item_state, robot_info_item);
	// set_deltaDRV_cmd(robot_adr::toolATCcheck, robot_info_toolATC_check);
	// set_deltaDRV_cmd(robot_adr::rs1, robot_info_RS1);
	// set_deltaDRV_cmd(robot_adr::rs2, robot_info_RS2);
	// set_deltaDRV_cmd(robot_adr::rs3, robot_info_RS3);
	// set_deltaDRV_cmd(robot_adr::rs4, robot_info_RS4);
	// set_deltaDRV_cmd(robot_adr::kinetrol, robot_info_kinetrol);
	// set_deltaDRV_cmd(robot_adr::brake, robot_info_brake);
	// set_deltaDRV_cmd(robot_adr::gripper, robot_info_gripper);
	// set_deltaDRV_cmd(robot_adr::toolATC, robot_info_toolATC);
	// set_deltaDRV_cmd(robot_adr::fixture, robot_info_fixture);
	// set_deltaDRV_cmd(robot_adr::action_cmd, static_cast<uint16_t>(robot_action_invalid));
	return 0;
}
int cas_lab_StandController::set_deltaDRV_cmd(robot_adr adr, uint16_t data)
{
	rc = deltaDRV_ctl.write_deltaDRV_DataBuffer(static_cast<int>(adr),data);
	return rc;
}
int cas_lab_StandController::read_adam5000_total(void)
{
	read_adam5000_cmd(stand_adr_in::noitem, &armM5_info_noitem);
	read_adam5000_cmd(stand_adr_in::lowitem, &armM5_info_lowitem);
	read_adam5000_cmd(stand_adr_in::highitem, &armM5_info_highitem);
	// read_adam5000_cmd(stand_adr_in::ATCcheck, &armM5_info_toolATC_check);
	// read_adam5000_cmd(stand_adr_in::rs1, &armM5_info_RS1);
	// read_adam5000_cmd(stand_adr_in::rs2, &armM5_info_RS2);
	// read_adam5000_cmd(stand_adr_in::rs3, &armM5_info_RS3);
	// read_adam5000_cmd(stand_adr_in::rs4, &armM5_info_RS4);
	return 0;
}
int cas_lab_StandController::read_adam5000_cmd(stand_adr_in ch, uint8_t* data)
{
	rc = adam5000_ctl.adam5000_readDI(static_cast<adam5000_DI>(ch));
	*data = adam5000_ctl.get_DI_status(static_cast<adam5000_DI>(ch));
	return rc;
}
int cas_lab_StandController::set_adam5000_total(void)
{
	set_adam5000_cmd(stand_adr_out::regulate, armM5_info_regulate);
	set_adam5000_cmd(stand_adr_out::kinetrol_up, armM5_info_kinetrolUP);
	set_adam5000_cmd(stand_adr_out::kinetrol_down, armM5_info_kinetrolDOWN);
	set_adam5000_cmd(stand_adr_out::brake, armM5_info_brake);
	set_adam5000_cmd(stand_adr_out::gripper_open, armM5_info_gripperOPEN);
	set_adam5000_cmd(stand_adr_out::gripper_close, armM5_info_gripperCLOSE);
	set_adam5000_cmd(stand_adr_out::security, armM5_info_security);
	set_adam5000_cmd(stand_adr_out::value1_lock, armM5_info_value1_lock);
	set_adam5000_cmd(stand_adr_out::value1_unlock, armM5_info_value1_unlock);
	set_adam5000_cmd(stand_adr_out::value2_lock, armM5_info_value2_lock);
	set_adam5000_cmd(stand_adr_out::value2_unlock, armM5_info_value2_unlock);
	set_adam5000_cmd(stand_adr_out::value3_lock, armM5_info_value3_lock);
	set_adam5000_cmd(stand_adr_out::value3_unlock, armM5_info_value3_unlock);
	set_adam5000_cmd(stand_adr_out::value4_lock, armM5_info_value4_lock);
	set_adam5000_cmd(stand_adr_out::value4_unlock, armM5_info_value4_unlock);
	return 0;
}
int cas_lab_StandController::set_adam5000_cmd(stand_adr_out ch, uint8_t data)
{
	rc = adam5000_ctl.adam5000_setDO(static_cast<adam5000_DO>(ch),data);
	return rc;
}
int cas_lab_StandController::set_adam5000_cmd(stand_adr_out ch, uint16_t data)
{
	rc = adam5000_ctl.adam5000_setAO(static_cast<adam5000_AO>(ch),data);
	return rc;
}

bool cas_lab_StandController::check_robot_cmd(void)
{
	rc = deltaDRV_ctl.read_deltaDRV_DataBuffer(static_cast<int>(robot_adr::action_cmd), 1, &robot_cmd);
	std::cout << "rc = " << rc << " , robot_cmd = " << robot_cmd << std::endl;
	if( (rc==1) && (robot_cmd==robot_action_valid) )
		return true;
	else
		return false;
}
void cas_lab_StandController::check_action(void)
{
	read_deltaDRV_total();
	/* check brake */
	if( robot_info_brake_old != robot_info_brake )
	{
		std::cout << "robot_info_brake is change" << std::endl;
		std::cout << "    robot_info_brake     = " << robot_info_brake << std::endl;
		std::cout << "    robot_info_brake_old = " << robot_info_brake_old << std::endl;
		robot_info_brake_old = robot_info_brake;
		action_brake = true;
	}
	/* check fixture */
	if( robot_info_fixture_old != robot_info_fixture )
	{
		std::cout << "robot_info_fixture is change" << std::endl;
		std::cout << "    robot_info_fixture     = " << robot_info_fixture << std::endl;
		std::cout << "    robot_info_fixture_old = " << robot_info_fixture_old << std::endl;
		robot_info_fixture_old = robot_info_fixture;
		action_fixture = true;
	}
	/* check kinetrol */
	if( robot_info_kinetrol_old != robot_info_kinetrol )
	{
		std::cout << "robot_info_kinetrol is change" << std::endl;
		std::cout << "    robot_info_kinetrol     = " << robot_info_kinetrol << std::endl;
		std::cout << "    robot_info_kinetrol_old = " << robot_info_kinetrol_old << std::endl;
		robot_info_kinetrol_old = robot_info_kinetrol;
		action_kinetrol = true;
	}
	/* check toolATC  */
	if( robot_info_toolATC_old != robot_info_toolATC )
	{
		std::cout << "robot_info_toolATC is change" << std::endl;
		std::cout << "    robot_info_toolATC     = " << robot_info_toolATC << std::endl;
		std::cout << "    robot_info_toolATC_old = " << robot_info_toolATC_old << std::endl;
		robot_info_toolATC_old = robot_info_toolATC;
		action_toolATC = true;
	}
	/* check regulate  */
	if( robot_info_regulate_kg_old != robot_info_regulate_kg )
	{
		std::cout << "robot_info_regulate_kg is change" << std::endl;
		std::cout << "    robot_info_regulate_kg     = " << robot_info_regulate_kg << std::endl;
		std::cout << "    robot_info_regulate_kg_old = " << robot_info_regulate_kg_old << std::endl;
		robot_info_regulate_kg_old = robot_info_regulate_kg;
		action_regulate = true;
	}
}
void cas_lab_StandController::action_stand(void)
{
	/* action brake */
	if( action_brake )
	{
		std::cout << "action_brake working, ";
		if( robot_info_brake == static_cast<uint16_t>(armM5_brake::lock) )
			std::cout << "3ARMs M5 brake LOCK..." << std::endl;
		else if( robot_info_brake == static_cast<uint16_t>(armM5_brake::release) )
			std::cout << "3ARMs M5 brake RELEASE..." << std::endl;
		armM5_info_brake = static_cast<uint8_t>(arm_M5_pin_valid);
		set_adam5000_cmd(stand_adr_out::brake, armM5_info_brake);
		delay_1ms(time_blank_pin);
		armM5_info_brake = static_cast<uint8_t>(arm_M5_pin_invalid);
		set_adam5000_cmd(stand_adr_out::brake, armM5_info_brake);
		action_brake = false;
		std::cout << "action_brake worked." << std::endl;
	}
	/* action regulate  */
	if( action_regulate )
	{
		std::cout << "action_regulate working ..." << std::endl;
		regulate_kg2bar = regulate_kg2bar_a + regulate_kg2bar_b*robot_info_regulate_kg;
		armM5_info_regulate_float = regulate_kg2bar * regulate_bar2bin;
		if(armM5_info_regulate_float<0) armM5_info_regulate_float=0;
		if(armM5_info_regulate_float>2048)armM5_info_regulate_float=2048;
		armM5_info_regulate = static_cast<uint16_t>(armM5_info_regulate_float);
		// std::cout << "    target kg = " << robot_info_regulate_kg << std::endl;
		// std::cout << "    target bar= " << regulate_kg2bar << std::endl;
		// std::cout << "    target fff= " << armM5_info_regulate_float << std::endl;
		// std::cout << "    target bin= " << armM5_info_regulate << std::endl;
		rc = set_adam5000_cmd(stand_adr_out::regulate, armM5_info_regulate);
		action_regulate = false;
		std::cout << "action_regulate worked" << std::endl;
	}
	/* action kinetrol */
	if( action_kinetrol )
	{
		if( robot_info_kinetrol == static_cast<uint16_t>(armM5_kinetrol::up) )
		{
			std::cout << "action_kinetrol up working ..." << std::endl;
			armM5_info_security = static_cast<uint8_t>(arm_M5_pin_invalid);
			armM5_info_kinetrolDOWN = static_cast<uint8_t>(arm_M5_pin_invalid);
			rc = set_adam5000_cmd(stand_adr_out::security, armM5_info_security);
			rc = set_adam5000_cmd(stand_adr_out::kinetrol_down, armM5_info_kinetrolDOWN);
			delay_1ms(time_blank_pin);
			armM5_info_security = static_cast<uint8_t>(arm_M5_pin_valid);
			armM5_info_kinetrolUP = static_cast<uint8_t>(arm_M5_pin_valid);
			rc = set_adam5000_cmd(stand_adr_out::security, armM5_info_security);
			rc = set_adam5000_cmd(stand_adr_out::kinetrol_up, armM5_info_kinetrolUP);
		}
		else if( robot_info_kinetrol == static_cast<uint16_t>(armM5_kinetrol::down) )
		{
			std::cout << "action_kinetrol down working ..." << std::endl;
			armM5_info_security = static_cast<uint8_t>(arm_M5_pin_invalid);
			armM5_info_kinetrolUP = static_cast<uint8_t>(arm_M5_pin_invalid);
			rc = set_adam5000_cmd(stand_adr_out::security, armM5_info_security);
			rc = set_adam5000_cmd(stand_adr_out::kinetrol_up, armM5_info_kinetrolUP);
			delay_1ms(time_blank_pin);
			armM5_info_security = static_cast<uint8_t>(arm_M5_pin_valid);
			armM5_info_kinetrolDOWN = static_cast<uint8_t>(arm_M5_pin_valid);
			rc = set_adam5000_cmd(stand_adr_out::security, armM5_info_security);
			rc = set_adam5000_cmd(stand_adr_out::kinetrol_down, armM5_info_kinetrolDOWN);
		}
		action_kinetrol = false;
		std::cout << "action_kinetrol worked." << std::endl;
	}
	/* action fixture */
	if( action_fixture )
	{
		if( robot_info_fixture == static_cast<uint16_t>(armM5_fixture_state::open) )
		{
			std::cout << "action_fixture open working ..." << std::endl;
			armM5_info_value2_lock = static_cast<uint8_t>(arm_M5_pin_invalid);
			armM5_info_value3_lock = static_cast<uint8_t>(arm_M5_pin_invalid);
			rc = set_adam5000_cmd(stand_adr_out::value2_lock, armM5_info_value2_lock);
			rc = set_adam5000_cmd(stand_adr_out::value3_lock, armM5_info_value3_lock);
			delay_1ms(time_blank_pin);
			armM5_info_value3_unlock = static_cast<uint8_t>(arm_M5_pin_valid);
			rc = set_adam5000_cmd(stand_adr_out::value3_unlock, armM5_info_value3_unlock);
			delay_1ms(time_blank_action);
			armM5_info_value2_unlock = static_cast<uint8_t>(arm_M5_pin_valid);
			rc = set_adam5000_cmd(stand_adr_out::value2_unlock, armM5_info_value2_unlock);
		}
		else if( robot_info_fixture == static_cast<uint16_t>(armM5_fixture_state::close) )
		{
			std::cout << "action_fixture close working ..." << std::endl;
			armM5_info_value2_unlock = static_cast<uint8_t>(arm_M5_pin_invalid);
			armM5_info_value3_unlock = static_cast<uint8_t>(arm_M5_pin_invalid);
			rc = set_adam5000_cmd(stand_adr_out::value2_unlock, armM5_info_value2_unlock);
			rc = set_adam5000_cmd(stand_adr_out::value3_unlock, armM5_info_value3_unlock);
			delay_1ms(time_blank_pin);
			armM5_info_value3_lock = static_cast<uint8_t>(arm_M5_pin_valid);
			rc = set_adam5000_cmd(stand_adr_out::value3_lock, armM5_info_value3_lock);
			delay_1ms(time_blank_action);
			armM5_info_value2_lock = static_cast<uint8_t>(arm_M5_pin_valid);
			rc = set_adam5000_cmd(stand_adr_out::value2_lock, armM5_info_value2_lock);
		}
		action_fixture = false;
		std::cout << "action_fixture worked." << std::endl;
	}
	/* action toolATC */
	if( action_toolATC )
	{
		if( robot_info_toolATC == static_cast<uint16_t>(armM5_toolATC_state::lock) )
		{
			std::cout << "action_toolATC lock working ..." << std::endl;
			armM5_info_value1_unlock = static_cast<uint8_t>(arm_M5_pin_invalid);
			rc = set_adam5000_cmd(stand_adr_out::value1_unlock, armM5_info_value1_unlock);
			delay_1ms(time_blank_pin);
			armM5_info_value1_lock = static_cast<uint8_t>(arm_M5_pin_valid);
			rc = set_adam5000_cmd(stand_adr_out::value1_lock, armM5_info_value1_lock);
		}
		else if( robot_info_toolATC == static_cast<uint16_t>(armM5_toolATC_state::release) )
		{
			std::cout << "action_toolATC release working ..." << std::endl;
			armM5_info_value2_lock = static_cast<uint8_t>(arm_M5_pin_invalid);
			armM5_info_value2_unlock = static_cast<uint8_t>(arm_M5_pin_invalid);
			armM5_info_value3_lock = static_cast<uint8_t>(arm_M5_pin_invalid);
			armM5_info_value3_unlock = static_cast<uint8_t>(arm_M5_pin_invalid);
			rc = set_adam5000_cmd(stand_adr_out::value2_lock, armM5_info_value2_lock);
			rc = set_adam5000_cmd(stand_adr_out::value2_unlock, armM5_info_value2_unlock);
			rc = set_adam5000_cmd(stand_adr_out::value3_lock, armM5_info_value3_lock);
			rc = set_adam5000_cmd(stand_adr_out::value3_unlock, armM5_info_value3_unlock);
			armM5_info_value1_lock = static_cast<uint8_t>(arm_M5_pin_invalid);
			rc = set_adam5000_cmd(stand_adr_out::value1_lock, armM5_info_value1_lock);
			delay_1ms(time_blank_pin);
			armM5_info_value1_unlock = static_cast<uint8_t>(arm_M5_pin_valid);
			rc = set_adam5000_cmd(stand_adr_out::value1_unlock, armM5_info_value1_unlock);
		}
		action_toolATC = false;
		std::cout << "action_toolATC worked." << std::endl;
	}
	rc = set_deltaDRV_cmd(robot_adr::action_cmd, static_cast<uint16_t>(robot_action_invalid));
	std::cout << "rc= " << rc << " ,robot command address clean." << std::endl;
}

void cas_lab_StandController::adaminfo2robotinfo(void)
{
	/* set robot_info_item */
	if( armM5_info_noitem == static_cast<uint8_t>(arm_M5_pin_valid) )
		robot_info_item = static_cast<uint16_t>(armM5_item_state::no_item);
	else if( armM5_info_lowitem == static_cast<uint8_t>(arm_M5_pin_valid) )
		robot_info_item = static_cast<uint16_t>(armM5_item_state::low_item);
	else if( armM5_info_highitem == static_cast<uint8_t>(arm_M5_pin_valid) )
		robot_info_item = static_cast<uint16_t>(armM5_item_state::high_item);
	else
		robot_info_item = static_cast<uint16_t>(armM5_item_state::invalid_item);
	std::cout << "adaminfo2robotinfo : robot_info_item = " << robot_info_item << std::endl;
	// /* set robot_info_toolATC_check */
	// 	robot_info_toolATC_check = static_cast<uint16_t>(armM5_info_toolATC_check);
	// /* set rs1-4 */
	// robot_info_RS1 = static_cast<uint16_t>(armM5_info_RS1);
	// robot_info_RS1 = static_cast<uint16_t>(armM5_info_RS2);
	// robot_info_RS1 = static_cast<uint16_t>(armM5_info_RS3);
	// robot_info_RS1 = static_cast<uint16_t>(armM5_info_RS4);
	// std::cout << "adaminfo2robotinfo finish." << std::endl;
}

/** * @brief delay function
	* @param none
 	* @return stand_state, stand system state
**	**/
void cas_lab_StandController::run(void)
{
	if(check_robot_cmd())
	{
		std::cout << "checked robot send new action cmd" << std::endl;
		check_action();
		action_stand();
		// read_adam5000_total();
		// adaminfo2robotinfo();
		// set_deltaDRV_total();
	}
	else
		std::cout << "checked robot not cmd" << std::endl;

	std::cout << "---------------------------------------" << std::endl << std::endl;
	delay_1ms(500);
	std::cout << TC_CLOSE << std::endl;
}


/** * @brief cas lab stand system initialization
	* @param none
 	* @return none
**	**/
void cas_lab_StandController::init(void)
{
	std::cout << "wait robot to_stand_init() " << std::flush;
	delay_1ms(1000);
	do{
		deltaDRV_ctl.read_deltaDRV_DataBuffer(static_cast<int>(robot_adr::action_cmd), 1, &robot_cmd);
		if(robot_cmd==robot_action_init) break;
		else std::cout << "." << std::flush;
		delay_1ms(500);
	}while(1);
	std::cout << std::endl << "robot to_stand_init() finish." << std::endl;
	

	/* adam5000 information initialization */
	action_regulate = false;
	action_kinetrol = false;
	action_brake = false;
	action_toolATC = false;
	action_fixture = false;
	action_gripper = false;
	armM5_info_regulate = 1;
	armM5_info_kinetrolUP = arm_M5_pin_valid;
	armM5_info_kinetrolDOWN = arm_M5_pin_invalid;
	armM5_info_brake = arm_M5_pin_invalid;
	armM5_info_security = arm_M5_pin_invalid;
	armM5_info_gripperOPEN = arm_M5_pin_valid;
	armM5_info_gripperCLOSE = arm_M5_pin_invalid;
	armM5_info_value1_lock = arm_M5_pin_invalid;
	armM5_info_value1_unlock = arm_M5_pin_valid;
	armM5_info_value2_lock = arm_M5_pin_invalid;
	armM5_info_value2_unlock = arm_M5_pin_valid;
	armM5_info_value3_lock = arm_M5_pin_invalid;
	armM5_info_value3_unlock = arm_M5_pin_valid;
	armM5_info_value4_lock = arm_M5_pin_invalid;
	armM5_info_value4_unlock = arm_M5_pin_valid;
	/* deltaDRV control-BOX modbus handshake area data initialization  */
	robot_info_kinetrol_old = 0;
	robot_info_brake_old = 0;
	robot_info_gripper_old = 0;
	robot_info_toolATC_old = 0;
	robot_info_fixture_old = 0;
	robot_info_regulate_kg_old=0;
	/* action init */
	check_action();
	action_stand();
	// read_adam5000_total();
	// adaminfo2robotinfo();
	// set_deltaDRV_total();
	std::cout << "stand init() finish." << std::endl;
	std::cout << "----------------------------------------------------" << std::endl << std::endl;
}

/** * @brief delay function
	* @param int time, delay time, unit 1ms
 	* @return none
**	**/
void cas_lab_StandController::delay_1ms(int time)
{
	delay_count = 0;
	gettimeofday(&tv, NULL);
	delay_time_us_old = ((tv.tv_sec*1000000)+tv.tv_usec);
	delay_count_old = delay_time_us_old;
	while(1)
	{
		gettimeofday(&tv, NULL);
		if( delay_count>6000000 )
		{
			// rc = set_adam5000_cmd(stand_adr_out::security, armM5_info_security);
			rc = set_deltaDRV_cmd(robot_adr::de_timeout_cmd, static_cast<uint16_t>(robot_action_valid));
			if( rc != 1 )
				std::cout << "set_deltaDRV_cmd de_timeout_cmd error!" << std::endl;
			delay_count = 0;
		}

		delay_time_us = ((tv.tv_sec*1000000)+tv.tv_usec);
		if( (delay_time_us-delay_time_us_old) > (time*1000) )
			break;
		delay_count++;
	}
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF cas_lab_StandController.cpp ***** */
