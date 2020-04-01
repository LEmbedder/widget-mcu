#ifndef AUTOREPLYPRINT_H
#define AUTOREPLYPRINT_H

//AUTOREPLYPRINT_API
#ifdef _MSC_VER
  #ifdef AUTOREPLYPRINT_EXPORTS
    #ifndef AUTOREPLYPRINT_API
    #define AUTOREPLYPRINT_API __declspec(dllexport)
    #endif
  #else
    #ifndef AUTOREPLYPRINT_API
    #define AUTOREPLYPRINT_API __declspec(dllimport)
    #endif
  #endif
#else
  #ifndef AUTOREPLYPRINT_API
  #define AUTOREPLYPRINT_API
  #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum CP_ComDataBits { CP_ComDataBits_4 = 4, CP_ComDataBits_5 = 5, CP_ComDataBits_6 = 6, CP_ComDataBits_7 = 7, CP_ComDataBits_8 = 8 } CP_ComDataBits;

typedef enum CP_ComParity { CP_ComParity_NoParity, CP_ComParity_OddParity, CP_ComParity_EvenParity, CP_ComParity_MarkParity, CP_ComParity_SpaceParity } CP_ComParity;

typedef enum CP_ComStopBits { CP_ComStopBits_One, CP_ComStopBits_OnePointFive, CP_ComStopBits_Two } CP_ComStopBits;

typedef enum CP_ComFlowControl { CP_ComFlowControl_None, CP_ComFlowControl_XonXoff, CP_ComFlowControl_RtsCts, CP_ComFlowControl_DtrDsr } CP_ComFlowControl;

typedef enum CP_CharacterSet {
    CP_CharacterSet_USA = 0,
    CP_CharacterSet_FRANCE = 1,
    CP_CharacterSet_GERMANY = 2,
    CP_CharacterSet_UK = 3,
    CP_CharacterSet_DENMARK_I = 4,
    CP_CharacterSet_SWEDEN = 5,
    CP_CharacterSet_ITALY = 6,
    CP_CharacterSet_SPAIN_I = 7,
    CP_CharacterSet_JAPAN = 8,
    CP_CharacterSet_NORWAY = 9,
    CP_CharacterSet_DENMARK_II = 10,
    CP_CharacterSet_SPAIN_II = 11,
    CP_CharacterSet_LATIN = 12,
    CP_CharacterSet_KOREA = 13,
    CP_CharacterSet_SLOVENIA = 14,
    CP_CharacterSet_CHINA = 15
} CP_CharacterSet;

typedef enum CP_CharacterCodepage {
    CP_CharacterCodepage_CP437 = 0,
    CP_CharacterCodepage_KATAKANA = 1,
    CP_CharacterCodepage_CP850 = 2,
    CP_CharacterCodepage_CP860 = 3,
    CP_CharacterCodepage_CP863 = 4,
    CP_CharacterCodepage_CP865 = 5,
    CP_CharacterCodepage_WCP1251 = 6,
    CP_CharacterCodepage_CP866 = 7,
    CP_CharacterCodepage_MIK = 8,
    CP_CharacterCodepage_CP755 = 9,
    CP_CharacterCodepage_IRAN = 10,
    CP_CharacterCodepage_CP862 = 15,
    CP_CharacterCodepage_WCP1252 = 16,
    CP_CharacterCodepage_WCP1253 = 17,
    CP_CharacterCodepage_CP852 = 18,
    CP_CharacterCodepage_CP858 = 19,
    CP_CharacterCodepage_IRAN_II = 20,
    CP_CharacterCodepage_LATVIAN = 21,
    CP_CharacterCodepage_CP864 = 22,
    CP_CharacterCodepage_ISO_8859_1 = 23,
    CP_CharacterCodepage_CP737 = 24,
    CP_CharacterCodepage_WCP1257 = 25,
    CP_CharacterCodepage_THAI = 26,
    CP_CharacterCodepage_CP720 = 27,
    CP_CharacterCodepage_CP855 = 28,
    CP_CharacterCodepage_CP857 = 29,
    CP_CharacterCodepage_WCP1250 = 30,
    CP_CharacterCodepage_CP775 = 31,
    CP_CharacterCodepage_WCP1254 = 32,
    CP_CharacterCodepage_WCP1255 = 33,
    CP_CharacterCodepage_WCP1256 = 34,
    CP_CharacterCodepage_WCP1258 = 35,
    CP_CharacterCodepage_ISO_8859_2 = 36,
    CP_CharacterCodepage_ISO_8859_3 = 37,
    CP_CharacterCodepage_ISO_8859_4 = 38,
    CP_CharacterCodepage_ISO_8859_5 = 39,
    CP_CharacterCodepage_ISO_8859_6 = 40,
    CP_CharacterCodepage_ISO_8859_7 = 41,
    CP_CharacterCodepage_ISO_8859_8 = 42,
    CP_CharacterCodepage_ISO_8859_9 = 43,
    CP_CharacterCodepage_ISO_8859_15 = 44,
    CP_CharacterCodepage_THAI_2 = 45,
    CP_CharacterCodepage_CP856 = 46,
    CP_CharacterCodepage_CP874 = 47,
    CP_CharacterCodepage_TCVN3 = 48
} CP_CharacterCodepage;

