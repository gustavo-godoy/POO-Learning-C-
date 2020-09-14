#include "../include/stochastic.h"
#include <iostream> //debug
#include <cstring>

Stochastic::Stochastic(){}
Stochastic::~Stochastic(){}

void Stochastic::setHighDailyPrice(void)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
{
    float priceCloseDaily[200], price[200+16];
    float  bestprice;
    float priceHighDaily[200];
    int n = 8; // n = intervalo que deseja analisar

    // 200 = len(std::<vector>)
    for(int i = 0; i < 200; i ++) {
        priceCloseDaily[i] = price[i];
    }

    for(int i = 0; i < 200; i++) {
        if(i > 8) {
            n++;
        }
        bestprice = price[i];

        for(int j = i; j < i + n; j++) {
            if(price[j] > bestprice) {
                bestprice = price[j];
            }
        }
        this->stochasticData.priceHighDaily[i] = bestprice;
        //ver sentido dos dados, Primeiro mais recente ou mais antigo
    }
    this->highPriceDaily = priceHighDaily[0];
}


//////////////////

// Função %K:
size_t Stochastic::kValues(float * output, float * arrayMin, float* arrayMax, float* arrayClose, size_t sizeClose){
    enum { magic_periodos = 8};
    float kArray[sizeClose]; size_t kSize=0;
    float k;
    
    for(size_t i=magic_periodos; i < sizeClose; ++i){
        k = ( arrayClose[i] - arrayMin[i-magic_periodos] ) / ( arrayMax[i-magic_periodos] - arrayMin[i-magic_periodos] );
        k *= 100;
        kArray[kSize++] = k;
    }
    
    output = new float[kSize];
    memcpy(output, kArray, kSize);
    
    return kSize;
}

// float Stochastic::valorK( float * inputArray, size_t inputSize)

size_t Stochastic::valoresMinimos(float * output, float * inputArray, size_t inputSize){
    enum { magic_periodos = 8};
    int y=0;
    int z=0;
    size_t arraySize=0;
    int arrayMinimos[inputSize];
    
    for(size_t i=0; i < inputSize-magic_periodos; ++i){
        
	    z=inputArray[y];
	    for(size_t j=0; j < magic_periodos; ++j){
		    if(z>inputArray[y+1]){
			    z=inputArray[y+1];
		    }
		    y++;
	    }
	    arrayMinimos[arraySize++] = z;
	    y -= magic_periodos-1;
    }
    
    output = new float[arraySize];
    memcpy(output, arrayMinimos, arraySize);

    return arraySize;
}


size_t Stochastic::valoresMaximos(float * output, float * inputArray, size_t inputSize){
    enum { magic_periodos = 8 };
    int y=0;
    int z=0;
    size_t arraySize=0;
    int arrayMaximos[inputSize];
    
    for(size_t i=0; i < inputSize-magic_periodos; ++i){
	    z=inputArray[y];
	    for(size_t j=0; j < magic_periodos; ++j){
		    if(z<inputArray[y+1]){
			    z=inputArray[y+1];
		    }
		    y++;
	    }
	    arrayMaximos[arraySize++] = z;
	    y -= magic_periodos-1;
    }

    output = new float[arraySize];
    memcpy(output, arrayMaximos, arraySize);

    return arraySize;    
}


///////////////////

void Stochastic::setLowDailyPrice(void)
{
    int n = 8;
    float worstprice;
    float priceLowDaily[200];

    for(int i = 0; i < 200; i++) {
        if(i > 8) {
            n++;
        }
        worstprice = this->stochasticData.price[i];
        for(int j = i; j < i + n; j++) {
            if(this->stochasticData.price[j] < worstprice) {
                worstprice = this->stochasticData.price[j];
            }
        }
        this->stochasticData.priceLowDaily[i] = worstprice;
    }
    this->lowPriceDaily = priceLowDaily[0];

}

void Stochastic::getKcurve(void)
{
    float Kcurve[200];

    for(int i = 0; i < 200+ 2; i++) {
        this->stochasticData.Kcurve[i] = 100 * 
        ((this->stochasticData.price[i] - this->stochasticData.priceLowDaily[i])
        /(this->stochasticData.priceLowDaily[i]-this->stochasticData.priceLowDaily[i]));
    }
}

void Stochastic::averageKcurve(void)
{
    for(int i = 0; i < 200; i++) {
        this->stochasticData.KcurveAverage[i] = this->stochasticData.Kcurve[i] + 
        this->stochasticData.Kcurve[i + 1] + this->stochasticData.Kcurve[i + 2];
    }
}

void Stochastic::setPrice(float* price, size_t arraySize)
{
    for(int i = 0; i < arraySize; i++)
    {
        this->stochasticData.price[i] = price[i];
    }
}

float Stochastic::getResult(void)
{
    this->stochasticResult = this->stochasticData.Kcurve[0];
    return this->stochasticResult;
}


float Stochastic::getLowDailyPrice(void)
{
    return this->lowPriceDaily;
}
float Stochastic::getHighDailyPrice(void)
{
    return this->highPriceDaily;
}