/*
 * Measure.h - Library to help manage accumulating data from sensors or similar sources
 * Author: David Bryant <david@disquiry.com>
 * Version: 0.9.0
 * Date: January 17, 2026
 */

#ifndef MEASURE_HPP
#define MEASURE_HPP

#include <Arduino.h>

/*
 * Define Measure as a C++ template so the size of the retained data buffer can
 * be specified at the time an instance of the templated class is created.
*/
template <uint16_t retained = 1> // Defaults to 1 retained storage location
class Measure {
  public:
    void begin() {
      // Initialization function, which might not be necessary (TODO)
      int i;
      for(i=0;i<_capacity;i++) {
        _values[i] = 0.0;
      }
    }
    // Get the retained value at a particular index. Note that the retention buffer
    // is managed such that the mostly recently included value is at the last location
    // in the buffer, with prior values in reverse chronological order from the
    // end towards the beginning.
    // TODO: Currently returns value at location in retatined storage whether
    //       actual included data is there or not. Could enhance to return an
    //       out-of-range or error indicator if referencing an unincluded location.
    float getMember(int index) {
      // Avoid out-of-range index requests
      if(index < 0) return _values[0];
      if(index >= _capacity) return _values[_capacity-1];
      return _values[index];
    }

    // Get the current (most recently retained) value
    float getCurrent() {
      return _values[_capacity-1];
    }

    // Get the size of the internal retention buffer
    uint16_t getCapacity() {
      return _capacity;
    }

    // Returns the number of values held in the retention buffer.
    uint16_t getStored() {
      return _stored;
    }

    // Completely resets all accumulation processing and associated calculations
    // (e.g., max, min, average, count, total) so that the next included value
    // will restart those operations.
    // NOTE: This does not discard retained values. Use the deleteRetained() method
    //       to do that.
    void clear() {
      _total = _average = 0;
      _count = 0;
      _maxvalue = _minvalue = 0.0;
      _new_min_max = true;


    }

    // resetAvg() clears the value, total, count and average but leaves the min
    // and max values unmodified.  Use resetAvg() to reset the cumulative averaging
    // behavior, e.g., to begin a new sampling interval, but leave the 
    // longer term observed max/min values alone.
    // NOTE: This does not discard retained values. Use the deleteRetained() method
    //       to do that.
    void resetAvg() {
      _total = _average = 0.0;
      _count = 0;
    }

    // Discard all retained values and reset the retention counter to zero. This
    // doesn't happen automatically as part of clear() or resetAvg() to let the
    // application decide whether/when to abandon retained values as they might
    // be used separately from reporting average/min/max (e.g., for graphing).
    void deleteRetained() {
      int i;
      // Clear retained values by zeroing them
      for(i=0;i<_capacity;i++) _values[i] = 0.0;
      _stored = 0;
    }

    uint32_t getCount() {
      return _count;
    }

    float getTotal() {
      return _total;
    }

    float getMax() {
      return _maxvalue;
    }

    float getMin() {
      return _minvalue;
    }

    float getAverage() {
      return _average;
    }

    void include(float newvalue) {
      int i;

      // Handle aggregation functionality for the new value
      _count++; // started with 0
      _total += newvalue;
      if(_new_min_max == true) {
        _maxvalue = _minvalue = newvalue;
        _new_min_max = false;
      }
      else {
        if(newvalue > _maxvalue) _maxvalue = newvalue;
        if(newvalue < _minvalue) _minvalue = newvalue;
      }
      _average = _total / _count;

      // If only retaining one value, just store it
      if(_capacity == 1) {
        _values[0] = newvalue;
        _stored = 1;
      }
      else {
        // Otherwise shift stored values to make room for newest one...
        for(i=(_capacity - _stored - 2);i < _capacity-1;i++) {
          _values[i] = _values[i+1];
        }
        // ...and store the newest value
        _values[_capacity-1] = newvalue;
        if(_stored < _capacity) _stored++;
      }
    }

    void printRetained() {
      int i;
      Serial.print("["); Serial.print(_stored);
      Serial.print(" of "); Serial.print(_capacity);
      Serial.print("]:(");
      for(i=(_capacity - _stored);i < _capacity;i++) {
        if(i!=(_capacity - _stored)) Serial.print(",");
        Serial.print(_values[i]);
      }
      Serial.println(")");
    }
  
  private:
    float _values[retained]; // Internal retention buffer
    uint16_t _capacity = retained; // Size of internal retention buffer
    uint16_t _stored = 0;  // Number of values retained in internal buffer
    uint32_t _count;  // Number of values included since last clear/reset
    float _total = 0;
    float _maxvalue = 0;
    float _minvalue = 0;
    float _average = 0;
    bool _new_min_max = true;
};

#endif // MEASURE_H