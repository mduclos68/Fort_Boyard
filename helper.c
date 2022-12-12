// helper.c
// Helper functions used by multiple modules
#include "helper.h"

// Helper function that reads from a file specified 
int Helper_readFromFile(char *fileName){

    // open file and check if successful
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL) {
        printf("ERROR: Unable to open file (%s) for read. %s.\n", fileName, strerror(errno));
        exit(-1);
    }

    // Read string (line)
    const int MAX_LENGTH = 1024;
    char buff[MAX_LENGTH];
    fgets(buff, MAX_LENGTH, pFile);

    // Close
    fclose(pFile);
    pFile = NULL;

    // convert output to integer and return
    return atoi(buff);
}

void Helper_writeToFile(char *fileName, char* message){
    // Use fopen() to open the file for write access.
    FILE *pFile = fopen(fileName, "w");
    if (pFile == NULL) {
        printf("ERROR: Unable to open %s file. %s\n", fileName, strerror(errno));
        exit(1);
    }

    // Write to data to the file using fprintf():
    fprintf(pFile, "%s", message);

    // Close the file using fclose():
    fclose(pFile);
    pFile = NULL;
    Helper_sleepForMs(300); // sleep for 300ms
}

// Helper function that runs a given system command
void Helper_runCommand(char* command){
    // Execute the shell command (output into pipe)
    
    FILE *pipe = popen(command, "r");

    // Ignore output of the command; but consume it 
    // so we don't get an error when closing the pipe.
    
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe)) {
        if (fgets(buffer, sizeof(buffer), pipe) == NULL)
        break;
    }

    // Get the exit code from the pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));
    if (exitCode != 0) {
        perror("Unable to execute command:");
        printf(" command: %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }
}

// Helper function that puts the system to slep for the specified number of Ms
void Helper_sleepForMs(long long delayInMs){
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}


// Helper function that gets the current time in Ms
long long getTimeInMs(void){
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long long seconds = spec.tv_sec;
    long long nanoSeconds = spec.tv_nsec;
    long long milliSeconds = seconds * 1000 + nanoSeconds / 1000000;
    return milliSeconds;
}

