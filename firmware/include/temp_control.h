#ifndef TEMP_CONTROL_H
#define TEMP_CONTROL_H

#include <Arduino.h>

#include <vector>

#define HEATUP true
#define COOLDOWN false

class TempStep {
 public:
  TempStep(const char* label, bool heatup, double targetTemp, long duration, double kP = 1.0)
      : duration(duration), heatup(heatup), targetTemp(targetTemp), label(label), kP(kP) {
    reachedMillis = 0;
  }
  long duration;
  double targetTemp;
  const char* label;
  bool heatup;
  long reachedMillis;
  double kP;
};

class TempControl {
 public:
  TempControl() {}
  void add(TempStep* step) { this->steps.push_back(step); }

  void start() {
    stepIndex = 0;
    running = true;
    for (int i = 0; i < steps.size(); i++) {
      steps[i]->reachedMillis = 0;
    }
  }
  void stop() { running = false; }

  double getProgress() {
    if (!running || stepIndex >= steps.size()) {
      return 100;
    }
    double totalMillis = 0;
    for (int i = 0; i < steps.size(); i++) {
      totalMillis += steps[i]->duration;
    }

    double elapsedMillis = 0;
    for (int i = 0; i < stepIndex; i++) {
      elapsedMillis += steps[i]->duration;
    }
    // current step progress (0 if not reached)
    long stepElapsed = steps[stepIndex]->reachedMillis ? millis() - steps[stepIndex]->reachedMillis : 0;
    // catch overrun
    stepElapsed = stepElapsed > steps[stepIndex]->duration ? steps[stepIndex]->duration : stepElapsed;
    elapsedMillis += stepElapsed;

    return (elapsedMillis / totalMillis) * 100;
  }

  bool isRunning() { return running; }
  double getKp() {
    if (!running || stepIndex >= steps.size()) {
      return 1.0;
    }
    return steps[stepIndex]->kP;
  }
  double getTargetTemp() {
    if (!running || stepIndex >= steps.size()) {
      return 0.0;
    }
    return steps[stepIndex]->targetTemp;
  }
  long getDuration() {
    if (!running || stepIndex >= steps.size()) {
      return 0;
    }
    return steps[stepIndex]->duration;
  }
  const char* getLabel() {
    if (!running || stepIndex >= steps.size()) {
      return "finished";
    }
    return steps[stepIndex]->label;
  }
  bool isStepReached() {
    if (!running || stepIndex >= steps.size()) {
      return true;
    }
    return steps[stepIndex]->reachedMillis;
  }
  bool isHeating() {
    if (!running || stepIndex >= steps.size()) {
      return true;
    }
    return steps[stepIndex]->heatup;
  }

  void update(double temperature) {
    if (!running || stepIndex >= steps.size()) {
      return;
    }

    TempStep* cs = steps[stepIndex];
    if (!cs->reachedMillis                                         // step not reached yet -> check temp
        && ((cs->heatup && cs->targetTemp <= temperature)          // temperature hot enough
            || (!cs->heatup && temperature <= cs->targetTemp))) {  // temperature cold enough
      cs->reachedMillis = millis();
    } else if (cs->reachedMillis && cs->reachedMillis + cs->duration <= millis()) {  // step reached -> check duration
      stepIndex++;
      if (stepIndex >= steps.size()) {
        running = false;
      }
    }
  }

 private:
  std::vector<TempStep*> steps;
  int stepIndex = 0;
  bool running = false;
};

#endif
