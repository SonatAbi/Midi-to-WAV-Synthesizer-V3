#include "qinstrument.hpp"
#include <QWidget>
#include <QLayout>
#include <QRadioButton>

QInstrument::QInstrument(QWidget * parent) : QWidget(parent) {

	QGridLayout *layout = new QGridLayout;//Main Layout

	/*Instrument Parameters*/
	insPar = new QGroupBox(tr("Instrument Parameters"));
	firstHar = new QCheckBox("Enable First Harmonic");
	firstHar->setObjectName("harmonic1");
	firstHar->setEnabled(true);
	secondHar = new QCheckBox("Enable Second Harmonic");
	secondHar->setEnabled(true);
	secondHar->setObjectName("harmonic2");

	velocity = new QDoubleSpinBox;
	velocity->setObjectName("velocity");
	velocity->setMaximum(100000);
	velocity->setMinimum(0);
	velocity->setValue(1000);
	vel = 1000;
	connect(velocity, SIGNAL(valueChanged(double)),this, SLOT(updateVel()));

	attackTime = new QDoubleSpinBox;
	attackTime->setObjectName("attack");
	attackTime->setDecimals(6);
	attackTime->setMaximum(1);
	attackTime->setMinimum(0);
	attackTime->setValue(0.0625);
	att = 0.0625;
	connect(attackTime, SIGNAL(valueChanged(double)), this, SLOT(updateAtt()));

	decayTime = new QDoubleSpinBox;
	decayTime->setObjectName("decay");
	decayTime->setDecimals(6);
	decayTime->setMaximum(1);
	decayTime->setMinimum(0);
	decayTime->setValue(0.05);
	dec = 0.05;
	connect(decayTime, SIGNAL(valueChanged(double)), this, SLOT(updateDec()));

	relTime = new QDoubleSpinBox;
	relTime->setObjectName("release");
	relTime->setDecimals(6);
	relTime->setMaximum(1);
	relTime->setMinimum(0);
	relTime->setValue(0.05);
	rel = 0.05;
	connect(relTime, SIGNAL(valueChanged(double)), this, SLOT(updateRel()));

	insLayout = new QGridLayout;
	insLayout->addWidget(firstHar, 0, 0);
	insLayout->addWidget(secondHar, 0, 1);
	insLayout->addWidget(new QLabel(tr("Velocity:"), this), 1, 0);
	insLayout->addWidget(velocity, 1, 1);
	insLayout->addWidget(new QLabel(tr("Attack Time(s):"), this), 2, 0);
	insLayout->addWidget(attackTime, 2, 1);
	insLayout->addWidget(new QLabel(tr("Decay Time(s):"), this), 3, 0);
	insLayout->addWidget(decayTime, 3, 1);
	insLayout->addWidget(new QLabel(tr("Release Time(s):"), this), 4, 0);
	insLayout->addWidget(relTime, 4, 1);
	insPar->setLayout(insLayout);
	
	/**********************************************************************/

	/*MIDI Input*/
	midiInput = new QGroupBox(tr("MIDI Input"));
	input = new QLineEdit;
	input->setObjectName("inputpath");
	inpbrowse = new QPushButton("Browse");
	connect(inpbrowse, SIGNAL(clicked()), this, SLOT(getinput()));
	connect(input, SIGNAL(textChanged(QString)), this, SLOT(getminput()));

	inpLayout = new QGridLayout;
	inpLayout->addWidget(input, 0, 0);
	inpLayout->addWidget(inpbrowse, 0, 1);
	midiInput->setLayout(inpLayout);

	/**********************************************************************/

	/*MIDI Output*/
	midiOut = new QGroupBox(tr("MIDI Output"));
	output = new QLineEdit;
	output->setObjectName("outputpath");
	outbrowse = new QPushButton("Browse");
	connect(outbrowse, SIGNAL(clicked()), this, SLOT(getoutput()));
	connect(output, SIGNAL(textChanged(QString)), this, SLOT(getmoutput()));

	outLayout = new QGridLayout;
	outLayout->addWidget(output, 0, 0);
	outLayout->addWidget(outbrowse, 0, 1);
	midiOut->setLayout(outLayout);
	/**********************************************************************/

	/*Synthesize*/
	synth = new QPushButton("Synthesize");
	synth->setObjectName("synth");
	connect(synth, SIGNAL(clicked()), this, SLOT(synthesize()));
	/**********************************************************************/

	layout->addWidget(insPar);
	layout->addWidget(midiInput);
	layout->addWidget(midiOut);
	layout->addWidget(synth);
	setLayout(layout);

}

void QInstrument::updateVel() {
	vel = velocity->value();
}

void QInstrument::updateAtt()
{
	att = attackTime->value();
}

void QInstrument::updateDec()
{
	dec = decayTime->value();
}

void QInstrument::updateRel()
{
	rel = relTime->value();
}

void QInstrument::getinput()
{
	inpfile = QFileDialog::getOpenFileName(this, QDir::currentPath());
	input->setText(inpfile);
	inpstring = inpfile.toStdString();
}

void QInstrument::getminput()
{
	inpfile = input->text();
	inpstring = inpfile.toStdString();
}

void QInstrument::getoutput()
{
	outfile = QFileDialog::getOpenFileName(this, QDir::currentPath());
	output->setText(outfile);
	outstring = outfile.toStdString();
}

void QInstrument::getmoutput()
{
	outfile = output->text();
	outstring = outfile.toStdString();
}

void QInstrument::synthesize()
{
	TrackListType tracklist = readMIDIFromFile(inpstring);
	Track t = tracklist.front();
	InteractiveInstrument ins(t);
	ins.setVelocity(v());
	ins.setAttackTime(a());
	ins.setDecayTime(d());
	ins.setReleaseTime(r());
	ins.enableFirstHarmonic(firstH());
	ins.enableSecondHarmonic(secondH());
	Signal curr(44100);
	double samp = 0;
	double n = 0;

	int samprate = curr.getSampleRate();
	while (!ins.halted()) {
		double delta = n / samprate;
		samp = ins.sample(delta);
		curr.push_back(samp);
		n = n + 1;
	}
	curr.normalize();
	write_wav(curr, outstring);
}

bool QInstrument::firstH()
{
	if (firstHar->isChecked())
		return true;
	else
		return false;
}

bool QInstrument::secondH()
{
	if (secondHar->isChecked())
		return true;
	else 
		return false;
}

double QInstrument::v()
{
	return vel;
}

double QInstrument::a()
{
	return att;
}

double QInstrument::d()
{
	return dec;
}

double QInstrument::r()
{
	return rel;
}

string QInstrument::i()
{
	return inpstring;
}

string QInstrument::o()
{
	return outstring;
}