typedef enum CP_MultiByteEncoding { CP_MultiByteEncoding_GBK = 0, CP_MultiByteEncoding_UTF8 = 1, CP_MultiByteEncoding_BIG5 = 3, CP_MultiByteEncoding_ShiftJIS = 4, CP_MultiByteEncoding_EUCKR = 5 } CP_MultiByteEncoding;

typedef enum CP_ImageBinarizationMethod { CP_ImageBinarizationMethod_Dithering, CP_ImageBinarizationMethod_Thresholding } CP_ImageBinarizationMethod;

typedef enum CP_ImageCompressionMethod { CP_ImageCompressionMethod_None, CP_ImageCompressionMethod_Level1, CP_ImageCompressionMethod_Level2 } CP_ImageCompressionMethod;

typedef enum CP_ImagePixelsFormat { 
    CP_ImagePixelsFormat_MONO = 1,
    CP_ImagePixelsFormat_MONOLSB = 2,
    CP_ImagePixelsFormat_GRAY8 = 3,
    CP_ImagePixelsFormat_BYTEORDERED_RGB24 = 4,
    CP_ImagePixelsFormat_BYTEORDERED_BGR24 = 5,
    CP_ImagePixelsFormat_BYTEORDERED_ARGB32 = 6,
    CP_ImagePixelsFormat_BYTEORDERED_RGBA32 = 7,
    CP_ImagePixelsFormat_BYTEORDERED_ABGR32 = 8,
    CP_ImagePixelsFormat_BYTEORDERED_BGRA32 = 9
} CP_ImagePixelsFormat;

typedef enum CP_QRCodeECC { CP_QRCodeECC_L = 1, CP_QRCodeECC_M = 2, CP_QRCodeECC_Q = 3, CP_QRCodeECC_H = 4 } CP_QRCodeECC;

typedef enum CP_Pos_Alignment { CP_Pos_Alignment_Left, CP_Pos_Alignment_HCenter, CP_Pos_Alignment_Right } CP_Pos_Alignment;

typedef enum CP_Pos_BarcodeType { 
    CP_Pos_BarcodeType_UPCA = 0x41,
    CP_Pos_BarcodeType_UPCE = 0x42,
    CP_Pos_BarcodeType_EAN13 = 0x43,
    CP_Pos_BarcodeType_EAN8 = 0x44,
    CP_Pos_BarcodeType_CODE39 = 0x45,
    CP_Pos_BarcodeType_ITF = 0x46,
    CP_Pos_BarcodeType_CODEBAR = 0x47,
    CP_Pos_BarcodeType_CODE93 = 0x48,
    CP_Pos_BarcodeType_CODE128 = 0x49
} CP_Pos_BarcodeType;

typedef enum CP_Pos_BarcodeTextPrintPosition { CP_Pos_BarcodeTextPrintPosition_None, CP_Pos_BarcodeTextPrintPosition_AboveBarcode, CP_Pos_BarcodeTextPrintPosition_BelowBarcode, CP_Pos_BarcodeTextPrintPosition_AboveAndBelowBarcode } CP_Pos_BarcodeTextPrintPosition;

typedef enum CP_Page_DrawDirection { CP_Page_DrawDirection_LeftToRight, CP_Page_DrawDirection_BottomToTop, CP_Page_DrawDirection_RightToLeft, CP_Page_DrawDirection_TopToBottom } CP_Page_DrawDirection;

#ifndef MarcoDefinitionCPPageDrawAlignment
#define MarcoDefinitionCPPageDrawAlignment
#define CP_Page_DrawAlignment_Left -1
#define CP_Page_DrawAlignment_HCenter -2
#define CP_Page_DrawAlignment_Right -3
#define CP_Page_DrawAlignment_Top -1
#define CP_Page_DrawAlignment_VCenter -2
#define CP_Page_DrawAlignment_Bottom -3
#endif

