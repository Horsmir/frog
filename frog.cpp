#include "frog.h"

frog::frog(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	manager = new GameManager(this);
	QSvgRenderer *render = new QSvgRenderer(QLatin1String("../images/tigullio-bridge.svg"), this);
	manager->setRender(render);
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
	HelpBrowser::showPage("../doc/", "index.html");
}

#include "frog.moc"
