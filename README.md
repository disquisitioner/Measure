# Measure

Many of my projects involve reading data from a connected sensor or data 
source, keeping track of maximum and minimum values observed, calculating 
averages or counts of results and sometimes graphing recently recorded 
values. I found I was writing the same code over and over, and at one 
point created a [template application](https://github.com/disquisitioner/SensorHelper) to use for dealing with sensors.

One piece of that SensorHelper template has proven useful in a number of 
other projects, and that's the Measure utility class that streamlines 
accumulating and reporting collected sensor values. This repository lets 
Measure have a life of its own.

A part of that desire for independence is work I've done recently to 
leverage C++ templates so Measure can include its own retained storage 
for recent values and have that storage configured at the time an instance 
of the class is declared. Check out the included example application to see 
how that's done and to get familiar with other capabilities of the Measure 
class.

## Using the Measure class

### Declaration

`Measure<size> InstanceObject;`  
Declares `InstanceObject` as an instance of the Measure class, with internal retained storage for `size` values (with `size` as an integer).

### API

The **Measure** object class provides the following public functions. Note that all sensor values to be handled are processed as floating point numbers, which may not correspond to values returned from those sensor but should work for all cases and keeps things simple.


`void include(float value)`  
Adds numeric `value` to the accumulation.  

`float getMax()`  
Returns the maximum value included in the Measure thus far.  Maximum value tracking can be reset with the `clear()` function (see below).

`float getMin()`  
Returns the minimum value included in the Measure thus far.  Minimum tracking can be reset with the `clear()` function (see below).

`float getAverage()`  
Returns the average of all values included in the Measure thus far.  Average tracking can be reset with either the `resetAverage()` function, which just resets running average calculation, or the `clear()` function (see below).

`float getCurrent()`  
Returns the most recent retained value in the Measure accumulation.

`float getTotal()`  
Returns the running sum of all values included in the Measure thus far.

`uint32_t getCount()`  
Returns the number of values included in the Measure since it was created or most recently cleared.

`void resetAverage()`  
Resets the running average calculation by clearing the count, total, and average values as well as the most recently included (current) value. Does not reset 
tracking of maximum and minimum included values so only the averaging process is
impacted. To reset averaging and also reset maximum and minimum tracking use the `clear()` function. Also does not clear or impact values in retained storage. To delete all retained values use the `deleteRetained()` function.

`void clear()`  
Clears average, maximum, minimum, total, and count metrics for the Measure, effectively returning those operations to an unused initial state. Does not remove or otherwise alter values held in retained storage. To delete all retained values use the 'deleteRetained()` function.

`uint16_t getCapacity()`  
Returns the size of the internal retained storage, which was set when the Measure instance was declared (see above).

`uint16_t getStored()`  
Returns the number of values inserted into retained storage (via the `include()` method described above).

`float getMember(int index)`  
Returns the value in retained storage at location `index`.  Note that retained storage is managed as a "most recent last" array, with the most recently included value in the last location. It may help to think of retained storage as a chart recorder in which the most recent value is always at the end of retained storage with older values stored in reverse time order towards the beginning of the storage array.  Put another way, retained storage holds (at most) the most recent `size` values, where `size` is the value given when the Measure instance was created.

`void deleteRetained()`
Deletes all values held in the Member object's retained storage and sets the count of retained values to zero.  Use this to reset the accumulation of included values. Values deleted cannot be recovered.  The separation of behaviors for `clear()`, `resetAverage()`, and `deleteRetained()` is to allow full control of managing running calculation of average, minimum, and maximum values as well as the presumably separate retention of recent values (as might be essential for graphing or otherwise post-processing retained data).
