################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Type.cpp \
../fs.cpp \
../install.cpp \
../main.cpp \
../parcel.cpp \
../source.cpp \
../update.cpp 

OBJS += \
./Type.o \
./fs.o \
./install.o \
./main.o \
./parcel.o \
./source.o \
./update.o 

CPP_DEPS += \
./Type.d \
./fs.d \
./install.d \
./main.d \
./parcel.d \
./source.d \
./update.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


