<#
.SYNOPSIS
    A simple TCP port scanning script for use from a Windows host
.PARAMETER

.EXAMPLE
     Get-Ports 10.10.0.1 137
     Get-Ports 10.10.0.1 (135,137,445)
     Get-Ports (Get-Content .\ips.txt) 137
     Get-Ports (Get-Content .\ips.txt) (135,137,445)
     0..255 | foreach { Get-Ports 10.10.0.$_ 137 }
     0..255 | foreach { Get-Ports 10.10.0.$_ (135,137,445) }

.NOTES
    FILENAME: TCPscan.ps1
    AUTHOR: @linkavych
    Modified: 2021-06-24
#>
$lines="=============================="
function writer($a) {
    Write-Host
    Write-Host -ForegroundColor DarkGreen $lines
    Write-Host -ForegroundColor DarkBlue " "$a
    Write-Host -ForegroundColor DarkGreen $lines
}

function Get-Ports {
    param (
        $hosts,
        $ports
    )
    if (!$ports) {
        writer "Usage: Get-Ports <host> <ports>"
        return
    }
    $results = ".\scan_results.txt"
    ForEach($port in [array]$ports) {
        ForEach($hst in [array]$hosts){
            $x = (Get-Content $results -ErrorAction SilentlyContinue | Select-String "^$hst,tcp,$port,")
            if ($x) {
                (Get-Content $results) | Select-String "^$hst,tcp,$port,"
                continue
            }
            $msg = "$hst,tcp,$port,"
            $tcp = New-Object System.Net.Sockets.TcpClient
            $conn = $tcp.ConnectAsync($hst,$port)
            for($i=0; $i -lt 10; $i++){
                if ($conn.IsCompleted){ break; }
                Start-Sleep -Milliseconds 100
            }
            $tcp.Close();
            $resp = "Filtered"
            if ($conn.IsFaulted -and $conn.Exception -match "actively refused"){
                $resp = "Closed"
            } elseif ($conn.Status -eq "RanToCompletion"){
                $resp = "Open"
            }
            $msg += $resp
            Write-Host $msg
            $msg | Out-File -FilePath '.\scan_results.txt' -Append
        }
    }
}