#include "printinformation.h"
#include "wchar.h"

PrintInformation::PrintInformation(QObject *parent) : QObject(parent)
{

}

/*
 * 打印标签
 */
void PrintInformation::print(Print_t *print)
{
    const char *port_name = "/dev/usb/lp0";
    void *h = 0;
    int nPageWidth = 48 * 8;
    int nPageHeight = 25 * 8;
    int height = 1;
    QString barCode = "";

    h = CP_Port_OpenUsb(port_name, 0);
    CP_Pos_SetMultiByteMode(h);
    CP_Pos_SetMultiByteEncoding(h, CP_MultiByteEncoding_GBK);
    CP_Label_PageBegin(h, 0, 0, nPageWidth, nPageHeight, CP_Label_Rotation_0);
    CP_Label_DrawBox(h, 0, 0, nPageWidth, nPageHeight, 1, CP_Label_Color_Black);
    CP_Label_DrawTextInGBK(h, 10, 10+height, 24, 0, L"工件号:");
    CP_Label_DrawTextInBytes(h, 100, 10+height, 24, 0, print->workpiece_number.toStdString().c_str(),print->workpiece_number.length());

    CP_Label_DrawTextInGBK(h, 10, 40+height, 24, 0, L"工序 :气密性检查");
    CP_Label_DrawTextInGBK(h, 10, 70+height, 24, 0, L"工号 :");
    CP_Label_DrawTextInBytes(h, 100, 70+height, 24, 0, print->worker_number.toStdString().c_str(),print->worker_number.length());

    CP_Label_DrawTextInGBK(h, 10, 100+height, 24, 0, L"设备号:");
    CP_Label_DrawTextInBytes(h, 100, 100+height, 24, 0, print->device_number.toStdString().c_str(),print->device_number.length());

    CP_Label_DrawTextInGBK(h, 10, 130+height, 24, 0, L"结果:");
    CP_Label_DrawTextInBytes(h, 100, 130+height, 24, 0, print->result.toStdString().c_str(),print->result.length());

    CP_Label_DrawTextInGBK(h, 10, 160+height, 24, 0, L"时间:");
    CP_Label_DrawTextInBytes(h, 100, 160+height, 24, 0, print->timer.toStdString().c_str(),print->timer.length());
    barCode = print->workpiece_number+print->worker_number+print->device_number+print->result+print->timer;
    CP_Label_DrawQRCode(h, 240, 10+height, 4, CP_QRCodeECC_L, 4, CP_Label_Rotation_0, barCode.toStdString().c_str());
    CP_Label_PagePrint(h, 1);
    CP_Port_Close(h);
}
