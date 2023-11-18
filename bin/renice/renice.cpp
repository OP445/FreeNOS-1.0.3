// renice.cpp

#include <Types.h>
#include <Macros.h>
#include <stdio.h>
#include <unistd.h>
#include <ProcessClient.h>
#include <renice.h>

class Renice : public POSIXApplication
{
public:
    Renice(int argc, char **argv)
        : POSIXApplication(argc, argv)
    {
        parser().setDescription("Change the priority level of a process");
        parser().addPositionalArgument("pid", "Process ID", Argument::Required);
        parser().addPositionalArgument("priority", "New priority level (1 to 5)", Argument::Required);
    }

    Result exec() override
    {
        const ProcessClient process;

        // Retrieve arguments
        int pid = atoi(parser().positionals()[0]);
        int newPriority = atoi(parser().positionals()[1]);

        // Check if the priority is within the valid range (1 to 5)
        if (newPriority < 1 || newPriority > 5)
        {
            fprintf(stderr, "Error: Priority level must be between 1 and 5.\n");
            return InvalidArgument;
        }

        // Change the priority of the process
        ProcessClient::Result result = process.setPriority(pid, newPriority);

        // Check the result and display appropriate messages
        if (result == ProcessClient::Success)
        {
            printf("Priority of process %d changed to %d.\n", pid, newPriority);
            return Success;
        }
        else if (result == ProcessClient::NoSuchProcess)
        {
            fprintf(stderr, "Error: No such process with ID %d.\n", pid);
        }
        else
        {
            fprintf(stderr, "Error: Unable to change priority of process %d.\n", pid);
        }

        return UnknownError;
    }
};

int main(int argc, char **argv)
{
    Renice reniceApp(argc, argv);
    return reniceApp.run();
}
