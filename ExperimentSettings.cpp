#include "ExperimentSettings.h"
#include <QString>

ExperimentSettings::ExperimentSettings() {
    ExperimentSettings("Default Test");
}

ExperimentSettings::ExperimentSettings(QString desc, int s, int d, int me, int ma) {
    description = desc;
    size = s;
    distance = d;
    method = me;
    max = ma;
}

