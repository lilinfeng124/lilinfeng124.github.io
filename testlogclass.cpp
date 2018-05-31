#include "testlogclass.h"
#include "DeviceDebug.inl"
#include <QCoreApplication>
testlogclass::testlogclass(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	m_run = false;
	m_nNo = 0;
	connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(StartOrStop()));

	
}

testlogclass::~testlogclass()
{

}

void testlogclass::StartOrStop()
{
	if(!m_run)
	{
		m_run = true;

		while(1)
		{
			if(!m_run)
			{
				return;
			}
			QCoreApplication::processEvents();
			QString str = QString::number(m_nNo++);
			str +=QString("test word ");
			//RecordMsg(str);
			CDeviceDebug()<<str<<m_nNo;
		}
	}
	else
	{
		m_run = false;
	}
}
