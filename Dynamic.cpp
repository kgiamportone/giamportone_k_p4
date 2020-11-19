#include "Dynamic.h"\

using namespace std;

void greedy1(FILE * input_file, char *output_name) {

    FILE * output_file;
    output_file = fopen(output_name, "w");

    int num_items;
    int money_to_spend;

    while (fscanf(input_file, "%d %d", &num_items, &money_to_spend) != EOF) {
        printf("Num items %d\n", num_items);
        printf("Money to spend %d\n", money_to_spend);
        auto time1 = chrono::high_resolution_clock::now();

        vector<Item> knapsack;
        int weight;
        int profit;
        for (int i = 0; i < num_items; i++) {
            // id = i +1
            fscanf(input_file, "%d %d", &weight, &profit);
            Item to_add = Item(weight, profit, i+1);
            knapsack.push_back(to_add);
        }
        sort(knapsack.begin(), knapsack.end(), [](const Item& lhs, const Item& rhs){
            return lhs.ratio < rhs.ratio;
        });
	/*
        for (int i = 0; i < knapsack.size(); i++) {
            printf("Ratio %f ID %d\n", knapsack[i].ratio, knapsack[i].id);
        }
	*/
        vector<Item> retVal;
        int price_of_bag = 0;
        int max_profit = 0;
        int index_bag = 0;
        while (price_of_bag < money_to_spend) {
            if ((price_of_bag + knapsack[index_bag].weight) <= money_to_spend) {
                retVal.push_back(knapsack[index_bag]);
                price_of_bag += knapsack[index_bag].weight;
                max_profit += knapsack[index_bag].profit;
                index_bag++;
            }
            else {
                break;
            }
        }
        auto time2 = chrono::high_resolution_clock::now();
        auto elapsed = (float)(chrono::duration_cast<chrono::microseconds>(time2 - time1).count());
        fprintf(output_file, "%d %d %lf ", num_items, max_profit, elapsed);
        for (unsigned long int i = 0; i < retVal.size(); i++) {
            fprintf(output_file, "%d ", retVal[i].id);
        }
        fprintf(output_file, "\n");
    }
    fclose(output_file);
}

void greedy2(FILE * input_file, char *output_name) {

    FILE * output_file;
    output_file = fopen(output_name, "w");

    int num_items;
    int money_to_spend;

    while (fscanf(input_file, "%d %d", &num_items, &money_to_spend) != EOF) {
        printf("Num items %d\n", num_items);
        printf("Money to spend %d\n", money_to_spend);
        auto time1 = chrono::high_resolution_clock::now();

        vector<Item> knapsack;
        int weight;
        int profit;
        for (int i = 0; i < num_items; i++) {
            // id = i +1
            fscanf(input_file, "%d %d", &weight, &profit);
            Item to_add = Item(weight, profit, i+1);
            knapsack.push_back(to_add);
        }
        sort(knapsack.begin(), knapsack.end(), [](const Item& lhs, const Item& rhs){
            return lhs.ratio < rhs.ratio;
        });
        /*
        for (int i = 0; i < knapsack.size(); i++) {
            printf("Ratio %f ID %d\n", knapsack[i].ratio, knapsack[i].id);
        }
        */
        vector<Item> retVal;
        int price_of_bag = 0;
        int max_profit = 0;
        int index_bag = 0;
        while (price_of_bag < money_to_spend) {
            if ((price_of_bag + knapsack[index_bag].weight) <= money_to_spend) {
                retVal.push_back(knapsack[index_bag]);
                price_of_bag += knapsack[index_bag].weight;
                max_profit += knapsack[index_bag].profit;
                index_bag++;
            }
            else {
                break;
            }
        }
        // check greatest single item profit
        int indiv_profit = 0;
        Item indiv_item = Item(1, 0, 0); // default
        for (unsigned long int i = 0; i < knapsack.size(); i++) {
            if (knapsack[i].weight <= money_to_spend) {
                if (knapsack[i].profit > indiv_profit) {
                    indiv_profit = knapsack[i].profit;
                    indiv_item = knapsack[i];
                }
            }
        }

        auto time2 = chrono::high_resolution_clock::now();
        auto elapsed = (float)(chrono::duration_cast<chrono::microseconds>(time2 - time1).count());

        if (max_profit > indiv_profit) {
            fprintf(output_file, "%d %d %lf ", num_items, max_profit, elapsed);
            for (unsigned long int i = 0; i < retVal.size(); i++) {
                fprintf(output_file, "%d ", retVal[i].id);
            }
        }
        else {
            fprintf(output_file, "%d %d %lf %d", num_items, indiv_profit, elapsed, indiv_item.id);
        }
        fprintf(output_file, "\n");
    }
    fclose(output_file);
}

