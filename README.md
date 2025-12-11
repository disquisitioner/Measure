# Measure

Many of my projects involve reading data from a connected sensor or data 
source, keeping track of maximum and minimum values observed, calculating 
averages or counts of results and sometimes graphing recently recorded 
values. I found I was writing the same code over and over, and at one 
point created a [template application](https://github.com/disquisitioner/SensorHelper) to use for deailng with sensors.

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
