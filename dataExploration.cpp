#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>    
#include <cmath>

using namespace std;

int main(int argc, char** argv){
    ifstream inFS; //Input file stream
    string line;
    string rm_in, medv_in;
    const int MAX_LEN = 1000;
    vector<double> rm(MAX_LEN);
    vector<double> medv(MAX_LEN);

    //Try to open file
    cout << "Opening file Boston.csv." << endl;

    inFS.open("Boston.csv");
    if(!inFS.is_open()){
        cout << "Could not open file Boston.csv." << endl;
        return 1; //1 indicates error
    }

    //Can now use inFS stream like cin stream
    //Boston.csv should contain two doubles

    cout << "Reading line 1" << endl;
    getline(inFS, line);

    //echo heading
    cout << "heading: " << line << endl;

    int numObservations = 0;
    while (inFS.good()) {
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, ',');

        rm.at(numObservations) = stof(rm_in);
        medv.at(numObservations) = stof(medv_in);

        numObservations++;
    }

    rm.resize(numObservations);
    medv.resize(numObservations);

    cout << "new length " << rm.size() << endl;

    cout << "Closing file Boston.csv." << endl;
    inFS.close(); //Done with file, so close it

    cout << "Number of records: " << numObservations << endl;

    cout << "\nStats for rm" << endl;
    print_stats(rm);

    cout << "\nStats for medv" << endl;
    print_stats(medv);

    cout << "\nCovariance = " << covar(rm, medv) << endl;

    cout << "\nCorrelation = " << cor(rm, medv) << endl;

    cout << "\nProgram Terminated.";

    return 0;
}

double sumVector(vector <double> vect){
    //pass in a vector and calculate sum via a loop
    double sum; //initialize sum var to hold sum
    for (int i = 0; i < vect.size(); i++)
    {
        sum += vect[i];
    }

    return sum;
}

double meanVector(vector <double> vect) {
    double sum = sumVector(vect);
    double size = vect.size();
    double mean = sum / size;
    return mean;
}

double medianVector(vector <double> vect) {
    double median;
    //sort vector from  smallest to largest
    sort(vect.begin(), vect.end());
    int mid = vect.size() / 2;
    // decision tree dependent on size of vector
    if(vect.size() % 2 != 0)
        return vect[mid];
    return ((vect[mid - 1] + vect[mid]) / 2);
}

double rangeVector(vector <double> vect){
    double range;
    //sort vector like we did in the median function
    sort(vect.begin(), vect.end());
    double min = vect[0];
    double max = vect.back();
    range = max - min;
    return range;
}

double covar(vector <double> rm, vector<double> medv){
    //covar notes: vector - vector.mean * that for the other vector /data points -1
    //assuming both vectors have the same number of datapoints
    double rmMean = meanVector(rm);
    double medvMean = meanVector(medv);
    double totalSum;
    double covarriance;
    // loop for all values in vectors
    for (int i = 0; i < rm.size(); i++)
        totalSum = totalSum + (rm[i] - meanVector(rm)) * (medv[i] - meanVector(medv));
    covarriance = totalSum / (rm.size()) - 1;
    return covarriance;
}

double cor(vector <double> rm, vector <double> medv){
    //call covar of rm and medv
    double covarriance = covar(rm, medv);
    //calculate stdev for rm and medv
    double rmMean = meanVector(rm);
    double medvMean = meanVector(medv);
    double rmStdev;
    double medvStdev;
    double totalStdev;
    // iterate thru each vector and subtract mean from vect[i]
    for (int i = 0; i < rm[i]; i++){
        double temprm = pow((rm[i] - rmMean), 2);
        rmStdev = sqrt(temprm);
    }
    for (int i = 0; i < medv[i]; i++){
        double tempmedv = pow((medv[i] - medvMean), 2);
        medvStdev = sqrt(tempmedv);
    }

    //call cov function and divide by product of stdevs
    covarriance = covar(rm, medv);
    totalStdev = medvStdev * rmStdev;

    return covarriance / totalStdev;
}

void print_stats(vector<double> vect){
    cout << "\n Sum of " << vect << ": " << sumVector(vect);
    cout << "\n Mean of " << vect << ": " << meanVector(vect);
    cout << "\n Median of " << vect << ": " << medianVector(vect);
    cout << "\n Range of " << vect << ": " << rangeVector(vect);
}