//g++ chernobyl.cpp -o chernobyl

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <thread>
#include <chrono>
#include <atomic>



std::atomic<bool> timeExpired(false);


uint8_t encodedPassword[] = { 0x34,0x2b,0x3e,0x38,0x44,0x5e,0x5e,0x56,0x59,0x2c,0x21,0x0c,0x0e,0x0d,0x12,0x06,0x01}; 
size_t passwordLength = sizeof(encodedPassword) / sizeof(encodedPassword[0]);


std::string FAKE_PASSWORD = "C0rrect_P4ssw0rd";



// Decodes the XOR-encoded password
std::string decodePassword() {
    std::string decoded;
    const char* key = "fission"; 
    size_t keyLen = 7; // Length of "fission"

    for (size_t i = 0; i < passwordLength; i++) {
        decoded += static_cast<char>(encodedPassword[i] ^ key[i % keyLen]);
    }
    return decoded;
}
// Converts hex array to ASCII and XORs with 'A'
void shutdown_reactor(const std::string& input) {

    if (input != "AZ-5") {
        std::cout << "Control rods did not fully insert! Reactor explosion imminent...\n";
        return;
    }
    
    // da flag
    uint8_t hexArray[] = {
    0x5b,0xba,0x82,0x6e,0x8f,0xbd,0x63,
    0x74,0x53,0x61,0x68,0xba,0x67,0x62,
    0x64,0x90,0x5f,0xbc,0x68,0x73,0x68,
    0x71,0xbb,0x7e,0x67,0xba,0x5c,0x90,
    0x5f,0xbd,0x60,0x84,0x53,0xbc,0x5f,
    0xbb,0x68,0x5f,0x54,0xbb,0x67,0x5e,
    0x70,0xbf,0x90,0x5b,0xb7,0xb7
        };
    size_t hexArraySize = sizeof(hexArray) / sizeof(hexArray[0]);

    std::cout << "[*] Reactor Successfully stalled!\n";

    // Reactor status messages 
    const char* messages[] = {
         "Checking core temperature... Normald2VsbA==",
        "Verifying control rod position... Status: In ZG9uZQ==",
        "Coolant pressure... Stable aXQg",
        "Turbine output... Optimalc2VlbXM=",
        "Containment integrity... SecuredGhhdA==",
        "Monitoring neutron flux... Within safe levels eW91",
        "Analyzing reactor stability... Stable",
        "Diagnostic check: Control system... FunctionalbWFuYWdlZA==",
        "Thermal monitoring... NormaldG8=",
        "Primary power grid... Operational",
        "Secondary backup systems... Onlinec29sdmU=",
        "All safety checks... PASSEDdGhpcw==",
        "Authentication required...",
        "Neutron moderator... ActivecmV2ZXJzZQ==",
        "Emergency shutdown system... Armed",
        "Reactor pressure vessel integrity... Verified",
        "SCRAM override status... Disabled ZW5naW5lZXJpbmc=",
        "Battery backup... Fully charged",
        "Electrical grid synchronization... StableY2hhbGxlbmdl",
        "Transformer cooling... Nominal",
        "Gamma radiation levels... Normal",
        "FLAG status ..............FOUND!",
        "Containment seals... Secured",
        "Cybersecurity scan... No anomalies detectedaGVoZWhlaGVoZWU=",
        "Reactor data logging... Enabled",
        "Cooling tower efficiency... Maximum capacity",
        "Hydrogen recombiner... Active QWZ0ZXJBbGw="
    };

    // Print reactor diagnostics with a 500ms delay between messages
    for (const char* msg : messages) {
        std::cout << msg << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "Reactor Stabalized";
    for (size_t i = 0; i < hexArraySize; i++) {
        char decodedChar = (hexArray[i] - 'R') ^ 'X';
        std::cout << decodedChar;
    }
    std::cout << "\n";
   
}

// Timer function 
void countdownTimer() {
    for (int i = 10; i > 0; --i) {
        if (timeExpired.load()) return;  
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    timeExpired.store(true);
    std::cout << "\n[CRITICAL] Reactor meltdown! You ran out of time!\n";
    std::exit(EXIT_FAILURE);
}

// Reactor shutdown sequence with 30-second timer
void overload() {
    std::string switchInput, passInput;
    std::string realPassword = decodePassword();

    std::cout << "[WARNING] Reactor core unstable!\n";
    
    // Start the timer in a separate thread
    std::thread timerThread(countdownTimer);

    std::cout << "Enter the emergency shutdown switch: ";
    std::cin >> switchInput;

    std::cout << "Enter the reactor override password: ";
    std::cin >> passInput;

    timeExpired.store(true);  
    timerThread.join();  

    if (passInput == FAKE_PASSWORD) {
        std::cout << "ACCESS DENIED! Reactor core meltdown...\n";
        std::exit(EXIT_FAILURE);
        return;
    }

    if (passInput == realPassword) {
        shutdown_reactor(switchInput);
    } else {
        std::cout << "Wrong password! Reactor explosion imminent...\n";
        std::exit(EXIT_FAILURE);
    }
}

bool isValidArgument(const char* arg) {
    size_t len = strlen(arg);
    
    if (len < 9) return false;  // Minimum required length
    
    return (arg[0] == '-') &&
           (arg[len -1 ] == 'n') &&
           (arg[2] == 'm') &&
           ((arg[4] - 0x42) == 0x2A) &&
           (arg[5] == (0x45 + 0x2F)) &&
           (arg[8] == 0x88) &&
           ((arg[6] ^ 0x44) == 0);
}

int main(int argc, char *argv[]) {
    if (argc < 2 || isValidArgument(argv[1])) {
        srand(time(0));
        int a, b, answer;
        while (true) {
            a = rand() % 100;
            b = rand() % 100;
            std::cout << "Lets see if you're a real nuclear scientist\n";
            std::cout << "Solve: " << a << " + " << b << " = ";
            std::cin >> answer;
            if (answer == a + b) {
                std::cout << "Correct! Next question...\n";
            } else {
                std::cout << "Incorrect! Try again.\n";
                return 0;
            }
        }
    }

    overload();  // Start reactor shutdown sequence if correct argument is provided
    return 0;
}
