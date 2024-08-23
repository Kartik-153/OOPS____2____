#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>
using namespace std;
#define SIZE 100
class numberOfSpectrums{  // 1 question
    public:
    string OG_date;
    string CompanyName;
    int SpectrumRange;
    string circle;
    int revenue;
};
class numberofSubscribers {   // 2 question
    public:
    string NUMBER_OF_SUBSCRIBERS_DATE;
    string NUMBER_OF_SUBSCRIBERS_COMPANY;
    string NUMBER_OF_SUBSCRIBERS_LOCATION;
    int NUMBER_OF_SUBSCRIBERS;
};
class spectrumRequest {        // 3 question
    public:
    string SPECTRUM_DATE;
    string SPECTRUM_REQUEST_COMPANY;
    string SPECTRUM_REQUEST_LOCATION;
    int REQUESTS;
};
class MVNOds {
    public:
    string MVNO_DATE;
    string MVNO_SPECTRUM;
    string MVNO_LOCATION;
    int MVNO_REQUEST;
};
numberOfSpectrums SPECTRUM_RANGE[SIZE];
int length_of_1=0;
numberofSubscribers SUBSCRIBERS_LIST[SIZE];
int length_of_2=0;
spectrumRequest REQUESTS_LIST[SIZE];
int length_of_3=0;
MVNOds MVNO_LIST[SIZE];
int length_of_4=0;
bool ALLOCATION[SIZE];
void readSpectrumRange(const string& filename){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open " << filename << endl;
        return;
    }
    string line;
    getline(file, line);
    int count = 1;
    while(getline(file, line)){
        numberOfSpectrums item;
        stringstream ss(line);
        getline(ss, item.OG_date, ',');
        getline(ss, item.CompanyName, ',');
        string token;
        if(getline(ss, token, ',')) {
            int val=stoi(token);
            item.SpectrumRange=val;
        }
        getline(ss, item.circle, ',');
        if(getline(ss, token, ',')) {
            int val=stoi(token);
            item.revenue=val;
        }
        SPECTRUM_RANGE[length_of_1++]=item;
    }
    file.close();
}
void readSubscribers(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open " << filename << endl;
        return;
    }
    string line;
    getline(file, line);
    int count = 1;
    while(getline(file, line)){
        numberofSubscribers item;
        stringstream ss(line);
        getline(ss, item.NUMBER_OF_SUBSCRIBERS_DATE, ',');
        getline(ss, item.NUMBER_OF_SUBSCRIBERS_COMPANY, ',');
        getline(ss, item.NUMBER_OF_SUBSCRIBERS_LOCATION, ',');
        string token;
        if(getline(ss, token, ',')) {
            int val=stoi(token);
            item.NUMBER_OF_SUBSCRIBERS=val;
        }
        SUBSCRIBERS_LIST[length_of_2++]=item;
    }
    file.close();
}
void readSpectrumRequest(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open " << filename << endl;
        return;
    }
    string line;
    getline(file, line);
    int count = 1;
    while(getline(file, line)){
        spectrumRequest item;
        stringstream ss(line);
        getline(ss, item.SPECTRUM_DATE, ',');
        getline(ss, item.SPECTRUM_REQUEST_COMPANY, ',');
        getline(ss, item.SPECTRUM_REQUEST_LOCATION, ',');
        string token;
        if(getline(ss, token, ',')) {
            int val=stoi(token);
            item.REQUESTS=val;
        }
        REQUESTS_LIST[length_of_3++]=item;
    }
    file.close();
}

void readMVNOSpectrum(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open " << filename << endl;
        return;
    }
    string line;
    getline(file, line);
    int count = 1;
    while(getline(file, line)){
        MVNOds item;
        stringstream ss(line);
        getline(ss, item.MVNO_DATE, ',');
        getline(ss, item.MVNO_SPECTRUM, ',');
        getline(ss, item.MVNO_LOCATION, ',');
        string token;
        if(getline(ss, token, ',')) {
            int val=stoi(token);
            item.MVNO_REQUEST=val;
        }
        MVNO_LIST[length_of_4++]=item;
    }
    file.close();
}

void allocation_deallocation(int threshold){
    string company__;
    string location__;

    for(int i = 0; i < SIZE; i++) {
        int total_request = 0;
        int total_spectrum = 0;
        int allocate = 0;
        int usage_density = 0;
        company__=REQUESTS_LIST[i].SPECTRUM_REQUEST_COMPANY;
        location__=REQUESTS_LIST[i].SPECTRUM_REQUEST_LOCATION;
        // Calculate number of subscribers in Given request of csv file;
        for(int j = 0; j < SIZE; j++) {
            if(SUBSCRIBERS_LIST[j].NUMBER_OF_SUBSCRIBERS_COMPANY == company__ && 
            SUBSCRIBERS_LIST[j].NUMBER_OF_SUBSCRIBERS_LOCATION == location__) {
                total_request = total_request + SUBSCRIBERS_LIST[j].NUMBER_OF_SUBSCRIBERS;
            }
        }
        // Calculate nuuumber of spectrum in the given region and put it into total_spectrum variable;
        for(int a = 0; a < SIZE; a++) {
            if(SPECTRUM_RANGE[a].CompanyName == company__ && SPECTRUM_RANGE[a].circle == location__) {
                total_spectrum = total_spectrum + 1;
            }
        }
        allocate = total_request / total_spectrum;
        usage_density = (REQUESTS_LIST[i].REQUESTS*1000)/allocate;
        if(usage_density > threshold) {
            ALLOCATION[i] = false;
        }
        if(usage_density < threshold) {
            ALLOCATION[i] = true;
        }
    }
}

int main(void) {
    readSpectrumRange("spectrumRange.csv");
    readSubscribers("subscribers.csv");
    readSpectrumRequest("spectrumRequest.csv");
    readMVNOSpectrum("MVNOSpectrum.csv");
    allocation_deallocation(70);
    for(int i = 0; i < SIZE; i++) {
        cout << ALLOCATION[i] << endl;
        cout << endl;
    }
    return 0;
}