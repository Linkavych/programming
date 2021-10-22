<#
.SYNOPSIS
    Check the file path for recently modified files.
    
.PARAMETER days
    Specify the number of days to check within (e.g. 7).

.PARAMETER filepath
    Specify the file past to check for modify times.

.PARAMETER depth
    Specify the depth for recursion.

.EXAMPLE
    PS> . .\ConfirmFiles.ps1
    PS> Confirm-Files 2 "C:\temp"


.NOTES
    FILENAME: ConfirmFiles.ps1
    AUTHOR: @Linkavych
    MODIFIED: 2021-06-24
#>

$lines="=============================="

function writer($a) {
    Write-Host 
    Write-Host -ForegroundColor DarkGreen $lines
    Write-Host -ForegroundColor DarkBlue " "$a
    Write-Host -ForegroundColor DarkGreen $lines
}

function Confirm-Files {
    param ($days, $filepath,$depth)
    
    Get-ChildItem -Path $filepath -Recurse -Depth $depth| 
    Where-Object { $_.CreationTime -gt (Get-Date).AddDays('-'+$days) } |
    Select-Object FullName, LastWriteTime

    writer "Files Modified within the last $days day(s)."
}

