#include <bits/stdc++.h>

using namespace std;

class Product {
private:
    char name[20];
    double costofproduct, gstofproduct;
    int Numberofquantity;

public:
    Product(const char* n, double c, double g, int qty)
        : costofproduct(c), gstofproduct(g), Numberofquantity(qty) {
        strncpy(name, n, sizeof(name));
        name[sizeof(name) - 1] = '\0';
    }

    const char* getName() const {
        return name;
    }

    double calcTotalCost() const {
        return costofproduct * Numberofquantity * (1 + gstofproduct / 100);
    }

    double calcGstAmount() const {
        return costofproduct * Numberofquantity * (gstofproduct / 100);
    }

    double calcDiscountedTotalCost() const {
        return (costofproduct >= 500) ? calcTotalCost() * 0.95 : calcTotalCost();
    }
};

Product findProductWithMaxGst(const Product* productList, size_t size) {
    Product maxGstProduct = productList[0];
    double maxGstAmount = maxGstProduct.calcGstAmount();

    for (size_t  i= 1; i< size; ++i) {
        double currentGstAmount = productList[i].calcGstAmount();
        maxGstProduct = (currentGstAmount > maxGstAmount) ? productList[i] : maxGstProduct;
        maxGstAmount = (currentGstAmount > maxGstAmount) ? currentGstAmount : maxGstAmount;
    }

    return maxGstProduct;
}

int main() {
    Product products[] = {
        Product("Leather Wallet", 1100, 18, 1),
        Product("Umbrella", 900, 12, 4),
        Product("Cigarette", 200, 28, 3),
        Product("Honey", 100, 0, 2)
    };

    Product maxGstProduct = findProductWithMaxGst(products, sizeof(products) / sizeof(products[0]));

    double totalAmountToPay = 0.0;
    for (const auto& product : products) {
        totalAmountToPay += product.calcDiscountedTotalCost();
    }

    cout << "Product with maximum GST amount: " << maxGstProduct.getName() << endl;
    cout << "Total amount to be paid: Rs. " << totalAmountToPay << endl;

    return 0;
}