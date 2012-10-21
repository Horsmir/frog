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
	manager->setSizeScene(1024, 400);
	manager->initCards();
	ui->graphicsView->setScene(manager->getScene());
	QMainWindow::show();
}

void frog::on_actionNew_triggered()
{
	manager->newCards();
}

#include "frog.moc"
