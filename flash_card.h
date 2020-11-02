#ifndef FLASH_CARDS_H
#define FLASH_CARDS_H
#include <string>

struct FlashCard
{
    unsigned int chapter;
    std::string front;
    std::string back;
};

#endif