#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char symbol[10];
    double price;
    int quantity;
} Stock;

typedef struct {
    double balance;
    Stock* portfolio;
    int portfolioSize;
} Player;

void displayPortfolio(Player* player) {
    printf("\n=== Portfolio ===\n");
    printf("Balance: $%.2f\n", player->balance);

    if (player->portfolioSize > 0) {
        printf("\nStocks:\n");
        printf("%-10s %-10s %-10s\n", "Symbol", "Price", "Quantity");
        for (int i = 0; i < player->portfolioSize; ++i) {
            printf("%-10s %-10.2f %-10d\n", player->portfolio[i].symbol, player->portfolio[i].price, player->portfolio[i].quantity);
        }
    } else {
        printf("\nNo stocks in the portfolio.\n");
    }
}

int main() {
    Player player;
    player.balance = 10000.0; // Initial balance
    player.portfolio = NULL;
    player.portfolioSize = 0;

    while (1) {
        printf("\n=== Stock Trading Simulator ===\n");
        printf("1. Buy Stock\n");
        printf("2. Sell Stock\n");
        printf("3. Display Portfolio\n");
        printf("4. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Buy Stock
                if (player.balance <= 0) {
                    printf("Insufficient funds.\n");
                    break;
                }

                Stock newStock;
                printf("Enter stock symbol: ");
                scanf("%s", newStock.symbol);
                printf("Enter stock price: $");
                scanf("%lf", &newStock.price);
                printf("Enter quantity to buy: ");
                scanf("%d", &newStock.quantity);

                double totalCost = newStock.price * newStock.quantity;
                if (totalCost > player.balance) {
                    printf("Insufficient funds to buy %d shares of %s.\n", newStock.quantity, newStock.symbol);
                    break;
                }

                // Update player's balance and portfolio
                player.balance -= totalCost;
                player.portfolio = realloc(player.portfolio, (player.portfolioSize + 1) * sizeof(Stock));
                player.portfolio[player.portfolioSize++] = newStock;

                printf("Stock bought successfully!\n");
                break;

            case 2: // Sell Stock
                if (player.portfolioSize == 0) {
                    printf("No stocks in the portfolio to sell.\n");
                    break;
                }

                displayPortfolio(&player);

                int sellIndex;
                printf("Enter the index of the stock to sell: ");
                scanf("%d", &sellIndex);

                if (sellIndex < 0 || sellIndex >= player.portfolioSize) {
                    printf("Invalid stock index.\n");
                    break;
                }

                Stock* soldStock = &player.portfolio[sellIndex];
                printf("Enter quantity to sell: ");
                scanf("%d", &newStock.quantity);

                if (newStock.quantity > soldStock->quantity) {
                    printf("Not enough shares to sell.\n");
                    break;
                }

                // Update player's balance and portfolio
                double saleProceeds = soldStock->price * newStock.quantity;
                player.balance += saleProceeds;
                soldStock->quantity -= newStock.quantity;

                if (soldStock->quantity == 0) {
                    // Remove the stock from the portfolio if all shares are sold
                    for (int i = sellIndex; i < player.portfolioSize - 1; ++i) {
                        player.portfolio[i] = player.portfolio[i + 1];
                    }
                    player.portfolio = realloc(player.portfolio, (player.portfolioSize - 1) * sizeof(Stock));
                    player.portfolioSize--;
                }

                printf("Stock sold successfully!\n");
                break;

            case 3: // Display Portfolio
                displayPortfolio(&player);
                break;

            case 4: // Exit
                free(player.portfolio);
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
