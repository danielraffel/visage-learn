//
// Created by Paul Walker on 2/5/25.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#define VLLOG(...) std::cout << __FILE__ << ":" << __LINE__ << " " << __VA_ARGS__ << std::endl;
#define VLV(x) #x << "=" << x << " "
#endif //CONFIG_H
