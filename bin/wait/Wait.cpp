/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Wait.h"
#include <ProcessClient.h>

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for a child process to change its state to either exit or terminate");
    parser().registerPositional("PID", "wait for the given child process to change its state");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    pid_t pid = 0;
    
    //grab the argument, which is the process ID, and convert it to int of process ID
    if((pid = atoi(arguments().get("PID"))) == 0){
        ERROR("invalid PID `" << arguments().get("PID") << "'");
        return InvalidArgument;
        /*
            **NOTE** atoi returns 0 regardless if input is a string "0" or an invalid input
            This makes the valid input 0 becomes invalid
        */ 
    }
    if(pid == getpid()){    //input PID is the current PID
        ERROR("PID " << arguments().get("PID") << " is not a child process of this shell");
        return InvalidArgument;
    }

    ProcessClient::Info info;
    ProcessClient proc;
    proc.processInfo(pid, info);    //get the input process ID info

    int exit_stat;
    
    pid_t current_ppid = getppid(); //get the current process parent PID
    pid_t target_ppid = info.kernelState.parent; //get the input process Parent PID

    // add a way to wait for the input pid to wait for that process to complete using waitpid()
    // add a way to handle if the input pid is valid BUT is not the child process (one way is to use ProcessClient:: Info)

    // Done
    return Success;
}
