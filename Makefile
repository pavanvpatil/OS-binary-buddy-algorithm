compile:
	@echo "Compiling..."
	@g++ binary_buddy_algo.cpp -o a.out
	@echo "Done."

run:
	@echo "Running the test cases..."
	@echo "--------------------------------------------------------------------------"
	@echo "For: input1.txt U:10 L:4"
	@./a.out ./inputs/input1.txt
	@echo "--------------------------------------------------------------------------"
	@echo "For: input2.txt U:10 L:2"
	@./a.out ./inputs/input2.txt
	@echo "--------------------------------------------------------------------------"
	@echo "For: input3.txt U:20 L:5"
	@./a.out ./inputs/input3.txt
	@echo "--------------------------------------------------------------------------"
	@echo "For: input4.txt U:15 L:3"
	@./a.out ./inputs/input4.txt
	@echo "--------------------------------------------------------------------------"
	@echo "For: input5.txt U:16 L:4"
	@./a.out ./inputs/input5.txt
	@echo "--------------------------------------------------------------------------"
	@echo "Done."

clean:
	@echo "Cleaning..."
	@rm -rf a.out
	@echo "Done."

info:
	@echo "Author: Pavan Kumar V Patil"
	@echo "Roll No: 200030041"
	@echo "date: 2023-04-06"
	@echo "description: Implementation of binary buddy algorithm"
	@echo "course: Operating Systems"
	@echo "Institute: IIT Dharwad"