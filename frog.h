#ifndef frog_H
#define frog_H

#include <QtCore/QDebug>
#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include <QtGui/QResizeEvent>
#include <QtCore/QDir>
#include "ui_mainwindow.h"
#include "gamemanager.h"
#include "help_browser/helpbrowser.h"
#include "frogconfigure.h"

namespace Ui
{
	class MainWindow;
}

class frog : public QMainWindow
{
Q_OBJECT
public:
	frog(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    virtual ~frog();
	
public slots:
	void show();
	void on_actionNew_triggered();
	void on_actionHelp_triggered();
	void on_actionAbout_triggered();
	void on_actionAboutQt_triggered();
	
protected:
	virtual void resizeEvent(QResizeEvent *event);
	
private:
	Ui::MainWindow *ui;
	GameManager *manager;
	QString appName;
	bool firstPaint;
	QDir appDir;
};

#endif // frog_H
