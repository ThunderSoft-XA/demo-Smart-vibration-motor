/**
************************************************************
* @file         gagent_soc.h
* @brief        gagent
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/

#ifndef GAGENT_SOC_H
#define GAGENT_SOC_H
#define SDK_USER_VER_LEN        2
#include "txm_module.h"
#include "stdlib.h"
#include "stdint.h"
#include <stdio.h>
#include <stdarg.h>
#include "qapi/qapi_types.h"
#include "threadx_api/txm_module.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_dss.h"
#include "qapi/qapi_socket.h"
#include "qapi/qapi_dnsc.h"
#include "qapi_uart.h"
#include "qapi_ns_utils.h"
#include "qapi_fs.h"
#include "qapi_timer.h"
#include "qapi/qapi_gpioint.h"
#include "qapi/qapi_tlmm.h"
#include "qapi_diag.h"
#include "msgcfg.h"
#include "msg_mask.h"
#include "qapi_lwm2m.h"
#include "qapi/qapi_device_info.h"
#include <errno.h>

#define PK_LEN           32
#define PKS_LEN          32
#define MAC_LEN          16
#define MAC_MAXLEN       32
#define PASSCODE_LEN     10
#define PASSCODE_MAXLEN  32
#define DID_LEN          22
#define CLIENTID_MAXLEN  23
#define DOMAIN_LEN       60
#define IP_LEN           15
#define PORT_STR_LEN     10
#define AUTHkEY_LEN      32
#define APN_LEN          64

#define MCU_PROTOCOLVER_LEN     8
#define MCU_P0VER_LEN           8
#define MCU_HARDVER_LEN         8
#define MCU_SOFTVER_LEN         8
#define MCUATTR_LEN             8

typedef char int8;

typedef void (*gagentConnectCb)(int32 result, uint8* pszDID, uint8 *szPasscode, void *arg);
typedef void (*gagentResetSimulatorCb)(int32 result, uint8* szMac, void *arg);
typedef void (*gagentUploadDataCb)( int32 result,void *arg,uint8* pszDID);
typedef void (*gagentDisconnectCb)(int32 result, uint8* pszDID, void *arg);

typedef struct
{
    uint16 year;
    uint8 month;
    uint8 day;
    uint8 hour;
    uint8 minute;
    uint8 second;
    uint32 ntp;
}_tm;

typedef struct _regRest_st
{
    int32  result;    // 云端返回码，非0为失败。
    uint8  szDID[DID_LEN+1];    // 成功为有效DID,否则为NULL
    uint8  szAuthKey[AUTHkEY_LEN+1];    // 成功为有效DID,否则为NULL
    uint8  szMac[MAC_MAXLEN+1];
    uint8  szPasscode[PASSCODE_MAXLEN+1];
    uint8  szMeshId[32+1];
    uint8* msg;    // 登陆成功或者失败的相关信息，失败时此信息有助于定位问题
}regRest_st;

typedef struct _loginCb_st
{
    int32  result;
    uint8  szDID[DID_LEN+1];
}loginCb_st;

typedef enum _GAgentKeyVal_t
{
    GIZ_DID,                    // did
    GIZ_PASSCODE,               // passcode
    GIZ_TZS,                    // 当前时区秒
    GIZ_GSER,                   // 当前服务器域名
}GAgentKeyVal_t;

struct devAttrs
{
    unsigned short mBindEnableTime;
    unsigned char mstrProtocolVer[MCU_PROTOCOLVER_LEN];
    unsigned char mstrP0Ver[MCU_P0VER_LEN];
    unsigned char mstrDevHV[MCU_HARDVER_LEN];
    unsigned char mstrDevSV[MCU_SOFTVER_LEN];
    unsigned char mstrProductKey[PK_LEN];
    unsigned char mstrPKSecret[PKS_LEN];
    unsigned char mDevAttr[MCUATTR_LEN];
    unsigned char mstrSdkVerLow[SDK_USER_VER_LEN];
    //gagent 微信公众号ID,默认为机智云微信宠物屋ID
    uint8 *szWechatDeviceType;
    //gagent 默认连接服务器域名
    uint8 *szGAgentSever;
    //gagent 默认连接服务器端口，默认为80
    uint8 *gagentSeverPort;
    //gagent softap Name ,默认值:XPG-GAgent-xxxx(后面4位为MAC后4位)
    uint8 *szGAgentSoftApName;
    uint8 *szGAgentSoftApName0;
    //gagent softap 密码 ,默认值:123456789，若内容为空则热点不加密;
    uint8 *szGAgentSoftApPwd;
    //m2m keepalive 默认值 120s
    uint8 *m2mKeepAliveS;
    //m2m 心跳间隔 默认值为 50s
    uint8 *m2mHeartbeatIntervalS;
    //gagent 时区秒，默认为东八区:8*(60*60)
    int32 *timeZoneS;
    //串口心跳间隔S，默认值 55秒
    uint8 *localHeartbeatIntervalS;
    //串口数据传送ACK时间，默认值600ms+数据长度耗时
    uint8 *localTransferIntervalMS;
    //网卡名称
    uint8 *networkCardName;
    // 默认配置模式
    uint8 *configMode;
};
typedef void (*gagentDevsLoginCb)(loginCb_st result[],int32 resultNum, void *arg);
typedef void (*gagentDevsRegisterCb)(regRest_st result[],int32 resultNum, void *arg);
void gagentInit(struct devAttrs attrs);
void gagentDisconnectM2M(uint8 *szDID, void *arg, gagentDisconnectCb fun);
int32 gagentconnect2M2M(uint8 *szMac, uint8 *szPk, uint8 *szPks,uint8 *szDID, uint8 *szPasscode, int8 flag ,void *arg,gagentConnectCb fun );
int32 gagentResetSimulator( uint8 *szMac,uint8 *szPk, uint8 *szPks,uint8 *szPasscode, void *arg,gagentResetSimulatorCb fun );
int32 gagentUploadData(uint8 *szDID, uint8 *src, uint32 len,uint8 flag, void *arg,gagentUploadDataCb fun );

int32 gagentDevsRegister( regRest_st* subDev,int32 devNum, uint8* szPK,uint8* szPKS,uint8 *pszParentDID, uint8 *pGwDid,uint8 *devExtra,void *arg,int8 is_reset,gagentDevsRegisterCb fun );
int32 gagentDevsLogin( uint8 *szDID[],int32 devNum, void *arg, gagentDevsLoginCb fun );
uint8 *GAgentInfoGet( GAgentKeyVal_t key );

void gagentGetNTP(_tm *time);
void gagentConfig(unsigned char configType);
void gagentReset(void);
void GAgentEnableBind();

#endif