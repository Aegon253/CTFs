# Challenge: Chernobyl

## Challenge Description
You have been provided with a mysterious binary. Your task is to reverse-engineer it to uncover the secrets hidden within.

## Steps to Solve:
1. **Decompile the Binary**  
   - Analyze the binary using tools like `Ghidra`, `IDA Pro`, or `radare2`.  
   - Identify the command-line arguments required for execution.  

2. **Discover the Required Argument**  
   - The binary requires the argument `--meltdown` to proceed to the `overload` function.

3. **Find the Password**  
   - Within the binary, you will find a password check mechanism.  
   - The correct password to proceed is:  
     ```
     RBMK-1000_Reactor
     ```

4. **Retrieve the Flag**  
   - Once the correct password is provided, the flag will be revealed.  

### or
    - decompile and analyze the reactor shutdown function, if u run it youll get the flag

