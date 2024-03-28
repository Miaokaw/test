#ifndef __ZDTMOTORCONTROL_H__
#define __ZDTMOTORCONTROL_H__

#include "main.h"

#define		ABS(x)		((x) > 0 ? (x) : -(x)) 

typedef enum 
{
  S_VER   = 0,      /* ��ȡ�̼��汾�Ͷ�Ӧ��Ӳ���汾 */
  S_RL    = 1,      /* ��ȡ��ȡ���������� */
  S_PID   = 2,      /* ��ȡPID���� */
  S_ORG   = 3,      /* ��ȡ������� */
  S_VBUS  = 4,      /* ��ȡ���ߵ�ѹ */
  S_CBUS  = 5,      /* ��ȡ���ߵ��� */
  S_CPHA  = 6,      /* ��ȡ����� */
  S_ENC   = 7,      /* ��ȡ������ԭʼֵ */
  S_CPUL  = 8,      /* ��ȡʵʱ������������ʵʱλ�ü���õ����������� */
  S_ENCL  = 9,      /* ��ȡ�������Ի�У׼��ı�����ֵ */
  S_TPUL  = 10,     /* ��ȡ���������� */
  S_TPOS  = 11,     /* ��ȡ���Ŀ��λ�� */
  S_OPOS  = 12,     /* ��ȡ���ʵʱ�趨��Ŀ��λ�ã�����ģʽ��ʵʱλ�ã� */
  S_VEL   = 13,     /* ��ȡ���ʵʱת�� */
  S_CPOS  = 14,     /* ��ȡ���ʵʱλ�ã����ڽǶȱ������ۼӵĵ��ʵʱλ�ã� */
  S_PERR  = 15,     /* ��ȡ���λ����� */
  S_TEMP  = 16,     /* ��ȡ���ʵʱ�¶� */
  S_SFLAG = 17,     /* ��ȡ״̬��־λ */
  S_OFLAG = 18,     /* ��ȡ����״̬��־λ */
  S_Conf  = 19,     /* ��ȡ�������� */
  S_State = 20,     /* ��ȡϵͳ״̬���� */
}SysSingtype;

void resetCurPosToZero(uint8_t addr); // ����ǰλ������
void resetClogPro(uint8_t addr); // �����ת����
void readSysParams(uint8_t addr, SysSingtype s); // ��ȡ����
void modifyCtrlMode(uint8_t addr, bool svF, uint8_t ctrlMode); // ���������л�����/�ջ�����ģʽ
void enControl(uint8_t addr, bool state, uint8_t snF); // ���ʹ�ܿ���
void torqueControl(uint8_t addr, uint8_t sign, uint16_t tRamp, uint16_t torque, uint8_t snF); // ����ģʽ����
void velocityControl(uint8_t addr, uint8_t dir, uint16_t vRamp, float velocity, uint8_t snF); // �ٶ�ģʽ����
void bypassPositionLVControl(uint8_t addr, uint8_t dir, float velocity, float position, uint8_t raf, uint8_t snF); // ֱͨ����λ��ģʽ����
void trajPositionControl(uint8_t addr, uint8_t dir, uint16_t acc, uint16_t dec, float velocity, float position, uint8_t raf, uint8_t snF); // �������߼Ӽ���λ��ģʽ����
void stopNow(uint8_t addr, uint8_t snF); // �õ������ֹͣ�˶�
void synchronousmotion(uint8_t addr); // �������ͬ����ʼ�˶�
void originSetO(uint8_t addr, bool svF); // ���õ�Ȧ��������λ��
void originModifyParams(uint8_t addr, bool svF, uint8_t oMode, uint8_t oDir, uint16_t oVel, uint32_t oTm, uint16_t slVel, uint16_t slMa, uint16_t slMs, bool potF); // �޸Ļ������
void originTriggerReturn(uint8_t addr, uint8_t oMode, bool snF); // �������������
void originInterrupt(uint8_t addr); // ǿ���жϲ��˳�����
void receiveData(uint8_t *rxCmd, uint8_t *rxCount); // �������ݽ��պ���

#endif /* __ZDTMOTORCONTROL_H__ */
