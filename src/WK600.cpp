#include <WK600.h>

WK600::WK600()
{

}

void WK600::begin(ModbusMaster &CommMaster)
{
    _CommMaster = &CommMaster;
}

void WK600::ConnectionCheck()
{
    uint8_t Return = _CommMaster->readHoldingRegisters(MONITOR_ACTSPEED_ADDR,1);
    if (Return==_CommMaster->ku8MBSuccess){
        _ConnectionOK = true;
    }
    else{
        _ConnectionOK = false;
    } 
}

void WK600::setSpeed(uint16_t speed /*%*/)
{
    uint8_t Return = _CommMaster->writeSingleRegister(SETPOINT_ADDR, speed*100);
    if (Return==_CommMaster->ku8MBSuccess){
        #ifdef COMM_DEBUG
            Serial.printf("\nsetpoint inviato: %u", speed*100);
        #endif
        _CommMaster->clearTransmitBuffer();
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore invio del setpoint: %u",Return);
            _CommMaster->clearTransmitBuffer();
        #endif
    }

}

void WK600::run_forw()
{
    uint8_t Return = _CommMaster->writeSingleRegister(COMMANDS_ADDR, VFDCommand::COMMAND_FORW);
    if (Return==_CommMaster->ku8MBSuccess){
        #ifdef COMM_DEBUG
            Serial.printf("\nComando di run forward inviato: %x", VFDCommand::COMMAND_FORW);
        #endif
        _CommMaster->clearTransmitBuffer();
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore invio comando di run forward: %u",Return);
        #endif
        _CommMaster->clearTransmitBuffer();
    }
}

void WK600::run_rev()
{
    uint8_t Return = _CommMaster->writeSingleRegister(COMMANDS_ADDR, VFDCommand::COMMAND_REV);
    if (Return==_CommMaster->ku8MBSuccess){
        #ifdef COMM_DEBUG
            Serial.printf("\nComando di run reverse inviato: %u", VFDCommand::COMMAND_REV);
        #endif
        _CommMaster->clearTransmitBuffer();
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore invio comando di run reverse: %x",Return);
            _CommMaster->clearTransmitBuffer();
        #endif
    }
}
void WK600::stop()
{
    uint8_t Return = _CommMaster->writeSingleRegister(COMMANDS_ADDR, VFDCommand::COMMAND_STOP);
    if (Return==_CommMaster->ku8MBSuccess){
        #ifdef COMM_DEBUG
            Serial.printf("\nComando di stop inviato: %x", VFDCommand::COMMAND_STOP);
        #endif
        _CommMaster->clearTransmitBuffer();
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore invio comando di run reverse: %u",Return);
            _CommMaster->clearTransmitBuffer();
        #endif
    }
}

void WK600::free_stop()
{
    uint8_t Return = _CommMaster->writeSingleRegister(COMMANDS_ADDR, VFDCommand::COMMAND_FREE_STOP);
    if (Return==_CommMaster->ku8MBSuccess){
        #ifdef COMM_DEBUG
            Serial.printf("\nComando di free stop inviato: %x", VFDCommand::COMMAND_FREE_STOP);
        #endif
        _CommMaster->clearTransmitBuffer();
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore invio comando di run reverse: %u",Return);
            _CommMaster->clearTransmitBuffer();
        #endif
    }
}

void WK600::reset()
{
    uint8_t Return = _CommMaster->writeSingleRegister(COMMANDS_ADDR, VFDCommand::COMMAND_RESET);
    if (Return==_CommMaster->ku8MBSuccess){
        #ifdef COMM_DEBUG
            Serial.printf("\nComando di reset inviato: %x", VFDCommand::COMMAND_RESET);
        #endif
        _CommMaster->clearTransmitBuffer();
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore invio comando di run reverse: %u",Return);
            _CommMaster->clearTransmitBuffer();
        #endif
    }    
}

