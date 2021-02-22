#include "Global.h"

Global GVL;
RemoteDebug Debug;
ModbusMaster node;
Button EncBtn(InEncoderBUT);

Global::Global()
{
    MotorParam motorParameter = {2850, 5, 400, 50};
    MenuEntitys.push_back({"RPM DES: ", {4,0,0}}); //{Stringa, x-pos, y-pos, pag}
    MenuEntitys.push_back({"ACT RPM: ", {4,1,0}});
    MenuEntitys.push_back({"ACT PWR: ", {0,2,0}});
    MenuEntitys.push_back({"STATUS:", {0,3,0}});
    MenuEntitys.push_back({"ERR:", {12,3,0}});
}

void Global::begin()
{
    debugW("DEVICE CONNECTED");
    vfd.run_forw();
    vfd.setSpeed(50);   
}