typedef enum CP_Label_BarcodeType { 
    CP_Label_BarcodeType_UPCA = 0,
    CP_Label_BarcodeType_UPCE = 1,
    CP_Label_BarcodeType_EAN13 = 2,
    CP_Label_BarcodeType_EAN8 = 3,
    CP_Label_BarcodeType_CODE39 = 4,
    CP_Label_BarcodeType_ITF = 5,
    CP_Label_BarcodeType_CODEBAR = 6,
    CP_Label_BarcodeType_CODE93 = 7,
    CP_Label_BarcodeType_CODE128 = 8,
    CP_Label_BarcodeType_CODE11 = 9,
    CP_Label_BarcodeType_MSI = 10,
    CP_Label_BarcodeType_128M = 11,
    CP_Label_BarcodeType_EAN128 = 12,
    CP_Label_BarcodeType_25C = 13,
    CP_Label_BarcodeType_39C = 14,
    CP_Label_BarcodeType_39 = 15,
    CP_Label_BarcodeType_EAN13PLUS2 = 16,
    CP_Label_BarcodeType_EAN13PLUS5 = 17,
    CP_Label_BarcodeType_EAN8PLUS2 = 18,
    CP_Label_BarcodeType_EAN8PLUS5 = 19,
    CP_Label_BarcodeType_POST = 20,
    CP_Label_BarcodeType_UPCAPLUS2 = 21,
    CP_Label_BarcodeType_UPCAPLUS5 = 22,
    CP_Label_BarcodeType_UPCEPLUS2 = 23,
    CP_Label_BarcodeType_UPCEPLUS5 = 24,
    CP_Label_BarcodeType_CPOST = 25,
    CP_Label_BarcodeType_MSIC = 26,
    CP_Label_BarcodeType_PLESSEY = 27,
    CP_Label_BarcodeType_ITF14 = 28,
    CP_Label_BarcodeType_EAN14 = 29
} CP_Label_BarcodeType;

typedef enum CP_Label_BarcodeTextPrintPosition { CP_Label_BarcodeTextPrintPosition_None, CP_Label_BarcodeTextPrintPosition_AboveBarcode, CP_Label_BarcodeTextPrintPosition_BelowBarcode, CP_Label_BarcodeTextPrintPosition_AboveAndBelowBarcode } CP_Label_BarcodeTextPrintPosition;

typedef enum CP_Label_Rotation { CP_Label_Rotation_0, CP_Label_Rotation_90, CP_Label_Rotation_180, CP_Label_Rotation_270 } CP_Label_Rotation;

typedef enum CP_Label_Color { CP_Label_Color_White, CP_Label_Color_Black } CP_Label_Color;

#ifndef MarcoDefinitionCPPrinterStatus
#define MarcoDefinitionCPPrinterStatus
#define CP_PRINTERSTATUS_ERROR_CUTTER(error_status) (error_status & 0x01)
#define CP_PRINTERSTATUS_ERROR_FLASH(error_status) (error_status & 0x02)
#define CP_PRINTERSTATUS_ERROR_NOPAPER(error_status) (error_status & 0x04)
#define CP_PRINTERSTATUS_ERROR_VOLTAGE(error_status) (error_status & 0x08)
#define CP_PRINTERSTATUS_ERROR_MARKER(error_status) (error_status & 0x10)
#define CP_PRINTERSTATUS_ERROR_ENGINE(error_status) (error_status & 0x20)
#define CP_PRINTERSTATUS_ERROR_OVERHEAT(error_status) (error_status & 0x40)
#define CP_PRINTERSTATUS_ERROR_COVERUP(error_status) (error_status & 0x80)
#define CP_PRINTERSTATUS_ERROR_MOTOR(error_status) (error_status & 0x100)
#define CP_PRINTERSTATUS_INFO_LABELPAPER(info_status) (info_status & 0x02)
#define CP_PRINTERSTATUS_INFO_LABELMODE(info_status) (info_status & 0x04)
#define CP_PRINTERSTATUS_INFO_HAVEDATA(info_status) (info_status & 0x08)
#define CP_PRINTERSTATUS_INFO_NOPAPERCANCELED(info_status) (info_status & 0x10)
#define CP_PRINTERSTATUS_INFO_PAPERNOFETCH(info_status) (info_status & 0x20)
#define CP_PRINTERSTATUS_INFO_PRINTIDLE(info_status) (info_status & 0x40)
#define CP_PRINTERSTATUS_INFO_RECVIDLE(info_status) (info_status & 0x80)
#endif

#ifndef MarcoDefinitionCPRTStatus
#define MarcoDefinitionCPRTStatus
#define CP_RTSTATUS_DRAWER_OPENED(status) (((status >> 0) & 0x04) == 0x00)
#define CP_RTSTATUS_OFFLINE(status) (((status >> 0) & 0x08) == 0x08)
#define CP_RTSTATUS_COVERUP(status) (((status >> 8) & 0x04) == 0x04)
#define CP_RTSTATUS_FEED_PRESSED(status) (((status >> 8) & 0x08) == 0x08)
#define CP_RTSTATUS_NOPAPER(status) (((status >> 8) & 0x20) == 0x20)
#define CP_RTSTATUS_ERROR_OCCURED(status) (((status >> 8) & 0x40) == 0x40)
#define CP_RTSTATUS_CUTTER_ERROR(status) (((status >> 16) & 0x08) == 0x08)
#define CP_RTSTATUS_UNRECOVERABLE_ERROR(status) (((status >> 16) & 0x20) == 0x20)
#define CP_RTSTATUS_DEGREE_OR_VOLTAGE_OVERRANGE(status) (((status >> 16) & 0x40) == 0x40)
#define CP_RTSTATUS_PAPER_NEAREND(status) (((status >> 24) & 0x0C) == 0x0C)
#define CP_RTSTATUS_PAPER_TAKEOUT(status) (((status >> 24) & 0x04) == 0x04)
#endif

