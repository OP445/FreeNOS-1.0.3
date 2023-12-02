#include <Types.h>
#include <Macros.h>
#include <stdio.h>
#include <unistd.h>
#include <ProcessClient.h>
#include "ProcessList.h"

ProcessList::ProcessList(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    // Display output list
    parser().setDescription("Output system process list");
    // Display long list of priority levels
    parser().registerFlag('l', "priority", "Lists priority levels of all processes");
}

ProcessList::Result ProcessList::exec()
{
    const ProcessClient process;
    String out;
    // Print header with the new "Priority" column
    if (arguments().get("priority"))
    {
         out << "ID  PARENT  USER GROUP STATUS CMD   PRIORITY\r\n";
    }
    else {
        
    out << "ID  PARENT  USER GROUP STATUS     CMD\r\n";
    }

    // Loop processes
    for (ProcessID pid = 0; pid < ProcessClient::MaximumProcesses; pid++)
    {
        ProcessClient::Info info;

        const ProcessClient::Result result = process.processInfo(pid, info);
        if (result == ProcessClient::Success)
        {
            DEBUG("PID " << pid << " state = " << *info.textState);
            // Output a line with the new "Priority" column
            if (arguments().get("priority"))
                char line[128];
                snprintf(line, sizeof(line),
                        "%3d %9d %4d %5d %10s %32s\r\n",
                        pid, info.kernelState.priority, info.kernelState.parent,
                        0, 0, *info.textState, *info.command, info.priority);
                out << line;
            else
            {
                char line[128];
                snprintf(line, sizeof(line),
                        "%3d %7d %4d %5d %10s %32s\r\n",
                        pid, info.kernelState.parent,
                        0, 0, *info.textState, *info.command, info.priority);
                out << line;
            }
        }
    }

    // Output the table
    write(1, *out, out.length());
    return Success;
}