int32_t WK600::getActSetpoint()
{
    uint8_t Return = _CommMaster->readHoldingRegisters(MONITOR_SETSPEED_ADDR,1);
    if (Return==_CommMaster->ku8MBSuccess){
        int32_t tempVal = _CommMaster->getResponseBuffer(0)/100;
        #ifdef COMM_DEBUG
            Serial.printf("\nLettura setpoint avvenuta: %u", tempVal);
        #endif
        _CommMaster->clearResponseBuffer();
        return tempVal;
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore lettura setpoint: %u",Return);
            _CommMaster->clearResponseBuffer();
        #endif
        return 0;
    } 
}

int32_t WK600::getActSpeed()
{
    uint8_t Return = _CommMaster->readHoldingRegisters(MONITOR_ACTSPEED_ADDR,1);
    if (Return==_CommMaster->ku8MBSuccess){
        int32_t tempVal = abs(_CommMaster->getResponseBuffer(0));
        #ifdef COMM_DEBUG
            Serial.printf("\nLettura velocita attuale avvenuta: HIGH %d", tempVal);
        #endif
        _CommMaster->clearResponseBuffer();
        return tempVal/100;
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore lettura velocita attuale: %d",Return);
            _CommMaster->clearResponseBuffer();
        #endif
        return 0;
    } 
}

int32_t WK600::getActVin()
{
    uint8_t Return = _CommMaster->readHoldingRegisters(MONITOR_INVOLTAGE_ADDR,1);
    if (Return==_CommMaster->ku8MBSuccess){
        int32_t tempVal = _CommMaster->getResponseBuffer(0)/10;
        #ifdef COMM_DEBUG
            Serial.printf("\nLettura tensione di alimentazione avvenuta: %u", tempVal);
        #endif
        _CommMaster->clearResponseBuffer();
        return tempVal;
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore lettura tensione ingresso Vin: %u",Return);
            _CommMaster->clearResponseBuffer();
        #endif
        return 0;
    } 
}

int32_t WK600::getActVout()
{
    uint8_t Return = _CommMaster->readHoldingRegisters(MONITOR_OUTVOLTAGE_ADDR,1);
    if (Return==_CommMaster->ku8MBSuccess){
        int32_t tempVal = _CommMaster->getResponseBuffer(0);
        #ifdef COMM_DEBUG
            Serial.printf("\nLettura tensione di uscita avvenuta: %u", tempVal);
        #endif
        _CommMaster->clearResponseBuffer();
        return tempVal;
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore lettura tensione uscita Vout: %u",Return);
            _CommMaster->clearResponseBuffer();
        #endif
        return 0;
    } 
}

uint16_t WK600::getActOutCurrent()
{
    uint8_t Return = _CommMaster->readHoldingRegisters(MONITOR_OUTCURRENT_ADDR,1);
    if (Return==_CommMaster->ku8MBSuccess){
        uint16_t tempVal = _CommMaster->getResponseBuffer(0)/100;
        #ifdef COMM_DEBUG
            Serial.printf("\nLettura corrente di uscita avvenuta: %u", tempVal);
        #endif
        _CommMaster->clearResponseBuffer();
        return tempVal;
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore corrente tensione uscita Iout: %u",Return);
            _CommMaster->clearResponseBuffer();
        #endif
        return 0;
    } 
}

uint16_t WK600::getActOutPower()
{
    uint8_t Return = _CommMaster->readHoldingRegisters(MONITOR_OUTPOWER_ADDR,1);
    if (Return==_CommMaster->ku8MBSuccess){
        uint16_t tempVal = _CommMaster->getResponseBuffer(0);
        #ifdef COMM_DEBUG
            Serial.printf("\nLettura potenza erogata avvenuta: %u", tempVal);
        #endif
        _CommMaster->clearResponseBuffer();
        return tempVal;
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore potenza erogata Pout: %u",Return);
            _CommMaster->clearResponseBuffer();
        #endif
        return 0;
    } 
}

