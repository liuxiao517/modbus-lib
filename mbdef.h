/* 
 * File:   mbport.h
 * Author: Administrator
 *
 * Created on 2015��8��24��, ����8:38
 * modify @ 20180804
 * --΢��
 */

#ifndef __MBDEF_H
#define	__MBDEF_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "mbcrc.h"   

typedef unsigned char       mbSlaveIdType;  
typedef unsigned short      mbRegNumType; 
typedef unsigned short      mbRegAddrType; 
typedef unsigned short      mbRegDataType; 

#define MB_OS_USED                              1
#define MB_ASCII_EN                             0
    
#define MB_BUFF_SIZE                            (256)
#define MB_ERR_CNT_PV                           (  3 )
#define SMB_TIME_OUT_MS                         (6000)
#define MMB_TIME_OUT_MS                         (120 )

#define MB_EVENT_SEND_END                       (0x01)
#define MB_EVENT_RCV_END                        (0x02)

#define MB_FUN_READ_COILS_ENABLED               (  1 )  //Fun: 01
#define MB_FUN_READ_DISCRETE_INPUTS_ENABLED     (  1 )  //Fun: 02
#define MB_FUN_READ_REG_ENABLED                 (  1 )  //Fun: 03    
#define MB_FUN_READ_INPUT_ENABLED               (  1 )  //Fun: 04
#define MB_FUN_WRITE_COIL_ENABLED               (  1 )  //Fun: 05
#define MB_FUN_WRITE_REG_ENABLED                (  1 )  //Fun: 06
#define MB_FUN_WRITE_MULTIPLE_COILS_ENABLED     (  1 )  //Fun: 15
#define MB_FUN_WRITE_MULTIPLE_REG_ENABLED       (  1 )  //Fun: 16 
#define MB_FUN_W_R_MULTIPLE_REG_ENABLED         (  1 )  //Fun: 0x17 

#define MB_REG_COILS_CB_ENABLE	    ( MB_FUN_READ_COILS_ENABLED + MB_FUN_WRITE_COIL_ENABLED + MB_FUN_WRITE_MULTIPLE_COILS_ENABLED  ) 
#define MB_REG_HOLDING_CB_ENABLE    ( MB_FUN_READ_REG_ENABLED + MB_FUN_WRITE_REG_ENABLED + MB_FUN_WRITE_MULTIPLE_REG_ENABLED + MB_FUN_W_R_MULTIPLE_REG_ENABLED )  
#define MB_REG_INPUT_CB_ENABLE	    ( MB_FUN_READ_INPUT_ENABLED   ) 
#define MB_REG_DISCRETE_CB_ENABLE   ( MB_FUN_READ_DISCRETE_INPUTS_ENABLED   )    

#define MB_COIL_ON                      0xFF00
#define MB_COIL_OFF                     0x0000

#define MB_ERR_CODE                     0x80
#define MB_FAULT_CODE1                  0x01
#define MB_FAULT_CODE2                  0x02
#define MB_FAULT_CODE3                  0x03
#define MB_FAULT_CODE4                  0x04

#define     MB_ERR_NONE        0        //!< no error. 
#define     MB_ERR_NOREG       1        //!< illegal register address. 
#define     MB_ERR_DATA        2 
#define     MB_ERR_CRC_LRC     3 
#define     MB_ERR_FUN_CODE    4
#define     MB_ERR_HAL         5
#define     MB_ETIMEDOUT       16       

