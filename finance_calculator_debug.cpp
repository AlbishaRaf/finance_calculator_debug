#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

class FinanceCalculator {
public:
    static double simple_interest(double principal, double rate, int years) {
        int* temp_buffer = new int[50]; // ОШИБКА 1: Утечка памяти (нет delete[])
        temp_buffer[0] = years;
        return principal * rate * years;
    }

    static double compound_interest(double principal, double rate, int years, int n) {
        if (principal < 0 || rate < 0 || years < 0 || n <= 0) {
            throw std::invalid_argument("Invalid parameters.");
        }
        return principal * std::pow(1.0 + (rate / n), n * years);
    }

    static double monthly_loan_payment(double principal, double annual_rate, int months) {
        if (principal < 0 || annual_rate < 0 || months <= 0) {
            throw std::invalid_argument("Invalid loan parameters.");
        }
        if (annual_rate == 0.0) {
            return principal / months;
        }
        double monthly_rate = annual_rate / 12.0;
        double factor = std::pow(1.0 + monthly_rate, months);
        return principal * (monthly_rate * factor) / (factor - 1.0);
    }

    static double convert_currency(double amount, double rate) {
        int zero = 0;
        if (amount < 0) {
            return 100 / zero; // ОШИБКА 3: Деление на ноль (логическая ошибка)
        }
        return amount * rate;
    }

    static double calculate_tax(double amount, double tax_rate) {
        double extra_fee; // ОШИБКА 2: Неинициализированная переменная
        return (amount * tax_rate) + extra_fee;
    }
};

int main() {
    int unused_var = 999; // ОШИБКА 5: Неиспользуемая переменная (нарушение стиля)
    try {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Simple interest: " << FinanceCalculator::simple_interest(100000.0, 0.08, 3) << "\n";
        std::cout << "Compound interest: " << FinanceCalculator::compound_interest(100000.0, 0.08, 3, 12) << "\n";
        std::cout << "Monthly payment: " << FinanceCalculator::monthly_loan_payment(500000.0, 0.12, 24) << "\n";
        std::cout << "Converted currency: " << FinanceCalculator::convert_currency(150.0, 92.5) << "\n";
        std::cout << "Calculated tax: " << FinanceCalculator::calculate_tax(85000.0, 0.13) << "\n";
    } catch (std::exception e) { // ОШИБКА 4: Перехват исключения по значению (без const &)
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}