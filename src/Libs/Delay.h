/* ************************************************************************** */
/** Descriptive File Name

  @Company
    MOSY

  @File Name
    Delay.h

  @Summary
    Generate delays.

  @Description
    Generate delays.
 */
/* ************************************************************************** */

#ifndef _DELAY_H    /* Guard against multiple inclusion */
#define _DELAY_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

//#include "../system_config.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  Cpu constants.
     */


    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        cpu constants.
    
      @Description
        Cpu constants for generating accurate time delays.
    
      @Remarks
        Cpu constants.
     */

#ifdef _SYSTEM_CONFIG_H
    #define CPU_FREQ    SYS_CLK_FREQ
#else
    #define CPU_FREQ    48000000
#endif

//#define INSTRUCTION_TIME    1/CPU_FREQ
#define NOPS_TO_MS          CPU_FREQ/2000

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  Delays
     */

    // *****************************************************************************
    void delay_cpu(unsigned long delay_value);
    
    void delay_ms(unsigned int delay);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
