#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "outputnode.hpp"

#include <mm/heightmap.h>

#include <QMainWindow>
#include <QFutureWatcher>
#include <QTime>

namespace Ui {
class MainWindow;
}

class ControlScene;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionNewFractalGen_triggered();
	void on_actionNewFilterIslandize_triggered();
	void on_actionFlatten_triggered();
	void on_actionSmooth_triggered();
	void on_actionColorize_triggered();

	void renderingFinished();
	void renderingStarted();

	void on_actionConstant_triggered();

private:
	typedef QFutureWatcher<const Map*> FutureWatcherMap;

	void updateImage();

	Ui::MainWindow *ui;

	ControlScene *scene;

	OutputNode output;

	QTime updateStartTime;
	FutureWatcherMap futureWatcher;
};

#endif // MAINWINDOW_H
