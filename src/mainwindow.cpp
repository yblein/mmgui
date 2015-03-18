#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QtConcurrent>
#include <QDebug>
#include <QFileDialog>
#include <mm/heightmap.h>
#include <mm/colormap.h>

#include "controlscene.hpp"
#include "generatornode.hpp"
#include "fractalgenerator.hpp"
#include "constantgenerator.hpp"
#include "diamondsquaregenerator.hpp"
#include "filternode.hpp"
#include "filters.hpp"

static QImage heightmapToImage(const mm::heightmap &map)
{
	QImage image(map.width(), map.height(), QImage::Format_RGB32);
	for (size_t y = 0; y < map.height(); ++y) {
		for (size_t x = 0; x < map.width(); ++x) {
			double v = map.at(x, y) * 255;
			image.setPixel(x, y, qRgb(v, v, v));
		}
	}
	return std::move(image);
}

static QImage colormapToImage(const mm::colormap &map)
{
	QImage image(map.width(), map.height(), QImage::Format_RGB32);
	for (size_t y = 0; y < map.height(); ++y) {
		for (size_t x = 0; x < map.width(); ++x) {
			mm::color mmc = map.at(x, y);
			QRgb qtColor = qRgb(mmc.red_channel(), mmc.green_channel(), mmc.blue_channel());
			image.setPixel(x, y, qtColor);
		}
	}
	return std::move(image);
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QPixmap defaultImg(256, 256);
	defaultImg.fill(Qt::black);
	ui->image->setPixmap(defaultImg);

	scene = new ControlScene(this);
	scene->setBackgroundBrush(QBrush(Qt::darkGray));
	scene->addItem(&output);

	connect(&futureWatcher, &FutureWatcherMap::started, this, &MainWindow::renderingStarted);
	connect(&futureWatcher, &FutureWatcherMap::finished, this, &MainWindow::renderingFinished);
	connect(scene, &ControlScene::graphUpdated, this, &MainWindow::updateImage);

	ui->controlGraph->setScene(scene);
	ui->controlGraph->setRenderHints(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionNewFractalGen_triggered()
{
	auto node = new GeneratorNode(tr("Fractal generator"), HandleItem::HeightMap, new FractalGenerator(this));
	scene->addItem(node);
}

void MainWindow::on_actionConstant_triggered()
{
	auto node = new GeneratorNode(tr("Constant generator"), HandleItem::HeightMap, new ConstantGenerator());
	scene->addItem(node);
}

void MainWindow::on_actionDiamondSquare_triggered()
{
	auto node = new GeneratorNode(tr("Diamond square generator"), HandleItem::HeightMap, new DiamondSquareGenerator());
	scene->addItem(node);
}

void MainWindow::on_actionNewFilterIslandize_triggered()
{
	auto f = new FilterNode(tr("Islandize Filter"), HandleItem::HeightMap, new IslandizeFilter());
	scene->addItem(f);
}

void MainWindow::on_actionFlatten_triggered()
{
	auto f = new FilterNode(tr("Flatten Filter"), HandleItem::HeightMap, new FlattenFilter());
	scene->addItem(f);
}

void MainWindow::on_actionSmooth_triggered()
{
	auto f = new FilterNode(tr("Smooth Filter"), HandleItem::HeightMap, new SmoothFilter());
	scene->addItem(f);
}

void MainWindow::on_actionColorize_triggered()
{
	auto f = new FilterNode(tr("Colorize Filter"), HandleItem::ColorMap, new ColorizeFilter());
	scene->addItem(f);
}

void MainWindow::renderingStarted()
{
	statusBar()->showMessage(tr("Rendering started..."));
}

void MainWindow::renderingFinished()
{
	QImage img;
	auto map = futureWatcher.result();
	if (map != nullptr) {
		if (auto heightmap = dynamic_cast<const HeightMap*>(map)) {
			img = heightmapToImage(heightmap->data);
		} else if (auto colormap = dynamic_cast<const ColorMap*>(map)) {
			img = colormapToImage(colormap->data);
		} else {
			Q_ASSERT(0);
		}
	}

	QString msg;
	if (img.size().isNull()) {
		msg = tr("No output image");
	} else {
		int w = qMin(ui->image->maximumWidth(), img.width());
		int h = qMin(ui->image->maximumHeight(), img.height());

		ui->image->setPixmap(QPixmap::fromImage(img).scaled(w, h, Qt::KeepAspectRatio));

		int timeElapsed = updateStartTime.elapsed();

		msg = QString(tr("Rendering finished in %1 ms")).arg(timeElapsed);
	}
	statusBar()->showMessage(msg);
}

void MainWindow::updateImage()
{
	auto future = QtConcurrent::run(static_cast<Node*>(&output), &Node::map);
	updateStartTime.restart();
	futureWatcher.setFuture(future);
}

void MainWindow::on_actionSave_triggered()
{
	auto fileName = QFileDialog::getSaveFileName(this, "Save current map", "", tr("Image (*.png)"));
	ui->image->pixmap()->save(fileName);
}
