// renice.h

#ifndef __BIN_RENICE_RENICE_H
#define __BIN_RENICE_RENICE_H

#include <POSIXApplication.h>

/**
 * @addtogroup bin
 * @{
 */

/**
 * Change the priority level of a process.
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
    Renice(int argc, char **argv);

    /**
     * Execute the application.
     *
     * @return Result code
     */
    Result exec() override;
};

/**
 * @}
 */

#endif /* __BIN_RENICE_RENICE_H */
