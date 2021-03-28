#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int Bar_code ;
    char item_name[20];
    float item_price ;
    int Numitems ;
    struct Node * next ;
}Node ;

typedef struct ItemStruct
{
    int itemCode;
    float itemPrice;
    int itemQuantity;
    char itemName[16];
    float totalPrice;
    struct ItemStruct *nextItem;
} itemProduct;

typedef struct CatItems
{
    int CatCode;
    int CatQuantity;
    char CatName[16];
    float CatPrice;
    struct CatItems *nextItem;
} categoryItems;

// functions

void generateDailySummary(categoryItems *catHead)//generate summary recap
{
    FILE *GroceryData;
    GroceryData = fopen("CategoryName.dat", "r");
    if (GroceryData == NULL)
    {
        puts("UNABLE TO READ FILE");
        exit(1);
    }
    char buffer[40];
    int catNum;
    char catName[16];
    while (fgets(buffer, 40, GroceryData) != NULL)
    {
        sscanf(buffer, "%d ", &catNum);
        sscanf(buffer, "%[^\n]s", catName);
        printf("%d\t%s", catNum, catName);
    }
}

void writeToInventory(categoryItems *catHead)
{
    categoryItems *current;
    current = catHead;
    int hundreds;
    char fileStr[16];
    while (current != NULL)
    {
        hundreds = (current->CatCode) / 100;
    }
}

void ListIntitialize(itemProduct **head)
{
    *head = NULL;
}

void InitializeCatList(categoryItems **catHead) //initialize category list
{
    *catHead = NULL;
}

void deleteList(itemProduct **head)
{
    itemProduct *current = *head;
    itemProduct *next;

    while (current != NULL)
    {
        next = current->nextItem;
        free(current);
        current = next;
    }

    *head = NULL;
}

void beginningInsert(int code, int quantity, float price, float totalPrice, char name[], itemProduct **head)
{
    itemProduct *node = (itemProduct *)malloc(sizeof(itemProduct));
    node->itemCode = code;
    node->itemQuantity = quantity;
    node->itemPrice = price;
    node->totalPrice = totalPrice;
    strcpy(node->itemName, name);
    node->nextItem = NULL;

    if (*head != NULL)
    {
        node->nextItem = *head;
        *head = node;
    }
    else
    {
        *head = node;
    }
}

void beginningCatInsert(int code, int quantity, float price, char name[], categoryItems **catHead)
{
    categoryItems *node = (categoryItems *)malloc(sizeof(categoryItems));
    node->CatCode = code;
    node->CatQuantity = quantity;
    node->CatPrice = price;
    strcpy(node->CatName, name);
    node->nextItem = NULL;

    if (*catHead != NULL)
    {
        node->nextItem = *catHead;
        *catHead = node;
    }
    else
    {
        *catHead = node;
    }
}

void bubbleSort(itemProduct *head)
{
    int hasSwapped;
    itemProduct *ptr;
    itemProduct *lastPtr = NULL;

    if (head == lastPtr)
    {
        return;
    }
    do
    {
        hasSwapped = 0;
        ptr = head;
        while (ptr->nextItem != NULL)
        {
            if (ptr->itemCode > ptr->nextItem->itemCode)
            {
                swapping(ptr, ptr->nextItem);
                hasSwapped = 1;
            }
            ptr = ptr->nextItem;
        }
        lastPtr = ptr;
    } while (hasSwapped);
}

void swapping(itemProduct *a, itemProduct *b)
{
    int tempCode = a->itemCode;
    a->itemCode = b->itemCode;
    b->itemCode = tempCode;
    int tempQuantity = a->itemQuantity;
    a->itemQuantity = b->itemQuantity;
    b->itemQuantity = tempQuantity;
    float tempPrice = a->itemPrice;
    a->itemPrice = b->itemPrice;
    b->itemPrice = tempPrice;
    float tempTotal = a->totalPrice;
    a->totalPrice = b->totalPrice;
    b->totalPrice = tempTotal;
    char tempName[16];
    strcpy(tempName, a->itemName);
    strcpy(a->itemName, b->itemName);
    strcpy(b->itemName, tempName);
}

