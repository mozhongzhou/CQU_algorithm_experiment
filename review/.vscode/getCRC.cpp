#include <iostream>
#include <bitset>

// 计算CRC的函数
// data: 输入数据
// generator: 生成多项式
unsigned int calculateCRC(unsigned int data, unsigned int generator)
{
    unsigned int dataLength = 32 - __builtin_clz(data);     // 输入数据的实际位数
    unsigned int genLength = 32 - __builtin_clz(generator); // 生成多项式的实际位数
    unsigned int crc = data << (genLength - 1);             // 将数据左移以适应生成多项式的长度

    generator <<= (32 - genLength); // 将生成多项式左移至最高位对齐

    for (unsigned int i = 0; i < dataLength; ++i)
    {
        if (crc & (1 << (31 - i))) // 如果当前位是1
        {
            crc ^= generator >> i; // 执行模2除法
        }
    }

    return crc & ((1 << (genLength - 1)) - 1); // 返回计算出的CRC，仅包含生成多项式位数的位
}

int main()
{
    unsigned int data = 0b111;     // 示例数据
    unsigned int generator = 0b11; // 示例生成多项式

    // 计算CRC
    unsigned int crc = calculateCRC(data, generator);

    // 以二进制形式输出CRC
    std::cout << "CRC: " << std::bitset<5>(crc) << std::endl; // 生成多项式有5位，所以使用std::bitset<5>

    return 0;
}
