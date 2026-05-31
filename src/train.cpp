// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) return;
    Car* current = first->next;
    while (current != first) {
        Car* temp = current;
        current = current->next;
        delete temp;
    }
    delete first;
}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getOpCount() {
    return countOp;
}

int Train::getLength() {
    if (!first) return 0;

    first->light = true;
    Car* current = first;
    int stepCount = 0;

    while (true) {
        current = current->next;
        stepCount++;
        countOp++;

        if (current->light) {
            current->light = false;

            for (int i = 0; i < stepCount; ++i) {
                current = current->prev;
                countOp++;
            }

            if (!first->light) {
                return stepCount;
            }

            for (int i = 0; i < stepCount; ++i) {
                current = current->next;
                countOp++;
            }
        }
    }
}
