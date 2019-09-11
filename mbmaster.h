/* 
 * File:   MBMaster.h
 * Author: Administrator
 * 
 * Created on 2015��5��20��, ����7:31
 */
/*----------------------------------------------------------------------------*/
/*---------------����16λ���ݣ���8λ��ǰ����8λ�ں�-----------------------------*/
/*----------------------------------------------------------------------------*/

#ifndef MBMASTER_H
#define	MBMASTER_H

#include "mbdef.h"

#ifdef	__cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////                                            �����ײ�ӿ�                                           //////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Fun: 0x01
uint8_t    mbReadCoils(mbObjType * mbObj, uint16_t DataAdd, uint16_t Len);

//Fun: 0x02
uint8_t    mbReadDiscreteInputs(mbObjType * mbObj, uint16_t DataAdd, uint16_t Len);

//Fun: 0x03
uint8_t    mbReadRegister(mbObjType * mbObj, uint16_t DataAdd, uint16_t Len);

//Fun: 0x04
uint8_t    mbReadInputRegister(mbObjType * mbObj, uint16_t DataAdd, uint16_t Len);

//Fun: 0x05
uint8_t    mbWriteCoil(mbObjType * mbObj, uint16_t DataAdd, uint16_t Data);

//Fun: 0x06
uint8_t    mbWriteRegister(mbObjType * mbObj, uint16_t DataAdd, uint16_t Data);

//Fun: 0x0F
uint8_t    mbWriteMultipleCoils(mbObjType * mbObj, uint16_t DataAdd, uint16_t Len);

//Fun: 0x10
uint8_t    mbWriteMultipleRegister(mbObjType * mbObj, uint16_t DataAdd, uint16_t Len);

//Fun: 0x17
uint8_t    mbWRRegister(mbObjType * mbObj, uint16_t rDataAdd, uint16_t rLen, uint16_t wDataAdd, uint16_t wLen, uint16_t * pWdata);

uint8_t mbReadRegProc(mbObjType * mbObj);
uint8_t mbReadCoilProc(mbObjType * mbObj);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////                                            ����Ӧ�ò�ӿ�                                         //////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*-----------------------------------------------------------------------------------------------------------------------------*
 *    ����ʹ�û����������û���������Poll�����Զ���������е�����
 *
 *    ����ؽṹ����
 *        0                                                      mbSCBuffSize                                          mbCBuffSize
 *        |                                                           |                                                     |
 *    | Buff0 | Buff1 | Buff2 |  ....  | Buff[mbSCBuffSize-1] | Buff[mbSCBuffSize] | Buff[mbSCBuffSize+1] |  ....  | Buff[mbCBuffSize]|
 *        |                                       |                   |                                                     |
 *       ��̬                                    ��̬                ��̬                                                  ��̬
 *       ����                                    ����                ����                                                  ����
 *       ��ʼ                                    ����                ��ʼ                                                  ����
 *
 *    ɨ��˳��
 *    ��ɨ�趯̬�������ϴδ����λ�ÿ�ʼ�����к��˳�����ɨ����������̬����û�����У���ʼɨ�農̬��                               
 *    ɨ�農̬��������ͬ��̬����
 *    ����������������ڣ���̬����������ᱻ���������̬һֱ���־���״̬��
 *
 *
 *----------------------------------------------------------------------------------------------------------------------------*/
//����س�ʼ��
void mbCmdBuffInit(mbObjType *mbObj, mbCmdBuffType * pBuff, uint8_t mbCBuffSize, uint8_t mbSCBuffSize);
//�ź������� //��ʼ��֮��ſ��Ե��� //����Ҫʱ���Բ����� //��ΪMB_NULLȡ������
#if MB_OS_USED > 0 
void mbCmdMutexInit(mbObjType *mbObj, void (*Pend)(void),void (*Post)(void));
#endif

//��̬�������� 
uint8_t mbStaticCmdSet(mbObjType *mbObj, uint8_t CmdSite, uint8_t DeviceId, mbCmdType Cmd, uint16_t *Data, uint16_t mbAddr, uint16_t amount, void (*CallBack)(uint8_t,uint8_t));
//��̬��������   //����������Ϊ0��ʾȡ��������
uint8_t mbDynaCmdReq(mbObjType *mbObj, uint8_t DeviceId, mbCmdType Cmd, uint16_t *Data, uint16_t mbAddr, uint16_t amount, void (*CallBack)(uint8_t,uint8_t));

//����������������ͬ������һ�����������뻥���ź���
uint8_t mbStaticCmdSetNoOS(mbObjType *mbObj, uint8_t CmdSite, uint8_t DeviceId, mbCmdType Cmd, uint16_t *Data, uint16_t mbAddr, uint16_t amount, void(*CallBack)(uint8_t, uint8_t));
uint8_t mbDynaCmdReqNoOS(mbObjType *mbObj, uint8_t DeviceId, mbCmdType Cmd, uint16_t *Data, uint16_t mbAddr, uint16_t amount, void(*CallBack)(uint8_t, uint8_t));

//����0x17��ͬʱ��д����֧�־�̬���䣬��ռ�����������Ļ���������һΪ���������ڶ�Ϊд����,���в����Ե�һ������Ϊ׼��
//��������������ͨ��mbStaticCmdSetNoOS()���룬�������Ҫ�����в�����Ӧ�ֶ������ź�����

//��̬����ؾ�������
uint8_t NumOfMmbCmdReady(mbObjType *mbObj);

//��̬����ؿ�������
uint8_t NumOfMmbCmdIdle(mbObjType *mbObj);

//�����������״̬
void mbCmdStClrAll(mbObjType *mbObj);

//��ȡ��ǰ���ڴ��������
uint32_t mbCmdHandleGet(mbObjType *mbObj, mbCmdBuffType * pBuff);

//�������� ѭ���е���
void mbMasterPoll(mbObjType *mbObj);            

#ifdef	__cplusplus
}
#endif

#endif	/* MBMASTER_H */

