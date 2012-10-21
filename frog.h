#ifndef frog_H
#define frog_H

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"
#include "gamemanager.h"

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
	
private:
	Ui::MainWindow *ui;
	GameManager *manager;
};

#endif // frog_H
