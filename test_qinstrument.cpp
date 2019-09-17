#include <QTest>

#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTest>
#include <QString>

#include "qinstrument.hpp"
#include "test_config.hpp"

class TestQInstrument : public QObject {
  Q_OBJECT

private slots:

  void initTestCase();
  void testhar1();
  void testhar2();
  void velocity();
  void attack();
  void decay();
  void release();
  void input();
  void output();
  void compare();

private:

  QInstrument widget;
};

void TestQInstrument::initTestCase(){

	{
		auto w = widget.findChild<QCheckBox *>("harmonic1");
		QVERIFY2(w, "Could not find first harmonic button");
	}

	{
		auto w = widget.findChild<QCheckBox *>("harmonic2");
		QVERIFY2(w, "Could not find second harmonic button");
	}

	{
		auto w = widget.findChild<QDoubleSpinBox *>("velocity");
		QVERIFY2(w, "Could not find velocity edit widget");
	}

	{
		auto w = widget.findChild<QDoubleSpinBox *>("attack");
		QVERIFY2(w, "Could not find attack edit widget");
	}

	{
		auto w = widget.findChild<QDoubleSpinBox *>("decay");
		QVERIFY2(w, "Could not find decay edit widget");
	}

	{
		auto w = widget.findChild<QDoubleSpinBox *>("release");
		QVERIFY2(w, "Could not find release edit widget");
	}


	{
		auto w = widget.findChild<QLineEdit *>("inputpath");
		QVERIFY2(w, "Could not find a QLineEdit widget");
	}

	{
		auto w = widget.findChild<QLineEdit *>("outputpath");
		QVERIFY2(w, "Could not find a QLineEdit widget");
	}

	{
		auto w = widget.findChild<QPushButton *>("synth");
		QVERIFY2(w, "Could not find synthesizer button");
	}
}

QTEST_MAIN(TestQInstrument)
#include "test_qinstrument.moc"

void TestQInstrument::testhar1()
{
	auto a = widget.findChild<QCheckBox *>("harmonic1");
	QVERIFY2(!widget.firstH(), "harmonic 1 is wrong");
	a->setChecked(true);
	QVERIFY2(widget.firstH(), "harmonic 1 is wrong");
	a->setChecked(false);
	QVERIFY2(!widget.firstH(), "harmonic 1 is wrong");
}

void TestQInstrument::testhar2()
{
	auto a = widget.findChild<QCheckBox *>("harmonic2");
	QVERIFY2(!widget.secondH(), "harmonic 2 is wrong");
	a->setChecked(true);
	QVERIFY2(widget.secondH(), "harmonic 2 is wrong");
	a->setChecked(false);
	QVERIFY2(!widget.secondH(), "harmonic 2 is wrong");
}

void TestQInstrument::velocity()
{
	auto a = widget.findChild<QDoubleSpinBox *>("velocity");
	a->setValue(0.25);
	QVERIFY2(widget.v() == 0.25, "velocity is wrong");
	a->setValue(0.51);
	QVERIFY2(widget.v() == 0.51, "velocity is wrong");
	a->setValue(0.1);
	QVERIFY2(widget.v() == 0.1, "velocity is wrong");
}

void TestQInstrument::attack()
{
	auto a = widget.findChild<QDoubleSpinBox *>("attack");
	a->setValue(0.4);
	QVERIFY2(widget.a() == 0.4, "attack is wrong");
	a->setValue(0.78);
	QVERIFY2(widget.a() == 0.78, "attack is wrong");
	a->setValue(0.2);
	QVERIFY2(widget.a() == 0.2, "attack is wrong");
}

void TestQInstrument::decay()
{
	auto a = widget.findChild<QDoubleSpinBox *>("decay");
	a->setValue(0.31);
	QVERIFY2(widget.d() == 0.31, "decay is wrong");
	a->setValue(0.69);
	QVERIFY2(widget.d() == 0.69, "decay is wrong");
	a->setValue(0.82);
	QVERIFY2(widget.d() == 0.82, "decay is wrong");
}

void TestQInstrument::release()
{
	auto a = widget.findChild<QDoubleSpinBox *>("release");
	a->setValue(0.11);
	QVERIFY2(widget.r() == 0.11, "release is wrong");
	a->setValue(0.29);
	QVERIFY2(widget.r() == 0.29, "release is wrong");
	a->setValue(0.33);
	QVERIFY2(widget.r() == 0.33, "release is wrong");
}