#ifndef MarcoDefinitionCPLabelTextStyle
#define MarcoDefinitionCPLabelTextStyle
#define CP_LABEL_TEXT_STYLE_BOLD (1<<0)
#define CP_LABEL_TEXT_STYLE_UNDERLINE (1<<1)
#define CP_LABEL_TEXT_STYLE_HIGHLIGHT (1<<2)
#define CP_LABEL_TEXT_STYLE_STRIKETHROUGH (1<<3)
#define CP_LABEL_TEXT_STYLE_ROTATION_0 (0<<4)
#define CP_LABEL_TEXT_STYLE_ROTATION_90 (1<<4)
#define CP_LABEL_TEXT_STYLE_ROTATION_180 (2<<4)
#define CP_LABEL_TEXT_STYLE_ROTATION_270 (3<<4)
#define CP_LABEL_TEXT_STYLE_WIDTH_ENLARGEMENT(n) ((n)<<8)
#define CP_LABEL_TEXT_STYLE_HEIGHT_ENLARGEMENT(n) ((n)<<12)
#endif

typedef void (*CP_OnNetPrinterDiscovered)(const char *local_ip, const char *discovered_mac, const char *discovered_ip, const char *discovered_name, const void *private_data);

typedef void (*CP_OnBluetoothDeviceDiscovered)(const char *device_name, const char *device_address, const void *private_data);

typedef void (*CP_OnPortOpenedEvent)(void *handle, const char *name, void *private_data);

typedef void (*CP_OnPortOpenFailedEvent)(void *handle, const char *name, void *private_data);

typedef void (*CP_OnPortClosedEvent)(void *handle, void *private_data);

typedef void (*CP_OnPortWrittenEvent)(void *handle, const unsigned char *buffer, unsigned int count, void *private_data);

typedef void (*CP_OnPortReceivedEvent)(void *handle, const unsigned char *buffer, unsigned int count, void *private_data);

typedef void (*CP_OnPrinterStatusEvent)(void *handle, const long long printer_error_status, const long long printer_info_status, void *private_data);

typedef void (*CP_OnPrinterReceivedEvent)(void *handle, const unsigned int printer_received_byte_count, void *private_data);

typedef void (*CP_OnPrinterPrintedEvent)(void *handle, const unsigned int printer_printed_page_id, void *private_data);

AUTOREPLYPRINT_API const char *CP_Library_Version(void);

AUTOREPLYPRINT_API unsigned int CP_Port_EnumCom(char *pBuf, unsigned int cbBuf, unsigned int *pcbNeeded);

AUTOREPLYPRINT_API unsigned int CP_Port_EnumLpt(char *pBuf, unsigned int cbBuf, unsigned int *pcbNeeded);

AUTOREPLYPRINT_API unsigned int CP_Port_EnumUsb(char *pBuf, unsigned int cbBuf, unsigned int *pcbNeeded);

AUTOREPLYPRINT_API void CP_Port_EnumNetPrinter(unsigned int timeout, int *cancel, CP_OnNetPrinterDiscovered on_discovered, const void *private_data);

AUTOREPLYPRINT_API void CP_Port_EnumBtDevice(unsigned int timeout, int *cancel, CP_OnBluetoothDeviceDiscovered on_discovered, const void *private_data);

AUTOREPLYPRINT_API void CP_Port_EnumBleDevice(unsigned int timeout, int *cancel, CP_OnBluetoothDeviceDiscovered on_discovered, const void *private_data);

AUTOREPLYPRINT_API void *CP_Port_OpenCom(const char *name, unsigned int baudrate, CP_ComDataBits databits, CP_ComParity parity, CP_ComStopBits stopbits, CP_ComFlowControl flowcontrol, int autoreplymode);

AUTOREPLYPRINT_API void *CP_Port_OpenLpt(const char *name);

AUTOREPLYPRINT_API void *CP_Port_OpenUsb(const char *name, int autoreplymode);

AUTOREPLYPRINT_API void *CP_Port_OpenTcp(const char *local_ip, const char *dest_ip, unsigned short dest_port, unsigned int timeout, int autoreplymode);

AUTOREPLYPRINT_API void *CP_Port_OpenBtSpp(const char *address, int autoreplymode);

AUTOREPLYPRINT_API void *CP_Port_OpenBtBle(const char *address, int autoreplymode);

AUTOREPLYPRINT_API int CP_Port_Write(void *handle, const unsigned char *buffer, unsigned int count, unsigned int timeout);

AUTOREPLYPRINT_API int CP_Port_Read(void *handle, unsigned char *buffer, unsigned int count, unsigned int timeout);

