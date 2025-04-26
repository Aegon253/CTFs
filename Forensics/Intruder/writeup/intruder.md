# Intruder  

## Challenge Description  
An attacker managed to intrude our local network and send suspicious links to most of our employees. One of them clicked it and downloaded a suspicious file and even ran it.
The file happened to contain a malicious exe,this granted the attacker acces to out system.
The attacker only left a message in a file and made changes to ensure persistence.
We managed to get a hold of the attackers activities, Your job is to find out. 
Where was the malicious executable stored(Dir name) ?
In which file did the attacker leave his message? And what is the parent PID of that process
What is the name of the modification he made to ensure persistence and on for what file?

 

## Steps to Solve:  

1. **Where was the malicious executable stored(Dir name) ?**  
   - Open the given file in `Procmon`.  
   - Apply the **File Modification** filter to track changes and identify the path of the malicious `.exe` file.  

2. **In which file did the attacker leave his message?**  
   - Scroll through the logs until you find a file named `Thr33_arms.txt`.  
   - This file appears to follow a **Ben 10**-themed naming convention and is likely created by the attacker.  
   - Check its **Properties** to retrieve the **Parent Process ID (PID)**.  

3. **What is the name of the modification he made to ensure persistence and on for what file?**  
   - The attacker has hidden an entry in the **Run** folder in the **Windows Registry** to maintain persistence.  
   - Apply a **Registry filter** in `Procmon` to locate an entry related to the malicious file.  

4. **Complete the Challenge**  
   - Once you find the registry entry, you have successfully uncovered the persistence mechanism used by the attacker.  