void TestQInstrument::input()
{
	auto a = widget.findChild<QLineEdit *>("inputpath");
	a->setText("trolololololol");
	QVERIFY2(widget.i() == "trolololololol" , "input is wrong");
	a->setText("hohohoho");
	QVERIFY2(widget.i() == "hohohoho", "input is wrong");
	a->setText("asdf");
	QVERIFY2(widget.i() == "asdf", "input is wrong");
}

void TestQInstrument::output()
{
	auto a = widget.findChild<QLineEdit *>("outputpath");
	a->setText("trolololololol");
	QVERIFY2(widget.o() == "trolololololol", "input is wrong");
	a->setText("hohohoho");
	QVERIFY2(widget.o() == "hohohoho", "input is wrong");
	a->setText("asdf");
	QVERIFY2(widget.o() == "asdf", "input is wrong");
}

void TestQInstrument::compare()
{
	auto a = widget.findChild<QLineEdit *>("inputpath");
	string inp = TEST_FILE_DIR + "/test00.mid";
	QString qinp = QString::fromStdString(inp);
	a->setText(qinp);
	auto b = widget.findChild<QLineEdit *>("outputpath");
	string out = TEST_FILE_DIR + "/test1";
	QString qout = QString::fromStdString(out);
	b->setText(qout);
	auto c = widget.findChild<QPushButton *>("synth");
	QTest::mouseClick(c, Qt::LeftButton);
	
	auto d = widget.findChild<QCheckBox *>("harmonic1");
	d->setChecked(true);
	out = TEST_FILE_DIR + "/test2";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(false);
	auto e = widget.findChild<QCheckBox *>("harmonic2");
	e->setChecked(true);
	out = TEST_FILE_DIR + "/test3";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(true);
	out = TEST_FILE_DIR + "/test4";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);
	/////////////////////////////////////////test01.mid
	d->setChecked(false);
	e->setChecked(false);
	inp = TEST_FILE_DIR + "/test01.mid";
	qinp = QString::fromStdString(inp);
	a->setText(qinp);
	out = TEST_FILE_DIR + "/test5";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(true);
	out = TEST_FILE_DIR + "/test6";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(false);
	e->setChecked(true);
	out = TEST_FILE_DIR + "/test7";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(true);
	out = TEST_FILE_DIR + "/test8";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);
	/////////////////////////////////////////test02.mid
	d->setChecked(false);
	e->setChecked(false);
	inp = TEST_FILE_DIR + "/test02.mid";
	qinp = QString::fromStdString(inp);
	a->setText(qinp);
	out = TEST_FILE_DIR + "/test9";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(true);
	out = TEST_FILE_DIR + "/test10";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(false);
	e->setChecked(true);
	out = TEST_FILE_DIR + "/test11";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(true);
	out = TEST_FILE_DIR + "/test12";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);
	/////////////////////////////////////////test03.mid
	d->setChecked(false);
	e->setChecked(false);
	inp = TEST_FILE_DIR + "/test03.mid";
	qinp = QString::fromStdString(inp);
	a->setText(qinp);
	out = TEST_FILE_DIR + "/test13";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(true);
	out = TEST_FILE_DIR + "/test14";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(false);
	e->setChecked(true);
	out = TEST_FILE_DIR + "/test15";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(true);
	out = TEST_FILE_DIR + "/test16";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);
	/////////////////////////////////////////test04.mid
	d->setChecked(false);
	e->setChecked(false);
	inp = TEST_FILE_DIR + "/test04.mid";
	qinp = QString::fromStdString(inp);
	a->setText(qinp);
	out = TEST_FILE_DIR + "/test17";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(true);
	out = TEST_FILE_DIR + "/test18";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(false);
	e->setChecked(true);
	out = TEST_FILE_DIR + "/test19";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(true);
	out = TEST_FILE_DIR + "/test20";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	auto f = widget.findChild<QDoubleSpinBox *>("attack");
	auto g = widget.findChild<QDoubleSpinBox *>("decay");
	auto h = widget.findChild<QDoubleSpinBox *>("release");
	f->setValue(0.25);
	g->setValue(0.2);
	h->setValue(0.2);
	out = TEST_FILE_DIR + "/test21";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);

	d->setChecked(false);
	e->setChecked(false);
	f->setValue(0.0625);
	g->setValue(0.05);
	h->setValue(0.05);
	auto j = widget.findChild<QDoubleSpinBox *>("velocity");
	j->setValue(4000);
	out = TEST_FILE_DIR + "/test22";
	qout = QString::fromStdString(out);
	b->setText(qout);
	QTest::mouseClick(c, Qt::LeftButton);
	QVERIFY2(widget.v() == 4000 , "velocity is wrong");
}
