/*****************************************************************************
Copyright:  2016, Nari Tech. Co., Ltd.
File name:  DeviceDebug.h 
Description:代替qDebug使用，用于生成文件
Author:     李临风
Version:    v0.0.1
Date:       2018-05-29
History:    2016-05-29 李临风 创建.
*****************************************************************************/

#ifndef CDEVICEDEBUG_H_
#define CDEVICEDEBUG_H_
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
#include "RecordMng.h"

class CDeviceDebug
{
public:

	struct Stream {
		Stream(QIODevice *device) : ts(device), ref(1), type(QtDebugMsg), space(true), message_output(false) {}
		Stream(QString *string) : ts(string, QIODevice::WriteOnly), ref(1), type(QtDebugMsg), space(true), message_output(false) {}
		Stream(QtMsgType t) : ts(&buffer, QIODevice::WriteOnly), ref(1), type(t), space(true), message_output(true) {}
		QTextStream ts;
		QString buffer;
		int ref;
		QtMsgType type;
		bool space;
		bool message_output;
	} *stream;
public:
	inline CDeviceDebug(QIODevice *device) : stream(new Stream(device)) {}
	inline CDeviceDebug(QString *string) : stream(new Stream(string)) {}
	inline CDeviceDebug(QtMsgType t=QtDebugMsg) : stream(new Stream(t)) {}
	inline CDeviceDebug(const CDeviceDebug &o):stream(o.stream) { ++stream->ref; }
	inline CDeviceDebug &operator=(const CDeviceDebug &other);
	inline ~CDeviceDebug() {
		if (!--stream->ref) {
			if(stream->message_output) {
				QT_TRY {
					CRecordMng::getInst()->OutputMsg(stream->buffer.toLocal8Bit());
					//qt_message_output(stream->type, stream->buffer.toLocal8Bit().data());
				} QT_CATCH(std::bad_alloc&) { /* We're out of memory - give up. */ }
			}
			delete stream;
		}

	}
	inline CDeviceDebug &space() { stream->space = true; stream->ts << ' '; return *this; }
	inline CDeviceDebug &nospace() { stream->space = false; return *this; }
	inline CDeviceDebug &maybeSpace() { if (stream->space) stream->ts << ' '; return *this; }

	inline CDeviceDebug &operator<<(QChar t) { stream->ts << '\'' << t << '\''; return maybeSpace(); }
	inline CDeviceDebug &operator<<(QBool t) { stream->ts << (bool(t != 0) ? "true" : "false"); return maybeSpace(); }
	inline CDeviceDebug &operator<<(bool t) { stream->ts << (t ? "true" : "false"); return maybeSpace(); }
	inline CDeviceDebug &operator<<(char t) { stream->ts << t; return maybeSpace(); }
	inline CDeviceDebug &operator<<(signed short t) { stream->ts << t; return maybeSpace(); }
	inline CDeviceDebug &operator<<(unsigned short t) { stream->ts << t; return maybeSpace(); }
	inline CDeviceDebug &operator<<(signed int t) { stream->ts << t; return maybeSpace(); }
	inline CDeviceDebug &operator<<(unsigned int t) { stream->ts << t; return maybeSpace(); }
	inline CDeviceDebug &operator<<(signed long t) { stream->ts << t; return maybeSpace(); }
	inline CDeviceDebug &operator<<(unsigned long t) { stream->ts << t; return maybeSpace(); }
	inline CDeviceDebug &operator<<(qint64 t)
	{ stream->ts << QString::number(t); return maybeSpace(); }
	inline CDeviceDebug &operator<<(quint64 t)
	{ stream->ts << QString::number(t); return maybeSpace(); }
	inline CDeviceDebug &operator<<(float t) { stream->ts << t; return maybeSpace(); }
	inline CDeviceDebug &operator<<(double t) { stream->ts << t; return maybeSpace(); }
	inline CDeviceDebug &operator<<(const char* t) { stream->ts << QString::fromAscii(t); return maybeSpace(); }
	inline CDeviceDebug &operator<<(const QString & t) { stream->ts << '\"' << t  << '\"'; return maybeSpace(); }
	inline CDeviceDebug &operator<<(const QStringRef & t) { return operator<<(t.toString()); }
	inline CDeviceDebug &operator<<(const QLatin1String &t) { stream->ts << '\"'  << t.latin1() << '\"'; return maybeSpace(); }
	inline CDeviceDebug &operator<<(const QByteArray & t) { stream->ts  << '\"' << t << '\"'; return maybeSpace(); }
	inline CDeviceDebug &operator<<(const void * t) { stream->ts << t; return maybeSpace(); }
	inline CDeviceDebug &operator<<(QTextStreamFunction f) {
		stream->ts << f;
		return *this;
	}

	inline CDeviceDebug &operator<<(QTextStreamManipulator m)
	{ stream->ts << m; return *this; }
};


//extern void InitRecordHandler();
//extern void RecordMsg(QString str);
//extern void ReleaseRecordHandler();
#endif