AUTOREPLYPRINT_API int CP_Port_ReadUntilByte(void *handle, unsigned char *buffer, unsigned int count, unsigned int timeout, unsigned char breakByte);

AUTOREPLYPRINT_API int CP_Port_Available(void *handle);

AUTOREPLYPRINT_API int CP_Port_SkipAvailable(void *handle);

AUTOREPLYPRINT_API int CP_Port_IsConnectionValid(void *handle);

AUTOREPLYPRINT_API int CP_Port_IsOpened(void *handle);

AUTOREPLYPRINT_API int CP_Port_Close(void *handle);

AUTOREPLYPRINT_API int CP_Port_AddOnPortOpenedEvent(const CP_OnPortOpenedEvent event, void *private_data);

AUTOREPLYPRINT_API int CP_Port_AddOnPortOpenFailedEvent(const CP_OnPortOpenFailedEvent event, void *private_data);

AUTOREPLYPRINT_API int CP_Port_AddOnPortClosedEvent(const CP_OnPortClosedEvent event, void *private_data);

AUTOREPLYPRINT_API int CP_Port_AddOnPortWrittenEvent(const CP_OnPortWrittenEvent event, void *private_data);

AUTOREPLYPRINT_API int CP_Port_AddOnPortReceivedEvent(const CP_OnPortReceivedEvent event, void *private_data);

AUTOREPLYPRINT_API int CP_Port_RemoveOnPortOpenedEvent(const CP_OnPortOpenedEvent event);

AUTOREPLYPRINT_API int CP_Port_RemoveOnPortOpenFailedEvent(const CP_OnPortOpenFailedEvent event);

AUTOREPLYPRINT_API int CP_Port_RemoveOnPortClosedEvent(const CP_OnPortClosedEvent event);

AUTOREPLYPRINT_API int CP_Port_RemoveOnPortWrittenEvent(const CP_OnPortWrittenEvent event);

AUTOREPLYPRINT_API int CP_Port_RemoveOnPortReceivedEvent(const CP_OnPortReceivedEvent event);

AUTOREPLYPRINT_API int CP_Printer_AddOnPrinterStatusEvent(const CP_OnPrinterStatusEvent event, void *private_data);

AUTOREPLYPRINT_API int CP_Printer_AddOnPrinterReceivedEvent(const CP_OnPrinterReceivedEvent event, void *private_data);

AUTOREPLYPRINT_API int CP_Printer_AddOnPrinterPrintedEvent(const CP_OnPrinterPrintedEvent event, void *private_data);

AUTOREPLYPRINT_API int CP_Printer_RemoveOnPrinterStatusEvent(const CP_OnPrinterStatusEvent event);

AUTOREPLYPRINT_API int CP_Printer_RemoveOnPrinterReceivedEvent(const CP_OnPrinterReceivedEvent event);

AUTOREPLYPRINT_API int CP_Printer_RemoveOnPrinterPrintedEvent(const CP_OnPrinterPrintedEvent event);

AUTOREPLYPRINT_API int CP_Printer_GetPrinterResolutionInfo(void *handle, unsigned int *width_mm, unsigned int *height_mm, unsigned int *dots_per_mm);

AUTOREPLYPRINT_API int CP_Printer_GetPrinterFirmwareVersion(void *handle, char *pBuf, unsigned int cbBuf, unsigned int *pcbNeeded);

AUTOREPLYPRINT_API int CP_Printer_GetPrinterStatusInfo(void *handle, long long *printer_error_status, long long *printer_info_status, long long *timestamp_ms);

AUTOREPLYPRINT_API int CP_Printer_GetPrinterReceivedInfo(void *handle, unsigned int *printer_received_byte_count, long long *timestamp_ms);

AUTOREPLYPRINT_API int CP_Printer_GetPrinterPrintedInfo(void *handle, unsigned int *printer_printed_page_id, long long *timestamp_ms);

AUTOREPLYPRINT_API int CP_Printer_GetPrinterLabelPositionAdjustmentInfo(void *handle, double *label_print_position_adjustment, double *label_tear_position_adjustment, long long *timestamp_ms);

AUTOREPLYPRINT_API int CP_Printer_SetPrinterLabelPositionAdjustmentInfo(void *handle, double label_print_position_adjustment, double label_tear_position_adjustment);

AUTOREPLYPRINT_API int CP_Printer_ClearPrinterBuffer(void *handle);

AUTOREPLYPRINT_API int CP_Printer_ClearPrinterError(void *handle);

AUTOREPLYPRINT_API int CP_Pos_QueryRTStatus(void *handle, unsigned int timeout);

AUTOREPLYPRINT_API int CP_Pos_QueryPrintResult(void *handle, unsigned int nPageID, unsigned int timeout);

AUTOREPLYPRINT_API int CP_Pos_KickOutDrawer(void *handle, int nDrawerIndex, int nHighLevelTime, int nLowLevelTime);

