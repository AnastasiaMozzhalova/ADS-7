// Copyright 2022 NNTU-CS
#include "train.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

void runExperiment(const std::string& filename, const std::string& title, 
                   std::vector<int> sizes, Train (*creator)(int)) {
  std::ofstream dataFile(filename + ".dat");
  std::ofstream timeFile(filename + "_time.dat");    
  dataFile << "# N Operations\n";
  timeFile << "# N Time(ms)\n";

  for (int n : sizes) {
    Train train = creator(n);
    int ops = train.getLength();
    dataFile << n << " " << train.getOpCount() << "\n";
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; i++) {
      Train tempTrain = creator(n);
      tempTrain.getLength();
    }
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 10000.0; 
    timeFile << n << " " << time << "\n";  
    std::cout << "N = " << n << ", Operations = " << train.getOpCount() 
              << ", Time = " << time << " ms" << std::endl;
  }

  std::ofstream gnuplotScript("plot_script.gnu");
  gnuplotScript << "set terminal pngcairo enhanced font 'arial,10'\n";
  gnuplotScript << "set output '" << filename << "_ops.png'\n";
  gnuplotScript << "set title '" << title << " (Operations)'\n";
  gnuplotScript << "set xlabel 'Number of cars (N)'\n";
  gnuplotScript << "set ylabel 'Number of operations'\n";
  gnuplotScript << "plot '" << filename << ".dat' with linespoints title 'Operations', \\\n";
  gnuplotScript << "     x*x/2 with lines title 'O(n^2)'\n";

  gnuplotScript << "set output '" << filename << "_time.png'\n";
  gnuplotScript << "set title '" << title << " (Time)'\n";
  gnuplotScript << "set ylabel 'Time (ms)'\n";
  gnuplotScript << "plot '" << filename << "_time.dat' with linespoints title 'Time', \\\n";
  gnuplotScript << "     x*x/1000 with lines title 'O(n^2)'\n";

  system("gnuplot plot_script.gnu");
}

int main() {
  std::vector<int> sizes;
  for (int n = 10; n <= 200; n += 10) {
    sizes.push_back(n);
  }
  runExperiment("all_on", "All lights on", sizes, Train::createAllLightsOn);
  runExperiment("all_off", "All lights off", sizes, Train::createAllLightsOff);
  runExperiment("random", "Random lights", sizes, Train::createRandomLights);

  return 0;
}
