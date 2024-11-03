// finalproject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "olcNoiseMaker.h"

using namespace std;

struct sEnvelopeADSR {
    double dAttackTime;
    double dDecayTime;
    double dReleaseTime;

    double dSustainAmplitude;
    double dTopAmplitude;

    double dTriggerOnTime;
    double dTriggerOffTime;

    bool bNoteOn;


    sEnvelopeADSR() {
        dAttackTime = 0.01;
        dDecayTime = 0.01;
        dTopAmplitude = 1.0;
        dSustainAmplitude = 0.8;
        dReleaseTime = 0.02;

        dTriggerOffTime = 0.0;
        dTriggerOnTime = 0.0;
        bNoteOn = false;
    }

    double GetAmplitude(double dTime) {
        double dAmplitude = 0.0;
        double dLifeTime = dTime - dTriggerOnTime;

        if (bNoteOn) {
            if (dLifeTime <= dAttackTime) {
                dAmplitude = (dLifeTime / dAttackTime) * dTopAmplitude;
                //cout << "attacking\n";
            }
            else if (dLifeTime <= dAttackTime + dDecayTime) {
                dAmplitude = dTopAmplitude - ((dLifeTime - dAttackTime) / dDecayTime) * (dTopAmplitude - dSustainAmplitude);
                //cout << "decaying\n";
            }
            else {
                dAmplitude = dSustainAmplitude;
                //cout << "sustaining\n";
            }
        }
        else {
            double dReleasingTime = dTime - dTriggerOffTime;
            dAmplitude = dSustainAmplitude - (dReleasingTime / dReleaseTime) * dSustainAmplitude;
            //wcout << "\rreleasing" << dAmplitude;
        }

        if (dAmplitude <= 0.0001) {
            dAmplitude = 0;
        }

        return dAmplitude;
    }

    void NoteOn(double dTimeOn) {
        dTriggerOnTime = dTimeOn;
        bNoteOn = true;
    }

    void NoteOff(double dTimeOff) {
        dTriggerOffTime = dTimeOff;
        bNoteOn = false;
    }
};

double dBaseFrequency = 220.0;
atomic<double> dFrequencyOutput = 0;
sEnvelopeADSR envelope;

double w(double dHertz) {
    return dHertz * 2.0 * PI;
}

double osc(double dHertz, double dTime, int nType) {
    switch (nType) {
    case 0: //sine wave
        return sin(w(dHertz) * dTime);
    case 1: //multiple sine waves
        return 1.0 * sin(w(dHertz) * dTime)
            + 1.0 * sin(w(dHertz) * 1.5 * dTime)
            /*+ 1.0 * sin(w(dHertz) * 2 * dTime)
            + 0.6 * sin(w(dHertz) * 2.5 * dTime)
            + 0.5 * sin(w(dHertz) * 3 * dTime)*/
            ;
    case 2: //square wave
        return sin(w(dHertz) * dTime) > 0 ? 1.0 : -1.0;
    case 3: //triangle wave
        return asin(sin(w(dHertz) * dTime)) * 2.0 / PI;
    default:
        return 0.0;
    }

}

double MakeNoise(double dTime) {
    double dAmplitude = envelope.GetAmplitude(dTime);
    return dAmplitude * osc(dFrequencyOutput, dTime, 1);
}

double dIntonationFrequency(int semitones) {
    double dMultiplier = 1;
    int octaves = semitones / 12;
    semitones %= 12;
    switch (semitones) {
    case 0: //unison
        dMultiplier = 1;
        break;
    case 1: //minor second
        dMultiplier = 16.0 / 15.0;
        break;
    case 2: //major second
        dMultiplier = 9.0 / 8.0;
        break;
    case 3: //minor third
        dMultiplier = 6.0 / 5.0;
        break;
    case 4: //major third
        dMultiplier = 5.0 / 4.0;
        break;
    case 5: //perfect fourth
        dMultiplier = 4.0 / 3.0;
        break;
    case 6: //tritone
        dMultiplier = 64.0 / 45.0;
        break;
    case 7: //perfect fifth
        dMultiplier = 3.0 / 2.0;
        break;
    case 8: //minor sixth
        dMultiplier = 8.0 / 5.0;
        break;
    case 9: //major sixth
        dMultiplier = 5.0 / 3.0;
        break;
    case 10: //minor seventh
        dMultiplier = 16.0 / 9.0;
        break;
    case 11: //major seventh
        dMultiplier = 15.0 / 8.0;
        break;
    }

    return dBaseFrequency * pow(2, octaves) * dMultiplier;
}