int max_solution(int sol1, int sol2) {
    if (sol1 > sol2) return sol1;
    else return sol2;
}

int backtrack_helper(int capacity, vector<Item> items, int num_items) {
    if (num_items == 0 || capacity == 0) {
        return 0;
    }

    if (items[num_items].weight > capacity) { // cannot fit in knapsack (backtrack)
        return backtrack_helper(capacity, items, num_items-1);
    }

    else { // return max when including or not including item
        return max_solution(items[num_items].profit + backtrack_helper(capacity - items[num_items].weight, items, num_items-1),
    backtrack_helper(capacity, items, num_items-1));
    }

}

void backtrack(FILE * input_file, char *output_name) {

    FILE * output_file;
    output_file = fopen(output_name, "w");

    int num_items;
    int money_to_spend;

    while (fscanf(input_file, "%d %d", &num_items, &money_to_spend) != EOF) {
        // printf("Num items %d\n", num_items);
        // printf("Money to spend %d\n", money_to_spend);
        auto time1 = chrono::high_resolution_clock::now();

        vector<Item> knapsack;
        int weight;
        int profit;
        for (int i = 0; i < num_items; i++) {
            // id = i +1
            fscanf(input_file, "%d %d", &weight, &profit);
            Item to_add = Item(weight, profit, i+1);
            knapsack.push_back(to_add);
        }
        // FOR BACKTRACKING
        vector<Item> unsorted = knapsack;

        sort(knapsack.begin(), knapsack.end(), [](const Item& lhs, const Item& rhs){
            return lhs.ratio < rhs.ratio;
        });
        /*
        for (int i = 0; i < knapsack.size(); i++) {
            printf("Ratio %f ID %d\n", knapsack[i].ratio, knapsack[i].id);
        }
        */
        vector<Item> retVal;
        int price_of_bag = 0;
        int max_profit = 0;
        int index_bag = 0;
        while (price_of_bag < money_to_spend) {
            if ((price_of_bag + knapsack[index_bag].weight) <= money_to_spend) {
                retVal.push_back(knapsack[index_bag]);
                price_of_bag += knapsack[index_bag].weight;
                max_profit += knapsack[index_bag].profit;
                index_bag++;
            }
            else {
                break;
            }
        }
        // check greatest single item profit
        int indiv_profit = 0;
        Item indiv_item = Item(1, 0, 0); // default
        for (long unsigned int i = 0; i < knapsack.size(); i++) {
            if (knapsack[i].weight <= money_to_spend) {
                if (knapsack[i].profit > indiv_profit) {
                    indiv_profit = knapsack[i].profit;
                    indiv_item = knapsack[i];
                }
            }
        }
        // Backtrack
        int backtrack_profit = backtrack_helper(money_to_spend, unsorted, unsorted.size()-1);
        // printf("Backtrack profit %d\n", backtrack_profit);

        // END COMPARISONS
        auto time2 = chrono::high_resolution_clock::now();
        auto elapsed = (float)(chrono::duration_cast<chrono::microseconds>(time2 - time1).count());

        // greedy1 is greatest
        if (max_profit > indiv_profit && max_profit > backtrack_profit) {
            printf("greedy1 chosen\n");
            fprintf(output_file, "%d %d %lf ", num_items, max_profit, elapsed);
            for (long unsigned int i = 0; i < retVal.size(); i++) {
                fprintf(output_file, "%d ", retVal[i].id);
            }
        }
        // greedy2 is greatest
        else if (indiv_profit > max_profit && indiv_profit > backtrack_profit){
            printf("greedy2 chosen\n");
            fprintf(output_file, "%d %d %lf %d", num_items, indiv_profit, elapsed, indiv_item.id);
        }
        // backtrack is greatest
        else {
            printf("backtrack chosen\n");
            fprintf(output_file, "%d %d %lf", num_items, backtrack_profit, elapsed);
        }
        fprintf(output_file, "\n");
    }
    fclose(output_file);
}

