# Branch Prediction Project

## Introduction to Branch Prediction

Branch prediction is a technique used in computer processors to improve the flow in pipelines. When a program reaches a branch (such as an if-else statement, a switch-case, or a for loop), the processor must decide which path to take. Since this decision can be time-consuming, processors often predict the outcome of branches to keep the pipeline full, improving overall performance. However, inaccurate predictions can cause delays, as the processor needs to discard incorrect speculative executions and restart. Therefore, accurate branch prediction plays a crucial role in improving processor efficiency and speed.

## Project Overview

In this project, I focus on generating a dataset for branch prediction and testing various machine learning models for predicting the branch behavior. The dataset was generated using Intel's Pin Tool, an advanced dynamic binary instrumentation tool that allows us to analyze and manipulate binary programs at runtime.

### System Configuration

- **Processor**: Intel i5-11400H
- **Operating System**: Windows 11
- **Tool Used**: Intel Pin Tool for Linux, executed via WSL (Windows Subsystem for Linux)

### Intel Pin Tool Setup

To begin, I downloaded Intel Pin Tool version 3.31 for Linux, released on June 30, 2024, from [Intel’s official website](https://www.intel.com/content/www/us/en/developer/articles/tool/pin-a-binary-instrumentation-tool-downloads.html). You can unzip this tool in any folder of your choice. 

#### Steps to Set Up Intel Pin Tool:

1. After extracting the tool, navigate to the following directory:  
   `pin/pin/source/tools/ManualExamples`.

2. Place the `test3.cpp` file, which I created, in this directory.

3. In WSL (Windows Subsystem for Linux), use the `make test3.test` command to compile the source code. This command generates `test3.so`, and the default `cp-pin.exe` is executed, which creates a `branch_data.out` file containing the branch data in the format:
   - Branch Address
   - Taken (1 or 0, where 1 is taken and 0 is not taken)
   - Branch History (containing the previous history and current state)

### Dataset Generation

To generate the dataset, the process involves the following steps:

#### 1. Compile the Target Programs
First, compile your target program (in this case, 6 different programs) using the `g++` command. For example:
```bash
g++ test.cpp -o test
```

This command compiles the test.cpp file into an executable binary named "test"

#### 2. Running the Pin Tool
Now, run the Pin Tool with the compiled binary file:
```bash
../../../pin -t obj-intel64/test3.so -- ./test
```
This generates the branch_data.out file, which includes the branch address, taken status, and branch history.

# Branch Prediction Dataset Generation and Machine Learning Models

## Target Programs

The dataset was generated using the following programs:

- **Calculator Program**: A program with a switch-case structure for performing addition, subtraction, multiplication, or division.
- **Palindrome Check**: A program to check if a string is a palindrome.
- **Breadth First Search**: A graph traversal algorithm.
- **Depth First Search**: Another graph traversal algorithm.
- **Prim’s Algorithm**: A graph algorithm to find a minimum spanning tree.
- **cp-pin.exe**: A default program executed during the `make test3.test` command.

## Branch History Length Variations

Multiple datasets were generated with varying history lengths:

- **4-bit history**: 3 bits of previous history and 1 bit of actual taken/not taken state.
- **8-bit history**: 7 bits of previous history and 1 bit of actual taken/not taken state.
- **16-bit history**: 15 bits of previous history and 1 bit of actual taken/not taken state.
- **32-bit history**: 31 bits of previous history and 1 bit of actual taken/not taken state.

## Models Tested

Several machine learning models were tested on the generated datasets to predict branch behavior:

- **Logistic Regression**:
  - Accuracy: 71-74% (for 4-bit history across all 6 programs)
- **Decision Tree**:
  - Accuracy: 72% (for the Calculator Program)
- **Multilayer Perceptron (MLP)**:
  - Accuracy: 84% (for the Calculator Program using 16-bit history)
- **Long Short-Term Memory (LSTM)**:
  - Accuracy: 86% (for the Calculator Program using 16-bit history)
- **Perceptron**:
  - Accuracy: 67%

## Power Consumption Considerations

In branch prediction, power consumption is a critical factor, especially when designing hardware-based branch predictors. While complex models like MLP, LSTM, XGBoost, Random Forest, and SVM might offer higher accuracy, they come at the cost of increased computational requirements and power consumption. Therefore, simpler models like Perceptron, Logistic Regression, and Decision Trees are generally preferred in real-world scenarios, as they offer a good balance between accuracy and energy efficiency.

In this project, the **Perceptron**, **Logistic Regression**, and **Decision Trees** showed favorable performance while maintaining lower power consumption compared to more complex models.

## Conclusion

This project demonstrates how to generate a dataset for branch prediction using Intel’s Pin Tool, along with the performance of different machine learning models for predicting branch behavior. It also highlights the importance of power consumption in designing efficient branch predictors. While more complex models may offer slightly higher accuracy, simpler models provide significant advantages in terms of energy efficiency, which is a key consideration for hardware implementations.