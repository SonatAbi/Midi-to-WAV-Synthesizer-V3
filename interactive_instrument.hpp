/** \file The InteractiveInstrument Module
 */
#ifndef INTERACTIVE_INSTRUMENT_HPP
#define INTERACTIVE_INSTRUMENT_HPP

#include "event.hpp"
#include "track.hpp"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>

using namespace std;

/** The interactive instrument.
 */
class InteractiveInstrument{
public:

  /** No default constructor. A InteractiveInstrument must have an associated 
   * track. 
   */
  InteractiveInstrument() = delete;

  /** Cannot be copied. 
   */
  InteractiveInstrument(const InteractiveInstrument & ) = delete;

  /** Cannot be assigned.
   */
  InteractiveInstrument & operator=(const InteractiveInstrument & ) = delete;

  /** Construct a Interactive Instrument using the specified track.
   * \param track the track to read events from. 
   */
  InteractiveInstrument(const Track & track);

  /** Returns true of the InteractiveInstrument has stopped processing events.
   * This can occu e.g. if all events have been consumed or a EndTrackEvent
   * has been processed.
   */
  bool halted();

  /** Enables the addition of a first harmonic to the instrument notes 
   * \param value true if enabled, false if not
   */
  void enableFirstHarmonic(bool value);

  /** Enables the addition of a second harmonic to the instrument notes 
   * \param value true if enabled, false if not
   */
  void enableSecondHarmonic(bool value);

  /** Sets the velocity of the notes.
   * \param value the new velocity
   */
  void setVelocity(double value);

  /** Sets the attack time of the envelope function.
   * \param value the new attack time
   */
  void setAttackTime(double value);

  /** Sets the decay time of the envelope function.
   * \param value the new decay time
   */
  void setDecayTime(double value);

  /** Sets the release time of the envelope function.
   * \param value the new release time
   */
  void setReleaseTime(double value);

  /** Resets the instrument to a default state.*/
  void reset();
  
  /** Return the sample after the (real) time increment. Samples the 
   * instrument based on its state after processing all events prior 
   * to this time.
   * \param deltaT the time increment in seconds.
   */
  double sample(double deltaT);

private:
	Track track_;
	Track::ConstIteratorType it;
	bool halted_;
	bool fhar_;
	bool shar_;
	double velocity_;
	double attack_;
	double decay_;
	double release_;

	intmax_t tempo;
	intmax_t M;
	double f_it;
	double s_it;
	bool samenote = false;

	double realTime(intmax_t eventtime, intmax_t tempo, intmax_t tickpbeat);
	double envelope(double t, bool notestat, intmax_t on, intmax_t off);
	double giveFreq(int8_t note);

	struct Notes {
		NoteEvent note;
		intmax_t tick_time_on;
		intmax_t tick_time_off;
		int on_time;
		bool onoff;
	};
	std::vector<Notes> nv;
};


#endif
