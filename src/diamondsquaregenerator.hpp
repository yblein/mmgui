#ifndef DIAMONDSQUAREGENERATOR_HPP
#define DIAMONDSQUAREGENERATOR_HPP

#include "src/generator.hpp"

#include <mm/diamond_square.h>

#include <QDialog>

namespace Ui {
class DiamondSquareGenerator;
}
class Map;

class DiamondSquareGenerator : private QDialog, public Generator
{
	Q_OBJECT

public:
	DiamondSquareGenerator(QWidget *parent = 0);
	virtual ~DiamondSquareGenerator();

	virtual void generate(Map *output);
	virtual bool configure();

private slots:
	void on_buttonBox_accepted();

private:
	Ui::DiamondSquareGenerator *ui;
	mm::random_engine engine_;
	mm::diamond_square diamondSquare_;
	size_t width_;
	size_t height_;
};

#endif // DIAMONDSQUAREGENERATOR_HPP
