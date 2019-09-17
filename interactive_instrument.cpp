#include "interactive_instrument.hpp"

// TODO

InteractiveInstrument::InteractiveInstrument(const Track & track)
{
	track_ = track;
	it = track_.begin();
	fhar_ = false;
	shar_ = false;
	halted_ = false;
	velocity_ = 1000;
	attack_ = 0.0625;
	decay_ = 0.05;
	release_ = 0.05;
}

bool InteractiveInstrument::halted()
{
	if (halted_ == true)
		return true;
	else
		return false;
}

void InteractiveInstrument::enableFirstHarmonic(bool value)
{
	fhar_ = value;
}

void InteractiveInstrument::enableSecondHarmonic(bool value)
{
	shar_ = value;
}

void InteractiveInstrument::setVelocity(double value)
{
	velocity_ = value;
}

void InteractiveInstrument::setAttackTime(double value)
{
	attack_ = value;
}

void InteractiveInstrument::setDecayTime(double value)
{
	decay_ = value;
}

void InteractiveInstrument::setReleaseTime(double value)
{
	release_ = value;
}

void InteractiveInstrument::reset()
{
	fhar_ = false;
	shar_ = false;
	velocity_ = 1000;
	attack_ = 0.0625;
	decay_ = 0.05;
	release_ = 0.05;
}

double InteractiveInstrument::sample(double deltaT)
{
	if (it->isTempoEvent()) 
	{
		tempo = it->asTempoEvent().getTempo();
		M = track_.getTicksPerBeat();
		it++;
		intmax_t x = it->getTickTime();
		it--;
		s_it = realTime(x, tempo, M);

		if (deltaT < s_it) {
			return 0;
		}
		else {
			it++;
			return 0;
		}
	}
	else if (it->isNoteEvent())
	{
		intmax_t n;
		intmax_t off;
		f_it = realTime(it->getTickTime(), tempo, M);
		it++;
		s_it = realTime(it->getTickTime(), tempo, M);
		it--;

		if (samenote == false) 
		{
			if (it->asNoteEvent().getNoteOn()) {
				intmax_t tickt = (intmax_t)(it->getTickTime());
				Notes a = { it->asNoteEvent(), tickt, 0, 0, true };
				nv.push_back(a);
				samenote = true;
			}
			else {
				intmax_t tickt = (intmax_t)(it->getTickTime());
				int i = 0;
				while (i < nv.size()) {
					if (nv.at(i).note.getNoteNumber() == it->asNoteEvent().getNoteNumber()) {
						nv.at(i).tick_time_off = tickt;
						nv.at(i).onoff = false;
					}
					i++;
				}
			}
		}

		double sample = 0;
		double snote;

		if (deltaT < s_it) 
		{
			size_t k = 0;
			while (k < nv.size()) {
				double f = giveFreq(nv.at(k).note.getNoteNumber());

				int time = nv.at(k).on_time;
				double tx = time;
				double sto = (double)(tx / 44100);
				n = nv.at(k).tick_time_on;
				off = nv.at(k).tick_time_off;
				double env = envelope(sto, nv.at(k).onoff, n, off);

				if (fhar_ == false && shar_ == false) {
					snote = velocity_ * env * sin(2 * M_PI * f * sto);
				}
				else if (fhar_ == true && shar_ == false) {
					snote = velocity_ * env * (sin(2 * M_PI * f * sto) + sin(2 * M_PI * 2 * f * sto)) / 2;
				}
				else if (fhar_ == false && shar_ == true) {
					snote = velocity_ * env * (sin(2 * M_PI * f * sto) + sin(2 * M_PI * 3 * f * sto)) / 2;
				}
				else {
					snote = velocity_ * env * (sin(2 * M_PI * f * sto) + sin(2 * M_PI * 2 * f * sto) + sin(2 * M_PI * 3 * f * sto)) / 3;
				}


				time++;
				nv.at(k).on_time = time;
				sample = sample + snote;
				k++;
			}
			return sample;
		}
		else 
		{
			it++;
			samenote = false;
			if (it->isEndTrackEvent()) {
				halted_ = true;
			}
			size_t k = 0;
			while (k < nv.size()) {
				double f = giveFreq(nv.at(k).note.getNoteNumber());

				int time = nv.at(k).on_time;
				double tx = time;
				double sto = (double)(tx / 44100);

				n = nv.at(k).tick_time_on;
				off = nv.at(k).tick_time_off;
				double env = envelope(sto, nv.at(k).onoff, n, off);

				if (fhar_ == false && shar_ == false) {
					snote = velocity_ * env * sin(2 * M_PI * f * sto);
				}
				else if (fhar_ == true && shar_ == false) {
					snote = velocity_ * env * (sin(2 * M_PI * f * sto) + sin(2 * M_PI * 2 * f * sto)) / 2;
				}
				else if (fhar_ == false && shar_ == true) {
					snote = velocity_ * env * (sin(2 * M_PI * f * sto) + sin(2 * M_PI * 2 * f * sto)) / 2;
				}
				else {
					snote = velocity_ * env * (sin(2 * M_PI * f * sto) + sin(2 * M_PI * 2 * f * sto) + sin(2 * M_PI * 3 * f * sto)) / 3;
				}

				time++;
				nv.at(k).on_time = time;
				sample = sample + snote;
				k++;
			}
			return sample;
		}

	}
	else
		return 0;
}

