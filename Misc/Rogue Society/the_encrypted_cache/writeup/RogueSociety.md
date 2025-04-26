# Rogue Society - Misc Challenge  

## Challenge Description  
A **rogue developer** left our society to form his own, naming it **KHK**—whatever that means.  

Our **brilliant hackers** tracked him down and seized his **laptop**.  

Inside, we found a **CTF poster**, but **the flag was missing**, its parts hidden within the files.  

### Your Mission:  
Can you recover the **stolen flag**?  

## **Hints**  
🔹 **Hint 1:** `"Hello Pieter! did u control the stack"`  
🔹 **Hint 2:** `"If u look at the logo, esoteric problems require esoteric solutions"`  

---  

## **Writeup: How to Solve the Challenge**  

### Step 1️⃣: Find the First Part of the Flag  
- Open the **poster image**.  
- Look closely at the **symbols at the end**—they appear **unusual**.  
- These are written in **Wingdings cipher**.  
- It appears at the 3rd or 4th option in dCode symbol ciphers
- Use an **online Wingdings decoder** to extract the **first part of the flag**.  

### Step 2️⃣: Extract Hidden Files  
- Use `binwalk` to **extract** embedded files from `poster.png`.  
- This will reveal **two hidden images**:  
  - One is a **rabbithole** (`secret.jpg`)—ignore it.  
  - The other contains **the next clue**.  

### Step 3️⃣: Decode the Logo  
- The extracted image contains a **mysterious pattern**.  
- Reverse image after a lot of khwaari search reveals it is written in **Piet programming language**—an **esoteric** language.  
- `Hint 1` references **stack-based execution**, hinting at Piet.  
- `Hint 2` tells us to **look for esoteric solutions**.  
- Use an **online Piet interpreter** to **decode the image**.  

### Step 4️⃣: Retrieve the Flag  
- Running the **Piet code** will reveal the **second part of the flag**:  