AUTOREPLYPRINT_API int CP_Pos_Beep(void *handle, int nBeepCount, int nBeepMs);

AUTOREPLYPRINT_API int CP_Pos_FeedAndHalfCutPaper(void *handle);

AUTOREPLYPRINT_API int CP_Pos_FullCutPaper(void *handle);

AUTOREPLYPRINT_API int CP_Pos_HalfCutPaper(void *handle);

AUTOREPLYPRINT_API int CP_Pos_FeedLine(void *handle, int numLines);

AUTOREPLYPRINT_API int CP_Pos_FeedDot(void *handle, int numDots);

AUTOREPLYPRINT_API int CP_Pos_PrintSelfTestPage(void *handle);

AUTOREPLYPRINT_API int CP_Pos_PrintText(void *handle, const char *str);

AUTOREPLYPRINT_API int CP_Pos_PrintTextInUTF8(void *handle, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Pos_PrintTextInGBK(void *handle, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Pos_PrintTextInBIG5(void *handle, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Pos_PrintTextInShiftJIS(void *handle, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Pos_PrintTextInEUCKR(void *handle, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Pos_PrintTextInBytes(void *handle, const char *str, int len);

AUTOREPLYPRINT_API int CP_Pos_PrintBarcode(void *handle, CP_Pos_BarcodeType nBarcodeType, const char *str);

AUTOREPLYPRINT_API int CP_Pos_PrintQRCode(void *handle, int nVersion, CP_QRCodeECC nECCLevel, const char *str);

AUTOREPLYPRINT_API int CP_Pos_PrintQRCodeUseEpsonCmd(void *handle, int nQRCodeUnitWidth, CP_QRCodeECC nECCLevel, const char *str);

AUTOREPLYPRINT_API int CP_Pos_PrintDoubleQRCode(void *handle, int nQRCodeUnitWidth, int nQR1Position, int nQR1Version, CP_QRCodeECC nQR1ECCLevel, const char *strQR1, int nQR2Position, int nQR2Version, CP_QRCodeECC nQR2ECCLevel, const char *strQR2);

AUTOREPLYPRINT_API int CP_Pos_PrintPDF417BarcodeUseEpsonCmd(void *handle, int columnCount, int rowCount, int unitWidth, int rowHeight, int nECCLevel, int dataProcessingMode, const char *str);

AUTOREPLYPRINT_API int CP_Pos_PrintRasterImageFromFile(void *handle, int dstw, int dsth, const char *pszFile, CP_ImageBinarizationMethod binaryzation_method, CP_ImageCompressionMethod compress_method);

AUTOREPLYPRINT_API int CP_Pos_PrintRasterImageFromData(void *handle, int dstw, int dsth, const unsigned char *data, unsigned int data_size, CP_ImageBinarizationMethod binaryzation_method, CP_ImageCompressionMethod compress_method);

AUTOREPLYPRINT_API int CP_Pos_PrintRasterImageFromPixels(void *handle, const unsigned char *img_data, unsigned int img_datalen, int img_width, int img_height, int img_stride, CP_ImagePixelsFormat img_format, CP_ImageBinarizationMethod binaryzation_method, CP_ImageCompressionMethod compress_method);

AUTOREPLYPRINT_API int CP_Pos_PrintHorizontalLine(void *handle, int nLineStartPosition, int nLineEndPosition);

AUTOREPLYPRINT_API int CP_Pos_PrintHorizontalLineSpecifyThickness(void *handle, int nLineStartPosition, int nLineEndPosition, int nLineThickness);

AUTOREPLYPRINT_API int CP_Pos_PrintMultipleHorizontalLinesAtOneRow(void *handle, int nLineCount, int *pLineStartPosition, int *pLineEndPosition);

AUTOREPLYPRINT_API int CP_Pos_ResetPrinter(void *handle);

AUTOREPLYPRINT_API int CP_Pos_SetPrintSpeed(void *handle, int nSpeed);

AUTOREPLYPRINT_API int CP_Pos_SetPrintDensity(void *handle, int nDensity);

AUTOREPLYPRINT_API int CP_Pos_SetSingleByteMode(void *handle);

AUTOREPLYPRINT_API int CP_Pos_SetCharacterSet(void *handle, CP_CharacterSet nCharacterSet);

AUTOREPLYPRINT_API int CP_Pos_SetCharacterCodepage(void *handle, CP_CharacterCodepage nCharacterCodepage);

AUTOREPLYPRINT_API int CP_Pos_SetMultiByteMode(void *handle);

AUTOREPLYPRINT_API int CP_Pos_SetMultiByteEncoding(void *handle, CP_MultiByteEncoding nEncoding);

AUTOREPLYPRINT_API int CP_Pos_SetMovementUnit(void *handle, int nHorizontalMovementUnit, int nVerticalMovementUnit);

AUTOREPLYPRINT_API int CP_Pos_SetPrintAreaLeftMargin(void *handle, int nLeftMargin);

AUTOREPLYPRINT_API int CP_Pos_SetPrintAreaWidth(void *handle, int nWidth);

AUTOREPLYPRINT_API int CP_Pos_SetHorizontalAbsolutePrintPosition(void *handle, int nPosition);

AUTOREPLYPRINT_API int CP_Pos_SetHorizontalRelativePrintPosition(void *handle, int nPosition);

AUTOREPLYPRINT_API int CP_Pos_SetVerticalAbsolutePrintPosition(void *handle, int nPosition);

AUTOREPLYPRINT_API int CP_Pos_SetVerticalRelativePrintPosition(void *handle, int nPosition);

AUTOREPLYPRINT_API int CP_Pos_SetAlignment(void *handle, CP_Pos_Alignment nAlignment);

AUTOREPLYPRINT_API int CP_Pos_SetTextScale(void *handle, int nWidthScale, int nHeightScale);

AUTOREPLYPRINT_API int CP_Pos_SetAsciiTextFontType(void *handle, int nFontType);

AUTOREPLYPRINT_API int CP_Pos_SetTextBold(void *handle, int nBold);

AUTOREPLYPRINT_API int CP_Pos_SetTextUnderline(void *handle, int nUnderline);

AUTOREPLYPRINT_API int CP_Pos_SetTextUpsideDown(void *handle, int nUpsideDown);

AUTOREPLYPRINT_API int CP_Pos_SetTextWhiteOnBlack(void *handle, int nWhiteOnBlack);

AUTOREPLYPRINT_API int CP_Pos_SetTextRotate(void *handle, int nRotate);

AUTOREPLYPRINT_API int CP_Pos_SetTextLineHeight(void *handle, int nLineHeight);

AUTOREPLYPRINT_API int CP_Pos_SetAsciiTextCharRightSpacing(void *handle, int nSpacing);

AUTOREPLYPRINT_API int CP_Pos_SetKanjiTextCharSpacing(void *handle, int nLeftSpacing, int nRightSpacing);

AUTOREPLYPRINT_API int CP_Pos_SetBarcodeUnitWidth(void *handle, int nBarcodeUnitWidth);

AUTOREPLYPRINT_API int CP_Pos_SetBarcodeHeight(void *handle, int nBarcodeHeight);

AUTOREPLYPRINT_API int CP_Pos_SetBarcodeReadableTextFontType(void *handle, int nFontType);

AUTOREPLYPRINT_API int CP_Pos_SetBarcodeReadableTextPosition(void *handle, CP_Pos_BarcodeTextPrintPosition nTextPosition);

AUTOREPLYPRINT_API int CP_Page_SelectPageMode(void *handle);

AUTOREPLYPRINT_API int CP_Page_SelectPageModeEx(void *handle, int nHorizontalMovementUnit, int nVerticalMovementUnit, int x, int y, int width, int height);

AUTOREPLYPRINT_API int CP_Page_ExitPageMode(void *handle);

AUTOREPLYPRINT_API int CP_Page_PrintPage(void *handle);

AUTOREPLYPRINT_API int CP_Page_ClearPage(void *handle);

AUTOREPLYPRINT_API int CP_Page_SetPageArea(void *handle, int x, int y, int width, int height);

AUTOREPLYPRINT_API int CP_Page_SetPageDrawDirection(void *handle, CP_Page_DrawDirection nDirection);

AUTOREPLYPRINT_API int CP_Page_DrawRect(void *handle, int x, int y, int width, int height, int color);

AUTOREPLYPRINT_API int CP_Page_DrawBox(void *handle, int x, int y, int width, int height, int borderwidth, int bordercolor);

AUTOREPLYPRINT_API int CP_Page_DrawText(void *handle, int x, int y, const char *str);

AUTOREPLYPRINT_API int CP_Page_DrawTextInUTF8(void *handle, int x, int y, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Page_DrawTextInGBK(void *handle, int x, int y, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Page_DrawTextInBIG5(void *handle, int x, int y, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Page_DrawTextInShiftJIS(void *handle, int x, int y, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Page_DrawTextInEUCKR(void *handle, int x, int y, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Page_DrawBarcode(void *handle, int x, int y, CP_Pos_BarcodeType nBarcodeType, const char *str);

AUTOREPLYPRINT_API int CP_Page_DrawQRCode(void *handle, int x, int y, int nVersion, CP_QRCodeECC nECCLevel, const char *str);

AUTOREPLYPRINT_API int CP_Page_DrawRasterImageFromFile(void *handle, int x, int y, int dstw, int dsth, const char *pszFile, CP_ImageBinarizationMethod binaryzation_method);

AUTOREPLYPRINT_API int CP_Page_DrawRasterImageFromData(void *handle, int x, int y, int dstw, int dsth, const unsigned char *data, unsigned int data_size, CP_ImageBinarizationMethod binaryzation_method);

AUTOREPLYPRINT_API int CP_Page_DrawRasterImageFromPixels(void *handle, int x, int y, const unsigned char *img_data, unsigned int img_datalen, int img_width, int img_height, int img_stride, CP_ImagePixelsFormat img_format, CP_ImageBinarizationMethod binaryzation_method);

AUTOREPLYPRINT_API int CP_BlackMark_EnableBlackMarkMode(void *handle);

AUTOREPLYPRINT_API int CP_BlackMark_DisableBlackMarkMode(void *handle);

AUTOREPLYPRINT_API int CP_BlackMark_SetBlackMarkMaxFindLength(void *handle, int maxFindLength);

AUTOREPLYPRINT_API int CP_BlackMark_FindNextBlackMark(void *handle);

AUTOREPLYPRINT_API int CP_BlackMark_SetBlackMarkPaperPrintPosition(void *handle, int position);

AUTOREPLYPRINT_API int CP_BlackMark_SetBlackMarkPaperCutPosition(void *handle, int position);

AUTOREPLYPRINT_API int CP_BlackMark_FullCutBlackMarkPaper(void *handle);

AUTOREPLYPRINT_API int CP_BlackMark_HalfCutBlackMarkPaper(void *handle);

AUTOREPLYPRINT_API int CP_Label_EnableLabelMode(void *handle);

AUTOREPLYPRINT_API int CP_Label_DisableLabelMode(void *handle);

AUTOREPLYPRINT_API int CP_Label_CalibrateLabel(void *handle);

AUTOREPLYPRINT_API int CP_Label_FeedLabel(void *handle);

AUTOREPLYPRINT_API int CP_Label_PageBegin(void *handle, int x, int y, int width, int height, CP_Label_Rotation rotation);

AUTOREPLYPRINT_API int CP_Label_PagePrint(void *handle, int copies);

AUTOREPLYPRINT_API int CP_Label_DrawText(void *handle, int x, int y, int font, int style, const char *str);

AUTOREPLYPRINT_API int CP_Label_DrawTextInUTF8(void *handle, int x, int y, int font, int style, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Label_DrawTextInGBK(void *handle, int x, int y, int font, int style, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Label_DrawTextInBIG5(void *handle, int x, int y, int font, int style, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Label_DrawTextInShiftJIS(void *handle, int x, int y, int font, int style, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Label_DrawTextInEUCKR(void *handle, int x, int y, int font, int style, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Label_DrawTextInBytes(void *handle, int x, int y, int font, int style, const char *str, int len);

AUTOREPLYPRINT_API int CP_Label_DrawBarcode(void *handle, int x, int y, CP_Label_BarcodeType nBarcodeType, CP_Label_BarcodeTextPrintPosition nBarcodeTextPrintPosition, int height, int unitwidth, CP_Label_Rotation rotation, const char *str);

AUTOREPLYPRINT_API int CP_Label_DrawQRCode(void *handle, int x, int y, int nVersion, CP_QRCodeECC nECCLevel, int unitwidth, CP_Label_Rotation rotation, const char *str);

AUTOREPLYPRINT_API int CP_Label_DrawQRCodeInUTF8(void *handle, int x, int y, int nVersion, CP_QRCodeECC nECCLevel, int unitwidth, CP_Label_Rotation rotation, const wchar_t *str);

AUTOREPLYPRINT_API int CP_Label_DrawQRCodeInBytes(void *handle, int x, int y, int nVersion, CP_QRCodeECC nECCLevel, int unitwidth, CP_Label_Rotation rotation, const char *str, int len);

AUTOREPLYPRINT_API int CP_Label_DrawPDF417Code(void *handle, int x, int y, int column, int nAspectRatio, int nECCLevel, int unitwidth, CP_Label_Rotation rotation, const char *str);

AUTOREPLYPRINT_API int CP_Label_DrawImageFromFile(void *handle, int x, int y, int dstw, int dsth, const char *pszFile, CP_ImageBinarizationMethod binaryzation_method);

AUTOREPLYPRINT_API int CP_Label_DrawImageFromData(void *handle, int x, int y, int dstw, int dsth, const unsigned char *data, unsigned int data_size, CP_ImageBinarizationMethod binaryzation_method);

AUTOREPLYPRINT_API int CP_Label_DrawImageFromPixels(void *handle, int x, int y, const unsigned char *img_data, unsigned int img_datalen, int img_width, int img_height, int img_stride, CP_ImagePixelsFormat img_format, CP_ImageBinarizationMethod binaryzation_method);

AUTOREPLYPRINT_API int CP_Label_DrawLine(void *handle, int startx, int starty, int endx, int endy, int linewidth, CP_Label_Color linecolor);

AUTOREPLYPRINT_API int CP_Label_DrawRect(void *handle, int x, int y, int width, int height, CP_Label_Color color);

AUTOREPLYPRINT_API int CP_Label_DrawBox(void *handle, int x, int y, int width, int height, int borderwidth, CP_Label_Color bordercolor);

#ifdef __cplusplus
}
#endif

#endif