#define     MB_NULL            (0)

    /* -----------------------  Cmd Type definitions ---------------------------------*/
    typedef enum {
        FUN_CODE_NONE = 0,
        FUN_CODE_READ_COILS = 0x01,
        FUN_CODE_READ_DISCRETE = 0x02,
        FUN_CODE_READ_REG = 0x03,
        FUN_CODE_READ_INPUT = 0x04,
        FUN_CODE_WRITE_COIL = 0x05,
        FUN_CODE_WRITE_REG = 0x06,
        FUN_CODE_WRITE_MULTIPLE_COIL = 0x0F,
        FUN_CODE_WRITE_MULTIPLE_REG = 0x10,
        FUN_CODE_WRITE_MASK = 0x16,
        FUN_CODE_W_R_MULTIPLE_REG = 0x17,
        FUN_CODE_READ_SLAVE_ID = 0x2B,
    } mbCmdType;

    /* -----------------------  Data Type definitions -------------------------*/
    typedef union {
        uint16_t Val;
        uint16_t uVal;
        int16_t iVal;
        struct {
            uint8_t LB;
            uint8_t HB;
        } byte;
    } mbU16Type;

    /* -----------------------  Receive State Type definitions ----------------*/
    typedef enum {
        MB_RX_IDLE, // Receiver is in idle state.
        MB_RX_RCV, // Frame is beeing received.
        MB_RX_RCVEND, // Port Receive complete ,3.5T timer
        MB_RX_WAIT, //Just for master
        MB_RX_TIMEOUT // Time out ,Send a command and no data return after 500ms( --> system timer)
    } mbRcvStType;

    /* -----------------------  Send State Type definitions -------------------*/
    typedef enum {
        MB_TX_IDLE, // Transmitter is in idle state.
        MB_TX_XMIT // Transmitter is in transfer state.
    } mbSndStType;

    /* -----------------------  Data parity definitions -----------------------*/
    typedef enum {
        MB_PAR_NONE, /*!< No parity. */
        MB_PAR_ODD, /*!< Odd parity. */
        MB_PAR_EVEN /*!< Even parity. */
    } mbParityType;

    /* -----------------------  RW Type definitions ---------------------------*/
    typedef enum {
        MB_REG_READ,
        MB_REG_WRITE,
    } mbRegModeType;

    /* --------------------  Modbus mode Type definitions ---------------------*/
    typedef enum {
        MB_RTU_MASTER,
        MB_RTU_SLAVE,
        //ASCII_MASTER,
        //ASCII_SLAVE
    } mbModeType;

    /* ------------------  baudary Type definitions ---------------------------*/
    typedef enum {
        MB_BAUD_1200 = 0,
        MB_BAUD_2400 = 1,
        MB_BAUD_4800 = 2,
        MB_BAUD_9600 = 3,
        MB_BAUD_19200 = 4,
        MB_BAUD_38400 = 5,
        MB_BAUD_115200 = 6
    } mbBaudType;

    /* ------------------  Run State Type definitions -------------------------*/
    typedef union {
        uint64_t St;

        struct {
            uint8_t MasterMode;
            uint8_t RTUMode;
            uint8_t PortSt;
            uint8_t Connect;
        } bits;
    } mbRunStType;

    /* ------------------  Error State Type definitions -----------------------*/
    typedef union {
        uint64_t St;

        struct {
            uint8_t ErrHal ;
            uint8_t ErrData ;
            uint8_t ErrNoReg ;
            uint8_t ErrFunCode ;
            uint8_t ErrCrcLrc ;
        } bits;
    } mbErrStType;

    /* ---------------  Cmd Buffer State Type definitions ---------------------*/
    typedef enum {
        MB_CMD_ST_IDLE = 0, //������Ч���Ѿ�ִ�й�
        MB_CMD_ST_READY = 1, //�������׼��ִ��
    } mbCmdStType;

    /* ------------- Master Cmd Buffer struct Type definitions -----------------------*/
    typedef struct {  
        uint8_t DeviceId; //�ӻ�ID
        mbCmdType Cmd; //����  //
        uint16_t *Data; //���ݵ�ַ
        uint16_t mbAddr; //modbus��ַ
        uint16_t amount; //����
        mbCmdStType ReqSt; //����״̬
        void (*CallBack)(uint8_t CmdSite, uint8_t ErrSt); //�ص�����
    } mbCmdBuffType;

    /* ------------ Slave extern Function Type definitions --------------------*/
    typedef struct {
        uint8_t(*RegInputCB)(uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs);
        uint8_t(*RegHoldingCB)(uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs, mbRegModeType eMode);
        uint8_t(*RegDiscreteCB)(uint8_t *pucRegBuffer, uint16_t usAddress, uint16_t usNCoils);
        uint8_t(*RegCoilsCB)(uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNCoils, mbRegModeType eMode);
    } mbSlaveFunType;

    /* ------------- Master Function Type definitions -------------------------*/
    typedef struct {
        uint8_t ErrCnt; //���������
        uint8_t DcmdReqIndex; //��̬������������
        uint8_t DcmdHandleIndex; //��̬���������
        uint8_t ScmdHandleIndex; //��̬���������
        uint8_t CmdHandleIndex; //��ǰ������������
        uint8_t CmdBuffSize; //�ܻ���سߴ�
        uint8_t ScmdBuffSize; //��̬����سߴ�
        uint8_t LenReq; //�������ݳ��� �ֽ���
        uint16_t *pData; //����ָ�� - ��Ŵ����������
        mbCmdBuffType* pcmdBuff; //����ָ�� - ָ������������
#if MB_OS_USED > 0 
        void (*MutexPend)(void);
        void (*MutexPost)(void);
#endif
    } mbMasterFunType;

    /* -------------- Modbus object Type definitions ---------------------------*/
    typedef struct {
        mbRunStType RunSt; //����״̬
        mbErrStType ErrSt; //����״̬
        mbRcvStType RcvSt; //����״̬       //Ӳ���жϹ��� //���յ��ַ���ΪRCV �����ս�����ΪRCVEND //�в���ϵͳʱ���ⲿ��ΪTIMEOUT
        mbSndStType SndSt; //����״̬       //���ķ��ͽ������ⲿ��ΪIDLE
        uint8_t SlaveId; //�ӻ�id
        uint8_t bPulse10ms; //���ڳ�ʱ����,ÿ10ms������һһ�� //ʹ���ⲿ��ʱ����ʱ����0����
        uint16_t TimeOutCnt; //��ʱ���������޲���ϵͳʱʹ��  //�������ķ��ͽ�����ʼ��ʱ
        uint16_t RcvCnt; //�������ݸ���   //Ӳ���жϼ�Ӧ�ò���� 
        uint16_t SndSize; //���������ݸ���
        uint16_t SndCnt; //���͹��̼���
        void (*AduSend)(void); //����ָ�� - ����AduBuff���ݵ��˿ڣ�������SndSizeָʾ

        union {
            mbSlaveFunType Slave; //�ӻ��ṹ
            mbMasterFunType Master; //�����ṹ
        } Fun;
        uint8_t AduBuff[MB_BUFF_SIZE]; //���ݻ���
    } mbObjType;

    /* -------------- ״̬������ ---------------------------*/
    /*
    �ӻ���
        RX-IDLE&TX-IDLE -> RX-RCV&TX-IDLE -> RX-RCVEND&TX-IDLE -> RX-IDLE&TX-SEND -> RX-IDLE&TX-IDLE 
             
    ������
        RX-IDLE&TX-IDLE -> RX-RCV&TX-SEND -> RX-RCV&TX-IDLE -> RX-RCVEND&TX-IDLE -> RX-IDLE&TX-IDLE 
    */

#ifdef	__cplusplus
}
#endif

#endif	/* __MBDEF_H */

