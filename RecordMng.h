/*****************************************************************************
Copyright:  2016, Nari Tech. Co., Ltd.
File name:  RecordMng.h 
Description:��ʷ��¼,ÿһ��дһ��log�ļ����ļ���С����һ����С����ɾ�������ݵ�ǰ����֮һ��
Author:     ���ٷ�
Version:    v0.0.1
Date:       2018-05-29
History:    2016-05-29 ���ٷ� ����.
*****************************************************************************/

#ifndef CDBGRECORDMNG_H_
#define CDBGRECORDMNG_H_
#include <QString>
#include <QFile>
#include <QMutex>
#include <QObject>
#include <QTimer>
#include <QStringList>
#include <qglobal.h>
#include <QIODevice>
#include <QDataStream>
#include <QTextStream>

class CRecordMng:public QObject
{
	Q_OBJECT
public:
	static CRecordMng* getInst();
public:
	~CRecordMng();

	void OutputMsg(QByteArray str);
	public slots:
		void ManageFileSizeSlot();

		void WriteLogSlot();//дlog�ļ��Ĳۺ������̶�1s����д��һ��

private:
	CRecordMng(QObject*p=NULL);
	void ReadIni();
private:
	static CRecordMng* g_Inst;
	QString m_strLogFile;//�ļ�ȫ·����
	QFile* m_fFile;
	bool m_bCreateLog; //�Ƿ�����log�ļ�
	bool m_bDbg;    //�Ƿ��ӡ
	QMutex m_Mtx;
	QTimer *m_pSizeMngTimer; //����log�ļ���С�ļ�ʱ��
	QTimer *m_pWriteTimer;   //д��־�ļ�ʱ��
	int    m_nFileMaxSize;   //�ļ���󳤶�
	int    m_nCheckTimeSpan; //����ļ����ȵ�ʱ��

	QList<QByteArray>  m_strContentLst;    //�洢��д�����ݡ�ÿһ��д��һ��

};


//extern void InitRecordHandler();
//extern void RecordMsg(QString str);
//extern void ReleaseRecordHandler();
#endif