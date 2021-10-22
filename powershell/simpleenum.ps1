<#
.SYNOPSIS
    A simple way to check the security status of a Windows machine using powershell.
.PARAMETER extended
    Does more extensive checking of the system
.EXAMPLE
    PS C:\> simpleenum.ps1 extended
.NOTES
    Filename: simpleenum.ps1
    Author: Adam V. Link
    Modified: 2021-06-24
#>
param($extended)

$lines="=============================="

function writer($a){
    Write-Host
    Write-Host -ForegroundColor DarkGreen $lines
    Write-Host -ForegroundColor Green " "$a
    Write-Host -ForegroundColor DarkGreen $lines
}

$basic_commands = [ordered]@{

    'System Information'                = 'Get-ComputerInfo | Format-Table OSVersion, OSBuildNumber, OSArchitecture, CSName, CSDomain';
    'Environment Variables'             = 'Get-ChildItem Env: | Format-Table key,value';
    'System Patch Levels'               = 'Get-HotFix -Description "Security*"| Sort-Object -Property InstalledOn -Descending';
    'Connected Drives'                  = 'Get-PSDrive | Where-Object {$_.Provider -like "Microsoft.Powershell.Core\FileSystem"} | Format-Table Name, Root';
    'Current User'                      = 'Write-Host $env:UserDomain\$env:UserName';
    'Current User Privileges'           = 'Start-Process "whoami" -Argumentlist "/priv" -NoNewWindow -Wait | Format-Table';
    'System Users'                      = 'Get-LocalUser | Format-Table Name, Enabled, LastLogon, Description, SID';
    'User Directories'                  = 'Get-ChildItem C:\Users | Format-Table Name';
    'Check Logged In Users'             = 'Start-Process "qwinsta" -NoNewWindow -Wait | Format-Table';
    'Local Groups'                      = 'Get-LocalGroup | Format-Table Name, SID';
    'Local Admins'                      = 'Get-LocalGroupMember Administrators | Format-Tables Name, PrincipalSource';
    'Password Policy'                   = 'Start-Process "net" -ArgumentList "accounts" | Format-Table';
    'Credential Manager'                = 'Start-Process "cmdkey" -ArgumentList "/list" -NoNewWindow -Wait | Format-Table';
    'AntiVirus Check'                   = 'Start-Process "sc" -ArgumentList "query windefend" -NoNewWindow -Wait | Format-Table';
    'AppLocker Policy Check'            = 'Get-AppLockerPolicy -Effective -xml';
    'Installed Software'                = 'Get-ChildItem "C:\Program Files", "C:\Program Files (x86)" | Format-Table Parent,Name,LastWriteTime';
    'Running Processes'                 = 'Get-CimInstance -Classname Win32_Process | Format-Table Name,ProcessID,ParentProcessID,CommandLine -Autosize';
    'Service Checks'                    = 'Get-CimInstance -Classname Win32_Service | Where {$_.state -eq "Running"} | Format-Table Name, DisplayName, PathName';
    'Scheduled Tasks'                   = 'Get-ScheduledTask | Where {$_.TaskPath -notlike "\Microsoft*"} | Format-Table TaskName,TaskPath,State';
    'Check Task Folder'                 = 'Get-ChildItem C:\Windows\Tasks | Format-Table';
    'Startup Tasks'                     = 'Get-CimInstance Win32_StartupCommand | Select Name, Command, Location, User | Format-List';
    'NetWork Information'               = 'Get-NetIPConfiguration | Format-Table InterfaceAlias,InterfaceDescription,IPv4Address';
    'DNS Servers'                       = 'Get-DnsClientServerAddress -AddressFamily IPv4 | Format-Table';
    'ARP Cache'                         = 'Get-NetNeighbor -AddressFamily IPv4 | Format-Table ifIndex,IPAddress,LinkLayerAddress,State';
    'Routing Information'               = 'Get-NetRoute -AddressFamily IPv4 | Format-Table DestinationPrefix,NextHop,RouteMetric,ifIndex';
    'Network Connections'               = 'Start-Process "netstat" -ArgumentList "-ano" -NoNewWindow -Wait | Format-Table';
    'Firewall Profile'                  = 'Get-NetFirewallProfile';

}
$extended_commands = [ordered]@{
    # LOGGING AND FILE/Folder CHECKS GO HERE
    'Folders with Everyone Permissions'             = 'Get-ChildItem "C:\Program Files\*", "C:\Program Files (x86)\*" | % { try { Get-Acl $_ -EA SilentlyContinue | Where {($_.Access|select -ExpandProperty IdentityReference) -match "Everyone"} } catch {}} | Format-Table';
    'Folders with BUILTIN\User Permissions'         = 'Get-ChildItem "C:\Program Files\*", "C:\Program Files (x86)\*" | % { try { Get-Acl $_ -EA SilentlyContinue | Where {($_.Access|select -ExpandProperty IdentityReference) -match "BUILTIN\Users"} } catch {}} | Format-Table';
    'Checking registry for AlwaysInstallElevated'   = 'Test-Path -Path "Registry::HKEY_CURRENT_USER\SOFTWARE\Policies\Microsoft\Windows\Installer" | ft';
    'User Autologon Registry Items'                 = 'Get-ItemProperty -Path "Registry::HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\WinLogon" | Select "Default*" | Format-Table';
    'Searching for SAM backup files'                = 'Test-Path %SYSTEMROOT%\repair\SAM ; Test-Path %SYSTEMROOT%\system32\config\regback\SAM';
    'Unquoted Service Paths'                        = 'Get-WmiObject -class Win32_Service -Property Name, DisplayName, PathName, StartMode | Where {$_.StartMode -eq "Auto" -and $_.PathName -notlike "C:\Windows*" -and $_.PathName -notlike ''"*''} | select PathName, DisplayName, Name | Format-Table';
    'Check Hosts File'                              = 'Get-Content -Path C:\Windows\System32\drivers\etc\hosts';
    'Searching for Unattend and Sysprep files'      = 'Get-Childitem –Path C:\ -Include *unattend*,*sysprep* -File -Recurse -ErrorAction SilentlyContinue | where {($_.Name -like "*.xml" -or $_.Name -like "*.txt" -or $_.Name -like "*.ini")} | Out-File C:\temp\unattendfiles.txt';
    'Searching for web.config files'                = 'Get-Childitem –Path C:\ -Include web.config -File -Recurse -ErrorAction SilentlyContinue | Out-File C:\temp\webconfigfiles.txt';
    'Searching for other interesting files'         = 'Get-Childitem –Path C:\ -Include *password*,*cred*,*vnc* -File -Recurse -ErrorAction SilentlyContinue | Out-File C:\temp\otherfiles.txt';
    'Searching for various config files'            = 'Get-Childitem –Path C:\ -Include php.ini,httpd.conf,httpd-xampp.conf,my.ini,my.cnf -File -Recurse -ErrorAction SilentlyContinue | Out-File C:\temp\configfiles.txt'
    'Searching HKLM for passwords'                  = 'reg query HKLM /f password /t REG_SZ /s | Out-File C:\temp\hklmpasswords.txt';
    'Searching HKCU for passwords'                  = 'reg query HKCU /f password /t REG_SZ /s | Out-File C:\temp\hkcupasswords.txt';
    'Searching for files with passwords'            = 'Get-ChildItem c:\* -include *.xml,*.ini,*.txt,*.config -Recurse -ErrorAction SilentlyContinue | Where-Object {$_.PSPath -notlike "*C:\temp*" -and $_.PSParentPath -notlike "*Reference Assemblies*" -and $_.PSParentPath -notlike "*Windows Kits*"}| Select-String -Pattern "password" | Out-File C:\temp\password.txt';
    'Searching for Alternate Data Streams'          = 'Get-ChildItem -Recurse | % {gi $_.Fullname -stream *} | where stream -ne ":$Data" | Out-File C:\temp\ads.txt';
}

function RunCommands($commands) {
    ForEach ($command in $commands.GetEnumerator()) {
        writer $command.Name
        Invoke-Expression $command.Value
    }
}

RunCommands($basic_commands)

if ($extended) {
    if ($extended.ToLower() -eq 'extended'){
        $result = Test-Path C:\temp
        if ($result -eq $False) {
            New-Item c:\temp -type directory
        }
        writer "[+] Writing detailed files to c:\temp\..."
        RunCommands($extended_commands)
        writer "[+] Completed! Files in c:\temp\"
    }
}
else {
    writer "[+] Completed!"
}
