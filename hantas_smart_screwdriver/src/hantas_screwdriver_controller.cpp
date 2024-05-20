/** ******************************************************
	* @file		hantas_screwdriver_controller.cpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <iostream>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "hantas_screwdriver_controller.hpp"
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
int rc;
modbus_t *hantas;
modbus_t *deltaDRV;
uint16_t robot_cmd_data;
uint16_t MonitoringStatus;
struct_MonitoringRealtimeData param_RealtimeData;

/* Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
int connect_hantas(void);
int connect_deltaDRV(void);
int send_hantas_start(void);
int check_hantas_motion(void);
/* Function End */



/* ---------------------------------------------------------*/
/* ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ Program ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ ---------------------------*/
/* ---------------------------------------------------------*/
/* Program Begin */

/** * @brief  Program entry point.
	* @param argc(int) Number of input parameters
 	* @param argv(int) input parameters
 	* @return (int) Program Error.
**	**/
int main(int argc, char **argv)
{
	long count = 1;
	bool hantas_ok = false;

	if(connect_hantas()==0)
		std::cout << "create and connect hastas smart screwdeiver SUCCESS!" << std::endl;
	else
		std::cout << TC_ERROR << "create and connect hastas smart screwdeiver FAIL!" << TC_RESET << std::endl;

	if(connect_deltaDRV()==0)
		std::cout << "create and connect deltaDRV robot SUCCESS!" << std::endl;
	else
		std::cout << TC_ERROR << "create and connect deltaDRV robot FAIL!" << TC_RESET << std::endl;

	while(1)
	{
		rc = modbus_read_registers(deltaDRV,robot_cmd_adr,1,&robot_cmd_data);
		printf("%li, %i, new robot_cmd_data is %i\n",count,rc,robot_cmd_data);
		if( (robot_cmd_data==robot_cmd_lock_screw) || (robot_cmd_data==robot_cmd_take_out_screw) )
		{
			send_hantas_start();
			while(!hantas_ok)
			{
				modbus_write_register(deltaDRV,robot_cmd_adr,robot_cmd_data);
				check_hantas_motion();

				if(MonitoringStatus==2)
				{
					modbus_write_register(deltaDRV,robot_cmd_adr,static_cast<uint16_t>(robot_cmd_ERR));
					hantas_ok = true;
					std::cout << TC_ERROR << "    !!!!FasteningNotOK TorqueNotUp!!!!" << TC_RESET << std::endl;
				}
				
				if(MonitoringStatus==1)
					if(param_RealtimeData.Speed==0)
						if(param_RealtimeData.TorqueUp==1)
							if(param_RealtimeData.FasteningOK==1)
				{
					modbus_write_register(deltaDRV,robot_cmd_adr,static_cast<uint16_t>(robot_cmd_finish));
					hantas_ok = true;
					std::cout << "    !!!!FasteningOK TorqueUp!!!!" << std::endl;
				}
				usleep(1000);
				std::cout << TC_CLOSE << std::endl;
			} 
			hantas_ok = false;
			sleep(1);
		}
		else
			std::cout << "robot_cmd_data not take_out or lock " << std::endl;
		
		usleep(1000*500);
		count++;
		std::cout << TC_CLOSE << std::endl;
	}
	/* main quit */
	return 0;
}


int connect_hantas(void)
{
	hantas = modbus_new_tcp(hantas_screwdriver_ip, hantas_screwdriver_port);
	if (hantas == NULL)
	{
		fprintf(stderr, "Unable to allocate libmodbus context\n");
		return -1;
	}
	rc = modbus_set_slave(hantas, hantas_screwdriver_slaveID);
	if (rc == -1)
	{
		fprintf(stderr, "Invalid slave ID\n");
		modbus_free(hantas);
		return -1;
	}
	if (modbus_connect(hantas) == -1)
	{
		fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
		modbus_free(hantas);
		return -1;
	}
	return 0;
}
int connect_deltaDRV(void)
{
	deltaDRV = modbus_new_tcp(deltaDRV_ip, deltaDRV_port);
	if (deltaDRV == NULL)
	{
		fprintf(stderr, "Unable to allocate libmodbus context\n");
		return -1;
	}
	rc = modbus_set_slave(deltaDRV, deltaDRV_slaveID);
	if (rc == -1)
	{
		fprintf(stderr, "Invalid slave ID\n");
		modbus_free(deltaDRV);
		return -1;
	}
	if (modbus_connect(deltaDRV) == -1)
	{
		fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
		modbus_free(deltaDRV);
		return -1;
	}
	return 0;
}

int send_hantas_start(void)
{
	rc = modbus_write_register(hantas,RemoteControl_Forward_Loosening_adr,Forward);
	printf("%i, set RemoteControl F/L to %i\n",rc, Forward);
	rc = modbus_write_register(hantas,RemoteControl_PresetChange_adr,robot_cmd_data);
	printf("%i, set Preset to %i\n",rc, robot_cmd_data);
	rc = modbus_write_register(hantas,RemoteControl_Start_adr,1);
	printf("%i, screwdriver start\n",rc);
	return rc;
}

int check_hantas_motion(void)
{
	rc = modbus_read_input_registers(hantas,Monitoring_Status_adr,1,&MonitoringStatus);
	printf("%i, MonitoringStatus= %i\n",rc, MonitoringStatus);
	rc = modbus_read_input_registers(hantas,realtime_CurrentPreset_adr,1,&param_RealtimeData.CurrentPreset);
	printf("%i, RealtimeData.CurrentPreset= %i\n",rc, param_RealtimeData.CurrentPreset);
	rc = modbus_read_input_registers(hantas,realtime_Speed_adr,1,&param_RealtimeData.Speed);
	printf("%i, param_RealtimeData.Speed= %i\n",rc, param_RealtimeData.Speed);
	rc = modbus_read_input_registers(hantas,realtime_Forward_Loosening_adr,1,&param_RealtimeData.Forward_Loosening);
	printf("%i, param_RealtimeData.Forward_Loosening= %i\n",rc, MonitoringStatus);
	rc = modbus_read_input_registers(hantas,realtime_MotorRUN_adr,1,&param_RealtimeData.MotorRUN);
	printf("%i, param_RealtimeData.MotorRUN= %i\n",rc, MonitoringStatus);
	rc = modbus_read_input_registers(hantas,realtime_TorqueUp_adr,1,&param_RealtimeData.TorqueUp);
	printf("%i, param_RealtimeData.TorqueUp= %i\n",rc, MonitoringStatus);
	rc = modbus_read_input_registers(hantas,realtime_FasteningOK_adr,1,&param_RealtimeData.FasteningOK);
	printf("%i, param_RealtimeData.FasteningOK= %i\n",rc, MonitoringStatus);
	printf("-----------------------------------------------------------\n\n");
	return rc;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF hantas_screwdriver_controller.cpp ***** */
