// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <random>
#include "train.h"

int main() {
    std::ofstream outFile("result/experiment_data.csv");// Открываем файл для сохранения результатов в папке result
    
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл." << std::endl;// Проверка, удалось ли открыть файл
        return 1;
    }

    outFile << "Length,AllOff,AllOn,Random\n";

    std::mt19937 gen(123);
    std::uniform_int_distribution<> dist(0, 1);

    int maxLength = 100; // Максимальная длина поезда

    for (int n = 2; n <= maxLength; ++n) {
        
        Train trainOff;
        for (int i = 0; i < n; ++i) {
            trainOff.addCar(false);
        }
        trainOff.getLength();
        int opsOff = trainOff.getOpCount();

        Train trainOn;
        for (int i = 0; i < n; ++i) {
            trainOn.addCar(true);
        }
        trainOn.getLength();
        int opsOn = trainOn.getOpCount();

        Train trainRand;
        for (int i = 0; i < n; ++i) {
            trainRand.addCar(dist(gen));
        }
        trainRand.getLength();
        int opsRand = trainRand.getOpCount();

        outFile << n << "," << opsOff << "," << opsOn << "," << opsRand << "\n";
    }

    outFile.close();
    
    std::cout << "Данные сохранены в 'result/experiment_data.csv'." << std::endl;

    return 0;
}