// *** DYNAMIC PROGRAMMING CODE STARTS HERE ***

void dynamic(FILE * input_file, char *output_name) {
    FILE * output_file;
    output_file = fopen(output_name, "w");

    int num_items;
    int money_to_spend;

    while (fscanf(input_file, "%d %d", &num_items, &money_to_spend) != EOF) {
        printf("Num items %d\n", num_items);
        printf("Money to spend %d\n", money_to_spend);
        auto time1 = chrono::high_resolution_clock::now();

        vector<Item> knapsack;
        int weight;
        int profit;
        for (int i = 0; i < num_items; i++) {
            // id = i +1
            fscanf(input_file, "%d %d", &weight, &profit);
            Item to_add = Item(weight, profit, i+1);
            knapsack.push_back(to_add);
        }
        // arrays for dynamic solution (size C + 1)
        int arr1[money_to_spend + 1];
        int arr2[money_to_spend + 1];

        for (int i = 0; i < money_to_spend+1; i++) {
            arr1[i] = 0; // initialize zeros for first row of table
        }
        // loop for each item (each row of the table)
        for (int i = 0; i < num_items; i++) {
            for (int j = 0; j < money_to_spend+1; j++) {
                if (knapsack[i].weight > j) {
                    arr2[j] = arr1[j];
                }
                else {
                    int no_p_i = arr1[j];
                    int with_p_i = arr1[j - knapsack[i].weight] + knapsack[i].profit;
                    if (no_p_i > with_p_i) {
                        arr2[j] = no_p_i;
                    }
                    else {
                        arr2[j] = with_p_i;
                    }
                }
            }
            // update arr1 for next iteration
            for (int i = 0; i < money_to_spend+1; i++) {
                // printf("%d ", arr1[i]);
                arr1[i] = arr2[i];
            }
            // printf("\n");
        }
        /*
        for (int i = 0; i < money_to_spend+1; i++) {
            printf("%d ", arr1[i]);
        }
        printf("\n");
        */
        int max_profit = arr2[money_to_spend];
        printf("Max profit = %d\n", max_profit);


        auto time2 = chrono::high_resolution_clock::now();
        auto elapsed = (float)(chrono::duration_cast<chrono::microseconds>(time2 - time1).count());
        fprintf(output_file, "%d %d %lf ", num_items, max_profit, elapsed);
        fprintf(output_file, "\n");

    }
    fclose(output_file);
}

int main(int argc, char *argv[]) {
    // ./program3 = argv[0]
    // input file = argv[1]
    // output file = argv[2]
    // 0/1/2 = argv[3] = mode

    FILE * input_file;
    input_file = fopen(argv[1], "r");

    // add manual output naming for argv[2]
    char * output_name = argv[2];

    char * mode = argv[3];
    printf("Mode: %s\n", mode);

    // SELECT MODE
    if (strncmp(mode, "0", 1) == 0) {
        greedy1(input_file, output_name);
    }
    else if (strncmp(mode, "1", 1) == 0) {
        greedy2(input_file, output_name);
    }
    else if (strncmp(mode, "2", 1) == 0) {
        backtrack(input_file, output_name);
    }
    else if (strncmp(mode, "3", 1) == 0) {
        dynamic(input_file, output_name);
    }


    fclose(input_file);

}