int32_t WK600::getFaultCode()
{
    uint8_t Return = _CommMaster->readHoldingRegisters(MONITOR_FAULTCODE_ADDR,1);
    if (Return==_CommMaster->ku8MBSuccess){
        int32_t tempVal = _CommMaster->getResponseBuffer(0);
        #ifdef COMM_DEBUG
            Serial.printf("\nLettura codice errore avvenuta: %u", tempVal);
        #endif
        _CommMaster->clearResponseBuffer();
        return tempVal;
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore lettura codice errore: %u",Return);
            _CommMaster->clearResponseBuffer();
        #endif
        return 0;
    } 
}

VFDStatus WK600::getStatus()
{
    VFDStatus tempStatus;
    uint8_t Return = _CommMaster->readHoldingRegisters(STATUS_ADDR,1);
    if (Return==_CommMaster->ku8MBSuccess){
        int32_t tempVal = _CommMaster->getResponseBuffer(0);
        #ifdef COMM_DEBUG
            Serial.printf("\nLettura stato drive avvenuta: %u", tempVal);
        #endif
        if(tempVal==VFDStatus::STATUS_RUN_FORW)
        {
            tempStatus = VFDStatus::STATUS_RUN_FORW;
        }
        else if (tempVal==VFDStatus::STATUS_RUN_REV)
        {
            tempStatus = VFDStatus::STATUS_RUN_REV;
        }
        else if (tempVal==VFDStatus::STATUS_STOP)
        {
            tempStatus = VFDStatus::STATUS_STOP;
        }
        else
        {
            tempStatus = VFDStatus::STATUS_ERROR;
        }
        _CommMaster->clearResponseBuffer();
        return tempStatus;
    }
    else{
        #ifdef COMM_DEBUG
            Serial.printf("\nErrore lettura stato drive: %u",Return);
        #endif
        _CommMaster->clearResponseBuffer();
        return VFDStatus::STATUS_ERROR;
    } 
}

int32_t WK600::PercentToRPM(int32_t speedPercent, MotorParam motorParameter)
{
    float y, m;
    int32_t tempPercent = abs(speedPercent);
    #ifdef CONVERSION_DEBUG
        Serial.printf("\nConversione %->RPM. Valore assoluto: %d",tempPercent);
    #endif
    #ifdef CONVERSION_DEBUG
        Serial.printf("\nConversione %->RPM. Parametro motore RPM: %u", motorParameter.RPMmax);
    #endif
    m = (float)motorParameter.RPMmax/100;
    #ifdef CONVERSION_DEBUG
        Serial.printf("\nConversione %->RPM. Coefficiente: %f",m);
    #endif
    y = (float)m*tempPercent;
    #ifdef CONVERSION_DEBUG
        Serial.printf("\nConversione %->RPM. Risultato: %f",y);
    #endif
    return (int32_t)y;
}

int32_t WK600::RPMToPercent(int32_t speedRPM, MotorParam motorParameter)
{
    float y, m;
    int32_t tempRPM = abs(speedRPM);
    #ifdef CONVERSION_DEBUG
        Serial.printf("\nConversione RPM->%. Valore assoluto: %d",tempRPM);
    #endif
    #ifdef CONVERSION_DEBUG
        Serial.printf("\nConversione RPM->%. Parametro motore RPM: %u", motorParameter.RPMmax);
    #endif
    m = (float)speedRPM/(float)motorParameter.RPMmax;
    #ifdef CONVERSION_DEBUG
        Serial.printf("\nConversione RPM->%. Coefficiente: %f",m);
    #endif
    y = (float)m*100;
    #ifdef CONVERSION_DEBUG
        Serial.printf("\nConversione RPM->%. Risultato: %f",y);
    #endif
    return (int32_t)y;
}

int32_t  WK600::HZToPercent(int32_t vfdHz, MotorParam motorParameter)
{
    float y, m;
    int32_t tempHz = abs(vfdHz);
    m = 100/motorParameter.Freq;
    y = m*tempHz;
    return y;
}

int32_t  WK600::HZToRPM(int32_t vfdHz, MotorParam motorParameter)
{
    float y, m;
    int32_t tempHz = abs(vfdHz);
    m = motorParameter.RPMmax/motorParameter.Freq;
    y = m*tempHz;
    return y;
}