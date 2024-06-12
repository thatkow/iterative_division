#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

// Helper function to compare two numeric strings in a given base
bool isSmaller(const std::string& str1, const std::string& str2, int base) {
    int n1 = str1.length(), n2 = str2.length();
    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;
    for (int i = 0; i < n1; i++)
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false;
    return false;
}

// Helper function to subtract two numeric strings in a given base
std::string subtract(const std::string& str1, const std::string& str2, int base) {
    std::string s1 = str1, s2 = str2;
    if (isSmaller(s1, s2, base))
        std::swap(s1, s2);
    std::string str = "";
    int n1 = s1.length(), n2 = s2.length();
    std::reverse(s1.begin(), s1.end());
    std::reverse(s2.begin(), s2.end());
    int carry = 0;
    for (int i = 0; i < n2; i++) {
        int sub = ((s1[i] - '0') - (s2[i] - '0') - carry);
        if (sub < 0) {
            sub += base;
            carry = 1;
        } else
            carry = 0;
        str.push_back(sub + '0');
    }
    for (int i = n2; i < n1; i++) {
        int sub = ((s1[i] - '0') - carry);
        if (sub < 0) {
            sub += base;
            carry = 1;
        } else
            carry = 0;
        str.push_back(sub + '0');
    }
    std::reverse(str.begin(), str.end());
    int first_not_of_idx =  str.find_first_not_of('0');
    if(first_not_of_idx==std::string::npos) return "0";
    else return str.erase(0, first_not_of_idx); // remove leading zeros
}

// Helper function to convert a digit to a character in the given base
char toChar(int num) {
    if (num < 10) return num + '0';
    return num - 10 + 'A';
}

// Helper function to convert a character to a digit in the given base
int toInt(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    return ch - 'A' + 10;
}

// Helper function to validate if a given number is valid in the specified base
bool isValidNumber(const std::string& num, int base) {
    for (char ch : num) {
        int value = toInt(ch);
        if (value >= base) return false;
    }
    return true;
}

// Main function to perform iterative division and print each decimal value
void divideIteratively(const std::string& num1, const std::string& num2, int precision, int base) {
    if (!isValidNumber(num1, base) || !isValidNumber(num2, base)) {
        std::cerr << "Invalid number for the specified base." << std::endl;
        return;
    }

    std::string dividend = num1;
    std::string divisor = num2;

    // Handle integer part of the division
    std::string integerPart = "";
    std::string temp = "";
    for (char ch : dividend) {
        temp.push_back(ch);
        int x = 0;
        while (!isSmaller(temp, divisor, base)) {
            temp = subtract(temp, divisor, base);
            x++;
        }
        integerPart.push_back(toChar(x));
    }

    // Print the integer part and prepare for the fractional part
    size_t startpos = integerPart.find_first_not_of('0');
    if (startpos != std::string::npos) {
        std::cout << integerPart.substr(startpos);
    } else {
        std::cout << "0";
    }

    std::cout << ".";

    // Handle fractional part of the division
    std::unordered_map<std::string, int> remainderMap;
    std::string fractionalPart = temp;
    std::string result = "";
    bool repeating = false;
    int repeatStart = 0;

    for (int i = 0; i < precision; i++) {
        if (remainderMap.find(fractionalPart) != remainderMap.end()) {
            repeatStart = remainderMap[fractionalPart];
            repeating = true;
            break;
        }
        remainderMap[fractionalPart] = i;
        if(fractionalPart!="0")
            fractionalPart.push_back('0');
        int x = 0;
        while (!isSmaller(fractionalPart, divisor, base) && fractionalPart != "0") {
            fractionalPart = subtract(fractionalPart, divisor, base);
            x++;
        }
        
        result.push_back(toChar(x));
    }

    if (repeating) {
        std::cout << result.substr(0, repeatStart) << "(" << result.substr(repeatStart) << ")" << std::endl;
    } else {
        std::cout << result << std::endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <numerator> <denominator> <precision> <base>" << std::endl;
        return 1;
    }

    std::string num1 = argv[1];
    std::string num2 = argv[2];
    int precision = std::stoi(argv[3]);
    int base = std::stoi(argv[4]);

    divideIteratively(num1, num2, precision, base);

    return 0;
}