void endInsert(int code, int quantity, float price, float totalPrice, char name[], itemProduct **head)
{
    itemProduct *node = (itemProduct *)malloc(sizeof(itemProduct));
    node->itemCode = code;
    node->itemQuantity = quantity;
    node->itemPrice = price;
    node->totalPrice = totalPrice;
    strcpy(node->itemName, name);
    node->nextItem = NULL;
    if (*head == NULL)
    {
        *head = node;
    }
    itemProduct *current = *head;
    while (current->nextItem != NULL)
    {
        current = current->nextItem;
    }
    current->nextItem = node;
}

void printReceipt(itemProduct *head)
{
    itemProduct *current;
    current = head;
    while (current != NULL)
    {
        if (strlen(current->itemName) >= 8)
        {
            printf(" %d\t%s\t%.2f\t%d\t%.2f\n", current->itemCode, current->itemName, current->itemPrice, current->itemQuantity, current->totalPrice);
        }
        else
        {
            printf(" %d\t%s\t\t%.2f\t%d\t%.2f\n", current->itemCode, current->itemName, current->itemPrice, current->itemQuantity, current->totalPrice);
           
        }
        current = current->nextItem;
    }
}


int main()
{
    itemProduct *itemHead;
    ListIntitialize(&itemHead);

    categoryItems *categoryHead;
    InitializeCatList(&categoryHead);

    int consumer = 1;

    FILE *GroceryData;
    GroceryData = fopen("CategoryName.dat", "r");
    if (GroceryData == NULL)
    {
        puts("UNABLE TO READ FILE");
        exit(1);
    }
    FILE *PriceData;
    PriceData = fopen("CodeNamePrice.dat", "r");
    if (PriceData == NULL)
    {
        puts("UNABLE TO READ FILE2");
        exit(1);
    }
    FILE *DailyTrans;
    DailyTrans = fopen("DailyTransactions.dat", "r");
    if (DailyTrans == NULL)
    {
        puts("UNABLE TO READ FILE 3");
        exit(1);
    }
    char tempString[40];
    int transactionCode;
    int transactionQuantity;
    int itemCode;
    char *tokenPtr;
    char itemName[16];
    float itemPrice;
    float totalItemPrice;
    float consumerTotal;

    while (fgets(tempString, 40, DailyTrans) != NULL)
    {
        sscanf(tempString, "%d %d", &transactionCode, &transactionQuantity);
        memset(tempString, 0, 40);   //copying character
        fseek(PriceData, 0, SEEK_SET); //file postioning
        while (fgets(tempString, 40, PriceData) != NULL)
        {
            sscanf(tempString, "%d", &itemCode);
            tokenPtr = strtok(tempString, "\t");
            tokenPtr = strtok(NULL, "\t");
            int count = 0;
            while (tokenPtr != NULL)
            {
                switch (count)
                {
                case 0:
                    strcpy(itemName, tokenPtr);//copying string
                    tokenPtr = strtok(NULL, "\t");
                case 1:
                    itemPrice = atof(tokenPtr); //converting string to float
                    tokenPtr = strtok(NULL, "\t");
                }
                count++;
            }
            count = 0;
            memset(tempString, 0, 40);//copying characters
            if (transactionCode == itemCode)
            {
                totalItemPrice = (float)transactionQuantity * itemPrice;
                beginningInsert(transactionCode, transactionQuantity, itemPrice, totalItemPrice, itemName, &itemHead);
                beginningCatInsert(transactionCode, transactionQuantity, totalItemPrice, itemName, &categoryHead);
                consumerTotal += totalItemPrice;
            }
        }
        if (transactionCode == 0)
        {
            printf("Customer Receipt # %d\n", consumer);
            printf("Code\tItem Name\tPrice\tNumItem\tTotSale\n");
            bubbleSort(itemHead);
            printReceipt(itemHead);
            printf("\t\t\tTotals:\t%.2f\n", consumerTotal);
            printf("\t\tTHANK YOU FOR SHOPPING!!!\n");
            consumer++;
            consumerTotal = 0;
            deleteList(&itemHead);
        }
    }
    generateDailySummary(categoryHead);
}