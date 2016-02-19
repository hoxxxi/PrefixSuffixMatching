################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Main.cpp \
../NGramGraph.cpp \
../ProbMatrix.cpp \
../QualityScore.cpp \
../StringMatching.cpp 

OBJS += \
./Main.o \
./NGramGraph.o \
./ProbMatrix.o \
./QualityScore.o \
./StringMatching.o 

CPP_DEPS += \
./Main.d \
./NGramGraph.d \
./ProbMatrix.d \
./QualityScore.d \
./StringMatching.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


