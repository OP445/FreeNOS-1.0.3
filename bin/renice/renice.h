#ifndef __BIN_Renice_Renice_H
#define __BIN_Renice_Renice_H

#include <POSIXApplication.h>

/**
 * @addtogroup bin
 * @{
 */

 /**
  * Stop executing for some time.
  */
class Renice : public POSIXApplication
{
public:

    /**
     * Constructor
     *
     * @param argc Argument count
     * @param argv Argument values
     */
    Renice(int argc, char** argv);

    /**
     * Destructor
     */
    virtual ~Renice();

    /**
     * Execute the application.
     *
     * @return Result code
     */
    virtual Result exec();
};

/**
 * @}
 */

#endif /* __BIN_RENICE_RENICE_H */
