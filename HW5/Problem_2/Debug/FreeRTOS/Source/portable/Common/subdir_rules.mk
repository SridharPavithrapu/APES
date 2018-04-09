################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/Common/mpu_wrappers.obj: ../FreeRTOS/Source/portable/Common/mpu_wrappers.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/sridh/workspace_v8/Problem_2" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="C:/Users/sridh/workspace_v8/Problem_2/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/Users/sridh/workspace_v8/Problem_2/FreeRTOS/Source/portable/Common" --include_path="C:/Users/sridh/workspace_v8/Problem_2/FreeRTOS/Source/include" --include_path="C:/Users/sridh/workspace_v8/Problem_2/FreeRTOS" --include_path="C:/FreeRTOSv10.0.1/FreeRTOS/Demo/CORTEX_M4F_MSP432_LaunchPad_IAR_CCS_Keil" --define=ccs="ccs" --define=TARGET_IS_TM4C123_RA0 --define=PART_TM4C1294NCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/Source/portable/Common/mpu_wrappers.d_raw" --obj_directory="FreeRTOS/Source/portable/Common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


