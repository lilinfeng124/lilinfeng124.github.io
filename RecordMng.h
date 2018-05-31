/*****************************************************************************
Copyright:  2016, Nari Tech. Co., Ltd.
File name:  RecordMng.h 
Description:历史记录,每一秒写一次log文件，文件大小超过一定大小，会删除掉内容的前三分之一。
Author:     李临风
Version:    v0.0.1
Date:       2018-05-29
History:    2016-05-29 李临风 创建.
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

		void WriteLogSlot();//写log文件的槽函数，固定1s集中写入一次

private:
	CRecordMng(QObject*p=NULL);
	void ReadIni();
private:
	static CRecordMng* g_Inst;
	QString m_strLogFile;//文件全路径名
	QFile* m_fFile;
	bool m_bCreateLog; //是否生成log文件
	bool m_bDbg;    //是否打印
	QMutex m_Mtx;
	QTimer *m_pSizeMngTimer; //控制log文件大小的计时器
	QTimer *m_pWriteTimer;   //写日志的计时器
	int    m_nFileMaxSize;   //文件最大长度
	int    m_nCheckTimeSpan; //检查文件长度的时长

	QList<QByteArray>  m_strContentLst;    //存储待写入内容。每一秒写入一次

};


//extern void InitRecordHandler();
//extern void RecordMsg(QString str);
//extern void ReleaseRecordHandler();
#endif