double dEqualTempFrequency(int semitones) {
    return dBaseFrequency * pow(pow(2.0, 1.0 / 12.0), semitones);
}


int main()
{
    cout << "Hello World!";
    vector<wstring> devices = olcNoiseMaker<short>::Enumerate();
    for (auto d : devices) wcout << "Found Output Device:" << d << endl;
    olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);
    sound.SetUserFunction(MakeNoise);

    bool keyPressed = false;
    int nCurrentKey = -1;
    while (true) {
        ////unison
        //if (GetAsyncKeyState('A') & 0x8000)
        //    dFrequencyOutput = dBaseFrequency;
        ////minor second
        //else if (GetAsyncKeyState('W') & 0x8000)
        //    dFrequencyOutput = dBaseFrequency * (16.0/15.0);
        ////major second
        //else if (GetAsyncKeyState('S') & 0x8000)
        //    dFrequencyOutput = dBaseFrequency * 1.125;
        ////minor third
        //else if (GetAsyncKeyState('E') & 0x8000)
        //    dFrequencyOutput = dBaseFrequency * 1.2;
        ////major third
        //else if (GetAsyncKeyState('D') & 0x8000)
        //    dFrequencyOutput = dBaseFrequency * 1.25;
        ////perfect fourth
        //else if (GetAsyncKeyState('F') & 0x8000)
        //    dFrequencyOutput = dBaseFrequency * (4.0 / 3.0);
        ////tritone
        //else if (GetAsyncKeyState('T') & 0x8000)
        //    dFrequencyOutput = dBaseFrequency * (64.0 / 45.0);
        ////perfect fifth
        //else if (GetAsyncKeyState('G') & 0x8000)
        //    dFrequencyOutput = dBaseFrequency * 1.5;
        ////minor sixth
        //else if (GetAsyncKeyState('Y') & 0x8000)
        //    dFrequencyOutput = dBaseFrequency * 1.6;
        ////major sixth
        //else if (GetAsyncKeyState('H') & 0x8000)
        //    dFrequencyOutput = dBaseFrequency * (5.0 / 3.0);
        ////minor seventh
        //else if (GetAsyncKeyState('U') & 0x8000)
        //    dFrequencyOutput = dBaseFrequency * (16.0 / 9.0);
        ////major seventh
        //else if (GetAsyncKeyState('J') & 0x8000)
        //    dFrequencyOutput = dBaseFrequency * 1.875;
        ////octave
        //else if (GetAsyncKeyState('K') & 0x8000)
        //    dFrequencyOutput = dBaseFrequency * 2;
        //else
        //    dFrequencyOutput = 0.0;

        ////octave down
        //if (GetAsyncKeyState('Z') & 0x8000)
        //    dBaseFrequency = 220.0;
        ////octave middle
        //if (GetAsyncKeyState('X') & 0x8000)
        //    dBaseFrequency = 440.0;
        ////octave up
        //if (GetAsyncKeyState('C') & 0x8000)
        //    dBaseFrequency = 880.0;

        keyPressed = false;
        for (int key = 0; key <= 13; key++) {
            if (GetAsyncKeyState((unsigned char)"AWSEDFTGYHUJKL"[key]) & 0x8000) {
                if (nCurrentKey != key) {
                    dFrequencyOutput = dIntonationFrequency(key);
                    //dFrequencyOutput = dEqualTempFrequency(key);
                    nCurrentKey = key;
                    envelope.NoteOn(sound.GetTime());
                    wcout << "\rNote On : " << sound.GetTime() << "s " << dFrequencyOutput << "Hz";
                }
                keyPressed = true;

            }
        }

        if (!keyPressed) {
            if (nCurrentKey != -1) {
                nCurrentKey = -1;
                envelope.NoteOff(sound.GetTime());
                wcout << "\rNote Off: " << sound.GetTime() << "s                        ";
            }
        }
    }
    return 0;
}