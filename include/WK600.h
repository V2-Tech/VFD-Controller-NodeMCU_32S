#pragma once
#include <Arduino.h>
#include <HardwareSerial.h>
#include <ModbusMaster.h>

#define COMM_DEBUG
//#define CONVERSION_DEBUG

//INDIRIZZI MODBUS WK600
#define SETPOINT_ADDR 0x1000 //%*100
#define COMMANDS_ADDR 0x2000 
#define STATUS_ADDR 0x3000
#define MONITOR_SETSPEED_ADDR 0x7001 //Hz*100
#define MONITOR_INVOLTAGE_ADDR 0x7002 //V*10
#define MONITOR_OUTVOLTAGE_ADDR 0x7003 //V
#define MONITOR_OUTCURRENT_ADDR 0x7004 //A*100
#define MONITOR_OUTPOWER_ADDR 0x7005 //W
#define MONITOR_ACTSPEED_ADDR 0x703C //%*100
#define MONITOR_SETPOINT 0x701C //%*100
#define MONITOR_STATUS_ADDR 0x703D // Serve testarlo
#define MONITOR_FAULTCODE_ADDR 0x703E //NON RAGGIUNGIBILE Guardare manuale. Enumeratore decodificatrore?

enum VFDCommand : uint16_t
{
    //COMANDI DRIVE WK600
    COMMAND_FORW = 0x0001,
    COMMAND_REV = 0x0002,
    COMMAND_FREE_STOP = 0x0005,
    COMMAND_STOP = 0x0006,
    COMMAND_RESET = 0x0007
};

enum VFDStatus : uint16_t
{
    //STATO DRIVE WK600
    STATUS_ERROR = 0xFFFF,
    STATUS_RUN_FORW = 0x0001,
    STATUS_RUN_REV = 0x0002,
    STATUS_STOP = 0x0003
};

typedef struct
{
    uint16_t RPMmax;
    uint16_t In; //Corrente nominale [A]
    uint16_t Vn; // Tensione nominale [V]
    uint16_t Freq; // Frequenza massima di lavoro [Hz]
} MotorParam;

class WK600
{
    public:
        WK600();
        void begin(ModbusMaster &CommMaster);
        void ConnectionCheck();
        void setSpeed(uint16_t speed /*%*/);
        void run_forw();
        void run_rev();
        void stop();
        void free_stop();
        void reset();
        int32_t getActSetpoint();
        int32_t getActSpeed();
        int32_t getActVin();
        int32_t getActVout();
        uint16_t getActOutCurrent();
        uint16_t getActOutPower();
        int32_t getFaultCode();
        VFDStatus getStatus();
        int32_t PercentToRPM(int32_t speedPercent, MotorParam motorParameter);
        int32_t RPMToPercent(int32_t speedRPM, MotorParam motorParameter);
        int32_t HZToPercent(int32_t vfdHz, MotorParam motorParameter);
        int32_t HZToRPM(int32_t vfdHz, MotorParam motorParameter);
        bool _ConnectionOK;
    private:
        ModbusMaster* _CommMaster;
};