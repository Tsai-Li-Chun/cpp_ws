/** ******************************************************
	* @file		hantas_DataStruct_Define.h
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __hantas_DataStruct_Define_H__
#define __hantas_DataStruct_Define_H__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include <stdint.h>
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */

#define default_preset_quantity 15

/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */

/* define preset#1-default_preset_quantity fastening format */
struct struct_preset_fastening
{
	uint16_t TCAM_ACTM;;
	uint16_t Torque;
	uint16_t TorqueMinMax_per;
	uint16_t TargetAngle_deg;
	uint16_t MinAngle_deg;
	uint16_t MaxAngle_deg;
	uint16_t SnugTorque;
	uint16_t Speed_rpm;
	uint16_t FreeFastenigAngle_deg;
	uint16_t FreeFastenigSpeed_rpm;
	uint16_t SoftStart;
	uint16_t SeatingPoint_per;
	uint16_t TorqueRisingRate_ms;
	uint16_t RampUpSpeed_rpm;
	uint16_t TorqueCompensation_per;
}param_preset_fasteningm[default_preset_quantity];
/* define general Control Setting format */
struct struct_control_setting
{
	uint16_t ScrewCount;
	uint16_t DecimalPoint;
	uint16_t DriverModel;
	uint16_t TorqueUnit;
	uint16_t ResetFactorySetting;
	uint16_t AutoSpeedTorqueSetting;
	uint16_t MotorAcc;
	uint16_t TorqueHoldingTime;
	uint16_t LooseningSpeed;
	uint16_t RunTimeLimitForward_sec;
	uint16_t RunTimeLimit_Reverse_sec;
	uint16_t MotorStallTimeLimit_sec;
	uint16_t ErrorDisplayResetTime;
	uint16_t ScrewType;
	uint16_t JudgeFasteningMinTurns;
	uint16_t FasteningStopError; 
	uint16_t TorqueCompensationMaster_per;
	uint16_t ReverseLock;
	uint16_t InitialPreset;
	uint16_t AutoDataOutput;
	uint16_t AutoLock;
	uint16_t LightOnTime;
	uint16_t EventDataSelect;
	uint16_t PresetChangeByBarcode;
	uint16_t DriverLockAfterWifiDisconnect_sec;
	uint16_t SelectDisplayPresetNumber;
	uint16_t LooseningFasteningSwitchType;
	uint16_t SleepTime;
	uint16_t TriggerStartDelayTime;
	uint16_t LcdButtonLock;
}param_control_setting;
/* define network toolsetting format */
struct struct_network_toolsetting
{
	uint16_t TargetIP1;
	uint16_t TargetIP2;
	uint16_t TargetIP3;
	uint16_t TargetIP4;
	uint16_t TargetPort;
	uint16_t NetworkEnable;
	uint16_t StaticDHCP;
	uint16_t IPAddress1;
	uint16_t IPAddress2;
	uint16_t IPAddress3;
	uint16_t IPAddress4;
	uint16_t SubnetMask1;
	uint16_t SubnetMask2;
	uint16_t SubnetMask3;
	uint16_t SubnetMask4;
	uint16_t Gateway1;
	uint16_t Gateway2;
	uint16_t Gateway3;
	uint16_t Gateway4;
	uint16_t Port;
}param_network_toolsetting;
/* define network APsetting format */
struct struct_network_APsetting
{
	uint16_t SSID[32];
	uint16_t Password[32];
	uint16_t CountryType;
}param_network_APsetting;
/* define error code */
uint16_t param_error_code[8];
/* define Controller Model */
uint16_t ControllerModel;
/* define Advanced preset - FreeReverse */
struct struct_FreeReverse
{
	uint16_t Speed_rpm;
	uint16_t Angle_turn;
};
/* define Advanced preset - ThreadTapping */
struct struct_ThreadTapping
{
	uint16_t MinTorque;
	uint16_t MaxTorque;
	uint16_t Speed_rpm;
	uint16_t FinishTorque;
	uint16_t AngleStartFromThreadTapping;
};
/* define Advanced preset - EngagingTorqueDetection */
struct struct_EngagingTorqueDetection
{
	uint16_t Speed_rpm;
	uint16_t Torque_per;
	uint16_t AngleLimit_turn;
	uint16_t TimeLimit_sec;
	uint16_t AngleStartSromEngaging;
};
/* define Advanced preset - AngelAfterTorqueUp */
struct struct_AngelAfterTorqueUp
{
	uint16_t Speed_rpm;
	uint16_t Angle_deg;
	uint16_t Direction;
};
struct struct_AdvancedPreset
{
	struct_FreeReverse FreeReverse;
	struct_ThreadTapping ThreadTapping;
	struct_EngagingTorqueDetection EngagingTorqueDetection;
	struct_AngelAfterTorqueUp AngelAfterTorqueUp;
}param_AdvancedPreset[default_preset_quantity];

/* define Monitoring Realtime Data */
struct struct_MonitoringRealtimeData
{
	uint16_t Speed;
	uint16_t CurrentPreset;
	uint16_t TorqueUp;
	uint16_t FasteningOK;
	uint16_t Ready;
	uint16_t MotorRUN;
	uint16_t AlarmNO;
	uint16_t Forward_Loosening;
	uint16_t ScrewCountValue;
	uint16_t MotorTemperature;
};

/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__hantas_DataStruct_Define_H__ */

/* ***** END OF hantas_DataStruct_Define.H ***** */
