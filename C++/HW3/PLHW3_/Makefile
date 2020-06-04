LDFLAGS=-std=c++11

transaction: ; g++ $(LDFLAGS) transaction_test.cpp Transaction.cpp -o Test
account: ; g++ $(LDFLAGS) account_test.cpp Transaction.cpp Account.cpp -o Test
bank: ; g++ $(LDFLAGS) bank_test.cpp Transaction.cpp Account.cpp Bank.cpp -o Test
run: ;./Test
valgrind: ; valgrind --leak-check=full ./Test
clean: ; rm -rf Test
