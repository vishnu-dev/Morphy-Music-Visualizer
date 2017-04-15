//#include "aquila/global.h"
#include "aquila/source/WaveFile.h"
//#include "aquila/transform/FftFactory.h"
//#include "aquila/tools/TextPlot.h"
//#include <algorithm>
//#include <cstdlib>
//#include <iostream>
//
//int main(int argc, char *argv[])
//{
//    if (argc < 2)
//    {
//        std::cout << "Usage: wave_iteration <FILENAME>" << std::endl;
//        return 1;
//    }
//
//    Aquila::WaveFile wav(argv[1]);
//    std::cout << "Loaded file: " << wav.getFilename()
//              << " (" << wav.getBitsPerSample() << "b)" << std::endl;
//    Aquila::SampleType maxValue = 0, minValue = 0, average = 0;
//    //Aquila::TextPlot plt("Input signal");
//    // simple index-based iteration
//    auto fft = Aquila::FftFactory::getFft(wav.getAudioLength());
//    auto test=fft->fft(wav.toArray());
//    //plt.plotSpectrum(test);
//    for (std::size_t i = 0; i < wav.getSamplesCount(); ++i)
//    {
//        if (wav.sample(i) > maxValue)
//            maxValue = wav.sample(i);
//            std::cout<<wav.sample(i)<<" ";
//    }
//    std::cout << "Maximum sample value: " << maxValue << std::endl;
//
//    // iterator usage
//    for (auto it = wav.begin(); it != wav.end(); ++it)
//    {
//        if (*it < minValue)
//            minValue = *it;
//        //std::cout<<*it<<endl;
//    }
//    std::cout << "Minimum sample value: " << minValue << std::endl;
//
//    // range-based for loop
//    for (auto sample : wav)
//    {
//        average += sample;
//    }
//    average /= wav.getSamplesCount();
//    std::cout << "Average: " << average << std::endl;
//
//    // STL algorithms work too, so the previous examples could be rewritten
//    // using max/min_element.
//    int limit = 5000;
//    int aboveLimit = std::count_if(
//        wav.begin(),
//        wav.end(),
//        [limit] (Aquila::SampleType sample) {
//            return sample > limit;
//        }
//    );
//    std::cout << "There are " << aboveLimit << " samples greater than "
//              << limit << std::endl;
//    return 0;
//}


#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"
#include <algorithm>
#include <functional>
#include <memory>
#include <cmath>

Aquila::SpectrumType plotFourierTransform(Aquila::WaveFile wav)
{
//	std::ofstream out("Fourier.txt", ios::app);
//	out << endl << endl;
	Aquila::TextPlot plt("Fast Fourier Transform");
	int po=0;
	std::cout<<(po=pow(2,(int)std::log2(wav.getSamplesCount())))<<std::endl;
	std::cout<<wav.getSamplesCount();
	auto fft = Aquila::FftFactory::getFft(1024);
	Aquila::SpectrumType spectrum = fft->fft(wav.toArray());
//	for (int i = 0; i < spectrum.size(); i++)
//		out << spectrum[i] <<std::endl;
	//plt.plotSpectrum(spectrum);
	spectrum.shrink_to_fit();
	for(auto i=spectrum.begin();i!=spectrum.end();i++)
        std::cout<<*i<<std::endl;
	return spectrum;
}
int main(int argc,char** argv)
{
    // input signal parameters

    Aquila::TextPlot plt("Test");
    //plt.plot(sum);
    Aquila::WaveFile wav(argv[1]);
    //    const Aquila::FrequencyType sampleFreq = wav.getSampleFrequency();
//    const Aquila::FrequencyType f_lp = 500;
//    // calculate the FFT
//    auto fft = Aquila::FftFactory::getFft(sizeof(wav.toArray())/sizeof(Aquila::SampleType));
//    Aquila::SpectrumType spectrum = fft->fft(wav.toArray());
//    plt.setTitle("Signal spectrum before filtration");
//    plt.plotSpectrum(spectrum);
//
//    // generate a low-pass filter spectrum
//    Aquila::SpectrumType filterSpectrum(SIZE);
//    for (std::size_t i = 0; i < SIZE; ++i)
//    {
//        if (i < (SIZE * f_lp / sampleFreq))
//        {
//            // passband
//            filterSpectrum[i] = 1.0;
//        }
//        else
//        {
//            // stopband
//            filterSpectrum[i] = 0.0;
//        }
//    }
//    plt.setTitle("Filter spectrum");
//    plt.plotSpectrum(filterSpectrum);
//
//    // the following call does the multiplication of two spectra
//    // (which is complementary to convolution in time domain)
//    std::transform(
//        std::begin(spectrum),
//        std::end(spectrum),
//        std::begin(filterSpectrum),
//        std::begin(spectrum),
//        [] (Aquila::ComplexType x, Aquila::ComplexType y) { return x * y; }
//    );
    auto spectrum=plotFourierTransform(wav);
    plt.setTitle("Signal spectrum after filtration");
    plt.plotSpectrum(spectrum);

    // Inverse FFT moves us back to time domain
//    double x1[SIZE];
//    fft->ifft(spectrum, x1);
//    plt.setTitle("Signal waveform after filtration");
//    plt.plot(x1, SIZE);

    return 0;
}
