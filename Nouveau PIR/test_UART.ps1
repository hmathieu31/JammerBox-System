#!/usr/bin/env pwsh

Write-Output "Testing the communication of fault injections between the RaspberryPi and the STM32..."
$listofInjections = "CONFIGCRK", "CONFIGCAM", "RESETCRK", "RESETCAM", "CRKRUNOUT",
"CAMPATERR", "CAMDELAY", "CRKTOOTHOFF", "CRKGAPNOTDET", "CRKPOSNENGSTST", "CRKSEGADPERRLIM"

$allTestsPassed = $true

foreach ($failureInjection in $listofInjections) {
    Write-Output $failureInjection | Out-Null
    $execResult = ./UART_Script.py $failureInjection
    if ($execResult.Contains("Port could not be opened")) {
        throw "The connection could not be established with the STM32"
    }
    $execResult[-2] -match "Data sent: (.*)"  | Out-Null
    $sentData = $Matches[1]
    $execResult -match "Data received:"  | Out-Null
    $receivedData = $Matches[1]
    if ($sentData -ne $receivedData) { $allTestsPassed = $false }
    if ($allTestsPassed -eq $false) {
        Write-Output ("❌ Test ${failureInjection} did not return the expected output")
        Write-Output ("Expected ${sentData}")
        Write-Output ("Received ${receivedData}")
    }
}
if ($allTestsPassed -eq $true) { Write-Output "
✅ All failure injection tests passed successfully
" }