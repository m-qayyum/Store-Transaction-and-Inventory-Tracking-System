# Store-Transaction-and-Inventory-Tracking-System

A C language program for a grocery store that needs a computer program to help keep track of inventory and price data.

The program must work by processing all the customer transactions gathered during each day. At the beginning of the day the program logic is started, and all initialization steps are carried out before processing any customers.

Initialization Steps:

The initialization steps require inputting data from two files that provide numbers and name strings for various categories of goods that are sold by the grocery store. This data is referenced throughout the program. For each customer, the cashier processes items in the order received. After the last item is processed for a given customer, the cashier triggers generation of a transaction receipt. This receipt is sorted by an item code, and states the name, price/item, number of items and total cost for that item (or group of items if more than one); which, then lists the total number of items of all types (or codes) purchased and the total purchase price for the complete transaction.

NOTE:

Usually this would be done using a cash register, but for the purpose of this prototype we simulate data entry through an input file and output using standard output. After the final record of items input, a Code value of 000 indicates the end of the transaction listing. At the end of the day, once all customer data has been processed, two reports are generated, and one file is produced.
