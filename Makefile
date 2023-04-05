compile:
	@echo "Compiling..."
	@g++ binary_buddy_algo.cpp -o a.out
	@echo "Done."

clean:
	@echo "Cleaning..."
	@rm -rf a.out
	@echo "Done."