double InteractiveInstrument::realTime(intmax_t eventtime, intmax_t tempo, intmax_t tickpbeat)
{
	double etime = (double)eventtime;
	double pay = (double)(etime * tempo);
	double x = pay / 1000000;
	double time = x / tickpbeat;
	return time;
}

double InteractiveInstrument::envelope(double t, bool notestat, intmax_t on, intmax_t off)
{
	if ((0 <= t) && (t <= attack_)) {
		return (t / attack_);
	}
	else if ( (attack_ < t) && (t <= (attack_ + decay_)) ){
		return (1 - t + attack_);
	}
	else if (((attack_ + decay_) < t) && notestat == true) {
		return 0.8;
	}
	else {
		double ont = realTime(on, tempo, M);
		double offt = realTime(off, tempo, M);
		double t3 = offt - ont;
		if ((t > t3) && (t <= (t3 + release_))) {
			double tt3 = t - t3;
			double rel = 0.8 / release_;
			double x = tt3 * rel;
			return 0.8 - x;
		}
		else
			return 0;
	}
}

double InteractiveInstrument::giveFreq(int8_t note)
{
	double freq = 0;

	double c = 261.63;
	double cp = 277.18;
	double d = 293.66;
	double dp = 311.13;
	double e = 329.63;
	double f = 349.63;
	double fp = 369.994;
	double g = 392.0;
	double gp = 415.305;
	double a = 440.0;
	double ap = 466.164;
	double b = 493.88;

	if (note == 0)  freq = c / (2 * 2 * 2 * 2 * 2);
	if (note == 1)  freq = cp / (2 * 2 * 2 * 2 * 2);
	if (note == 2)  freq = d / (2 * 2 * 2 * 2 * 2);
	if (note == 3)  freq = dp / (2 * 2 * 2 * 2 * 2);
	if (note == 4)  freq = e / (2 * 2 * 2 * 2 * 2);
	if (note == 5)  freq = f / (2 * 2 * 2 * 2 * 2);
	if (note == 6)  freq = fp / (2 * 2 * 2 * 2 * 2);
	if (note == 7)  freq = g / (2 * 2 * 2 * 2 * 2);
	if (note == 8)  freq = gp / (2 * 2 * 2 * 2 * 2);
	if (note == 9)  freq = a / (2 * 2 * 2 * 2 * 2);
	if (note == 10)  freq = ap / (2 * 2 * 2 * 2 * 2);
	if (note == 11)  freq = b / (2 * 2 * 2 * 2 * 2);

	if (note == 12)  freq = c / (2 * 2 * 2 * 2);
	if (note == 13)  freq = cp / (2 * 2 * 2 * 2);
	if (note == 14)  freq = d / (2 * 2 * 2 * 2);
	if (note == 15)  freq = dp / (2 * 2 * 2 * 2);
	if (note == 16)  freq = e / (2 * 2 * 2 * 2);
	if (note == 17)  freq = f / (2 * 2 * 2 * 2);
	if (note == 18)  freq = fp / (2 * 2 * 2 * 2);
	if (note == 19)  freq = g / (2 * 2 * 2 * 2);
	if (note == 20)  freq = gp / (2 * 2 * 2 * 2);
	if (note == 21)  freq = a / (2 * 2 * 2 * 2);
	if (note == 22)  freq = ap / (2 * 2 * 2 * 2);
	if (note == 23)  freq = b / (2 * 2 * 2 * 2);

	if (note == 24)  freq = c / (2 * 2 * 2);
	if (note == 25)  freq = cp / (2 * 2 * 2);
	if (note == 26)  freq = d / (2 * 2 * 2);
	if (note == 27)  freq = dp / (2 * 2 * 2);
	if (note == 28)  freq = e / (2 * 2 * 2);
	if (note == 29)  freq = f / (2 * 2 * 2);
	if (note == 30)  freq = fp / (2 * 2 * 2);
	if (note == 31)  freq = g / (2 * 2 * 2);
	if (note == 32)  freq = gp / (2 * 2 * 2);
	if (note == 33)  freq = a / (2 * 2 * 2);
	if (note == 34)  freq = ap / (2 * 2 * 2);
	if (note == 35)  freq = b / (2 * 2 * 2);

	if (note == 36)  freq = c / (2 * 2);
	if (note == 37)  freq = cp / (2 * 2);
	if (note == 38)  freq = d / (2 * 2);
	if (note == 39)  freq = dp / (2 * 2);
	if (note == 40)  freq = e / (2 * 2);
	if (note == 41)  freq = f / (2 * 2);
	if (note == 42)  freq = fp / (2 * 2);
	if (note == 43)  freq = g / (2 * 2);
	if (note == 44)  freq = gp / (2 * 2);
	if (note == 45)  freq = a / (2 * 2);
	if (note == 46)  freq = ap / (2 * 2);
	if (note == 47)  freq = b / (2 * 2);

	if (note == 48)  freq = c / 2;
	if (note == 49)  freq = cp / 2;
	if (note == 50)  freq = d / 2;
	if (note == 51)  freq = dp / 2;
	if (note == 52)  freq = e / 2;
	if (note == 53)  freq = f / 2;
	if (note == 54)  freq = fp / 2;
	if (note == 55)  freq = g / 2;
	if (note == 56)  freq = gp / 2;
	if (note == 57)  freq = a / 2;
	if (note == 58)  freq = ap / 2;
	if (note == 59)  freq = b / 2;

	//////////////////////////////////////////////
	if (note == 60)  freq = 261.63;
	if (note == 61)  freq = 277.18;
	if (note == 62)  freq = 293.66;
	if (note == 63)  freq = 311.13;
	if (note == 64)  freq = 329.63;
	if (note == 65)  freq = 349.63;
	if (note == 66)  freq = 369.994;
	if (note == 67)  freq = 392.0;
	if (note == 68)  freq = 415.305;
	if (note == 69)  freq = 440.0;
	if (note == 70)  freq = 466.164;
	if (note == 71)  freq = 493.88;
	//////////////////////////////////////////////
	if (note == 72)  freq = c * 2;
	if (note == 73)  freq = cp * 2;
	if (note == 74)  freq = d * 2;
	if (note == 75)  freq = dp * 2;
	if (note == 76)  freq = e * 2;
	if (note == 77)  freq = f * 2;
	if (note == 78)  freq = fp * 2;
	if (note == 79)  freq = g * 2;
	if (note == 80)  freq = gp * 2;
	if (note == 81)  freq = a * 2;
	if (note == 82)  freq = ap * 2;
	if (note == 83)  freq = b * 2;

	if (note == 84)  freq = c * 2 * 2;
	if (note == 85)  freq = cp * 2 * 2;
	if (note == 86)  freq = d * 2 * 2;
	if (note == 87)  freq = dp * 2 * 2;
	if (note == 88)  freq = e * 2 * 2;
	if (note == 89)  freq = f * 2 * 2;
	if (note == 90)  freq = fp * 2 * 2;
	if (note == 91)  freq = g * 2 * 2;
	if (note == 92)  freq = gp * 2 * 2;
	if (note == 93)  freq = a * 2 * 2;
	if (note == 94)  freq = ap * 2 * 2;
	if (note == 95)  freq = b * 2 * 2;

	if (note == 96)  freq = c * 2 * 2 * 2;
	if (note == 97)  freq = cp * 2 * 2 * 2;
	if (note == 98)  freq = d * 2 * 2 * 2;
	if (note == 99)  freq = dp * 2 * 2 * 2;
	if (note == 100)  freq = e * 2 * 2 * 2;
	if (note == 101)  freq = f * 2 * 2 * 2;
	if (note == 102)  freq = fp * 2 * 2 * 2;
	if (note == 103)  freq = g * 2 * 2 * 2;
	if (note == 104)  freq = gp * 2 * 2 * 2;
	if (note == 105)  freq = a * 2 * 2 * 2;
	if (note == 106)  freq = ap * 2 * 2 * 2;
	if (note == 107)  freq = b * 2 * 2 * 2;

	if (note == 108)  freq = c * 2 * 2 * 2 * 2;
	if (note == 109)  freq = cp * 2 * 2 * 2 * 2;
	if (note == 110)  freq = d * 2 * 2 * 2 * 2;
	if (note == 111)  freq = dp * 2 * 2 * 2 * 2;
	if (note == 112)  freq = e * 2 * 2 * 2 * 2;
	if (note == 113)  freq = f * 2 * 2 * 2 * 2;
	if (note == 114)  freq = fp * 2 * 2 * 2 * 2;
	if (note == 115)  freq = g * 2 * 2 * 2 * 2;
	if (note == 116)  freq = gp * 2 * 2 * 2 * 2;
	if (note == 117)  freq = a * 2 * 2 * 2 * 2;
	if (note == 118)  freq = ap * 2 * 2 * 2 * 2;
	if (note == 119)  freq = b * 2 * 2 * 2 * 2;

	if (note == 120)  freq = c * 2 * 2 * 2 * 2 * 2;
	if (note == 121)  freq = cp * 2 * 2 * 2 * 2 * 2;
	if (note == 122)  freq = d * 2 * 2 * 2 * 2 * 2;
	if (note == 123)  freq = dp * 2 * 2 * 2 * 2 * 2;
	if (note == 124)  freq = e * 2 * 2 * 2 * 2 * 2;
	if (note == 125)  freq = f * 2 * 2 * 2 * 2 * 2;
	if (note == 126)  freq = fp * 2 * 2 * 2 * 2 * 2;
	if (note == 127)  freq = g * 2 * 2 * 2 * 2 * 2;

	return freq;
}
