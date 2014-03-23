#ifndef __EXPERIMENTSETTINGS_H
#define __EXPERIMENTSETTINGS_H

class ExperimentSettings {

    public:
        static const int BYCLICKS = 0;
        static const int BYHITS = 1;

        ExperimentSettings(int size=10, int distance=150, int method=BYCLICKS, int max=10);
        int getSize() {return size;}
        int getDistance() {return distance;}
        int getMax() { return max; }
        int getMethod() { return method; }

    private:
        int size;
        int distance;
        int max;
        int method;
};

#endif
