#ifndef GPIOHANDLER_H
#define GPIOHANDLER_H

#include <stdbool.h>


    
//     //@brief GPIOHandler ructor
//     //@param _gpio initial GPIO
//    GPIOHandler(unsigned int _gpio);

//    /**
//     * @brief gpio
//     * @return current gpio
//     */
//    unsigned int    gpio() ;

    /**
     * @brief setGpio
     * @param _gpio GPIO
     */
    void    setGpio(unsigned int _gpio);

    /**
     * @brief setGpioValue sets GPIO Value
     * @param _Value true = high
     */
    void    setValue(bool _Value , char* gpio_number);

    //    void    operator=(bool _value);

    /**
     * @brief getGpioValue returns GPIO Value
     * @return
     */
    bool    getValue(char* gpio_number);

    /**
     * @brief switchGpioValue switches gpio Value
     */
    void    switchValue(char *gpio_number);

    /**
     * @brief exportEnabled
     * @return true = exporting is enabled, false = unexport
     */
    bool    exportEnabled(char* gpio_number) ;

    /**
     * @brief enableExport
     * @param _enable true = export, false = unexport
     */
    void    enableExport(bool _enable, char *gpio_number) ;

    /**
     * @brief setDirection
     * @param _dir true = "out", false = "in"
     */
    void    setDirection(bool _dir , char *gpio_number);

    /**
     * @brief direction
     * @return true = "out", false = "in";
     */
    bool    direction(char* gpio_number) ;

    /**
     * @brief gpioPath
     * @return GPIO system path of current GPIO
     */
    char*  gpioPath(char* gpio_number) ;

    /**
     * @brief directionPath returns path to direction system file of current GPIO.
     * @return path to direction file
     */
    char*  directionPath(char* gpio_number) ;

    /**
     * @brief valuePath returns path to value system file of current GPIO.
     * @return
     */
    char*  valuePath(char* gpio_number) ;

//    /**
//     * @brief gpioStr returns current char* number in char* forml
//     * @return
//     */
//    char*  gpioStr() ;

    /**
     * @brief className
     * @return
     */
     char* className() ;


    /// GPIO number
//    unsigned int  gpio_;

    /// Path to GPIO in Pironex's Angstrom Linux
//    static  char* GPIO_SYS_PATH_;

    /// Path to GPIO export file
    char* exportPath();

    /// Path to GPIO unexport file
    char *unexportPath();





#endif // GPIOHANDLER_H
