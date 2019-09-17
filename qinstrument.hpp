#ifndef QINSTRUMENT_HPP
#define QINSTRUMENT_HPP

#include <QWidget>
#include <QState>
#include <QObject>
#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <fstream>
#include "interactive_instrument.hpp"
#include "midi.hpp"
#include "signal.hpp"
#include "wav.hpp"

using namespace std;

class QInstrument: public QWidget {
	Q_OBJECT

public:
	QInstrument(QWidget * parent = nullptr);
	bool firstH();
	bool secondH();
	double v();
	double a();
	double d();
	double r();
	string i();
	string o();


private slots:
	void updateVel();
	void updateAtt();
	void updateDec();
	void updateRel();
	void getinput();
	void getminput();
	void getoutput();
	void getmoutput();
	void synthesize();

private:
	double vel;
	double att;
	double dec;
	double rel;

	QString inpfile;
	std::string inpstring;
	QString outfile;
	std::string outstring;
	//Instrument Parameter Variables
	QGroupBox * insPar;
	QGridLayout * insLayout;
	QCheckBox * firstHar;
	QCheckBox * secondHar;
	QDoubleSpinBox * velocity;
	QDoubleSpinBox * attackTime;
	QDoubleSpinBox * decayTime;
	QDoubleSpinBox * relTime;

	//MIDI Input Variables
	QGroupBox *midiInput;
	QGridLayout *inpLayout;
	QLineEdit *input;
	QPushButton *inpbrowse;

	//MIDI Input Variables
	QGroupBox *midiOut;
	QGridLayout *outLayout;
	QLineEdit *output;
	QPushButton *outbrowse;

	QPushButton *synth;
	

};


#endif
