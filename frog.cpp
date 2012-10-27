#include "frog.h"

frog::frog(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), ui(new Ui::MainWindow)
{
	appDir.setPath(APP_PATH);
	QString cardImgFile = appDir.absolutePath() + "/share/frog/images/tigullio-bridge.svg";
	qDebug() << cardImgFile;
	ui->setupUi(this);
	manager = new GameManager(this);
	QSvgRenderer *render = new QSvgRenderer(cardImgFile, this);
	manager->setRender(render);
	
	appName = "Frog";
	firstPaint = true;
}

frog::~frog()
{
	delete ui;
}

void frog::show()
{
	ui->graphicsView->setScene(manager->getScene());
	QMainWindow::show();
	manager->setSizeScene(ui->graphicsView->width() - 10, ui->graphicsView->height() - 10);
	manager->initCards();
}

void frog::on_actionNew_triggered()
{
	manager->newCards();
}

void frog::on_actionHelp_triggered()
{
	HelpBrowser::showPage(appDir.absolutePath() + "/share/doc/frog", "index.html");
}

void frog::on_actionAbout_triggered()
{
	QString str1, str2, str3, str4;
	
	str1 = trUtf8("<h2>%1 %2</h2><p><b>%1</b> - пасьянс с двумя колодами также называют «Жаба в норе». Имеются восемь баз, основанных на тузах, и пять стопок сброса.</p><p>Copyright &copy;  2012 Роман Браун</p>").arg(appName).arg(VERSION);
	str2 = trUtf8("<p>Это программа является свободным программным обеспечением. Вы можете распространять и/или модифицировать её согласно условиям Стандартной Общественной Лицензии GNU, опубликованной Фондом Свободного Программного Обеспечения, версии 3 или, по Вашему желанию, любой более поздней версии.</p>");
	str3 = trUtf8("<p>Эта программа распространяется в надежде, что она будет полезной, но БЕЗ ВСЯКИХ ГАРАНТИЙ, в том числе подразумеваемых гарантий ТОВАРНОГО СОСТОЯНИЯ ПРИ ПРОДАЖЕ и ГОДНОСТИ ДЛЯ ОПРЕДЕЛЁННОГО ПРИМЕНЕНИЯ. Смотрите Стандартную Общественную Лицензию GNU для получения дополнительной информации.</p>");
	str4 = trUtf8("<p>Вы должны были получить копию Стандартной Общественной Лицензии GNU вместе с программой. В случае её отсутствия, посмотрите <a href=\"http://www.gnu.org/licenses/\">http://www.gnu.org/licenses/</a>.</p><p>E-Mail: <a href=\"mailto:firdragon76@gmail.com\">firdragon76@gmail.com</a><br>Сайт программы: <a href=\"github.com/Horsmir/frog\">github.com/Horsmir/frog</a></p>");
	
	QMessageBox::about(this, trUtf8("О программе"), str1 + str2 + str3 + str4);
}

void frog::on_actionAboutQt_triggered()
{
	qApp->aboutQt();
}

void frog::resizeEvent(QResizeEvent* event)
{
	if(!firstPaint)
	{
		qreal scal = qreal(event->size().width()) / qreal(event->oldSize().width());
		ui->graphicsView->scale(scal, scal);
	}
	firstPaint = false;
	QWidget::resizeEvent(event);
}

#include "frog.moc"
